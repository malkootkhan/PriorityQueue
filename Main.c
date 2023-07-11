
/* Please be aware that the code in its current state is in the initial phase and has undergone minimal testing. It is strongly recommended to thoroughly test and make any necessary modifications before utilizing it. */
/* I cannot be held responsible for any issues or difficulties arising from using the code without making appropriate modifications. */
/* Basic Priority queue implementation using array in c */
/*
Priority Queue Implementation in C
File: Main.c
Author: Malkoot Khan
Date: 11/07/2023
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true }bool;
typedef enum { INSERT = 1, MAX_PRIORITY_DATA, DELETE, SEARCH, RELEASE_MEM, MAX_PRIORITY, CAPACITY, DISPLAY }operation;

struct PriorityQueue {
	int capacity;
	int *front;
	int *rear;
	int max_priority;
	int **data;
};
struct PriorityQueue* createPqueue(int cap, int maxPriority) {
	struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
	pq->capacity = cap;
	pq->max_priority = maxPriority;
	pq->front = (int*)malloc(sizeof(int)*(pq->max_priority + 1));
	pq->rear = (int*)malloc(sizeof(int)*(pq->max_priority + 1));
	pq->data = (int **)malloc(sizeof(int *) * (pq->max_priority + 1));
	for (int priority = 0; priority <= pq->max_priority; priority++)
			pq->data[priority] = (int*)malloc(sizeof(int) * pq->capacity);

	for (int priority = 0; priority <= pq->max_priority; priority++) {
		pq->front[priority] = -1;
		pq->rear[priority] = -1;
	}
	return pq;
}
inline bool isPriorityValid(struct PriorityQueue *pq,int currPriority) {
	if (currPriority <= pq->max_priority && currPriority >= 0)
		return true;
	return false;
}
inline bool  isFull(struct PriorityQueue *pq, int priority) {
	if (pq->front[priority] == 0 && pq->rear[priority] == pq->capacity - 1)
		return true;
	else if (pq->rear[priority] + 1 == pq->front[priority])
		return true;
	else
		return false;
}
inline bool  isEmpty(struct PriorityQueue *pq, int priority) {
	if ((pq->front[priority] == -1) && (pq->rear[priority] == -1))
		return true;
	else
		return false;
}
void insert(struct PriorityQueue* pq, int priority, int value) {
	if (isFull(pq, priority)) {
		printf("The queue is full!\n");
		return;
	}
	else {
		if (isEmpty(pq, priority))
		{
			pq->front[priority] = 0;
			pq->rear[priority] = 0;
		}
		else if (pq->rear[priority] == pq->capacity - 1)
			pq->rear[priority] = 0;
		else
			pq->rear[priority]++;
		pq->data[priority][pq->rear[priority]] = value;
		
	}
}
inline int  getMaxPriority(struct PriorityQueue *pq) { return pq->max_priority; }
inline int  getCapacity(struct PriorityQueue* pq) { return pq->capacity; }
int *getMaxPriorityData(struct PriorityQueue *pq) {
		for (int priority = pq->max_priority; priority >= 0; priority--) 
		{
			if (!isEmpty(pq, priority)) {
				return pq->data[priority];
			}
		}
		printf("There is no data in queues\n");
		return NULL;
}
void search(struct PriorityQueue* pq, int priority, int myData) {
	if (isEmpty(pq, priority)) {
		printf("queue is empty!\n");
		return;
	}
	else
	{
		for (int index = 0; index < pq->capacity; index++) {
			if (myData == pq->data[priority][index])
			{
				printf("Data found!\n");
				return;
			}
		}
		printf("Data not found!\n");
		return;
	}
}
void deleteMaxPriorityData(struct PriorityQueue *pq) {
	for (int priority = pq->max_priority; priority >= 0; priority--) {
		if (!isEmpty(pq, priority)) {
			if (pq->front[priority] == pq->rear[priority]) {
				pq->front[priority] = -1;
				pq->rear[priority] = -1;
			}
			else if (pq->front[priority] == pq->capacity - 1) {
				pq->front[priority] = 0;
			}
			else {
				pq->front[priority]++;
			}
			return;
		}
	}
	printf("The queue is empty!\n");
}
void releaseMemory(struct PriorityQueue* pq) {
	for (int index = 0; index <= pq->max_priority; index++) 
		free(pq->data[index]);
	free(pq->data);
	free(pq->front);
	free(pq->rear);
	exit(0);
}
void display(struct PriorityQueue* pq) {
	for (int priority = pq->max_priority; priority >= 0; priority--) {
		printf("\nPriority Level: %d", priority); printf("\n");
		for (int dataIndex = pq->front[priority]; dataIndex < pq->capacity; dataIndex++)
		{
			if (!isEmpty(pq, priority))
			{
				if (dataIndex == pq->rear[priority])
				{
					printf("%d ", pq->data[priority][dataIndex]);
					break;
				}
				else if (dataIndex == pq->capacity - 1)
				{
					printf("%d ", pq->data[priority][dataIndex]);
					dataIndex = -1;
				}
				else
					printf("%d ", pq->data[priority][dataIndex]);
			}
			else
			{
				printf("At given priority the queue is empty!\n ");
				break;
			}
		}
		printf("\n");
	}
}

int main() {
	int maxPriority;
	int currPriority;
	int capacity;
	int choice;
	int data;
	int* dataPtr = NULL;
	printf("Enter maximum priority ");
	scanf("%d", &maxPriority);
	printf("Enter pQueue capacity ");
	scanf("%d", &capacity);
	struct PriorityQueue* pQ = createPqueue(capacity, maxPriority);
	while (true) {
		printf("\n******** Follow the commands below to deal with the priority queue *********\n");
		printf("1. Insert value to the queue\n");
		printf("2. Get Max Priority data from the queue\n");
		printf("3. Delete value from the queue\n");
		printf("4. Search value in the queue\n");
		printf("5. Release the allocated memory\n");
		printf("6. Get Max Priority queue\n");
		printf("7. Get queue capacity\n");
		printf("8. Display queue\n");
		printf("Enter your choice shown above ");
		scanf("%d",&choice);
		switch (choice) {
		case INSERT:
			printf("Enter data ");
			scanf("%d", &data);
			printf("Enter priority ");
			scanf("%d", &currPriority);
			if(isPriorityValid(pQ, currPriority))
				insert(pQ, currPriority, data);
			else
				printf("Invalid priority level!\n");
			break;
		case MAX_PRIORITY_DATA:
			dataPtr = getMaxPriorityData(pQ);
			if (dataPtr) {
				for (int index = 0; index < pQ->capacity; index++)
					printf("%d ", dataPtr[index]);
				printf("\n");
			}
			break;
		case DELETE:
			deleteMaxPriorityData(pQ);
			break;
		case SEARCH:
			printf("Enter data to be sought ");
			scanf("%d", &data);
			printf("Enter priority level for searching ");
			scanf("%d", &currPriority);
			if (isPriorityValid(pQ, currPriority))
				search(pQ, currPriority, data);
			else
				printf("Invalid priority level!\n");
			break;
		case RELEASE_MEM:
			releaseMemory(pQ);
			break;
		case MAX_PRIORITY:
			printf("%d", getMaxPriority(pQ));
			break;
		case CAPACITY:
			printf("%d", getCapacity(pQ));
			break;
		case DISPLAY:
			display(pQ);
			break;
		default:
			printf("Invalid choice!\n");
			break;
		}
	}
	return 0;
}

