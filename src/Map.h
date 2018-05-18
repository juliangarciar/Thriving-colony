#ifndef MAP_H
#define MAP_H

#include "CameraController.h"
#include "Player.h"

#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Light.h>
#include <GraphicEngine/SkyDome.h>

#include <Types.h>

/**
 * @class Map.
 * @brief Create a Map type object. Singleton class.
 */
class Map {

    public:
        /**
         * @brief Get the instance of the class. If it doesn't exist, create a new instance.
         * 
         * @return Pointer to a Map object that will be the value of instance variable.
		 */
        static Map* Instance();

        /**
		 * @brief Initialize all variables.
		 */
        void Init();

        /**
		 * @brief Get the inputs of the camera and the mouse.
		 */
        void Input();

        /**
		 * @brief Update the camera.
         * 
         * @see void Update(f32) method from CameraController class.
		 */
        void Update();

        /**
		 * @brief Render.
		 */
        void Render();

        /**
         * @brief Delete all variables.
         */
        void CleanUp();

        /**
        * @brief Get the terrain.
        * 
        * @return Pointer to a Terrain object that will be the value of the terrain variable.
        */
        Terrain* getTerrain();

        /**
         * @brief Get the position of the human player's command center.
         * @return Vector2 that will be the value of humanStartPos variable.
         */
        Vector2<f32> getHumanStartPosition();

        /**
         * @brief Get the position of the AI player's command center.
         * 
         * @return Vector2 that will be the value of iaStartPos variable.
         */
        Vector2<f32> getIAStartPosition();

        /**
         * @brief Get the postion of the terrain correspondent to the position of the mouse cursor.
         * 
         * @return Vector3 that will be the value of collisionPoint variable.
         */
        Vector3<f32> getMouseCollitionPoint();

        /**
         * @brief Get the current active camera.
         * 
         * @return Pointer to a CameraController object that will be the value of camera variable.
         */
        CameraController* getCamera();

		/**
		 * @brief Get the Map Margins object
		 * 
		 * @return Margins* 
		 */
		Margins *getMapMargins();

    protected:
        /**
		 * @brief Map constructor.
		 */
        Map();

        /**
		 * @brief Map destructor.
		 */
        virtual ~Map();

    private:
        /**
         * @brief Show at the terminal the progress of the map loading.
         * 
         * @param i32 is the value of the current progress.
         */
        void loadProgress(i32);

        //Pointer to the only instance of Human class.
        static Map* pinstance;

        //Pointer to the current active camera.
        CameraController *camera;

        //List of lights.
        std::vector<Light*> lights;

        //Pointer to the terrain.
        Terrain *terrain;

        //Position of the human player's command center.
        Vector2<f32> humanStartPos;

        //Position of the AI player's command center.
        Vector2<f32> iaStartPos;

        //Position of the terrain correspondent to the position of the mouse cursor.
        Vector3<f32> collisionPoint;

        //Skydome of the map.
        SkyDome *skydome;

		//MapMargins
		Margins *mapMargins;
};

#endif