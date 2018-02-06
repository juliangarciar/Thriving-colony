#ifndef TAB_H
#define TAB_H

#include <nanogui/nanogui.h>
#include "GUIElement.h"
//#include "TabPanel.h"

class Tab : public GUIElement{
    public:
        Tab(nanogui::Widget *t);
        virtual ~Tab();

        void show();
        void hide();
        bool isVisible();

        void addChild(GUIElement *elem);
        
        void setPosition(Vector2<int> position);
        
        void setTooltip(std::string text);

        std::string getTitle();

        nanogui::Widget *getGUIElement();
    private:
        nanogui::Widget *tab;
};

#endif