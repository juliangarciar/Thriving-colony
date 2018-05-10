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
        void endScene(bool b);

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

        /**
         * @brief calculates the framerate of the window. It is important to call
         * this function after the game logic has fully executed to see how long it
         * took to get through it, otherwise results won't be correct.
         * 
         */
        void calculateFramerate();

        /**
         * @brief returns the current framerate
         * 
         * @return i32 framerate
         */
        i32 getFrameRate();
        
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
        i32 framerate;
};

#endif