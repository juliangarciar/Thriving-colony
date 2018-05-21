#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class TVideo : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TVideo(GLuint programID, VideoData *);

        /**
         * @brief 
         * 
         */
        ~TVideo();

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
	private:
		bool readFrame();
		int decode(AVCodecContext *avctx, AVFrame *frame, int *got_frame, AVPacket *pkt);

		VideoData *data;

		GLuint programID;

		GLuint mvpID;
		GLuint textureID;

		GLuint vert_buf;
		GLuint uv_buf;
		GLuint elem_buf;

		GLuint frame_tex;
};

#endif