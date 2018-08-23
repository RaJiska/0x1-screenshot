/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: take_screenshot.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Wed Aug 22nd 18:29:47 2018
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "nnullptr-screenshot.h"

#ifdef linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static img_t *G_IMG;
static unsigned long long int G_IMGOFF = 0;

static void png_write_callback(void *context, void *data, int size)
{
	memcpy(G_IMG->data + G_IMG->size, data, size);
	G_IMG->size += size;
}

bool take_screenshot(img_t *img)
{
	Display *display = XOpenDisplay(NULL);
	Screen *screen;
	Window window;
	XImage *ximg;
	uint8_t *buf;
	uint8_t *buf_bak;
	uint32_t pixel;

	if (!display)
		return false;
	screen = XDefaultScreenOfDisplay(display);
	window = DefaultRootWindow(display);
	ximg = XGetImage(display, window, img->area.x, img->area.y, img->area.w, img->area.h, AllPlanes, XYPixmap);
	if (!(buf = buf_bak = malloc(img->area.w * img->area.h * 3)))
		return false;
	for (unsigned int y = 0; y < img->area.h; ++y)
	{
		for (unsigned int x = 0; x < img->area.w; ++x)
		{
			pixel = XGetPixel(ximg, x, y);
			(*buf++) = pixel >> 16;
			(*buf++) = pixel >> 8;
			(*buf++) = pixel;
		}
	}
	XDestroyImage(ximg);
	G_IMG = img;
	stbi_write_png_to_func(png_write_callback, NULL, img->area.w, img->area.h, 3, buf_bak, img->area.w * 3);
}
#endif /* linux */