    #include "raylib.h"
    #include "Player.hpp"
    #include "Enemy.hpp"
    #include "WaveSpawner.hpp"
    #include <iostream>
    #include <cstring>
    int main() {
        InitWindow(800, 600, "GoblinKiller");
        SetTargetFPS(60);
        ToggleFullscreen();
        bool GameOver {false};
        Player player(GetScreenWidth(), GetScreenHeight());
        std::string score;
        std::string wave;
        WaveSpawner waves;
        while (!WindowShouldClose()) {
            if (!GameOver){
                player.Update(GetScreenWidth(), GetScreenHeight());
                // Consume Player attack from player
                if (player.ConsumeAttack()) 
                    // Let waves handle the damage intake of the enemies
                    waves.HandlePlayerAttack(player.GetAttackHitbox(), player.GetDamage());
                waves.Update(player, GetScreenWidth(), GetScreenHeight());
                score = std::to_string(waves.GetDeadEnemies());
                wave = std::to_string(waves.GetWave());
                if (player.IsDead()){
                    GameOver = true;
                }
            }
            if (GameOver && IsKeyPressed(KEY_ENTER)) {
                player = Player(GetScreenWidth(), GetScreenHeight());
                waves = WaveSpawner();
                GameOver = false;
            }       
            BeginDrawing();
            if (GameOver) {
                ClearBackground(WHITE);
                DrawText("GAME OVER", GetScreenWidth()/2 -100*5, GetScreenHeight()/2, 100, BLACK);
                DrawText("Press Enter to restart", GetScreenWidth()/2 -100*5, GetScreenHeight()/2 + 100, 100, BLACK);
            } else {
                ClearBackground(RAYWHITE);
                DrawRectangle(15,15, player.GetMaxHp()*4, 40, RED);
                DrawRectangle(15,15, player.GetCurrentHp()*4 , 40, GREEN);
                DrawText("Waves", GetScreenWidth()/2, 20, 40, BLACK);
                DrawText(wave.c_str(), GetScreenWidth()/2 + 60, 50, 40, BLACK);
                DrawText("Score", GetScreenWidth() - 160, 10, 40, BLACK);
                DrawText(score.c_str(), GetScreenWidth() - 130, 50, 40, BLACK);
                player.DrawHitBox();
                waves.DrawEnemies();
            }
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }
