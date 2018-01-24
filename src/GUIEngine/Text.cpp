#include "Text.h"
#include <GraphicEngine/Window.h>

Text::Text(std::string t) {
    text = Window::Instance()->getGUIEnvironment()->add<nanogui::Label>(t);
}

Text::~Text() {
    //ToDo: borrar text
}

void Text::show(){
    text->setVisible(true);
}
 
void Text::hide(){
    text->setVisible(false);
}

void Text::setText(std::string t) {
    text->setCaption(t);
}

nanogui::Widget *Text::getGUIElement(){
    return text;
}