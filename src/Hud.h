#ifndef HUD_H
#define HUD_H

#include <Types.h>
#include <Enumeration.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Vector3.h>
#include <GUIEngine/TextBox.h>
#include <GUIEngine/Button.h>
#include <GUIEngine/TabPanel.h>
#include <GUIEngine/Tab.h>
#include <GUIEngine/Panel.h>
#include <GUIEngine/Label.h>
#include <GUIEngine/ComboBox.h>
#include <GUIEngine/Widget.h>
#include <GUIEngine/ScrollPanel.h>
#include <GUIEngine/ProgressBar.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/Mouse.h>
#include <IOEngine/Timer.h>

#include <string>
#include <sstream>

/**
 * @class Hud.
 * @brief Create a Hud type object. Singleton class.
 */
class Hud {
    public:
        /**
		 * @brief Get the instance of the class. If it doesn't exist, create a new instance.
         * @return Pointer to a Hud object that will be the value of pinstance variable.
		 */
        static Hud* Instance();

        /**
		 * @brief Initialize all variables.
		 */
        void Init();

        /**
		 * @brief Update timers.
		 */
        void Update();

        /**
		 * @brief Delete all variables.
		 */
        void CleanUp();

        /**
         * @brief Enable the tab pssaed by parameter.
         * @param The Enumeration::BuildingType is the type of building of the tab that is going to be enabled: Enumeration::BuildingType::Barrack, Enumeration::BuildingType::Barn or Enumeration::BuildingType::Workshop.
         */
        void enableTab(Enumeration::BuildingType);

        /**
         * @brief Disable the tab passed by parameter.
         * @param The Enumeration::BuildingType is the type of building of the tab that is going to be disabled: Enumeration::BuildingType::Barrack, Enumeration::BuildingType::Barn or Enumeration::BuildingType::Workshop.
         */
        void disableTab(Enumeration::BuildingType);

        /**
         * @brief Show the tabContainer variable.
         */
        void showPopup();

        /**
         * @brief Show the tabContainer variable and the tab passed by parameter.
         * @param The Enumeration::BuildingType is the type of building of the tab that is going to be shown: Enumeration::BuildingType::MainBuilding, Enumeration::BuildingType::Barrack, Enumeration::BuildingType::Barn or Enumeration::BuildingType::Workshop.
         */
        void showPopup(Enumeration::BuildingType);

        /**
         * @brief Hide the tabContainer variable.
         */
        void hidePopup();

        /**
         * @brief Update the psitions of each element in the hud.
         */
        void updatePositions();

        /**
         * @brief Add the troop passed by parameter to the list of troops in the command center.
         * @param The i32 is the identifier number of the troop.
         * @param The Enumeration::UnitType is the type of the unit.
         */
        void addTroopToHall(i32, Enumeration::UnitType);

        /**
         * @brief Remove the troop passed by parameter from the list of troops in the command center.
         * @param The i32 is the identifier number of the troop.
         */
        void removeTroopFromHall(i32);

        /**
         * @brief Add the troop passed by parameter to the queue of troops that are going to be trained.
         * @param The i32 is the identifier number of the troop.
         * @param The Enumeration::UnitType is the type of the unit.
         */
        void addTroopToQueue(i32, Enumeration::UnitType);

        /**
         * @brief Modify the progress of training of the troop passed by parameter.
         * @param The i32 is the identifier of the troop.
         * @param The f32 is the new value of the progress of training of the troop.
         */
        void modifyTroopFromQueue(i32, f32);

        /**
         * @brief Remove the troop passed by parameter from the queue of troops that are going to be trained.
         * @param The i32 is the identifier number of the troop.
         */
        void removeTroopFromQueue(i32);

        /**
         * @brief Show the text passed by parameter.
         * @param The std::string is the text that is going to be shown.
         */
        void showToast(std::string);

        /**
         * @brief Hide the text that is been shown.
         */
        void hideToast();

        /**
         * @brief Get if there is or not any pop up opened.
         * @return Trues if there is any pop up opened and false in other case.
         */
        bool getPopUpOpen();
        
        /**
         * @brief Set the Button Status object
         * 
         * @param b 
         * @param status
         */
        void setButtonStatus(Enumeration::BuildingType b, bool status);

        /**
         * @brief 
         */
        void adjustMenuVisibility();

        /**
         * @brief 
         * @param std::string 
         */
        void debug();
    protected:
        /**
         * @brief Constructor
         */
        Hud();
        /**
         * @brief Destructor
         */
        ~Hud();
    private:
        static Hud* pinstance;

        //Stuff
        bool popUpOpen;
    
        std::vector<i32> troopsInHallIDs;

        std::map<i32, Widget*> troopQueueList;
        std::map<i32, ProgressBar*> troopQueueProgressBars;

        //Buildings panel
        Panel *buildingsPanel;

        Button *buttonOpenPanel;

        Widget *generalWidget;
        Widget *resourceWidget;
        Widget *serviceWidget;
        Widget *militaryWidget;
        Widget *defenseWidget;

        Button *buttonHouse;
        Button *buttonSiderurgy;
        Button *buttonQuarry;
        Button *buttonSchool;
        Button *buttonMarket;
        Button *buttonHospital;
        Button *buttonBarrack;
        Button *buttonBarn;
        Button *buttonWorkshop;
        Button *buttonTower;
        Button *buttonWall;
        Button *buttonExpandTerrain;

        //Popup panel
        Panel *tabContainer;
        
        TabPanel *tabs;
        
        Widget *barrackEmpty;
        Widget *barrackContent;
        Widget *barnEmpty;
        Widget *barnContent;
        Widget *workshopEmpty;
        Widget *workshopContent;

        Widget *barrackTroopQueueWidget;
        Widget *barnTroopQueueWidget;
        Widget *workshopTroopQueueWidget;

        ComboBox *hallTroopList;
        
        //Debug
        Panel *playerResources;
        Label *playerMetalAmount;
        Label *playerCrystalAmount;
        Label *playerCitizens;
        Label *playerHappiness;
        Label *playerCityLevel;
        Label *playerArmySize;
        Label *playerMelees;
        Label *playerRangeds;
        Label *playerSieges;

        Panel *iaResources;
        Label *iaMetalAmount;
        Label *iaCrystalAmount;
        Label *iaCitizens;
        Label *iaHappiness;
        Label *iaCityLevel;
        Label *iaArmySize;
        Label *iaMelees;
        Label *iaRangeds;
        Label *iaSieges;
        Label *iaNextChoice;
        Label *iaBehaviour;


        Timer* debugTimer;

        //Toast
        Panel *toast;
        Label *toastText;

        bool toastBool;
        Timer* toastTimer;

        /**
         * @brief Crea un boton 
         * @param id del boton, de tipo entero
         * @param type sera el tipo de edificio que se creara con ese boton, de tipo entero
         */
        void addTab(i32, i32);
};

#endif