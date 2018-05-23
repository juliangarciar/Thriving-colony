#ifndef OBDPARTICLEEMITER_H
#define OBDPARTICLEEMITER_H

#include "Graphics/TParticle.h"

/**
 * @brief The different types of OBDParticleEmiter.
 * 
 */
enum ParticleEmiterType {
    Point
};

class OBDParticleEmiter {
    
    public:
        /**
         * @brief OBDParticleEmiter constructor.
         * 
         */
        OBDParticleEmiter();

        /**
         * @brief OBDParticleEmiter destructor.
         * 
         */
        ~OBDParticleEmiter();

        /**
         * @brief Draws the particles passed by parameter.
         * 
         * @param now is the time in miliseconds when the method is called.
         * @param lastCall is the time in miliseconds when the method was called the last time.
         * @param std::vector<TParticle*> are the particles that are going to be drawn.
         */
        void emit(i32 now, i32 lastCall, std::vector<TParticle*>);

        /**
         * @brief Get the type of OBDParticleEmiter.
         * 
         * @return ParticleEmiterType that will be the value of type variable.
         */
        ParticleEmiterType getType();

        /**
         * @brief Get the direction of OBDParticleEmiter.
         * 
         * @return glm::vec2 that will be the value of direction variable.
         */
        glm::vec3 getDirection();

        /**
         * @brief Get the maximum start size of OBDParticleEmiter.
         * 
         * @return glm::vec2 that will be the value of the maxStartSize variable.
         */
        glm::vec2 getMaxStartSize();

        /**
         * @brief Get the minimum start size of OBDParticleEmiter.
         * 
         * @return glm::vec2 that will be the value of the minStartSize variable.
         */
        glm::vec2 getMinStartSize();

        /**
         * @brief Get the maximum angle of OBDParticleEmiter.
         * 
         * @return i32 that will be the value of the maxAngle variable.
         */
        i32 getMaxAngle();

        /**
         * @brief Get the maximum life time of OBDParticleEmiter.
         * 
         * @return i32 that will be the value of the maxLifeTime variable.
         */
        i32 getMaxLifeTime();

        /**
         * @brief Get the minimum life time of OBDParticleEmiter.
         * 
         * @return i32 that will be the value of the minLifeTime variable.
         */
        i32 getMinLifeTime();
        
        /**
         * @brief Get the maximum number of particles per second of OBDParticleEmiter.
         * 
         * @return i32 that will be the value of the maxParticlesPerSecond.
         */
        i32 getMaxParticlesPerSecond();

        /**
         * @brief Get the minimum number of particles per second of OBDParticleEmiter.
         * 
         * @return i32 that will be the value of the minParticlesPerSecond.
         */
        i32 getMinParticlesPerSecond();

        /**
         * @brief Get the maximum value of start color of OBDParticleEmiter.
         * 
         * @return OBDColor that will be the value of the maxStartColor variable.
         */
        OBDColor* getMaxStartColor();

        /**
         * @brief Get the minimum value of start color of OBDParticleEmiter.
         * 
         * @return OBDColor that will be the value of minStartColor variable.
         */
        OBDColor* getMinStartColor();

        /**
         * @brief Set the value of the direction variable.
         * 
         */
        void setDirection(glm::vec3);

        /**
         * @brief Set the value of the maxStartSize variable.
         * 
         */
        void setMaxStartSize(glm::vec2);

        /**
         * @brief Set the value of the minStartSize variable.
         * 
         */
        void setMinStartSize(glm::vec2);

        /**
         * @brief Set the value of the maxAngle variable.
         * 
         */
        void setMaxAngle(i32);

        /**
         * @brief Set the value of the maxLifeTime variable.
         * 
         */
        void setMaxLifeTime(i32);

        /**
         * @brief Set the value of the minLifeTime variable.
         * 
         */
        void setMinLifeTime(i32);

        /**
         * @brief Set the value of the maxParticlesPerSecond variable.
         * 
         */
        void setMaxParticlesPerSecond(i32);

        /**
         * @brief Set the value of the minParticlesPerSecond variable.
         * 
         */
        void setMinParticlesPerSecond(i32);

        /**
         * @brief Set the value of maxStartColor variable.
         * 
         */
        void setMaxStartColor(OBDColor*);

        /**
         * @brief Set the minStartColor variable.
         * 
         */
        void setMinStartColor(OBDColor*);

        /**
         * @brief Set if the OBDParticleEmiter is going to be active or not.
         * 
         * @param True when it is going to be activa and false in other case.
         */
        void setActive(bool);

    protected:

        //Type of the OBDParticleEmiter.
        ParticleEmiterType type;

        //Direction of the OBDParticleEmiter.
        glm::vec3 direction;

        //Maximum start size of the OBDParticleEmiter.
        glm::vec2 maxStartSize;

        //Minimum start size of the OBDParticleEmiter.
        glm::vec2 minStartSize;

        //Max angle with which the particles are going to be emited.
        i32 maxAngle;

        //Maximum life time of the particles.
        i32 maxLifeTime;

        //Minimum life time of the particles.
        i32 minLifeTime;

        //Maximum number of particles per second.
        i32 maxParticlesPerSecond;

        //Minimum number of particles per second.
        i32 minParticlesPerSecond;

        //Maximum start color of the particles.
        OBDColor* maxStartColor;

        //Minimum start color of the particles.
        OBDColor* minStartColor;

        //True when the OBDParticleEmiter is active and false in other case.
        bool active;
};

#endif