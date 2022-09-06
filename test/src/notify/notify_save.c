#include "notify_save.h"
#include "notify.h"

uint8_t NOTIFY_VERSION_COMPARE;

bool notify_Load(void)
{
	uint8_t slot;

	slot = ti_Open(NOTIFY_APPVAR_NAME, "r");

	if(slot){

		// Check the version of the appvar
		if (ti_Read(&NOTIFY_VERSION_COMPARE, sizeof(uint8_t), 1, slot)){

			if (NOTIFY_VERSION_COMPARE != NOTIFY_VERSION_NUM){
				// Error: Version does not match with current file version
				return false;
			}

		}
		
		// Read the stack size
		ti_Read(&notify_amount, sizeof(notify_amount), 1, slot);

		notify = malloc(notify_amount * sizeof(struct notify_t));
		
		// Makes sure that there is space to store stack
		if (notify != NULL){
			ti_Read(notify, notify_amount * sizeof(struct notify_t), 1, slot);
		} else {

			// Error: There wasn't enough space to store stack.
			return false;
		}

		ti_Close(slot);
		
		return true;

	} else {

		// Error: There is no notify appvar.
		return false;

	}

}

void notify_Save(void)
{
	uint8_t slot;

	// Store lastest version to be compared later on.
	NOTIFY_VERSION_COMPARE = NOTIFY_VERSION_NUM;

	// Open slot!
	slot = ti_Open(NOTIFY_APPVAR_NAME, "w");

	// Store compare data into appvar.
	ti_Write(&NOTIFY_VERSION_COMPARE, sizeof(uint8_t), 1, slot);
	
	// Store the current size of the stack
	ti_Write(&notify_amount, sizeof(uint8_t), 1, slot);
	
	// Store the current stack
	ti_Write(notify, notify_amount * sizeof(struct notify_t), 1, slot);
	
	// Free the current stack from memory
	free(notify);
	
	// Set the appvar archive status to true
	ti_SetArchiveStatus(1, slot);

	// Close Slot!
	ti_Close(slot);
}