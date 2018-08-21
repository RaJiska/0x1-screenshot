/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: retrieve_selected_area.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Tue Aug 21st 17:10:46 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include "nnullptr-screenshot.h"

#ifdef linux
static inline void draw_rectangle(Display *display, Window window, GC gc, const area_coords_t *area)
{
	area_coords_t new;

	if (area->w > 0 && area->h > 0)
		XDrawRectangle(display, window, gc, area->x, area->y, area->w, area->h);
	else
	{
		memcpy(&new, area, sizeof(area_coords_t));
		if (area->w < 0)
		{
			new.x += area->w;
			new.w = -area->w;
		}
		if (area->h < 0)
		{
			new.y += area->h;
			new.h = -area->h;
		}
		XDrawRectangle(display, window, gc, new.x, new.y, new.w, new.h);
	}
}

static inline void selection_loop(Display *display, Window window, GC gc, area_coords_t *area)
{
	XEvent ev;
	bool done = false;
	bool mouse_pressed = false;

	while (!done)
	{
		XNextEvent(display, &ev);
		switch (ev.type)
		{
		case MotionNotify:
			if (mouse_pressed)
			{
				draw_rectangle(display, window, gc, area);
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
		}
	}
}


bool retrieve_selected_area(area_coords_t *area)
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
	XFreeGC(display, gc);
	XCloseDisplay(display);
}
#endif /* linux */