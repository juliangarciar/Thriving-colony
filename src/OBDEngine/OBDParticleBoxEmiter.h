#ifndef OBDPARTICLEBOXEMITER_H
#define OBDPARTICLEBOXEMITER_H

#include "OBDParticleEmiter.h"

class OBDParticleBoxEmiter : public OBDParticleEmiter {
    
    public:
        /**
         * @brief 
         * 
         */
        OBDParticleBoxEmiter();

        /**
         * @brief 
         * 
         */
        ~OBDParticleBoxEmiter();

        /**
         * @brief 
         * 
         */
        void emit(i32, i32, std::vector<TParticle*>);

    private:
};

#endif