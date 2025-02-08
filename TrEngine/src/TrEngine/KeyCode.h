#pragma once

//from glfw3.h
#define TE_KEY_SPACE              32
#define TE_KEY_APOSTROPHE         39  /* ' */
#define TE_KEY_COMMA              44  /* , */
#define TE_KEY_MINUS              45  /* - */
#define TE_KEY_PERIOD             46  /* . */
#define TE_KEY_SLASH              47  /* / */
#define TE_KEY_0                  48
#define TE_KEY_1                  49
#define TE_KEY_2                  50
#define TE_KEY_3                  51
#define TE_KEY_4                  52
#define TE_KEY_5                  53
#define TE_KEY_6                  54
#define TE_KEY_7                  55
#define TE_KEY_8                  56
#define TE_KEY_9                  57
#define TE_KEY_SEMICOLON          59  /* ; */
#define TE_KEY_EQUAL              61  /* = */
#define TE_KEY_A                  65
#define TE_KEY_B                  66
#define TE_KEY_C                  67
#define TE_KEY_D                  68
#define TE_KEY_E                  69
#define TE_KEY_F                  70
#define TE_KEY_G                  71
#define TE_KEY_H                  72
#define TE_KEY_I                  73
#define TE_KEY_J                  74
#define TE_KEY_K                  75
#define TE_KEY_L                  76
#define TE_KEY_M                  77
#define TE_KEY_N                  78
#define TE_KEY_O                  79
#define TE_KEY_P                  80
#define TE_KEY_Q                  81
#define TE_KEY_R                  82
#define TE_KEY_S                  83
#define TE_KEY_T                  84
#define TE_KEY_U                  85
#define TE_KEY_V                  86
#define TE_KEY_W                  87
#define TE_KEY_X                  88
#define TE_KEY_Y                  89
#define TE_KEY_Z                  90
#define TE_KEY_LEFT_BRACKET       91  /* [ */
#define TE_KEY_BACKSLASH          92  /* \ */
#define TE_KEY_RIGHT_BRACKET      93  /* ] */
#define TE_KEY_GRAVE_ACCENT       96  /* ` */
#define TE_KEY_WORLD_1            161 /* non-US #1 */
#define TE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define TE_KEY_ESCAPE             256
#define TE_KEY_ENTER              257
#define TE_KEY_TAB                258
#define TE_KEY_BACKSPACE          259
#define TE_KEY_INSERT             260
#define TE_KEY_DELETE             261
#define TE_KEY_RIGHT              262
#define TE_KEY_LEFT               263
#define TE_KEY_DOWN               264
#define TE_KEY_UP                 265
#define TE_KEY_PAGE_UP            266
#define TE_KEY_PAGE_DOWN          267
#define TE_KEY_HOME               268
#define TE_KEY_END                269
#define TE_KEY_CAPS_LOCK          280
#define TE_KEY_SCROLL_LOCK        281
#define TE_KEY_NUM_LOCK           282
#define TE_KEY_PRINT_SCREEN       283
#define TE_KEY_PAUSE              284
#define TE_KEY_F1                 290
#define TE_KEY_F2                 291
#define TE_KEY_F3                 292
#define TE_KEY_F4                 293
#define TE_KEY_F5                 294
#define TE_KEY_F6                 295
#define TE_KEY_F7                 296
#define TE_KEY_F8                 297
#define TE_KEY_F9                 298
#define TE_KEY_F10                299
#define TE_KEY_F11                300
#define TE_KEY_F12                301
#define TE_KEY_F13                302
#define TE_KEY_F14                303
#define TE_KEY_F15                304
#define TE_KEY_F16                305
#define TE_KEY_F17                306
#define TE_KEY_F18                307
#define TE_KEY_F19                308
#define TE_KEY_F20                309
#define TE_KEY_F21                310
#define TE_KEY_F22                311
#define TE_KEY_F23                312
#define TE_KEY_F24                313
#define TE_KEY_F25                314
#define TE_KEY_KP_0               320
#define TE_KEY_KP_1               321
#define TE_KEY_KP_2               322
#define TE_KEY_KP_3               323
#define TE_KEY_KP_4               324
#define TE_KEY_KP_5               325
#define TE_KEY_KP_6               326
#define TE_KEY_KP_7               327
#define TE_KEY_KP_8               328
#define TE_KEY_KP_9               329
#define TE_KEY_KP_DECIMAL         330
#define TE_KEY_KP_DIVIDE          331
#define TE_KEY_KP_MULTIPLY        332
#define TE_KEY_KP_SUBTRACT        333
#define TE_KEY_KP_ADD             334
#define TE_KEY_KP_ENTER           335
#define TE_KEY_KP_EQUAL           336
#define TE_KEY_LEFT_SHIFT         340
#define TE_KEY_LEFT_CONTROL       341
#define TE_KEY_LEFT_ALT           342
#define TE_KEY_LEFT_SUPER         343
#define TE_KEY_RIGHT_SHIFT        344
#define TE_KEY_RIGHT_CONTROL      345
#define TE_KEY_RIGHT_ALT          346
#define TE_KEY_RIGHT_SUPER        347
#define TE_KEY_MENU               348

