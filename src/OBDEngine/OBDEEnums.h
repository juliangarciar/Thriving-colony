#ifndef OBDEENUMS_H
#define OBDEENUMS_H

/**
 * @class OBDEEnums
 * @brief Declara las enumeraciones que van a ser necesarias
 */
class OBDEEnums {
    public:
        enum CameraProjection {
            ProjectionPerspective,
            ProjectionOrtographic,
            ProjectionParallel
        };
        enum ShaderType {
            VERTEX,
            FRAGMENT
        };
        enum Matrices {
            MATRIX_PROJECTION = 0,
            MATRIX_VIEW,
            MATRIX_MODEL,
            MATRIX_MVP,
            MATRIX_VIEWMODEL,
            
            MATRIX_LIGHT,

            MATRIX_TEXTURE_AMBIENT,
            MATRIX_TEXTURE_DIFFUSE,
            MATRIX_TEXTURE_SPECULAR,
            MATRIX_TEXTURE_ALPHA,
            MATRIX_TEXTURE_BUMP,
            MATRICES
        };
        enum TextureTypes {
            TEXTURE_AMBIENT,
            TEXTURE_DIFFUSE,
            TEXTURE_SPECULAR,
            TEXTURE_ALPHA,
            TEXTURE_BUMP
        };
};

#endif