/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: cfg.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 23rd 18:24:07 2018
 */

#ifndef CFG_H_
#define CFG_H_

#include <stdio.h>
#include "list.h"

typedef struct
{
	const char *file;
	size_t entry_nb;
	list_t *entries;
} cfg_t;

typedef struct
{
	char *key;
	char *value;
} cfg_entry_t;

bool cfg_open(cfg_t *cfg);
void cfg_close(cfg_t *cfg);

#endif /* CFG_H_ */