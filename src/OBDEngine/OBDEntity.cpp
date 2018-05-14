#include "OBDEntity.h"
#include "OBDSceneNode.h"

OBDEntity::OBDEntity(){
	node_position = glm::vec3(0);
	node_rotation = glm::vec3(0);
	node_scale = glm::vec3(0);

	parent_model_matrix = glm::mat4(1.0f);
	model_matrix = glm::mat4(1.0f);
	inverse_model_matrix = glm::mat4(1.0f);

	rotationNode = new TNode(new TTransform());
	translationNode = new TNode(new TTransform(), rotationNode);
	scaleNode = new TNode(new TTransform(), translationNode);

	parent = nullptr;

	refreshModelMatrix(parent_model_matrix);
}

OBDEntity::OBDEntity(OBDSceneNode *p){
	node_position = glm::vec3(0);
	node_rotation = glm::vec3(0);
	node_scale = glm::vec3(0);

	parent_model_matrix = glm::mat4(1.0f);
	model_matrix = glm::mat4(1.0f);
	inverse_model_matrix = glm::mat4(1.0f);

	rotationNode = new TNode(new TTransform());
	translationNode = new TNode(new TTransform(), rotationNode);
	scaleNode = new TNode(new TTransform(), translationNode);

	parent = p;
    p->addChild(this);

	refreshModelMatrix(parent_model_matrix);
}

OBDEntity::~OBDEntity(){
	//ToDo
}

void OBDEntity::refreshModelMatrix(glm::mat4 parent){
	parent_model_matrix = parent;
	TTransform* r = (TTransform*) rotationNode -> getEntity();
	TTransform* t = (TTransform*) translationNode -> getEntity();
	TTransform* s = (TTransform*) scaleNode -> getEntity();
	model_matrix = s->getMatrix() * t->getMatrix() * r->getMatrix() * parent;
	inverse_model_matrix = glm::inverse(model_matrix);
}

void OBDEntity::translate(glm::vec3 p) {
	TTransform* t = (TTransform*) translationNode -> getEntity();
	t -> translate(p);
	node_position += glm::vec3(p.x, p.y, p.z);
}

void OBDEntity::rotate(glm::vec3 r, f32 angle) {
	TTransform* t = (TTransform*) rotationNode -> getEntity();
	t -> rotate(r, angle);
	node_rotation += glm::vec3(r.x, r.y, r.z);
}

void OBDEntity::scale(glm::vec3 s) {
	TTransform* t = (TTransform*) scaleNode -> getEntity();
	t -> scale(s);
	node_scale += glm::vec3(s.x, s.y, s.z);
}

void OBDEntity::setPosition(glm::vec3 p) {
	TTransform* t = (TTransform*) translationNode -> getEntity();
	glm::vec3 o = p - node_position;
	t -> translate(o);
	node_position = p;
}

void OBDEntity::setRotation(glm::vec3 r) {
	TTransform* t = (TTransform*) rotationNode -> getEntity();
	r = glm::vec3(r.x/360, r.y/360, r.z/360);
	glm::vec3 o = r - node_rotation;
	t -> rotate(o, 360);
	node_rotation = r;
}

void OBDEntity::setScale(glm::vec3 s) {
	TTransform* t = (TTransform*) scaleNode -> getEntity();
	glm::vec3 o = s - node_scale;
	t -> scale(o);
	node_scale = s;
}

void OBDEntity::setActive(bool a) {
	rotationNode -> setActive(a);
}

glm::vec3 OBDEntity::getPosition(){
	return node_position;
}

glm::vec3 OBDEntity::getRotation(){
	return glm::vec3(node_rotation.x * 360, node_rotation.y * 360, node_rotation.y * 360);
}

glm::vec3 OBDEntity::getScale(){
	return node_scale;
}

bool OBDEntity::getActive() {
	TTransform* t = (TTransform*) rotationNode -> getEntity();
	return t;
}

TNode *OBDEntity::getFirstNode(){
	return rotationNode;
}