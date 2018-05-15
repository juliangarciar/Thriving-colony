#include "TParticleSystem.h"

TParticleSystem::TParticleSystem() : TEntity(){

}

TParticleSystem::~TParticleSystem() {

}

void TParticleSystem::beginDraw() {

}

void TParticleSystem::endDraw() {
    
}

void TParticleSystem::setParticles(std::vector<TParticle*> newParticles) {
    particles = newParticles;
}

std::vector<TParticle*> TParticleSystem::getParticles() {
    return particles;
}