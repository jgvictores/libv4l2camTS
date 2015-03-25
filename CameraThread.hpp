// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "Camera.hpp"

#include <yarp/os/Thread.h>
#include <yarp/os/Semaphore.h>

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
