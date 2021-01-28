#include "MyVideo.h"

MyVideo* myVideo;

void InitMyVideo(std::string str)
{
	myVideo = new MyVideo(str);
}

long GetFps()
{
	return myVideo->GetFps();
}

long GetFrameCount()
{
	return myVideo->GetFrameCount();
}

double GetRate()
{
	return myVideo->GetRate();
}

double GetPosMsec()
{
	return myVideo->GetPosMsec();
}

double GetPosFrames()
{
	return myVideo->GetPosFrames();
}

double GetPosAviRatio()
{
	return myVideo->GetPosAviRatio();
}

bool SetPosAviRatio(double PosAviRadio)
{
	return myVideo->SetPosAviRatio(PosAviRadio);
}

bool SetPosFrames(double PosFrames)
{
	return myVideo->SetPosFrames(PosFrames);
}

cv::Mat&& GetFrameMat(std::vector<cv::Point>& result)
{
	return myVideo->GetFrameMat(result);
}