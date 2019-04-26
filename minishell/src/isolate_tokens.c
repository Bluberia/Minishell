/*
** EPITECH PROJECT, 2017
** minishell2
** File description:
** Isolate the given tokens
*/

/* File created the 06/04/2018 at 18:17:45 by julian.frabel@epitech.eu */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "mysh.h"

int handle_ignore(const char *ignore[2], int *ignore_index, char *old, int i)
{
	const char *ignore_start = ignore[0];
	const char *ignore_end = ignore[1];

	if ((*ignore_index) && ignore_end[(*ignore_index) - 1] != old[i])
		return (1);
	if ((*ignore_index)) {
		(*ignore_index) = 0;
		return (1);
	}
	(*ignore_index) = my_str_contains(ignore_start, old[i]);
	if ((*ignore_index))
		return (1);
	return (0);
}

int calculate_newline_size(char *line, char **isolate, \
const char *ignore_start, const char *ignore_end)
{
	int new_size = 0;
	int ignore_index = 0;
	const char *ignore[2] = {ignore_start, ignore_end};
	int isolate_index = 0;

	for (int i = 0; line[i]; i++, new_size++) {
		if (line[i] == '\\' && line[i + 1] != '\0' && ++i) {
			new_size++;
			continue;
		}
		if (handle_ignore(ignore, &ignore_index, line, i))
			continue;
		isolate_index = my_array_index(&(line[i]), isolate);
		if (isolate_index != -1) {
			new_size += (line[i - 1] != ' ' && line[i - 1] != '\t');
			new_size += strlen(isolate[isolate_index]);
			i += (strlen(isolate[isolate_index]) - 1);
			new_size += (line[i + 1] != ' ' && line[i + 1] != '\t');
		}
	}
	return (new_size);
}

void fill_isolate(char *lines[2], char **isolate, int *j, int *i)
{
	char *old = lines[0];
	char *new = lines[1];
	int isolate_index = my_array_index(&(old[*i]), isolate);

	if (old[*i - 1] != ' ' && old[*i - 1] != '\t') {
		new[*j] = ' ';
		(*j)++;
	}
	for (unsigned int k = 0; k < strlen(isolate[isolate_index]); k++) {
		new[*j] = old[*i];
		(*j)++;
		(*i)++;
	}
	(*i)--;
	(*j)--;
	if (old[*i + 1] != ' ' && old[*i + 1] != '\t') {
		(*j)++;
		new[*j] = ' ';
	}
}

void fill_new_line(char *lines[2], char **isolate, \
const char *ignore_start, const char *ignore_end)
{
	char *old = lines[0];
	char *new = lines[1];
	const char *ignore[2] = {ignore_start, ignore_end};
	int ignore_index = 0;
	int isolate_index = -1;
	int j = 0;

	for (int i = 0; old[i]; j++, i++) {
		new[j] = old[i];
		if (old[i] == '\\' && old[i + 1] != '\0') {
			new[++j] = old[++i];
			continue;
		}
		if (handle_ignore(ignore, &ignore_index, old, i))
			continue;
		isolate_index = my_array_index(&(old[i]), isolate);
		if (isolate_index != -1)
			fill_isolate(lines, isolate, &j, &i);
	}
	new[j] = '\0';
}

char *isolate_tokens(char **line, const char *to_isolate, \
const char *ignore_start, const char *ignore_end)
{
	int new_line_size = 1;
	char *new_line = NULL;
	char **isolate = my_parse_str_to_array(to_isolate, ",", "[", "]");

	if (!to_isolate || !ignore_start || !ignore_end || !isolate) {
		my_free_array((void **)isolate);
		return (*line);
	}
	new_line_size += calculate_newline_size(*line, isolate, \
ignore_start, ignore_end);
	new_line = calloc(new_line_size, sizeof(*new_line));
	if (new_line == NULL) {
		my_free_array((void **)isolate);
		return (*line);
	}
	fill_new_line((char *[2]){*line, new_line}, \
isolate, ignore_start, ignore_end);
	*line = new_line;
	my_free_array((void **)isolate);
	return (*line);
}