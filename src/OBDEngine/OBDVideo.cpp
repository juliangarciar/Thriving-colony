#include "OBDVideo.h"

OBDVideo::OBDVideo(OBDSceneNode* parent, OBDShaderProgram *program, std::string path){
	data = new VideoData();

	data->fmt_ctx = NULL;
	data->stream_idx = -1;
	data->video_stream = NULL;
	data->codec_ctx = NULL;
	data->decoder = NULL;
	data->av_frame = NULL;
	data->gl_frame = NULL;
	data->conv_ctx = NULL;

	// open video
	if (avformat_open_input(&data -> fmt_ctx, path.c_str(), NULL, NULL) != 0) {
		std::cout << "Error: failed to open file: " << path.c_str() << std::endl;
		exit(0);
	}
	
	// find stream info
	if (avformat_find_stream_info(data -> fmt_ctx, NULL) < 0) {
		std::cout << "Error: failed to get stream info" << std::endl;
		exit(0);
	}
	
	// dump debug info
	av_dump_format(data -> fmt_ctx, 0, path.c_str(), 0);
	
	// find the video stream
    for (unsigned int i = 0; i < data -> fmt_ctx->nb_streams; ++i) {
        if (data -> fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            data -> stream_idx = i;
            break;
        }
    }

    if (data -> stream_idx == -1) {
		std::cout << "failed to find video stream" << std::endl;
		exit(0);
    }

    data -> video_stream = data -> fmt_ctx->streams[data -> stream_idx];
    data -> codec_ctx = data -> video_stream->codec;

	// find the decoder
    data -> decoder = avcodec_find_decoder(data -> codec_ctx->codec_id);
    if (data -> decoder == NULL) {
		std::cout << "failed to find decoder" << std::endl;
		exit(0);
    }

	// open the decoder
    if (avcodec_open2(data -> codec_ctx, data -> decoder, NULL) < 0) {
    	std::cout << "failed to open codec" << std::endl;
		exit(0);
    }

	// allocate the video frames
    data -> av_frame = av_frame_alloc();
    data -> gl_frame = av_frame_alloc();
    int size = avpicture_get_size(AV_PIX_FMT_RGB24, data -> codec_ctx->width, data -> codec_ctx->height);
    uint8_t *internal_buffer = (uint8_t *)av_malloc(size * sizeof(uint8_t));
    avpicture_fill((AVPicture *)data -> gl_frame, internal_buffer, AV_PIX_FMT_RGB24, 
    	data -> codec_ctx->width, data -> codec_ctx->height);
	data -> packet = (AVPacket *)av_malloc(sizeof(AVPacket));

	//Create the node
    videoNode = new TNode(new TVideo(program->getShaderProgram(), data));
    parent->addChild(videoNode);
}

OBDVideo::~OBDVideo(){
	if (data->av_frame) av_free(data->av_frame);
	if (data->gl_frame) av_free(data->gl_frame);
	if (data->packet) av_free(data->packet);
	if (data->codec_ctx) avcodec_close(data->codec_ctx);
	if (data->fmt_ctx) avformat_free_context(data->fmt_ctx);
    if (data->fmt_ctx) avformat_close_input(&data->fmt_ctx);

	delete videoNode;
	videoNode = nullptr;

	delete data;
	data = nullptr;
}