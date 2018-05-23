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
		o->at(i)->setupMesh(o->at(i)->getResource()->begin()->second);
		glslMesh *tmp = new glslMesh();
		tmp -> VAO = o->at(i)->getResource()->begin()->second->VAO;
		tmp -> num_indices = o->at(i)->getResource()->begin()->second->ibo->size();

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
		// Disable the current frame and enable the next one.
		frames -> at(currentFrame) -> setActive(false);
		frames -> at(nextFrame) -> setActive(true);
		currentFrame = nextFrame;
		// Increase the frame
		nextFrame++;
		// Last frame reached, reset.
		if (nextFrame >= numberOfFrames) nextFrame = 0;
	}
}

void OBDAnimation::setActive(bool a){
	OBDEntity::setActive(a);
	// When deactivating an animation, reset it.
	setCurrentFrame(0);
}

void OBDAnimation::setCurrentFrame(i32 nFrame){
	// Make sure the desired frame is within the limits.
	assert(nFrame >= 0 && nFrame < numberOfFrames);
	// Deactivate the current frame
	frames -> at(currentFrame) -> setActive(false);
	// Jump to the desired frame and nebale it.
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