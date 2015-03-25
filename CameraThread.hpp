// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __CAMERA_THREAD__HPP__
#define __CAMERA_THREAD__HPP__

#include "Camera.hpp"

#include <yarp/os/Thread.h>

#include <unistd.h>  //-- usleep

namespace scr
{

class CameraThread : public yarp::os::Thread {
    public:
        CameraThread(const char *name, int w, int h, int fps=30);
        ~CameraThread();
        void run();

        void toMat(cv::Mat& im, double& ts);

    private:
        Camera* c;
        cv::Mat m;
        double ts;
};

}  // namespace scr

#endif  // __CAMERA_THREAD__HPP__
