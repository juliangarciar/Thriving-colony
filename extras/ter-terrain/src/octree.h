/*
Author: Adrian Szatmari
Date: 2018-03-31
License: MIT
Dependencies: None, just drag and drop octree.h into your project. To visualize use libigl.

Description: this is a small header library to compute the Surface Distance Function (SDF). The SDF measures the penetration distance 
in the inward normal direction, until the next surface hit. The following web pages helped for the dev of this code:

WARNING: to save time and memory, this SDF class references the matrices instead of a local copy, therefore do not change their values once
the tree structure is built. 

TODO:
-For some reason the code crashes for very big meshes (>500k faces). I suspect it is a stack/heap issue. 
-Need to adjust automatically the values that SDF outputs for visualization (using igl::jet).
-Need to multithread the build() routine and and query() routine. The first is non trivia, but the strategy is to manually split
the first 8 children into 8 separate threads, and then to unite the output by hand. The query() can be trivially parallelized.   
*/

#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cmath>
#include <memory>
#include <glm/glm.hpp>

class SDF {
	private:
		//Data
		std::vector<glm::vec3> & V;
		std::vector<std::array<unsigned int, 3>> & F;
		std::vector<glm::vec3> & bary; //of the triangles in F

		//Node
		int leaves;
		std::array<glm::vec3, 2> box; //defined by low and high
		std::vector<unsigned int> indices; //of triangles
		std::array<std::unique_ptr<SDF>, 8> children;

		//Methods
		bool is_leaf() const;
	public:
		SDF(std::vector<glm::vec3> & V, std::vector<std::array<unsigned int, 3>> & F, std::vector<glm::vec3> & bary)
			: V(V), F(F), bary(bary) {}; //passing V, F, bary, by reference
		SDF(const SDF& other) = delete; //non-copy move only semantic
		SDF& operator=(const SDF& rhs) = delete; //non-copy move only semantic

		void init(); //necessary
		void build();
		std::vector<glm::vec3> query(glm::vec3 & source, glm::vec3 & dir) const;
		std::vector<double> query(std::vector<glm::vec3> & v_normals) const;
};
