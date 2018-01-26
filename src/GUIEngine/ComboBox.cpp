#include "ComboBox.h"
#include <GraphicEngine/Window.h>

ComboBox::ComboBox(std::vector<std::string> opts) {
    combobox = Window::Instance() -> getGUIEnvironment() -> add<nanogui::ComboBox>(opts);
    options = opts;
}

ComboBox::ComboBox(GUIElement *parent, std::vector<std::string> opts) {
    combobox = parent -> getGUIElement() -> add<nanogui::ComboBox>(opts);
    options = opts;
}

ComboBox::~ComboBox() {
    delete combobox;
    combobox = NULL;
}

void ComboBox::show(){
    combobox -> setVisible(true);
}
 
void ComboBox::hide(){
    combobox -> setVisible(false);
}

void ComboBox::setPosition(Vector2<int> position){
    combobox -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void ComboBox::setTooltip(std::string text){
    combobox -> setTooltip(text);
}

void ComboBox::setCallback(std::function<void(bool)> callback){
    combobox -> setCallback(callback);
}

int ComboBox::addOption(std::string option){
    options.push_back(option);
    combobox->setItems(options);
    return options.size()-1;
}

void ComboBox::removeOption(int option){
    options.erase(options.begin()+option);
    combobox->setItems(options);
}

void ComboBox::removeOption(std::string option){
    std::vector<std::string>::iterator it = std::find(options.begin(), options.end(), option);
    if (it != options.end()) {
        options.erase(it);
        combobox->setItems(options);
    }
}

int ComboBox::getSelectedOption(){
    return combobox->selectedIndex();
}

std::string ComboBox::getSelectedOptionText(){
    return options.at(combobox->selectedIndex());
}
        
nanogui::Widget *ComboBox::getGUIElement(){
    return combobox; 
}