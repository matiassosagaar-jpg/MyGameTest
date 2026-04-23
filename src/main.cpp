    #include "raylib.h"
    #include "Player.hpp"
    #include "Enemy.hpp"
    int main() {
        InitWindow(800, 600, "GoblinKiller");
        SetTargetFPS(60);
        ToggleFullscreen();
        Player player;
        Enemy enemy;
        while (!WindowShouldClose()) {
            player.Update(GetScreenWidth(), GetScreenHeight());
            enemy.Update(player.GetPosition(), GetScreenWidth(), GetScreenHeight());
            BeginDrawing();
            ClearBackground(RAYWHITE);
            player.DrawHitBox();
            enemy.DrawHitBox();
            DrawText("Goblin Killer", 300, 280, 20, BLACK);
            EndDrawing();
        }

        CloseWindow();
        return 0;
    }
