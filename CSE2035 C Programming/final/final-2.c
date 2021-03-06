#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _DATA_ {
	double value;
	struct _DATA_ *next;
} data;

void readData(char* filename, data** head);

void appendData(data** head, double value);

void interpolationData(data** head);

void printData(data* head);

void freeData(data* head);

int main() {
	char filename[21];
	scanf("%s", filename);

	data* list = NULL;
	
	readData(filename, &list);

	interpolationData(&list);

	printData(list);

	freeData(list);

	return 0;
}

void readData(char* filename, data** head) {
	FILE* file = fopen(filename, "r");
	char buffer[100];
	double temp;

	while (fgets(buffer, 100, file)) {
		temp = atof(buffer);
		appendData(head, temp);
	}

	fclose(file);
}

void appendData(data** head, double value) {
	data* newData = (data*)malloc(sizeof(data));
	newData->value = value;
	newData->next = NULL;

	if (*head == NULL) {
		*head = newData;
	}
	else {
		data* curr = *head;
		while (curr->next != NULL) {
			curr = curr->next;
		}

		curr->next = newData;
	}
}

void interpolationData(data** head) {
	if (*head == NULL) return;

	int i = 0;
	data *prev, *curr = *head;
	double avg;

	while (curr->next != NULL) {
		prev = curr;
		curr = curr->next;
		avg = (prev->value + curr->value) / 2;

		data* newData = (data*)malloc(sizeof(data));
		newData->value = avg;
		newData->next = curr;
		prev->next = newData;
	}
}

void printData(data* head) {
	data *curr = head;

	while (curr != NULL) {
		printf("%.3lf\n", curr->value);
		curr = curr->next;
	}
}

void freeData(data* head) {
	data *prev, *curr = head;

	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}