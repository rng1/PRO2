/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 3
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * GROUP: 6.1
 * DATE: 25 / 06 / 21
 */

#include <stdlib.h>
#include <string.h>
#include "dynamic_list.h"

void createEmptyList(tList *l)
/*
* Goal  : creates an empty list.
* Input :
*    - l: a pointer to a list.
* Output: an empty list.
* PostCD: the list is initialised and has no elements.
*/
{
    // Start a list without any nodes.
    *l = LNULL;
}

bool createNode(tPosL *p)
/*
* Goal  : creates an empty node.
* Input :
*    - p: a pointer to a position.
* Output: a node.
*/
{
    // Create and assign memory to variable.
    *p = malloc(sizeof(struct tNode));
    return *p != LNULL;
}

tPosL findPosition(tItemL d, tList l)
/*
* Goal  : finds the position of an item in the list.
* Input :
*    - d: an item.
*    - l: a list.
* Output: if found, the position of that item within the list, NULL if it's not.
 /*/
{
    // Create an auxiliary position.
    tPosL p;

    // Iterate through the list to find the position of the given item.
    p = l;
    while ((LNULL != p->next) && (strcmp(d.nickname, p->next->data.nickname) > 0))
        p = p->next;
    return p;
}

bool insertItem(tItemL d, tList *l)
/*
* Goal  : inserts an element in the list ordered by the field nickname. If the element could be inserted,
          the value true is returned; otherwise, false is returned.
* Input :
*    - d: an item.
*    - l: a pointer to a list.
* Output: a boolean, 'true' if the list have been updated.
* PreCD : the specified position is a valid position in the list or a NULL position.
* PostCD: the positions of the elements in the list following that of the inserted one may have varied.
*/
{
    // Declare two auxiliary positions.
    tPosL n, p;

    // Create a node in one of the lists, if there's enough memory, turn (n) into a new node.
    if (!createNode(&n))
        return false;
    else {
        // Point the node (n) to the item to be added.
        n->data = d;
        n->next = LNULL;
        // If the list is empty, start the list with the new item.
        if (LNULL == *l)
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

void updateItem(tItemL d, tPosL p, tList *l)
/*
* Goal  : modifies the data of the item located at the given position.
* Input :
*    - d: an item.
*    - p: a position.
*    - l: a pointer to a list.
* Output: an updated list with the item of that position changed.
* PreCD : the indicated position is a valid position in the list.
* PostCD: the order of the elements in the list has not been modified.
*/
{
    // Change the data with the item given.
    p->data = d;
}

void deleteAtPosition(tPosL p, tList *l)
/*
* Goal  : deletes the element from the list at the given position.
* Input :
*    - p: a position.
*    - l: a pointer to a list.
* Output: an updated list with the item of that position deleted.
* PreCD : the indicated position is a valid position in the list and its play list is empty.
* PostCD: the positions of the elements in the list following that of the deleted one may have varied.
*/
{
    // Create an auxiliary position.
    tPosL q;

    // Delete the first element.
    if (*l == p)
        *l = p->next;
    // Delete the last element.
    else if (p->next == LNULL) {
        for(q = *l; q->next != p; q = q->next);
        // When 'q' is the previous node to 'p'.
        q->next = LNULL;
    }
    // Delete an element in any other position.
    else {
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

bool isEmptyList(tList l)
/*
* Goal  : determines whether the list is empty or not.
* Input :
*    - l: a list
* Output: a boolean 'true' if the list is empty.
*/
{
    // Check if there are any items within the list.
    return (LNULL == l);
}

tPosL findItem(tNickname n, tList l)
/*
* Goal  : returns the position of the first element in the list whose nickname matches the
*         one indicated (or NULL if there is no such element).
* Input :
*    - n: a nickname.
*    - l: the list to look through.
* Output: the position of the item searched.
*/
{
    tPosL p;

    // First we check if the item is outside the edges of the list or if we are searching in an empty list.
    if ((l == LNULL) || (strcmp(n, first(l)->data.nickname)<0) || (strcmp(n,last(l)->data.nickname)>0))
        return LNULL;
    else {
        // We compare the data with the nickname we are looking for for every position or until we find it.
        for (p = first(l); (LNULL != p) && (strcmp(n, p->data.nickname) > 0); p = p->next);
        // If found, return its position.
        if (strcmp(p->data.nickname, n) == 0)
            return p;
        else
            return LNULL;
    }
}

tItemL getItem(tPosL p, tList l)
/*
* Goal  : retrieves the content of the element at the indicated position.
* Input :
*    - p: a position.
*    - l: a list
* Output: a video item.
* PreCD : the indicated position is a valid position in the list.
*/
{
    // Return the data of the item at the given position.
    return p->data;
}

tPosL first(tList l)
/*
* Goal: returns the position of the first element of the list.
* Input :
*    - l: a list.
* Output: a position.
* PreCD : the list is not empty.
*/
{
    return l;
}

tPosL last(tList l)
/*
* Goal  : returns the position of the last element of the list.
* Input :
*    - l: list.
* Output: a position.
* PreCD : the list is not empty.
*/
{
    tPosL p;

    for (p = l; p->next != LNULL; p = p->next);
    return p;
}

tPosL next(tPosL p, tList l)
/*
* Goal  : returns the position preceding the one we indicate (or NULL if the specified position has no preceding element).
* Input : a position and a list.
*    - p: a position.
*    - l: a list.
* Output: a position.
* PreCD : the indicated position is a valid position in the list.
*/
{
    return p->next;
}

tPosL previous(tPosL p, tList l)
/*
* Goal  : returns the position preceding the one we indicate (or NULL if the specified position has no previous element).
* Input :
*    - p: a position.
*    - l: a list.
* Output: a position.
* PreCD : the indicated position is a valid position in the list.
*/
{
    tPosL q;

    if (p == l) {
        return LNULL;
    } else {
        for (q = l; q->next != p; q = q->next);
        return q;
    }
}
