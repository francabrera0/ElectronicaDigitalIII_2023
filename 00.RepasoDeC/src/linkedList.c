#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char firstName[20];
    char lastName[20];
    int age;
} Person;

typedef struct Node {
    Person data;
    struct Node* next;
} Node;

Node* createNode(Person data);
void insertBegin(Node** head, Person data);
void insertEnd(Node** head, Person data);
void printList(Node* head);
void freeList(Node* head);


int main() {

    Node* head = NULL;

    Person person = {"José", "Sanchez", 52};
    insertBegin(&head, person);

    strcpy(person.firstName, "Matias");
    strcpy(person.lastName, "Dominguez");
    person.age = 23;
    insertBegin(&head, person);

    strcpy(person.firstName, "Juan");
    strcpy(person.lastName, "Perez");
    person.age = 27;
    insertEnd(&head, person);

    printf("Linked List: ");
    printList(head);

    freeList(head);

    return 0;
}


/**
 * @brief Create a new Node
 * 
 * @param data Person struct to save in the new node
 * @return Pointer to the new Node
*/
Node* createNode(Person data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief insert a new node at the beginning of the list
 * 
 * @param head reference to the head of the list
 * @param data Person struct to save in the new node
 * @return none
*/
void insertBegin(Node** head, Person data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    *head = newNode;
}

/**
 * @brief insert a new node at the end of the list
 * 
 * @param head reference to the head of the list.
 * @param data Person struct to save in the new node
 * @return none
*/
void insertEnd(Node** head, Person data) {
    Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node* iteratorNode = *head;
    while (iteratorNode->next != NULL) {
        iteratorNode = iteratorNode->next;
    }

    iteratorNode->next = newNode;
}

/**
 * @brief Prit the linked list
 * 
 * @param head Head list
 * @return none
*/
void printList(Node* head) {
    Node* iteratorNode = head;
    while (iteratorNode != NULL) {
        printf("%s, %s, %d -> ", iteratorNode->data.firstName, iteratorNode->data.lastName, iteratorNode->data.age);
        iteratorNode = iteratorNode->next;
    }
    printf("NULL\n");
}

/**
 * @brief Frees the memory space allocated to the nodes
 * 
 * @param head Head list
 * @return none
*/
void freeList(Node* head) {
    Node* iteratorNode = head;
    while (iteratorNode != NULL) {
        Node* temp = iteratorNode;
        iteratorNode = iteratorNode->next;
        free(temp);
    }
}
