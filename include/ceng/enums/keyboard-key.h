/*****************************************************************************
*
* keyboard-key.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_KEYBOARD_CODES_H
#define _CENG_KEYBOARD_CODES_H

namespace Ceng
{
	namespace KEYBOARD_KEY
	{
		enum value
		{
			A = 0 ,
			B = 1,
			C = 2,
			D = 3,
			E = 4,
			F = 5,
			G = 6,
			H = 7,
			I = 8,
			J = 9,
			K = 10,
			L = 11,
			M = 12,
			N = 13,
			O = 14,
			P = 15,
			Q = 16,
			R = 17,
			S = 18,
			T = 19,
			U = 20,
			V = 21,
			W = 22,
			X = 23,
			Y = 24,
			Z = 25,
		
			KEY_1 = 26,
			KEY_2 = 27,
			KEY_3 = 28,
			KEY_4 = 29,
			KEY_5 = 30,
			KEY_6 = 31,
			KEY_7 = 32,
			KEY_8 = 33,
			KEY_9 = 34,
			KEY_0 = 35,
		
			MINUS = 36, // '-'
		
			COMMA = 37, // ','
			PERIOD = 38, // '.'
			SLASH = 39, // '/'
		
			SEMICOLON = 40, // ;
			GRAVE = 41, // ´
			BACKSLASH = 42, // '\''
		
			LEFT_BRACKET = 43, // '['
		
			EQUALS = 44, // =
			APOSTROPHE = 45, // '
		
			SPACE = 46,
			ENTER = 47,
			BACKSPACE = 48,
		
			TAB = 49,
			CAPS = 50,
			LEFT_SHIFT = 51, // Left shift
			LEFT_CTRL = 52, // Left control
			
			LEFT_OS = 53, // Windows key
			
			LEFT_ALT = 54, // Left alt
			RIGHT_ALT = 55, // Right alt

			RIGHT_OS = 56, // Right side OS-specific key

			RIGHT_CTRL = 57, // Right control
			RIGHT_SHIFT = 58,
		
			LEFT_ARROW = 59,
			RIGHT_ARROW = 60,
			UP_ARROW = 61,
			DOWN_ARROW = 62,
		
			KEY_DELETE = 63,
			
			HOME = 64,
			END = 65,
			PAGE_UP = 66,
			PAGE_DOWN = 67,
		
			NUMPAD_1 = 68,
			NUMPAD_2 = 69,
			NUMPAD_3 = 70,
			NUMPAD_4 = 71,
			NUMPAD_5 = 72,
			NUMPAD_6 = 73,
			NUMPAD_7 = 74,
			NUMPAD_8 = 75,
			NUMPAD_9 = 76,
			NUMPAD_0 = 77,
		
			NUMPAD_PERIOD = 78,
			NUMPAD_ENTER = 79,
			NUMPAD_PLUS = 80,    // '+'
			NUMPAD_MINUS = 81,   // '-'
			NUMPAD_STAR = 82,    // '*'
			NUMPAD_SLASH = 83,	// '/' 
		
			F1 = 84,
			F2 = 85,
			F3 = 86,
			F4 = 87,
			F5 = 88,
			F6 = 89,
			F7 = 90,
			F8 = 91,
			F9 = 92,
			F10 = 93,
			F11 = 94,
			F12 = 95,
		
			ESC = 96,
		
			INSERT = 97,
			PRINT_SCREEN = 98 ,
			
			SCROLL_LOCK = 99,
			NUMLOCK = 100,
		
			RIGHT_BRACKET = 101, // ']'

			FORCE32B = 1 << 30 ,
		};
	};

};

#endif