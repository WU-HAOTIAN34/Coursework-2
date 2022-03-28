#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "book_management.h"
#include "interface.h"
#include "librarian.h"


void freeSpace(Book* book) {
	if (book->next == NULL) {
		free(book->title);
		free(book->authors);
		free(&book);
	}
	else {
		if (book->next->next == NULL) {
			free(book->next->title);
			free(book->next->authors);
			free(book->next);
			book->next = NULL;
		}
		else {
			freeSpace(book->next);
		}
	}
}

void searchModel() {
	BookList res;
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
		option = (int)enter[0];
		if (strlen(enter) > 1 || option <= 48 || option >= 53) {
			printf("Sorry, the option you entered was invalid, please try again.");
		}
		else {
			option -= 48;
			switch (option)
			{
			case 1:
				printf("Please enter the title: ");
				scanf("%[^\n]s", findWay);
				res = find_book_by_title(findWay);
				if (res.length == 0) {
					printf("\nDon't find.\n");
				}
				else {
					printBook(&res);
				}
				break;
			case 2:
				printf("Please enter the author: ");
				scanf("%[^\n]s", findWay);
				res = find_book_by_author(findWay);
				if (res.length == 0) {
					printf("\nDon't find.\n");
				}
				else {
					printBook(&res);
				}
				break;
			case 3:
				printf("Please enter the year: ");
				scanf("%[^\n]s", findWay);
				year = covertInt(findWay);
				res = find_book_by_year(year);
				if (res.length == 0) {
					printf("\nDon't find.\n");
				}
				else {
					printBook(&res);
				}
				break;
			case 4:
				break;
			default:
				break;
			}
		}
	}
	return;
}




void librarianModel() {
	Book* book; 
	char enter[100];
	int option = 0;
	memset(enter, '\0', 100);
	while (option != 5) {
		printf("\nPlease choose an option: \n\n1. Add book\n2. Remove book\n");
		printf("3. Search for books\n4. Display all books\n5. Quit\nOption: ");
		scanf("%s", enter);
		option = (int)enter[0];
		if (strlen(enter) > 1 || option <= 48 || option >= 54) {
			printf("Sorry, the option you entered was invalid, please try again.");
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
				break;
			default:
				break;
			}
		}
	}
	return;
}