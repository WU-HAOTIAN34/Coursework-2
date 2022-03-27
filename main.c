#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "interface.h"
#include "book_management.h"


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



void registerModule(user* a) {
	user* list = a->next;
	user* newUser;
	char ID[40];
	char password[40];
	while (1) {
		printf("Please enter your ID number(8-digit-number): ");
		scanf("%s", ID);
		if (strspn(ID, "0123456789") == strlen(ID) && strlen(ID) == 8) {
			break;
		}
		else {
			printf("Format error, please enter again!\n");
		}
		while (list->next != NULL) {
			if (strcmp(list->ID, ID)) {
				printf("The ID already exists.");
				break;
			}
		}
	}
	printf("Ok\n");
	while (1) {
		printf("Please enter your password(8-digit-number): ");
		memset(password, '\0', sizeof(password));
		scanf("%s", password);
		if (strspn(password, "0123456789") == strlen(password) && strlen(password) == 8) {
			printf("Ok\n");
			break;
		}
		else {
			printf("Format error, please enter again!\n");
		}
	}
	while (list->next != NULL) {
		list = list->next;
	}
	newUser = (user*)malloc(sizeof(user));
	list->next = newUser;
	strcpy(newUser->ID, ID);
	strcpy(newUser->password, password);
	newUser->broBook = NULL;
	newUser->next = NULL;
	printf("Congratuulations. You have registered successfully!\n");



}

void signModule(user* a) {
	user* list = a->next;
	user* newUser;
	char enterID[40];
	char enterpassword[40];       // Receive the entered ID and password
	char password[9];
	while (1) {
		printf("Please enter your ID number(8-digit-number): ");
		scanf("%s", enterID);
		if (strspn(enterID, "0123456789") == strlen(enterID) && strlen(enterID) == 8) {
			break;
		}
		else {
			printf("Format error, please enter again!\n");
		}
		while (list->next != NULL) {
			if (strcmp(list->ID, enterID)) {
				strcmp(password, list->password);
				break;
			}
		}
		printf("The ID doesn't exist.");
	}
	while (1) {
		printf("Please enter your password(8-digit-number): ");
		scanf("%s", password);
		if (strspn(password, "0123456789") == strlen(password) && strlen(password) == 8) {
			printf("Ok\n");
			break;
		}
		else {
			printf("Format error, please enter again!\n");
		}
		if (strcmp(password, enterpassword)) {			
			return;
		}
		else {
			printf("Icorrect password, please enter again.");
		}
	}
}


