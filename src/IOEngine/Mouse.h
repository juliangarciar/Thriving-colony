#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>
#include <GraphicEngine/Vector2.h>
#include <Enumeration.h>
#include <Types.h>

#define CURSOR_NORMAL GLFW_ARROW_CURSOR
#define CURSOR_IBEAM GLFW_IBEAM_CURSOR
#define CURSOR_CROSSHAIR GLFW_CROSSHAIR_CURSOR
#define CURSOR_HAND GLFW_HAND_CURSOR
#define CURSOR_HRESIZE GLFW_HRESIZE_CURSOR
#define CURSOR_VRESIZE GLFW_VRESIZE_CURSOR

class Mouse {
    public:
        Mouse();
        ~Mouse();

        void refreshStates();

        bool leftMousePressed();
        bool leftMouseReleased();
        bool leftMouseUp();
        bool leftMouseDown();

        bool middleMousePressed();
        bool middleMouseReleased();
        bool middleMouseUp();
        bool middleMouseDown();

        bool rightMousePressed();
        bool rightMouseReleased();
        bool rightMouseUp();
        bool rightMouseDown();

        f32 getWheelX();
        f32 getWheelY();

        void setPosition(Vector2<i32> p);

        void changeIcon(i32 shape);

        void show();
        void hide();

        GLFWcursor *getMouse();
        Vector2<i32> getPosition();

        bool isVisible();

        // Mouse position
        Vector2<i32> position;
        // Mouse wheel
        Vector2<f32> wheel;
		// Mouse button states.
		Enumeration::ioStatesENUM mouseButtonState[GLFW_MOUSE_BUTTON_LAST]; //Left(0), Right(1), Middle(2) and more buttons.
    private:
        bool visible;
        i32 currentCursor;

        GLFWcursor* cursor;
};

#endif