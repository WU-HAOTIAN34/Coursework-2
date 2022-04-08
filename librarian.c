#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "book_management.h"
#include "interface.h"
#include "librarian.h"

//  free a Book struct author title and itself
void freeNode(Book* book) {
	free(book->authors);
	free(book->title);
	free(book);
}

// free a list of book struct
void freeList(Book* list) {
	Book* newBook = list;
	Book* next;
	while (newBook != NULL) {
		next = newBook;
		newBook = newBook->next;
		freeNode(next);
	}
}

// free a list of  user struct
void freeUser(userList* list) {
	user* newUser = list->list;
	user* next;
	while (newUser != NULL) {
		next = newUser;
		newUser = newUser->next;
		free(next->ID);
		free(next->broBook);
		free(next);
	}
}

// the interface of seach book
void searchModel() {
	BookList* res;
	int year;
	char findWay[100];
	char enter[100];
	int option = 0;
	memset(findWay, '\0', 100);
	memset(enter, '\0', 100);
	while (option != 4) {
		printf("\nPlease choose an option: \n\n1. Find books by title\n2. Find books by author\n");
		printf("3. Find books by year\n4. Quit\nOption: ");
		scanf("%s", enter);
		getchar();
		// judge if the option is valid
		option = (int)enter[0];
		if (strlen(enter) > 1 || option <= 48 || option >= 53) {
			printf("\033[47;31mSorry, the option you entered was invalid, please try again.\033[0m");
		}
		else {
			option -= 48;
			switch (option)
			{
			case 1:
				printf("\nPlease enter the title: ");
				scanf("%[^\n]s", findWay);
				getchar();
				res = (BookList*)malloc(sizeof(BookList));
				*res = find_book_by_title(findWay);
				// print searched booklist
				if (res->length == 0) {
					printf("\nDon't find.\n");
				}
				else {
					printBook(res);
				}
				//   free the searched booklist
				freeList(res->list);
				free(res);
				break;
			case 2:
				printf("\nPlease enter the author: ");
				scanf("%[^\n]s", findWay);
				getchar();
				res = (BookList*)malloc(sizeof(BookList));
				*res = find_book_by_author(findWay);
				if (res->length == 0) {
					printf("\nDon't find.\n");
				}
				else {
					printBook(res);
				}
				freeList(res->list);
				free(res);
				break;
			case 3:
				printf("\nPlease enter the year: ");
				scanf("%[^\n]s", findWay);
				getchar();
				year = covertInt(findWay);
				res = (BookList*)malloc(sizeof(BookList));
				*res = find_book_by_year(year);
				if (res->length == 0) {
					printf("\nDon't find.\n");
				}
				else {
					printBook(res);
				}
				freeList(res->list);
				free(res);
				break;
			case 4:
			default:
				break;
			}
		}
	}
}



// the interface after librarian login
void librarianModel() {
	Book* book;
	char enter[100];
	int option = 0;
	memset(enter, '\0', 100);
	while (option != 5) {
		printf("\nPlease choose an option: \n\n1. Add book\n2. Remove book\n");
		printf("3. Search for books\n4. Display all books\n5. Quit\nOption: ");
		scanf("%[^\n]s", enter);
		getchar();
		option = (int)enter[0];
		if (strlen(enter) > 1 || option <= 48 || option >= 54) {
			printf("\033[47;31mSorry, the option you entered was invalid, please try again.\033[0m\n");
		}
		else {
			option -= 48;
			switch (option)
			{
			case 1:
				book = (Book*)malloc(sizeof(Book));
				add_book(*book);
				free(book);
				break;
			case 2:
				book = (Book*)malloc(sizeof(Book));
				remove_book(*book);
				free(book);
				break;
			case 3:
				searchModel();
				break;
			case 4:
				printBook(library);
				break;
			case 5:
			default:
				break;
			}
		}
	}
}

