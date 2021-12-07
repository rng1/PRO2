/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 3
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * GROUP: 6.1
 * DATE: 25 / 06 / 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif

void new(char *nick, char *cat, tList *list);
/*
* Goal  : add a new user, ordered alphabetically.
* Input :
*    - nick: a string representing the user's nickname.
*    -  cat: a string representing the user's category.
*    - list: the list where we wish to operate.
* Output: the list with the corresponding changes. If successful, with one more user.
* PreCD : the list must have been initialized and the string of the category must be one of the two existing options.
* PostCD: the positions of the elements in the list following that of the inserted user may have varied.
*/

void delete(char *nick, tList *list);
/*
* Goal  : delete the user that matches the indicated nickname.
* Input :
*    - nick: a string representing the user's nickname.
*    - list: the list where we wish to operate.
* Output: the list with the corresponding changes. If successful, with one less user.
* PreCD : the list must have been initialized.
* PostCD: the positions of the elements in the list following that of the deleted one may have varied.
*/

void play(char *nick, char *video, tList *list);
/*
* Goal  : modify the user that matches the indicated nickname, increasing the playtime of the specified video.
* Input :
*    -  nick: a string representing the user's nickname.
*    - video: a string representing the video title.
*    -  list: the list where we wish to operate.
* Output: the list with the corresponding changes. If successful, with his reproductions counter incremented by 1.
* PreCD : the list must have been initialized.
* PostCD: the order of the elements in the list has not been modified.
*/

void stats(tList *list);
/*
* Goal : print the list of users, its data and a table of the total number of users and their video list.
* Input:
*    - list: the list where we wish to operate.
* PreCD: the list must have been initialized.
*/

tItemL addUser(char *nick, char *cat);
/*
* Goal  : create a new item with the given nickname and category.
* Input :
*    - nick: a string representing the user's nickname.
*    -  cat: a string representing the user's category.
* Output: an element with the corresponding nickname and category,
*         with an empty video list and the total play time at zero.
* PreCD : the category must be one of the existing options.
*/

char* extractCategory(tItemL user);
/*
* Goal  : convert the item's category variable into a string.
* Input :
*    - user: the element from which we want to extract the category.
* Output: a string with one of the two categories.
* PreCD : the category must be one of the existing options.
*/

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *list)
/*
* Goal  : process each command available and print its respective information.
* Input :
*    - commandNumber: the assigned command number.
*    -       command: the command of the operation to use.
*    -        param1: first of the multipurpose parameters which will be used in the selected operation
*                    (nick, category, video title).
*    -        param2: second of the multipurpose parameters.
*    -          list: the list where we wish to operate.
* Output: the list with the corresponding changes (if any).
* PreCD : the list must have been initialized.
*/
{
    switch (command) {
            // [N]ew
        case 'N': {
            printf("********************\n");
            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);
            new(param1, param2, list);
            break;
        }
            // [D]elete
        case 'D': {
            printf("********************\n");
            printf("%s %c: nick %s\n", commandNumber, command, param1);
            delete(param1, list);
            break;
        }
            // [P]lay
        case 'P': {
            printf("********************\n");
            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);
            play(param1, param2, list);
            break;
        }
            // [S]tats
        case 'S': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            stats(list);
            break;
        }
            // Default
        default: {
            printf("+ Error: Process command not possible");
            break;
        }
    }
}


void readTasks(char *filename)
/*
* Goal  : read the input files and start each process.
* Input :
*    - filename: the filed used as input from which the instructions are readed.
* Output: the list with all the changes (if any).
* PreCD : the input file must be an existing one.
*/
{
    FILE *df;
    char *commandNumber, *command, *param1, *param2;

    // Create a temp list in case it needs to be implements in future functions.
    tList list;
    createEmptyList(&list);

    df = fopen(filename, "rb");
    if (df != NULL) {
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, &list);
        }
        fclose(df);

    } else
        printf("Cannot open file %s.\n", filename);
}

int main(int nargs, char **args) {

    char *file_name;

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}

void new(char *nick, char *cat, tList *list) {
    // Create an auxiliary item to add to the list.
    tItemL auxUser = addUser(nick,cat);

    // Check if the user is unique.
    if (LNULL == findItem(auxUser.nickname, *list)) {
        // Copy the temporary user to the empty position.
        if (insertItem(auxUser, list) == true)
            printf("* New: nick %s category %s\n", auxUser.nickname, extractCategory(auxUser));
        // ERROR
        else printf("+ Error: New not possible\n");
    }
    // ERROR
    else printf("+ Error: New not possible\n");
}

