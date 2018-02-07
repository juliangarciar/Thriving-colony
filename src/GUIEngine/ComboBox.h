#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <vector>
#include <nanogui/nanogui.h>
#include "GUIElement.h"

class ComboBox : public GUIElement {

    public:
        ComboBox(std::vector<std::string> opts);
        ComboBox(GUIElement *parent, std::vector<std::string> opts);
        virtual ~ComboBox();

        void show();
        void hide();
        bool isVisible();

        int addOption(std::string option);
        void removeOption(std::string option);
        void removeOption(int option);
        int getSelectedOption();
        std::string getSelectedOptionText();
        
        void setPosition(Vector2<int> position);
        
        void setTooltip(std::string text);
        void setCallback(std::function<void(bool)> callback);

        nanogui::Widget *getGUIElement();
    private:
        nanogui::ComboBox* combobox;
        std::vector<std::string> options;
};

#endif