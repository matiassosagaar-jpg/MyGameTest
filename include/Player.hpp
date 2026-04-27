#pragma once
#include <string>
#include <raylib.h>
class Player {
private:    
    int maxHp = 100;
    int currentHp = maxHp;
    Rectangle hitBox;
    Vector2 direction {0,0};
    float speed = 200; //100 pixels per second
public:
    Player();
    void DrawHitBox();
    void Update(int ScreenWidth, int ScreenHeigth);
    void CheckCollisionWithBorders(int ScreenWidth, int ScreenHeigth);
    Vector2 GetPosition() const;
    Rectangle GetHitBox() const;
    void TakeDamage(int damage);
    int GetMaxHp() const;
    int GetCurrentHp() const;
private:
    void Move();
    void ApplyMovement();
    
};



//cpp

