#include "OBDParticleAffector.h"

OBDParticleAffector::OBDParticleAffector() {
    enabled = true;
}

OBDParticleAffector::~OBDParticleAffector() {

}

bool OBDParticleAffector::getEnabled() {
    return enabled;
}

void OBDParticleAffector::setEnabled(bool newEnabled) {
    enabled = newEnabled;
}