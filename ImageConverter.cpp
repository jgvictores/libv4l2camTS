// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * 2015 - Juan G Victores
 *
 * Lightly based on https://code.google.com/p/libv4l2cam/
 * Copyright (C) 2009 Giacomo Spigler
 * 2013 - George Jordanov - improve in performance for HSV conversion and improvements
 * CopyPolicy: Released under the terms of the GNU GPL v3.0.
 */

# include "ImageConverter.hpp"

namespace scr
{

ImageConverter::ImageConverter( int& w, int& h )
{
    height = h;
    w2 = w/2;

#ifdef USE_LOOKUP
    genYUVtoRGBLookups();
#endif
}

#ifdef USE_LOOKUP
void ImageConverter::genYUVtoRGBLookups()
{
    int iyv, iyu, iy2v, iy2u;
    int i, j;
    for(i=0; i<256; i++){
        for(j=0; j<256; j++){
                iyv= i + (1.370705 * (j-128));  //Red
                iyu= i + (1.732446 * (j-128)); //Blue
                iy2v= (i/2) - (0.698001 * (j-128));//Green 1/2
                iy2u= (i/2) - (0.337633 * (j-128));//Green 1/2

                if(iyv > 255) iyv = 255;
                //if(iy2v + iy2u > 255) { iy2v = 127; iy2u = 128;}
                if(iyu > 255) iyu = 255;
                if(iyv < 0) iyv = 0;
                //if(iy2v + iy2u < 0) { iy2v = 0; iy2u = 0;}
                if(iyu < 0) iyu = 0;
                
                yv[i][j] = (unsigned char) iyv;
                yu[i][j] = (unsigned char) iyu;
                //Int
                y2v[i][j] = iy2v;
                y2u[i][j] = iy2u;
        }
    }
}
#endif

void ImageConverter::toIplImage(unsigned char *data, IplImage *l) {
  unsigned char *l_=(unsigned char *)l->imageData;


  for(int x=0; x<w2; x++) {
    for(int y=0; y<height; y++) {
      int y0, y1, u, v; //y0 u y1 v

      int i=(y*w2+x)*4;
      y0=data[i];
      u=data[i+1];
      y1=data[i+2];
      v=data[i+3];

#ifndef USE_LOOKUP
      int r, g, b;

      r = y0 + (1.370705 * (v-128));
      g = y0 - (0.698001 * (v-128)) - (0.337633 * (u-128));
      b = y0 + (1.732446 * (u-128));

      if(r > 255) r = 255;
      if(g > 255) g = 255;
      if(b > 255) b = 255;
      if(r < 0) r = 0;
      if(g < 0) g = 0;
      if(b < 0) b = 0;

      i=(y*l->width+2*x)*3;
      l_[i] = (unsigned char)(b); //B
      l_[i+1] = (unsigned char)(g); //G
      l_[i+2] = (unsigned char)(r); //R

      r = y1 + (1.370705 * (v-128));
      g = y1 - (0.698001 * (v-128)) - (0.337633 * (u-128));
      b = y1 + (1.732446 * (u-128));

      if(r > 255) r = 255;
      if(g > 255) g = 255;
      if(b > 255) b = 255;
      if(r < 0) r = 0;
      if(g < 0) g = 0;
      if(b < 0) b = 0;

      l_[i+3] = (unsigned char)(b); //B
      l_[i+4] = (unsigned char)(g); //G
      l_[i+5] = (unsigned char)(r); //R
#else
      int g;
      i=(y*l->width+2*x)*3;
      
      g=y2u[y0][u] + y2v[y0][v];
      if(g>255){g=255;}
      if(g<0){g=0;}
      l_[i] = yu[y0][u];
      l_[i+1] = g;
      l_[i+2] = yv[y0][v];
      
      g=y2u[y1][u] + y2v[y1][v];
      if(g>255){g=255;}
      if(g<0){g=0;}
      l_[i+3] = yu[y1][u];
      l_[i+4] = g;
      l_[i+5] = yv[y1][v];
#endif
    }
  }

}

void ImageConverter::toGrayScaleIplImage(unsigned char *data, IplImage *l)
{
    unsigned char *l_=(unsigned char *)l->imageData;
    
    for (int x = 0; x < w2; x++) {
        for (int y = 0; y < height; y++) {
            int y0, y1;
            
            int i = (y * w2 + x)*4;
            y0 = data[i];
            y1 = data[i + 2];

            i = (y * l->width + 2 * x)*1;
            l_[i] = (unsigned char) (y0);
            l_[i + 1] = (unsigned char) (y1);
        }
    }
}

void ImageConverter::toMat(unsigned char *data, cv::Mat& m) {

    unsigned char *m_ = (unsigned char *)(m.data);

    for(int x=0; x<w2; x++) {
        for(int y=0; y<height; y++) {
            int y0, y1, u, v; //y0 u y1 v

            int i=(y*w2+x)*4;
            y0=data[i];
            u=data[i+1];
            y1=data[i+2];
            v=data[i+3];
            
#ifndef USE_LOOKUP
            int r, g, b;

            r = y0 + (1.370705 * (v-128));
            g = y0 - (0.698001 * (v-128)) - (0.337633 * (u-128));
            b = y0 + (1.732446 * (u-128));

            if(r > 255) r = 255;
            if(g > 255) g = 255;
            if(b > 255) b = 255;
            if(r < 0) r = 0;
            if(g < 0) g = 0;
            if(b < 0) b = 0;

            i = y*m.cols*m.channels() + x*2*m.channels();
            m_[i] = (unsigned char)(b); //B
            m_[i+1] = (unsigned char)(g); //G
            m_[i+2] = (unsigned char)(r); //R

            r = y1 + (1.370705 * (v-128));
            g = y1 - (0.698001 * (v-128)) - (0.337633 * (u-128));
            b = y1 + (1.732446 * (u-128));

            if(r > 255) r = 255;
            if(g > 255) g = 255;
            if(b > 255) b = 255;
            if(r < 0) r = 0;
            if(g < 0) g = 0;
            if(b < 0) b = 0;

            m_[i+3] = (unsigned char)(b); //B
            m_[i+4] = (unsigned char)(g); //G
            m_[i+5] = (unsigned char)(r); //R
#else
            int g;

            i = y*m.cols*m.channels() + x*2*m.channels();

            g=y2u[y0][u] + y2v[y0][v];
            if(g>255){g=255;}
            if(g<0){g=0;}
            m_[i] = yu[y0][u];
            m_[i+1] = (unsigned char)g;
            m_[i+2] = yv[y0][v];

            g=y2u[y1][u] + y2v[y1][v];
            if(g>255){g=255;}
            if(g<0){g=0;}
            m_[i+3] = yu[y1][u];
            m_[i+4] = g;
            m_[i+5] = yv[y1][v];
#endif
        }
    }

}

void ImageConverter::toGrayScaleMat(unsigned char *data, cv::Mat& m)
{   
    unsigned char *m_ = (unsigned char *)(m.data);
    
    for (int x = 0; x < w2; x++) {
        for (int y = 0; y < height; y++) {
            int y0, y1;

            int i = (y * w2 + x)*4;
            y0 = data[i];
            y1 = data[i + 2];
            
            i = y*m.cols*m.channels() + x*2*m.channels(); 
            m_[i + 0] = (unsigned char) (y0);
            m_[i + 1] = (unsigned char) (y1);
            
            //More clear in logic but slower solution
            //m.at<uchar>(y, (2*x)) = (unsigned char) (y0);
            //m.at<uchar>(y, (2*x)+1) = (unsigned char) (y1);
        }
    }
}

}  // namespace scr
