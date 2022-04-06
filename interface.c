#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "book_management.h"
#include "librarian.h"
#include "user.h"


int covertInt(char* str) {
	int i;
	int len = strlen(str);
	int res = 0;
	for (int i = 0; i < len; i++) {
		res += ((int)str[i] - 48) * (int)pow(10, len - i - 1);
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
	int len;
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




void printBook(BookList* book) {
	int i;
	Book* newBook = book->list;
	printf("\nID     Title                         Author               Year          Copies\n\n");
	for (i = 0; i < book->length; i++) {
		printf("%-7d%-30s%-21s%-14d%-4d\n", newBook->id, newBook->title,
			newBook->authors, newBook->year, newBook->copies);
		newBook = newBook->next;
	}
}





int registerModel() {
	int len;
	char ID[100];
	char password[100];
	memset(ID, '\0', 100);
	memset(password, '\0', 100);
	user* newUser = member->list;
	printf("Please enter your ID (Consists of letters): ");
	scanf("%[^\n]s", ID);
	if (!ifStrValid(ID, strlen(ID))) {
		printf("Invalid ID, fail to register.");
		return 0;
	}
	while (newUser->next != NULL) {
		if (!strcmp(newUser->ID, ID)) {
			printf("The ID has existed, fail to register.");
			return 0;
		}
		newUser = newUser->next;
	}
	if (!strcmp(newUser->ID, ID)) {
		printf("The ID has existed, fail to register.");
		return 0;
	}
	printf("Please enter your password (8-digit-number): ");
	scanf("%[^\n]s", password);
	if (!(strspn(password, "0123456789") == strlen(password) && strlen(password) == 8)) {
		printf("\nInvalid password, fail to register.\n");
		return 0;
	}
	newUser->next = (user*)malloc(sizeof(user));
	newUser = newUser->next;
	member->userNum += 1;
	newUser->next = NULL;
	len = strlen(ID);
	newUser->ID = (char*)malloc(sizeof(char) * (len + 1));
	memset(newUser->ID, '\0', len + 1);
	strcpy(newUser->ID, ID);
	memset(newUser->password, '\0', 9);
	strcpy(newUser->password, password);
	newUser->broBook = NULL;
	newUser->bookNum = 0;
	printf("\nCongratulations, you have registered successfully!\n");
	return 1;
}





int signModel() {
	char ID[100];
	char password[100];
	memset(ID, '\0', 100);
	memset(password, '\0', 100);
	user* newUser = member->list;
	printf("Please enter your ID: ");
	scanf("%[^\n]s", ID);
	getchar();
	while (newUser != NULL) {
		if (!strcmp(newUser->ID, ID)) {
			printf("Please enter your password (8-digit-number): ");
			scanf("%[^\n]s", password);
			if (!strcmp(password, newUser->password)) {
				printf("\nLogin successfully!\n");
				if (!strcmp(newUser->ID, "librarian")) {
					librarianModel();
					return 1;
				}
				else {
					userModel(newUser);
					return 1;
				}
			}
			else {
				printf("Icorrect password, fail to login.\n");
			}
		}
		newUser = newUser->next;
	}
	printf("The ID doesn't exist, fail to login.\n");
	return 0;
}





void interface() {
	FILE* fp;
	char enter[100];
	int option = 0;
	memset(enter, '\0', 100);
	//        load book list and user list
	member = (userList*)malloc(sizeof(userList));
	library = (BookList*)malloc(sizeof(BookList));
	fp = fopen("book.txt", "rb");
	load_books(fp);
	fclose(fp);
	fp = fopen("user.txt", "rb");
	loadUser(fp);
	fclose(fp);
	fp = NULL;
	// option
	while (option != 5) {
		printf("\nPlease choose an option: \n\n1. Register an account\n2. Login\n");
		printf("3. Search for books\n4. Display all books\n5. Quit\nOption: ");
		scanf("%s", enter);
		getchar();
		option = (int)enter[0];
		if (strlen(enter) > 1 || option <= 48 || option >= 54) {
			printf("\033[47;31mSorry, the option you entered was invalid, please try again.\033[0m");
		}
		else {
			option -= 48;
			switch (option)
			{
			case 1:
				registerModel();
				break;
			case 2:
				signModel();
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