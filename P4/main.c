/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 4
 * AUTHOR 1: Martin do Rio Rico LOGIN 1: martin.dorio
 * AUTHOR 2: Rodrigo Naranjo Gonzalez LOGIN 2: r.naranjo
 * GROUP: 6.1
 * DATE: 25 / 06 / 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "video_list.h"
#include "user_list.h"

#define MAX_BUFFER 255

//THING TO DO...
/**
 * 1. WRITE THE SPECIFICATION OF FUNCTIONS LIKE MAIN
 * 2. COMMENT THE FUNCTIONS YOU CREATED
 * 3. FINISH WRITING THE CHANGES MADE
 */

//LIST OF MISTAKES
/**
 * (CHECK) Direct access to the intern implementation.
 * (CHECK) In the function statsV, the loop uses integers as positions.
 * (CHECK) In the function deleteV, there is a direct access to the static list's lastPos

 * (CHECK) The operation findItem is inefficient.
 * (QUESTION) The operation deleteAtPosition is inefficient.
 * (CHECK) The function play is inefficient.
 * (CHECK) The function remove is inefficient.

 * (CHECK) In the functions delete and remove the user with the newly empty video list is not updated before deleting it.
 * (QUESTION) Doesn't reference necessary parameters in the function deleteV.
 * (CHECK) Reference unnecessary parameters in many functions.

 * (WAITING) The specification of some functions are missing

 * (CHECK) Use of enumeration as int instead of standard or premium.
 * (CHECK) Excessive use of unnecessary getItem or findItem instead od using auxiliary variables.
 * (CHECK) Introduce declarations of variables in the middle of the code.
 * (CHECK) Local variables without or indirectly commented.
 */

//LIST OF CHANGES
/**
 * We omitted some auxiliary variables that could be substituted by the function directly such as findItem and extractCategory.
 * We moved all declarations of variables to the top of the function.
 * We deleted redundant variables.
 * The operations containing categories has been updated to use standard or premium instead of an int.

 * We fixed the direct access to the intern implementation.
 * In the function statV, the loop uses now positions as intended.
 * In the function deleteV, the changed the condition so it doesn't use lastPos.

 * We revised and optimized the functions findItem, play and remove.

 * Now in the functions delete and remove the empty video list is updated before deleting the user.
 * Now all functions don't print the instructions themselves so they have no unnecessary parameters.
 */

void new(char *nick, char *cat, tUserList *list);
/**
  * Goal  : add a new user, ordered alphabetically.
  * Input :
  *    - nick: a string representing the user's nickname.
  *    -  cat: a string representing the user's category.
  *    - list: the list where we wish to operate.
  * Output: the list with the corresponding changes. If successful, with one more user.
  * PreCD : the list must have been initialized and the string of the category must be one of the two existing options.
  * PostCD: the positions may have varied because the elements in the list are still ordered by nickname.
*/

void delete(char *nick, tUserList *list);
/**
  * Goal  : delete the user that matches the indicated nickname.
  * Input :
  *    - nick: a string representing the user's nickname.
  *    - list: the list where we wish to operate.
  * Output: the list with the corresponding changes. If successful, with one less user.
  * PreCD : the list must have been initialized.
  * PostCD: the positions of the elements in the list following that of the deleted one may have varied.
 */

void deleteV(tUserPos pos, tUserList *list);
/**
  * Goal  : delete all videos of the indicated user's list.
  * Input :
  *    -  pos: the position of the user within the list.
  *    - list: the list where we wish to operate.
  * Output: the list with the corresponding changes.
  * PreCD : the list must have been initialized.
 */

void stats(tUserList *list);
/**
  * Goal : print the list of users, its data, and a table of the total number of users and their video list.
  * Input:
  *    - list: the list where we wish to operate.
  * PreCD: the list must have been initialized.
*/

void statsV(tUserItem user);
/**
  * Goal : print the list of videos of a user.
  * Input:
  *    - user: the user from which the infor is extracted.
  * PreCD: the list must have been initialized.
*/

