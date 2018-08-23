/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: cfg_close.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 23rd 19:11:31 2018
 */

#include <stdlib.h>
#include "list.h"
#include "cfg.h"

static void destroy_callback(void *elm)
{
	cfg_entry_t *entry = elm;

	free(entry->key);
	free(entry->value);
	free(elm);
}

void cfg_close(cfg_t *cfg)
{
	list_destroy(&cfg->entries, LIST_FREE_FNC, destroy_callback);
}