#include "save.h"
#include "core.h"

#include <debug.h>

/**
 * @brief Initialise the library
 * 
 */
static void _initialise(void)
{
	notify_amount = 0;
	notify = malloc(sizeof(struct notify_t));
}

bool notify_Load(void)
{
	uint8_t slot;

	slot = ti_Open(NOTIFY_APPVAR_NAME, "r");

	if (slot)
	{
		// Read the stack size
		ti_Read(&notify_amount, sizeof(notify_amount), 1, slot);

		// This might a issue down the line
		notify = malloc(notify_amount * sizeof(struct notify_t));
		ti_Read(notify, notify_amount * sizeof(struct notify_t), 1, slot);

		ti_Close(slot);
		return true;
	}
	else
	{
		// Error: There is no notify appvar. (Should we initialise)
		_initialise();
		return false;
	}
}

void notify_Save(void)
{
	uint8_t slot;

	// Open slot!
	slot = ti_Open(NOTIFY_APPVAR_NAME, "w");

	// Store the current size of the stack
	ti_Write(&notify_amount, sizeof(uint8_t), 1, slot);

	// Store the current stack
	ti_Write(notify, notify_amount * sizeof(struct notify_t), 1, slot);

	// Set the appvar archive status to true
	ti_SetArchiveStatus(1, slot);

	// Close Slot!
	ti_Close(slot);
}