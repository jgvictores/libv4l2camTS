// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "SeparateSingleOutput.hpp"

namespace scr
{

int SeparateSingleOutput::main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr,"[ERROR] Usage: separateSingleOutput <filename>.\n");
        return 1;
    }
    cv::VideoCapture capture_single(argv[1]);

    if(!capture_single.isOpened() )
    {
        fprintf(stderr,"[ERROR] Cannot extract images from video.\n");
        return false;
    }

    // Get the properties from the camera
    width = capture_single.get(CV_CAP_PROP_FRAME_WIDTH);
    height = capture_single.get(CV_CAP_PROP_FRAME_HEIGHT);
    fps = capture_single.get(CV_CAP_PROP_FPS);

    // print camera frame size
    printf("Stream properties:\n");
    printf("width = %d\n",width);
    printf("height = %d\n",height);

    std::string FILENAME_VIDEO_0 = "feed_0.avi";
    std::string FILENAME_VIDEO_1 = "feed_1.avi";

    // Create the video writers
    cv::VideoWriter video_0;
    video_0.open(FILENAME_VIDEO_0, CV_FOURCC('X','V','I','D'), fps, cv::Size(width/2,height) );
    if (!video_0.isOpened()){
        fprintf(stderr,"Could not open the output video for write (maybe missing codec): %s\n",FILENAME_VIDEO_0.c_str());
        return 1;
    }
    cv::VideoWriter video_1;
    video_1.open(FILENAME_VIDEO_0, CV_FOURCC('X','V','I','D'), fps, cv::Size(width/2,height) );
    if (!video_1.isOpened()){
        fprintf(stderr,"Could not open the output video for write (maybe missing codec): %s\n",FILENAME_VIDEO_1.c_str());
        return 1;
    }

    cv::Mat frame_single;
    while( capture_single.read(frame_single) )
    {
        cv::Mat left(frame_single, cv::Rect(0, 0, width/2, height)); // Copy constructor
        cv::Mat right(frame_single, cv::Rect(width/2, 0, width/2, height)); // Copy constructor

        // Save frame to video
        video_0.write(left);
        video_1.write(right);

    }

    printf("[INFO] Releasing resources!\n");
    video_0.release();
    video_1.release();
    printf("[INFO] Quitting program!\n");

    return 0;
}

}  // namespace scr

