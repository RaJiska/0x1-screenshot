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

#define CFG_KEY_UPLOADURL "uploadurl"
#define CFG_KEY_SCREENSHOTTOOL "screenshottool"

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

extern const cfg_entry_t CFG_DEFAULTS[2];
extern cfg_t G_CFG;

bool cfg_init(void);
const char *cfg_key_get_value(const char *key);
const char *cfg_key_get_default_value(const char *key);
void cfg_destroy(void);

#endif /* CFG_H_ */