#include "ComboBox.h"
#include <GraphicEngine/Window.h>

ComboBox::ComboBox(std::vector<std::string> opts) {
    combobox = Window::Instance() -> getGUIEnvironment() -> add<nanogui::ComboBox>(opts);
    options = opts;
    if (options.size() < 1) this->hide();
}

ComboBox::ComboBox(GUIElement *parent, std::vector<std::string> opts) {
    combobox = parent -> getGUIElement() -> add<nanogui::ComboBox>(opts);
    parent->addChild(this);
    options = opts;
    if (options.size() < 1) this->hide();
}

ComboBox::~ComboBox() {
    for (int i = 0; i < children.size(); i++){
        //ToDo: eliminar hijos
    }
    //ToDo: eliminar este
    hide();
}

void ComboBox::addChild(GUIElement *elem) {
    children . push_back(elem);
}

void ComboBox::show(){
    combobox -> setVisible(true);
}
 
void ComboBox::hide(){
    combobox -> setVisible(false);
}

bool ComboBox::isVisible(){
    return combobox -> visible();
}

void ComboBox::setPosition(Vector2<i32> position){
    combobox -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void ComboBox::setSize(Vector2<i32> size){
    combobox -> setSize(Eigen::Vector2i(size.x, size.y));
}

void ComboBox::setTooltip(std::string text){
    combobox -> setTooltip(text);
}

void ComboBox::setCallback(std::function<void(bool)> callback){
    combobox -> setCallback(callback);
}

i32 ComboBox::addOption(std::string option){
    options.push_back(option);
    combobox->setItems(options);
    if (options.size() == 1) this->show();
    return options.size()-1;
}

void ComboBox::removeOption(i32 option){
    options.erase(options.begin()+option);
    combobox->setItems(options);
    if (options.size() < 1) this->hide();
}

void ComboBox::removeOption(std::string option){
    std::vector<std::string>::iterator it = std::find(options.begin(), options.end(), option);
    if (it != options.end()) {
        options.erase(it);
        combobox->setItems(options);
        if (options.size() < 1) this->hide();
    }
}

i32 ComboBox::getSelectedOption(){
    return combobox->selectedIndex();
}

std::string ComboBox::getSelectedOptionText(){
    return options.at(combobox->selectedIndex());
}
        
nanogui::Widget *ComboBox::getGUIElement(){
    return combobox; 
}