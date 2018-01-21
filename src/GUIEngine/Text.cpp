#include "Text.h"
#include <GraphicEngine/Window.h>

Text::Text(Rect2D<int> dimPos, const wchar_t *t) {
    text = Window::Instance() -> getGUIEnvironment() -> addStaticText(t, dimPos.getRect2D(), false);
}

Text::Text(Rect2D<int> dimPos, const wchar_t *t, bool bg) {
    text = Window::Instance() -> getGUIEnvironment() -> addStaticText(t, dimPos.getRect2D(), bg);
    text -> setBackgroundColor(video::SColor(255,255,255,255));
}

Text::~Text() {
    //ToDo: borrar text
}

gui::IGUIElement *Text::getGUIElement() {
    return text;
}

void Text::setText(const wchar_t *t) {
    text  -> setText(t);
}

void Text::disable() {
    text -> setVisible(false);
    text -> setEnabled(false);
    
}

void Text::enable() {
    text -> setVisible(true);
    text -> setEnabled(true);
}