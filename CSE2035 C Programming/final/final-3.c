#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _QUEUE_NODE_ {
    int number;
    int works;
    struct _QUEUE_NODE_ *next;
} queue_node;

typedef struct _QUEUE_ {
    queue_node *front;
    int count;
    queue_node *rear;
} queue;

void initialQueue(queue** head);

void doRoundRobbin(queue* head);

int enqueue(queue *head, queue_node *node);

int dequeue(queue *head, queue_node **node);

int main() {
    queue* q;

    initialQueue(&q);

    doRoundRobbin(q);

    free(q);

    return 0;
}

void initialQueue(queue** head) {
    *head = (queue*)malloc(sizeof(queue));
    (*head)->count = 0;
    (*head)->front = NULL;
    (*head)->rear = NULL;

    int program_count, number, amount;
    scanf("%d", &program_count);

    while (program_count--) {
        scanf("%d%d", &number, &amount);

        queue_node *node = (queue_node*)malloc(sizeof(queue_node));

        node->number = number;
        node->works = amount;
        node->next = NULL;

        enqueue(*head, node);
    }
}

void doRoundRobbin(queue* head) {
    int i = 0;
    while (1) {
        i++;

        queue_node *node;
        if (!dequeue(head, &node)) {
            break;
        }

        if (node->works == 1) {
            printf("%d %d\n", node->number, i);
            free(node);
        }
        else {
            node->works--;
            enqueue(head, node);
        }
    }
}

int enqueue(queue *head, queue_node *node) {
    if (!(head->count)) {
        head->front = node;
        head->rear = node;
        head->count++;
        return 1;
    }
    else {
        head->rear->next = node;
        head->rear = node;
        head->count++;
        return 1;
    }
    return 0;
}

int dequeue(queue *head, queue_node **node) {
    if (!(head->count)) {
        return 0;
    }
    else {
        *node = head->front;

        if (head->front->next == NULL) {
            head->front = NULL;
            head->rear = NULL;
            head->count = 0;
        }
        else {
            head->front = head->front->next;
            head->count--;
        }
        return 1;
    }
}