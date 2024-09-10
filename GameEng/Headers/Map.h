#ifndef MAP_H
#define MAP_H
#include <vector>
#include <stdio.h>
#include <string>
#include "tinyxml2.h"
#include "SDL.h"

namespace Map {
	class MapHandler{
	private:
		std::string mapPath;
		SDL_Renderer* renderer;
		std::vector<SDL_Texture*> tilesets;

		void ParseTileSet(tinyxml2::XMLElement* mapElement);
		void ParseLayers(tinyxml2::XMLElement* mapElement);
		void ParseCSVLayerData(const char* data);
		SDL_Texture* LoadTexture(std::string path);

	public:
		MapHandler(std::string mapPath, SDL_Renderer* renderer);
		~MapHandler();
		void ParseMap();
		void SaveCurrentMapLocation();
		void LoadMap();
	};
}




#endif
