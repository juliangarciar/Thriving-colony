#include "ParticleAffector.h"

ParticleAffector::ParticleAffector() {

}

ParticleAffector::~ParticleAffector() {

}

scene::IParticleAffector* ParticleAffector::getParticleAffectorNode() {
    return particleAffectorNode;
}