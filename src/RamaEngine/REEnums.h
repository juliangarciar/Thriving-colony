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
            MATRIX_TEXTURE,
            MATRIX_MVP,
            MATRIX_VIEWMODEL,
            MATRIX_LIGHT,
            MATRICES
        };
        enum TextureTypes {
            TEXTURE_AMBIENT,
            TEXTURE_DIFFUSE,
            TEXTURE_SPECULAR,
            TEXTURE_ALPHA,
            TEXtURE_BUMP
        };
};

#endif