// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * 2015 - Juan G Victores - enable timestamp on toMat, threads, semaphores, namespace...
 *
 * Lightly based on https://code.google.com/p/libv4l2cam/
 * Copyright (C) 2009 Giacomo Spigler
 * 2013 - George Jordanov - improve in performance for HSV conversion and improvements
 * CopyPolicy: Released under the terms of the GNU GPL v3.0.
 */

#ifndef __CAMERA__HPP__
#define __CAMERA__HPP__

#define USE_OPENCV
#define USE_LOOKUP

#include <sys/time.h>

#ifdef USE_OPENCV
#include <cv.h>
#include "opencv2/core/core.hpp"
#endif

struct buffer {
        void *                  start;
        size_t                  length;
};

typedef enum {
	IO_METHOD_READ,
	IO_METHOD_MMAP,
	IO_METHOD_USERPTR
} io_method;

namespace scr
{

class Camera {
private:
    timeval timestampStructure;

    void Open();
    void Close();

    void Init();
    void UnInit();

    void Start();
    void Stop();

    void init_userp(unsigned int buffer_size);
    void init_mmap();
    void init_read(unsigned int buffer_size);

    bool initialised;

public:
    const char *name;  //dev_name
    int width;
    int height;
    int fps;

    io_method io;
    int fd;
    buffer *buffers;
    int n_buffers;

    int mb, Mb, db, mc, Mc, dc, ms, Ms, ds, mh, Mh, dh, msh, Msh, dsh;
    bool ha;

    //Camera();
    Camera(const char *name, int w, int h, int fps=30);
    void  StartCamera(const char *name, int w, int h, int fps=30);
    ~Camera();

    bool getRawData(unsigned char *data, double& timestamp);

    void StopCam();

    int minBrightness();
    int maxBrightness();
    int defaultBrightness();
    int minContrast();
    int maxContrast();
    int defaultContrast();
    int minSaturation();
    int maxSaturation();
    int defaultSaturation();
    int minHue();
    int maxHue();
    int defaultHue();
    bool isHueAuto();
    int minSharpness();
    int maxSharpness();
    int defaultSharpness();

    int setBrightness(int v);
    int setContrast(int v);
    int setSaturation(int v);
    int setHue(int v);
    int setHueAuto(bool v);
    int setSharpness(int v);

};

}  // namespace scr

#endif  // __CAMERA__HPP__
