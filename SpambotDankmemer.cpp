//Got banned from dank memer bot for doing this lol
#include <windows.h>
#include <winuser.h>
#include <chrono>
#include <string>
#include <thread>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <complex>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using namespace std;
INPUT ip;
using namespace std;


// 2. forward declaration (also see later)
void toClipboard(HWND hwnd,
	const std::string& s);
// 2. declare functions at file scope 
void toClipboard(HWND hwnd,
	const std::string& s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}


void pressKey(char a) {
	// Press the "A" key
	ip.ki.wVk = a; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "A" key 0x0A
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}

void ctrlv() {
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = 'V';
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	sleep_for(milliseconds(100));

	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = 'V';
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

}
bool stopping(int msTime) {

	for (int i = 0; i < double(msTime) / 50.0; i++) {
		if (GetKeyState('S') < 0)
			return true;

		sleep_for(milliseconds(50));
	}
	return false;
}

void pasteString(string s) {
	HWND hwnd = GetDesktopWindow();
	toClipboard(hwnd, s);
	ctrlv();

	sleep_for(milliseconds(10));
	pressKey(VK_RETURN);
}
void meme() {
	pasteString("pls pm");
	sleep_for(milliseconds((rand() % 300)+300));
	pasteString("n");
}
void beg() {
	pasteString("pls beg");
}
void fish() {
	pasteString("pls fish");
}
void trivia() {
	pasteString("pls trivia");
	sleep_for(milliseconds((rand() % 300)+300));

	pasteString("a");

}
int main() {
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	cout << "3 secs till spam\n";
	sleep_for(milliseconds(3000));
	int reps = 10000000;
	for (int q = 0; q < reps; q++) {
		cout << q << '\n';
		pasteString("pls pm");
		sleep_for(milliseconds(400));
		pasteString("n");
		sleep_for(milliseconds(4000));
		pasteString("pls fish");
		sleep_for(milliseconds(4000));
		pasteString("pls beg");
		sleep_for(milliseconds(4000));
		pasteString("pls trivia");
		sleep_for(milliseconds(400));
		pasteString("a");
		sleep_for(milliseconds(4000));
		if (rand() % 24 == 1) pasteString("pls buy laptop");
		sleep_for(milliseconds(45000 + rand() % 2000));
	}

}
