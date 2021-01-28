#ifndef DECODEC_H
#define DECODEC_H

extern "C" {
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
}

int decodeVideo();

#endif // DECODEC_H
