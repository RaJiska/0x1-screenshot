/*
** EPITECH PROJECT, 2018
** myftp.h
** File description:
** myftp.h
*/
/**
* \file
* \brief Utils header
*/

#ifndef UTIL_H_
# define UTIL_H_

#include <stdbool.h>
#include <stddef.h>

#define STRINGIFY(elm) #elm
#define TOSTRING(elm) STRINGIFY(elm)

#define FNC_WARN(elm, ...) utils_error(0, __FILE__ ":" TOSTRING(__LINE__) ": WARNING: " elm, ##__VA_ARGS__)
#define FNC_WARN_RET(type, ret, elm, ...) ((type) (FNC_WARN(elm, ##__VA_ARGS__)))
#define FNC_PERROR(elm, ...) utils_perror(0, __FILE__ ":" TOSTRING(__LINE__) ": ERROR: " elm, ##__VA_ARGS__)
#define FNC_PERROR_RET(type, ret, elm, ...) ((type) (FNC_PERROR(elm, ##__VA_ARGS__)))
#define FNC_ERROR(elm, ...) utils_error(0, __FILE__ ":" TOSTRING(__LINE__) ": ERROR: " elm, ##__VA_ARGS__)
#define FNC_ERROR_RET(type, ret, elm, ...) ((type) (FNC_ERROR(elm, ##__VA_ARGS__)))
#define COND_PRINTF(cond, fmt, ...) if (cond) printf(fmt, ##__VA_ARGS__);

long long int utils_perror(long long int ret, const char *s, ...);
long long int utils_error(long long int ret, const char *s, ...);
char **utils_strsplit(const char *str, const char *delims, int max_delims);
char *utils_strjoin(char * const *wt, const char *separator);
size_t utils_wt_count(char * const *wt);
char **utils_wt_push(char **wt, const char *s);
char **utils_wt_copy(char * const *wt);
char **utils_wt_pop_front(char **wt, char **str);
void utils_wt_destroy(char **wt);
bool utils_strreplace(char *s, const char *from, const char *to);
char *utils_clearstr(char *s);
char *utils_strsep(char **str, const char *delims);

#endif /* !UTIL_H_ */
