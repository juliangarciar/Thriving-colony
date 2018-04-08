#ifndef MAP_H
#define MAP_H

#include "CameraController.h"
#include "Player.h"

#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Light.h>
#include <GraphicEngine/SkyDome.h>

#include <Types.h>
/**
 * @class Map
 * @brief Singleton del mapa
 */
class Map {
    public:
        /**
		 * @brief Crea una Instancia de Map
		 */
        static Map* Instance();

        /**
		 * @brief Inicializa Map
		 */
        void Init();
        /**
		 * @brief Recoge las entradas de teclado y raton
		 */
        void Input();
        /**
		 * @brief Actualiza
		 */
        void Update();
        /**
		 * @brief Renderiza
		 */
        void Render();
        /**
		 * @brief Constructor
		 */
        void CleanUp();

        /**
        * @brief Devuelve el mapa
        * @return objeto de tipo Terrain
        */
        Terrain* getTerrain();

        /**
         * @brief raycast
         * 
         * @return Vector2<f32> 
         */
        Vector3<f32> getHumanStartPosition();

        /**
         * @brief raycast
         * 
         * @return Vector2<f32> 
         */
        Vector3<f32> getIAStartPosition();

        /**
         * @brief raycast
         * 
         * @return Vector2<f32> 
         */
        Vector3<f32> getMouseCollitionPoint();


        CameraController* getCamera();

    protected:
        /**
		 * @brief Constructor de Map
		 */
        Map();
        /**
		 * @brief Destructor
		 */
        virtual ~Map();

    private:
        static Map* pinstance;

        //Stuff
        CameraController *camera;
        std::vector<Light*> lights;
        Terrain *terrain;

        //Start Positions
        Vector3<f32> humanStartPos;
        Vector3<f32> iaStartPos;

        //For raycast
        Vector3<f32> collisionPoint;

        //Skydome
        SkyDome* skydome;

};

#endif