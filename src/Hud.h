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
#include <GUIEngine/Widget.h>
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
         * @brief Activa una pestaña
         * @param Tipo de pestaña
         */
        void enableTab(Enumeration::BuildingType);
        /**
         * @brief Desctiva una pestaña
         * @param Tipo de pestaña
         */
        void disableTab(Enumeration::BuildingType);
        /**
         * @brief Despliega y muestra el PopUp
         */
        void showPopup();
        /**
         * @brief Despliega y muestra el PopUp
         * @param indica el tipo de pestaña que mostrar en el popup
         */
        void showPopup(Enumeration::BuildingType);
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
        std::vector<Button*> *buttons;

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

        Tab *mainBuildingTab;
        
        Tab *barrackTab;
        Panel *barrackEmpty;
        Label *barrackEmptyLabel;
        Panel *barrackContent;
        Tab *barnTab;
        Panel *barnEmpty;
        Label *barnEmptyLabel;
        Panel *barnContent;
        Tab *workshopTab;
        Panel *workshopEmpty;
        Label *workshopEmptyLabel;
        Panel *workshopContent;

        float updateTimer;
        float deleteTextTimer;

        /**
         * @brief Crea un boton 
         * @param id del boton, de tipo entero
         * @param type sera el tipo de edificio que se creara con ese boton, de tipo entero
         */
        void addTab(int, int);
};

#endif