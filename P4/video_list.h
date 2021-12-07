/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 4
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * GROUP: 6.1
 * DATE: 25 / 06 / 21
 */

#ifndef P4_VIDEO_LIST_H
#define P4_VIDEO_LIST_H

#include <stdbool.h>
#include "types.h"

#define NULL_VIDEO -1
#define MAX 25

/** type declaration */

typedef int tVideoPos;

typedef struct {
    tVideoItem data[MAX];
    tVideoPos lastPos;
} tVideoList;

/** function prototypes */

void createEmptyListV (tVideoList *l);
// Creates an empty list.
// PostCD: the list is initialised and has no elements.
// Input : a pointer to a list.
// Output: an empty list.

bool insertItemV(tVideoItem d, tVideoList *l);
// Inserts an element in the List ordered by the field nickname. If the element could be inserted, the value true is returned; otherwise false is returned.
// PreCD : the specified position is a valid position in the list or a NULL_VIDEO position.
// PostCD: the positions of the elements in the list following that of the inserted one may have varied.
// Input : a video item, a position, a pointer to a list.
// Output: a boolean, 'true' if the list have been updated.

void updateItemV(tVideoItem d, tVideoPos p, tVideoList *l);
// Modifies the content of the element at the position we indicate.
// PreCD : the indicated position is a valid position in the list.
// PostCD: the order of the elements in the list has not been modified.
// Input : a video item and a position and a pointer to a list.
// Output: An updated list (the item of that position changed).

void deleteAtPositionV(tVideoPos p, tVideoList *l);
// Deletes the element at the given position from the list.
// PreCD : the indicated position is a valid position in the list and its play list is empty.
// PostCD: the positions of the elements in the list following that of the deleted one may have varied.
// Input : a position, a pointer to a list.
// Output: an updated list (the item of that position deleted).

bool isEmptyListV(tVideoList l);
// Determines whether the list is empty or not.
// Input : a pointer to a list.
// Output: a boolean 'true' if the list is empty.

tVideoPos findItemV(tNickname n, tVideoList l);
// Returns the position of the first element in the list whose nickname matches the
// one indicated (or NULL_VIDEO if there is no such element).
// Input : a title and a pointer to the list.
// Output: the position of the item searched.

tVideoItem getItemV(tVideoPos p, tVideoList l);
// Retrieves the content of the element at the position we indicate.
// PreCD : the indicated position is a valid position in the list.
// Input : a position and a pointer to a list.
// Output: a video item.

tVideoPos firstV(tVideoList l);
// Returns the position of the first element of the list.
// PreCD : the list is not empty.
// Input : a pointer to a list.
// Output: a position.

tVideoPos lastV(tVideoList l);
// Returns the position of the last element of the list.
// PreCD : the list is not empty.
// Input : a pointer to a list.
// Output: a position.

tVideoPos nextV(tVideoPos p, tVideoList l);
// Returns the position preceding the one we indicate (or NULL_VIDEO if the specified position has no previous element).
// PreCD : the indicated position is a valid position in the list.
// Input : a position and a pointer to a list.
// Output: a position.

tVideoPos previousV(tVideoPos p, tVideoList l);
// Returns the position preceding the one we indicate (or NULL_VIDEO if the specified position has no previous element).
// PreCD : the indicated position is a valid position in the list.
// Input : a position and a pointer to a list.
// Output: a position.

#endif //P4_VIDEO_LIST_H

