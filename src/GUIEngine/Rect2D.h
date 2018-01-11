#ifndef RECT_H
#define RECT_H

#include <iostream>
#include <irrlicht.h>

using namespace irr;

template <class T>
class Rect2D {
    private:
    public:
        T x, y, w, h;

		//ToDo: constructor con primer y ultimo puntos

        /**
         * Crea un objeto zona de impresion
         * @param rX: Coordenada x
         * @param rY: Coordenada y
         * @param rW: Ancho
         * @param rH: Alto
         */
        Rect2D(T rX, T rY, T rW, T rH);
        
        /**
         * Crea un objeto zona de impresion
         * @param rect: Zona a imprimir
         */
        Rect2D(core::rect<T> rect);
        
        /**
         * Crea un objeto zona de impresion
         * @param rect: Zona a imprimir
         */
        Rect2D(const Rect2D<T>& rect);
        
        virtual ~Rect2D();
        
        /**
         * Establece la zona de corte
         * @param rX: Coordenada x
         * @param rY: Coordenada y
         * @param rW: Ancho
         * @param rH: Alto
         */
        void setRect2D(T rX, T rY, T rW, T rH);
        
        /**
         * Establece la zona de corte
         * @param rect: Zona de core
         */
        void setRect2D(core::rect<T> rect);

        //Get Fixed Rect 2D
        Rect2D<T> getFixed();
        
        //Return
        core::rect<T> getRect2D();
        
        friend std::ostream& operator << (std::ostream &o,const Rect2D<float> &p);
        friend std::ostream& operator << (std::ostream &o,const Rect2D<int> &p);
};

inline std::ostream& operator << (std::ostream &o,const Rect2D<float> &p) {
    o << "(" << p.x << ", " << p.y << ", " << p.w << ", " << p.h << ")\n";
    return o;
}
inline std::ostream& operator << (std::ostream &o,const Rect2D<int> &p) {
    o << "(" << p.x << ", " << p.y << ", " << p.w << ", " << p.h << ")\n";
    return o;
}

#endif /* RECT_H */
