#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 10
#define FILE_NAME "student grade.txt"
typedef struct {
	char name[NAME_LEN + 1];//full name
	int number;				//Student number
	int sanskrit;			//sanskrit
	int math;				//mathematics
	int english;			//English
	int average;			//average
	int sum;				//Total score
} student;					//Used to store information about individual students
typedef struct node {
	student stu;		//Data field to store student information
	struct node *next;	//Pointer field, pointing to the next node
} studentNode;			//Student node
typedef struct {
	studentNode *head;	//Head pointer
	studentNode *tail;	//Tail pointer
	int count;			//Total number of student nodes
} studentList;			//Student list
void initialize(studentList *L);//Initialize the list, create the header node
void enter(studentList *L);		//Enter linked list
void display(studentList *L);	//Output linked list
void find(studentList *L);		//Find a node
void modify(studentList *L);	//Modify a node
void sort(studentList *L);		//Rebuild the table in descending order and output
void write(studentList *L);		//Write files to free up space while writing
void read(studentList *L);		//Read files and create tables while reading
int main() {
	//Interactive interface
	printf("		*********Student achievement management system*********\n");
	printf("		*  1.Enter new student grades                      *\n");
	printf("		*  2.Modify student grades by name                    *\n");
	printf("		*  3.Query student scores by name                    *\n");
	printf("		*  4.Output the results of all students                    *\n");
	printf("		*  5.Output student scores by average                  *\n");
	printf("		*  6.Exit student achievement management system                  *\n");
	printf("		********************************************\n");
	printf("  	                                                \n");
	//Create student linked list
	studentList *L = (studentList *)malloc(sizeof(studentList));
	//Initialize student linked list
	initialize(L);
	//Read data from file to linked list
	read(L);
	//The interactive interface is written with an infinite loop and a switch
	while (1) {
		int code;
		printf("Please enter the number corresponding to the operation you want to perform: ");
		scanf("%d", &code);
		switch (code) {
			case 1:
				enter(L);
				break;
			case 2:
				modify(L);
				break;
			case 3:
				find(L);
				break;
			case 4:
				display(L);
				break;
			case 5:
				sort(L);
				break;
			case 6:
				write(L);
				free(L->head);	//The header node is destroyed
				free(L);		//The linked list was destroyed
				return 0;
			default:
				printf("%d Is an invalid number, please re-enter!\n\n", code);
				break;
		}
	}
	return 0;
}
void initialize(studentList *L) {
	//Create header node
	studentNode *s = (studentNode *)malloc(sizeof(studentNode));
	s->next = NULL;
	//Initialize linked list:
	//The head and tail pointers refer to the head node, and the initial length is zero
	L->head = s;
	L->tail = s;
	L->count = 0;
}
void enter(studentList *L) {
	//Create a new node
	studentNode *s = (studentNode *)malloc(sizeof(studentNode));
	//Type information into the new node
	printf("Please enter student name:");
	scanf("%s", s->stu.name);
	printf("Please enter student ID:");
	scanf("%d", &s->stu.number);
	printf("Please enter your language score:");
	scanf("%d", &s->stu.sanskrit);
	printf("Please enter your math score:");
	scanf("%d", &s->stu.math);
	printf("Please enter your English score:");
	scanf("%d", &s->stu.english);
	s->stu.sum = s->stu.sanskrit + s->stu.math + s->stu.english;
	s->stu.average = s->stu.sum / 3;
	//If the linked list is empty, point the tail pointer to the new node
	if (L->head == L->tail) {
		L->tail = s;
	}
	//Insert the new node into the head of the linked list (head insertion method)
	s->next = L->head->next;
	L->head->next = s;
	L->count++;
	//Output interactive information
	printf("Information entered successfully!\n\n");
}
void display(studentList *L) {
	printf("share%d Group student data:\n", L->count);
	printf("full name\t\t Student number\t\t sanskrit\t\t mathematics\t\t English\t\t Total score\t\t average\n");
	//Create a node pointer to the head node
	studentNode *p;
	p = L->head;
	//Traversal list output
	while (p->next) {
		p = p->next;
		printf("%s", p->stu.name);
		printf("\t\t%d", p->stu.number);
		printf("\t\t%d", p->stu.sanskrit);
		printf("\t\t%d", p->stu.math);
		printf("\t\t%d", p->stu.english);
		printf("\t\t%d", p->stu.sum);
		printf("\t\t%d", p->stu.average);
		printf("\n");
	}
	printf("\n");
}
void find(studentList *L) {
	//Let the user enter the student to find
	printf("Please enter student name:");
	char name[NAME_LEN + 1];
	scanf("%s", name);
	//Traverse the linked list and compare names
	studentNode *p = L->head->next;
	while (p) {
		//If it matches, output and end the function
		if (strcmp(p->stu.name, name) == 0) {
			printf("full name\t\t Student number\t\t chinese\t\t mathematics\t\t English\t\t Total score\t\t average\n");
			printf("%s", p->stu.name);
			printf("\t\t%d", p->stu.number);
			printf("\t\t%d", p->stu.sanskrit);
			printf("\t\t%d", p->stu.math);
			printf("\t\t%d", p->stu.english);
			printf("\t\t%d", p->stu.sum);
			printf("\t\t%d", p->stu.average);
			printf("\n\n");
			return;
		}
		//If the name doesn't match, it's next
		p = p->next;
	}
	//I didn't find the name in the traversal
	printf("I didn't find this%s Information!\n\n", name);
}
void modify(studentList *L) {
	//Let the user enter the student to modify
	printf("Please enter student name:");
	char name[NAME_LEN + 1];
	scanf("%s", name);
	//Traverse the linked list and compare names
	studentNode *p = L->head->next;
	while (p) {
		//If yes, let the user retype and end the function
		if (strcmp(p->stu.name, name) == 0) {
			printf("Please re-enter the information:\n");
			printf("Please enter student ID:");
			scanf("%d", &p->stu.number);
			printf("Please enter your language score:");
			scanf("%d", &p->stu.sanskrit);
			printf("Please enter your math score:");
			scanf("%d", &p->stu.math);
			printf("Please enter your English score:");
			scanf("%d", &p->stu.english);
			p->stu.sum = p->stu.sanskrit + p->stu.math + p->stu.english;
			p->stu.average = p->stu.sum / 3;
			printf("Information modified successfully!\n\n");
			return;
		}
		//If the name doesn't match, it's next
		p = p->next;
	}
	//I didn't find the name in the traversal
	printf("I didn't find this%s Information!\n\n", name);
}
void sort(studentList *L) {
	//Neither node is in order
	if (L->count < 2) {
		printf("List sorting completed!\n");
		display(L);
		return;
	}
	//Insert sort
	studentNode *p, *pre, *tmp;
	//p points to the second student node
	p = L->head->next;
	//The linked list is disconnected from the head node and the first student node
	L->head->next = NULL;
	//Cycle back from the first student node
	while (p) {
		//Save the pointer of the next node
		tmp = p->next;
		//Find insertion location
		pre = L->head;
		while (pre->next != NULL && pre->next->stu.average > p->stu.average)
			pre = pre->next;
		//Update tail pointer
		if (pre->next == NULL) {
			L->tail = p;
		}
		//insert
		p->next = pre->next;
		pre->next = p;
		//Skip to next
		p = tmp;
	}
	printf("List sorting completed!\n");
	display(L);
}
void write(studentList *L) {
	//Open file flow
	FILE *fp = fopen(FILE_NAME, "w");
	if (fp == NULL) {
		printf("file%s Open failed\n", FILE_NAME);
		exit(EXIT_FAILURE);
	}
	//Output the total number of student nodes on the first line
	fprintf(fp, "%d\n", L->count);
	//Create a node pointer to the head node
	studentNode *p;
	p = L->head->next;
	//Traverse the linked list and output a set of data as a row
	while (p) {
		fprintf(fp, "%s ", p->stu.name);
		fprintf(fp, "%d ", p->stu.number);
		fprintf(fp, "%d ", p->stu.sanskrit);
		fprintf(fp, "%d ", p->stu.math);
		fprintf(fp, "%d ", p->stu.english);
		fprintf(fp, "%d ", p->stu.sum);
		fprintf(fp, "%d ", p->stu.average);
		fprintf(fp, "\n");
		//Free node space after output
		studentNode *next = p->next;
		free(p);
		p = next;
	}
	//Close file stream
	fclose(fp);
	//Interactive information
	printf("Data saved! Thanks for using. Bye!\n");
}
void read(studentList *L) {
	//Open file stream
	FILE *fp = fopen(FILE_NAME, "r");
	if (fp == NULL) {
		printf("file%s Open failed\n", FILE_NAME);
		exit(EXIT_FAILURE);
	}
	//Read the total number of student nodes in the first row
	fscanf(fp, "%d", &L->count);
	//The data is read circularly, and the number of cycles is count
	for (int i = 1; i <= L->count; i++) {
		//Create a new node
		studentNode *s = (studentNode *)malloc(sizeof(studentNode));
		//Read data
		fscanf(fp, "%s ", s->stu.name);
		fscanf(fp, "%d ", &s->stu.number);
		fscanf(fp, "%d ", &s->stu.sanskrit);
		fscanf(fp, "%d ", &s->stu.math);
		fscanf(fp, "%d ", &s->stu.english);
		fscanf(fp, "%d ", &s->stu.sum);
		fscanf(fp, "%d ", &s->stu.average);
		//Insert the new node into the tail of the linked list (tail insertion method)
		s->next = NULL;
		L->tail->next = s;
		L->tail = s;
	}
	//Close file stream
	fclose(fp);
}
