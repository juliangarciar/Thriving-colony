#include "OBDAnimation.h"

OBDAnimation::OBDAnimation(OBDSceneNode* p, std::vector<ResourceOBJ*> *o, ResourceMTL *m) : OBDEntity(p) {
	objects = o;
	objectMaterial = m;

	frames = new std::vector<OBDMesh*>();
	frames->reserve(o->size());

	numberOfFrames = o->size();
	currentFrame = 0;
	nextFrame = 0;

	auto it = m->getResource()->begin();

	material = new OBDMaterial(m, it->first);

	for (int i = 0; i < o->size(); i++) {
		glslMesh *tmp = new glslMesh();
		tmp -> vbo = o->at(i)->getResource()->begin()->second->vbo;
		tmp -> ibo = o->at(i)->getResource()->begin()->second->indices;

        OBDMesh *tempMesh = new OBDMesh(tmp, material);
		tempMesh -> setMaterialName(m -> getResource()->begin()->first);
		tempMesh -> setBoundingBox(o -> at(i)->getResource()->begin()->second->aabbMin, o->at(i)->getResource()->begin()->second->aabbMax);

        tempMesh -> getFirstNode()->setParent(scaleNode);
        scaleNode -> addChild(tempMesh->getFirstNode());

		tempMesh -> setActive(false);

		frames -> push_back(tempMesh);
	}

    p -> addChild(this);
}

OBDAnimation::~OBDAnimation() {

}

void OBDAnimation::updateFrame() {
	if (getActive()){
		frames -> at(currentFrame) -> setActive(false);
		frames -> at(nextFrame) -> setActive(true);
		currentFrame = nextFrame;
		nextFrame++;
		if (nextFrame >= numberOfFrames) nextFrame = 0;
	}
}

void OBDAnimation::setActive(bool a){
	OBDEntity::setActive(a);
	setCurrentFrame(0);
}

/* Me pase de listo */
void OBDAnimation::setCurrentFrame(i32 nFrame){
	assert(nFrame >= 0 && nFrame < numberOfFrames);
	frames -> at(currentFrame) -> setActive(false);
	currentFrame = nFrame;
	nextFrame = nFrame;
	frames -> at(currentFrame) -> setActive(true);
}

i32 OBDAnimation::getNumberOfFrames(){
	return numberOfFrames;
}

OBDMaterial *OBDAnimation::getMaterial() {
	return material;
}