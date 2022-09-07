/**
 * @file notify.h
 * @author Alvajoy Asante
 * @brief Oxygen Notification system.
 * @version 0.1
 * @date 2022-08-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef OXY_NOTIFY_H
#define OXY_NOTIFY_H

#include <tice.h>
#include <graphx.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Notifications structure file.  
 */ 
struct notify_t{
	// Simple notification information. 
	gfx_sprite_t *icon;	
	char title[9];
	char text[30];

	// Color infromation
	uint8_t outline_index;
	uint8_t fill_index;
	
	// Text color information
	uint8_t fg_index;
	uint8_t bg_index; 
};
extern struct notify_t *notify;

/**
 * @brief Manages amount of notifications in stack.  
 */ 
extern uint8_t notify_amount;

/**
 * Creates a new notification.
 * @param icon Icon of the notification
 * @param title Title of the notification (Name of Program).
 * @param text Text or dialog of the notifications.
 */
int notify_Create(gfx_sprite_t *icon, char title[9], char text[30]);

/**
 * @brief Deletes Notification out of a stack,
 * @param index index in stack.
 */
void notify_Delete(uint8_t index);

/**
 * @brief This function deletes all the notification in notification stack.
 */ 
void notify_DeleteAll(void);

/**
 * @brief Renders notification at the top of the notification stack.
 */ 
void notify_Alert(void);

/**
 * @brief Renders a notification.
 */ 
void notify_Show(uint8_t index);

/**
 * @brief Renders all the notification in a tray.
 */ 
void notify_Tray(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OXY_NOTIFY_H__ */