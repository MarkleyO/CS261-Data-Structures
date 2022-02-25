/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Owen Markley
 * Email: markleyo@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include "dynarray.h"
#include "pq.h"
#include <assert.h>

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct element{
	void* val;
	int priority;
};

struct pq{
	struct dynarray* elements;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* priorQueue = malloc(sizeof(struct pq));
	priorQueue->elements = dynarray_create();

	return priorQueue;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	assert(pq);
	int i;
	struct element* temp;
	for(i=0; i<dynarray_size(pq->elements); i++){
		temp = dynarray_get(pq->elements, i);
		free(temp);
	}
	dynarray_free(pq->elements);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	assert(pq);
	if(dynarray_size(pq->elements) == 0)
		return 1;
	else
		return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void swap(struct pq* pq, int parentIndex, int childIndex){
	struct element* tempParent = dynarray_get(pq->elements, parentIndex);
	struct element* tempChild = dynarray_get(pq->elements, childIndex);
	dynarray_set(pq->elements, parentIndex, tempChild);
	dynarray_set(pq->elements, childIndex, tempParent);
}

void moveUp(struct pq* pq){
	int childIndex = dynarray_size(pq->elements)-1;
	int parentIndex = (childIndex-1)/2;
	struct element* tempChild = dynarray_get(pq->elements, childIndex);
	struct element* tempParent = dynarray_get(pq->elements, parentIndex);
	int childPrior = tempChild->priority;
	int parentPrior = tempParent->priority;

	while(childIndex > 0 && childPrior<parentPrior){
		swap(pq, parentIndex, childIndex);
		childIndex = parentIndex;
		parentIndex = (parentIndex-1)/2;
		tempParent = dynarray_get(pq->elements, parentIndex);
		parentPrior = tempParent->priority;
	}
}


void pq_insert(struct pq* pq, void* value, int priority) {
	assert(pq);
	assert(pq->elements);

	struct element* add = malloc(sizeof(struct element));
	add->val = value;
	add->priority = priority;
	dynarray_insert(pq->elements, -1, add);
	moveUp(pq); 
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	assert(pq);
	assert(pq->elements);
	struct element* e = dynarray_get(pq->elements, 0);
	void* value = e->val;
	return value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	assert(pq);
	assert(pq->elements);
	struct element* e = dynarray_get(pq->elements, 0);
	int prior = e->priority;
	return prior;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

void balance(struct pq* pq){
	int leftInd, rightInd, leftPr, rightPr;
	struct element* left;
	struct element* right;
	struct element* current;
	int size = dynarray_size(pq->elements)-1;
	int currentNode = 0;

	while(2*currentNode+1 < size){
		leftInd = 2*currentNode+1;
		rightInd = leftInd+1;

		if(leftInd<=size){
			left = dynarray_get(pq->elements, leftInd);
			leftPr = left->priority;
		}
		if(leftInd<size){
			right = dynarray_get(pq->elements, rightInd);
			rightPr = right->priority;
		}
		current = dynarray_get(pq->elements, currentNode);


		if(leftPr < current->priority && leftPr <= rightPr){
			//printf("swapping\n");
			swap(pq, currentNode, leftInd);
			currentNode = leftInd;
		}
		else if(rightPr < current->priority && rightPr <=leftPr){
			swap(pq, currentNode, rightInd);
			currentNode = rightInd;
		}
		else
			currentNode = size;
	}
}

void* pq_remove_first(struct pq* pq) {
	assert(pq);
	assert(pq->elements);
	struct element* removed = dynarray_get(pq->elements, 0);
	void* removedVal = removed->val;
	free(removed);
	dynarray_set(pq->elements, 0, dynarray_get(pq->elements, -1));
	dynarray_remove(pq->elements, -1);

	balance(pq);

	return removedVal;
}
