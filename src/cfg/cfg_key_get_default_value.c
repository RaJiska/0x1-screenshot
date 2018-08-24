/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: cfg_key_get_default_value.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 24th 10:18:16 2018
 */

#include <string.h>
#include "cfg.h"

const char *cfg_key_get_default_value(const char *key)
{
	for (int it = 0; it < sizeof(G_CFG_DEFAULTS) / sizeof(cfg_entry_t); ++it) {
		if (!strcmp(key, G_CFG_DEFAULTS[it].key))
			return G_CFG_DEFAULTS[it].value;
	}
	return NULL;
}