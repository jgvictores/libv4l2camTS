/*
 * Copyright (C) 2009 Giacomo Spigler
 * 2015 - Juan G Victores - enable timestamp on toMat
 * CopyPolicy: Released under the terms of the GNU GPL v3.0.
 */

#include <stdio.h>
#include "libcam.h"

using namespace std;


int main() {

    int ROWS_1 = 480;
    int COLS_1 = 640;

    Camera c0("/dev/video0", COLS_1, ROWS_1, 14);  //-- optinal fps at end, set 14 for minoru
    Camera c1("/dev/video1", COLS_1, ROWS_1, 14);  //-- optinal fps at end, set 14 for minoru

    if( ! c0.Update() ) {
        printf("[error] update timeout c0.\n");
        return 1;
    }
    if( ! c1.Update() ) {
        printf("[error] update timeout c1.\n");
        return 1;
    }

    cv::Mat m0 = cv::Mat::zeros(ROWS_1, COLS_1, CV_8UC3);
    double ts0;
    c0.toMat(m0,ts0);

    cv::Mat m1 = cv::Mat::zeros(ROWS_1, COLS_1, CV_8UC3);
    double ts1;
    c1.toMat(m1,ts1);


    printf("c0 [%f] %d %d\n",  ts0, m0.rows, m0.cols );
    printf("c1 [%f] %d %d\n",  ts1, m1.rows, m1.cols );

    return 0;
}



