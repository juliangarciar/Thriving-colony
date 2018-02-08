#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <vector>
#include <nanogui/nanogui.h>
#include "GUIElement.h"
#include <Types.h>

class ComboBox : public GUIElement {

    public:
        ComboBox(std::vector<std::string> opts);
        ComboBox(GUIElement *parent, std::vector<std::string> opts);
        virtual ~ComboBox();

        void show();
        void hide();
        bool isVisible();

        i32 addOption(std::string option);
        void removeOption(std::string option);
        void removeOption(i32 option);
        i32 getSelectedOption();
        std::string getSelectedOptionText();
        
        void setPosition(Vector2<i32> position);
        
        void setTooltip(std::string text);
        void setCallback(std::function<void(bool)> callback);

        nanogui::Widget *getGUIElement();
    private:
        nanogui::ComboBox* combobox;
        std::vector<std::string> options;
};

#endif