#pragma once
#ifndef RLUTIL_H
#define RLUTIL_H

#ifdef __SWITCH__
#ifdef __cplusplus
#include <iostream>
#endif
#include <switch.h>
#define sleep msleep
#define usleep msleep
#define getch sgetch
#endif

#ifdef UNICODE
#define _UNICODE
#endif // UNICODE

#ifdef _UNICODE
#define UNICODE
#endif // _UNICODE

#if 0
#define RLUTIL_USE_ANSI
#endif

#if 0
#define RLUTIL_STRING_T char*
#endif

#ifndef RLUTIL_INLINE
#ifdef _MSC_VER
#define RLUTIL_INLINE __inline
#else // _MSC_VER
#define RLUTIL_INLINE static __inline__
#endif // _MSC_VER
#endif // RLUTIL_INLINE												

#ifdef __cplusplus
#include <iostream>
#include <string>
#include <cstdio>
namespace rlutil {
	RLUTIL_INLINE void locate(int x, int y);
}
#else // __cplusplus
#include <stdio.h>
#include <string.h>
RLUTIL_INLINE void locate(int x, int y);
#endif // __cplusplus

#ifdef _WIN32
#include <windows.h>
#include <winsock.h>
#define _NO_OLDNAMES
#include <conio.h>
#define getch _getch
#define kbhit _kbhit
#else // _WIN32
#ifndef __SWITCH__
#include <sys/termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#endif // __SWITCH__

#ifndef __SWITCH__

