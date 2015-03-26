// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "CameraThread.hpp"

namespace scr
{

void CameraThread::run() {
    while( ! this->isStopping() ) {
        ready.wait();
        int ret = c->getRawData(raw_frame,ts);
        ready.post();
        if(!gotFirstFrame && ret) gotFirstFrame = true;
    }
}

bool CameraThread::getRawData(unsigned char *data, double& timestamp) {
    if (!gotFirstFrame) return false;
    ready.wait();
    timestamp = ts;
    memcpy(data, raw_frame, height*width*4);
    ready.post();
    return true;
}

}  // namespace scr
