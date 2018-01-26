#include "TextBox.h"
#include <GraphicEngine/Window.h>

TextBox::TextBox(std::string t) {
    textbox = Window::Instance() -> getGUIEnvironment() -> add<nanogui::TextBox>(t);
}

TextBox::~TextBox() {
    //ToDo: borrar Label
    this -> hide();
}

void TextBox::setPosition(Vector2<int> position){
    textbox -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void TextBox::setTooltip(std::string t){
    textbox -> setTooltip(t);
}

void TextBox::setText(std::string t) {
    textbox -> setDefaultValue(t);
}

void TextBox::setEditable(bool b) {
    textbox -> setEditable(b);
}

void TextBox::show(){
    textbox -> setVisible(true);
}
 
void TextBox::hide(){
    textbox -> setVisible(false);
}

void TextBox::setSize(Vector2<int> size) {
    textbox -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

nanogui::Widget *TextBox::getGUIElement(){
    return textbox;
}