RLUTIL_INLINE int getch(void) {

	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

RLUTIL_INLINE int kbhit(void) {
	static struct termios oldt, newt;
	int cnt = 0;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	newt.c_iflag = 0;
	newt.c_oflag = 0;
	newt.c_cc[VMIN] = 1;
	newt.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ioctl(0, FIONREAD, &cnt);
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 100;
	select(STDIN_FILENO + 1, NULL, NULL, NULL, &tv);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return cnt;
}
#endif // __SWITCH__
#endif // _WIN32

#ifndef IOC_OUT													
#define IOC_OUT 0x40000000										
#endif															

#ifndef IOCPARM_MASK											
#define IOCPARM_MASK 0x7f										
#endif															

#ifndef _IOR(x,y,t)																													
#define _IOR(x,y,t)	(IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#endif																				

#ifndef FIONREAD												
#define FIONREAD _IOR('f', 127, u_long)							
#endif			

#ifndef gotoxy

RLUTIL_INLINE void gotoxy(int x, int y) {
#ifdef __cplusplus
	rlutil::
#endif
		locate(x, y);
}
#endif

#ifdef __cplusplus

namespace rlutil {
#endif



#ifdef __cplusplus
#ifndef RLUTIL_STRING_T
	typedef std::string RLUTIL_STRING_T;
#endif

#define RLUTIL_PRINT(st) do { std::cout << st; } while(false)
#else
#ifndef RLUTIL_STRING_T
	typedef const char* RLUTIL_STRING_T;
#endif

#define RLUTIL_PRINT(st) printf("%s", st)
#endif


	enum {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		GREY,
		DARKGREY,
		LIGHTBLUE,
		LIGHTGREEN,
		LIGHTCYAN,
		LIGHTRED,
		LIGHTMAGENTA,
		YELLOW,
		WHITE
	};


	static const RLUTIL_STRING_T ANSI_CLS = "\033[2J\033[3J";
	static const RLUTIL_STRING_T ANSI_CONSOLE_TITLE_PRE = "\033]0;";
	static const RLUTIL_STRING_T ANSI_CONSOLE_TITLE_POST = "\007";
	static const RLUTIL_STRING_T ANSI_ATTRIBUTE_RESET = "\033[0m";
	static const RLUTIL_STRING_T ANSI_CURSOR_HIDE = "\033[?25l";
	static const RLUTIL_STRING_T ANSI_CURSOR_SHOW = "\033[?25h";
	static const RLUTIL_STRING_T ANSI_CURSOR_HOME = "\033[H";
	static const RLUTIL_STRING_T ANSI_BLACK = "\033[22;30m";
	static const RLUTIL_STRING_T ANSI_RED = "\033[22;31m";
	static const RLUTIL_STRING_T ANSI_GREEN = "\033[22;32m";
	static const RLUTIL_STRING_T ANSI_BROWN = "\033[22;33m";
	static const RLUTIL_STRING_T ANSI_BLUE = "\033[22;34m";
	static const RLUTIL_STRING_T ANSI_MAGENTA = "\033[22;35m";
	static const RLUTIL_STRING_T ANSI_CYAN = "\033[22;36m";
	static const RLUTIL_STRING_T ANSI_GREY = "\033[22;37m";
	static const RLUTIL_STRING_T ANSI_DARKGREY = "\033[01;30m";
	static const RLUTIL_STRING_T ANSI_LIGHTRED = "\033[01;31m";
	static const RLUTIL_STRING_T ANSI_LIGHTGREEN = "\033[01;32m";
	static const RLUTIL_STRING_T ANSI_YELLOW = "\033[01;33m";
	static const RLUTIL_STRING_T ANSI_LIGHTBLUE = "\033[01;34m";
	static const RLUTIL_STRING_T ANSI_LIGHTMAGENTA = "\033[01;35m";
	static const RLUTIL_STRING_T ANSI_LIGHTCYAN = "\033[01;36m";
	static const RLUTIL_STRING_T ANSI_WHITE = "\033[01;37m";
	static const RLUTIL_STRING_T ANSI_BACKGROUND_BLACK = "\033[40m";
	static const RLUTIL_STRING_T ANSI_BACKGROUND_RED = "\033[41m";
	static const RLUTIL_STRING_T ANSI_BACKGROUND_GREEN = "\033[42m";
	static const RLUTIL_STRING_T ANSI_BACKGROUND_YELLOW = "\033[43m";
	static const RLUTIL_STRING_T ANSI_BACKGROUND_BLUE = "\033[44m";
	static const RLUTIL_STRING_T ANSI_BACKGROUND_MAGENTA = "\033[45m";
	static const RLUTIL_STRING_T ANSI_BACKGROUND_CYAN = "\033[46m";
	static const RLUTIL_STRING_T ANSI_BACKGROUND_WHITE = "\033[47m";
	// Remaining colors not supported as background colors


	enum {
		KEY_ESCAPE = 0,
		KEY_ENTER = 1,
		KEY_SPACE = 32,

		KEY_INSERT = 2,
		KEY_HOME = 3,
		KEY_PGUP = 4,
		KEY_DELETE = 5,
		KEY_END = 6,
		KEY_PGDOWN = 7,

		KEY_UP = 14,
		KEY_DOWN = 15,
		KEY_LEFT = 16,
		KEY_RIGHT = 17,

		KEY_F1 = 18,
		KEY_F2 = 19,
		KEY_F3 = 20,
		KEY_F4 = 21,
		KEY_F5 = 22,
		KEY_F6 = 23,
		KEY_F7 = 24,
		KEY_F8 = 25,
		KEY_F9 = 26,
		KEY_F10 = 27,
		KEY_F11 = 28,
		KEY_F12 = 29,

		KEY_NUMDEL = 30,
		KEY_NUMPAD0 = 31,
		KEY_NUMPAD1 = 127,
		KEY_NUMPAD2 = 128,
		KEY_NUMPAD3 = 129,
		KEY_NUMPAD4 = 130,
		KEY_NUMPAD5 = 131,
		KEY_NUMPAD6 = 132,
		KEY_NUMPAD7 = 133,
		KEY_NUMPAD8 = 134,
		KEY_NUMPAD9 = 135
	};

	RLUTIL_INLINE int getkey(void) {
#ifndef __SWITCH__
#ifndef _WIN32
		int cnt = kbhit();
#endif
		int k = getch();
		switch (k) {
		case 0: {
			int kk;
			switch (kk = getch()) {
			case 71: return KEY_NUMPAD7;
			case 72: return KEY_NUMPAD8;
			case 73: return KEY_NUMPAD9;
			case 75: return KEY_NUMPAD4;
			case 77: return KEY_NUMPAD6;
			case 79: return KEY_NUMPAD1;
			case 80: return KEY_NUMPAD2;
			case 81: return KEY_NUMPAD3;
			case 82: return KEY_NUMPAD0;
			case 83: return KEY_NUMDEL;
			default: return kk - 59 + KEY_F1;
			}}
		case 224: {
			int kk;
			switch (kk = getch()) {
			case 71: return KEY_HOME;
			case 72: return KEY_UP;
			case 73: return KEY_PGUP;
			case 75: return KEY_LEFT;
			case 77: return KEY_RIGHT;
			case 79: return KEY_END;
			case 80: return KEY_DOWN;
			case 81: return KEY_PGDOWN;
			case 82: return KEY_INSERT;
			case 83: return KEY_DELETE;
			default: return kk - 123 + KEY_F1;
			}}
		case 13: return KEY_ENTER;
#ifdef _WIN32
		case 27: return KEY_ESCAPE;
#else
		case 155:
		case 27: {

			if (cnt >= 3 && getch() == '[') {
				switch (k = getch()) {
				case 'A': return KEY_UP;
				case 'B': return KEY_DOWN;
				case 'C': return KEY_RIGHT;
				case 'D': return KEY_LEFT;
				}
			}
			else return KEY_ESCAPE;
		}
#endif
		default: return k;
		}
#else
		u64 kDown;
		do
		{
			hidScanInput();
			kDown = hidKeysDown(CONTROLLER_P1_AUTO);
			if (kDown & KEY_DUP)
				return KEY_UP;
			else
				if (kDown & KEY_DLEFT)
					return KEY_LEFT;
				else
					if (kDown & KEY_DRIGHT)
						return KEY_RIGHT;
					else
						if (kDown & KEY_DDOWN)
							return KEY_DOWN;
						else
							if (kDown & KEY_A)
								return KEY_ENTER;
							else
								if (kDown & KEY_B)
									return KEY_ESCAPE;
		} while (1);
#endif	
	}

#ifndef __SWITCH__
	RLUTIL_INLINE int nb_getch(void) {
		if (kbhit()) return getch();
		else return 0;
	}
#endif

	RLUTIL_INLINE RLUTIL_STRING_T getANSIColor(const int c) {
		switch (c) {
		case BLACK: return ANSI_BLACK;
		case BLUE: return ANSI_BLUE;
		case GREEN: return ANSI_GREEN;
		case CYAN: return ANSI_CYAN;
		case RED: return ANSI_RED;
		case MAGENTA: return ANSI_MAGENTA;
		case BROWN: return ANSI_BROWN;
		case GREY: return ANSI_GREY;
		case DARKGREY: return ANSI_DARKGREY;
		case LIGHTBLUE: return ANSI_LIGHTBLUE;
		case LIGHTGREEN: return ANSI_LIGHTGREEN;
		case LIGHTCYAN: return ANSI_LIGHTCYAN;
		case LIGHTRED: return ANSI_LIGHTRED;
		case LIGHTMAGENTA: return ANSI_LIGHTMAGENTA;
		case YELLOW: return ANSI_YELLOW;
		case WHITE: return ANSI_WHITE;
		default: return "";
		}
	}


	RLUTIL_INLINE RLUTIL_STRING_T getANSIBackgroundColor(const int c) {
		switch (c) {
		case BLACK: return ANSI_BACKGROUND_BLACK;
		case BLUE: return ANSI_BACKGROUND_BLUE;
		case GREEN: return ANSI_BACKGROUND_GREEN;
		case CYAN: return ANSI_BACKGROUND_CYAN;
		case RED: return ANSI_BACKGROUND_RED;
		case MAGENTA: return ANSI_BACKGROUND_MAGENTA;
		case BROWN: return ANSI_BACKGROUND_YELLOW;
		case GREY: return ANSI_BACKGROUND_WHITE;
		default: return "";
		}
	}


	RLUTIL_INLINE void setColor(int c) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(hConsole, &csbi);

		SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | (WORD)c);
#else
		RLUTIL_PRINT(getANSIColor(c));
#endif
	}


	RLUTIL_INLINE void setBackgroundColor(int c) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(hConsole, &csbi);

		SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFF0F) | (((WORD)c) << 4));
