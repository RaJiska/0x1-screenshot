/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: retrieve_selected_area.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Tue Aug 21st 17:10:46 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nnullptr-screenshot.h"
#include "sshot.h"

#ifdef linux
#include <X11/Xlib.h>
#include <X11/cursorfont.h>

static inline const area_coords_t *retrieve_real_coords(const area_coords_t *area)
{
	static area_coords_t real;

	if (area->w > 0 && area->h > 0)
		return area;
	memcpy(&real, area, sizeof(area_coords_t));
	if (area->w < 0)
	{
		real.x += area->w;
		real.w = -area->w;
	}
	if (area->h < 0)
	{
		real.y += area->h;
		real.h = -area->h;
	}
	return &real;
}

static inline void draw_rectangle(Display *display, Window window, GC gc, const area_coords_t *area)
{
	static area_coords_t old = { 0 };

	XDrawRectangle(display, window, gc, old.x, old.y, old.w, old.h);
	XDrawRectangle(display, window, gc, area->x, area->y, area->w, area->h);
	memcpy(&old, area, sizeof(area_coords_t));
}

static inline void selection_loop(Display *display, Window window, GC gc, area_coords_t *area)
{
	XEvent ev;
	bool done = false;
	bool mouse_pressed = false;
	const area_coords_t *real_coords = area;

	while (!done)
	{
		XNextEvent(display, &ev);
		switch (ev.type)
		{
		case MotionNotify:
			if (mouse_pressed)
			{
				draw_rectangle(display, window, gc, retrieve_real_coords(area));
				area->w = ev.xmotion.x - area->x;
				area->h = ev.xmotion.y - area->y;
			}
			break;
		case ButtonPress:
			if (!mouse_pressed) {
				mouse_pressed = true;
				area->x = ev.xbutton.x;
				area->y = ev.xbutton.y;
			}
			break;
		case ButtonRelease:
			done = true;
			break;
		case KeyPress:
			if (ev.xkey.keycode == 0x09)
				done = true;
			break;
		}
	}
}


bool sshot_select_area(area_coords_t *area)
{
	Display *display = XOpenDisplay(NULL);
	Screen *screen;
	XGCValues gcval;
	Window root_window;
	Cursor cursor;
	GC gc;

	if (!display)
		return false;
	screen = ScreenOfDisplay(display, DefaultScreen(display));
	gcval.foreground = XWhitePixel(display, 0);
	gcval.function = GXxor;
	gcval.background = XBlackPixel(display, 0);
	gcval.plane_mask = gcval.background ^ gcval.foreground;
	gcval.subwindow_mode = IncludeInferiors;
	root_window = RootWindow(display, XScreenNumberOfScreen(screen));
	cursor = XCreateFontCursor(display, XC_crosshair);
	if ((XGrabPointer(display, root_window, False,
		ButtonMotionMask | ButtonPressMask | ButtonReleaseMask,
		GrabModeAsync, GrabModeAsync, root_window, cursor, CurrentTime) != GrabSuccess))
		return false;
	if ((XGrabKeyboard(display, root_window, False, GrabModeAsync, GrabModeAsync, CurrentTime) != GrabSuccess))
		return false;
	gc = XCreateGC(display, root_window, GCFunction | GCForeground | GCBackground | GCSubwindowMode, &gcval);
	memset(area, 0, sizeof(area_coords_t));
	selection_loop(display, root_window, gc, area);
	draw_rectangle(display, root_window, gc, &(area_coords_t) { 0 });
	XFreeGC(display, gc);
	XCloseDisplay(display);
	memcpy(area, retrieve_real_coords(area), sizeof(area_coords_t));
	return true;
}
#endif /* linux */