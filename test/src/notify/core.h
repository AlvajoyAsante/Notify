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



#define NOTIFY_STACK_MAX 255
#define NOTIFY_STACK_AMOUNT notify_amount

#include <tice.h>
#include <graphx.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	/**
	 * @brief Notifications stack structure
	 */
	struct notify_t
	{
		// Simple notification information.
		gfx_sprite_t *icon;
		char title[9];
		char text[30];
	};
	extern struct notify_t *notify;

	/**
	 * @brief This holds the amount of notifications in the stack
	 */
	static uint8_t notify_amount;

	/**
	 * Creates a new notification.
	 * @param icon Icon of the notification
	 * @param title Title of the notification (Name of Program).
	 * @param text Text or dialog of the notifications.
	 */
	struct notify_t *notify_Create(gfx_sprite_t *icon, char title[9], char text[30]);

	/**
	 * @brief Deletes Notification out of a stack,
	 * @param index index in stack.
	 */
	bool notify_Delete(struct notify_t * notification);

	/**
	 * @brief This function deletes all the notification in notification stack.
	 */
	bool notify_DeleteAll(void);

	/**
	 * @brief Returns notification at the top of the notification stack.
	 */
	bool notify_Alert(void);

	/**
	 * @brief Renders a notification based on stack index
	 * 
	 * @param  x: X position
	 * @param  y: Y position
	 */
	bool notify_Render(struct notify_t * notification, int x, int y);

	/**
	 * @brief Renders all the notification in a tray.
	 */
	void notify_Tray(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NOTIFY_CORE_H__ */