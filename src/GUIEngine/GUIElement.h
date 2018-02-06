#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <nanogui/nanogui.h>
#include <GraphicEngine/Vector2.h>

class GUIElement {
    public:
        virtual void show() = 0;
        virtual void hide() = 0;

        virtual bool isVisible() = 0;

        virtual void setPosition(Vector2<int>) = 0;
        virtual void setTooltip(std::string) = 0;

        virtual nanogui::Widget *getGUIElement() = 0;
    private:
};

#endif