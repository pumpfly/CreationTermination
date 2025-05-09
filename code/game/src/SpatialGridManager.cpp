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

    int entityPosX = static_cast<int>(entity->getPosition().x);
    int entityPosY = static_cast<int>(entity->getPosition().y);

    int entitySizeX = entity->getScale().x;
    int entitySizeY = entity->getScale().y;

    // if entity is outside the grid than it should not be added to a spatialGrid cell
    if(entityPosX < 0 || entityPosY < 0
        || entityPosX > screenWidth || entityPosY > screenHeight) return;

    //Mapping world position
    int entityMinXcell = static_cast<int>(std::floor(entityPosX / cellSize));
    int entityMaxXcell = static_cast<int>(std::floor((entityPosX + entitySizeX) / cellSize));

    int entityMinYcell = static_cast<int>(std::floor(entityPosY / cellSize));
    int entityMaxYcell = static_cast<int>(std::floor((entityPosY + entitySizeY) / cellSize));

    int ID = entity->getID();

    for(int cX = entityMinXcell; cX <= entityMaxXcell; cX++) {
        for(int cY = entityMinYcell; cY <= entityMaxYcell; cY++) {
            spatialGrid[cX][cY].push_back(ID);
        }
    }

}

void SpatialGridManager::querryForCollisionPairs() {


    std::vector<int> collisionPairs(2);

    int entityA;
    int entityB;

    std::vector<std::vector<int>> gridColl;
    std::vector<int> gridCell;

    //Debugging
    int collisions = 0;

    for(int i = 0; i < spatialGrid.max_size(); i++) {

        gridColl = spatialGrid[i];

        if(gridColl.empty()){continue;}

        for(int j = 0; j < gridColl.size(); j++) {
            gridCell = gridColl[j];

            if(gridCell.empty()) {continue;}

            for(int k = 0; k < gridCell.size(); k++) {

            }
        }
    }
}

// Debugging

void SpatialGridManager::drawGrid(gl3::Game* game, int cellSize, int screenWidth, int screenHeight) {
    for (int i = 0; i < screenWidth; i = i + cellSize) {
        GeometryRenderer::Instance().drawLine(game, {i, 0.0}, {i, screenHeight});
    }
    for (int j = 0; j < screenHeight; j = j + cellSize) {
        GeometryRenderer::Instance().drawLine(game, {0.0, j}, {screenWidth, j});
    }
}
