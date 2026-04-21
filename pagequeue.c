/** pagequeue.c
 * ===========================================================
 * Name: Gia Sanchirico, Apr 20 2026
 * Section: CS483 / M3
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
    PageQueue* pq = malloc(sizeof(PageQueue));
    pq->head = NULL;
    pq->tail = NULL;
    pq->size = NULL;
    pq->maxSize = maxSize;
    return pq;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).

    PqNode* tmp = pq->tail;
    int i = 0;

    while(tmp != NULL){
        // HIT path (page found at depth d):
        //   - Remove the node from its current position and re-insert
        //     it at the tail (most recently used).
        //   - Return d.
        if(tmp->pageNum == pageNum){
            //delete helper function?
            free(tmp);git add
            return i;
        }
        
        // MISS path (page not found):
        //   - Allocate a new node for pageNum and insert it at the tail.
        //   - If size now exceeds maxSize, evict the head node (free it).
        //   - Return -1.
        else{
            PqNode* newNode = pageNum;
            newNode->next = NULL;
            if(pq->head == NULL){
                newNode->prev = NULL;
                pq->head = newNode;
                pq->tail = newNode;
            }
            else{
                newNode->prev = pq->tail;
                pq->tail->next = newNode;
                pq->tail = newNode;
            }

            pq->size++;
            if(pq->size > pq->maxSize){
                //delete the head
                pq->head = tmp->next;

                pq->head->prev = NULL;
                
                pq->size--;

                free(tmp);
                return -1;
            }

        }
        tmp = tmp->next;
        i++;
    }
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
}