#else
		RLUTIL_PRINT(getANSIBackgroundColor(c));
#endif
	}


	RLUTIL_INLINE int saveDefaultColor(void) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
		static char initialized = 0; // bool
		static WORD attributes;

		if (!initialized) {
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			attributes = csbi.wAttributes;
			initialized = 1;
		}
		return (int)attributes;
#else
		return -1;
#endif
	}


	RLUTIL_INLINE void resetColor(void) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)saveDefaultColor());
#else
		RLUTIL_PRINT(ANSI_ATTRIBUTE_RESET);
#endif
	}


	RLUTIL_INLINE void cls(void) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)

		const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		const COORD coordScreen = { 0, 0 };
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(hConsole, &csbi);
		const DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);

		GetConsoleScreenBufferInfo(hConsole, &csbi);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

		SetConsoleCursorPosition(hConsole, coordScreen);
#else
#ifndef __SWITCH__
		RLUTIL_PRINT(ANSI_CLS);
		RLUTIL_PRINT(ANSI_CURSOR_HOME);
#else
		consoleClear();
		consoleUpdate(NULL);
#endif
#endif
	}


	RLUTIL_INLINE void locate(int x, int y) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
		COORD coord;
		coord.X = (SHORT)(x - 1);
		coord.Y = (SHORT)(y - 1); // Windows uses 0-based coordinates
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
#ifdef __cplusplus
		RLUTIL_PRINT("\033[" << y << ";" << x << "H");
