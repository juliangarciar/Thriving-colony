#ifndef WINDOW_H
#define WINDOW_H

#include <irrlicht.h>

using namespace irr;

class Window {
    public:
        static Window* Instance();

        void setEventReceiver(IEventReceiver *receiver);

        void beginScene();
        void endScene();

        bool isOpen();
        bool isReady();
        
        void close();

        IrrlichtDevice* getDevice();
        video::IVideoDriver* getVideoDriver();
        scene::ISceneManager* getSceneManager();
        gui::IGUIEnvironment* getGUIEnvironment();

        int getScreenWidth();
        int getScreenHeight();

        float getDeltaTime();
        
    protected:
        Window(int width, int height);
        virtual ~Window();
        Window(const Window & );
        Window &operator = (const Window & );

    private:
        static Window* pinstance;
        IrrlichtDevice* device;
        video::IVideoDriver* driver;
        scene::ISceneManager* scene;
        gui::IGUIEnvironment* gui;

        int screenWidth;
        int screenHeight;
        
        float dtThen;
        float deltaTime;
};

#endif