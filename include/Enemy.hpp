#pragma once
#include <raylib.h>
#include "Player.hpp"
class Enemy {
private:    
    int hp = 100;
    Rectangle hitBox;
    Vector2 direction {0,0};
    int attackRange = 75;
    Vector2 attackSize {75,75};
    int damage = 20;
    float attackCooldown = 0;
    float speed = 150; //100 pixels per second
public:
    Enemy() : hitBox {800, 800, 50, 50} {};
    Enemy(Vector2 startPos) : hitBox{ startPos.x, startPos.y, 50, 50 } {};
    void DrawHitBox() const;
    void Update(Player& player, int ScreenWidth, int ScreenHeigth);
    void CheckCollisionWithBorders(int ScreenWidth, int ScreenHeigth);
    Vector2 GetPosition() const;
    Rectangle GetAttackHitBox(const Player& player) const;
    float DistanceFromPlayer(const Player& player) const;
    void Attack(Player& player);
private:
    void Move(const Player& player);
    void ApplyMovement();
    void DrawAttackHitBox(const Player& player);
    // --- states ----
    enum class State {Charging,
                    Attack,
                    Idle};
    State state = State::Idle;
    bool attackSucceeded = false;
    float timer = 0;
    static constexpr float chargeTime = 0.8f;
    static constexpr float AttackTime = 0.2f;

};
