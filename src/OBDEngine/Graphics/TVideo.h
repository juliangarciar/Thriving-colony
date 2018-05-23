#ifndef TVIDEO_H
#define TVIDEO_H

#ifdef USEVIDEO

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

		/**
		 * @brief 
		 * @param play
		 */
		void setPlay(bool);

		/**
		 * @brief Set the Loop
		 * @param loop
		 */
		void setLoop(bool);
	private:
		bool readFrame();
		int decode(AVCodecContext *avctx, AVFrame *frame, int *got_frame, AVPacket *pkt);

		bool play;
		bool loop;

		VideoData *data;

		GLuint programID;

		GLuint mvpID;
		GLuint textureID;

		GLuint VAO;
		GLuint vert_buf;
		GLuint uv_buf;
		GLuint elem_buf;

		GLuint frame_tex;
		
		glm::mat4 mvp;
};

#endif
#endif