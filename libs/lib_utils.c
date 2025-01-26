#include "../cub3d.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2)
			return (unsigned char)*s1 - (unsigned char)*s2;
		if (*s1 == '\0')
			return 0;
		s1++;
		s2++;
	}
	return 0;
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

char *ft_strdup(const char *s)
{
	char *dup;
	size_t len;

	len = strlen(s);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return NULL;
	strcpy(dup, s);
	return dup;
}

int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

// 문자열에서 특정 문자가 존재하는지 확인
int ft_strchr(const char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return 1;
		i++;
	}
	return 0;
}

// 문자열의 특정 부분을 추출하여 반환
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char *substr;
	size_t i;

	if (!s)
		return NULL;
	if (start >= strlen(s))
		return strdup("");
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return NULL;
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return substr;
}

// 문자열 앞뒤에서 특정 문자 집합을 제거
char *ft_strtrim(char *s1, char *set)
{
	size_t start;
	size_t end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}