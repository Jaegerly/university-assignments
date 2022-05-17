#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h> // Provides size_t

namespace FHSULINKEDLIST
{
    struct Node
    {
        typedef int Item;
        Item data;
        Node *link;
    };
    
    // FUNCTIONS for the linked list toolkit
    size_t list_length(const Node* head_ptr);
    void list_head_insert(Node*& head_ptr, const Node::Item& entry);
    void list_insert(Node* previous_ptr, const Node::Item& entry);
    Node* list_search(Node* head_ptr, const Node::Item& target);
    Node* list_locate(Node* head_ptr, size_t position);
    void list_head_remove(Node*& head_ptr);
    void list_remove(Node* previous_ptr);
    void list_clear(Node*& head_ptr);
    void list_copy(Node* source_ptr, Node*& head_ptr);
    size_t list_occurrences(Node* head_ptr, const Node::Item& target);
    void list_tail_attach(Node*& head_ptr, const Node::Item& entry);
    void list_tail_remove(Node*& head_ptr);
    Node* list_copy_front(Node* source_ptr, size_t n);
}

#endif

