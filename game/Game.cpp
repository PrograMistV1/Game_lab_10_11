#include "Game.h"
#include <filesystem>

namespace fs = std::filesystem;

void Game::load() {
    fs::create_directory("./saves");
    this->player = new Player;
}
