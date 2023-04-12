#ifndef NOTIFY_SAVE_H
#define NOTIFY_SAVE_H

#define NOTIFY_APPVAR_NAME "NOTIFY"

#include <tice.h>
#include <fileioc.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    /**
     * @brief Loads notification data.
     */
    bool notify_Load(void);

    /**
     * @brief Saves notification data.
     */
    void notify_Save(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif