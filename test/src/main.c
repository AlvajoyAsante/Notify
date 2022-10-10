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

int main(void)
{   

    if (notify_Create(NULL, "TEST", "TEST") == -1) goto end;

    gfx_Begin();

    gfx_SetColor(RED_INDEX);
    if (notify_Alert() == -2) goto end; 
    
    while (!os_GetCSC());
    

end:    
    gfx_End();
    return 0;
}
