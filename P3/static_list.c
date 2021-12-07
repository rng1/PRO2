/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 3
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * GROUP: 6.1
 * DATE: 25 / 06 / 21
 */

#include <string.h>
#include "static_list.h"

void createEmptyList (tList* l)
/*
* Goal  : creates an empty list.
* Input :
*    - l: a pointer to a list.
* Output: an empty list.
* PostCD: the list is initialised and has no elements.
*/
{
    l->lastPos = LNULL;
}

bool insertItem(tItemL d, tList *l)
/*
* Goal  : inserts an element in the List ordered by the field nickname. If the element could be inserted,
*         the value true is returned; otherwise false is returned.
* Input :
*    - d: an item.
*    - l: a pointer to a list.
* Output: a boolean, 'true' if the list have been updated.
* PreCD : the specified position is a valid position in the list or a NULL_VIDEO position.
* PostCD: the positions of the elements in the list following that of the inserted one may have varied.
*/
{
    // Declare a counter.
    tPosL c;

    // If there is no space left, cancel the operation.
    if (l->lastPos == MAX - 1)
        return false;
    else {
        // Insert the item at the end.
        if (isEmptyList(*l) || (strcmp(d.nickname, l->data[l->lastPos].nickname) > 0)) {
            // Move the limit once.
            l->lastPos++;
            // Insert the item in the space created.
            l->data[l->lastPos] = d;
        } else {
            // Move the limit once.
            l->lastPos++;
            // Search for the given position while moving every item to make space.
            for (c = l->lastPos; (c > 0) && (strcmp(d.nickname, l->data[c - 1].nickname) < 0); c--)
                l->data[c] = l->data[c - 1];
            l->data[c] = d;
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
* Output: an updated list (the item of that position changed).
* PreCD : the indicated position is a valid position in the list.
* PostCD: the order of the elements in the list has not been modified.
*/
{
    // Change the data with the item given.
    l->data[p] = d;
}

void deleteAtPosition(tPosL p, tList *l)
/*
* Goal  : deletes the element from the list at the given position.
* Input :
*    - p: a position.
*    - l: a pointer to a list.
* Output: an updated list (the item of that position deleted).
* PreCD : the indicated position is a valid position in the list and its play list is empty.
* PostCD: the positions of the elements in the list following that of the deleted one may have varied.
*/
{
    // Declare a counter.
    int c;

    // Move everything to the left until the given position.
    for (c = p; c < l->lastPos; c++)
        l->data[c] = l->data[c + 1];
    // Move the limit to remove a space.
    l->lastPos--;
}

bool isEmptyList(tList l)
/*
* Goal  : determines whether the list is empty or not.
* Input :
*    - l: a list.
* Output: a boolean 'true' if the list is empty.
*/
{
    // Check if there are any items within the list.
    return (l.lastPos == LNULL);
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
    // Declare a counter.
    tPosL p;

    // Check is the list is empty or if the name isn't within the list's range.
    if ((LNULL == l.lastPos) || (strcmp(n, l.data[0].nickname) < 0) || (strcmp(n, l.data[l.lastPos].nickname) > 0))
        return LNULL;
    else {
        // Compare the data with the nickname we are looking for until it's found.
        for (p = 0; (p <= l.lastPos) && (strcmp(n, l.data[p].nickname) > 0); p++);
        // If found, return the position of the item within the list.
        if (strcmp(l.data[p].nickname, n) == 0)
            return p;
        else
            return LNULL;
    }
}

tItemL getItem(tPosL p, tList l)
/*
* Goal  : retrieves the content of the element at the position we indicate.
* Input :
*    - p: a position.
*    - l: a list.
* Output: an item.
* PreCD : the indicated position is a valid position in the list.
*/
{
    // We return the data of the item.
    return l.data[p];
}

tPosL first(tList l)
/*
* Goal  : returns the position of the first element of the list.
* Input :
*    - l: a list.
* Output: a position.
* PreCD : the list is not empty.
*/
{
    return 0;
}

tPosL last(tList l)
/*
* Goal  : returns the position of the last element of the list.
* Input :
*    - l: a list
* Output: a position.
* PreCD : the list is not empty.
*/
{
    return l.lastPos;
}

tPosL next(tPosL p, tList l)
/*
* Goal  : returns the position preceding the one we indicate (or NULL_VIDEO if the specified position has no previous element).
* Input :
*    - p: a position.
*    - l: a list.
* Output: a position.
* PreCD : the indicated position is a valid position in the list.
*/
{
    if (p == l.lastPos)
        return LNULL;
    else
        return ++p;
}

tPosL previous(tPosL p, tList l)
/*
* Goal  : returns the position preceding the one we indicate (or NULL_VIDEO if the specified position has no previous element).
* Input :
*    - p: a position.
*    - l: a list.
* Output: a position.
* PreCD : the indicated position is a valid position in the list.
*/
{
    return --p;
}
