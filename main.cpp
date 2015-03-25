// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <stdio.h>
#include <string>

#include "CameraThread.hpp"

#include "opencv/highgui.h"

#define SOURCE_0 0
#define SOURCE_1 1
#define FPS 20

int main() {

    cv::VideoCapture capture_0(SOURCE_0);
    cv::VideoCapture capture_1(SOURCE_1);

    if(!capture_0.isOpened() || !capture_1.isOpened() ){
        std::cerr << "[ERROR] Cannot extract images from video" << std::endl;
        return -1;
    }

    // Get the properties from the camera
    double width_0 = capture_0.get(CV_CAP_PROP_FRAME_WIDTH);
    double height_0 = capture_0.get(CV_CAP_PROP_FRAME_HEIGHT);

    double width_1 = capture_1.get(CV_CAP_PROP_FRAME_WIDTH);
    double height_1 = capture_1.get(CV_CAP_PROP_FRAME_HEIGHT);

    // print camera frame size
    std::cout << "Camera properties\n";
    std::cout << "width_0 = " << width_0 << std::endl <<"height_0 = "<< height_0 << std::endl;
    std::cout << "width_1 = " << width_1 << std::endl <<"height_1 = "<< height_1 << std::endl;

    capture_0.release();
    capture_1.release();

    scr::CameraThread c0("/dev/video0", width_0, height_0, FPS);  //-- optional fps at end, set 14 for minoru
    scr::CameraThread c1("/dev/video1", width_1, height_1, FPS);  //-- optional fps at end, set 14 for minoru

    c0.start();
    c1.start();

    std::string FILENAME_VIDEO_0 = "feed_0_.avi";
    std::string FILENAME_VIDEO_1 = "feed_1_.avi";

    // Create the video writer
    cv::VideoWriter video_0(FILENAME_VIDEO_0, CV_FOURCC('X','V','I','D'), FPS, cv::Size((int)width_0,(int)height_0) );
    cv::VideoWriter video_1(FILENAME_VIDEO_1, CV_FOURCC('X','V','I','D'), FPS, cv::Size((int)width_1,(int)height_1) );


    // declarations

    cv::Mat frame_0 = cv::Mat::zeros(height_0, width_0, CV_8UC3);
    double ts0;

    cv::Mat frame_1 = cv::Mat::zeros(height_1, width_1, CV_8UC3);
    double ts1;

    //grab key declarations
    char k;

    while(TRUE){

        // conversion
        c0.toMat(frame_0,ts0);
        c1.toMat(frame_1,ts1);

        // check if timestamps are close enough
        if( fabs(ts0-ts1) > 0.020 )
            continue;

        // Save frame to video
        video_0.write(frame_0);
        video_1.write(frame_1);


    //    printf("c0 [%f] %d %d\n",  ts0, frame_0.rows, frame_0.cols );
    //    printf("c1 [%f] %d %d\n",  ts1, frame_1.rows, frame_1.cols );

        cv::imshow("Frame 0", frame_0);
        cv::imshow("Frame 1", frame_1);


        k = cv::waitKey(1);
        if (k == 27){ // ESC
            capture_0.release();
            capture_1.release();
            c0.stop();
            c1.stop();
            cv::destroyAllWindows();
            std::cout << "[INFO] Quitting program!" << std::endl;
            break;
        }

    }


    return 0;
}



