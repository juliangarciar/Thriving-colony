#ifndef OBDLIGHT_H
#define OBDLIGHT_H

#include "OBDEntity.h"
#include "OBDSceneNode.h"
#include "OBDColor.h"

#include "Graphics/TTransform.h"
#include "Graphics/TLight.h"

class OBDLight {
    public:
        /**
         * @brief Construct a new OBDLight object
         * 
         * @param parent 
         * @param color 
         * @param intensity 
         * @param ambient 
         * @param attenuation 
         */
        OBDLight(OBDSceneNode* parent, OBDColor color, f32 intensity, f32 ambient, f32 attenuation);

        /**
         * @brief 
         * 
         */
        virtual ~OBDLight();

        /**
         * @brief Set the Color object
         * 
         * @param color
         * @param intensity 
         */
        void setColor(OBDColor color, f32 intensity);

		/**
		 * @brief Set the Ambient Coeficient object
		 * 
         * @param f32 
		 */
		void setAmbientCoeficient(f32);

		/**
		 * @brief Set the Attenuation Coeficient object
		 * 
         * @param f32 
		 */
		void setAttenuationCoeficient(f32);
        
        /**
         * @brief Set the Position object
         * 
         * @param p 
         */
        void setPosition(glm::vec3 p);

        /**
         * @brief set the light to active or inactive
         * 
         * @param bool new light active state
         */
        void setActive(bool);

        /**
         * @brief Get the Position object
         * 
         * @return glm::vec3 
         */
        glm::vec3 getPosition();

        /**
         * @brief returns wether or not the light is active
         * 
         * @return true if the light is active
         * @return false otherwise
         */
        bool getActive();
        
        /**
         * @brief 
         * 
         * @return TLight* 
         */
        TLight* getLightEntity();

        /**
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode *getFirstNode();

        /**
         * @brief Set the Type object
         * 
         * @param newType 
         */
        void setType(OBDEnums::LightTypes newType);
    private:
        TNode* lightNode;
};

#endif