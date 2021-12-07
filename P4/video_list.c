/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 4
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * GROUP: 6.1
 * DATE: 25 / 06 / 21
 */

#include <string.h>
#include "types.h"
#include "video_list.h"

/** CAMBIOS
 * Funciones insertItem, findItem adaptadas para funcionar como lista ordenada.
 *
 *
 *
 *
 */

void createEmptyListV (tVideoList* l)
// Creates an empty list.
// Input : a pointer to a list.
// Output: an empty list.
// PostCD: the list is initialised and has no elements.
{
    // Create a list with no spaces.
    l->lastPos = NULL_VIDEO;
}

bool insertItemV(tVideoItem d, tVideoList *l)
// Inserts an element in the List ordered by the field nickname. If the element could be inserted, the value true is returned; otherwise false is returned.
// Input : a video item, a position, a pointer to a list.
// Output: a boolean, 'true' if the list have been updated.
// PreCD : the specified position is a valid position in the list or a NULL_VIDEO position.
// PostCD: the positions of the elements in the list following that of the inserted one may have varied.
{
    // Declare a counter.
    tVideoPos c;

    // If there is no space left, cancel the operation.
    if(l->lastPos == MAX-1)
        return false;
    else {
        // Insert the item at the end.
        if(isEmptyListV(*l) || (strcmp(d.titleVideo, l->data[l->lastPos].titleVideo) > 0)) {
            // Move the limit once.
            l->lastPos++;
            // Insert the item in the space created
            l->data[l->lastPos] = d;
        }
        // Insert the item at any other position.
        else {
            // Move the limit once.
            l->lastPos++;
            // Search for the given position while moving every item to make space.
            for(c = l->lastPos; (c > 0) && (strcmp(d.titleVideo, l->data[c - 1].titleVideo) < 0); c--)
                l->data[c] = l->data[c - 1];
            l->data[c] = d;
        }

        return true;
    }
}

void updateItemV(tVideoItem d, tVideoPos p, tVideoList *l)
// Modifies the content of the element at the position we indicate.
// Input : a video item and a position and a pointer to a list.
// Output: an updated list (the item of that position changed).
// PreCD : the indicated position is a valid position in the list.
// PostCD: the order of the elements in the list has not been modified.
{
    // Change the data of the item with the one given.
    l->data[p] = d;
}

void deleteAtPositionV(tVideoPos p, tVideoList *l)
// Deletes the element at the given position from the list.
// Input : a position, a pointer to a list.
// Output: an updated list (the item of that position deleted).
// PreCD : the indicated position is a valid position in the list and its play list is empty.
// PostCD: the positions of the elements in the list following that of the deleted one may have varied.
{
    // Declare a counter.
    int c;

    // Move everything to the left until the given position.
    for(c = p; c <= l->lastPos; c++)
        l->data[c] = l->data[c + 1];
    // Move the limit to remove a space.
    l->lastPos--;
}

tVideoPos findItemV(tTitleVideo n, tVideoList l)
// Returns the position of the first element in the list whose nickname matches the
//   one indicated (or NULL_VIDEO if there is no such element).
// Input : a title and a pointer to the list.
// Output: the position of the item searched.
{
    // Declare a counter and a value to compare
    tVideoPos p;

    /*int cmp;
    //We see if the is any item
    if(l.lastPos == NULL_VIDEO)
        return NULL_VIDEO;
    else
    {
        //We compare the data with the nickname we are looking for
        cmp = strcmp(l.data[0].titleVideo,n);
        //And we do it for every position until we find it
        for (p = 0; (p < l.lastPos) && (cmp != 0); p++)
            cmp = strcmp(l.data[p+1].titleVideo,n);
        //If we found we confirm it
        if(cmp == 0)
            return p;
        else
            return NULL_VIDEO;
    }*/

    // Check if the list is empty or if the name isn't within the list's range.
    if ((NULL_VIDEO == l.lastPos) || (strcmp(n, l.data[0].titleVideo) < 0)
        || (strcmp(n, l.data[l.lastPos].titleVideo) > 0))
        return NULL_VIDEO;
    else {
        // Iterate through the list comparing the data with the video we are looking for until it's found.
        for (p = 0; (p <= l.lastPos) && (strcmp(n, l.data[p].titleVideo) > 0); p++);
        // If found, return the position of the item within the list.
        if (strcmp(l.data[p].titleVideo, n) == 0)
            return p;
        else
            return NULL_VIDEO;
    }
}

bool isEmptyListV(tVideoList l)
// Determines whether the list is empty or not.
// Input : a list.
// Output: a boolean 'true' if the list is empty.
{
    // Check if there are any items within the list.
    return (l.lastPos == NULL_VIDEO);
}

tVideoItem getItemV(tVideoPos p, tVideoList l)
// Retrieves the content of the element at the position we indicate.
// Input : a position and a list.
// Output: a video item.
// PreCD : the indicated position is a valid position in the list.
{
    // Return the data of the item
    return l.data[p];
}

tVideoPos firstV(tVideoList l)
// Returns the position of the first element of the list.
// Input : a list.
// Output: a position.
// PreCD : the list is not empty.
{
    return 0;
}

tVideoPos lastV(tVideoList l)
// Returns the position of the last element of the list.
// Input : a list.
// Output: a position.
// PreCD : the list is not empty.
{
    return l.lastPos;
}

tVideoPos previousV(tVideoPos p, tVideoList l)
// Returns the position preceding the one we indicate (or NULL_VIDEO if the specified position has no previous element).
// Input : a position and a list.
// Output: a position.
// PreCD : the indicated position is a valid position in the list.
{
    return --p;
}

tVideoPos nextV(tVideoPos p, tVideoList l)
// Returns the position preceding the one we indicate (or NULL_VIDEO if the specified position has no previous element).
// Input : a position and a list.
// Output: a position.
// PreCD : the indicated position is a valid position in the list.
{
    //We check we are no trying to surpass the length of the array
    if(p == l.lastPos)
        return NULL_VIDEO;
    else
        return ++p;
}
