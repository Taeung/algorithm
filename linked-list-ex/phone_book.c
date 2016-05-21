/*
  *phone-book.c
 *
  *Copyright (C) 2014, Taeung Song <treeze.taeung@gmail.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct phone_node {
	char name[1024];
	char phone_number[1024];
	struct phone_node *next;
};

struct phone_node *search(struct phone_node **head, const char *name)
{
	struct phone_node *current_node;

	if (*head == NULL)
		return NULL;

	current_node = *head;
	while (current_node != NULL) {
		if (strcmp(current_node->name, name) == 0)
			return current_node;
		current_node = current_node->next;
	}

	return NULL;
}

void print_bar(bool newline)
{
	if (newline)
		printf("\n\t===============================\n");
	else
		printf("\t===============================\n");
}

void show_contact_info(struct phone_node *contact_info)
{
	printf("\tName : %s \n", contact_info->name);
	printf("\tPhone number : %s \n", contact_info->phone_number);
}

void display(struct phone_node **head)
{
	struct phone_node *current_node;

	if (*head == NULL) {
		printf("\tThere is nothing. \n");
		return;
	}

	current_node = *head;

	print_bar(true);
	while (current_node != NULL) {
		show_contact_info(current_node);
		current_node = current_node->next;
		print_bar(false);
	}
}

const char *get_name_from_user(void)
{
	static char name[1024] = {0};

	printf("\tPlease enter a name : ");
	scanf("%s", name);
	return name;
}

const char *get_phone_number_from_user(void)
{
	static char phone_number[1024] = {0};

	printf("\tPlease enter a phone number : ");
	scanf("%s", phone_number);
	return phone_number;
}

struct phone_node *create_contact(struct phone_node **head)
{
	const char *name = get_name_from_user();
	const char *phone_number = get_phone_number_from_user();
	struct phone_node *contact;

	if (search(head, name) != NULL) {
		printf("\tThere is already this name : %s \n", name);
		return NULL;
	}

	contact = (struct phone_node *)malloc(sizeof(struct phone_node));
	strcpy(contact->name, name);
	strcpy(contact->phone_number, phone_number);

	print_bar(true);
	show_contact_info(contact);
	print_bar(false);

	return contact;
}

void insert(struct phone_node **head)
{
	struct phone_node *current_node;
	struct phone_node *new_node = create_contact(head);

	if (new_node == NULL)
		return;

	if (*head == NULL) {
		/* first */
		*head = new_node;
		(*head)->next = NULL;
	} else {
		current_node = *head;
		while (current_node->next != NULL) {
			current_node = current_node->next;
		}

		current_node->next = new_node;
		current_node->next->next = NULL;
	}
}

void update(struct phone_node **head)
{
	struct phone_node *current_node;
	const char *phone_number;
	const char *name = get_name_from_user();

	current_node = search(head, name);
	if (current_node == NULL) {
		printf("\tThere is not this name : %s \n", name);
		return;
	} else {
		phone_number = get_phone_number_from_user();
		strcpy(current_node->phone_number, phone_number);
	}
}

void delete(struct phone_node **head)
{
	struct phone_node *current_node;
	struct phone_node *before_node;
	const char *name = get_name_from_user();

	current_node = search(head, name);

	if (current_node == NULL) {
		printf("\tThere is not this name : %s \n", name);
		return;
	} else {
		if (current_node == *head) {
			/* first */
			*head = current_node->next;
			free(current_node);
		} else if (current_node->next == NULL) {
			/* end */
			before_node = *head;
			do {
				if (current_node == before_node->next)
					break;
				before_node = before_node->next;
			} while (1);
			before_node->next = NULL;
			free(current_node);
		} else {
			/* middle */
			before_node = *head;
			do {
				if (current_node == before_node->next)
					break;
				before_node = before_node->next;
			} while (1);
			before_node->next = current_node->next;
			free(current_node);
		}
	}
}

int menu(void)
{
	int menu;

	do {
		printf("\n\n\t=======================================\n");
		printf("\t===        Phone number Book        ===\n");
		printf("\t=======================================\n");
		printf("\t=== 1. Insert new phone number      ===\n");
		printf("\t=== 2. Delete existing phone number ===\n");
		printf("\t=== 3. Update existing phone number ===\n");
		printf("\t=== 4. Show existing phone number   ===\n");
		printf("\t=== 5. Exit this program            ===\n");
		printf("\t=======================================\n\n");
		printf("\tChoose menu >> ");
		scanf("%d", &menu);
		if (menu <= 5 && menu >= 1)
			break;
		else {
			system("clear");
			printf("\tError, You have to choose menu , again.\n");
		}
	} while (1);

	return menu;
}

int main(int argc, const char  *argv[])
{
	/* head node for contacts list */
	struct phone_node *contacts = NULL;
	int menu_num;
	char end;

	do {
		system("clear");
		menu_num = menu();
		switch (menu_num) {
		case 1:
			insert(&contacts);
			break;
		case 2:
			delete(&contacts);
			break;
		case 3:
			update(&contacts);
			break;
		case 4:
			display(&contacts);
			break;
		case 5:
			printf("\n\n\t Good bye !! \n\n");
			return 0;
		default:
			break;
		}
		printf("\n\tIf you want to continue, press enter key.. ");
		scanf("%c%c", &end, &end);
	} while (menu_num != 5);

	return 0;
}
