#ifndef TABPANEL_H
#define TABPANEL_H

#include <vector>
#include <nanogui/nanogui.h>
#include "Tab.h"
#include "GUIElement.h"
#include <Types.h>

class TabPanel : public GUIElement {
    public:
        TabPanel();
        TabPanel(GUIElement *parent);
        virtual ~TabPanel();

        void addChild(GUIElement *);

        void show();
        void hide();
        bool isVisible();

        Tab *createTab(std::string text);
        Tab *getTab(i32 index);

        void changeActiveTab(i32 index);
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);
        
        void setTooltip(std::string text);

        nanogui::Widget *getGUIElement();
    private:
        nanogui::TabWidget *ctrl;
        std::vector<Tab*> tabs;
};

#endif