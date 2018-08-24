/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: sshot.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 24th 10:43:13 2018
 */

#ifndef SSHOT_H_
#define SSHOT_H_

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define SSHOT_MAX_SIZE 1000 * 1000 * 10 /* 10 MB */

typedef struct
{
	int x;
	int w;
	int y;
	int h;
} area_coords_t;

typedef struct
{
	bool builtin;
	union {
		struct {
			void *data;
			unsigned long long int size;
			area_coords_t area;
		};
		char file_name[4096];
	};
} img_t;

bool sshot_select_area(area_coords_t *area);
bool sshot_capture(img_t *img);
bool sshot_capture_alternate(img_t *img, const char *tool);
bool sshot_upload(const img_t *img);

#endif /* SSHOT_H_ */