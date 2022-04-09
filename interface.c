#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "book_management.h"
#include "librarian.h"
#include "user.h"


// covert a string which contains some character number into int number
int covertInt(char* str) {
	int i, j, k = 1;
	int len = strlen(str);
	int res = 0;
	// calculate each digit of number
	for (i = 0; i < len; i++) {
		for (j = 0; j < len - i - 1; j++) {
			k *= 10;
		}
		res += ((int)str[i] - 48) * k;
		k = 1;
	}
	return res;
}



//judge if the string is valid
//a valid string consists of letters. Don't have contiguous Spaces, 
//don't begin or end with space  
int ifStrValid(char* str, int len) {
	int i, a;
			// can't begin or end with space
	if (str[0] == ' ' || len == 0 || str[len - 1] == ' ') {
		return 0;
	}
	for (i = 0; i < len; i++) {
		a = (int)str[i];
		//judge if consists of letter
		if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122)) {
			continue;
		}                                  
		if (str[i] == ' ' && str[i + 1] != ' ') {
			continue;             // can't exist two connected spaces
		}
		return 0;
	}
	return 1;
}





// load the imformation of users 
// return 0 if the file has been modified or corrupted
int loadUser(FILE* file) {
	char x;    // judge if there are extra bits
	int i, j, len;    // len load the length of string  
	Book* newBook;	  // the node of each book
	member->list = (user*)malloc(sizeof(user));
	user* newUser = member->list;	//the node of each user
	// load the number of user
	if (fread(&(member->userNum), sizeof(int), 1, file) == 0) {
		return 0;
	}
	for (i = 0; i < member->userNum; i++) {
		// the information of the user
		if (fread(&len, sizeof(int), 1, file) == 0) {
			return 0;					// length of ID
		}
		newUser->ID = (char*)malloc(sizeof(char) * (len + 1));
		memset(newUser->ID, '\0', len + 1);
		memset(newUser->password, '\0', 9);

		if (fread(newUser->ID, sizeof(char), len, file) == 0 ||
			fread(newUser->password, sizeof(char), 8, file) == 0 ||
			fread(&(newUser->bookNum), sizeof(int), 1, file) == 0) {
			return 0;
		}
		//load the user's borrowed books
		if (newUser->bookNum == 0) {
			newUser->broBook = NULL;
		}
		else {
			newUser->broBook = (Book*)malloc(sizeof(Book));
			newBook = newUser->broBook;
			for (j = 0; j < newUser->bookNum; j++) {
				//allocate and initialize the space of title and load
				if (fread(&(newBook->id), sizeof(unsigned int), 1, file) == 0 ||
					fread(&(len), sizeof(int), 1, file) == 0) {          // title length
					return 0;
				}
				newBook->title = (char*)malloc(sizeof(char) * (len + 1));
				memset(newBook->title, '\0', len + 1);      // fill in \0 to initialize
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
	if (fread(&x, sizeof(char), 1, file) != 0) {
		return 0;
	}
	return 1;
}



// store the imformation of user to the file
int storeUser(FILE* file) {

	int len;	// the length of string
	Book* newBook;   // book node
	user* newUser = member->list;	//user node
	fwrite(&(member->userNum), sizeof(int), 1, file);
	while (newUser != NULL) {
		// store user's information
		len = strlen(newUser->ID);
		fwrite(&len, sizeof(int), 1, file);      // obtain and storethe length of id
		fwrite(newUser->ID, sizeof(char), len, file);
		//store password and book number
		fwrite(newUser->password, sizeof(char), 8, file);
		fwrite(&(newUser->bookNum), sizeof(int), 1, file);
		// store the borrowed book information
		if (newUser->bookNum != 0) {
			newBook = newUser->broBook;
			while (newBook != NULL) {
				fwrite(&(newBook->id), sizeof(unsigned int), 1, file);
				len = strlen(newBook->title);  // obtain the length of title
				// store the length because loading the title need to know the length of the string		
				fwrite(&(len), sizeof(int), 1, file);
				fwrite(newBook->title, sizeof(char), len, file);
				//    author
				len = strlen(newBook->authors);
				fwrite(&(len), sizeof(int), 1, file);
				fwrite(newBook->authors, sizeof(char), len, file);
				fwrite(&(newBook->year), sizeof(unsigned int), 2, file);
				newBook = newBook->next;
			}
		}
		newUser = newUser->next;
	}
	return 1;
}



// print the book list 
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




// the register a user 
int registerModel() {
	int len;		//length of string
	char ID[100];	// recive id
	char password[100]; // recive password
	memset(ID, '\0', 100);
	memset(password, '\0', 100);
	user* newUser = member->list;	// find the last node
	// judge if is a valid ID
	printf("\nPlease enter your ID (Consists of letters): ");
	scanf("%[^\n]s", ID);
	getchar();
	if (!ifStrValid(ID, strlen(ID))) {
		printf("\033[47;31mInvalid ID, fail to register.\033[0m\n");
		printf("Expected ID: consists of letters and spaces, don't have multiple\nspaces connected, don't start or end with a space.\n");
		return 0;
	}
	while (newUser->next != NULL) {
		if (!strcmp(newUser->ID, ID)) {
			printf("\033[47;31mThe ID has existed, fail to register.\033[0m\n");
			return 0;
		}
		newUser = newUser->next;
	}
	// compare with the last node
	if (!strcmp(newUser->ID, ID)) {
		printf("\033[47;31mThe ID has existed, fail to register.\033[0m\n");
		return 0;
	}
	printf("Please enter your password (8-digit-number): ");
	scanf("%[^\n]s", password);
	getchar();
	if (!(strspn(password, "0123456789") == strlen(password) && strlen(password) == 8)) {
		printf("\033[47;31mInvalid password, fail to register.\033[0m\n");
		printf("Expected password: an 8-digit number, don't start or end with a space.\n");
		return 0;
	}
	// store the imformation of new user
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




// used for user login
int signModel() {
	char ID[100];		// recive id
	char password[100];	// recive password
	memset(ID, '\0', 100);
	memset(password, '\0', 100);
	user* newUser = member->list;	// match user
	printf("\nPlease enter your ID: ");
	scanf("%[^\n]s", ID);
	getchar();
	while (newUser != NULL) {
		if (!strcmp(newUser->ID, ID)) {
			printf("Please enter your password (8-digit-number): ");
			scanf("%[^\n]s", password);
			getchar();
			if (!strcmp(password, newUser->password)) {
				printf("\nLogin successfully!\n");
				// judge is a common user or the librarian
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
				printf("\033[47;31mIcorrect password, fail to login.\033[0m\n");
				return 0;
			}
		}
		newUser = newUser->next;
	}
	printf("\033[47;31mThe ID doesn't exist, fail to login.\033[0m\n");
	return 0;
}




// print the interface of the program
void interface() {
	char enter[100];	//recive entering 
	int option = 0;		// obtain the correct character
	memset(enter, '\0', 100);

	// option
	while (option != 5) {
		printf("\nPlease choose an option: \n\n1. Register an account\n2. Login\n");
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
			default:
				break;
			}
		}
	}
	return;
}