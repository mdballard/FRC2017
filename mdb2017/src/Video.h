
#ifndef VIDEO_H
#define VIDEO_H
#include "WPILib.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <Thread>

typedef struct
{
	int  Size_X;
	int  Size_Y;

	int  CAM1_Brightness;
	int  CAM1_Exposure;
	bool CAM1_AutoExposure;
	int  CAM1_WhiteBalance;
	bool CAM1_AutoWhiteBalance;

	int  CAM1_FPS;
	bool CAM1_Enable;

	int  CAM2_Brightness;
	int  CAM2_Exposure;
	bool CAM2_AutoExposure;
	int  CAM2_WhiteBalance;
	bool CAM2_AutoWhiteBalance;

	int  CAM2_FPS;
	bool CAM2_Enable;

	bool CAM1_Selected;
	int  changeCount;


} cameraControl;


class Video{
private:

	std::shared_ptr<cs::UsbCamera> Cam_01;
	std::shared_ptr<cs::UsbCamera> Cam_02;
	cs::CvSink cvSink1;
	cs::CvSink cvSink2;
	cs::CvSource outputStreamStd;
    cv::Mat image;
    cameraControl *cc;
    int myChangeCount;
    bool cam1CurrentCam;

public:
	Video(cameraControl *control);
    bool Init();
    void Run();
    void End();
    void Configure();

};

#endif
