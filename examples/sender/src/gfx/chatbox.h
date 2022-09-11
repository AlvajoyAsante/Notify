#ifndef chatbox_include_file
#define chatbox_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define chatbox_width 16
#define chatbox_height 16
#define chatbox_size 258
#define chatbox ((gfx_sprite_t*)chatbox_data)
extern unsigned char chatbox_data[258];

#ifdef __cplusplus
}
#endif

#endif
