#include "Player.h"
#include "Score.h"
#include "GameOverScreen.h"

int main() {
    Player player;
    Score score(player);
    GameOverScreen gameOverScreen(player);
    player.getDamage(40);
    player.getDamage(40);
    player.getDamage(40);
}