#include "Text.h"
#include <GraphicEngine/Window.h>

Text::Text(Rect2D<int> dimPos, const wchar_t *t) {
    text = Window::Instance()->getGUIEnvironment()->addStaticText(t, dimPos.getRect2D(), false);
}

Text::~Text() {
    
}

gui::IGUIElement *Text::getGUIElement(){
    return text;
}