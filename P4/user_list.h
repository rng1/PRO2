/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 4
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef P4_USER_LIST_H
#define P4_USER_LIST_H

#include <stdbool.h>
#include "types.h"
#include "video_list.h"

#define NULL_USER NULL

/** type declaration */

typedef struct {
    tNickname nickname ;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tVideoList videoList;
} tUserItem;

typedef struct tUserNode *tUserPos;
struct tUserNode {
    tUserItem data;
    tUserPos next;
};

typedef tUserPos tUserList;

/** function prototypes */

void createEmptyList (tUserList* l);
// Creates an empty list.
// PostCD: the list is initialised and has no elements.
// Input : a pointer to a list.
// Output: an empty list.

bool insertItem(tUserItem d, tUserList* l);
// Inserts an element containing the provided data item in the list. If the specified
//   position is NULL_USER, then the element is added at the end of the list; otherwise, it will
//   be placed right before the element currently holding that position. It the element
//   could be inserted, the value true is returned, false otherwise.
// PreCD : the specified position is a valid position in the list or a NULL_USER position.
// PostCD: the positions of the elements in the list following that of the inserted one may have varied.
// Input : a user item, a position, a pointer to a list.
// Output: a boolean, 'true' if the list have been updated.

void updateItem(tUserItem d, tUserPos p, tUserList* l);
// Modifies the content of the element at the position we indicate.
// PreCD : the indicated position is a valid position in the list.
// PostCD: the order of the elements in the list has not been modified.
// Input : a user item and a position and a pointer to a list.
// Output: an updated list (the item of that position changed).

void deleteAtPosition(tUserPos p, tUserList* l);
// Deletes the element at the given position from the list.
// PreCD : the indicated position is a valid position in the list.
// PostCD: the positions of the elements in the list following that of the deleted one may have varied.
// Input : a position, a pointer to a list.
// Output: an updated list (the item of that position deleted).

bool isEmptyList(tUserList l);
// Determines whether the list is empty or not.
// Input : a pointer to a list.
// Output: a boolean 'true' if the list is empty.

tUserPos findItem(tNickname, tUserList);
// Returns the position of the first element in the list whose nickname matches the
//   one indicated (or NULL_USER if there is no such element).
// Input : a nickname and a pointer to the list.
// Output: the position of the item searched.

tUserItem getItem(tUserPos p, tUserList l);
// Retrieves the content of the element at the position we indicate.
// PreCD : the indicated position is a valid position in the list.
// Input : a position and a pointer to a list.
// Output: a user item.

tUserPos first(tUserList l);
// Returns the position of the first element of the list.
// PreCD : the list is not empty.
// Input : a pointer to a list.
// Output: a position.

tUserPos last(tUserList l);
// Returns the position of the last element of the list.
// PreCD : the list is not empty.
// Input : a pointer to a list.
// Output: a position.

tUserPos previous(tUserPos p, tUserList l);
// Returns the position preceding the one we indicate (or NULL_USER if the specified position has no previous element).
// PreCD : the indicated position is a valid position in the list.
// Input : a position and a pointer to a list.
// Output: a position.

tUserPos next(tUserPos p, tUserList l);
// Returns the position following that one we indicate (or NULL_USER if the specified position has no next element).
// PreCD : the indicated position is a valid position in the list.
// Input : a position and a pointer to a list.
// Output: a position.

#endif //P4_USER_LIST_H