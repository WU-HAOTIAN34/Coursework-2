#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "book_management.h"


int covertInt(char* str) {
	int i;
	int len = strlen(str);
	int res = 0;
	for (i = 0; i < len; i++) {
		res += ((int)str[i] - 48) * pow(10, len - i - 1);
	}
	return res;
}


int ifStrValid(char* str, int len) {
	int i, a;
	if (str[0] == ' ' || len == 0) {
		return 0;
	}
	for (i = 0; i < len; i++) {
		a = (int)str[i];
		if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122)) {
			continue;
		}
		if (str[i] == ' ' && str[i + 1] != ' ') {
			continue;
		}
		return 0;
	}
	return 1;
}





int loadUser(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	int i, j, len;
	Book* newBook;
	member->list = (user*)malloc(sizeof(user));
	user* newUser = member->list;
	fread(&(member->userNum), sizeof(int), 1, file);
	for (i = 0; i < member->userNum; i++) {
		fread(&len, sizeof(int), 1, file);     // load the length of ID
		//copy ID
		newUser->ID = (char*)malloc(sizeof(char) * (len + 1));
		memset(newUser->ID, '\0', len + 1);
		fread(newUser->ID, sizeof(char), len, file);
		//load password and borrowed book number
		memset(newUser->password, '\0', 9);
		fread(newUser->password, sizeof(char), 8, file);
		fread(&(newUser->bookNum), sizeof(int), 1, file);
		         //load borrowed books
		if (newUser->bookNum == 0) {
			newUser->broBook = NULL;
		}
		else {
			newUser->broBook = (Book*)malloc(sizeof(Book));
			newBook = newUser->broBook;
			for (j = 0; j < newUser->bookNum; j++) {
				//load book id
				fread(&(newBook->id), sizeof(unsigned int), 1, file);
				// load title
				fread(&(len), sizeof(int), 1, file);        // obtain the length of title
				newBook->title = (char*)malloc(sizeof(char) * (len + 1));
				memset(newBook->title, '\0', len + 1);      // fill in \0 to initialize
				fread(newBook->title, sizeof(char), len, file);  //load
				// load author
				fread(&(len), sizeof(int), 1, file);
				newBook->authors = (char*)malloc(sizeof(char) * (len + 1));
				memset(newBook->authors, '\0', len + 1);
				fread(newBook->authors, sizeof(char), len, file);
				// year and copies
				fread(&(newBook->year), sizeof(unsigned int), 2, file);
				//judge if is the last member
				if (j == newUser->bookNum - 1) {
					newBook->next = NULL;
					break;
				}
				else {
					newBook->next = (Book*)malloc(sizeof(Book));
					newBook = newBook->next;
				}
			}
		}
		//judge if is the last member
		if (i == member->userNum - 1) {
			newUser->next = NULL;
			break;
		}
		else {
			newUser->next = (user*)malloc(sizeof(user));
			newUser = newUser->next;
		}
	}
	return 1;
}



int storeUser(FILE* file) {
	if (file == NULL) {
		return 0;
	}
	int i, j, len;
	Book* newBook;
	user* newUser = member->list;
	fwrite(&(member->userNum), sizeof(int), 1, file);
	while (newUser != NULL) {
		// write user's id
		len = strlen(newUser->ID);   // obtain the length of id
		// store length
		fwrite(&len, sizeof(int), 1, file); 
		fwrite(newUser->ID, sizeof(char), len, file);  //store id
		//store password and book number
		fwrite(newUser->password, sizeof(char), 8, file);
		fwrite(&(newUser->bookNum), sizeof(int), 1, file);
		// store the borrowed book information
		if (newUser->bookNum != 0) {
			newBook = newUser->broBook;
			while (newBook != NULL) {
				// write id
				fwrite(&(newBook->id), sizeof(unsigned int), 1, file);
				// write title
				len = strlen(newBook->title);  // obtain the length of title
				// write the length because loading the title need to know the length of the string		
				fwrite(&(len), sizeof(int), 1, file);
				fwrite(newBook->title, sizeof(char), len, file);  // write title
				//   write author
				len = strlen(newBook->authors);
				fwrite(&(len), sizeof(int), 1, file);
				fwrite(newBook->authors, sizeof(char), len, file);
				// year and copies
				fwrite(&(newBook->year), sizeof(unsigned int), 2, file);
				newBook = newBook->next;
			}
		}
		newUser = newUser->next;
	}
	return 1;
}




void printBook(Book* library) {
	Book* newBook = library->next;
	printf("\nID     Title                         Author               Year     Copies\n\n");
	while (newBook != NULL) {
		printf("%7d%30s%21s%9d%4d\n", newBook->id, newBook->title, 
			    newBook->authors, newBook->year, newBook->copies);
		newBook = newBook->next;
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