#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "book_management.h"

user* loadUser(FILE* a) {
	user* newUser;
	Book* newBook;
	int i;
	user* res = (user*)malloc(sizeof(user));
	int userSize = sizeof(user) - sizeof(Book*) - sizeof(user*);     
	int bookSize = sizeof(Book) - sizeof(Book*);
	while (1) {
		newUser = (user*)malloc(sizeof(user));       
		newBook = newUser->broBook;
		if (fread(newUser, userSize, 1, a) != 0) {
			if (newUser->bookNum != 0) {
				newBook = (Book*)malloc(sizeof(Book));
				newUser->broBook = newBook;
				for (i = 1; i < newUser->bookNum; i++) {
					fread(&(newBook->id), sizeof(int), 1, a);                   //load a Book struct
					newBook->title = (char*)malloc(sizeof(char)*TITLE);
					fread(newBook->title, sizeof(char) * TITLE, 1, a);
					newBook->authors = (char*)malloc(sizeof(char) * AUTHOR);    
					fread(newBook->authors, sizeof(char) * AUTHOR, 1, a);
					fread(&(newBook->year), sizeof(int), 1, a);
					fread(&(newBook->copies), sizeof(int), 1, a);
					newBook->next = (Book*)malloc(sizeof(Book));
					newBook = newBook->next;
				}
			}
		}		
	}
}



void writeUser(FILE* a,user* b) {
	user* newUser;
	Book* newBook;
	int i;
	int userSize = sizeof(user) - sizeof(Book*) - sizeof(user*);
	int bookSize = sizeof(Book) - sizeof(Book*);
	newUser = b->next;
	while (newUser != NULL) {
		fwrite(newUser, userSize, 1, b);
		if (newUser->bookNum != 0) {
			newBook = newUser->broBook;
			for (i = 0; i < newUser->broBook; i++) {
				fwrite(&(newBook->id), sizeof(int), 1, a);
				fwrite(newBook->title, sizeof(char) * TITLE, 1, a);
				fwrite(newBook->authors, sizeof(char) * AUTHOR, 1, a);
				fwrite(&(newBook->year), sizeof(int), 1, a);
				fwrite(&(newBook->copies), sizeof(int), 1, a);
				newBook = newBook->next;
			}
		}
		newUser = newUser->next;
	}
}













void interface() {
	char choice;
	while (1) {
		printf("\nPlease choose an option: \n\n1. Register an account\n2. Login\n");
		printf("3. Search for books\n4. Display all books\n5. Quit\nOption: ");
		scanf("%c", &choice);
		getchar();
		if ((int)choice > 48 && (int)choice < 54) {
			break;
		}
		else {
			printf("\nSorry, the option you entered was invalid, please try again.\n");
		}
	}
	switch ((int)choice - 48)
	{
	case 1:
		printf("1. Register an account");
		break;
	case 2:
		printf("2. Login");
		break;
	case 3:
		printf("3. Search for books");
		break;
	case 4:
		printf("4. Display all books");
		break;
	case 5:
		printf("5. Quit");
	default:
		break;
	}
}