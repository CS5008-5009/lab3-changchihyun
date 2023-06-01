#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node* prev;
    int data;
    struct Node* next;
}node_t;

node_t* makeNode(int data){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL){
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode; 
}

typedef struct doublyList{
    int size;
    node_t* head;
}doublyList_t;

doublyList_t* makedoublyList(){
    doublyList_t* newList = (doublyList_t*)malloc(sizeof(doublyList_t));
    if (newList == NULL){
        return NULL;
    }
    newList->head = NULL;
    newList->size = 0;
    return newList;
}
int searchElement(doublyList_t* dlist, int element){
    if(dlist->head == NULL){
        printf("Cannot search empty doubly linked list.\n");
        return 0;
    }
    int pos = 1;
    node_t* itr = dlist->head;
    while(itr != NULL){
        if(itr->data == element){
            return pos;
        }
        itr = itr->next;
        pos++;
    }
    return -1;
}
int insertMiddle(doublyList_t* dlist, int element, int position){
    if(position > (dlist->size) + 1){
        printf("position out of range.\n");
        return 0;
    }
    node_t* dummy = makeNode(-1);
    dummy->next = dlist->head;
    if(dlist->head != NULL){
        dlist->head->prev = dummy;
    }

    node_t* cur = dummy;
    for(int i = 0; i < position - 1; i++){
        cur = cur->next;
    }
    node_t* newNode = makeNode(element);
    newNode->next = cur->next;
    newNode->prev = cur;
    if(cur->next != NULL) {
        cur->next->prev = newNode;
    }
    cur->next = newNode;

    if(dummy->next == newNode){
        dlist->head = newNode;
    }
    if(dummy->next != NULL){
        dummy->next->prev = NULL;
        dummy->next = NULL;
    }
    dlist->size++;
    free(dummy);
    return 1;
}

int insertFront(doublyList_t* dlist, int element){
    return insertMiddle(dlist, element, 1);
}
int insertEnd(doublyList_t* dlist, int element){
    return insertMiddle(dlist, element, dlist->size + 1);
}
void printNode(node_t* node){
    node_t* itr = node;
    while (itr!= NULL){
        printf("%d", itr->data);
        if(itr->next != NULL){
            printf(",");
        }
        itr = itr->next;
    }
    printf("\n");
}

void freeNode(node_t* node){
    if (node == NULL){
        return;
    }
    free(node);
}
int deleteMiddle(doublyList_t* dlist, int element){
    if (dlist->size < 3){
        printf("The size of doubly linked list cannot be allowed for delete from middle.");
        return 0;
    }
    node_t* temp = dlist->head;
    while (temp->next != NULL && temp->next->data != element){
        temp = temp->next;
    }
    if(temp->next == NULL){
        printf("Cannot find Element.\n");
        return 0;
    }
    node_t* delNode = temp->next;
    temp->next = temp->next->next;
    temp->next->prev = temp;
    freeNode(delNode);
    dlist->size--;
    return 1;
}

int deleteFront(doublyList_t* dlist){
    if(dlist->head == NULL){
        printf("Empty doubly linked list, cannot delete.\n");
        return 0;
    }

    node_t* temp = dlist->head;
    if(dlist->head->next == NULL){
        dlist->head = NULL;
    } else {
        dlist->head = dlist->head->next;
        dlist->head->prev = NULL;
    }
    
    temp->next = NULL;
    dlist->size--;
    freeNode(temp);
    return 1;
}

int deleteEnd(doublyList_t* dlist){
    if(dlist->head == NULL){
        printf("Empty doubly linked list, cannot delete.\n");
        return 0;
    }
    if(dlist->head->next == NULL){
        return deleteFront(dlist);
    }
    node_t* temp = dlist->head;
    while(temp->next->next != NULL){
        temp = temp->next;
    }
    node_t* delNode = temp->next;
    temp->next->prev = NULL;
    temp->next = NULL;
    dlist->size--;
    freeNode(delNode);
    return 1;
}

int main(){
    doublyList_t* dlist = makedoublyList();
    //deleteFront(dlist);
    printf("Insert at the Middle of doubly linked list.\n");
    insertMiddle(dlist, 23, 1);
    insertMiddle(dlist, 53, 2);
    insertMiddle(dlist, 19, 3);
    insertMiddle(dlist, 9, 4);
    insertMiddle(dlist, 100, 5);
    printNode(dlist->head);
    printf("Insert at the front of doubly linked list.\n");
    insertFront(dlist, 6);
    printNode(dlist->head);   
    printf("Insert at the end of doubly linked list.\n");
    insertEnd(dlist, 6);
    printNode(dlist->head);
    printf("Delete element at the middle of doubly linked list.\n");   
    deleteMiddle(dlist, 53);
    printNode(dlist->head);
    printf("Delete element at the front of doubly linked list.\n");   
    deleteFront(dlist);
    printNode(dlist->head);   
    printf("Delete element at the end of doubly linked list.\n");   
    deleteEnd(dlist);
    printNode(dlist->head);
    printf("Insert at the Middle of doubly linked list.\n");
    insertMiddle(dlist, 53, 3);   
    printNode(dlist->head);   
    int pos = searchElement(dlist, 53);
    printf("Search (53) element at position: %d\n", pos);
    int pos1 = searchElement(dlist, 1);
    printf("Search (1) element at position: %d\n", pos1);   
}
