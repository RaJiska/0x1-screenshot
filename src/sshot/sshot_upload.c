/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: upload_screenshot.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 23rd 14:00:35 2018
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <curl/curl.h>
#include "nnullptr-screenshot.h"
#include "sshot.h"
#include "cfg.h"

typedef struct
{
	uint8_t *data;
	size_t size;
} response_data_t;

#ifdef linux
/* TODO: Ensure response is not evaluated as a shell command */
static inline void open_uploaded_screenshot(const response_data_t *link)
{
	char *buf = malloc(sizeof("xdg-open ") + link->size + 1);

	sprintf(buf, "xdg-open %s", link->data);
	system(buf);
	free(buf);
}
#endif /* linux */

static inline size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	response_data_t *mem = (response_data_t *) userp;

	mem->data = realloc(mem->data, mem->size + realsize + 1);
	if(mem->data == NULL) {
		fprintf(stderr, "Memory allocation failure: %s\n", strerror(errno));
		return 0;
	}
	memcpy(&(mem->data[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->data[mem->size] = 0;
	return realsize;
}

bool sshot_upload(const img_t *img)
{
	CURL *curl = curl_easy_init();
	CURLcode res;
	struct curl_httppost *post = NULL;
	struct curl_httppost *last = NULL;
	bool ret = true;
	response_data_t rdata = { 0 };

	if (!curl) {
		fprintf(stderr, "Could not init curl: %s\n", curl_easy_strerror(res));
		return false;
	}
	if (img->builtin)
		curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "file",
			CURLFORM_BUFFER, "File_From_0x1_Screenshot",
			CURLFORM_BUFFERPTR, img->data,
			CURLFORM_BUFFERLENGTH, img->size,
			CURLFORM_END);
	else
		curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "file",
			CURLFORM_FILE, img->file_name,
			CURLFORM_END);
	curl_easy_setopt(curl, CURLOPT_URL, cfg_key_get_value(CFG_KEY_UPLOADURL));
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rdata);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "0x1-screenshot");
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fprintf(stderr, "Error Sending The Request: %s\n", curl_easy_strerror(res));
		ret = false;
	}
	curl_easy_cleanup(curl);
	curl_formfree(post);
	open_uploaded_screenshot(&rdata);
	free(rdata.data);
	return ret;
}