#else
		char buf[32];
		sprintf(buf, "\033[%d;%df", y, x);
		RLUTIL_PRINT(buf);
#endif
#endif
	}


#ifdef __cplusplus
	RLUTIL_INLINE void setString(const RLUTIL_STRING_T & str_) {
#ifdef _UNICODE
		std::wstring stemp = std::wstring(str_.begin(), str_.end());
		LPCWSTR str = stemp.c_str();
		unsigned int len = static_cast<unsigned int>(str_.size());
#else	// _UNICODE
		const char * const str = str_.data();
		unsigned int len = static_cast<unsigned int>(str_.size());
#endif // _UNICODE

#else // __cplusplus
	RLUTIL_INLINE void setString(RLUTIL_STRING_T str) {
		unsigned int len = strlen(str);
#endif // __cplusplus

#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD numberOfCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);

#ifdef UNICODE

		WriteConsoleOutputCharacterA(hConsoleOutput, str, len, csbi.dwCursorPosition, &numberOfCharsWritten);

#else // UNICODE

		WriteConsoleOutputCharacter(hConsoleOutput, str, len, csbi.dwCursorPosition, &numberOfCharsWritten);

#endif // UNICODE

#else // _WIN32 || USE_ANSI
		RLUTIL_PRINT(str);
#ifdef __cplusplus
		RLUTIL_PRINT("\033[" << len << 'D');
#else // __cplusplus
		char buf[3 + 20 + 1];
		sprintf(buf, "\033[%uD", len);
		RLUTIL_PRINT(buf);
#endif // __cplusplus
#endif // __WIN32 || USE_ANSI
	}


	RLUTIL_INLINE void setChar(char ch) {
		const char buf[] = { ch, 0 };
		setString(buf);
	}


	RLUTIL_INLINE void setCursorVisibility(char visible) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO structCursorInfo;
		GetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
		structCursorInfo.bVisible = (visible ? TRUE : FALSE);
		SetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
#else // WIN32 && NOT ANSI
		RLUTIL_PRINT((visible ? ANSI_CURSOR_SHOW : ANSI_CURSOR_HIDE));
#endif// WIN32 && NOT ANSI
	}


	RLUTIL_INLINE void hidecursor(void) {
		setCursorVisibility(0);
	}


	RLUTIL_INLINE void showcursor(void) {
		setCursorVisibility(1);
	}


	RLUTIL_INLINE void msleep(unsigned int ms) {
#ifdef _WIN32
		Sleep(ms);
#else

		if (ms > 1000) sleep(ms / 1000000);
		usleep((ms % 1000000) * 1000);
#endif
	}


	RLUTIL_INLINE int trows(void) {
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return -1;
		else
			return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

#else
#ifdef TIOCGSIZE
		struct ttysize ts;
		ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
		return ts.ts_lines;
#elif defined(TIOCGWINSZ)
		struct winsize ts;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
		return ts.ws_row;
#else
		return -1;
#endif
#endif
	}


	RLUTIL_INLINE int tcols(void) {
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return -1;
		else
			return csbi.srWindow.Right - csbi.srWindow.Left + 1;

#else
#ifdef TIOCGSIZE
		struct ttysize ts;
		ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
		return ts.ts_cols;
#elif defined(TIOCGWINSZ)
		struct winsize ts;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
		return ts.ws_col;
#else
		return -1;
#endif
#endif
	}


