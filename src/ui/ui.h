#define WINDOW_WIDTH 370
#define WINDOW_HEIGHT 770

#define DARK_MODE 1

#if DARK_MODE

#define BG_COLOR 0x121212
#define BG_COLOR_BUTTONS 0xFFFFFF
#define BG_COLOR_STATUS_BAR 0xACB1B0
#define BG_COLOR_MENU_SELECTED 0xd3d3d3
#define BG_COLOR_INPUT_AREA 0xFFFFFF
#define TEXT_COLOR 0x000000
#define BG_COLOR_LINE TEXT_COLOR
#define TEXT_COLOR_STATUS_BAR 0xFFFFFF
#define TEXT_COLOR_DESCRIPTION_LABEL 0x777777

#else

#define BG_COLOR 0xb1adac
#define BG_COLOR_BUTTONS 0xfffffff
#define BG_COLOR_STATUS_BAR 0xacb1b0
#define BG_COLOR_MENU_SELECTED 0x977c75
#define BG_COLOR_INPUT_AREA     0xffffff
#define TEXT_COLOR 0x000000
#define BG_COLOR_LINE           TEXT_COLOR
#define TEXT_COLOR_STATUS_BAR   0xffffff

#endif

#define FONT &JuliaMono_Regular_14
#define FONT_INPUT_AREA &JuliaMono_Regular_16

#define FONT_MATH &noto_sans_math_regular_comb_14
#define FONT_MATH_INPUT_AREA &noto_sans_math_regular_comb_16