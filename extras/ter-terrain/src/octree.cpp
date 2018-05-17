#include "octree.h"

using namespace std;

double dot(const glm::vec3 &A, const glm::vec3 &B) {
	//Returns the dot product, only for a 3 array
	double out = A[0] * B[0] + A[1] * B[1] + A[2] * B[2];
	return out;
}

glm::vec3 cross(const glm::vec3 &A, const glm::vec3 &B) {
	//Returns the cross product only for a 3 array
	glm::vec3 out;
	out[0] = A[1] * B[2] - A[2] * B[1];
	out[1] = A[2] * B[0] - A[0] * B[2];
	out[2] = A[0] * B[1] - A[1] * B[0];
	return out;
}

/*
Input: source point of ray, direction vector of ray, triangle defined by 3 points.
Output: bool of whether there is intersection, intersection point by reference.
Warning: This routine returns false and empty intersection in case the ray is on the same plane as the triangle and goes through. 
Link: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
*/
bool RayTriangle(const glm::vec3 & source, const glm::vec3 & dir, const array<glm::vec3, 3> & tri, glm::vec3 & intersection) {
	const double epsilon = 0.00000001;
	glm::vec3 v0 = tri[0];
	glm::vec3 v1 = tri[1];
	glm::vec3 v2 = tri[2];
	glm::vec3 h, s, q;
	double a, f, u, v;
	glm::vec3 edge1 = glm::vec3(v1[0] - v0[0], v1[1] - v0[1] , v1[2] - v0[2]);
	glm::vec3 edge2 = glm::vec3(v2[0] - v0[0], v2[1] - v0[1] , v2[2] - v0[2]);
	h = cross(dir, edge2);
	a = dot(edge1, h);
	if (a > -epsilon && a < epsilon) {
		//DOES NOT HANDLE CASE WHEN LINE IS PARALLEL TO TRIANGLE PLANE
		return false;
	}
	f = 1 / a;
	s = glm::vec3(source[0] - v0[0], source[1] - v0[1], source[2] - v0[2]);
	u = f * dot(s, h);
	if (u < 0.0 - epsilon || u > 1.0 + epsilon){
		return false;
	}
	q = cross(s, edge1);
	v = f * dot(dir, q);
	if (v < 0.0 - epsilon || u + v > 1.0 + epsilon){
		return false;
	}
	// At this stage we can compute t to find out where the intersection point is on the line.
	double t = f * dot(edge2, q);
	if (t > epsilon) { //ray intersection
		intersection[0] = source[0] + t * dir[0];
		intersection[1] = source[1] + t * dir[1];
		intersection[2] = source[2] + t * dir[2];
		return true;
	}
	else {
		return false;
	}
}

/*
Input: source point of ray, direction vector of ray, interval for the scalar factor for direction vector, box defined by diagonal points low and high.
Output: bool of whether there is intersection.
Link: https://www.cs.utah.edu/~awilliam/box/box.pdf
*/
bool RayBox(const glm::vec3 & source, const glm::vec3 & dir, double low_t, double high_t, const array<glm::vec3, 2> & box) {
	glm::vec3 inv_dir = glm::vec3(1 / dir[0], 1 / dir[1], 1 / dir[2]);
	array<unsigned int, 3> sign;
	sign[0] = inv_dir[0] < 0;
	sign[1] = inv_dir[1] < 0;
	sign[2] = inv_dir[2] < 0;
	double tmin, tmax, tymin, tymax, tzmin, tzmax;
	tmin = (box[sign[0]][0] - source[0]) * inv_dir[0];
	tmax = (box[1 - sign[0]][0] - source[0]) * inv_dir[0];
	tymin = (box[sign[1]][1] - source[1]) * inv_dir[1];
	tymax = (box[1 - sign[1]][1] - source[1]) * inv_dir[1];
	if ((tmin > tymax) || (tymin > tmax)){
		return false;
	}
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (box[sign[2]][2] - source[2]) * inv_dir[2];
	tzmax = (box[1 - sign[2]][2] - source[2]) * inv_dir[2];
	if ((tmin > tzmax) || (tzmin > tmax)){
		return false;
	}
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	return ((tmin < high_t) && (tmax > low_t));
}

