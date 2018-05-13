#include "TextBox.h"
#include <GraphicEngine/Window.h>

TextBox::TextBox(std::string t) {
    textbox = Window::Instance() -> getGUIEnvironment() -> add<nanogui::TextBox>(t);
}

TextBox::TextBox(GUIElement *parent, std::string t) {
    textbox = parent -> getGUIElement() -> add<nanogui::TextBox>(t);
    parent->addChild(this);
}

TextBox::~TextBox() {
    for (i32 i = 0; i < children.size(); i++){
        //if (children[i] -> getGUIElement() -> getRefCount() > 1) children[i] -> getGUIElement() -> decRef();
    }
    //ToDo: eliminar este
    hide();
}

void TextBox::addChild(GUIElement *elem) {
    children.push_back(elem);
}

void TextBox::setPosition(Vector2<i32> position){
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

bool TextBox::isVisible(){
    return textbox -> visible();
}

void TextBox::setSize(Vector2<i32> size) {
    textbox -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

nanogui::Widget *TextBox::getGUIElement(){
    return textbox;
}