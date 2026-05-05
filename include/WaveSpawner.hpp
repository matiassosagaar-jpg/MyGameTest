#pragma once
#include <vector>
#include "Enemy.hpp"
class WaveSpawner {
private:
    std::vector<Enemy> enemies;
    int wave = 0;
    float spawnTimer = 0.0f;
    static constexpr float spawnRate = 3.0f;
    int enemiesSpawned = 0;
    int enemiesToSpawn = 0;
public:
    WaveSpawner() = default;
    void Update(Player& player, int screenWidth, int screenHeight);
    void DrawEnemies() const;
    void HandlePlayerAttack(Rectangle playerAttackHitBox, int damage);
    int GetDeadEnemies() const;
    int GetWave() const {return wave;}
private:
    void SpawnEnemy(int screenWidth, int screenHeight);
    void UpdateEnemies(Player& player, int screenWidth, int screenHeight);
    void Start();
    void ClearDeadEnemies();
    
};