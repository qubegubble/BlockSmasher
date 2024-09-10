#include "windows.h"
#include "Headers\ScreenSettings.h"

using namespace util;

void Screensize::GetDesktopResolution(int& horizontal, int& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}