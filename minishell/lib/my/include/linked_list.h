/*
** EPITECH PROJECT, 2017
** Lib my linked list
** File description:
** header file
*/

#ifndef MY_LINKEDLIST
#define MY_LINKEDLIST

	typedef struct linked_list {
		void *element;
		char *name;
		struct linked_list *prev;
		struct linked_list *next;
	} linked_list_t;

	void add_node(linked_list_t **list, char *name, void *element);
	linked_list_t *get_node(linked_list_t *list, char *name);
	int get_list_size(linked_list_t *list);
	linked_list_t *get_node_by_pos(int pos, linked_list_t *list);
	void destroy_list(linked_list_t *, void (*)(linked_list_t *));
	void remove_node_by_name(linked_list_t **list, char *name);

#endif