#ifdef __cplusplus
#ifndef __SWITCH__
	RLUTIL_INLINE void anykey() {
		getch();
	}
#endif

	template <class T> void anykey(const T& msg) {
		RLUTIL_PRINT(msg);
#else
	RLUTIL_INLINE void anykey(RLUTIL_STRING_T msg) {
		if (msg)
			RLUTIL_PRINT(msg);
#endif
#ifndef __SWITCH__
		getch();
#endif
	}

	RLUTIL_INLINE void setConsoleTitle(RLUTIL_STRING_T title) {
		const char * true_title =
#ifdef __cplusplus
			title.c_str();
#else
			title;
#endif
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
		SetConsoleTitleA(true_title);
#else
		RLUTIL_PRINT(ANSI_CONSOLE_TITLE_PRE);
		RLUTIL_PRINT(true_title);
		RLUTIL_PRINT(ANSI_CONSOLE_TITLE_POST);
#endif
	}



#ifdef __cplusplus

	struct CursorHider {
		CursorHider() { hidecursor(); }
		~CursorHider() { showcursor(); }
	};

}
#endif

#ifdef __SWITCH__
RLUTIL_INLINE const char sgetch()
{
	consoleUpdate(NULL);
	u64 kDown = 0;
	do
	{
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_DUP)
			return 'W';
		else
			if (kDown & KEY_DLEFT)
				return 'A';
			else
				if (kDown & KEY_DRIGHT)
					return 'D';
				else
					if (kDown & KEY_DDOWN)
						return 'S';
					else
						kDown = 0;
	} while (kDown == 0);
}

RLUTIL_INLINE void switch_pause() {

	u64 kDown = 0;
	std::cout << "Press A to continue" << std::endl;
	do
	{
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_A) return;
	} while (1);
}

RLUTIL_INLINE const int getnum()
{
	consoleUpdate(NULL);
	u64 kDown = 0;
	do {
		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) return 0;
		else
			if (kDown & KEY_L) return 1;
			else
				if (kDown & KEY_R) return 2;
				else
					if (kDown & KEY_ZL) return 3;
					else
						if (kDown & KEY_ZR) return 4;
						else
							if (kDown & KEY_DUP) return 5;
							else
								if (kDown & KEY_DLEFT) return 6;
								else
									if (kDown & KEY_DDOWN) return 7;
									else
										if (kDown & KEY_DRIGHT) return 8;
										else
											if (kDown & KEY_X) return 9;
											else
												if (kDown & KEY_Y) return 10;

	} while (1);
}
#endif // __SWITCH__

#endif // RLUTIL_H
