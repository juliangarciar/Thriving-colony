#ifndef SLIDER_H
#define SLIDER_H

#include <nanogui/nanogui.h>
#include "GUIElement.h"
#include <Types.h>
#include <GraphicEngine/Window.h>

class Slider : public GUIElement {

    public:
        Slider(GUIElement *parent);
        virtual ~Slider();

        void addChild(GUIElement *);

        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);

        void setTooltip(std::string t);
        void setRange(std::pair<f32, f32> r);

        nanogui::Widget *getGUIElement();
    private:
        nanogui::Slider *slider;
};

#endif