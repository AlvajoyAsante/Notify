#include "notify.h"
#include "notify_save.h"

struct notify_t *notify;
uint8_t notify_amount;

// Creating notifications.
int notify_Create(gfx_sprite_t *icon, char title[9], char text[30])
{
	struct notify_t *curr_index;
	
	notify_Load();
	
	if (notify_amount < 255){
		notify_amount++;
		notify = realloc(notify, notify_amount * sizeof(struct notify_t));
		curr_index = &notify[notify_amount - 1];
	
		strncpy(curr_index->title, title, 9);
		strncpy(curr_index->text, text, 30);
	
		if (icon != NULL) {
			curr_index->icon = icon;
		}else{
			curr_index->icon = NULL;
		}
		
		return notify_amount - 1;

	}else{
		return -1;
	}
	
	notify_Save();
}

// Deleting notifications.
void notify_Delete(uint8_t index)
{
	notify_Load();
	
	if (notify_amount > 0){
		notify_amount--;
        notify[index] = notify[notify_amount];
        notify = realloc(notify, notify_amount * sizeof(struct notify_t));
    }
	
	notify_Save();
}

void notify_DeleteAll(void)
{
	// Set the notification amount in stack to zero
	notify_amount = 0;

	// Set the size of the stack to the orignal size.
	notify = realloc(notify, sizeof(struct notify_t));
	
	// Saves and free the daata
	notify_Save();
}

/**
 * This function renders a filled round rectangle depending on the type on "type" (read the .h file for more).
 */
 // copied from oxygen
static void oxy_FillRoundRectangle(uint16_t x, uint8_t y, int w, uint8_t h, uint8_t type)
{
	switch (type){
		case 0: // oxy_RoundFillRectangle
			for (int i = 0; i < w; i++){
				if (i == 0 || i == w - 1){
					gfx_VertLine(x+i, y+1, h - 2);
				}else gfx_VertLine(x+i, y, h);
			}
			break;
			
		case 1: // oxy_RoundFillRectangle_Upper
			for (int i = 0; i < w; i++){
				if (i == 0 || i == w - 1){
					gfx_VertLine(x+i, y+1, h - 1);
				}else gfx_VertLine(x+i, y, h);
			}
			break;
			
		case 2: // oxy_RoundFillRectangle_Bottom
			for (int i = 0; i < w; i++){
				if (i == 0 || i == w - 1){
					gfx_VertLine(x+i, y, h - 1);
				}else gfx_VertLine(x+i, y, h);
			}
			break;
		
		case 3: // oxy_RoundFillRectangle_Left
			for (int i = 0; i < w; i++){
				if (i == 0){
					gfx_VertLine(x+i, y + 1, h - 2);
				}else gfx_VertLine(x+i, y, h);
			}
			break;
			
		case 4: // oxy_RoundFillRectangle_Right
			for (int i = 0; i < w; i++){
				if (i == w - 1){
					gfx_VertLine(x+i, y + 1, h - 2);
				}else gfx_VertLine(x+i, y, h);
			}
			break;
	}
}

// Renders the notification on top of the stack.
void notify_Alert(void)
{
	int index;
	struct notify_t *curr_notify;
	uint8_t xprint;
	uint16_t yprint = 15;
	
	if (!notify_amount) {
		return;
	}else{
		index = notify_amount - 1;
	}

	notify_Load();
	
	curr_notify = &notify[index];

	gfx_SetColor(0);
	
	if (curr_notify->icon != NULL){
		xprint = (320 - 205)/2;
		oxy_FillRoundRectangle(xprint, yprint, 205, 40, 0);
		
		gfx_SetColor(255);
		oxy_FillRoundRectangle(xprint, yprint + 1, 38, 38, 0);
		
		/* place prog name here */
		gfx_SetColor(10);
		oxy_FillRoundRectangle(xprint + 40, yprint + 1, 163, 14, 0);
		
		gfx_SetTextFGColor(255);
		gfx_SetTextBGColor(10);
	
		if (curr_notify->title[0] != '\0'){
			gfx_PrintStringXY(curr_notify->title, 102, 19);
		}
		
		/* place text here */ 
		gfx_SetColor(255);
		oxy_FillRoundRectangle(101, 31, 163, 23, 0);
		
		gfx_SetTextFGColor(0);
		gfx_SetTextBGColor(255);
		
		if (curr_notify->text[0] != '\0'){
			gfx_PrintStringXY(curr_notify->text, 102, yprint + 18);
		}

	}else{

		xprint = (320 - 165)/2;
		oxy_FillRoundRectangle(xprint, yprint, 165, 40, 0);
		
		/* place prog name here */ 
		gfx_SetColor(10);
		oxy_FillRoundRectangle(xprint + 1, yprint + 1, 163, 14, 0);
		
		gfx_SetTextFGColor(255);
		gfx_SetTextBGColor(10);
	
		if (curr_notify->title[0] != '\0'){
			gfx_PrintStringXY(curr_notify->title, xprint + 2, yprint + 3);
		}
		
		/* place text here */ 
		gfx_SetColor(255);
		oxy_FillRoundRectangle(xprint + 1, yprint + 16, 163, 23, 0);
		
		gfx_SetTextFGColor(0);
		gfx_SetTextBGColor(255);
		
		if (curr_notify->text[0] != '\0'){
			gfx_PrintStringXY(curr_notify->text, xprint + 2, yprint + 18);
		}
	}
	
	while (!os_GetCSC());
	
	notify_Delete(index);
}

// Displays the notification tray. 
void notify_Tray(void)
{
	
}