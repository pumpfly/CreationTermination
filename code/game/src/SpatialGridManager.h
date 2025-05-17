//
// Created by Lisa B on 01/05/2025.
//

#pragma once

#include <map>
#include <vector>

#include "entities/Entity.h"

namespace gl3 {
    class SpatialGridManager {
    public:
        explicit SpatialGridManager(int cellSize = 150, int screenWidth = 1280, int screenHeight = 720);
        virtual ~SpatialGridManager() = default;

        // Getter and Setter
        [[nodiscard]] const int &getCellSize() const {return cellSize; }
        [[nodiscard]] const int &getScreenWidth() const {return screenWidth; }
        [[nodiscard]] const int &getScreenHeight() const {return screenHeight; }

        void clearIDs();
        std::vector<int> boundingBox(int entityMinX, int entityMaxX, int entityMinY, int entityMaxY);
        void cellAssignment (int entityMinX, int entityMaxX, int entityMinY, int entityMaxY,size_t ID);
        std::vector<size_t> queryForCollisionCandidates(int entityMinX, int entityMaxX, int entityMinY, int entityMaxY);


        //Debug
        static void drawGrid(gl3::Game* game, int cellSize, int screenWidth, int screenHeight);

        std::vector<std::vector<std::vector<size_t>>> spatialGrid;

    protected:
        int cellSize;
        int screenWidth;
        int screenHeight;
    };
}