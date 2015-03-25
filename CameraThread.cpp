// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "CameraThread.hpp"

namespace scr
{

CameraThread::CameraThread(const char *name, int w, int h, int fps) {
    c = new Camera(name, w, h, fps);
    m = cv::Mat::zeros(h, w, CV_8UC3);
    ts = 0;
}

CameraThread::~CameraThread() {
            delete c;
}

void CameraThread::run() {
    while( ! this->isStopping() ) {
        c->Get();
    }
}

void CameraThread::toMat(cv::Mat& im, double& ts) {
  c->toMat(im,ts);
}

}  // namespace scr