/*
Input: triangle defined by 3 points, box defined by diagonal points low and high.
Output: bool of whether there is intersection.
*/
bool TriangleBox(const array<glm::vec3, 3> & triangle, const array<glm::vec3, 2> & box) {
	//There is an intersection iff one of the points of the triangle is not in the box
	for (size_t i = 0; i < 3; ++i) {
		glm::vec3 pt = triangle[i];
		if (box[0][0] > pt[0] || pt[0] > box[1][0]) {
			return false;
		}
		if (box[0][1] > pt[1] || pt[1] > box[1][1]) {
			return false;
		}
		if (box[0][2] > pt[2] || pt[2] > box[1][2]) {
			return false;
		}
	}
	return true;
}

void SDF::init() {
	//Necessary to jump start the build
	//Puts the indices of all faces in the initial root node, since the root contains all faces
	//Theses indices are later pushed down to the leaves
	for (size_t i = 0; i < this->F.size(); ++i) {
		this->indices.push_back((int)i);
	}
}

void SDF::build() {
	if (this->indices.size() == 0) {
		return;
	}
	this->leaves = indices.size();

	//Compute box and add a halo for safety
	glm::vec3 bound_down;
	glm::vec3 bound_up;
	double epsilon = 0.0000000001; //halo
	glm::vec3 first;
	first = this->V.at(this->F.at(this->indices.at(0))[0]);
	bound_up = glm::vec3(first[0] + epsilon, first[1] + epsilon, first[2] + epsilon);
	bound_down = glm::vec3(first[0] - epsilon, first[1] - epsilon, first[2] - epsilon);

	//Find the dimensions in the box, the box has to contain all the 3 points of each face in the node
	for (size_t i = 0; i < this->indices.size(); ++i) {
		for (size_t j = 0; j < 3; ++j) {
			glm::vec3 pt = this->V.at(this->F.at(this->indices.at(i))[j]);
			for (size_t d = 0; d < 3; ++d) {
				if (bound_up[d] < pt[d]) {
					bound_up[d] = pt[d];
				}
				if (bound_down[d] > pt[d]) {
					bound_down[d] = pt[d];
				}
			}
		}
	}
	//Add halo
	bound_up = glm::vec3(bound_up[0] + epsilon, bound_up[1] + epsilon, bound_up[2] + epsilon);
	bound_down = glm::vec3(bound_down[0] - epsilon, bound_down[1] - epsilon, bound_down[2] - epsilon);

	this->box[0] = bound_down;
	this->box[1] = bound_up;

	//More than one triangle remaining in the box, recursion
	if (this->indices.size() > 1) {
		//Compute center
		glm::vec3 mean;
		int nb = this->indices.size();
		mean[0] = bary.at(this->indices.at(0))[0];
		mean[1] = bary.at(this->indices.at(0))[1];
		mean[2] = bary.at(this->indices.at(0))[2];
		for (size_t i = 1; i < nb; ++i) {
			mean[0] = mean[0] + (bary.at(this->indices.at(i))[0] - mean[0]) / (i + 1);
			mean[1] = mean[1] + (bary.at(this->indices.at(i))[1] - mean[1]) / (i + 1);
			mean[2] = mean[2] + (bary.at(this->indices.at(i))[2] - mean[2]) / (i + 1);
		}

		//Compute new indices, split the index set into 8, 1 per quadrant
		array<vector<unsigned int>, 8> sub_indices;

		for (size_t i = 0; i < this->indices.size(); ++i) {
			glm::vec3 pt = bary.at(indices.at(i));
			if (pt[0] > mean[0]) {
				if (pt[1] > mean[1]) {
					if (pt[2] > mean[2]) {
						sub_indices[0].push_back(indices.at(i));
					}
					else {//pt[2] <= mean[2] 
						sub_indices[1].push_back(indices.at(i));
					}
				}
				else {   //pt[1] <= mean[1]
					if (pt[2] > mean[2]) {
						sub_indices[2].push_back(indices.at(i));
					}
					else {//pt[2] <= mean[2]
						sub_indices[3].push_back(indices.at(i));
					}
				}
			}
			else {		 //pt[0] <= mean[0]
				if (pt[1] > mean[1]) {
					if (pt[2] > mean[2]) {
						sub_indices[4].push_back(indices.at(i));
					}
					else {//pt[2] <= mean[2]
						sub_indices[5].push_back(indices.at(i));
					}
				}
				else {   //pt[1] <= mean[1]
					if (pt[2] > mean[2]) {
						sub_indices[6].push_back(indices.at(i));
					}
					else //pt[2] <= mean[2]
						sub_indices[7].push_back(indices.at(i));
				}
			}
		}
		indices.clear(); //free memory

		//Create children and recurse
		for (size_t i = 0; i < 8; ++i) {
			if (sub_indices[i].size() > 0) {
				this->children[i] = unique_ptr<SDF>(new SDF(this->V, this->F, this->bary));
				this->children[i]->indices = sub_indices[i];
				this->children[i]->build();
			}
			else {
				this->children[i] = nullptr;
			}
		}
	}
	return;
}