void add(char *nick, char *title, tUserList *list);
/**
  * Goal  : add a new video to a user's list.
  * Input :
  *    - nick: a string representing the user's nickname.
  *    -  cat: a string representing the video title.
  *    - list: the list where we wish to operate.
  * Output: the list with the corresponding changes. If successful, with a video added to the specified user.
  * PreCD : the list must have been initialized.
  * PostCD: the order of the elements in the list has not been modified.
*/

void play(char *nick,char *title, char *min, tUserList *list);
/**
  * Goal  : modify the user that matches the indicated nickname, adding the given number to the playtime of the
  *         specified video.
  * Input :
  *    -  nick: a string representing the user's nickname.
  *    -   cat: a string representing the video title.
  *    - title: a string representing the number of minutes to be added, later converted to a number.
  *    -  list: the list where we wish to operate.
  * Output: the list with the corresponding changes. If successful,
  * PreCD : the list must have been initialized.
  * PostCD: the order of the elements in the list has not been modified.
 */

void removes(char *min, tUserList *list);
/**
  * Goal  : delete the standard users that surpassed the indicated limit of minutes.
  * Input : the command, its number, a string representing the max play time allowed, and the list where we operate.
  *    -  min: a string representing the max play time allowed.
  *    - list: the list where we wish to operate.
  * Output: the list with the corresponding changes. If successful, with less elements.
  * PreCD : the list must have been initialized.
  * PostCD: the positions of the elements in the list may have varied.
*/

void applyPromo(tUserList *list);
/**
  * Goal  : puts the counter of the standard users that fulfil the next requisites
  *     - have at least 30 minutes less that the standard user with more play time
  *     - have more than 4 videos with a play time bigger than 0
  * Input :
  *    - list: the list where we wish to operate.
  * Output: the list with the corresponding changes.
  * PreCD : the list must have been initialized.
*/

tUserItem newUser(char *nick, char *cat);
/**
  * Goal  : create a new item with the given nickname and category.
  * Input :
  *    - nick: a string representing the user's nickname.
  *    -  cat: a string representing the user's category.
  * Output: an element with the corresponding nickname and category,
  *         with an empty video list and the total play time at zero.
  * PreCD : the category must be one of the two already existing options.
*/

tVideoItem newVideo(char *title);
/**
  * Goal  : create a new video with the given title.
  * Input :
  *    - title: a string representing the video title.
  * Output: an video with the corresponding title within the user's list.
  * PreCD : the category must be one of the two already existing options.
*/

char* extractCategory(tUserItem user);
/**
  * Goal  : convert the item's category variable into a string.
  * Input :
  *    - user: the element from which we want to extract the category.
  * Output: a string with one of the two categories.
 */

int maxPlayTime(tUserList *list);

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tUserList *list) {

    switch(command) {
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
            // [A]dd
        case 'A': {
            printf("********************\n");
            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);
            add(param1, param2, list);
            break;
        }
            // [S]tats
        case 'S': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            stats(list);
            break;
        }
            // [P]lay
        case 'P': {
            printf("********************\n");
            printf("%s %c: nick %s video %s minutes %s\n", commandNumber, command, param1, param2, param3);
            play(param1, param2, param3, list);
            break;
        }
            // [R]emoves
        case 'R': {
            printf("********************\n");
            printf("%s %c: maxtime %s\n", commandNumber, command, param1);
            removes(param1, list);
            break;
        }
            // applyPro[M]o
        case 'M': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            applyPromo(list);
            break;
        }
        default: {
            break;
        }
    }
}

void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2, *param3;

    // Create a temp list in case it needs to be implemented in future functions.
    tUserList list;
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
            param3 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, param3, &list);
        }
        fclose(df);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
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

void new(char *nick, char *cat, tUserList *list) {
    // Create an auxiliary item to add to the list.
    tUserItem auxUser = newUser(nick,cat);
    // Check if the user is unique.
    if (NULL_USER == findItem(auxUser.nickname, *list)) {
        // Copy the temporary user to the empty position.
        if (insertItem(auxUser, list) == true) { printf("* New: nick %s category %s\n", auxUser.nickname, extractCategory(auxUser)); }
        /**ERROR*/
        else { printf("+ Error: New not possible\n"); }
    }
    /**ERROR*/
    else { printf("+ Error: New not possible\n"); }
}

