/**
 * @file notify_core.h
 * @author Alvajoy Asante
 * @brief Oxygen Notification system.
 * @version 0.1
 * @date 2022-08-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef NOTIFY_CORE_H
#define NOTIFY_CORE_H

#include <tice.h>
#include <graphx.h>

#define NOTIFY_STACK_LIMIT 255

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
};
extern struct notify_t *notify;

/* Notification Stack amount */
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
int notify_Alert(void);

/**
 * @brief Renders a notification.
 */ 
void notify_Render(int x, int y, int index);

/**
 * @brief Renders all the notification in a tray.
 */ 
void notify_Tray(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NOTIFY_CORE_H__ */