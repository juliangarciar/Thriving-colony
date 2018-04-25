#ifndef TLIGHT_H
#define TLIGHT_H

#include "TEntity.h"
#include "../OBDColor.h"

class TLight : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TLight(OBDColor, f32);

        /**
         * @brief 
         * 
         */
        virtual ~TLight();

        /**
         * @brief 
         * 
         */
        void beginDraw();

        /**
         * @brief 
         * 
         */
        void endDraw();
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setAmbientComponent(OBDColor, f32);
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setDiffuseComponent(OBDColor, f32);
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setSpecularComponent(OBDColor, f32);

        /**
         * @brief Set the Position object
         * 
         * @param p 
         */
        void setPosition(glm::vec3 p);

        /**
         * @brief Set the Active object
         * 
         */
        void setActive(bool);

        /**
         * @brief Get the Position object
         * 
         * @return glm::vec3 
         */
        glm::vec3 getPosition();
    private:
        OBDEnums::LightTypes lightType;

        glslLight components;

        bool active;
};

#endif