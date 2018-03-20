#ifndef REENUMS_H
#define REENUMS_H

/**
 * @class REEnums
 * @brief Declara las enumeraciones que van a ser necesarias
 */
class REEnums {
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

        enum LightTypes {
            LIGHT_POINT,
            LIGHT_DIRECTIONAL,
            LIGHT_SPOT
        };
};

#endif