void delete(char *nick, tUserList *list) {
    //We declare an auxiliary user to extract the information for printing.
    tUserItem auxUser;
    //We declare a position to search for the item.
    tUserPos pos;
    //We declare a nickname to copy the string that contains the nickname.
    tNickname tempNickname;

    /**ERROR*/
    if (isEmptyList(*list) == true) { printf("+ Error: Delete not possible\n"); }
    else
    {
        // Copy the nickname into a searchable variable.
        strcpy(tempNickname, nick);
        // Check if the user to be deleted exists.
        pos = findItem(tempNickname, *list);
        // Delete if it exists in that position.
        if (pos == NULL_USER) { printf("+ Error: Delete not possible\n"); }
        else {
            // Create an auxiliary user.
            auxUser = getItem(pos, *list);
            printf("* Delete: nick %s category %s total play time %d\n", auxUser.nickname, extractCategory(auxUser), auxUser.totalPlayTime);
            // Empty the video list and then we delete the user
            deleteV(pos, list);
            deleteAtPosition(pos, list);
        }
    }
}

void deleteV(tUserPos pos, tUserList *list) {
    // Create an auxiliary user.
    tUserItem user = getItem(pos, *list);
    // Create a position to work as a counter.
    tVideoPos c = firstV(user.videoList);
    // Delete each video of the list.
    for(c = firstV(user.videoList); !isEmptyListV(user.videoList); c = firstV(user.videoList)) { deleteAtPositionV(c, &user.videoList); }
    /* while(!isEmptyListV(user.videoList)) {
        deleteAtPositionV(c, &user.videoList);
        c = firstV(user.videoList);
    } */
    //We update the user with the empty list
    updateItem(user, pos, list);
}

void stats(tUserList* list) {
    //We declare an auxiliary user to extract the information for printing.
    tUserItem auxUser;
    //We declare a position to search for the item.
    tUserPos pos;
    //We declare a nickname to copy the string that contains the nickname.
    tNickname tempNickname;
    // Create variables for the play time
    tPlayTime auxTime;
    // Create variables for total play time of each category.
    tPlayTime playTimeStandard = 0, playTimePremium = 0;
    // Create variables for the number of users and the average.
    double numStandard = 0, numPremium = 0, avgStandard, avgPremium;
    /**ERROR*/
    if (isEmptyList(*list) == true) { printf("+ Error: Stats not possible\n"); }
    else {
        // Look for the position of the first user.
        pos = first(*list);
        // Create a loop which shows the current user and searches for the next one.
        do {
            // Extract the user.
            auxUser = getItem(pos, *list);
            // Extract the user's play time.
            auxTime = auxUser.totalPlayTime;
            // Add one to the total of standard users and add its play time to the total.
            if (extractCategory(auxUser) == 0) {
                numStandard++;
                playTimeStandard += auxTime;
            }
            // Add one to the total of premium users and add its play time to the total.
            else {
                numPremium++;
                playTimePremium += auxTime;
            }
            // Print the current user.
            printf("*Nick %s category %s totalplaytime %d\n", auxUser.nickname, extractCategory(auxUser), auxTime);
            // Print the list of videos and get the total playtime.
            statsV(auxUser);
            // Move on to the next user.
            pos = next(pos, *list);
        } while (pos != NULL_USER);
        // Calculate the number of reproductions per category, avoiding zero in the numerator.
        if (numStandard == 0) { avgStandard = 0; }
        else { avgStandard = playTimeStandard / numStandard; }
        if (numPremium == 0) { avgPremium = 0; }
        else { avgPremium = playTimePremium / numPremium; }
        // Print the table.
        printf("Category  Users  TimePlay  Average\n");
        printf("Standard %6.0f %9d %8.2f\n", numStandard, playTimeStandard, avgStandard);
        printf("Premium  %6.0f %9d %8.2f\n", numPremium, playTimePremium, avgPremium);
    }
}