int main() {
	/*signModule();
	library = (Book*)malloc(sizeof(Book));*/
	/*char a[12] = "edadeadadagg";
	int i;
	i = strspn("ababababababab", "abcdefghijklmnop\0");
	printf("%d", i);*/

	member = (userList*)malloc(sizeof(userList));
	FILE* a = fopen("user.txt", "rb");
	loadUser(a);
	fclose(a);


	//******************************************************************************************
	/*Book* newBook;
	int len;
	char a[100];
	memset(a, '\0', sizeof(char) * 100);
	member = (userList*)malloc(sizeof(userList));
	member->userNum = 5;
	member->list = (user*)malloc(sizeof(user));
	user* newUser = member->list;
	
	strcpy(a, "librarian");
	len = strlen(a);
	newUser->ID = (char*)malloc(sizeof(char) * (len + 1));
	memset(newUser->ID, '\0', len + 1);
	strcpy(newUser->ID, a);
	memset(newUser->password, '\0', sizeof(char) * 9);
	strcpy(newUser->password, "11111111");
	newUser->bookNum = 0;
	newUser->broBook = NULL;
	newUser->next = (user*)malloc(sizeof(user));
	newUser = newUser->next;
	//11111111111111111111111111111

	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Wu");
	len = strlen(a);
	newUser->ID = (char*)malloc(sizeof(char) * (len + 1));
	memset(newUser->ID, '\0', len + 1);
	strcpy(newUser->ID, a);

	memset(newUser->password, '\0', sizeof(char) * 9);
	strcpy(newUser->password, "22222222");
	newUser->bookNum = 2;
	newUser->broBook = (Book*)malloc(sizeof(Book));
	newBook = newUser->broBook;

	newBook->id = 2;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Isaac Asimov");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "I,Robot");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 2013;
	newBook->copies = 102;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;

	newBook->id = 1;
	strcpy(a, "Frank Herbert");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Dune");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1978;
	newBook->copies = 23;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = NULL;
	



	newUser->next = (user*)malloc(sizeof(user));
	newUser = newUser->next;

	//2222222222222222222222222222222222222222222222222222222222222222222222222

	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Hao");
	len = strlen(a);
	newUser->ID = (char*)malloc(sizeof(char) * (len + 1));
	memset(newUser->ID, '\0', len + 1);
	strcpy(newUser->ID, a);

	memset(newUser->password, '\0', sizeof(char) * 9);
	strcpy(newUser->password, "33333333");
	newUser->bookNum = 1;
	newUser->broBook = (Book*)malloc(sizeof(Book));
	newBook = newUser->broBook;

	newBook->id = 3;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "William Gibson");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Neuromancer");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1846;
	newBook->copies = 42;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = NULL;


	newUser->next = (user*)malloc(sizeof(user));
	newUser = newUser->next;


	//333333333333333333333333333333333333333333333333333333333333333333333333333
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Tian");
	len = strlen(a);
	newUser->ID = (char*)malloc(sizeof(char) * (len + 1));
	memset(newUser->ID, '\0', len + 1);
	strcpy(newUser->ID, a);

	memset(newUser->password, '\0', sizeof(char) * 9);
	strcpy(newUser->password, "44444444");
	newUser->bookNum = 0;
	newUser->broBook = NULL;


	newUser->next = (user*)malloc(sizeof(user));
	newUser = newUser->next;
	//4444444444444444444444444444444444444444444444444444444444444444444444444444444444444
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Wu Haotian");
	len = strlen(a);
	newUser->ID = (char*)malloc(sizeof(char) * (len + 1));
	memset(newUser->ID, '\0', len + 1);
	strcpy(newUser->ID, a);

	memset(newUser->password, '\0', sizeof(char) * 9);
	strcpy(newUser->password, "55555555");
	newUser->bookNum = 3;
	newUser->broBook = (Book*)malloc(sizeof(Book));
	newBook = newUser->broBook;


	newBook->id = 6;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Neal Stephenson");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Snow Crash");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1586;
	newBook->copies = 79;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;

	newBook->id = 3;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "William Gibson");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Neuromancer");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1846;
	newBook->copies = 42;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;

	newBook->id = 7;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Jeff Noon");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Vurt");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1999;
	newBook->copies = 156;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = NULL;



	newUser->next = NULL;


	FILE* lllll = fopen("user.txt", "wb+");
	storeUser(lllll);
	fclose(lllll);*/
	//**************************************************************************************************


	//*****************************************************************************************************

	/*char a[100];
	memset(a, '\0', sizeof(char) * 100);
	library = (BookList*)malloc(sizeof(BookList));
	
	FILE* B = fopen("book.txt", "rb");
	load_books(B);
	fclose(B);*/

	
	/*Book* newBook;
	library->list = (Book*)malloc(sizeof(Book));
	newBook = library->list;
	
	library->length = 7;

	newBook->id = 1;
	strcpy(a, "Frank Herbert");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Dune");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1978;
	newBook->copies = 23;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;


	newBook->id = 2;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Isaac Asimov");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "I,Robot");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 2013;
	newBook->copies = 102;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;
	
	newBook->id = 3;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "William Gibson");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Neuromancer");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1846;
	newBook->copies = 42;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;
	
	newBook->id = 4;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Ray Bradbury");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Farenheit 451");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1685;
	newBook->copies = 345;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;
	
	newBook->id = 5;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Andy Weir");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "The Martian");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1959;
	newBook->copies = 13;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;

	newBook->id = 6;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Neal Stephenson");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Snow Crash");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1586;
	newBook->copies = 79;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;

	newBook->id = 7;
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Jeff Noon");
	newBook->title = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->title, '\0', strlen(a) + 1);
	strcpy(newBook->title, a);
	memset(a, '\0', sizeof(char) * 100);
	strcpy(a, "Vurt");
	newBook->authors = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	memset(newBook->authors, '\0', strlen(a) + 1);
	strcpy(newBook->authors, a);
	newBook->year = 1999;
	newBook->copies = 156;
	printf("%s\n", newBook->title);
	printf("%s\n", newBook->authors);
	newBook->next = NULL;

	
	



	FILE* b = fopen("book.txt", "wb+");
	store_books(b);
	fclose(b);*/



	printf("Ok");
	return 0;
}