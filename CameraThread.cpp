// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "CameraThread.hpp"

namespace scr
{

void CameraThread::run() {
    while( ! this->isStopping() ) {
        ready.wait();
        int ret = c->getRawData(raw_frame,ts);
        ready.post();
        if(!firstFrame && ret) firstFrame = true;
    }
}

void CameraThread::getRawData(unsigned char *data, double& timestamp) {
    ready.wait();
    timestamp = ts;
    memcpy(data, raw_frame, height*width*4);
    ready.post();
}

}  // namespace scr
