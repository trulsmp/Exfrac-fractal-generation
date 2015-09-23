//
//  png.c
//  HPC
//
//  Created by Truls Mørk Pettersen on 21/09/2015.
//  Copyright (c) 2015 Truls Mørk Pettersen. All rights reserved.
//

#include "png.h"

int save_png_to_file(bitmap_t *bitmap, const char *path, int resolution)
{
    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    int x, y;
    png_byte ** row_pointers = NULL;
    
    int pixel_size = 3;
    int depth = 8;
    
    fp = fopen (path, "wb");
    if (! fp) {
        return 0;
    }
    
    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    info_ptr = png_create_info_struct (png_ptr);
    
    if (png_ptr == NULL) {
        fclose (fp);;
    }
    
    if (info_ptr == NULL) {
        png_destroy_write_struct (&png_ptr, &info_ptr);
        fclose (fp);
    }
    
    
    // Set the config values, found from documentation
    
    png_set_IHDR (png_ptr,
                  info_ptr,
                  bitmap->width,
                  bitmap->height,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);
    
    // Intialize the rows of the png
    
    row_pointers = png_malloc (png_ptr, bitmap->height * sizeof (png_byte *));
    for (y = 0; y < bitmap->height; ++y) {
        png_byte *row = png_malloc (png_ptr, sizeof (uint8_t) * resolution * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < resolution; ++x) {
            pixel_t * pixel = (*bitmap).pixels + (*bitmap).width*y+x;
            *row++ = pixel->red;
            *row++ = pixel->green;
            *row++ = pixel->blue;
        }
    }
    
    // Write png data to file
    
    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    
    //Free the memory used by png_ptr
    for (y = 0; y < bitmap->height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);
    
    return 1;
}





