#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <nanogui/nanogui.h>
#include "GUIElement.h"

class ProgressBar : public GUIElement {

    public:
        ProgressBar();
        ProgressBar(GUIElement *parent);
        virtual ~ProgressBar();

        void show();
        void hide();
        bool isVisible();
        
        void setPosition(Vector2<int> position);

        void setTooltip(std::string t);
        void setValue(float value);

        void setSize(Vector2<int> size);
        
        nanogui::Widget *getGUIElement();
    private:
        nanogui::ProgressBar *progressBar;
};

#endif