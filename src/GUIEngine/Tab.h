#ifndef TAB_H
#define TAB_H

#include <nanogui/nanogui.h>
#include "GUIElement.h"
//#include "TabPanel.h"

class Tab : public GUIElement{
    public:
        //Tab(TabPanel *parent, std::string title, int id);
        Tab(nanogui::Widget *t);
        virtual ~Tab();

        void addChild(GUIElement *elem);

        void show();
        void hide();

        std::string getTitle();
        int getID();

        nanogui::Widget *getGUIElement();
    private:
        nanogui::Widget *tab;
};

#endif