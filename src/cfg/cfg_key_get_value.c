/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: cfg_key_get_value.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 23rd 22:49:55 2018
 */

#include <string.h>
#include "cfg.h"

const char *cfg_key_get_value(const cfg_t *cfg, const char *key)
{
	cfg_entry_t *entry;

	for (list_t *curr = cfg->entries; curr; curr = curr->next) {
		entry = curr->elm;
		if (!strcmp(entry->key, key))
			return entry->value;
	}
	return cfg_key_get_default_value(key);
}