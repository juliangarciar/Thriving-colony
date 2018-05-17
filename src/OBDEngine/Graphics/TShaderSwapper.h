#ifndef TSHADERSWAPPER_H
#define TSHADERSWAPPER_H

#include "TEntity.h"

class TShaderSwapper : public TEntity {
    public:
        /**
         * @brief 
         * @param GLuint
         */
        TShaderSwapper(GLuint);

		/**
		 * @brief Destroy the TShaderSwapper object
		 * 
		 */
		~TShaderSwapper();

		/**
		 * @brief 
		 * 
		 */
        void beginDraw();

		/**
		 * @brief 
		 * 
		 */
        void endDraw();

		/**
		 * @brief Set the Program I D object
		 * 
		 */
		void setProgramID(GLuint);

		/**
		 * @brief Get the Program I D object
		 * 
		 * @return GLuint 
		 */
		GLuint getProgramID();
	private:
		GLuint programID;
};

#endif