#define TE_KEY_LAST               TE_KEY_MENU

inline ImGuiKey GLFWKeyToImGuiKey(int keycode)
{
	static const std::unordered_map<int, ImGuiKey> keyMap = {
		{GLFW_KEY_SPACE, ImGuiKey_Space},
		{GLFW_KEY_A, ImGuiKey_A},
		{GLFW_KEY_B, ImGuiKey_B},
		{GLFW_KEY_C, ImGuiKey_C},
		{GLFW_KEY_D, ImGuiKey_D},
		{GLFW_KEY_E, ImGuiKey_E},
		{GLFW_KEY_F, ImGuiKey_F},
		{GLFW_KEY_G, ImGuiKey_G},
		{GLFW_KEY_H, ImGuiKey_H},
		{GLFW_KEY_I, ImGuiKey_I},
		{GLFW_KEY_J, ImGuiKey_J},
		{GLFW_KEY_K, ImGuiKey_K},
		{GLFW_KEY_L, ImGuiKey_L},
		{GLFW_KEY_M, ImGuiKey_M},
		{GLFW_KEY_N, ImGuiKey_N},
		{GLFW_KEY_O, ImGuiKey_O},
		{GLFW_KEY_P, ImGuiKey_P},
		{GLFW_KEY_Q, ImGuiKey_Q},
		{GLFW_KEY_R, ImGuiKey_R},
		{GLFW_KEY_S, ImGuiKey_S},
		{GLFW_KEY_T, ImGuiKey_T},
		{GLFW_KEY_U, ImGuiKey_U},
		{GLFW_KEY_V, ImGuiKey_V},
		{GLFW_KEY_W, ImGuiKey_W},
		{GLFW_KEY_X, ImGuiKey_X},
		{GLFW_KEY_Y, ImGuiKey_Y},
		{GLFW_KEY_Z, ImGuiKey_Z},
		{GLFW_KEY_ESCAPE, ImGuiKey_Escape},
		{GLFW_KEY_ENTER, ImGuiKey_Enter},
		{GLFW_KEY_TAB, ImGuiKey_Tab},
		{GLFW_KEY_BACKSPACE, ImGuiKey_Backspace},
		{GLFW_KEY_INSERT, ImGuiKey_Insert},
		{GLFW_KEY_DELETE, ImGuiKey_Delete},
		{GLFW_KEY_RIGHT, ImGuiKey_RightArrow},
		{GLFW_KEY_LEFT, ImGuiKey_LeftArrow},
		{GLFW_KEY_DOWN, ImGuiKey_DownArrow},
		{GLFW_KEY_UP, ImGuiKey_UpArrow},
		{GLFW_KEY_F1, ImGuiKey_F1},
		{GLFW_KEY_F2, ImGuiKey_F2},
		{GLFW_KEY_F3, ImGuiKey_F3},
		{GLFW_KEY_F4, ImGuiKey_F4},
		{GLFW_KEY_F5, ImGuiKey_F5},
		{GLFW_KEY_F6, ImGuiKey_F6},
		{GLFW_KEY_F7, ImGuiKey_F7},
		{GLFW_KEY_F8, ImGuiKey_F8},
		{GLFW_KEY_F9, ImGuiKey_F9},
		{GLFW_KEY_F10, ImGuiKey_F10},
		{GLFW_KEY_F11, ImGuiKey_F11},
		{GLFW_KEY_F12, ImGuiKey_F12},
		{GLFW_KEY_LEFT_SHIFT, ImGuiKey_LeftShift},
		{GLFW_KEY_LEFT_CONTROL, ImGuiKey_LeftCtrl},
		{GLFW_KEY_LEFT_ALT, ImGuiKey_LeftAlt},
		{GLFW_KEY_LEFT_SUPER, ImGuiKey_LeftSuper},
		{GLFW_KEY_RIGHT_SHIFT, ImGuiKey_RightShift},
		{GLFW_KEY_RIGHT_CONTROL, ImGuiKey_RightCtrl},
		{GLFW_KEY_RIGHT_ALT, ImGuiKey_RightAlt},
		{GLFW_KEY_RIGHT_SUPER, ImGuiKey_RightSuper},
		{GLFW_KEY_MENU, ImGuiKey_Menu},
	};

	auto it = keyMap.find(keycode);
	return (it != keyMap.end()) ? it->second : ImGuiKey_None;
}

