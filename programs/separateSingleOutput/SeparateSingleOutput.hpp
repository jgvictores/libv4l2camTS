// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* Copyright (C) 2015 Juan G Victores */

#ifndef __SEPARATE_SINGLE_OUTPUT__HPP__
#define __SEPARATE_SINGLE_OUTPUT__HPP__

#include <cstdio>
#include <unistd.h>

#include "opencv/highgui.h"

namespace scr
{

class SeparateSingleOutput {

    public:
        int main(int argc, char *argv[]);

    private:
        int width, height;
        double fps;
};

}  // namespace scr

#endif  // __SEPARATE_SINGLE_OUTPUT__HPP__

