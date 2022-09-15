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
    // Delete all notifications in the stack for demo example.
    notify_DeleteAll();

    // Creates a notification with no icon.
    notify_Create(NULL, "DEMOA", "My no icon notify works!");

    // Creates a notification with an icon. 
    notify_Create(chatbox, "DEMOA", "My icon notify works!");

    return 0;
}
