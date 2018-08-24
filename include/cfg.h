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

extern const cfg_entry_t G_CFG_DEFAULTS[2];

bool cfg_init(cfg_t *cfg);
const char *cfg_key_get_value(const cfg_t *cfg, const char *key);
const char *cfg_key_get_default_value(const char *key);
void cfg_destroy(cfg_t *cfg);

#endif /* CFG_H_ */