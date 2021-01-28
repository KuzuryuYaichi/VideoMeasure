#pragma once

#include <string>

void InitMyVideo(std::string str);

long GetFps();

long GetFrameCount();

double GetRate();

double GetPosMsec();

double GetPosFrames();

double GetPosAviRatio();

bool SetPosAviRatio(double);

bool SetPosFrames(double);

cv::Mat&& GetFrameMat(std::vector<cv::Point>& result);