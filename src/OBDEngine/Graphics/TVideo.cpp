#include "TVideo.h"

TVideo::TVideo(GLuint pID, VideoData *d){	
	programID = pID;
	data = d;

	mvpID = glGetUniformLocation(programID, "MVP");
	textureID = glGetUniformLocation(programID, "videoTexture");

	float quad[12] = {
		-1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};
	glGenBuffers(1, &vert_buf);
	glBindBuffer(GL_ARRAY_BUFFER, vert_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	float uvs[8] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};
	glGenBuffers(1, &uv_buf);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	
	unsigned short elem[6] = {
		0, 1, 2,
		0, 2, 3
	};
	glGenBuffers(1, &elem_buf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem_buf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elem), elem, GL_STATIC_DRAW);
	
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &frame_tex);
	glBindTexture(GL_TEXTURE_2D, frame_tex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data -> codec_ctx->width, data -> codec_ctx->height, 
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glm::mat4 mvp = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(mvp));
}

TVideo::~TVideo(){
	glDeleteBuffers(1, &vert_buf);
	glDeleteBuffers(1, &uv_buf);
	glDeleteBuffers(1, &elem_buf);
	glDeleteTextures(1, &frame_tex);
}

void TVideo::beginDraw(){
	readFrame();

	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, frame_tex);
	glUniform1i(textureID, 0);

	// Vertex bufer
	glBindBuffer(GL_ARRAY_BUFFER, vert_buf);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);

	// Vertex bufer
	glBindBuffer(GL_ARRAY_BUFFER, uv_buf);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8, 0);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem_buf);

	// Draw the triangles!
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void TVideo::endDraw(){
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

bool TVideo::readFrame() {	
	do {
		if (av_read_frame(data->fmt_ctx, data->packet) < 0) {
			av_packet_unref(data->packet);
			return false;
		}
	
		if (data->packet->stream_index == data->stream_idx) {
			int frame_finished = 0;
		
			if (avcodec_decode_video2(data->codec_ctx, data->av_frame, &frame_finished, 
				data->packet) < 0) {
				av_packet_unref(data->packet);
				return false;
			}
		
			if (frame_finished) {
				if (!data->conv_ctx) {
					data->conv_ctx = sws_getContext(data->codec_ctx->width, 
						data->codec_ctx->height, data->codec_ctx->pix_fmt, 
						data->codec_ctx->width, data->codec_ctx->height, AV_PIX_FMT_RGB24,
						SWS_BICUBIC, NULL, NULL, NULL);
				}
			
				sws_scale(data->conv_ctx, data->av_frame->data, data->av_frame->linesize, 0, 
					data->codec_ctx->height, data->gl_frame->data, data->gl_frame->linesize);
					
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->codec_ctx->width, 
					data->codec_ctx->height, GL_RGB, GL_UNSIGNED_BYTE, 
					data->gl_frame->data[0]);
			}
		}
		
		av_packet_unref(data->packet);
	} while (data->packet->stream_index != data->stream_idx);
	
	return true;
}