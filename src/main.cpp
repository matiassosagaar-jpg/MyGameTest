    #include "raylib.h"
    #include "Player.hpp"
    #include "Enemy.hpp"
    #include "WaveSpawner.hpp"
    int main() {
        InitWindow(800, 600, "GoblinKiller");
        SetTargetFPS(60);
        ToggleFullscreen();
        Player player;
        WaveSpawner waves;
        while (!WindowShouldClose()) {
            player.Update(GetScreenWidth(), GetScreenHeight());
            waves.Update(player, GetScreenWidth(), GetScreenHeight());
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(15,15, player.GetMaxHp()*4, 40, RED);
            DrawRectangle(15,15, player.GetCurrentHp()*4, 40, GREEN);
            player.DrawHitBox();
            waves.DrawEnemies();
            DrawText("Goblin Killer", 300, 280, 20, BLACK);
            EndDrawing();
        }

        CloseWindow();
        return 0;
    }
