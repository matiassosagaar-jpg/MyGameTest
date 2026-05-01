#pragma once
#include <raylib.h>
#include "Player.hpp"
class Enemy {
private:    
    int maxHp = 100;
    int currentHp = maxHp;
    Rectangle hitBox;
    Vector2 direction {0,0};
    int attackRange = 75;
    Vector2 attackSize {50,50};
    int damage = 20;
    float attackCooldown = 0;
    float speed = 150; //100 pixels per second
    bool isDead = false;
public:
    Enemy() : hitBox {800, 800, 50, 50} {};
    Enemy(Vector2 startPos) : hitBox{ startPos.x, startPos.y, 50, 50 } {};
    void DrawHitBox() const;
    void Update(Player& player, int ScreenWidth, int ScreenHeigth);
    void CheckCollisionWithBorders(int ScreenWidth, int ScreenHeigth);
    Vector2 GetPosition() const;
    Rectangle GetAttackHitBox() const;
    Rectangle GetHitBox() const {return hitBox;}
    float DistanceFromPlayer(const Player& player) const;
    void Attack(Player& player);
    void takeDamage(int damage);
    void Attack();
private:
    void Move(const Player& player);
    void ApplyMovement();
    void DrawAttackHitBox() const;
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
