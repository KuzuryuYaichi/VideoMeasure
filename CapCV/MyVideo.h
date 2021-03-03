#ifndef MY_VIDEO_H
#define MY_VIDEO_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#define EXPORT __declspec(dllexport)

class EXPORT MyVideo
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
	bool GetFrameMat(cv::Mat&, cv::Mat&, std::vector<cv::Point>&);
	long GetFrameWidth();
	long GetFrameHeight();

	bool SetPosAviRatio(double PosAviRadio);
	bool SetPosFrames(double PosFrames);
	bool SetPosMsec(double PosMsec);
	bool IsOpen();
private:
	long TotalFrameNumber = 0;
	double Fps = 0;
	double PosMsec = 0;
	double PosFrames = 0;
	double PosAviRadio = 0;
	long FrameWidth = 0;
	long FrameHeight = 0;
	cv::Ptr<cv::BackgroundSubtractorMOG2> bg;
	std::vector<std::vector<cv::Point>> contours;
	cv::Mat frame;
	cv::Mat back;
	cv::Mat fore;

	bool isOpen = false;
};

#endif
