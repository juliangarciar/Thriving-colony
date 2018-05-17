#ifndef OBDENUMS_H
#define OBDENUMS_H

/**
 * @class OBDEnums
 * @brief Declara las enumeraciones que van a ser necesarias
 */
class OBDEnums {
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

        enum TextureTypes {
            TEXTURE_DIFFUSE,
            TEXTURE_OCLUSIONS,
            TEXTURE_SPECULAR,
            TEXTURE_ALPHA,
            TEXTURE_BUMP,

            TEXTURE_SIZE
        };

        enum LightTypes {
            LIGHT_POINT,
            LIGHT_DIRECTIONAL,
            LIGHT_SPOT
        };

        // Internal
        enum OpenGLIDs {
            CURRENT_PROGRAM_ID = 0,

            VAO_BUFFER,

            MATRIX_PROJECTION,
            MATRIX_VIEW,
            MATRIX_MODEL,
            MATRIX_MV,
            MATRIX_MVP,

            BUFFER_LIGHT,
            BUFFER_MATERIAL,
            BUFFER_TEXTURE,

            LIGHT_AMOUNT,
			CAMERA_POSITION,

            SAMPLER_OCLUSIONS,
            SAMPLER_DIFFUSE,
            SAMPLER_SPECULAR,
            SAMPLER_ALPHA,
            SAMPLER_BUMP,

            PARAMS
        };
};

#endif