// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * 2015 - Juan G Victores
 *
 * Lightly based on https://code.google.com/p/libv4l2cam/
 * Copyright (C) 2009 Giacomo Spigler
 * 2013 - George Jordanov - improve in performance for HSV conversion and improvements
 * CopyPolicy: Released under the terms of the GNU GPL v3.0.
 */

#ifndef __IMAGE_CONVERTER__HPP__
#define __IMAGE_CONVERTER__HPP__

#define USE_LOOKUP

#include <cv.h>
#include "opencv2/core/core.hpp"

namespace scr
{

class ImageConverter {

    public:
        ImageConverter( int& width, int& height );
        void toIplImage( unsigned char *data, IplImage *im);
        void toGrayScaleIplImage( unsigned char *data, IplImage *im);
        void toGrayScaleMat( unsigned char *data, cv::Mat& im);
        void toMat( unsigned char *data, cv::Mat& im);

    private:
        int height;
        int w2;

#ifdef USE_LOOKUP
        void genYUVtoRGBLookups();
        unsigned char yv[256][256];
        unsigned char yu[256][256];
        int y2v[256][256];
        int y2u[256][256];
#endif

};

}  // namespace scr

#endif  // __IMAGE_CONVERTER__HPP__
