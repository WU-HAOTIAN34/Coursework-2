#define _CRT_SECURE_NO_WARNINGS
#include "book_management.h"
#include "interface.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "librarian.h"
#include "user.h"



int store_books(FILE* file) {
	int len;
	Book* newBook = library->list;
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
	char x;
	int len, i;
	Book* newBook;
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
	int len;
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
	int len;
	Book* newBook = library->list;
	char id[100], year[100], copies[100], title[100], author[100];
	memset(id, '\0', 10);
	memset(year, '\0', 10);
	memset(copies, '\0', 10);
	memset(title, '\0', 100);
	memset(author, '\0', 100);
	//judge if the ID is valid
	printf("\nPlease enter the ID: ");
	scanf("%[^\n]s", id);
	getchar();
	if ((int)id[0] == 48 || strspn(id, "0123456789") != strlen(id) || strlen(id) >= 5 || strlen(id) <= 0) {
		printf("\033[47;31mInvalid Id, fail to add.\033[0m\n");
		printf("Expected ID: consist of less than 5 digits number, and don't start with 0.\n");
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
		printf("Expected title: consist of characters and spaces,no more than one space is connected,\nno space at the beginning or end.\n");
		return 0;
	}
	//judge if the author is valid
	printf("Please enter the author: ");
	scanf("%[^\n]s", author);
	getchar();
	if (!(ifStrValid(author, strlen(author)))) {
		printf("\033[47;31mIvalid author, fail to add.\033[0m\n");
		printf("Expected author: consist of characters and spaces,no more than one space is connected,\nno space at the beginning or end.\n");
		return 0;
	}
	//judge if the year is valid
	printf("Please enter the year: ");
	scanf("%[^\n]s", year);
	getchar();
	if ((int)year[0] == 48 || strspn(year, "0123456789") != strlen(year) || strlen(year) >= 5 ||
		strlen(year) <= 0) {
		printf("\033[47;31mInvalid year, fail to add.\033[0m\n");
		printf("Expected year: consist of less than 5 digits number, less than 2022 and don't begin with 0. \n");
		return 0;
	}
	else {
		book.year = covertInt(year);
		if (book.year > 2022) {
			printf("\033[47;31mInvalid year, fail to add.\033[0m\n");
			printf("Expected year: consist of less than 5 digits number, less than 2022 and don't begin with 0.\n");
			return 0;
		}
	}
	//judge if the copies is valid
	printf("Please enter the copies (Less than 1000): ");
	scanf("%[^\n]s", copies);
	getchar();
	if ((int)copies[0] == 48 || strspn(copies, "0123456789") != strlen(copies) ||
		strlen(copies) >= 4 || strlen(copies) <= 0) {
		printf("\033[47;31mInvalid copies, fail to add.\033[0m\n");
		printf("Expected copies: less than 1000 and don't begin with 0. \n");
		return 0;
	}
	else {
		book.copies = covertInt(copies);
		if (book.copies >= 1000) {
			printf("Invalid copies, fail to add.\n");
			printf("Expected copies: less than 1000 and don't begin with 0. \n");
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
	char id[100];
	Book* temp;
	Book* newBook = library->list;
	memset(id, '\0', 100);
	printf("\nPlease enter the ID you want to remove: ");
	scanf("%[^\n]s", id);
	getchar();
	if ((int)id[0] == 48 || strspn(id, "0123456789") != strlen(id) || strlen(id) >= 5 || strlen(id) <= 0) {
		printf("\033[47;31mInvalid ID.\033[0m\n");
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
	int i, len;
	int num = 0;
	BookList* res = (BookList*)malloc(sizeof(BookList));
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;
	newBook->next = NULL;
	// query the library book list and copy 
	Book* query = library->list;
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
	int i, len;
	int num = 0;
	BookList* res = (BookList*)malloc(sizeof(BookList));
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;
	newBook->next = NULL;
	// query the library book list and copy 
	Book* query = library->list;
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
	int i, len;
	int num = 0;
	BookList* res = (BookList*)malloc(sizeof(BookList));
	res->list = (Book*)malloc(sizeof(Book));
	Book* newBook = res->list;
	newBook->next = NULL;
	// query the library book list and copy 
	Book* query = library->list;
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