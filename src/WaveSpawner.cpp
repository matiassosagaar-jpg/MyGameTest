#include "WaveSpawner.hpp"
#include <algorithm>
void WaveSpawner::Start() {
    wave++;
    enemiesToSpawn = wave;
    enemiesSpawned = 0;
    spawnTimer = 0.0f;
    enemies.clear();
    enemies.reserve(wave);
}

void WaveSpawner::Update(Player& player, int screenWidth, int screenHeight) {
    spawnTimer += GetFrameTime();
    while (spawnTimer >= spawnRate) {
        spawnTimer -= spawnRate;
        if (enemiesSpawned < enemiesToSpawn){
            SpawnEnemy(screenWidth, screenHeight);
            enemiesSpawned++;
        }
    }
    UpdateEnemies(player, screenWidth, screenHeight);
    if (enemiesSpawned >= enemiesToSpawn && enemies.empty()) {
        Start();
    }
}

void WaveSpawner::SpawnEnemy(int screenWidth, int screenHeight) {
    float x = GetRandomValue(50, screenWidth - 50);
    float y = GetRandomValue(50, screenHeight - 50);
    Vector2 startPos {x, y};
    enemies.push_back(Enemy(startPos));
}

void WaveSpawner::UpdateEnemies(Player& player, int screenWidth, int screenHeight) {
    for (Enemy& enemy : enemies) {
        enemy.Update(player, screenWidth, screenHeight);
    }
    ClearDeadEnemies();
}

void WaveSpawner::DrawEnemies() const{
    for (const Enemy& enemy : enemies) {
        enemy.DrawHitBox();
    }
}

void WaveSpawner::HandlePlayerAttack(Rectangle playerAttackHitBox, int damage) {
    for (Enemy& enemy : enemies) {
        if (CheckCollisionRecs(playerAttackHitBox, enemy.GetHitBox()))
            enemy.takeDamage(damage);
    }
}

int WaveSpawner::GetDeadEnemies() const{
    return std::count_if(enemies.begin(), enemies.end(),
        [](const Enemy& enemy) {return enemy.IsDead();} 
    );
}

void WaveSpawner::ClearDeadEnemies() {
    enemies.erase( //remove_if will reorder the vector, setting all the enemies that are dead in an invalid state, so they'll appear at the end of the vector
        std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {return enemy.IsDead();}),
        enemies.end() // and returns the pointer to the first invalid element of the vector
    ); // erase will elimante elements from that iterator to the end of the vector
}

    