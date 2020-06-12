#include<windows.h>
#include<winuser.h>
#include <chrono>
#include <string>
#include <thread>
#include <ctype.h>
#include <fstream>
#include <iostream>
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

int main() {

	using namespace std;

	string dir = "C:\\Users\\Antho\\OneDrive\\Documents\\";
	string bee = "beemovie.txt";
	string corona = "coronavirusCompleteGeneticSequence.txt";
	string cup = "cup";
	string inFileName =dir;
	string c;
	string e;
	ifstream file;
	string tsh;



	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
before:
	cout << bee << "(1), " << corona << "(2), or " << cup << "(3)?\n";
	cin >> c;
	if (c == "1")inFileName += bee;
	else if (c == "2")inFileName += corona;
	else if (c == "3") {
		e = cup;
	}
	else goto before;//none of the above

	if (inFileName != dir) {
		file.open(inFileName);
		if (file.is_open()) getline(file, e);
		file.close();
	}
	cout << "3 secs till spam\n";

	sleep_for(milliseconds(3000));

	int invl = 10;
	int intervl = 2000;
	int reps = 100;

	for (int q = 0; q < reps; q++) {

		for (int i = 0; i <= e.length() / intervl; i++) {
			string s = e.substr(i * intervl, intervl);
			size_t len = strlen(s.c_str());
			HWND hwnd = GetDesktopWindow();
			toClipboard(hwnd, s);
			ctrlv();

			sleep_for(milliseconds(10));
			pressKey(VK_RETURN);
			sleep_for(milliseconds(400));

		}
		if(stopping(invl)) break;

	}

}