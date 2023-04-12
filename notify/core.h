/**
 * @file core.h
 * @author Alvajoy 'Alvajoy123' Asante
 * @brief Core Notification system
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023
 *
 *     _/      _/    _/_/    _/_/_/_/_/  _/_/_/  _/_/_/_/  _/      _/
 *    _/_/    _/  _/    _/      _/        _/    _/          _/  _/
 *   _/  _/  _/  _/    _/      _/        _/    _/_/_/        _/
 *  _/    _/_/  _/    _/      _/        _/    _/            _/
 * _/      _/    _/_/        _/      _/_/_/  _/            _/
 *
 * BSD 3-Clause License
 * Copyright (c) 2023, Alvajoy 'Alvajoy123' Asante.
 * All rights reserved.
 *
 * 	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *
 *	Redistributions of source code must retain the above copyright notice, this
 *	list of conditions and the following disclaimer.
 *
 * 	Redistributions in binary form must reproduce the above copyright notice,
 *	this list of conditions and the following disclaimer in the documentation
 *	and/or other materials provided with the distribution.
 *
 * 	Neither the name of the copyright holder nor the names of its
 * 	contributors may be used to endorse or promote products derived from
 * 	this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
	 * @brief Creates a new notification.
	 *
	 * @param icon Icon of the notification
	 * @param title Title of the notification (Name of Program).
	 * @param text Text or dialog of the notifications.
	 * @return struct notify_t* pointer to notify struct
	 */
	struct notify_t *notify_Create(gfx_sprite_t *icon, char title[9], char text[30]);

	/**
	 * @brief Returns the first notification with same title name
	 *
	 * @param title title notification may contain
	 * @return struct notify_t* pointer to notify struct
	 */
	struct notify_t *notify_Search(char title[9]);

	/**
	 * @brief Deletes Notification out of a stack,
	 *
	 * @param notification pointer to notify struct
	 * @return true notification was deleted
	 * @return false notification was not deleted
	 */
	bool notify_Delete(struct notify_t *notification);

	/**
	 * @brief This function deletes all the notification in notification stack.
	 */
	void notify_DeleteAll(void);

	/**
	 * @brief Returns notification at the top of the notification stack.
	 */
	bool notify_Alert(void);

	/**
	 * @brief Default Renders a notification
	 *
	 * @param notification
	 * @param x X position
	 * @param y Y position
	 * @return true Notification was rendered
	 * @return false Notification was not rendered
	 */
	bool notify_Render(struct notify_t *notification, int x, int y);

	/**
	 * @brief Renders all the notification in a tray.
	 */
	void notify_Tray(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NOTIFY_CORE_H__ */