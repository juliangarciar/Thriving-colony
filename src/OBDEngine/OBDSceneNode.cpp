#include "OBDSceneNode.h"

OBDSceneNode::OBDSceneNode(TNode* parent) : OBDEntity() {
	octree = aabb::Tree();

	parent->addChild(rotationNode);
}

OBDSceneNode::OBDSceneNode(OBDSceneNode* parent) : OBDEntity(parent) {
	octree = aabb::Tree();

    parent->addChild(this);
}

OBDSceneNode::~OBDSceneNode() {

}

void OBDSceneNode::addChild(OBDEntity *e){
    e->getFirstNode()->setParent(scaleNode);
    scaleNode->addChild(e->getFirstNode());
}

void OBDSceneNode::addChild(TNode *e){
    e->setParent(scaleNode);
    scaleNode->addChild(e);
}

void OBDSceneNode::refreshModelMatrix(glm::mat4 parent){
	OBDEntity::refreshModelMatrix(parent);
    for (std::vector<OBDEntity*>::iterator i = children.begin(); i != children.end(); ++i) {
		OBDEntity *temp = *i;
		temp->refreshModelMatrix(model_matrix);
	}
}

void OBDSceneNode::insertBoundingBox(u32 id, aabb::AABB box){
	octree.insertParticle(id, box.lowerBound, box.upperBound);
}

void OBDSceneNode::refreshBoundingBox(u32 id, aabb::AABB box){
	octree.updateParticle(id, box.lowerBound, box.upperBound);
}

void OBDSceneNode::removeBoundingBox(u32 id){
	octree.removeParticle(id);
}

std::vector<u32> OBDSceneNode::getCollisionID(OBDLine ray){
	aabb::Ray r;
	r.rayStart = ray.start;
	r.rayEnd = ray.end;

	r.rayDirection = glm::normalize(ray.end - ray.start);
	r.rayInverseDirection.x = 1.0f/r.rayDirection.x;
	r.rayInverseDirection.y = 1.0f/r.rayDirection.y;
	r.rayInverseDirection.z = 1.0f/r.rayDirection.z;
	r.raySign.x = (r.rayInverseDirection.x < 0); 
	r.raySign.y = (r.rayInverseDirection.y < 0); 
	r.raySign.z = (r.rayInverseDirection.z < 0); 

	return octree.query(r);
}