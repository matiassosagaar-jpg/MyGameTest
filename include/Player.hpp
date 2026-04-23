#pragma once
#include <string>
#include <raylib.h>
class Player {
private:    
    int hp = 100;
    Rectangle hitBox;
    Vector2 direction {0,0};
    float speed = 200; //100 pixels per second
public:
    Player();
    void DrawHitBox();
    void Update(int ScreenWidth, int ScreenHeigth);
    void CheckCollisionWithBorders(int ScreenWidth, int ScreenHeigth);
    Vector2 GetPosition() const;
private:
    void Move();
    void ApplyMovement();
    
};

//cpp

