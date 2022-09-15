#include "notify_core.h"
#include "notify_save.h"

#include <tice.h>
#include <graphx.h>

struct notify_t *notify;
uint8_t notify_amount;

// Creating notifications.
int notify_Create(gfx_sprite_t *icon, char title[9], char text[30])
{
	struct notify_t *curr_index;
	
	notify_Load();
	
	// Check if the amount of notificatins are less than the limit
	if (notify_amount < NOTIFY_STACK_LIMIT) { 
		
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

	} else {

		return -1;
	}
	
	notify_Save();
}

// Deleting notifications.
void notify_Delete(uint8_t index)
{
	// Need to load the notification amount
	notify_Load();
	
	// Check if there is more than one notifications
	if (notify_amount > 0){
		// Delete the notification
		notify_amount--;
        notify[index] = notify[notify_amount];
        notify = realloc(notify, notify_amount * sizeof(struct notify_t));
    }
	
	// Save the notification stack
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
int notify_Alert(void)
{
	uint8_t index;
	uint8_t xprint = (320 - 205)/2;
	uint16_t yprint = 15;

	// Load stack so we can pull the stack information such as the size
	notify_Load();

	// The index equals to the (notification amount - 1) which equal to the top of the stack
	if (notify_amount) {
		index = notify_amount - 1;
	}else{
		free(notify);
		return - 1;
	}

	// print in the center of the screen
	notify_Render(xprint, yprint, index);

	// once it's been displayed delete
	notify_Delete(index);

	// return which item on the stack has been display and deleted
	return index;
}

void notify_Render(int x, int y, int index)
{
	struct notify_t *curr_notify;
	uint8_t fill = 255;
	uint8_t fg = 0;
	uint8_t bg = 255;

	if (index < 0) return;
	
	notify_Load();
	
	curr_notify = &notify[index];
		
	// Is there a icon to display
	if (curr_notify->icon != NULL){
		/* Print area */ 
		oxy_FillRoundRectangle(x, y, 205, 40, 0);
		
		/* Print Icon box */
		gfx_SetColor(fill);
		oxy_FillRoundRectangle(x + 2, y + 1, 38, 38, 0);
		
		/* place title name here */
		gfx_SetColor(fill);
		oxy_FillRoundRectangle(x + 40, y + 1, 163, 14, 0);
		
		gfx_SetTextFGColor(fg);
		gfx_SetTextBGColor(bg);
	
		if (curr_notify->title[0] != '\0'){
			gfx_PrintStringXY(curr_notify->title, x + 3, y + 4);
		}
		
		/* place text here */ 
		gfx_SetColor(fill);
		oxy_FillRoundRectangle(x + 40, y + 16, 163, 23, 0);
		
		gfx_SetTextFGColor(fg);
		gfx_SetTextBGColor(bg);
		
		if (curr_notify->text[0] != '\0'){
			gfx_PrintStringXY(curr_notify->text, x + 44, y + 18);
		}

	}else{ //  Print notification without a icon to display.

		oxy_FillRoundRectangle(x, y, 165, 40, 0);
		
		/* place title here */ 
		gfx_SetColor(fill);
		oxy_FillRoundRectangle(x + 1, y + 1, 163, 14, 0);
		
		gfx_SetTextFGColor(fg);
		gfx_SetTextBGColor(bg);
	
		if (curr_notify->title[0] != '\0'){
			gfx_PrintStringXY(curr_notify->title, x + 2, y + 3);
		}
		
		/* place text here */ 
		gfx_SetColor(fill);
		oxy_FillRoundRectangle(x + 1, y + 16, 163, 23, 0);
		
		gfx_SetTextFGColor(fg);
		gfx_SetTextBGColor(bg);
		
		if (curr_notify->text[0] != '\0'){
			gfx_PrintStringXY(curr_notify->text, x + 2, x + 18);
		}
	}

	// Free the current stack from memory without saving
	free(notify);
}

// Displays the notification tray. 
void notify_Tray(void)
{
	// in the process of creating.
}