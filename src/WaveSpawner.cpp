#include "WaveSpawner.hpp"
void WaveSpawner::Start() {
    wave++;
    enemiesToSpawn = wave;
    enemiesSpawned = 0;
    spawnTimer = 0.0f;
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
    if (enemiesSpawned >= enemiesToSpawn) {
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

