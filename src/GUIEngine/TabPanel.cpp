#include "TabPanel.h"
#include <GraphicEngine/Window.h>

using namespace irr;

TabPanel::TabPanel(Rect2D<int> dimPos, int id) {
    Window *sc = Window::Instance();
    ctrl = sc -> getGUIEnvironment() -> addTabControl(dimPos.getRect2D(), 0, true, true, id);

    tabs = new std::map<int, Tab*>();
}

TabPanel::~TabPanel() {
    //ToDo: borrar ctrl
    delete tabs;
    //ctrl = NULL;
}

Tab *TabPanel::addTab(const wchar_t *text, int id) {
    //std::cout << ctrl << std::endl;
    gui::IGUITab *tab = ctrl -> addTab(text, id);
    Tab *t = new Tab(tab);
    tabs -> insert(std::pair<int, Tab*>(id, t));
    return t;
} 

Tab *TabPanel::getTab(int id) {
    return new Tab(ctrl -> getTab(id)); 
}

void TabPanel::enable() {
   ctrl -> setEnabled(true);
   ctrl -> setVisible(true);
}

void TabPanel::disable() {
   ctrl -> setEnabled(false);
   ctrl -> setVisible(false);
}

bool TabPanel::changeActiveTab(int id) {
    std::map<int,Tab*>::iterator it = tabs -> find(id);
    if (it != tabs -> end()) {
        ctrl -> setActiveTab((gui::IGUITab*)it -> second -> getGUIElement());
        return true;
    }
    return false;
}

gui::IGUIElement *TabPanel::getGUIElement() {
    return ctrl;
}
 