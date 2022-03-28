#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "book_management.h"
#include "interface.h"
#include "librarian.h"


Book* findBook(Book* newBook, int id) {
	Book* res = NULL;
	while (newBook != NULL) {
		if (newBook->id == id) {
			res = newBook;
			break;
		}
		newBook = newBook->next;
	}
	return res;
}




int borrowBook(user* theUser) {
	int option,len;
	char enter[40];
	Book* query;
	Book* newBook;
	memset(enter, '\0', 40);
	printBook(library);
	printf("Plesse enter the ID you want to borrow: ");
	scanf("%s", enter);
	option = (int)enter[0];
	if (strlen(enter) > 1 || (int)enter[0] < 49 || (int)enter[0]>57) {
		printf("Invalid entering.\n");
		return 0;
	}
	if (findBook(theUser->broBook, option) != NULL) {
		printf("You have borrowed this book.\n");
		return 0;
	}
	query = findBook(library->list, option);
	if ( query == NULL) {
		printf("The book does not exist.\n");
		return 0;
	}
	else {
		query->copies -= 1;
		if (theUser->bookNum == 0) {
			theUser->bookNum += 1;
			theUser->broBook = (Book*)malloc(sizeof(Book));
			theUser->broBook->id = query->id;
			strcpy(theUser->broBook->title, query->title);
			strcpy(theUser->broBook->authors, query->authors);
			theUser->broBook->year = query->year;
			theUser->broBook->copies = query->copies;
			return 1;
		}
		else {
			theUser->bookNum += 1;
			newBook = theUser->broBook;
			while (newBook->next != NULL) {
				newBook = newBook->next;
			}
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
			newBook->id = query->id;
			newBook->year = query->year;
			newBook->copies = query->copies;
			len = strlen(query->title);
			newBook->title = (char*)malloc(sizeof(len + 1));
			memset(newBook->title, '\0', len + 1);
			strcpy(newBook->title, query->title);
			len = strlen(query->authors);
			newBook->authors = (char*)malloc(sizeof(len + 1));
			memset(newBook->authors, '\0', len + 1);
			strcpy(newBook->authors, query->authors);
			newBook->next = NULL;
			return 1;
		}
	}
}


void returnBook(user* theUser) {
	char id[100];
	int option;
	Book* temp;
	Book* newBook = theUser->broBook;
	memset(id, '\0', 100);
	printf("Please enter the ID you want to remove: ");
	scanf("%[^\n]s", id);
	if ((int)id[0] == 48 || strspn(id, "0123456789") != strlen(id) || strlen(id) >= 5 || strlen(id) <= 0) {
		printf("Invalid id\n");
		return 0;
	}
	else {
		option = covertInt(id);
	}
	if (newBook->next == NULL) {
		if (newBook->id == option) {
			library->length -= 1;
			library->list = NULL;
			free(newBook->authors);
			free(newBook->title);
			free(&newBook);
			printf("\nRevome successfully!\n");
			return 1;
		}
		else {
			printf("The book doesn't exist.");
			return 0;
		}
	}
	else {
		if (newBook->id == option) {
			library->length -= 1;
			library->list = newBook->next;
			free(newBook->authors);
			free(newBook->title);
			free(&newBook);
			printf("\nRevome successfully!\n");
			return 1;
		}
		while (newBook->next != NULL) {
			if (newBook->next->id == option) {
				if (newBook->next->next = NULL) {
					free(newBook->next->title);
					free(newBook->next->authors);
					free(newBook->next);
					newBook->next = NULL;
					printf("\nRevome successfully!\n");
					return 1;
				}
				else {
					temp = newBook->next;
					newBook->next = newBook->next->next;
					free(temp->authors);
					free(temp->title);
					free(temp);
					printf("\nRevome successfully!\n");
					return 1;
				}

			}
		}
		printf("The book doesn't exist.");
		return 0;
	}

}




void userModel(user* signUser) {
	BookList* book = (BookList*)malloc(sizeof(BookList));
	char enter[100];
	int option = 0;
	memset(enter, '\0', 100);
	while (option != 6) {
		printf("\nPlease choose an option: \n\n1. Borrow book\n2. Return book\n");
		printf("3. Search for books\n4. Display all books\n5. Show my books\n6. Quit\nOption: ");
		scanf("%s", enter);
		option = (int)enter[0];
		if (strlen(enter) > 1 || option <= 48 || option >= 55) {
			printf("Sorry, the option you entered was invalid, please try again.");
		}
		else {
			option -= 48;
			switch (option)
			{
			case 1:
				borrowBook(signUser);
				break;
			case 2:
				returnBook(signUser);
				break;
			case 3:
				searchModel();
				break;
			case 4:
				printBook(library);
				break;
			case 5:
				book->length = signUser->bookNum;
				book->list = signUser->broBook;
				printBook(book);
				break;
			case 6:
				break;
			default:
				break;
			}
		}
	}
	return;
}
