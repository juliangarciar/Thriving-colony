#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

#include <irrlicht.h>
#include <nanogui/nanogui.h>
#include <GraphicEngine/Vector2.h>

#include <iostream>

using namespace irr;

class Window {
    public:
        static Window* Instance();

        void setEventReceiver(IEventReceiver *receiver);
        void handleGUIEvents();

        void setGUI();

        void beginScene();
        void endScene();

        void close();

        bool isOpen();
        
        void onClose();

        IrrlichtDevice* getDevice();
        video::IVideoDriver* getVideoDriver();
        scene::ISceneManager* getSceneManager();
        nanogui::Screen* getGUIEnvironment();

        int getInitialWindowWidth();
        int getInitialWindowHeight();

        int getRealWindowWidth();
        int getRealWindowHeight();

        float getDeltaTime();

        GLFWwindow *getWindow() {
            return window;
        }
        
    protected:
        Window(int width, int height);
        virtual ~Window();
        Window(const Window & );
        Window &operator = (const Window & );

        void setGLAttributes();

    private:
        static Window* pinstance;

        GLFWwindow* window;

        bool closeWindow;

        IrrlichtDevice* device;
        video::IVideoDriver* driver;
        scene::ISceneManager* scene;
        nanogui::Screen* gui;

        int windowWidth;
        int windowHeight;
        
        double dtThen;
        double deltaTime;
};

#endif