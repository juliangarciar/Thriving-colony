#include "ListBox.h"
#include <GraphicEngine/Window.h>

ListBox::ListBox(Rect2D<int> dimPos) {
    listbox = Window::Instance()->getGUIEnvironment()->addListBox(dimPos.getRect2D());
}

ListBox::~ListBox() {
    
}

void ListBox::addItem(const wchar_t *t){
    listbox->addItem(t);
}
 
gui::IGUIElement *ListBox::getGUIElement(){
    return listbox;
}