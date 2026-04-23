#pragma once
#include <raylib.h>
#include "Player.hpp"
class Enemy {
private:    
    int hp = 100;
    Rectangle hitBox;
    Vector2 direction {0,0};
    float speed = 150; //100 pixels per second
public:
    Enemy();
    void DrawHitBox();
    void Update(const Vector2& playerPos, int ScreenWidth, int ScreenHeigth);
    void CheckCollisionWithBorders(int ScreenWidth, int ScreenHeigth);
    Vector2 GetPosition() const;
private:
    void Move(const Vector2& playerPos);
    void ApplyMovement();
    
};