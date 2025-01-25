#include "ft_split.h"

char **ft_split(const char *s, char c)
{
	int words;
	char **result;

	if (!s)
		return NULL;
	words = word_count(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return NULL;
	if (split_process(s, c, result) == -1)
	{
		free_all(result, words);
		return NULL;
	}
	return result;
}
