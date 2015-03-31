// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* Copyright (C) 2015 Juan G Victores & Santiago Morante */

#ifndef __SYNCED_CAMERA_RECORDER_SINLGE_OUTPUT__HPP__
#define __SYNCED_CAMERA_RECORDER_SINLGE_OUTPUT__HPP__

#include <cstdio>
#include <unistd.h>

#include <sys/time.h>

#include "CameraThread.hpp"
#include "ImageConverter.hpp"

#include "opencv/highgui.h"

#define SOURCE_0 0
#define SOURCE_1 1
#define FPS 20
#define RECORD_SECONDS 600

#define PRINTF_FPS


namespace scr
{

class SyncedCameraRecorderSingleOutput {

    public:
        bool discoverWidthHeight();
        int main();

    private:
        int width_0, width_1, height_0, height_1;
};

}  // namespace scr

#endif  // __SYNCED_CAMERA_RECORDER_SINLGE_OUTPUT__HPP__

