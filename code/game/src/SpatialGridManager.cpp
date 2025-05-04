//
// Created by Lisa B on 01/05/2025.
//

#include "SpatialGridManager.h"
#include "rendering/GeometryRenderer.h"

SpatialGridManager::SpatialGridManager(int cellSize, int screenWidth, int screenHeight):
    cellSize(cellSize),
    screenWidth(screenWidth),
    screenHeight(screenHeight) {

    spatialGrid = std::vector<std::vector<std::vector<int>>>(1 + ((screenWidth-1)/cellSize));

    for (auto & i : spatialGrid) {
        i = std::vector<std::vector<int>>(1 + ((screenHeight-1)/cellSize), std::vector<int>());
    }

}

void SpatialGridManager::cellAssignment(gl3::Entity *entity) {

    if(entity->getPosition().x < 0 || entity->getPosition().y < 0) return;

    //Mapping world position

    int column = std::floor(entity->getPosition().x / cellSize);
    int row = std::floor(entity->getPosition().y / cellSize);

    //TODO: Entities need IDs for putting them inside the grid cells. 


}

// Debuging

void SpatialGridManager::drawGrid(gl3::Game* game, int cellSize, int screenWidth, int screenHeight) {
    for (int i = 0; i < screenWidth; i = i + cellSize) {
        GeometryRenderer::Instance().drawLine(game, {i, 0.0}, {i, screenHeight});
    }
    for (int j = 0; j < screenHeight; j = j + cellSize) {
        GeometryRenderer::Instance().drawLine(game, {0.0, j}, {screenWidth, j});
    }
}
