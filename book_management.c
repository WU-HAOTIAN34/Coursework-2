#define _CRT_SECURE_NO_WARNINGS
#include "book_management.h"
#include "interface.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "librarian.h"
#include "user.h"



int store_books(FILE* file) {
	int len;	//the length of string
	Book* newBook = library->list; // book node
	fwrite(&library->length, sizeof(unsigned int), 1, file);   // store the book number
	while (newBook != NULL) {
		fwrite(&(newBook->id), sizeof(unsigned int), 1, file);
		// store the length of title and itself
		len = strlen(newBook->title);  // obtain the length of title	
		fwrite(&(len), sizeof(int), 1, file);
		fwrite(newBook->title, sizeof(char), len, file);  // write title
		//    author
		len = strlen(newBook->authors);
		fwrite(&(len), sizeof(int), 1, file);
		fwrite(newBook->authors, sizeof(char), len, file);
		fwrite(&(newBook->year), sizeof(unsigned int), 2, file);
		newBook = newBook->next;
	}
	return 1;
}




int load_books(FILE* file) {
	char x;		//judge if there are extra bits
	int len, i;		//length of string
	Book* newBook;	// book node
	if (fread(&(library->length), sizeof(unsigned int), 1, file) == 0) {
		return 0;		//load the number of book
	}
	library->list = (Book*)malloc(sizeof(Book));
	newBook = library->list;
	for (i = 0; i < library->length; i++) {

		if (fread(&(newBook->id), sizeof(unsigned int), 1, file) == 0 ||
			fread(&(len), sizeof(int), 1, file) == 0) {	      //length of title
			return 0;
		}
		//allocate and initialize the space of title and load
		newBook->title = (char*)malloc(sizeof(char) * (len + 1));
		memset(newBook->title, '\0', len + 1);        //   initialize by '\0'
		if (fread(newBook->title, sizeof(char), len, file) == 0 ||
			fread(&(len), sizeof(int), 1, file) == 0) {
			return 0;
		}
		//author
		newBook->authors = (char*)malloc(sizeof(char) * (len + 1));
		memset(newBook->authors, '\0', len + 1);
		if (fread(newBook->authors, sizeof(char), len, file) == 0 ||
			fread(&(newBook->year), sizeof(unsigned int), 2, file) == 0) {
			return 0;
		}
		if (i == library->length - 1) {
			newBook->next = NULL;
			break;
		}
		else {
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
		}
	}
	if (fread(&x, sizeof(char), 1, file) != 0) {
		return 0;
	}
	return 1;
}




//copy a Book struct from source to an empty Book struct destination
void copyNode(Book* destination, Book* source) {
	int len;	// length of string
	destination->id = source->id;
	//allocate and initialize the space and copy
	len = strlen(source->title);
	destination->title = (char*)malloc(sizeof(char) * (len + 1));
	memset(destination->title, '\0', len + 1);
	strcpy(destination->title, source->title);

	len = strlen(source->authors);
	destination->authors = (char*)malloc(sizeof(char) * (len + 1));
	memset(destination->authors, '\0', len + 1);
	strcpy(destination->authors, source->authors);

	destination->year = source->year;
	destination->copies = source->copies;
	destination->next = NULL;
}



int add_book(Book book) {
	int len;	//length of string
	Book* newBook = library->list;	// find the last node
	char id[100], year[100], copies[100], title[100], author[100];	//recive the entering
	memset(id, '\0', 10);		
	memset(year, '\0', 10);
	memset(copies, '\0', 10);
	memset(title, '\0', 100);
	memset(author, '\0', 100);
	//judge if the ID is valid
	printf("\nPlease enter the ID: ");
	scanf("%[^\n]s", id);
	getchar();
	if (checkID(id)) {
		printf("\033[47;31mInvalid Id, fail to add.\033[0m\n");
		printf("Expected ID: a number less than 5 digits. Don't start with 0,\ndon't start or end with a space.\n");
		return 0;
	}
	else if (findBook(library->list, covertInt(id)) != NULL) {
		printf("\033[47;31mThe ID has existed, fail to add.\033[0m\n");
		return 0;
	}
	else {
		book.id = covertInt(id);
	}
	//judge if the title is valid
	printf("Please enter the title: ");
	scanf("%[^\n]s", title);
	getchar();
	if (!(ifStrValid(title, strlen(title)))) {
		printf("\033[47;31mIvalid title, fail to add.\033[0m\n");
		printf("Expected title: consists of letters and spaces, don't have multiple\nspaces connected, don't start or end with a space.\n");
		return 0;
	}
	//judge if the author is valid
	printf("Please enter the author: ");
	scanf("%[^\n]s", author);
	getchar();
	if (!(ifStrValid(author, strlen(author)))) {
		printf("\033[47;31mIvalid author, fail to add.\033[0m\n");
		printf("Expected author: consists of letters and spaces, don't have multiple\nspaces connected, don't start or end with a space.\n");
		return 0;
	}
	//judge if the year is valid
	printf("Please enter the year: ");
	scanf("%[^\n]s", year);
	getchar();
	if (checkID(year)) {
		printf("\033[47;31mInvalid year, fail to add.\033[0m\n");
		printf("Expected year: a nummber less than 2022. Don't start with 0,\ndon't start or end with a space. \n");
		return 0;
	}
	else {
		book.year = covertInt(year);
		if (book.year > 2022) {
			printf("\033[47;31mInvalid year, fail to add.\033[0m\n");
			printf("Expected year: a nummber less than 2022. Don't start with 0,\ndon't start or end with a space.\n");
			return 0;
		}
	}
	//judge if the copies is valid
	printf("Please enter the copies (Less than 1000): ");
	scanf("%[^\n]s", copies);
	getchar();
	if (checkID(copies)) {
		printf("\033[47;31mInvalid copies, fail to add.\033[0m\n");
		printf("Expected copies: a number less than 10000. Don't start with 0,\ndon't start or end with a space. \n");
		return 0;
	}
	else {
		book.copies = covertInt(copies);
		if (book.copies >= 1000) {
			printf("Invalid copies, fail to add.\n");
			printf("Expected copies: a number less than 1000. Don't start with 0,\ndon't start or end with a space. \n");
			return 0;
		}
	}
	// find the last node and add
	while (newBook->next != NULL) {
		newBook = newBook->next;
	}
	newBook->next = (Book*)malloc(sizeof(Book));
	newBook = newBook->next;
	newBook->id = book.id;
	len = strlen(title);
	newBook->title = (char*)malloc(sizeof(char) * (len + 1));
	memset(newBook->title, '\0', len + 1);
	strcpy(newBook->title, title);
	len = strlen(author);
	newBook->authors = (char*)malloc(sizeof(char) * (len + 1));
	memset(newBook->authors, '\0', len + 1);
	strcpy(newBook->authors, author);
	newBook->year = book.year;
	newBook->copies = book.copies;
	newBook->next = NULL;
	library->length += 1;
	printf("\nAdd book successfully!\n");
	return 1;
}



