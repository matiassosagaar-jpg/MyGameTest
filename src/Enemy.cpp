#include "Enemy.hpp"
#include <stdexcept>
#include <raymath.h>
Enemy::Enemy() : hitBox {800, 800, 50, 50} {};

void Enemy::DrawHitBox() {
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
            Attack(player); // Aplico daño si aún no lo hice
        if (timer >= AttackTime) {  //cambio de estado cuando termina el tiempo estipulado
            state = State::Idle;
            attackSucceeded = false;
            timer = 0.0f;
        }
        break;
    case State::Idle:
        Move(player);   // Solo moverse en Idle, así enemy está estático mientras ataca
        ApplyMovement();
        if (DistanceFromPlayer(player) < attackRange) {
            state = State::Charging;
            timer = 0.0f;   // resetando el estado
        }
        break;
    default:
        throw std::invalid_argument("Unknown state");
        break;
    }
    
    
    DrawAttackHitBox(player);
    CheckCollisionWithBorders(ScreenWidth, ScreenHeigth);
    timer += dt;

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

Rectangle Enemy::GetAttackHitBox(const Player& player) const{
    Vector2 attackDir = Vector2Normalize(player.GetPosition() - this->GetPosition());
    // el centro del ataque será la posición actual + la suma de las mitades de ambas hitbox en la dirección del ataque
    Vector2 attackCenter = GetPosition() + attackDir*(hitBox.width/ 2.0f + attackSize.x / 2.0f);
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
void Enemy::DrawAttackHitBox(const Player& player) {
    switch (state)
    {
    case State::Idle:
        DrawRectangleRec(GetAttackHitBox(player), GRAY);
        break;
    case State::Charging:
        DrawRectangleRec(GetAttackHitBox(player), GREEN);
        break;
    case State::Attack:
        DrawRectangleRec(GetAttackHitBox(player), RED);
    default:
        break;
    }
    
}

void Enemy::Attack(Player& player) {
    if (CheckCollisionRecs(this -> GetAttackHitBox(player), player.GetHitBox())) {
        player.TakeDamage(damage);
        attackSucceeded = true;
    }
}