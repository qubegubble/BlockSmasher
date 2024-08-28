#ifndef SCREEN_H
#define SCREEN_H
namespace util {
	class Screensize {

	public:
		Screensize();

	public:
		static void GetDesktopResolution(int& horizontal, int& vertical);
		static void ToggleFullScreen(); //Still needs to be implemented
		static void CloseWindow(); // Same here
		static void MinimizeWindow(); // Same here

	};
}

#endif
