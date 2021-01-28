#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class MyVideo
{
public:
	MyVideo(std::string filePath);
	~MyVideo();
	cv::VideoCapture cap;
	long GetFrameCount();
	long GetFps();
	double GetRate();
	double GetPosMsec();
	double GetPosFrames();
	double GetPosAviRatio();
	cv::Mat&& GetFrameMat(std::vector<cv::Point>& result);

	bool SetPosAviRatio(double PosAviRadio);
	bool SetPosFrames(double PosFrames);
private:
	long TotalFrameNumber = 0;
	double Fps = 0;
	double PosMsec = 0;
	double PosFrames = 0;
	double PosAviRadio = 0;
	cv::Ptr<cv::BackgroundSubtractorMOG2> bg;
	std::vector<std::vector<cv::Point>> contours;
	cv::Mat frame;
	cv::Mat back;
	cv::Mat fore;
};

int ReadVideo();