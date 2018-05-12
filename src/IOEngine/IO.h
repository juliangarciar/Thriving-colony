#ifndef IO_H
#define IO_H

#include <OBDEngine/ResourceManager/ResourceManager.h>
#include <IOEngine/Mouse.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/EventSystem.h>

class IO {
    public:
        /**
		 * @brief Crea una Instancia de IO
		 */
        static IO* Instance();

         /**
		 * @brief Devuelve la tecla actual
         * @return Devuelve un objeto tipo Keyboard
		 */
        Keyboard *getKeyboard();

         /**
		 * @brief Devuelve las coordenadas del raton
         * @return Devuelve un objeto tipo getCursor
		 */
        Mouse *getMouse();
         /**
		 * @brief Devuelve el evento actual
         * @return Devuelve un objeto tipo EventSystem
		 */
        EventSystem *getEventManager();
        /**
         * @brief 
         * 
         * @return ResourceManager* 
         */
        ResourceManager *getResourceManager();
    protected:
        /**
         * @brief 
         * 
         */
        IO();

        /**
         * @brief 
         * 
         */
        ~IO();
    private:
        static IO* pinstance;

        Mouse *cursor;
        Keyboard *keyboard;

        EventSystem *events;

        ResourceManager *resourceManager;
        
};

#endif