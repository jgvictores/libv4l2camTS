#include "CameraThread.hpp"

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
        if( ! c->Update() )
            continue;
    }
}

void CameraThread::toMat(cv::Mat& im, double& ts) {
  c->toMat(im,ts);
}
