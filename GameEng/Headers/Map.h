#ifndef MAP_H
#define MAP_H
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>


namespace Map {
	struct TileSet {
		std::string imageSource;
		int firstGid;
		int tileWidth, tileHeight;
	};
	struct TileLayer {
		std::vector<int> data;
		int width, height;
	};
	class MapHandler {
	public:
		MapHandler();
		~MapHandler();
		rapidjson::Document LoadJSONMap(const std::string& filename);
		void ParseMap(const rapidjson::Document& doc);
		TileSet ParseTileset(const rapidjson::Document& doc);
		TileLayer ParseTileLayer(const rapidjson::Document& doc);
		void RenderTileLayer(SDL_Renderer* renderer, const TileLayer& layer, SDL_Texture* tileset, const TileSet& tilesetInfo);
		SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& path);
	};
}




#endif
