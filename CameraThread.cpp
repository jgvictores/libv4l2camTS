// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "CameraThread.hpp"

namespace scr
{

CameraThread::CameraThread(const char *name, int w, int h, int fps) {
    c = new Camera(name, w, h, fps);
}

CameraThread::~CameraThread() {
            delete c;
}

void CameraThread::run() {
    while( ! this->isStopping() ) {
        c->Get();
    }
}

bool CameraThread::getMat(cv::Mat& im, double& ts) {
  //return c->getMat(im,ts);
    return true;
}

}  // namespace scr
