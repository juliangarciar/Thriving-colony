#include <GLFW/glfw3.h>

#include <irrlicht.h>
#include <nanogui/nanogui.h>

#include <iostream>

using namespace std;
using namespace irr;
using namespace nanogui;

int main(int argc, char **argv) {
    int windowWidth = 1280;
    int windowHeight = 720;

    GLFWwindow* gwindow;
    IrrlichtDevice* device;
    video::IVideoDriver* driver;
    scene::ISceneManager* scene;
    nanogui::Screen* gui;

    glfwInit();
    glfwSetTime(0);

    // Create an application window with the following settings:
    gwindow = glfwCreateWindow(windowWidth, windowHeight, "Thriving Colony", nullptr, nullptr);
    if (gwindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(gwindow);

    irr::SIrrlichtCreationParameters params;
    params.DeviceType = E_DEVICE_TYPE::EIDT_GLFW3;
    params.DriverType = video::E_DRIVER_TYPE::EDT_OPENGL;
    params.WindowId = gwindow;
    params.IgnoreInput = true;
    params.WindowSize = core::dimension2du(windowWidth, windowHeight);
    device = createDeviceEx(params);
    if (!device) exit(0); 

    // create video driver
	driver = device -> getVideoDriver();
    driver -> setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

    // create scene manager
	scene = device -> getSceneManager();

    // create gui manager    
    gui = new nanogui::Screen();
    gui -> initialize(gwindow, true);

    glfwSetWindowUserPointer(gwindow, gui);

    glfwSetCharCallback(gwindow,
        [](GLFWwindow *w, unsigned int codepoint) {
            nanogui::Screen *gui = (nanogui::Screen*)glfwGetWindowUserPointer(w);
            gui -> charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(gwindow,
        [](GLFWwindow *w, int count, const char **filenames) {
            nanogui::Screen *gui = (nanogui::Screen*)glfwGetWindowUserPointer(w);
            gui -> dropCallbackEvent(count, filenames);
        }
    );

    glfwSetFramebufferSizeCallback(gwindow,
        [](GLFWwindow *w, int width, int height) {
            nanogui::Screen *gui = (nanogui::Screen*)glfwGetWindowUserPointer(w);
            gui -> resizeCallbackEvent(width, height);
        }
    );

    //Handle events on queue
    glfwSetCursorPosCallback(gwindow,
            [](GLFWwindow *w, double x, double y) {
            nanogui::Screen *gui = (nanogui::Screen*)glfwGetWindowUserPointer(w);
            gui -> cursorPosCallbackEvent(x, y);
        }
    );

    glfwSetScrollCallback(gwindow,
        [](GLFWwindow *w, double x, double y) {
            nanogui::Screen *gui = (nanogui::Screen*)glfwGetWindowUserPointer(w);
            gui -> scrollCallbackEvent(x, y);
       }
    );

    glfwSetMouseButtonCallback(gwindow,
        [](GLFWwindow *w, int button, int action, int modifiers) {
            nanogui::Screen *gui = (nanogui::Screen*)glfwGetWindowUserPointer(w);
            gui -> mouseButtonCallbackEvent(button, action, modifiers);
        }
    );
    
    scene::ICameraSceneNode* camera = scene -> addCameraSceneNode(0);
    //camera->setPosition()

    // Create nanogui gui
        Window *window = new Window(gui, "Misc. widgets");
        window->setPosition(Vector2i(425,15));
        window->setFixedSize(Vector2i(500, 300));
        window->setLayout(new GroupLayout());

        TabWidget* tabWidget = window->add<TabWidget>();

        Widget* layer = tabWidget->createTab("Color Wheel");
        layer->setLayout(new GroupLayout());

        // Use overloaded variadic add to fill the tab widget with Different tabs.
        layer->add<Label>("Color wheel widget", "sans-bold");
        layer->add<ColorWheel>();

        layer = tabWidget->createTab("Function Graph");
        layer->setLayout(new GroupLayout());

        layer->add<Label>("Function graph widget", "sans-bold");

        // Dummy tab used to represent the last tab button.
        tabWidget->createTab("+");

        // A simple counter.
        int counter = 1;
        tabWidget->setCallback([tabWidget, gui, counter] (int index) mutable {
            if (index == (tabWidget->tabCount()-1)) {
                // When the "+" tab has been clicked, simply add a new tab.
                string tabName = "Dynamic " + to_string(counter);
                Widget* layerDyn = tabWidget->createTab(index, tabName);
                layerDyn->setLayout(new GroupLayout());
                layerDyn->add<Label>("Function graph widget", "sans-bold");
                Graph *graphDyn = layerDyn->add<Graph>("Dynamic function");

                graphDyn->setHeader("E = 2.35e-3");
                graphDyn->setFooter("Iteration " + to_string(index*counter));
                VectorXf &funcDyn = graphDyn->values();
                funcDyn.resize(100);
                for (int i = 0; i < 100; ++i)
                    funcDyn[i] = 0.5f *
                        std::abs((0.5f * std::sin(i / 10.f + counter) +
                                  0.5f * std::cos(i / 23.f + 1 + counter)));
                ++counter;
                // We must invoke perform layout from the screen instance to keep everything in order.
                // This is essential when creating tabs dynamically.
                gui->performLayout();
                // Ensure that the newly added header is visible on screen
                tabWidget->ensureTabVisible(index);

            }
        });
        tabWidget->setActiveTab(0);
   
    gui -> setVisible(true);
    gui -> performLayout();

    scene::IMeshSceneNode *cube;
    cube = scene -> addCubeSceneNode(10);
    cube -> setMaterialFlag(video::EMF_LIGHTING, false);
    cube -> setPosition(core::vector3df(20, 20, 20));

    while (!glfwWindowShouldClose(gwindow)){
        glfwPollEvents();
        driver -> beginScene(true, true, video::SColor(0,0,0,0));

        scene -> drawAll();
        gui -> drawWidgets();
        glEnable(GL_DEPTH_TEST);

        driver -> endScene();
    }

    device -> drop();
    glfwTerminate();
}