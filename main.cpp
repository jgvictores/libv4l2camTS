/*
 * Copyright (C) 2009 Giacomo Spigler
 * 2015 - Juan G Victores - enable timestamp on toMat
 * CopyPolicy: Released under the terms of the GNU GPL v3.0.
 */

#include <stdio.h>
#include "libcam.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <string>

#define SOURCE_0 0
#define SOURCE_1 1
#define FPS 20

using namespace std;
using namespace cv;

int main() {

    cv::VideoCapture capture_0(SOURCE_0);
    cv::VideoCapture capture_1(SOURCE_1);

    if(!capture_0.isOpened() || !capture_1.isOpened() ){
        cerr << "[ERROR] Cannot extract images from video" << endl;
        return -1;
    }

    // Get the properties from the camera
    double width_0 = capture_0.get(CV_CAP_PROP_FRAME_WIDTH);
    double height_0 = capture_0.get(CV_CAP_PROP_FRAME_HEIGHT);

    double width_1 = capture_1.get(CV_CAP_PROP_FRAME_WIDTH);
    double height_1 = capture_1.get(CV_CAP_PROP_FRAME_HEIGHT);

    // print camera frame size
    cout << "Camera properties\n";
    cout << "width_0 = " << width_0 << endl <<"height_0 = "<< height_0 << endl;
    cout << "width_1 = " << width_1 << endl <<"height_1 = "<< height_1 << endl;

    capture_0.release();
    capture_1.release();

    Camera c0("/dev/video0", width_0, height_0, FPS);  //-- optional fps at end, set 14 for minoru
    Camera c1("/dev/video1", width_1, height_1, FPS);  //-- optional fps at end, set 14 for minoru


    string FILENAME_VIDEO_0 = "feed_0_.avi";
    string FILENAME_VIDEO_1 = "feed_1_.avi";

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

        // update
        if( ! c0.Update() ) {
            printf("[error] update timeout c0.\n");
            return 1;
        }
        if( ! c1.Update() ) {
            printf("[error] update timeout c1.\n");
            return 1;
        }


        // conversion
        c0.toMat(frame_0,ts0);
        c1.toMat(frame_1,ts1);


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
            cv::destroyAllWindows();
            cout << "[INFO] Quitting program!" << endl;
            break;
        }

    }


    return 0;
}



