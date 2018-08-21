/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: nnullptr-screenshot.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Tue Aug 21st 16:31:52 2018
 */

#ifndef NNULLPTR_SCREENSHOT_H_
#define NNULLPTR_SCREENSHOT_H_

#include <stdbool.h>

typedef struct
{
	int x;
	int w;
	int y;
	int h;
} area_coords_t;

bool retrieve_selected_area(area_coords_t *area);

#endif /* NNULLPTR_SCREENSHOT_H_ */