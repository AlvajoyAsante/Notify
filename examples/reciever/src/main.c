/*
 *--------------------------------------
 * Program Name: DEMOB
 * Author: Alvajoy 'Alvajoy123' Asante
 * Description: Notify Demo Reciever, The program displays the notification before closing.
 *--------------------------------------
*/

// Needed Headers
#include <tice.h>
#include <graphx.h>
#include "notify/notify.h"


void PrintCentered(const char *str);

int main(void)
{
    int index = 0;

    /* Initialize graphics drawing */
    gfx_Begin();


    // notify_Alert returns -1 if there is nothing to show index will equal to -1 and the loop ends
    while (index != -1){
        gfx_FillScreen(255);
        PrintCentered("Notify Reciever");
        
        /* Display Notification */
        gfx_SetColor(224);
        index = notify_Alert(); 

        /* Waits for a key */
        if (index != -1) {
            while (!os_GetCSC());
        }
    }

    /* End graphics drawing */
    gfx_End();

    return 0;
}

/*  */
void PrintCentered(const char *str)
{
    gfx_PrintStringXY(str,
                      (GFX_LCD_WIDTH - gfx_GetStringWidth(str)) / 2,
                      (GFX_LCD_HEIGHT - 8) / 2);
}