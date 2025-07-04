#include "brewEngine/collision/SpatialGridManager.h"

#include "brewEngine/rendering/GeometryRenderer.h"

namespace gl3::brewEngine::collision {
    SpatialGridManager::SpatialGridManager(Game &engine, int cellSize, int screenWidth, int screenHeight):
        cellSize(cellSize),
        screenWidth(screenWidth),
        screenHeight(screenHeight) {

        spatialGrid = std::vector<std::vector<std::vector<size_t>>>(1 + ((screenWidth-1)/cellSize));

        for (auto & i : spatialGrid) {
            i = std::vector<std::vector<size_t>>(1 + ((screenHeight-1)/cellSize), std::vector<size_t>());
        }

    }

    void SpatialGridManager::clearIDs() {
        for(auto& row : spatialGrid) {
            for(auto& cell : row) {
                cell.clear();
            }
        }
    }

    std::vector<int> SpatialGridManager::boundingBox(int entityMinX, int entityMaxX, int entityMinY, int entityMaxY) {
        //Mapping world position
        int entityMinXcell = std::max<int>(0, static_cast<int>(std::floor(entityMinX / cellSize)));
        int entityMaxXcell = std::min<int>(static_cast<int>(spatialGrid[0].size() - 1),
                                     static_cast<int>(std::floor(entityMaxX/ cellSize)));

        int entityMinYcell = std::max<int>(0, static_cast<int>(std::floor(entityMinY / cellSize)));
        int entityMaxYcell = std::min<int>(static_cast<int>(spatialGrid[0].size() - 1),
                                     static_cast<int>(std::floor(entityMaxY / cellSize)));

        std::vector<int> boundingBox = {entityMinXcell, entityMaxXcell, entityMinYcell, entityMaxYcell};

        return boundingBox;
    }

    void SpatialGridManager::cellAssignment(int entityMinX, int entityMaxX, int entityMinY,
                                            int entityMaxY, size_t ID) {

        // calculate which cells the entity touches
        std::vector<int> boundingBox = SpatialGridManager::boundingBox(entityMinX, entityMaxX, entityMinY, entityMaxY);
        int entityMinXcell = boundingBox[0];
        int entityMaxXcell = boundingBox[1];
        int entityMinYcell = boundingBox[2];
        int entityMaxYcell = boundingBox[3];

        //Assigning entity IDs to corresponding cells
        for(int cX = entityMinXcell; cX <= entityMaxXcell; cX++) {
            for(int cY = entityMinYcell; cY <= entityMaxYcell; cY++) {
                spatialGrid[cX][cY].push_back(ID);
                //Debugging:
                for (auto currEntity: spatialGrid[cX][cY]) {
                    //std::cout << "Row Number: " << cX << " Column Number: " << cY << " Cell content: " << currEntity << std::endl;
                }
            }
        }
    }

    std::vector<int> SpatialGridManager::queryForCollisionCandidates(int entityMinX, int entityMaxX, int entityMinY,
        int entityMaxY) {

        std::vector<int> boundingBox = SpatialGridManager::boundingBox(entityMinX, entityMaxX, entityMinY, entityMaxY);
        int entityMinXcell = boundingBox[0];
        int entityMaxXcell = boundingBox[1];
        int entityMinYcell = boundingBox[2];
        int entityMaxYcell = boundingBox[3];

        std::vector<int> collisionCandidates;

        for(int cX = entityMinXcell; cX <= entityMaxXcell; cX++) {
            for(int cY = entityMinYcell; cY <= entityMaxYcell; cY++) {
                if(spatialGrid[cX][cY].empty()) {continue;}
                collisionCandidates.insert(collisionCandidates.end(), spatialGrid[cX][cY].begin() ,spatialGrid[cX][cY].end());
            }
        }

        return collisionCandidates;
    }

    // Debugging

    void SpatialGridManager::drawGrid(int cellSize, int screenWidth, int screenHeight) {
        for (int i = 0; i < screenWidth; i = i + cellSize) {
            rendering::GeometryRenderer::Instance().drawLine(glm::vec4(1.0, 0.0, 0.0, 1.0), {i, 0.0}, {i, screenHeight});
        }
        for (int j = 0; j < screenHeight; j = j + cellSize) {
            rendering::GeometryRenderer::Instance().drawLine(glm::vec4(1.0, 0.0, 0.0, 1.0), {0.0, j}, {screenWidth, j});
        }
    }
}
