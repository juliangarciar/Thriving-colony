#ifndef TROOP_H
#define TROOP_H

#include <vector>
#include <string>
#include "Types.h"

template<class T>
class Vector3;

template<class T>
class Vector2;

class Model;

class SceneNode;

class Troop{

    public:
        /**
         * @brief Troop constructor.
         * 
         * @param SceneNode
         * @param const char
         * @param qnty
         * @param ID 
         */
        Troop(SceneNode *, std::string, i32 qnty, i32 ID);

        /**
         * @brief Troop destructor.
         */
        ~Troop();

        /**
         * @brief Set the Position object
         * 
         * @param vectorPos 
         */
        void setPosition(Vector2<f32> vectorPos);

        /**
         * @brief 
         * 
         * @param vectorMov 
         */
        void moveTroops(Vector2<f32> vectorMov);

        /**
         * @brief Set the Active object
         * 
         * @param data 
         */
        void setActive(bool data);
        /* NEW */
        std::vector<Vector2<f32>> getTroopsPosition();
        void setNearTroopsPosition(std::vector< Vector2<f32> >);
    private:
        //
        i32 max;

        //
        i32 actualIndex;

        //
        std::vector<Model*> modelVector;
        //
        std::vector<Vector2<f32>> positionVector; 
        std::vector<Vector2<f32>> nearUnitsPosition; 
        //
        f32 alignmentWeight;

        //
        f32 cohesionWeight;

        //
        f32 separationWeight;

        /* Flocking */
        Vector2<f32> alignment();
        Vector2<f32> cohesion();
        Vector2<f32> separation();
        Vector2<f32> calculateFlocking();
};

#endif