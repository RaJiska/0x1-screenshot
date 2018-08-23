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

static void *G_IMGOUT;
static unsigned long long int G_IMGOFF = 0;

static void png_write_callback(void *context, void *data, int size)
{
	memcpy(G_IMGOUT + G_IMGOFF, data, size);
	G_IMGOFF += size;
}

bool take_screenshot(const area_coords_t *area, void *img_out)
{
	Display *display = XOpenDisplay(NULL);
	Screen *screen;
	Window window;
	XImage *img;
	uint8_t *buf;
	uint8_t *buf_bak;
	uint32_t pixel;

	if (!display)
		return false;
	screen = XDefaultScreenOfDisplay(display);
	window = DefaultRootWindow(display);
	img = XGetImage(display, window, area->x, area->y, area->w, area->h, AllPlanes, XYPixmap);
	if (!(buf = buf_bak = malloc(area->w * area->h * 3)))
		return false;
	for (unsigned int y = 0; y < area->h; ++y)
	{
		for (unsigned int x = 0; x < area->w; ++x)
		{
			pixel = XGetPixel(img, x, y);
			(*buf++) = pixel >> 16;
			(*buf++) = pixel >> 8;
			(*buf++) = pixel;
		}
	}
	XDestroyImage(img);
	G_IMGOUT = img_out;
	stbi_write_png_to_func(png_write_callback, NULL, area->w, area->h, 3, buf_bak, area->w * 3);
}
#endif /* linux */