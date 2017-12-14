#include "Tab.h"
#include <GraphicEngine/Window.h>

using namespace irr;
 
Tab::Tab(Panel *panel, const wchar_t *text, int id){
    tab = panel->getTabControl->addTab(text, id);
}

Tab::~Tab(){
    delete tab;
    tab = NULL;
}

void Tab::addChildButton(){
    
}