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
         * @param std::string is the type of building of the tab that is going to be enabled.
         */
        void enableTab(std::string);

        /**
         * @brief Disable the tab passed by parameter.
         * @param std::string is the type of building of the tab that is going to be disabled.
         */
        void disableTab(std::string);

        /**
         * @brief Show the tabContainer variable.
         */
        void showPopup();

        /**
         * @brief Show the tabContainer variable and the tab passed by parameter.
         * @param std::string is the type of building of the tab that is going to be shown.
         */
        void showPopup(std::string);

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
         * @param i32 is the identifier number of the troop.
         * @param std::string is the type of the unit.
         */
        void addTroopToHall(i32, std::string);

        /**
         * @brief Remove the troop passed by parameter from the list of troops in the command center.
         * @param i32 is the identifier number of the troop.
         */
        void removeTroopFromHall(i32);

        /**
         * @brief Add the troop passed by parameter to the queue of troops that are going to be trained.
         * @param i32 is the identifier number of the troop.
         * @param std::string is the type of the unit.
         */
        void addTroopToQueue(i32, std::string);

        /**
         * @brief Modify the progress of training of the troop passed by parameter.
         * @param i32 is the identifier of the troop.
         * @param f32 is the new value of the progress of training of the troop.
         */
        void modifyTroopFromQueue(i32, f32);

        /**
         * @brief Remove the troop passed by parameter from the queue of troops that are going to be trained.
         * @param i32 is the identifier number of the troop.
         */
        void removeTroopFromQueue(i32);

        /**
         * @brief Show the text passed by parameter.
         * @param std::string is the text that is going to be shown.
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
         * @brief Show or hide the button passed by parameter.
         * @param std::string is the type of the button that is going to be shown or hidden.
         * @param False to be hidden or true to be shown.
         */
        void setButtonStatus(std::string, bool);

        /**
         * @brief Ajust the widgets that have to be shown or hidden.
         */
        void adjustMenuVisibility();

        /**
         * @brief Shows all relevant player's variables.
         */
        void debug();

    protected:
        /**
         * @brief Hud constructor.
         */
        Hud();

        /**
         * @brief Hud destructor.
         */
        ~Hud();

    private:
        //Pointer to the only instance of Hud class.
        static Hud* pinstance;

        //True if there is a pop up opened and false in other case.
        bool popUpOpen;

        //List of troops that are on the command center.
        std::vector<i32> troopsInHallIDs;

        //Queue of the troops that are going to be trained.
        std::map<i32, Widget*> troopQueueList;

        //List of troops that are being trained and their progress.
        std::map<i32, ProgressBar*> troopQueueProgressBars;

        //Panel with all types of buildings.
        Panel *buildingsPanel;

        //Button to open the panel.
        Button *buttonOpenPanel;

        //
        Widget *generalWidget;
        
        //Widget of the buildings that provide resources.
        Widget *resourceWidget;

        //Widget of the buildings that provide happiness.
        Widget *serviceWidget;

        //Widget of the buildings that allow training troops.
        Widget *militaryWidget;

        //Widget of the defense buildings.
        Widget *defenseWidget;

        //Button to build a house.
        Button *buttonHouse;

        //Button to build a siderurgy.
        Button *buttonSiderurgy;

        //Button to build a quarry.
        Button *buttonQuarry;

        //Button to build a school.
        Button *buttonSchool;

        //Button to build a market.
        Button *buttonMarket;

        //Button to build a hospital.
        Button *buttonHospital;

        //Button to build a barrack.
        Button *buttonBarrack;

        //Button to build a barn.
        Button *buttonBarn;

        //Button to build a workshop.
        Button *buttonWorkshop;

        //Button to build a tower.
        Button *buttonTower;

        //Button to build a wall.
        Button *buttonWall;

        //Button to expand the terrain.
        Button *buttonExpandTerrain;

        //
        Panel *tabContainer;
        
        //
        TabPanel *tabs;
        
        //Widget for when the barrack is not built.
        Widget *barrackEmpty;

        //Widget for when the barrack is built.
        Widget *barrackContent;

        //Widget for when the barn is not built.
        Widget *barnEmpty;

        //Widget for when the barn is built.
        Widget *barnContent;

        //Widget for when the workshop is not built.
        Widget *workshopEmpty;

        //Widget for when the workshop is built.
        Widget *workshopContent;

        //Widget for when in the barrack are troops being trained.
        Widget *barrackTroopQueueWidget;

        //Widget for when in the barn are troops being trained.
        Widget *barnTroopQueueWidget;

        //Widget for when in the workshop are troops being trained.
        Widget *workshopTroopQueueWidget;

        //Place where the troops that are in the command center will be listed.
        ComboBox *hallTroopList;
        
        //Panel where will be listed player's resources.
        Panel *playerResources;

        //Player's metal amount.
        Label *playerMetalAmount;

        //Player's crystal amount.
        Label *playerCrystalAmount;

        //Player's citizens amount.
        Label *playerCitizens;

        //Player's happiness amount.
        Label *playerHappiness;

        //Player's city level.
        Label *playerCityLevel;

        //Player's army size.
        Label *playerArmySize;

        //Player's melees amount.
        Label *playerMelees;

        //Player's rangeds amount.
        Label *playerRangeds;

        //Player's sieges amount.
        Label *playerSieges;

        //Panel where will be listed AI's resources.
        Panel *iaResources;

        //AI's metal amount.
        Label *iaMetalAmount;

        //AI's crystal amount.
        Label *iaCrystalAmount;

        //AI's citizens amount.
        Label *iaCitizens;

        //AI's happiness amount.
        Label *iaHappiness;

        //AI's city level.
        Label *iaCityLevel;

        //AI's army size.
        Label *iaArmySize;

        //AI's melees amount.
        Label *iaMelees;

        //AI's rangeds amount.
        Label *iaRangeds;

        //AI's sieges amount.
        Label *iaSieges;

        //AI's next choice.
        Label *iaNextChoice;

        //AI's behaviour.
        Label *iaBehaviour;

        //Time that crontols when the players' panels will be updated.
        Timer* debugTimer;

        //
        Panel *toast;

        //
        Label *toastText;

        //Frame per second of the game.
        Label *framerateLabel;
        
        //
        bool toastBool;

        //
        Timer* toastTimer;

        
};

#endif