#pragma once
#include <iostream>
#include "Player.h"

class Score {
public:
    explicit Score(Player &player) {
        player.onPlayerDeath.addListener([&] {
            score -= 100;
            printScore();
        });
    }


private:
    void printScore() {
        std::cout << "Score: " << score << std::endl;
    }

    int score = 500;
};
