#include "TVideo.h"

TVideo::TVideo(GLuint pID, VideoData *d){	
	programID = pID;
	data = d;

	play = false;
	loop = false;

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->pCodecCtx->width, data->pCodecCtx->height, 
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	mvpID = glGetUniformLocation(programID, "MVP");
	textureID = glGetUniformLocation(programID, "videoTexture");
}

TVideo::~TVideo(){
	glDeleteBuffers(1, &vert_buf);
	glDeleteBuffers(1, &uv_buf);
	glDeleteBuffers(1, &elem_buf);
	glDeleteTextures(1, &frame_tex);
}

void TVideo::beginDraw(){
	if (play) readFrame();
	
	glm::mat4 mvp = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(mvp));

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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool TVideo::readFrame() {
	int error;
	error = av_read_frame(data->pFormatCtx, &data->packet);
	if (error == 0) {
		//Todo bien, todo correcto
	} else if (error == AVERROR_EOF) {
		if(loop) {
			auto stream = data->pFormatCtx->streams[data->videoStream];
			avio_seek(data->pFormatCtx->pb, 0, SEEK_SET);
			avformat_seek_file(data->pFormatCtx, data->videoStream, 0, 0, stream->duration, 0);
		} else return false;
	} else {
		//std::cout << "Error " << error << " al leer el frame" << std::endl;
		return false;
	}
	// Is this a packet from the video stream?
	if(data->packet.stream_index==data->videoStream) {
		// Decode video frame
		decode(data->pCodecCtx, data->pFrame, &data->frameFinished, &data->packet);
		
		// Did we get a video frame?
		if(data->frameFinished) {
			// Convert the image from its native format to RGB
			sws_scale(data->sws_ctx, (uint8_t const * const *)data->pFrame->data,
					data->pFrame->linesize, 0, data->pCodecCtx->height,
					data->pFrameRGB->data, data->pFrameRGB->linesize);
			
			glBindTexture(GL_TEXTURE_2D, frame_tex);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->pCodecCtx->width, 
				data->pCodecCtx->height, GL_RGB, GL_UNSIGNED_BYTE, 
				data->pFrameRGB->data[0]);
		}
	}
	
	// Free the packet that was allocated by av_read_frame
	av_packet_unref(&data->packet);
	
	return true;
}

int TVideo::decode(AVCodecContext *avctx, AVFrame *frame, int *got_frame, AVPacket *pkt) {
    int ret;

    *got_frame = 0;

    if (pkt) {
        ret = avcodec_send_packet(avctx, pkt);
        // In particular, we don't expect AVERROR(EAGAIN), because we read all
        // decoded frames with avcodec_receive_frame() until done.
        if (ret < 0)
            return ret == AVERROR_EOF ? 0 : ret;
    }

    ret = avcodec_receive_frame(avctx, frame);
    if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
        return ret;
    if (ret >= 0)
        *got_frame = 1;

    return 0;
}

void TVideo::setPlay(bool p){
	play = p;
}

void TVideo::setLoop(bool l){
	loop = l;
}