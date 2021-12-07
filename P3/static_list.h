/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 3
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * GROUP: 6.1
 * DATE: 25 / 06 / 21
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include <stdbool.h>
#include "types.h"

#define LNULL (-1)
#define MAX 25

/** type declaration **/
typedef int tPosL;

typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
} tList;

/** function prototypes **/
// Generators
void createEmptyList(tList *l);
/*
* Goal  : creates an empty list.
* Input :
*    - l: a pointer to a list.
* Output: an empty list.
* PostCD: the list is initialised and has no elements.
*/

bool insertItem(tItemL d, tList *l);
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

void updateItem(tItemL d, tPosL p, tList *l);
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


// Destructors
void deleteAtPosition(tPosL p, tList *l);
/*
* Goal  : deletes the element from the list at the given position.
* Input :
*    - p: a position.
*    - l: a pointer to a list.
* Output: an updated list (the item of that position deleted).
* PreCD : the indicated position is a valid position in the list and its play list is empty.
* PostCD: the positions of the elements in the list following that of the deleted one may have varied.
*/


// Observers
bool isEmptyList(tList l);
/*
* Goal  : determines whether the list is empty or not.
* Input :
*    - l: a list.
* Output: a boolean 'true' if the list is empty.
*/

tPosL findItem(tNickname n, tList l);
/*
* Goal  : returns the position of the first element in the list whose nickname matches the
*         one indicated (or NULL if there is no such element).
* Input :
*    - n: a nickname.
*    - l: the list to look through.
* Output: the position of the item searched.
*/

tItemL getItem(tPosL p, tList l);
/*
* Goal  : retrieves the content of the element at the position we indicate.
* Input :
*    - p: a position.
*    - l: a list.
* Output: an item.
* PreCD : the indicated position is a valid position in the list.
*/

tPosL first(tList l);
/*
* Goal  : returns the position of the first element of the list.
* Input :
*    - l: a list.
* Output: a position.
* PreCD : the list is not empty.
*/

tPosL last(tList l);
/*
* Goal  : returns the position of the last element of the list.
* Input :
*    - l: a list
* Output: a position.
* PreCD : the list is not empty.
*/

tPosL next(tPosL p, tList l);
/*
* Goal  : returns the position preceding the one we indicate (or NULL_VIDEO if the specified position has no previous element).
* Input :
*    - p: a position.
*    - l: a list.
* Output: a position.
* PreCD : the indicated position is a valid position in the list.
*/

tPosL previous(tPosL p, tList l);
/*
* Goal  : returns the position preceding the one we indicate (or NULL_VIDEO if the specified position has no previous element).
* Input :
*    - p: a position.
*    - l: a list.
* Output: a position.
* PreCD : the indicated position is a valid position in the list.
*/

#endif
