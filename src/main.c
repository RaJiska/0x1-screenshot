/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: main.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Tue Aug 21st 16:10:35 2018
 */

#include <stdlib.h>
#include <string.h>
#include "nnullptr-screenshot.h"
#include "cfg.h"
#include "sshot.h"
#include "utils.h"

int main(int argc, char * const *argv)
{
	img_t img = { 0 };
	const char *tool;

	if (!cfg_init())
		return EXIT_FAILURE;
	tool = cfg_key_get_value(CFG_KEY_SCREENSHOTTOOL);
#ifdef linux
	if (!strcmp(tool, "builtin")) {
#endif /* linux */
		if (!sshot_select_area(&img.area))
			return EXIT_FAILURE;
		if (!img.area.w && !img.area.h)
			return EXIT_SUCCESS;
		if (!(img.data = malloc(SSHOT_MAX_SIZE)))
			return FNC_PERROR_RET(int, EXIT_FAILURE, "Could not allocate memory");
		if (!sshot_capture(&img))
			return EXIT_FAILURE;
#ifdef linux
	}
	else
		sshot_capture_alternate(&img, tool);
#endif /* linux */
	sshot_upload(&img);
	remove(img.file_name);
	cfg_destroy();
	return EXIT_SUCCESS;
}