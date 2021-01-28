#include "decodec.h"
#include "bitmap_image.hpp"
#include <stdio.h>

void saveFrame(AVFrame *pframe, int width, int height, int iframe) {
    const char *BASE_PATH = "C:/Users/27318/Desktop/build-QWidgetDemo-Desktop_Qt_5_15_1_MinGW_64_bit-Debug/VideoMeasure/debug";
    char filename[200];
    sprintf(filename, "%s/img/frame%d.bmp", BASE_PATH, iframe);

    bitmap_image bi(width, height, pframe->data[0]);
    bi.save_image(filename);
}

int decodeVideo() {
    AVFormatContext	*pFormatCtx;
    int i, videoindex;
    AVCodecContext  *pCodecCtx;
    AVCodec *pCodec;
    AVFrame *pFrame,*pFrameRgb;
    AVPacket *packet;
    int res, get_picture_ptr;
    char filePath[] = "D:/Share/MM_Projects/Fish/AVSEQ01.mp4";
//    char filePath[] = "../video/test.flv";

    av_register_all();
    avformat_network_init();
    pFormatCtx = avformat_alloc_context();

    if (avformat_open_input(&pFormatCtx, filePath, NULL, NULL) != 0) {
        printf("Couldn't open input stream.\n");
        return -1;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL)<0){
        printf("Couldn't find stream information.\n");
        return -1;
    }

    videoindex = -1;
    for (i = 0; i < pFormatCtx -> nb_streams; i++)
        if (pFormatCtx -> streams[i] -> codec -> codec_type == AVMEDIA_TYPE_VIDEO){
            videoindex = i;
            break;
        }
    if (videoindex == -1) {
        printf("Didn't find a video stream.\n");
        return -1;
    }

    pCodecCtx = pFormatCtx -> streams[videoindex] -> codec;   // 获取视频 codec
    pCodec = avcodec_find_decoder(pCodecCtx -> codec_id);   //

    struct SwsContext *swsCtx = sws_getContext (
        pCodecCtx->width,
        pCodecCtx->height,
        pCodecCtx->pix_fmt,
        pCodecCtx->width,
        pCodecCtx->height,
        AV_PIX_FMT_BGR24,
        SWS_BILINEAR,
        NULL,
        NULL,
        NULL
    );

    if (pCodec == NULL) {
        printf("Codec not found.\n");
        return -1;
    }
    if (avcodec_open2(pCodecCtx, pCodec,NULL) < 0) {
        printf("Could not open codec.\n");
        return -1;
    }

    pFrame = av_frame_alloc();
    pFrameRgb = av_frame_alloc();

    int num_bytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
    uint8_t *buffer = (uint8_t *)av_malloc(num_bytes * sizeof(uint8_t));

    packet = (AVPacket *) av_malloc(sizeof(AVPacket));

    avpicture_fill(
        (AVPicture *)pFrameRgb,
        buffer,
        AV_PIX_FMT_RGB24,
        pCodecCtx->width,
        pCodecCtx->height
    );

    av_dump_format(pFormatCtx, 0, filePath, 0);

    int index = 0;
    while (av_read_frame(pFormatCtx, packet) >= 0) {
        if (packet -> stream_index == videoindex){
            res = avcodec_decode_video2(pCodecCtx, pFrame, &get_picture_ptr, packet);
            if (res < 0) {
                printf("decode error.\n");
                return -1;
            }

            if (get_picture_ptr != 0) {
                sws_scale(swsCtx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRgb->data, pFrameRgb->linesize);

//                if (++index < 100) {
//                    saveFrame(pFrameRgb, pCodecCtx->width, pCodecCtx->height, index);
//                    printf("picture_ptr: %d \n", get_picture_ptr);
//                }
            }
        }
        av_free_packet(packet);
    }

    av_free(buffer);
    av_free(pFrameRgb);
    av_free(pFrame);

    avcodec_close(pCodecCtx);

    return 0;
}

