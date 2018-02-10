#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <nanogui/nanogui.h>
#include "GUIElement.h"
#include <Types.h>

class ProgressBar : public GUIElement {

    public:
        ProgressBar();
        ProgressBar(GUIElement *parent);
        virtual ~ProgressBar();

        void addChild(GUIElement *);

        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<i32> position);

        void setTooltip(std::string t);
        void setValue(f32 value);

        void setSize(Vector2<i32> size);
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::ProgressBar *progressBar;
};

#endif