#ifndef RECT_H
#define RECT_H

#include <irrlicht/irrlicht.h>
#include <Types.h>

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

        //Get Fixed Rect 2D
        Rect2D<T> getFixed();
        
        friend std::ostream& operator << (std::ostream &o,const Rect2D<f32> &p);
        friend std::ostream& operator << (std::ostream &o,const Rect2D<i32> &p);
};

inline std::ostream& operator << (std::ostream &o,const Rect2D<f32> &p) {
    o << "(" << p.x << ", " << p.y << ", " << p.w << ", " << p.h << ")\n";
    return o;
}
inline std::ostream& operator << (std::ostream &o,const Rect2D<i32> &p) {
    o << "(" << p.x << ", " << p.y << ", " << p.w << ", " << p.h << ")\n";
    return o;
}

#endif /* RECT_H */
