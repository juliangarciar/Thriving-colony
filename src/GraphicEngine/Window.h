#ifndef WINDOW_H
#define WINDOW_H

#include <irrlicht/irrlicht.h>
#include <GLFW/glfw3.h>
#include <nanogui/nanogui.h>

#include <Types.h>
#include <MathEngine/Vector2.h>

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

        i32 getInitialWindowWidth();
        i32 getInitialWindowHeight();

        i32 getRealWindowWidth();
        i32 getRealWindowHeight();

        f32 getDeltaTime();

        GLFWwindow *getWindow() {
            return window;
        }
        
    protected:
        Window(i32 width, i32 height);
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

        i32 windowWidth;
        i32 windowHeight;
        
        double dtThen;
        double deltaTime;
};

#endif