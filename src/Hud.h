#ifndef HUD_H
#define HUD_H

#include <irrlicht.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GUIEngine/Rect2D.h>
#include <GUIEngine/TextBox.h>
#include <GUIEngine/Button.h>
#include <GUIEngine/TabPanel.h>
#include <GUIEngine/Tab.h>
#include <GUIEngine/Panel.h>
#include <GUIEngine/Label.h>
#include <GUIEngine/ComboBox.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/Mouse.h>

using namespace irr;
       
static TextBox *warningText = 0;

/**
 * @class Hud
 * @brief Crea un objeto tipo Hud
 */
class Hud {
    
    public:
        /**
         * @brief Constructor
         */
        Hud();
        /**
         * @brief Destructor
         */
        ~Hud();

        /**
         * @brief Crea un boton 
         * @param id del boton, de tipo entero
         * @param type sera el tipo de edificio que se creara con ese boton, de tipo entero
         */
        void addTab(int, int);

        /**
         * @brief Despliega y muestra el PopUp
         */
        void showPopup();
        /**
         * @brief Despliega y muestra el PopUp
         * @param tabId indica el boton al que pertenece el popup
         */
        void showPopup(int tabId);
        /**
         * @brief Oculta el PopUp
         */
        void hidePopup();
        /**
         * @brief Establece los distintos eventos asociados a cada uno de los botones del HUD 
         */
        void setHUDEvents();

        /**
         * @brief Actualiza el HUD
         */
        void update();
        /**
         * @brief Actualiza las posiciones de los elementos del HUD
         */
        void updatePositions();

        /**
         * @brief Lanza una alerta de contruccion
         */
        static void drawWarning();
        /**
         * @brief Borra la alerta lanzada
         */
        static void deleteWarning();
    private:
        std::vector<int> *menuIDs;
        std::vector<Button*> *buttons;

        Button *buttonQuit;

        Panel *buildingsPanel;

        Panel *generalPanel;
        Panel *servicePanel;
        Panel *militaryPanel;
        Panel *resourcePanel;
        Panel *defensePanel;

        Button *buttonBarn;
        Button *buttonBarrack;
        Button *buttonHospital;
        Button *buttonHome;
        Button *buttonMarket;
        Button *buttonQuarry;
        Button *buttonSiderurgy;
        Button *buttonSchool;
        Button *buttonTower;
        Button *buttonWall;
        Button *buttonWorkshop;
        Button *buttonExpandTerrain;
        Button *buttonOpenPanel;
        
        TextBox *backgroundText;
        Label *resourceText;
        Label *iaResourceText;

        ComboBox *hallTroopList;

        Panel *tabContainer;
        TabPanel *tabs;

        float updateTimer;
        float deleteTextTimer;

/*
        Text *hallTroopText;
        //ListBox *hallTroopList;

        //ToDo: mejorar*/
};

#endif