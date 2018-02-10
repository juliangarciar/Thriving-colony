#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <nanogui/nanogui.h>
#include <GraphicEngine/Vector2.h>
#include <Types.h>

class GUIElement {
    public:
        virtual void addChild(GUIElement *) = 0;

        virtual void show() = 0;
        virtual void hide() = 0;

        virtual bool isVisible() = 0;

        virtual void setPosition(Vector2<i32>) = 0;
        virtual void setTooltip(std::string) = 0;

        virtual nanogui::Widget *getGUIElement() = 0;
    protected:
        std::vector<GUIElement*> children;
};

#endif