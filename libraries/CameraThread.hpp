// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* Copyright (C) 2015 Juan G Victores */

#ifndef __CAMERA_THREAD__HPP__
#define __CAMERA_THREAD__HPP__

#include "Camera.hpp"

#include <yarp/os/Thread.h>
#include <yarp/os/Semaphore.h>

#include <unistd.h>  //-- usleep

namespace scr
{

class CameraThread : public yarp::os::Thread {
    public:
        CameraThread(const char *n, int w, int h, int f)  {
            c = new Camera(n,w,h,f);
            name = n;
            width = w;
            height = h;
            raw_frame = (unsigned char *)malloc(h*w*4);
            firstFrame = false;
        }
        virtual void run();
        virtual void onStop();
        virtual void threadRelease();

        void getRawData(unsigned char *data, double& timestamp);
        bool gotFirstFrame();

    private:
        Camera* c;
        unsigned char *raw_frame;
        double ts;
        yarp::os::Semaphore ready;
        int width,height;
        bool firstFrame;
        std::string name;
};

}  // namespace scr

#endif  // __CAMERA_THREAD__HPP__
