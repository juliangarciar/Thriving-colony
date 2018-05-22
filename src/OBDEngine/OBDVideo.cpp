#ifdef USEVIDEO

#include "OBDVideo.h"
#include "Graphics/TVideo.h"

#include <libavutil/error.h>

OBDVideo::OBDVideo(OBDSceneNode* parent, OBDShaderProgram *program, std::string path){
	data = new VideoData();

	// Initalizing these to NULL prevents segfaults!
	data->pFormatCtx = NULL;
	data->pCodecCtxOrig = NULL;
	data->pCodecCtx = NULL;
	data->pCodec = NULL;
	data->pFrame = NULL;
	data->pFrameRGB = NULL;
	data->buffer = NULL;
	data->sws_ctx = NULL;

	int error = 0;

	// open video
	if((error = avformat_open_input(&data->pFormatCtx, path.c_str(), NULL, NULL)) != 0) {
		std::cout << "Error " << av_err2str(error) << ": failed to open file: " << path.c_str() << std::endl;
		exit(0);
	}
	
	// find stream info
	if(avformat_find_stream_info(data->pFormatCtx, NULL) < 0) {
		std::cout << "Error: failed to get stream info" << std::endl;
		exit(0);
	}
	
	// dump debug info
	av_dump_format(data->pFormatCtx, 0, path.c_str(), 0);
	
	// Find the first video stream
	data->videoStream=-1;
	for(int i=0; i<data->pFormatCtx->nb_streams; i++) {
		if(data->pFormatCtx->streams[i]->codecpar->codec_type==AVMEDIA_TYPE_VIDEO) {
			data->videoStream=i;
			break;
		}
	}
	if(data->videoStream==-1) {
		std::cout << "Error: Didn't find a video stream" << std::endl;
		exit(0);
	}
	
	// Get a pointer to the codec context for the video stream
	data->pCodecCtxOrig=data->pFormatCtx->streams[data->videoStream]->codec;
	// Find the decoder for the video stream
	data->pCodec=avcodec_find_decoder(data->pCodecCtxOrig->codec_id);
	if(data->pCodec==NULL) {
		std::cout << "Unsupported codec!" << std::endl;
		exit(0);
	}
	// Copy context
	data->pCodecCtx = avcodec_alloc_context3(data->pCodec);
	if(avcodec_copy_context(data->pCodecCtx, data->pCodecCtxOrig) != 0) {
		std::cout << "Couldn't copy codec context" << std::endl;
		exit(0);
	}

	// Open codec
	if(avcodec_open2(data->pCodecCtx, data->pCodec, NULL) < 0){
		std::cout << "Couldn't open codec context" << std::endl;
		exit(0);
	}
	
	// Allocate video frame
	data->pFrame = av_frame_alloc();
	
	// Allocate an AVFrame structure
	data->pFrameRGB = av_frame_alloc();
	if(data->pFrameRGB == NULL){
		std::cout << "Couldn't allocate frame" << std::endl;
		exit(0);
	}

	data->pFrameRGB->width = data->pCodecCtx->width;
	data->pFrameRGB->height = data->pCodecCtx->height;
	data->pFrameRGB->format = AV_PIX_FMT_RGB24;

	// Determine required buffer size and allocate buffer
	data->numBytes=av_image_get_buffer_size(AV_PIX_FMT_RGB24, data->pCodecCtx->width, data->pCodecCtx->height, 32);
	data->buffer=(uint8_t *)av_malloc(data->numBytes*sizeof(uint8_t));
	
	// Assign appropriate parts of buffer to image planes in pFrameRGB
	// Note that pFrameRGB is an AVFrame, but AVFrame is a superset
	// of AVPicture
	av_image_fill_arrays(data->pFrameRGB->data, data->pFrameRGB->linesize, data->buffer, (AVPixelFormat)data->pFrameRGB->format, data->pFrameRGB->width, data->pFrameRGB->height, 1);
	
	// initialize SWS context for software scaling
	data->sws_ctx = sws_getContext(
		data->pCodecCtx->width,
		data->pCodecCtx->height,
		data->pCodecCtx->pix_fmt,
		data->pCodecCtx->width,
		data->pCodecCtx->height,
		AV_PIX_FMT_RGB24,
		SWS_BILINEAR,
		NULL,
		NULL,
		NULL
	);

	//Create the node
    videoNode = new TNode(new TVideo(program->getShaderProgram(), data));
    parent->addChild(videoNode);
}

OBDVideo::~OBDVideo(){
	// Free the RGB image
	if (data->buffer) av_free(data->buffer);
	if (data->pFrameRGB) av_frame_free(&data->pFrameRGB);
	
	// Free the YUV frame
	if (data->pFrame) av_frame_free(&data->pFrame);
	
	// Close the codecs
	if (data->pCodecCtx) avcodec_close(data->pCodecCtx);
	if (data->pCodecCtxOrig) avcodec_close(data->pCodecCtxOrig);

	// Close the video file
	if (data->pFormatCtx) avformat_close_input(&data->pFormatCtx);

	if (data->sws_ctx) sws_freeContext(data->sws_ctx);

	delete videoNode;
	videoNode = nullptr;

	delete data;
	data = nullptr;
}

void OBDVideo::play(){
    TVideo* v = (TVideo*) videoNode -> getEntity();
	v -> setPlay(true);
}

void OBDVideo::pause(){
    TVideo* v = (TVideo*) videoNode -> getEntity();
	v -> setPlay(false);
}

void OBDVideo::setLoop(bool l){
    TVideo* v = (TVideo*) videoNode -> getEntity();
	v -> setLoop(l);
}
#endif