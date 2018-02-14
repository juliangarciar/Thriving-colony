#ifndef LABEL_H
#define LABEL_H

#include <nanogui/nanogui.h>
#include <Types.h>
#include <MathEngine/Vector2.h>
#include <GUIEngine/GUIElement.h>

class Label : public GUIElement {

    public:
        Label(std::string t);
        Label(GUIElement *parent, std::string t);
        virtual ~Label();

        void addChild(GUIElement *);

        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);
        void setSize(Vector2<i32> size);

        void setTooltip(std::string t);
        void setLabel(std::string t);
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::Label *label;
};

#endif