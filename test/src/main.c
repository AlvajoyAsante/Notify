/*
 *--------------------------------------
 * Program Name: TEST
 * Author: Alvajoy 'Alvajoy123' Asante
 * Description: Notify test, This program makes sure that programs can compile with notify.
 *--------------------------------------
 */


#include <tice.h>
#include <graphx.h>

#include "notify/notify.h"

#define RED_COLOR_INDEX 224

int main(void)
{
    gfx_Begin();

    if (notify_Create(NULL, "TEST", "TEST") != NULL)
        goto end;

    gfx_SetColor(RED_COLOR_INDEX);

    if (!notify_Alert())
        goto end;

    while (!os_GetCSC());

end:
    gfx_End();
    return 0;
}
