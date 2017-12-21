#include "ListBox.h"
#include <GraphicEngine/Window.h>

ListBox::ListBox(Rect2D<int> dimPos) {
    listbox = Window::Instance()->getGUIEnvironment()->addListBox(dimPos.getRect2D());
    //options = new std::vector<float>(); 
}

ListBox::~ListBox() {
    delete listbox;
    //delete options;   
}

void ListBox::addItem(const wchar_t *t){
    listbox->addItem(t);
}

void ListBox::removeItem(int id){
    listbox->removeItem(id);
}

void ListBox::removeAllItems(){
    listbox->clear();
}

int ListBox::getSelected(){
    return listbox->getSelected();
}
 
gui::IGUIElement *ListBox::getGUIElement(){
    return listbox; 
}