void statsV(tUserItem user) {
    // Create an auxiliary video.
    tVideoItem auxVideo;
    // Create a position to work as a counter.
    tVideoPos c;
    // Check if the video list is empty.
    if(isEmptyListV(user.videoList)) { printf("No videos\n"); }
    else {
        // Extract and print each video in the list.
        for (c = firstV(user.videoList); c != NULL_VIDEO; c = nextV(c, user.videoList)) {
            auxVideo = getItemV(c,user.videoList);
            printf("Video %s playtime %d\n", auxVideo.titleVideo, auxVideo.playTime);
        }
    }
}

void add(char *nick, char *title, tUserList *list) {
    // Create a variable to insert the nickname
    tNickname tempNickname;
    // Copy the nickname into a searchable variable.
    strcpy(tempNickname, nick);
    // Create an auxiliary item to modify the video list.
    tUserPos pos = findItem(tempNickname, *list);
    // Create an auxiliary user.
    tUserItem user;
    // Create an auxiliary video.
    tVideoItem video;
    /**ERROR*/
    if (pos == NULL_USER) { printf("+ Error: Add not possible\n"); }
    else {
        // Create an auxiliary user.
        user = getItem(pos, *list);
        // Create a new video to add to the list.
        video = newVideo(title);
        /**ERROR*/
        if (findItemV(video.titleVideo, user.videoList) != NULL_VIDEO) { printf("+ Error: Add not possible\n"); }
        else {
            /**ERROR*/
            if (insertItemV(video, &user.videoList) != true) { printf("+ Error: Add not possible\n"); }
            // Update and print the video added.
            else {
                updateItem(user, pos, list);
                printf("* Add: nick %s adds video %s\n", user.nickname, video.titleVideo);
            }
        }
    }
}

void play(char *nick, char *title, char *min, tUserList* list) {
    // Create a variable to convert the parameter into a number
    int playTime = atoi(min);
    // Create a variable to copy the nickname into a string to be able to search.
    tNickname tempNickname;
    strcpy(tempNickname, nick);
    // Create a variable to copy the title into a string to be able to search.
    tTitleVideo tempVideo;
    strcpy(tempVideo, title);
    // Create an auxiliary user and video to update.
    tUserItem user;
    tVideoItem video;
    // Create a position to search for an user and a video.
    tUserPos pos;
    tVideoPos posV;
    /**ERROR*/
    if (isEmptyList(*list) == true) { printf("+ Error: Play not possible\n"); }
    else {
        // Check if the user to be changed exists.
        pos = findItem(tempNickname, *list);
        /**ERROR*/
        if (pos == NULL_USER) { printf("+ Error: Play not possible\n"); }
        else {
            // Create an auxiliary user
            user = getItem(pos, *list);
            // Check if the video exists in the user's list.
            posV = findItemV(tempVideo, user.videoList);
            /**ERROR*/
            if (posV == NULL_VIDEO) { printf("+ Error: Play not possible\n"); }
            else {
                // Extract the video.
                video = getItemV(posV, user.videoList);
                // Change the play time.
                video.playTime += playTime;
                user.totalPlayTime += playTime;
                // Update the video.
                updateItemV(video, posV, &user.videoList);
                updateItem(user, pos, list);
                // Create a new auxiliary user and video, already updated to print.
                printf("* Play: nick %s plays video %s playtime %d\n", user.nickname, title, video.playTime);
            }
        }
    }
}

