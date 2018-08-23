/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: main.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Tue Aug 21st 16:10:35 2018
 */

#include <stdlib.h>
#include "nnullptr-screenshot.h"

int main(int argc, char * const *argv)
{
	area_coords_t coords;
	void *img;

	if (!retrieve_selected_area(&coords))
		return EXIT_FAILURE;
	img = malloc(IMG_MAX_SIZE);
	take_screenshot(&coords, img);
	free(img);
	return EXIT_SUCCESS;
}