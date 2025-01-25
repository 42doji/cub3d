#include "ft_split.h"
int word_count(const char *s, char c)
{
	int count;
	int in_word;

	count = 0;
	in_word = 0;
	while (*s)
    {
		if (*s != c && !in_word)
        {
			in_word = 1;
			count++;
		} else if (*s == c)
			in_word = 0;
		s++;
	}
	return count;
}

char *word_dup(const char *start, int len)
{
  	char *word;
	int i;

    word = malloc(len + 1);
	if (!word)
		return NULL;
	i = 0;
    while (i < len)
    {
    	word[i] = start[i];
    	i++;
    }
	word[len] = '\0';
	return (word);
}

int word_length(const char *s, char c)
{
	int length;

	length = 0;
	while (*s && *s != c)
    {
		length++;
		s++;
	}
	return (length);
}

void free_all(char **result, int count)
{
    int i;

    i = 0;
	while (i < count)
		free(result[i]);
	free(result);
}

int split_process(const char *s, char c, char **result)
{
	int i;
	int len;

    i = 0;
	len = 0;
	while (*s)
    {
		if (*s != c)
        {
			len = word_length(s, c);
			result[i] = word_dup(s, len);
			if (!result[i])
            {
				free_all(result, i);
				return (-1);
			}
			i++;
			s += len;
		}
        else
			s++;
	}
	result[i] = NULL;
	return 0;
}
