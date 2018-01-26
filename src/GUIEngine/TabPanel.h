#ifndef TABPANEL_H
#define TABPANEL_H

#include <map>
#include <nanogui/nanogui.h>
#include "Tab.h"
#include "GUIElement.h"

class TabPanel : public GUIElement {
    public:
        TabPanel();
        TabPanel(GUIElement *parent);
        virtual ~TabPanel();

        Tab *createTab(std::string text, int id);
        Tab *getTab(int id);
        bool changeActiveTab(int id);
        
        void setPosition(Vector2<int> position);
        
        void setTooltip(std::string text);

        void show();
        void hide();

        nanogui::Widget *getGUIElement();
    private:
        nanogui::TabWidget *ctrl;
        std::map<int, Tab*> *tabs;
};

#endif