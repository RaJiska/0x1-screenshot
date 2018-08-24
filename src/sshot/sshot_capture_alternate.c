/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: sshot_capture_alternate.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 24th 11:11:32 2018
 */

#include <stdlib.h>
#include <string.h>
#include "sshot.h"
#include "utils.h"

bool sshot_capture_alternate(img_t *img, const char *tool)
{
	const char *file_path = "/tmp/0x1-screenshot-alternatess";
	char cmd[1000];
	int ret;

	snprintf(&cmd[0], 1000, "%s %s", tool, file_path);
	if ((ret = system(&cmd[0])) == -1)
		return FNC_PERROR_RET(bool, false, "Could not execute tool command");
	else if (ret)
		return false;
	img->builtin = false;
	strcpy(img->file_name, file_path);
	return true;
}