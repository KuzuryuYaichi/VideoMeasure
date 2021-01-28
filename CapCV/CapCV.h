#pragma once

#include <opencv2/opencv.hpp>

#define EXPORT __declspec(dllexport)

EXPORT bool InitMyVideo(const char*);

EXPORT void DestroyMyVideo();

EXPORT long GetFps();

EXPORT long GetFrameCount();

EXPORT double GetRate();

EXPORT double GetPosMsec();

EXPORT double GetPosFrames();

EXPORT double GetPosAviRatio();

EXPORT bool SetPosAviRatio(double);

EXPORT bool SetPosFrames(double);

EXPORT bool GetFrameMat(cv::Mat&, cv::Mat&, std::vector<cv::Point>& result);

EXPORT long GetFrameWidth();

EXPORT long GetFrameHeight();
