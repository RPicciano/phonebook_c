#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINES 200


// Creates a struct which will hold users and numbers in two arrays
typedef struct {
	char user[10][MAX_LINES];
	char num[25][MAX_LINES];
} data;

data entry; // Defines how struct data will be referenced throughout the code
int i = 0; // Will be used to assign a value to a specific spot in an array, and exit while loop
char line[50];
char *output[200]; // Pointer to output (will contain both user and # for future parsing)

void handle_info(){
	FILE *fptr = fopen("users.txt", "r"); // Opens file in 'read' mode

// While we are under the max_lines to read and data in the file is not empty

	while(i < MAX_LINES && fgets(line, sizeof(line), fptr) != NULL){
		output[i] = malloc(strlen(line) +1); // Dedicate memory to respective spot [i] in array output[]
		strcpy(output[i], line); // Copy the line fgets() acquired to a spot in the array

		char *token = strtok(output[i],":"); // Take the output, and copy the first part into pointer token, before the delimiter ":"

		if (token !=NULL){ // If the pointer is not empty...
			strncpy(entry.user[i], token, sizeof(entry.user[i])); // Copy the token to entry.user[i] using size 10
		}
		token = strtok(NULL, ":"); // Set token to the part AFTER the delimiter ":"

		if (token != NULL){
			strncpy(entry.num[i], token, sizeof(entry.num[i])); // Set token to entry.num[i] at size 25
		}
		printf("%s:%s\n", entry.user[i], entry.num[i]); // Print entry.user[i] and entry.num[i] seperated by a colon
		i++; // Increase the value of i by 1
	}
	fclose(fptr); // Close the 'fptr' (file pointer)
}

void write_data(char user[10], char num[25]){ // This function will require two parameters of type char, with specificied max_sizes
	FILE *fptr = fopen("users.txt", "r+"); // Open file (again) in READ mode
	long pos; // A larger int, with more memory (a little bit unneccessary in this case, but needed for larger files)

	while(fgets(line, sizeof(line), fptr)){ // While the system finds 'something' in the file....
		if (strcmp(line, "\n") == 0){ // If the read line contains characters "\n" (see printf in handle_info())
			break; // Exit the if statement
		}
		// Because of this while statement and the previous break statement, this guarantees that the last value to assign to the 
		// pos variable will be before the newline character, this assures that we are always making a newline before writing
		pos = ftell(fptr); // Send the position of the system in the file to our file pointer
	}
	fseek(fptr, pos, SEEK_SET); // Set the file to position held in variable pos
	fprintf(fptr, "%s:%s\n", user, num); // Print user and num to fptr in format user:num
	fflush(fptr); // Clear the buffer, allowing us to immediately write to file
	fclose(fptr); // Close the file
}

char name[10]; // These names are unneccessary, but they helped me
char phone[25]; // They will be used for our write_data function (they'll be entered as parameters)
int choice; // Will determine what function we run


void login(){

	printf("Welcome to the Phonebook Database!\n____________________________\n");
	printf("Please Enter One of the Following Options: \n");
	printf("[1] Read all users and respective phone numbers \n");
	printf("[2] Add new person and phone number \n");
	printf("[3] Quit\n\n");
	printf("Enter choice ID here: ");
	scanf("%d",&choice);


	if (choice == 1){ // If the user enters '1'
		char option;
		system("clear"); // Clear the terminal--MACOS ONLY!!
		handle_info(); // Call our handle_info() function, which will display users.txt
		printf("Ready to go back? Type Y: ");
		scanf("%s", &option); // Reads user input

		if (option =='Y'){ // If the user says 'Y' aka 'Yes'
			system("clear"); // Clear the terminal
			login(); // Initiate the login() function again
		} else { // Otherwise
			exit(0); // Quit 
		}
	}

	if (choice == 2){
		system("clear");
		printf("____________________________\n\n");
		printf("Enter Person Here: ");
		scanf("%s", name); // Gather user input and store it in the name variable
		printf("\nEnter Phone Here: " );
		scanf("%s", phone); // Gather user input and store it in the phone variable
		write_data(name, phone); // Pass the name and phone variable as parameters through write_data()
		system("clear");
		login(); // Call the login function again
	}
}


int main() // This function is required, anything in here will actually be executed. 
{
	login();
}