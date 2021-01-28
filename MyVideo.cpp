#include "MyVideo.h"

MyVideo::MyVideo(std::string filePath)
{
	if (!cap.open(cv::String(filePath)))
	{
		return;
	}
	bg = cv::createBackgroundSubtractorMOG2();
	bg->setNMixtures(100);
	//bg.bShadowDetection = false;
}

MyVideo::~MyVideo()
{
	if (cap.isOpened())
		cap.release();
}

double MyVideo::GetRate()
{
	Fps = cap.get(cv::CAP_PROP_FPS);
	return Fps;
}

double MyVideo::GetPosMsec()
{
	PosMsec = cap.get(cv::CAP_PROP_POS_MSEC);
	return PosMsec;
}

double MyVideo::GetPosFrames()
{
	PosFrames = cap.get(cv::CAP_PROP_POS_FRAMES);
	return PosFrames;
}

double MyVideo::GetPosAviRatio()
{
	PosAviRadio = cap.get(cv::CAP_PROP_POS_AVI_RATIO);
	return PosAviRadio;
}

bool MyVideo::SetPosFrames(double PosFrames)
{
	bool re = cap.set(cv::CAP_PROP_POS_FRAMES, PosFrames);
	if (re)
		this->PosFrames = PosFrames;
	return re;
}

bool MyVideo::SetPosAviRatio(double PosAviRadio)
{
	if (PosAviRadio < 0 || PosAviRadio > 1)
		return false;
	bool re = cap.set(cv::CAP_PROP_POS_AVI_RATIO, PosAviRadio);
	if(re)
		this->PosAviRadio = PosAviRadio;
	return re;
}

long MyVideo::GetFrameCount()
{
	TotalFrameNumber = cap.get(cv::CAP_PROP_FRAME_COUNT);
	return TotalFrameNumber;
}

long MyVideo::GetFps()
{
	Fps = cap.get(cv::CAP_PROP_FPS);
	return Fps;
}

cv::Mat&& MyVideo::GetFrameMat(std::vector<cv::Point>& result)
{
	cap >> frame;
	cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
	bg->apply(frame, fore, 0.01);
	//bg->getBackgroundImage(back);
	cv::erode(fore, fore, cv::Mat()); //腐蚀
	cv::dilate(fore, fore, cv::Mat());//膨胀
	cv::findContours(fore, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	cv::drawContours(frame, contours, -1, cv::Scalar(0, 0, 255), 2);
	cv::threshold(fore, fore, 80, 250, cv::THRESH_BINARY_INV);
	int index = 0;
	for (auto _ = contours.begin(); _ != contours.end(); _++)
	{
		long x = 0, y = 0;
		for (auto iter = _->begin(); iter != _->end(); iter++)
		{
			x += iter->x;
			y += iter->y;
		}
		cv::Point p(x / _->size(), y / _->size());
		result.push_back(p);
	}
	return std::move(fore);

	////设置开始帧()
	//long frameToStart = 300;
	//cap.set(cv::CAP_PROP_POS_FRAMES, frameToStart);
	//cout << "从第" << frameToStart << "帧开始读" << endl;
	////设置结束帧
	//int frameToStop = 400;
	//if (frameToStop < frameToStart)
	//{
	//	cout << "结束帧小于开始帧，程序错误，即将退出！" << endl;
	//	return -1;
	//}
	//else
	//{
	//	cout << "结束帧为：第" << frameToStop << "帧" << endl;
	//}
}