void removes(char *min, tUserList* list)
{
    // Create a variable to convert the parameter into numbers.
    tPlayTime maxTime = atoi(min);
    // Create an auxiliary user.
    tUserItem auxUser;
    // Create a counter of the number of users removed.
    int c = 0;
    // Create a counter for the loop to check when something is deleted.
    tUserPos p, q;
    /**ERROR*/
    if (isEmptyList(*list) == true) { printf("+ Error: Remove not possible\n"); }
    else {
        p = NULL_USER;
        q = first(*list);
        do {
            // Extract this position user.
            auxUser = getItem(q, *list);
            // Check it's category and if it exceeds the limit.
            if ((auxUser.totalPlayTime > maxTime) && (auxUser.userCategory == standard)) {
                // Empty the video list and then we delete the user.
                deleteV(q, list);
                deleteAtPosition(q, list);
                printf("Removing nick %s totalplaytime %d\n", auxUser.nickname, auxUser.totalPlayTime);
                // Keep track of how many user are deleted.
                c++;
                // Check if that was the last element of the list.
                if (isEmptyList(*list)) { break; }
            }
            else { p = q; }
            if (p == NULL_USER) { q = first(*list); }
            else { q = next(p, *list); }
        } while (q != NULL_USER);
        /*while(pos != NULL_USER)
        {
            // Extract this position user.
            auxUser = getItem(pos, *list);
            deleted = false;
            } else
                pos = next(pos,*list);
        }*/
        // Check if no users were deleted
        if(c == 0) { printf("+ Error: Remove not possible\n"); }
    }
}

void applyPromo(tUserList *list) {
    // Counter for number of videos with playtime and the total number of users to whom the offer has been applied.
    int numV, totalPromos = 0;
    // Create an auxiliary user, video, and its respective counters.
    tUserItem auxUser;
    tUserPos userCount;
    tVideoItem auxVideo;
    tVideoPos videoCount;
    /**ERROR*/
    if(isEmptyList(*list)) { printf("+ Error: ApplyPromo not possible\n"); }
    else {
        // Iterate through the users of the list.
        for (userCount = first(*list); userCount != NULL_USER; userCount = next(userCount, *list)) {
            numV = 0;
            auxUser = getItem(userCount, *list);
            // Iterate through the list of videos embedded with each user.
            for (videoCount = firstV(auxUser.videoList); videoCount != NULL_VIDEO; videoCount = nextV(videoCount, auxUser.videoList)) {
                auxVideo = getItemV(videoCount, auxUser.videoList);
                // If the play time is greater than zero, count it towards the total number of videos.
                if (auxVideo.playTime > 0) { numV++; }
            }
            // Look if the user fulfil the requesites to apply the promo
            if ((auxUser.userCategory == standard) && (numV >= 4) && (maxPlayTime(list) - auxUser.totalPlayTime <= 30)) {
                auxUser.totalPlayTime = 0;
                printf("* ApplyPromo: nick %s\n", auxUser.nickname);
                totalPromos++;
                updateItem(auxUser, userCount, list);
            }
        }
        /**ERROR*/
        if (totalPromos == 0) { printf("+ Error: ApplyPromo not possible\n"); }
        else { printf("* Promo applied to %d users\n", totalPromos); }
    }
}

tUserItem newUser(char *nick, char *cat) {
    // Create a user.
    tUserItem user;
    // Copy the nickname to the user item.
    strcpy(user.nickname, nick);
    // Compare the category parameter and set it accordingly to the user.
    if (strcmp(cat, "standard") == 0)
        user.userCategory = standard;
    else
        user.userCategory = premium;
    // Set the number of reproductions to zero.
    user.totalPlayTime = 0;
    // Create an empty video list for the user.
    createEmptyListV(&user.videoList);
    return user;
}

tVideoItem newVideo(char *title) {
    // Create a video item.
    tVideoItem video;
    // Copy the title to the auxiliary video.
    strcpy(video.titleVideo, title);
    // Set the play time to 0.
    video.playTime = 0;
    return video;
}

char* extractCategory(tUserItem user) {
    // Create the variable for the auxiliary category.
    char* auxCategory = (char *)malloc(sizeof(char));
    // Translate the category to text.
    if (user.userCategory == standard) { strcpy(auxCategory, "standard"); }
    else { strcpy(auxCategory, "premium"); }
    return auxCategory;
}

int maxPlayTime(tUserList *list) {
    int max = 0;
    tUserPos c;
    tUserItem auxUser;
    for (c = first(*list); c != NULL_USER; c = next(c, *list)) {
        auxUser = getItem(c, *list);
        if ((auxUser.userCategory == standard) && (max < auxUser.totalPlayTime)) { max = auxUser.totalPlayTime; }
    }
    return max;
}