int remove_book(Book book) {
	char id[100];	//recive id
	//point to the node need to be removed so that can free the space after deleting it from list
	Book* temp;		
	Book* newBook = library->list;	//query which node need be removed
	memset(id, '\0', 100);
	printBook(library);
	printf("\nPlease enter the ID you want to remove: ");
	scanf("%[^\n]s", id);
	getchar();
	if (checkID(id)) {
		printf("\033[47;31mInvalid ID, fail to remove.\033[0m\n");
		printf("Expected ID: a number less than 5 digits. Don't start with 0,\ndon't start or end with a space.\n");
		return 0;
	}
	else {
		book.id = covertInt(id);
	}
	// find the first node
	if (newBook->next == NULL) {
		if (newBook->id == book.id) {
			library->length -= 1;
			library->list = NULL;
			freeNode(newBook);
			printf("\nRevome successfully!\n");
			return 1;
		}
		else {
			printf("\033[47;31mThe book doesn't exist.\033[0m\n");
			return 0;
		}
	}
	else {
		if (newBook->id == book.id) {
			library->length -= 1;
			library->list = newBook->next;
			freeNode(newBook);
			printf("\nRevome successfully!\n");
			return 1;
		}
		// if is the last node
		while (newBook->next != NULL) {
			if (newBook->next->id == book.id) {
				if (newBook->next->next == NULL) {
					library->length -= 1;
					freeNode(newBook->next);
					newBook->next = NULL;
					printf("\nRevome successfully!\n");
					return 1;
				}
				else {
					// if the node is among the list
					library->length -= 1;
					temp = newBook->next;
					newBook->next = newBook->next->next;
					freeNode(temp);
					printf("\nRevome successfully!\n");
					return 1;
				}

			}
			newBook = newBook->next;
		}
		printf("\033[47;31mThe book doesn't exist.\033[0m\n");
		return 0;
	}
}



BookList find_book_by_title(const char* title) {
	int num = 0; //the number of the matched book 
	BookList* res = (BookList*)malloc(sizeof(BookList));	//the result book list
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;
	newBook->next = NULL;
	// query the library book list and copy 
	Book* query = library->list;	//used to match books in the library
	while (query != NULL) {
		if (!strcmp(query->title, title)) {
			copyNode(newBook, query);
			num++;
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
			newBook->next = NULL;
		}
		query = query->next;
	}
	//    mark the last node
	res->length = num;
	newBook->authors = (char*)malloc(sizeof(char));
	newBook->title = (char*)malloc(sizeof(char));
	return *res;
}



BookList find_book_by_author(const char* author) {
	int num = 0;	//the number of the matched book
	BookList* res = (BookList*)malloc(sizeof(BookList));	//the result book list
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;	
	newBook->next = NULL;
	// query the library book list and copy 
	Book* query = library->list;	//used to match books in the library
	while (query != NULL) {
		if (!strcmp(query->authors, author)) {
			copyNode(newBook, query);
			num++;
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
			newBook->next = NULL;
		}
		query = query->next;
	}
	//    mark the last node
	res->length = num;
	newBook->authors = (char*)malloc(sizeof(char));
	newBook->title = (char*)malloc(sizeof(char));
	return *res;
}



BookList find_book_by_year(unsigned int year) {
	int num = 0;	//the number of the matched book
	BookList* res = (BookList*)malloc(sizeof(BookList));	//the result book list
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;
	newBook->next = NULL;
	// query the library book list and copy 
	Book* query = library->list;	//used to match books in the library
	while (query != NULL) {
		if (query->year == year) {
			copyNode(newBook, query);
			num++;
			newBook->next = (Book*)malloc(sizeof(Book));
			newBook = newBook->next;
			newBook->next = NULL;
		}
		query = query->next;
	}
	//    mark the last node
	res->length = num;
	newBook->authors = (char*)malloc(sizeof(char));
	newBook->title = (char*)malloc(sizeof(char));
	return *res;
}