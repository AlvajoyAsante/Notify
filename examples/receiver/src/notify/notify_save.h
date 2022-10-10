/**
 * @file notify_save.h
 * @author Alvajoy Asante
 * @brief Notifaction appvar saving.
 * @version 0.1
 * @date 2022-08-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef NOTIFY_SAVE_H
#define NOTIFY_SAVE_H

#define NOTIFY_APPVAR_NAME	"NOTIFY"

#include <tice.h>
#include <fileioc.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Loads all the files from notify appvar
 */ 
bool notify_Load(void);

/**
 * @brief Saves notify sturct.
 */ 
void notify_Save(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NOTIFY_SAVE_H__ */ 