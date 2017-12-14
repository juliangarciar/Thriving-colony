#ifndef TAB_H
#define TAB_H

#include <irrlicht.h>
#include <GUIEngine/Panel.h>

using namespace irr;

class Tab {
    public:
        Tab(Panel *panel, const wchar_t *text, int id);
        ~Tab();

        //void addTab(const wchar_t *text, int id);
    private:
        gui::IGUITab *tab;
};

#endif