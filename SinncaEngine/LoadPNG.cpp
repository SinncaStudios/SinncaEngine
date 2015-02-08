//
//  LoadPNG.c
//  SinncaEngine
//
//  Created by Ryan Oldis on 6/20/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Image.h"
#include <png.h>


namespace sinnca
{
	int image::loadPNG(std::string path)
	{
		png_byte header[8];
		
		
		FILE* fp = fopen(path.c_str(), "rb");
		if (!fp)
		{
			perror(path.c_str());
			return -1;
		}
		
		fread(header, 1, 8, fp);
		if (png_sig_cmp(header, 0, 8))
		{
			fprintf(stderr, "Error: Hey! %s isn't a PNG file! What are you trying to pull here?\n", path.c_str());
			fclose(fp);
			return -1;
		}
		
		png_structp snPng = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!snPng)
		{
			fprintf(stderr, "Error: png_create_read_struct failed...\n");
			fclose(fp);
			return -1;
		}
		png_infop snInfop = png_create_info_struct(snPng);
		if (!snInfop)
		{
			fprintf(stderr, "Error: png_create_info_struct failed...\n");
			png_destroy_read_struct(&snPng, (png_infopp)NULL, (png_infopp)NULL);
			fclose(fp);
			return -1;
		}
		png_infop snEndp = png_create_info_struct(snPng);
		if (!snEndp)
		{
			fprintf(stderr, "Error: png_create_info_struct failed... (end part)\n");
			png_destroy_read_struct(&snPng, &snInfop, (png_infopp)NULL);
			fclose(fp);
			return -1;
		}
		
		if (setjmp(png_jmpbuf(snPng)))
		{
			fprintf(stderr, "Error: libpng error\n");
			png_destroy_read_struct(&snPng, &snInfop, &snEndp);
			fclose(fp);
			return -1;
		}
		
		// Now the fun part!
		png_init_io(snPng, fp);
		png_set_sig_bytes(snPng, 8);
		png_read_info(snPng, snInfop);
		
		// get file info
		png_uint_32 tempW, tempH;
		int tempCol;
		png_get_IHDR(snPng, snInfop, &tempW, &tempH, &bitDepth, &tempCol, NULL, NULL, NULL);
		w = tempW;
		h = tempH;
		switch (tempCol)
		{
			case PNG_COLOR_TYPE_RGB:
				colorType = GL_RGB;
				break;
				
			case PNG_COLOR_TYPE_RGB_ALPHA:
				colorType = GL_RGBA;
				break;
				
			case PNG_COLOR_TYPE_GRAY:
				colorType = GL_LUMINANCE;
				break;
			case PNG_COLOR_TYPE_GRAY_ALPHA:
				colorType = GL_LUMINANCE_ALPHA;
				break;
		}
		
		png_read_update_info(snPng, snInfop);
		int rbytes = png_get_rowbytes(snPng, snInfop);
		rbytes += 3 - ((rbytes-1) % 4);
		
		png_byte* snPNGdata;
		snPNGdata = (png_byte*)Heap->allocate((unsigned int)rbytes * tempH * sizeof(png_byte) + 15, __alignof(png_byte));
		
		if (snPNGdata == NULL)
		{
			fprintf(stderr, "Error: couldn't allocate memory\n");
			png_destroy_read_struct(&snPng, &snInfop, &snEndp);
			fclose(fp);
			return -1;
		}
		
		png_bytep* rowPointers = (png_bytep*)Heap->allocate((unsigned int)tempH * sizeof(png_bytep), __alignof(png_bytep));
		if (rowPointers == NULL)
		{
			fprintf(stderr, "Error: couldn't allocate row pointers\n");
			png_destroy_read_struct(&snPng, &snInfop, &snEndp);
			fclose(fp);
			return -1;
		}
		
		for (int i = 0; i < tempH; i++)
		{
			rowPointers[tempH - 1 - i] = snPNGdata + i * rbytes;
		}
		
		png_read_image(snPng, rowPointers);
		
		glGenTextures(1, &data);
		glBindTexture(GL_TEXTURE_2D, data);
		glTexImage2D(GL_TEXTURE_2D, 0, colorType, tempW, tempH, 0, colorType, GL_UNSIGNED_BYTE, snPNGdata);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tb);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tb);
		
		//clean up!
		png_destroy_read_struct(&snPng, &snInfop, &snEndp);
		Heap->deallocate(snPNGdata);
		Heap->deallocate(rowPointers);
		fclose(fp);
		
		return 0;
	}
	
}