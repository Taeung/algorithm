/*
  *phone-book.c
 *
  *Copyright (C) 2014, Taeung Song <treeze.taeung@gmail.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct phone_node {
	char name[1024];
	char phone_number[1024];
	struct phone_node *next;
};

struct phone_node *search(struct phone_node **head, char *name)
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

void display(struct phone_node **head)
{
	struct phone_node *current_node;

	if (*head == NULL) {
		printf("\tThere is nothing. \n");
		return;
	}

	current_node = *head;

	while (current_node != NULL) {
		printf("\n\t===============================\n");
		printf("\tName : %s \n", current_node->name);
		printf("\tPhone number : %s \n", current_node->phone_number);
		current_node = current_node->next;
	}
	printf("\n\t===============================\n");
}

void insert(struct phone_node **head)
{
	struct phone_node *current_node;
	char phone_number[1024] = {0};
	char name[1024] = {0};

	printf("\tPlease enter a name : ");
	scanf("%s", name);

	if (search(head, name) != NULL) {
		printf("\tThere is already this name : %s \n", name);
		return;
	}

	if (*head == NULL) {
		/* first */
		*head = (struct phone_node *)malloc(sizeof(struct phone_node));
		strcpy((*head)->name, name);
		printf("\tPlease enter a phone number : ");
		scanf("%s", phone_number);
		strcpy((*head)->phone_number, phone_number);
		(*head)->next = NULL;
	} else {
		current_node = *head;
		while (current_node->next != NULL) {
			current_node = current_node->next;
		}

		current_node->next = (struct phone_node *)malloc(sizeof(struct phone_node));

		strcpy(current_node->next->name, name);
		printf("\tPlease enter a phone number : ");
		scanf("%s", phone_number);
		strcpy(current_node->next->phone_number, phone_number);
		current_node->next->next = NULL;
	}

	printf("\n\t===============================\n");
	printf("\tName : %s \n", name);
	printf("\tPhone number : %s \n", phone_number);
	printf("\t===============================\n");
}

void update(struct phone_node **head)
{
	struct phone_node *current_node;
	char phone_number[1024] = {0};
	char name[1024] = {0};

	printf("\tPlease enter a name : ");
	scanf("%s", name);
	current_node = search(head, name);
	if (current_node == NULL) {
		printf("\tThere is not this name : %s \n", name);
		return;
	} else {
		printf("\tPlease enter new phone number : ");
		scanf("%s", phone_number);
		strcpy(current_node->phone_number, phone_number);
	}
}

void delete(struct phone_node **head)
{
	struct phone_node *current_node;
	struct phone_node *before_node;
	char name[1024] = {0};

	printf("\tPlease enter a name : ");
	scanf("%s", name);
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
	struct phone_node *head = NULL;
	int menu_num;
	char end;

	do {
		system("clear");
		menu_num = menu();
		switch (menu_num) {
		case 1:
			insert(&head);
			break;
		case 2:
			delete(&head);
			break;
		case 3:
			update(&head);
			break;
		case 4:
			display(&head);
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
