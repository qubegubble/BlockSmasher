#include "Headers\tinyxml2.h"
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Headers\Map.h"

namespace Map {

    void MapHandler::ParseMap() {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(mapPath.c_str()) != tinyxml2::XML_SUCCESS) {
            std::cerr << "Failed to load map: " << mapPath << std::endl;
            return;
        }

        tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
        if (!mapElement) {
            std::cerr << "No map element found in .tmx file." << std::endl;
            return;
        }

        // Parse tilesets
        ParseTileSet(mapElement);

        // Parse layers
        ParseLayers(mapElement);
    }

    void MapHandler::ParseTileSet(tinyxml2::XMLElement* mapElement) {
        tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
        while (tilesetElement) {
            const char* source = tilesetElement->Attribute("source");
            if (source) {
                // Load the tileset image and store it in the tilesets map
                std::string sourcePath = "map-tiles/" + std::string(source);
                SDL_Texture* texture = LoadTexture(sourcePath);
                if (texture) {
                    tilesets.push_back(texture);
                }
            }

            tilesetElement = tilesetElement->NextSiblingElement("tileset");
        }
    }

    void MapHandler::ParseLayers(tinyxml2::XMLElement* mapElement) {
        tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
        while (layerElement) {
            tinyxml2::XMLElement* dataElement = layerElement->FirstChildElement("data");
            if (dataElement) {
                const char* encoding = dataElement->Attribute("encoding");
                if (encoding && std::string(encoding) == "csv") {
                    const char* data = dataElement->GetText();
                    ParseCSVLayerData(data);
                }
            }
            layerElement = layerElement->NextSiblingElement("layer");
        }
    }

    void MapHandler::ParseCSVLayerData(const char* data) {
        // Assuming a simple CSV parsing here
        std::stringstream ss(data);
        std::string token;
        while (std::getline(ss, token, ',')) {
            int tileID = std::stoi(token);
            if (tileID > 0) {
                // Store tileID to later render the correct tile
                mapTileIDs.push_back(tileID - 1);  // Tilesets are usually 1-based in TMX files
            }
        }
    }

    SDL_Texture* MapHandler::LoadTexture(std::string path) {
        SDL_Surface* tempSurface = IMG_Load(path.c_str());  // Using SDL_image to load PNG files
        if (!tempSurface) {
            std::cerr << "Failed to load texture: " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
        return texture;
    }

} // namespace Map