vector<glm::vec3> SDF::query(glm::vec3 & source, glm::vec3 & dir) const {
	/*
	Input: vector of source point(s) of ray, vector of direction(s) vector of ray.
	Output: first intersection point with the mesh of each ray defined by source and dir.
	Warning: it is yet unclear whether the first intersection point is the right one. 
	Maybe a condition such as if the first intersection point is too close, then pick the second one would make sense here.
	*/
	//This function also works by recursion, since we want at first all intersection points with the mesh
	if (this->is_leaf()) {
		glm::vec3 intersection;
		array<glm::vec3, 3> tri;

		int tri_idx = (this->indices).at(0);
		array<unsigned int, 3> pts_idx = (this->F).at(tri_idx);
		tri[0] = (this->V).at(pts_idx[0]);
		tri[1] = (this->V).at(pts_idx[1]);
		tri[2] = (this->V).at(pts_idx[2]);

		bool is_hit = RayTriangle(source, dir, tri, intersection);
		if (is_hit == true) {
			vector<glm::vec3> out = { intersection };
			return out;
		}
		else {
			vector<glm::vec3> empty;
			return empty;
		} //can add epsilon wiggle after
	}
	else { //if this is not a leaf, query until you find the leaf and then concatenate up
		vector<glm::vec3> out;
		for (size_t i = 0; i < 8; ++i) {
			if (this->children[i] != nullptr) { 
				if (true == RayBox(source, dir, 0, DBL_MAX, this->children[i]->box)) { //leap of faith
					vector<glm::vec3> temp = this->children[i]->query(source, dir);
					out.insert(end(out), begin(temp), end(temp));
				}
			}
		}
		return out; //may be empty
	}
};

vector<double> SDF::query(vector<glm::vec3> & inv_normals) const {
	/*
	Input: vector of inverted normals, one per vertiex in this->V.
	Output: closest surface distance from a point in V and the mesh itself.
	Warning: RIGHT now it is returning the distance squared, just change to sqrt to correct that
	*/
	vector<double> sdf;
	for (size_t i = 0; i < inv_normals.size(); ++i) {
		vector<glm::vec3> intersect = this->query((this->V).at(i), inv_normals.at(i));
		double my_min = DBL_MAX;
		for (size_t j = 0; j < intersect.size(); ++j) {
			glm::vec3 diff = { intersect.at(j)[0] - (this->V).at(i)[0], intersect.at(j)[1] - (this->V).at(i)[1],intersect.at(j)[2] - (this->V).at(i)[2] };
			double norm_sq = dot(diff, diff);
			if (my_min > norm_sq && norm_sq > 0.0005) {
				my_min = norm_sq;
			}
		}
		if (my_min != DBL_MAX) {
			sdf.push_back(my_min);
		}
		else {
			sdf.push_back(0); //in case there was "no interection"
		}
	}
	return sdf;
}

bool SDF::is_leaf() const {
	//Returns true is current node is a leaf
	bool is_leaf = true;
	for (int i = 0; i < 8; ++i) {
		if (this->children[i] != nullptr) {
			is_leaf = false;
		}
	}
	return is_leaf;
}
