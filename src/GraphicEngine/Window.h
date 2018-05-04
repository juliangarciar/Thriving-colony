#ifndef WINDOW_H
#define WINDOW_H

#include <OBDEngine/OBDEngine.h>
#include <GLFW/glfw3.h>
#include <nanogui/nanogui.h>

#include <Types.h>
#include <MathEngine/Vector2.h>

class Window {
    public:
        static Window* Instance();
		
        void handleGUIEvents();

        void setGUI();

        void beginScene();
        void endScene();

        void close();

        bool isOpen();
        
        void onClose();

		OBDEngine *getEngine();

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

		OBDEngine *e;

        nanogui::Screen* gui;

        i32 windowWidth;
        i32 windowHeight;
        
        double dtThen;
        double deltaTime;
        i32 framerate;
};

#endif