#include "Text.h"
#include <GraphicEngine/Window.h>

Text::Text(Rect2D<int> dimPos, const wchar_t *t) {
    text = Window::Instance()->getGUIEnvironment()->addStaticText(t, dimPos.getRect2D(), false);
}

Text::Text(Rect2D<int> dimPos, const wchar_t *t, bool bg) {
    text = Window::Instance()->getGUIEnvironment()->addStaticText(t, dimPos.getRect2D(), bg);
    text -> setBackgroundColor(video::SColor(255,255,255,255));
}

Text::~Text() {
    
}

gui::IGUIElement *Text::getGUIElement(){
    return text;
}

void Text::setText(const wchar_t *t) {
    text ->setText(t);
}

void Text::disable() {
    text -> setEnabled(false);
    text -> setVisible(false);
    std::cout<<"llega"<<std::endl;
}

void Text::enable() {
    text -> setEnabled(true);
    text -> setVisible(true);
    std::cout<<"llega1"<<std::endl;
}