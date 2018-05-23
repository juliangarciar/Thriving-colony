#ifndef TLIGHT_H
#define TLIGHT_H

#include "TEntity.h"
#include "../OBDColor.h"

class TLight : public TEntity {
    public:
        /**
         * @brief Construct a new TLight object
         * 
         * @param OBDColor color for the light.
         * @param f32 intensity for the light.
         * @param f32 ambient coefficient.
         * @param f32 atenuation coefficient. 
         * 
         */
        TLight(OBDColor, f32, f32, f32);

        /**
         * @brief Destroy the TLight object
         * 
         */
        virtual ~TLight();

        /**
         * @brief send light data to the shader program to render the scene.
         * 
         */
        void beginDraw();

        void endDraw();
        
        /**
         * @brief set a new color for the light
         * 
         * @param OBDColor new color.
         * @param f32 new intensity value.
         */
        void setColor(OBDColor, f32);

		/**
		 * @brief Set the Ambient Coeficient of the light
		 * 
		 */
		void setAmbientCoeficient(f32);

		/**
		 * @brief Set the Attenuation Coeficient of the light
		 * 
		 */
		void setAttenuationCoeficient(f32);

        /**
         * @brief Set the Position object
         * 
         * @param p new light position.
         */
        void setPosition(glm::vec3 p);

        /**
         * @brief Turn on or off the light as desired.
         * 
         */
        void setActive(bool);

        /**
         * @brief Get the Position object
         * 
         * @return glm::vec3  new light's position.
         */
        glm::vec3 getPosition();

        /**
         * @brief Set the Type object
         * 
         * @param newType new type for the light.
         */
        void setType(OBDEnums::LightTypes newType);
    private:
        // Struct containing all light data.
        glslLight components;

        bool active;
};

#endif