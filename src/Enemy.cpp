#include "Enemy.hpp"

#include <raymath.h>
Enemy::Enemy() : hitBox {800, 800, 40, 100} {
};

void Enemy::DrawHitBox() {
    DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, BLACK);
}

void Enemy::Move(const Vector2& playerPos) {
    Vector2 distanceFromPlayer = playerPos - GetPosition();
    if (Vector2Length(distanceFromPlayer) != 0)
        direction = Vector2Normalize(distanceFromPlayer);
}

void Enemy::ApplyMovement() {
    float dt = GetFrameTime();
    hitBox.x += speed*direction.x*dt; 
    hitBox.y += speed*direction.y*dt;
}

void Enemy::Update(const Vector2& playerPos, int ScreenWidth, int ScreenHeigth) {
    Move(playerPos);
    ApplyMovement();
    CheckCollisionWithBorders(ScreenWidth, ScreenHeigth);

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