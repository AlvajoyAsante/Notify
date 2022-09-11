/*
 *--------------------------------------
 * Program Name: DEMOA
 * Author: Alvajoy 'Alvajoy123' Asante
 * Description: Notify Demo Sender, Program store notification in stack.
 *--------------------------------------
*/

// Needed Headers
#include <tice.h>
#include <graphx.h>

#include "notify/notify.h"
#include "gfx/gfx.h"

// Colors used for demo
#define RED_INDEX      224
#define WHITE_INDEX    255
#define BLACK_INDEX    0

int main(void)
{
    int index; // used to get the stack index of the created notification (must be an 'int')

    // Delete all notifications in the stack for demo example.
    notify_DeleteAll();

    // Creates a notification with no icon.
    index = notify_Create(NULL, "DEMOA", "My no icon notify works!"); // Notification #1
    // For now your going to have to set the color each time you create a notification
    notify_SetColor(RED_INDEX, WHITE_INDEX, index);
    notify_SetTextColor(BLACK_INDEX, WHITE_INDEX, index);

    // Creates a notification with an icon. 
    index = notify_Create(chatbox, "DEMOA", "My icon notify works!"); // Notification #2
    // For now your going to have to set the color each time you create a notification
    notify_SetColor(RED_INDEX, WHITE_INDEX, index);
    notify_SetTextColor(BLACK_INDEX, WHITE_INDEX, index);

    return 0;
}
