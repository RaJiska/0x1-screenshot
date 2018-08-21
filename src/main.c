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

	if (!retrieve_selected_area(&coords))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}