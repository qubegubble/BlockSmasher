#include "Headers/Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <filesystem>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

using namespace Map;


Map::MapHandler::MapHandler()
{
}

Map::MapHandler::~MapHandler()
{
}

rapidjson::Document Map::MapHandler::LoadJSONMap(const std::string& filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		assert(ifs.is_open());
		std::cerr << "Error opening file: " << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);
	if (doc.HasParseError()) {
		std::cerr << "Error parsing JSON file." << std::endl;
	}
	return doc;
}

void MapHandler::ParseMap(const rapidjson::Document& doc)
{
	if (doc.HasMember("width") && doc.HasMember("height")) {
		assert(doc.HasMember("width") && doc.HasMember("height"));
		int mapWidth = doc["width"].GetInt();
		int mapHeight = doc["height"].GetInt();
	}
}

TileSet MapHandler::ParseTileset(const rapidjson::Document& doc) {
	TileSet tileset;

	const rapidjson::Value& tilesets = doc["tilesets"];
	const rapidjson::Value& tilesetEntry = tilesets[0];

	// Load the external tileset file
	std::string tilesetSource = tilesetEntry["source"].GetString();
	std::ifstream tilesetFile(tilesetSource);
	if (!tilesetFile.is_open()) {
		std::cerr << "Error opening tileset file: " << tilesetSource << std::endl;
		exit(EXIT_FAILURE);
	}

	rapidjson::IStreamWrapper isw(tilesetFile);
	rapidjson::Document tilesetDoc;
	tilesetDoc.ParseStream(isw);
	if (tilesetDoc.HasParseError()) {
		assert(!tilesetDoc.HasParseError());
		std::cerr << "Error parsing tileset JSON file." << std::endl;
		exit(EXIT_FAILURE);
	}

	// Parse tileset data from the loaded tileset document
	tileset.firstGid = tilesetDoc["firstgid"].GetInt();
	tileset.tileWidth = tilesetDoc["tilewidth"].GetInt();
	tileset.tileHeight = tilesetDoc["tileheight"].GetInt();
	tileset.imageSource = tilesetDoc["image"].GetString();

	return tileset;
}


TileLayer MapHandler::ParseTileLayer(const rapidjson::Document& doc) {
	TileLayer layer;

	if (!doc.HasMember("layers") || !doc["layers"].IsArray()) {
		assert(doc.HasMember("layers") && doc["layers"].IsArray());
		std::cerr << "Invalid layers data in JSON." << std::endl;
		exit(EXIT_FAILURE);
	}

	const rapidjson::Value& layers = doc["layers"];
	const rapidjson::Value& layerEntry = layers[0];
	layer.width = layerEntry["width"].GetInt();
	layer.height = layerEntry["height"].GetInt();
	const rapidjson::Value& dataArray = layerEntry["data"];

	if (!dataArray.IsArray()) {
		assert(dataArray.IsArray());
		std::cerr << "Invalid data array in tile layer." << std::endl;
		exit(EXIT_FAILURE);
	}

	for (rapidjson::SizeType i = 0; i < dataArray.Size(); i++) {
		layer.data.push_back(dataArray[i].GetInt());
	}

	return layer;
}


SDL_Texture* MapHandler::LoadTexture(SDL_Renderer* renderer, const std::string& path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (!surface) {
		assert(surface);
		std::cerr << "Unable to load image: " << IMG_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void Map::MapHandler::RenderTileLayer(SDL_Renderer* renderer, const TileLayer& layer, SDL_Texture* tileset, const TileSet& tilesetInfo) {
	int tilesPerRow = 256 / tilesetInfo.tileWidth; // Assuming a texture size of 256 pixels width
	for (int i = 0; i < layer.height; ++i) {
		for (int j = 0; j < layer.width; ++j) {
			int tileID = layer.data[i * layer.width + j] - tilesetInfo.firstGid;
			if (tileID >= 0) {
				int tileX = (tileID % tilesPerRow) * tilesetInfo.tileWidth;
				int tileY = (tileID / tilesPerRow) * tilesetInfo.tileHeight;
				SDL_Rect srcRect = { tileX, tileY, tilesetInfo.tileWidth, tilesetInfo.tileHeight };
				SDL_Rect dstRect = { j * tilesetInfo.tileWidth, i * tilesetInfo.tileHeight, tilesetInfo.tileWidth, tilesetInfo.tileHeight };
				SDL_RenderCopy(renderer, tileset, &srcRect, &dstRect);
			}
		}
	}
}
