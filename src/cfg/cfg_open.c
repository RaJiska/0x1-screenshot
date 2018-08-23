/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: cfg_open.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 23rd 18:23:41 2018
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cfg.h"
#include "utils.h"

#ifdef linux
#include <unistd.h>
#endif /* linux */

bool cfg_open(cfg_t *cfg)
{
	FILE *f;
	ssize_t rd_len;
	char **wt;
	size_t line_no = 0;
	cfg_entry_t *entry;

#ifdef linux
	cfg->file = !access("/etc/0x1-screenshot/general.cfg", R_OK) ? "/etc/0x1-screenshot/general.cfg" : "config.txt";
#elif _WIN32
	cfg->file = "config.txt";
#endif
	f = fopen(cfg->file, "r");
	if (!f)
		return FNC_WARN_RET(bool, false, "Could not read configuration file (%s)", cfg->file);
	for (char *line = NULL; (rd_len = getline(&line, &(size_t) { 0 }, f)) > 0; line = NULL) {
		++line_no;
		if (line[rd_len - 1] == '\n')
			line[rd_len] = 0;
		utils_clearstr(line);
		if (line[0] == 0 || !(wt = utils_strsplit(line, "=", 1))) {
			free(line);
			continue;
		}
		free(line);
		if (!wt[0] || !wt[1] || !strlen(utils_clearstr(wt[0])) || !strlen(utils_clearstr(wt[1]))) {
			FNC_ERROR("Syntax error in config file %s:%d", cfg->file, line_no);
			utils_wt_destroy(wt);
			continue;
		}
		if (!(entry = malloc(sizeof(cfg_entry_t)))) {
			utils_wt_destroy(wt);
			continue;
		}
		if (!list_push(&cfg->entries, entry)) {
			utils_wt_destroy(wt);
			free(entry);
			continue;
		}
		entry->key = wt[0];
		entry->value = wt[1];
		++cfg->entry_nb;
		free(wt);
	}
	fclose(f);
	return true;
}