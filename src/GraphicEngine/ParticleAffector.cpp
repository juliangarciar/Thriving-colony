#include "ParticleAffector.h"

ParticleAffector::ParticleAffector() {

}

ParticleAffector::~ParticleAffector() {

}

scene::IParticleAffectorSceneNode* ParticleAffector::getParticleAffectorNode() {
    return particleAffectorNode;
}