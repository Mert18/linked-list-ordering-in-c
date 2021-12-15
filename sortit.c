#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining the Node structure. I used an extra 'code' variable to handle ordering.
struct node {
    char data[100];
    int code;
    struct node *next;
};
// Decided to use global head pointer.
struct node *head;

// Insert function
void insert(char x[], int code) {

  // Preparing our newly created node, filling it with values(in the next few lines).
  struct node *ptr = malloc(sizeof(struct node));
  // I couldn't just do ptr->data = x, It gave an error because we are playing with strings and pointers, Since strings are hold in array type, we cannot presume their size, their size is determined in initialization phase, while we're ahead of it, we need an assignment here, so it is done by 'strcpy' string function.
  strcpy(ptr->data, x);
  ptr->code = code;
  ptr->next = NULL;
  
  // Used for traversing the list, finding a favorable location.
  struct node *temp = head;
  
  // If head is null,(linked list is empty, head pointer shows nowhere), insert our node here.
  if(head == NULL){
    head = ptr;
  }else{
    // If temp is null, It cannot have a 'next' so it gives segmentation error.
    if(temp != NULL){
      // Traversing the linked list until we encounter a code value in the next node that has a code value less than our given code value.
      // That means we need to insert value on between these nodes.
      while(temp->next && temp->next->code <= code){
        // If the next node not a duplicate record, go to next node.
        if(temp->next->code != code){
          temp = temp->next;
        }else{
          // If temp->next->code equals to code, it is a duplicate record. We skip this line.
          return;
        }
      }
      // After we reached the proper location, we insert our node here.
      ptr->next = temp->next;
      temp->next = ptr;
    }
  }
}

void printlist() {
    // We get the head node and assign it to temp, we will use it to traverse the list.
    struct node* temp = head;

    // In every line, while we are printing the line to the console, the line will be printed to Sorted.dat file too.
    FILE *fptr;
    fptr = fopen("Sorted.dat", "w");

    // If the file cannot be created and our file pointer is null, return error.
    if(fptr == NULL){
      printf("Error!");
      exit(1);
    }

    printf("_____________LINKED LIST_______________\n\n");

    //Traverse the list until there is none node left.
    while (temp!= NULL) {
      // Print the line into the console.
      printf("%s\n", temp->data);
      // Print the line into the file.
      fprintf(fptr, "%s\n", temp->data);
      // Go to next node.
      temp = temp->next;
      
    }
    // Close the file after we get our work done.
    fclose(fptr);
}

int main(){
  // Stores every line temporarily.
  char line[100];

  // Needed pointer to read lines from the Data.dat file.
  FILE *fileptr;
  fileptr = fopen("Data.dat", "r");

  // If the file cannot be read, return an error.
  if(fileptr == NULL){
    perror("Cannot open the file.");
    exit(1);
  }

  // Until the end of every line, get words.
  while(fgets(line, sizeof(line), fileptr)){

   // Copying the course code at the end of the line.
   char courseCode[4] = {line[strlen(line) -5], line[strlen(line) -4], line[strlen(line) -3] };

   // Emptying the course code from the line. (including unnecessary spaces that's why we do it 5 times.)
   line[strlen(line)-1] = '\0';
   line[strlen(line)-1] = '\0';
   line[strlen(line)-1] = '\0';
   line[strlen(line)-1] = '\0';
   line[strlen(line)-1] = '\0';

   //Defined a new line to store brand new string.
   char newLine[200];

   // It shows a weird symbol at the beginning If I remove this line :)
   newLine[0] = '\0';

   // Adding course code beginning of the string and line after it.
   strcat(newLine, courseCode);
   strcat(newLine, "    ");
   strcat(newLine, line);


   //Converting course code into integer because we will use it for ordering.
   int code = atoi(courseCode);

   // Inserting our node into the linked list.
   insert(newLine, code);

   //Emptying the string, leaving space for the next line.
   newLine[0] = '\0';

  }

  // Printing the lines to the console and the file.
  printlist();

  // Closing the file after we got our work done.
  fclose(fileptr);

  return 0;
}

