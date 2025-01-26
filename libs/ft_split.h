#ifndef FT_SPLIT_H
# define FT_SPLIT_H
# include "../cub3d.h"

char **ft_split(const char *s, char c);
int word_count(const char *s, char c);
char *word_dup(const char *start, int len);
int word_length(const char *s, char c);
void free_all(char **result, int count);
int split_process(const char *s, char c, char **result);
int ft_atoi(const char *str);

#endif