#ifndef SCREEN_H
#define SCREEN_H

#include <irrlicht.h>
#include <IOEngine/InputManager.h>

using namespace irr;

class Screen {
    public:
        static Screen* Instance();

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
        InputManager *getIO();
        
    protected:
        Screen(int width, int height);
        virtual ~Screen();
        Screen(const Screen & );
        Screen &operator = (const Screen & );

    private:
        static Screen* pinstance;
        IrrlichtDevice* device;
        video::IVideoDriver* driver;
        scene::ISceneManager* scene;
        gui::IGUIEnvironment* gui;

        InputManager *io;

        int screenWidth;
        int screenHeight;
        
        float dtThen;
        float deltaTime;
};

#endif