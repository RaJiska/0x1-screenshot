/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: nnullptr-screenshot.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Tue Aug 21st 16:31:52 2018
 */

#ifndef NNULLPTR_SCREENSHOT_H_
#define NNULLPTR_SCREENSHOT_H_

#include <stdbool.h>

#define WEBSITE_URL "http://0x1.rajiska.fr"
#define IMG_MAX_SIZE 1000 * 1000 * 10 /* 10 MB */

typedef struct
{
	int x;
	int w;
	int y;
	int h;
} area_coords_t;

typedef struct
{
	void *data;
	unsigned long long int size;
	area_coords_t area;
} img_t;

bool retrieve_selected_area(area_coords_t *area);
bool take_screenshot(img_t *img);
bool upload_screenshot(const img_t *img);

#endif /* NNULLPTR_SCREENSHOT_H_ */