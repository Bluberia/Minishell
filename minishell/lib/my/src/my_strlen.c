/*
** EPITECH PROJECT, 2017
** libmy
** File description:
** return the length of the string
*/

#include <stdlib.h>

int	my_strlen(char const *str)
{
	int	iterator = 0;

	if (str == NULL)
		return (0);
	while (str[iterator] != '\0') {
		iterator++;
	}
	return (iterator);
}
