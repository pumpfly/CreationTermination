#pragma once
#include <iostream>
#include "Player.h"

class GameOverScreen {
public:
    explicit GameOverScreen(Player &player) {
        player.onPlayerDeath.addListener([&] {
           showGameOverScreen();
        });
    }

    void onPlayerDeath() {
        showGameOverScreen();
    }

private:
    void showGameOverScreen() {
        std::cout << "Game over." << std::endl;
    }
};
