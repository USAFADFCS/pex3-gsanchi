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
    pq->size = 0;
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
            //Find it first
            //PqNode* change = pq->tail;

            //At tail of pq
            if (pq->tail->pageNum == pageNum)
            {
                //Hit is already at the end of the pq
                return i; 
            }
            
            // for(int j = 0; j<pq->size-1; j++){
            //     change = change->prev;
            // }

            //Re-direct to Tail
            //If found at the head
            if (pq->head->pageNum == pageNum)
            {
                pq->head = tmp->next;
                pq->head->prev = NULL;
            }

            //If found in the middle
            else{
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
            }     
            
            tmp->prev = pq->tail;
            pq->tail->next = tmp;
            pq->tail = tmp;
            tmp->next = NULL;

            return i;
        }

        tmp = tmp->next;
        i++;
    }
        
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.
    PqNode* newNode = malloc(sizeof(PqNode));
    newNode->pageNum = pageNum;
    newNode->next = NULL;
    
    //Check if the list is empty    
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
        //Made a holder for head so it does not seg fault
        PqNode* headTmp = malloc(sizeof(PqNode));
        headTmp = pq->head;

        //Delete head
        pq->head = pq->head->next;

        pq->head->prev = NULL;
                
        pq->size--;
        
        free(headTmp);
    }    

    return -1;       
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
    PqNode* tmp = pq->head;
    while(tmp != NULL){
        pq->head = tmp->next;
        tmp->next = NULL;
        free(tmp);
        tmp = pq->head;
    }
    pq->tail = NULL;
    free(pq);
}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
    PqNode* current = pq->head;
    while(current != NULL){
        printf("%lu\n", current->pageNum);
        current = current->next;
    }
}
