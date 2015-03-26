// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "SyncedCameraRecorder.hpp"

namespace scr
{

bool SyncedCameraRecorder::discoverWidthHeight()
{
    cv::VideoCapture capture_0(SOURCE_0);
    cv::VideoCapture capture_1(SOURCE_1);

    if(!capture_0.isOpened() || !capture_1.isOpened() )
    {
        fprintf(stderr,"[ERROR] Cannot extract images from video for discoverWidthHeight.\n");
        return false;
    }

    // Get the properties from the camera
    width_0 = capture_0.get(CV_CAP_PROP_FRAME_WIDTH);
    height_0 = capture_0.get(CV_CAP_PROP_FRAME_HEIGHT);

    width_1 = capture_1.get(CV_CAP_PROP_FRAME_WIDTH);
    height_1 = capture_1.get(CV_CAP_PROP_FRAME_HEIGHT);

    // print camera frame size
    printf("Camera properties:\n");
    printf("width_0 = %d\n",width_0);
    printf("height_0 = %d\n",height_0);
    printf("width_1 = %d\n",width_1);
    printf("height_1 = %d\n",height_1);

    capture_0.release();
    capture_1.release();
    return true;
}

int SyncedCameraRecorder::main()
{
    if( ! this->discoverWidthHeight() )
        return 1;

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

    while( ! c0.toMat(frame_0,ts0) );  //-- Returns false until got first image-
    while( ! c1.toMat(frame_1,ts1) );  //-- Returns false until got first image-

#ifdef TIMING
    timeval timestampStructure;
    gettimeofday(&timestampStructure,NULL);
    double last = double(timestampStructure.tv_sec + timestampStructure.tv_usec*1e-6);
    double frameCounter = 0;
#endif  // TIMING

    while(TRUE){

        // conversion
        c0.toMat(frame_0,ts0);
        c1.toMat(frame_1,ts1);

        // check if timestamps are close enough
        if( fabs(ts0-ts1) > (0.020) )
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
            c0.stop();
            c1.stop();
            cv::destroyAllWindows();
            std::cout << "[INFO] Quitting program!" << std::endl;
            break;
        }

#ifdef TIMING
        gettimeofday(&timestampStructure,NULL);
        double now = double(timestampStructure.tv_sec + timestampStructure.tv_usec*1e-6);
        if( (now - last) > 1 ) {  //-- every second
            printf("Got %f synced frames in past second.\n",frameCounter);
            last = now;
            frameCounter = 0;
        } else {
            frameCounter++;
        }
#endif  // TIMING

    }

    return 0;
}

}  // namespace scr

