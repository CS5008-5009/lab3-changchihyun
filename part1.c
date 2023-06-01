#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int data;
    struct ListNode* next;
}node_t;

node_t* makeNode(int data){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL){
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeNode(node_t* node){
    if(node == NULL){
        return;
    }
    free(node);
}
void printNode(node_t* node){

    node_t* itr = node;
    while (itr != NULL){
        printf("%d", itr->data);
        if (itr->next != NULL){
            printf(", ");
        }
        itr = itr->next;
    }
    printf("\n");
}

typedef struct sList{
    node_t* head;
    int size;
}sList_t;

sList_t* makeSlist(){
    sList_t* newList = (sList_t*)malloc(sizeof(sList_t));
    if (newList == NULL){
        return NULL;
    }
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

int searchElement(sList_t* slist, int element){
    node_t* itr = slist->head;
    int pos = 1;
    while (itr != NULL){
        if(itr->data == element){
            return pos;
        }
        itr = itr->next;
        pos++;
    }
    return -1;
}
int insertMiddle(sList_t* slist, int element, int position){
    if(slist->head == NULL|| position < 2 || position > slist->size){
        return 0;
    }
    node_t* temp = slist->head;
    for (int i = 1; i < position - 1; i++){
        temp = temp->next;
    }
    node_t* newNode = makeNode(element);
    newNode->next = temp->next;
    temp->next = newNode;
    slist->size++;
    return 1;
}
int insertFront(sList_t* slist, int element){
    node_t* newNode = makeNode(element);
    if (newNode == NULL){
        return 0;
    }
    newNode->next = slist->head;
    slist->head = newNode;
    slist->size++;
    return 1;
}
int insertEnd(sList_t* slist, int element){
    if (slist->size == 0){
        return insertFront(slist, element);
    }
    node_t* newNode = makeNode(element);
    if (newNode == NULL){
        return 0;
    }
    node_t* temp = slist->head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = NULL;
    slist->size++;
    return 1;
}
int deleteMiddle(sList_t* slist, int element){
    if (slist->size < 3){
        //printf("size: %d\n", slist->size);
        return 0;
    }

    //printf("size: %d\n", slist->size);
    node_t* temp = slist->head;
    
    while(temp->next != NULL && temp->next->data != element){
        temp = temp->next;
    }
    if(temp->next == NULL){
        printf("Cannot find the element.\n");
        return 0;
    }    
    node_t* delNode = temp->next;
    temp->next = temp->next->next;
    slist->size--;
    freeNode(delNode);
    return 1;
}
int deleteEnd(sList_t* slist){
    if(slist->size == 0){
        printf("Empty LinkedList, nothing to delete.\n");
        return 0;
    }
    if(slist->size == 1){
        node_t* delNode = slist->head;
        slist->head = NULL;
        slist->size--;
        free(delNode);
        return 1;
    }
    node_t* temp = slist->head;
    while (temp->next->next != NULL){
        temp = temp->next;
    }
    node_t* delNode =temp->next;
    temp->next = NULL;
    slist->size--;
    free(delNode);
    return 1;
}
int deleteFront(sList_t* slist){
    if(slist->size == 0){
        printf("Empty LinkedList, nothing to delete.\n");
        return 0;
    }
    node_t* delNode = slist->head;
    if(slist->size == 1){
        slist->head = NULL;
    }else {
        slist->head = slist->head->next;
    }
    slist->size--;
    free(delNode);
    return 1;
}

int main(){

    sList_t* slist = makeSlist();
    insertFront(slist, 52);
    insertFront(slist, 23);

    insertEnd(slist, 9);
    insertEnd(slist, 100);
    insertMiddle(slist, 19, 3);
    printNode(slist->head);
    int pos = searchElement(slist, 99);
    printf("search (99)element's postion: %d\n", pos);
    int pos1 = searchElement(slist, 19);
    printf("search (19)element's postion: %d\n", pos1);
    printf("Insert 7 at position 3.\n");
    insertMiddle(slist, 6, 2);
    printNode(slist->head);

    printf("delete 6 from the middle of the linked list.\n");
    deleteMiddle(slist, 6);
    printNode(slist->head);
    printf("Insert 6 at the front of the linked list.\n");
    insertFront(slist, 6);
    printNode(slist->head);
    printf("delete 6 from the front of the linked list.\n");
    deleteFront(slist);
    printNode(slist->head);
    printf("Insert 6 at the end of the linked list.\n");
    insertEnd(slist, 6);
    printNode(slist->head);
    printf("delete 6 at the end the linked list.\n");
    deleteEnd(slist);
    printNode(slist->head);








    return 0;
}
