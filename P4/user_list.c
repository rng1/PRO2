/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 4
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * GROUP: 6.1
 * DATE: 25 / 06 / 21
 */

#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "user_list.h"


void createEmptyList (tUserList* l)
// Creates an empty list.
// Input : a pointer to a list.
// Output: an empty list.
// PostCD: the list is initialised and has no elements.
{
    // Start a list without any nodes.
    *l = NULL_USER;
}

bool createNode(tUserPos *p)
// Creates an empty node.
// Input : a pointer to a position.
// Output: a node.
{
    // Create and assign memory to variable.
    *p = malloc(sizeof(struct tUserNode));
    return *p != NULL_USER;
}

tUserPos findPosition (tUserItem d, tUserList l)
// Finds the position of an item in the list.
// Input : an item and a list.
// Output: if found, the position of that item within the list, NULL if it's not.
{
    // Declare a position variable.
    tUserPos p;

    // Iterate through the list to find the position of the given item.
    p = l;
    while ((NULL_USER != p->next) && (strcmp(d.nickname, p->next->data.nickname) > 0))
        p = p->next;
    return p;
}

bool insertItem(tUserItem d, tUserList* l)
// Inserts an element in the list ordered by the field nickname. If the element could be inserted,
//     the value true is returned; otherwise, false is returned.
// Input : a user item and a pointer to a list.
// Output: a boolean, 'true' if the list have been updated.
// PreCD : the specified position is a valid position in the list or a NULL_USER position.
// PostCD: the positions of the elements in the list following that of the inserted one may have varied.
{
    // Declare two auxiliary nodes
    tUserPos n, p;

    // Create a node in one of the lists, if there's enough memory, turn (n) into a new node.
    if(!createNode(&n))
        return false;
    else {
        // Point the node (n) to the item to be added.
        n->data = d;
        n->next = NULL_USER;
        // If the list is empty, start the list with the new item.
        if (NULL_USER == *l)
            *l = n;
            // If the nickname goes before the first element of the list, add the new item at the beginning.
        else if (strcmp(d.nickname, (*l)->data.nickname) < 0) {
            n->next = *l;
            *l = n;
        }
        // Look for the position the item is going to be ordered and insert it.
        else {
            p = findPosition(d, *l);
            n->next = p->next;
            p->next = n;
        }
        return true;
    }
}

void updateItem(tUserItem d, tUserPos p, tUserList* l)
// Modifies the content of the element at the position we indicate.
// Input : a user item and a position and a pointer to a list.
// Output: an updated list (the item of that position changed).
// PreCD : the indicated position is a valid position in the list.
// PostCD: the order of the elements in the list has not been modified.
{
    // Change the data with the item given.
    p->data = d;
}

void deleteAtPosition(tUserPos p, tUserList* l)
// Deletes the element from the list at the given position.
// Input : a position and a pointer to a list.
// Output: an updated list with the item of that position deleted.
// PreCD : the indicated position is a valid position in the list.
// PostCD: the positions of the elements in the list following that of the deleted one may have varied.
{
    // Create an auxiliary position.
    tUserPos q;

    // Delete the first element.
    if (*l == p)
        *l = p->next;
    // Delete the last element.
    else if (p->next == NULL_USER) {
        for(q = *l; q->next != p; q = q->next);
        // When 'q' is the previous node to 'p'.
        q->next = NULL_USER;
    }
    // Delete at an intermediate position.
    else {
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    // Free the unused memory.
    free(p);
}

tUserPos findItem(tNickname n, tUserList l)
// Returns the position of the first element in the list whose nickname matches the
//     one indicated (or NULL_USER if there is no such element).
// Input : a nickname and the list to look through.
// Output: the position of the item searched.
{
    tUserPos p;

    // First we check if the item is outside the edges of the list or if we are searching in an empty list.
    if ((l == NULL_USER) || (strcmp(n, first(l)->data.nickname)<0) || (strcmp(n,last(l)->data.nickname)>0))
        return NULL_USER;
    else {
        // We compare the data with the nickname we are looking for for every position or until we find it.
        for (p = first(l); (NULL_USER != p) && (strcmp(n, p->data.nickname) > 0); p = p->next);
        // If found, return its position.
        if (strcmp(p->data.nickname, n) == 0)
            return p;
        else
            return NULL_USER;
    }
}

bool isEmptyList(tUserList l)
// Determines whether the list is empty or not.
// Input : a list.
// Output: a boolean 'true' if the list is empty.
{
    // Check if there are any items within the list.
    return (NULL_USER == l);
}

tUserItem getItem(tUserPos p, tUserList l)
// Retrieves the content of the element at the indicated position.
// Input: A position and a pointer to a list.
// Output: A user item.
// PreCD: The indicated position is a valid position in the list.
{
    // Return the item in the given position
    return p->data;
}

tUserPos first(tUserList l)
// Returns the position of the first element of the list.
// Input : a list.
// Output: a position.
// PreCD : the list is not empty.
{
    return l;
}

tUserPos last(tUserList l)
// Returns the position of the last element of the list.
// Input : a list.
// Output: a position.
// PreCD : the list is not empty.
{
    tUserPos p;

    for(p = l; p->next != NULL_USER; p = p->next);
    return p;
}

tUserPos previous(tUserPos p, tUserList l)
// Returns the position preceding the one we indicate (or NULL if the specified position has no previous element).
// Input : a position and a list.
// Output: a position.
// PreCD : the indicated position is a valid position in the list.
{
    tUserPos q;

    if (p == l) {
        return NULL_USER;
    } else {
        for (q = l; q->next != p; q = q->next);
        return q;
    }
}

tUserPos next(tUserPos p, tUserList l)
// Returns the position preceding the one we indicate (or NULL if the specified position has no preceding element).
// Input : a position and a list.
// Output: a position.
// PreCD : the indicated position is a valid position in the list.
{
    return p->next;
}

