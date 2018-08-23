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
	img_t img = { 0 };

	if (!retrieve_selected_area(&img.area))
		return EXIT_FAILURE;
	img.data = malloc(IMG_MAX_SIZE);
	take_screenshot(&img);
	upload_screenshot(&img);
	free(img.data);
	return EXIT_SUCCESS;
}