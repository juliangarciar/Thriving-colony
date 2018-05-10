#ifndef OBDPARTICLEEMITER_H
#define OBDPARTICLEEMITER_H

#include "Graphics/TParticle.h"

enum ParticleEmiterType {
    Point,
    Box
};

class OBDParticleEmiter {
    
    public:
        /**
         * @brief 
         * 
         */
        OBDParticleEmiter();

        /**
         * @brief 
         * 
         */
        ~OBDParticleEmiter();

        /**
         * @brief 
         * 
         * @param 
         */
        void emit(i32, i32, std::vector<TParticle*>);

        /**
         * @brief Get the Type object
         * 
         * @return ParticleEmiterType 
         */
        ParticleEmiterType getType();

        /**
         * @brief Get the Direction object
         * 
         * @return glm::vec2 
         */
        glm::vec3 getDirection();

        /**
         * @brief Get the Max Start Size object
         * 
         * @return glm::vec2 
         */
        glm::vec2 getMaxStartSize();

        /**
         * @brief Get the Min Start Size object
         * 
         * @return glm::vec2 
         */
        glm::vec2 getMinStartSize();

        /**
         * @brief Get the Max Angle object
         * 
         * @return i32 
         */
        i32 getMaxAngle();

        /**
         * @brief Get the Max Life Time object
         * 
         * @return i32 
         */
        i32 getMaxLifeTime();

        /**
         * @brief Get the Min Life Time object
         * 
         * @return i32 
         */
        i32 getMinLifeTime();
        
        /**
         * @brief Get the Max Particles Per Second object
         * 
         * @return i32 
         */
        i32 getMaxParticlesPerSecond();

        /**
         * @brief Get the Min Particles Per Second object
         * 
         * @return i32 
         */
        i32 getMinParticlesPerSecond();

        /**
         * @brief Get the Max Start Color object
         * 
         * @return OBDColor 
         */
        OBDColor* getMaxStartColor();

        /**
         * @brief Get the Min Start Color object
         * 
         * @return OBDColor 
         */
        OBDColor* getMinStartColor();

        /**
         * @brief Set the Direction object
         * 
         */
        void setDirection(glm::vec3);

        /**
         * @brief Set the Max Start Size object
         * 
         */
        void setMaxStartSize(glm::vec2);

        /**
         * @brief Set the Min Start Size object
         * 
         */
        void setMinStartSize(glm::vec2);

        /**
         * @brief Set the Max Angle object
         * 
         */
        void setMaxAngle(i32);

        /**
         * @brief Set the Max Life Time object
         * 
         */
        void setMaxLifeTime(i32);

        /**
         * @brief Set the Min Life Time object
         * 
         */
        void setMinLifeTime(i32);

        /**
         * @brief Set the Max Particles Per Second object
         * 
         */
        void setMaxParticlesPerSecond(i32);

        /**
         * @brief Set the Min Particles Per Second object
         * 
         */
        void setMinParticlesPerSecond(i32);

        /**
         * @brief Set the Max Start Color object
         * 
         */
        void setMaxStartColor(OBDColor*);

        /**
         * @brief Set the Min Start Color object
         * 
         */
        void setMinStartColor(OBDColor*);

    protected:
        ParticleEmiterType type;

        glm::vec3 direction;
        glm::vec2 maxStartSize;
        glm::vec2 minStartSize;

        i32 maxAngle;
        i32 maxLifeTime;
        i32 minLifeTime;
        i32 maxParticlesPerSecond;
        i32 minParticlesPerSecond;

        OBDColor* maxStartColor;
        OBDColor* minStartColor;
};

#endif