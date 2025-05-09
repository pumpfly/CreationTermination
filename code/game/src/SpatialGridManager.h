//
// Created by Lisa B on 01/05/2025.
//

#pragma once

#include <vector>

#include "entities/Entity.h"

class SpatialGridManager {
public:
    explicit SpatialGridManager(int cellSize = 100, int screenWidth = 1280, int screenHeight = 720);
    virtual ~SpatialGridManager() = default;

    // Getter and Setter
    [[nodiscard]] const int &getCellSize() const {return cellSize; }
    [[nodiscard]] const int &getScreenWidth() const {return screenWidth; }
    [[nodiscard]] const int &getScreenHeight() const {return screenHeight; }

    void cellAssignment (gl3::Entity *entity);

    //Debug
    static void drawGrid(gl3::Game* game, int cellSize, int screenWidth, int screenHeight);
    void querryForCollisionPairs();


private:
    std::vector<std::vector<std::vector<int>>> spatialGrid;

protected:
    int cellSize;
    int screenWidth;
    int screenHeight;
};

