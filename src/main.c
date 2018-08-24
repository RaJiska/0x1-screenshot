/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: main.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Tue Aug 21st 16:10:35 2018
 */

#include <stdlib.h>
#include "nnullptr-screenshot.h"
#include "sshot.h"

int main(int argc, char * const *argv)
{
	img_t img = { 0 };

	if (!sshot_select_area(&img.area))
		return EXIT_FAILURE;
	img.data = malloc(SSHOT_MAX_SIZE);
	sshot_capture(&img);
	sshot_upload(&img);
	free(img.data);
	return EXIT_SUCCESS;
}