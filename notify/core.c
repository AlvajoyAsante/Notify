#include "core.h"
#include "save.h"

#include <tice.h>
#include <graphx.h>

struct notify_t *notify;

// Creating notifications.
struct notify_t *notify_Create(gfx_sprite_t *icon, char title[9], char text[30])
{
	struct notify_t *curr_index;

	notify_Load();

	// Check if the amount of notifications are less than the limit
	if (!(NOTIFY_STACK_AMOUNT < NOTIFY_STACK_MAX))
		return NULL;

	notify = realloc(notify, ++NOTIFY_STACK_AMOUNT * sizeof(struct notify_t));
	curr_index = &notify[NOTIFY_STACK_AMOUNT - 1];

	strncpy(curr_index->title, title, 9);
	strncpy(curr_index->text, text, 30);

	if (icon != NULL)
	{
		curr_index->icon = icon;
	}
	else
	{
		curr_index->icon = NULL;
	}

	notify_Save();

	return curr_index;
}

struct notify_t *notify_Search(char title[9])
{
	struct notify_t *curr_index;

	for (int i = 0; i < NOTIFY_STACK_AMOUNT; i++)
	{
		curr_index = &notify[i];

		if (strcmp(curr_index->title, title))
		{
			return curr_index;
		}
	}

	return NULL;
}

// Deleting notifications.
bool notify_Delete(struct notify_t *notification)
{
	if (notification == NULL)
		return false;

	// Need to load the notification amount
	notify_Load();

	// Check if there is more than one notifications
	if (notify_amount > 0)
	{
		// Delete the notification

		notification = &notify[NOTIFY_STACK_AMOUNT - 1];
		notify = realloc(notify, --NOTIFY_STACK_AMOUNT * sizeof(struct notify_t));
	}

	// Save the notification stack
	notify_Save();

	return true;
}

void notify_DeleteAll(void)
{
	// Set the notification amount in stack to zero
	notify_amount = 0;

	// Set the size of the stack to the original size.
	notify = realloc(notify, sizeof(struct notify_t));

	// Saves
	notify_Save();
}

static struct notify_t *notify_CheckNotify(void)
{
	struct notify_t *curr_index;

	notify_Load();

	curr_index = &notify[notify_amount - 1];

	notify_Save();

	return curr_index;
}

// copied from oxygen
static void oxy_FillRoundRectangle(uint16_t x, uint8_t y, int w, uint8_t h, uint8_t type)
{
	switch (type)
	{
	case 0: // oxy_RoundFillRectangle
		for (int i = 0; i < w; i++)
		{
			if (i == 0 || i == w - 1)
			{
				gfx_VertLine(x + i, y + 1, h - 2);
			}
			else
				gfx_VertLine(x + i, y, h);
		}
		break;

	case 1: // oxy_RoundFillRectangle_Upper
		for (int i = 0; i < w; i++)
		{
			if (i == 0 || i == w - 1)
			{
				gfx_VertLine(x + i, y + 1, h - 1);
			}
			else
				gfx_VertLine(x + i, y, h);
		}
		break;

	case 2: // oxy_RoundFillRectangle_Bottom
		for (int i = 0; i < w; i++)
		{
			if (i == 0 || i == w - 1)
			{
				gfx_VertLine(x + i, y, h - 1);
			}
			else
				gfx_VertLine(x + i, y, h);
		}
		break;

	case 3: // oxy_RoundFillRectangle_Left
		for (int i = 0; i < w; i++)
		{
			if (i == 0)
			{
				gfx_VertLine(x + i, y + 1, h - 2);
			}
			else
				gfx_VertLine(x + i, y, h);
		}
		break;

	case 4: // oxy_RoundFillRectangle_Right
		for (int i = 0; i < w; i++)
		{
			if (i == w - 1)
			{
				gfx_VertLine(x + i, y + 1, h - 2);
			}
			else
				gfx_VertLine(x + i, y, h);
		}
		break;
	}
}

// Renders the notification on top of the stack.
bool notify_Alert(void)
{
	struct notify_t *curr_index = notify_CheckNotify();

	if (curr_index == NULL)
		return false;

	uint8_t xprint = (320 - 205) / 2;
	uint16_t yprint = 15;

	// Load stack so we can pull the stack information such as the size
	notify_Load();

	// print in the center of the screen
	if (!notify_Render(curr_index, xprint, yprint)){
		return false;
	}

	// once it's been displayed delete it from the stack
	notify_Delete(curr_index);

	// Saves all the notifications
	notify_Save();

	// return which item on the stack has been display and deleted
	return true;
}

bool notify_Render(struct notify_t *notification, int x, int y)
{
	uint8_t fill = 255;
	uint8_t fg = 0;
	uint8_t bg = 255;

	if (notification == NULL)
		return false;


	// Is there a icon to display
	switch ((bool)(notification->icon != NULL))
	{
	case true:
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

		if (notification->title[0] != '\0')
		{
			gfx_PrintStringXY(notification->title, x + 3, y + 4);
		}

		/* place text here */
		gfx_SetColor(fill);
		oxy_FillRoundRectangle(x + 40, y + 16, 163, 23, 0);

		gfx_SetTextFGColor(fg);
		gfx_SetTextBGColor(bg);

		if (notification->text[0] != '\0')
		{
			gfx_PrintStringXY(notification->text, x + 44, y + 18);
		}
		break;

	case false:
		//  Print notification without a icon to display.
		oxy_FillRoundRectangle(x, y, 165, 40, 0);

		/* place title here */
		gfx_SetColor(fill);
		oxy_FillRoundRectangle(x + 1, y + 1, 163, 14, 0);

		gfx_SetTextFGColor(fg);
		gfx_SetTextBGColor(bg);

		if (notification->title[0] != '\0')
		{
			gfx_PrintStringXY(notification->title, x + 2, y + 3);
		}

		/* place text here */
		gfx_SetColor(fill);
		oxy_FillRoundRectangle(x + 1, y + 16, 163, 23, 0);

		gfx_SetTextFGColor(fg);
		gfx_SetTextBGColor(bg);

		if (notification->text[0] != '\0')
		{
			gfx_PrintStringXY(notification->text, x + 2, y + 18);
		}
		break;
	}
}

// Displays the notification tray.
void notify_Tray(void)
{
	// in the process of creating.
}