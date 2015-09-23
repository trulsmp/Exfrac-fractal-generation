//
//  png.h
//  HPC
//
//  Created by Truls Mørk Pettersen on 21/09/2015.
//  Copyright (c) 2015 Truls Mørk Pettersen. All rights reserved.
//


#ifndef __HPC__png__
#define __HPC__png__

#include "mandelbrot.h"

int save_png_to_file(bitmap_t *bitmap, const char *path, int resolution);

#endif /* defined(__HPC__png__) */
