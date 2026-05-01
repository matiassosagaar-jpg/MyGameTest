#pragma once
#include <string>
#include <raylib.h>
class Player {
private:    
    int maxHp = 100;
    int currentHp = maxHp;
    Rectangle hitBox;
    Vector2 direction {0,0};
    Vector2 aimDirection {0,0};
    Vector2 attackSize {50,50};
    float speed = 200; //100 pixels per second
    bool isDead = false;
public:
    Player(int screenWidth, int screenHeight);
    void DrawHitBox() const;
    void Update(int ScreenWidth, int ScreenHeigth);
    void CheckCollisionWithBorders(int ScreenWidth, int ScreenHeigth);
    Vector2 GetPosition() const;
    Rectangle GetHitBox() const;
    Rectangle GetAttackHitbox() const;
    void TakeDamage(int damage);
    int GetMaxHp() const;
    int GetCurrentHp() const;
private:
    void Move();
    void ApplyMovement();
    void setAimDirectionMouse();
    //States
private:
    enum class State {
        Idle, 
        Recovery
    };
    State state = State::Idle;
    float timeInRecovery = 0.0f;
    const float recoveryTime = 0.5f;
private:
    //Attack Logic
    int damage = 40;
    bool attackedThisFrame = false;
    void DrawAttackHitbox() const;
public:
    int GetDamage() {return damage;}
    bool ConsumeAttack();
};



//cpp

