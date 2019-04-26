/*
** EPITECH PROJECT, 2017
** minishell 1
** File description:
** split the path var
*/

#include <stdlib.h>
#include "my.h"

static int count_words_in_str(char const *str);
static int is_alphanumeric(char c);
static int count_letter(char const *str, int word_start);
static void add_word(char const *str, int pos_str, char **tab, int *pos_tab);

char **split_path(char const *path)
{
	int words = count_words_in_str(path);
	char **tab = malloc(sizeof(*tab) * (words + 2));
	int pos_in_tab = 0;
	int pos_in_str = 0;

	if (path == NULL) {
		tab[0] = NULL;
		return (tab);
	}
	if (is_alphanumeric(path[pos_in_str])) {
		add_word(path, pos_in_str - 1, tab, &pos_in_tab);
	}
	for (pos_in_str = 0; path[pos_in_str] != '\0'; pos_in_str++) {
		if (is_alphanumeric(path[pos_in_str]) == 0) {
			add_word(path, pos_in_str, tab, &pos_in_tab);
		}
	}
	tab[pos_in_tab] = 0;
	return (tab);
}

void add_word(char const *str, int pos_str, char **tab, int *pos_tab)
{
	int letters = count_letter(str, pos_str + 1);
	char *cur_str;

	if (letters == 0)
		return;
	cur_str = malloc(sizeof(*cur_str) * (letters + 1));
	my_strncpy(cur_str, &str[pos_str + 1], letters);
	cur_str[letters] = '\0';
	tab[*pos_tab] = cur_str;
	*pos_tab += 1;
}

int count_letter(char const *str, int word_start)
{
	int letters = 0;

	for (int i = 0; is_alphanumeric(str[i + word_start]); i++)
		letters++;
	return (letters);
}

int count_words_in_str(char const *str)
{
	int words = 0;

	if (str == NULL)
		return (0);
	for (int i = 0; str[i] != '\0'; i++) {
		if (is_alphanumeric(str[i]) == 0 && count_letter(str, i + 1)) {
			words++;
		}
	}
	return (words);
}

int is_alphanumeric(char c)
{
	if (c == ':' || c == '\0')
		return (0);
	return (1);
}