void delete(char *nick, tList *list) {
    // Create an auxiliary user and position to look for the item.
    tItemL auxUser;
    tPosL pos;
    // Declare a variable to copy the nickname to.
    tNickname tempNickname;

    // ERROR
    if (isEmptyList(*list) == true)
        printf("+ Error: Delete not possible\n");
    else
    {
        // Copy the nickname into a searchable variable.
        strcpy(tempNickname, nick);
        // Search if the user to be deleted exists.
        pos = findItem(tempNickname, *list);

        // Delete if it exists in that position.
        if (pos != LNULL) {
            // Get the user's data.
            auxUser = getItem(pos, *list);
            // Print the data of the user to be deleted.
            printf("* Delete: nick %s category %s numplays %d\n",
                   auxUser.nickname, extractCategory(auxUser), auxUser.numPlay);
            // Delete the user.
            deleteAtPosition(pos, list);
        }
        // ERROR
        else
            printf("+ Error: Delete not possible\n");
    }
}

void play(char *nick, char *video, tList *list) {
    // Create an auxiliary user and position to look for the item.
    tItemL auxUser;
    tPosL pos;
    // Declare a variable to copy the nickname to.
    tNickname tempNickname;

    //ERROR
    if (isEmptyList(*list) == true)
        printf("+ Error: Play not possible\n");
    else
    {
        // Copy the nickname into a searchable variable.
        strcpy(tempNickname, nick);
        // Check if the user exists.
        pos = findItem(tempNickname, *list);

        // Modify it if it exists in that position.
        if (pos != LNULL) {
            // Get the user's data.
            auxUser = getItem(pos, *list);
            // Modify the auxiliary user.
            auxUser.numPlay++;
            // Copy any changes to the list.
            updateItem(auxUser, pos, list);
            // Print the information of the operation.
            printf("* Play: nick %s plays video %s numplays %d\n", auxUser.nickname, video, auxUser.numPlay);
        }
            // ERROR
        else { printf("+ Error: Play not possible\n"); }
    }
}

void stats(tList *list) {
    // Declare a counter for the positions and an auxiliary user to extract its information.
    tPosL pos;
    tItemL auxUser;

    float numStandard = 0, numPremium = 0;      // Number of users in each category.
    float playStandard = 0, playPremium = 0;    // Number of videos played by each category.
    float avgStandard, avgPremium;              // Average videos played per user of each category.

    //ERROR
    if (isEmptyList(*list) == true)
        printf("+ Error: Stats not possible\n");
    else {
        // Look for the position of the first user.
        pos = first(*list);
        // Create a loop which shows the current user and searches for the next one.
        do {
            // Extract the user's information.
            auxUser = getItem(pos, *list);

            // Count the number of user per category and the sum of their played videos.
            if (auxUser.userCategory == 0) {
                // Add one to the total of standard users.
                numStandard++;
                // Add the number of reproductions.
                playStandard += auxUser.numPlay;
            } else {
                // Add one to the total of premium users.
                numPremium++;
                // Add the number of reproductions.
                playPremium += auxUser.numPlay;
            }
            // Print the current user.
            printf("Nick %s category %s numplays %d\n",
                   auxUser.nickname, extractCategory(auxUser), auxUser.numPlay);
            // Move on to the next user.
            pos = next(pos, *list);
        } while (pos != LNULL);

        // Calculate the average number of reproductions per category.
        if (numStandard == 0)
            avgStandard = 0;
        else
            avgStandard = playStandard / numStandard;
        if (numPremium == 0)
            avgPremium = 0;
        else
            avgPremium = playPremium / numPremium;

        // Print all the information regarding the number of users and videos played.
        printf("%8s   %5s  %5s  %7s\n", "Category", "Users", "Plays", "Average");
        printf("%8s    %-4.0f  %-5.0f %-7.2f\n", "Standard", numStandard, playStandard, avgStandard);
        printf("%-8s    %-4.0f  %-5.0f %-7.2f\n", "Premium", numPremium, playPremium, avgPremium);
    }
}

tItemL addUser(char *nick, char *cat) {
    // Create a user.
    tItemL user;
    // Copy the nickname to the user item.
    strcpy(user.nickname, nick);
    // Compare the category parameter and set it accordingly to the user.
    if (strcmp(cat, "standard") == 0)
        user.userCategory = standard;
    else
        user.userCategory = premium;
    // Set the number of reproductions to zero.
    user.numPlay = 0;

    return user;
}

char* extractCategory(tItemL user) {
    // Create the variable for the auxiliary category.
    char* auxCategory = (char *)malloc(sizeof(char));

    // Translate the category to text.
    if (user.userCategory == standard)
        strcpy(auxCategory, "standard");
    else
        strcpy(auxCategory, "premium");

    return auxCategory;
}

