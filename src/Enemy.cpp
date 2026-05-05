#include "Enemy.hpp"
#include <stdexcept>
#include <raymath.h>
void Enemy::DrawHitBox() const{
    if (isDead) 
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, GRAY);
    else
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, BLACK);
}

void Enemy::Move(const Player& player) {
    Vector2 distanceFromPlayer = player.GetPosition() - this ->GetPosition();
    if (Vector2Length(distanceFromPlayer) != 0)
        direction = Vector2Normalize(distanceFromPlayer);
}

void Enemy::ApplyMovement() {
    float dt = GetFrameTime();
    hitBox.x += speed*direction.x*dt; 
    hitBox.y += speed*direction.y*dt;
}

void Enemy::Update(Player& player, int ScreenWidth, int ScreenHeigth) {
    if (!isDead) {
        float dt = GetFrameTime();
        switch (state) {
        case State::Charging:
            if (timer >= chargeTime) {
                state = State::Attack;
                timer = 0.0f;
            }
            break;
        case State::Attack:
            if (!attackSucceeded) 
                Attack(player); // Apply damage if I still haven't
            if (timer >= AttackTime) {  // change state when the timer reaches the attack Time
                state = State::Idle;
                attackSucceeded = false;
                timer = 0.0f;
            }
            break;
        case State::Idle:
            direction = Vector2Normalize(player.GetPosition() - this->GetPosition());
            Move(player);   // Enemy will only move in Idle, leaving it static when Charging-Attacking
            ApplyMovement();
            if (DistanceFromPlayer(player) < attackRange) {
                state = State::Charging;
                timer = 0.0f;   // reseting state
            }
            break;
        default:
            throw std::invalid_argument("Unknown state");
            break;
        }
        
        
        DrawAttackHitBox();
        CheckCollisionWithBorders(ScreenWidth, ScreenHeigth);
        timer += dt;
    }

}

void Enemy::CheckCollisionWithBorders(int ScreenWidth, int ScreenHeigth) {
    if (hitBox.y < 0)
        hitBox.y = 0;
    if (hitBox.y + hitBox.height > ScreenHeigth)
        hitBox.y = ScreenHeigth - hitBox.height;
    if (hitBox.x < 0)
        hitBox.x = 0;
    if (hitBox.x + hitBox.width > ScreenWidth)
        hitBox.x = ScreenWidth - hitBox.width;
}

Vector2 Enemy::GetPosition() const {
    return {hitBox.x + hitBox.width/2, hitBox.y + hitBox.height/2};
}

Rectangle Enemy::GetAttackHitBox() const {
    // The attack center will be the actual position plus the addition of both halfs of both hitboxes in the direction of the attack
    Vector2 attackCenter = GetPosition() + direction*(hitBox.width/ 2.0f + attackSize.x / 2.0f);
    Rectangle attackRect {attackCenter.x - attackSize.x/ 2.0f, 
                    attackCenter.y - attackSize.y/ 2.0f,
                    attackSize.x,
                    attackSize.y};
    return attackRect;
}

float Enemy::DistanceFromPlayer(const Player& player) const{
    float distance = Vector2Length(player.GetPosition() - this -> GetPosition());
    return distance;
}
void Enemy::DrawAttackHitBox() const {
    switch (state)
    {
    case State::Idle:
        DrawRectangleRec(GetAttackHitBox(), GRAY);
        break;
    case State::Charging:
        DrawRectangleRec(GetAttackHitBox(), GREEN);
        break;
    case State::Attack:
        DrawRectangleRec(GetAttackHitBox(), RED);
    default:
        break;
    }
    
}

void Enemy::Attack(Player& player) {
    if (CheckCollisionRecs(this -> GetAttackHitBox(), player.GetHitBox())) {
        player.TakeDamage(damage);
        attackSucceeded = true;
    }
}

void Enemy::takeDamage(int damage) {
    if (damage >= currentHp){
        currentHp = 0;
        isDead = true;
    }
    else
        currentHp -= damage;
}
