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

        void show();
        void hide();
        bool isVisible();

        Tab *createTab(std::string text, int id);
        Tab *getTab(int id);

        void changeActiveTab(int index);
        
        void setPosition(Vector2<int> position);
        
        void setTooltip(std::string text);

        nanogui::Widget *getGUIElement();
    private:
        nanogui::TabWidget *ctrl;
        std::map<int, Tab*> *tabs;
};

#endif