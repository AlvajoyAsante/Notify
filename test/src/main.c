/*
 *--------------------------------------
 * Program Name: NTEST
 * Author: Alvajoy 'Alvajoy123' Asante
 * Description: Notify test, This program makes sure that programs can compile with notify.
 *--------------------------------------
*/

// Needed Headers
#include <tice.h>
#include <graphx.h>

#include "notify/notify.h"

#define RED_INDEX      224
#define WHITE_INDEX    255
#define BLACK_INDEX    0

int main(void)
{    
    notify_Create(NULL, "TEST", "TEST");

    gfx_Begin();

    gfx_SetColor(RED_INDEX);
    notify_Alert(); 
    
    while (!os_GetCSC());
    
    gfx_End();

    return 0;
}
