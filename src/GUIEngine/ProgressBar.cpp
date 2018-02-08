#include "ProgressBar.h"
#include <GraphicEngine/Window.h>

ProgressBar::ProgressBar() {
    progressBar = Window::Instance() -> getGUIEnvironment() -> add<nanogui::ProgressBar>();
}

ProgressBar::ProgressBar(GUIElement *parent) {
    progressBar = parent -> getGUIElement() -> add<nanogui::ProgressBar>();
}

ProgressBar::~ProgressBar() {
    //ToDo: borrar ProgressBar
}

void ProgressBar::setPosition(Vector2<int> position){
    progressBar -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void ProgressBar::setTooltip(std::string t){
    progressBar->setTooltip(t);
}

void ProgressBar::setValue(float v) {
    progressBar -> setValue(v);
}

void ProgressBar::setSize(Vector2<int> size) {
    progressBar -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

void ProgressBar::show(){
    progressBar -> setVisible(true);
}
 
void ProgressBar::hide(){
    progressBar -> setVisible(false);
}

bool ProgressBar::isVisible(){
    return progressBar -> visible();
}

nanogui::Widget *ProgressBar::getGUIElement(){
    return progressBar;
}