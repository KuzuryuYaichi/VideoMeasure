#include "pch.h"

#include "CapCV.h"
#include "MyVideo.h"

MyVideo* myVideo = nullptr;

bool InitMyVideo(const char *str)
{
	myVideo = new MyVideo(std::string(str));
	if (myVideo != nullptr)
		return myVideo->IsOpen();
}

void DestroyMyVideo()
{
	if(myVideo != nullptr)
		delete myVideo;
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

bool GetFrameMat(cv::Mat& fore, cv::Mat& orgFrame, std::vector<cv::Point>& result)
{
	return myVideo->GetFrameMat(fore, orgFrame, result);
}

long GetFrameWidth()
{
	return myVideo->GetFrameWidth();
}

long GetFrameHeight()
{
	return myVideo->GetFrameHeight();
}
