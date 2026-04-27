#include "Player.hpp"
#include <raymath.h>
Player::Player() : hitBox {0,  0, 70, 70} {
};

void Player::DrawHitBox() {
    DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, BLACK);
}

void Player::Move() {
    Vector2 inputDirection {0,0};
    if(IsKeyDown(KEY_W)) 
        inputDirection.y -= 1;
    if(IsKeyDown(KEY_S))
        inputDirection.y += 1;
    if(IsKeyDown(KEY_A))
        inputDirection.x -= 1;
    if (IsKeyDown(KEY_D))
        inputDirection.x += 1;
    if (Vector2Length(inputDirection) != 0) // si el vector es nulo (no se pasaron inputs), su norma será cero
        direction = Vector2Normalize(inputDirection); // no intento normalizar un vector nulo
}

void Player::ApplyMovement() {
    float dt = GetFrameTime(); // tiempo transcurrido desde el último frame
    hitBox.x += speed*direction.x*dt; // como esto se calculará cada frame, al multiplicar por dt, hago que la velocidad por segundo no cambie
    hitBox.y+= speed*direction.y*dt; // si cambian los fps
}

void Player::Update(int ScreenWidth, int ScreenHeigth) {
    direction.x = 0, direction.y = 0;
    Move();
    ApplyMovement();
    CheckCollisionWithBorders(ScreenWidth, ScreenHeigth);

}

void Player::CheckCollisionWithBorders(int ScreenWidth, int ScreenHeigth) {
    if (hitBox.y < 0)
        hitBox.y = 0;
    if (hitBox.y + hitBox.height > ScreenHeigth)
        hitBox.y = ScreenHeigth - hitBox.height;
    if (hitBox.x < 0)
        hitBox.x = 0;
    if (hitBox.x + hitBox.width > ScreenWidth)
        hitBox.x = ScreenWidth - hitBox.width;
}

Vector2 Player::GetPosition() const {
    return {hitBox.x + hitBox.width/2, hitBox.y + hitBox.height/2};
}

Rectangle Player::GetHitBox() const {
    return hitBox;
}

void Player::TakeDamage(int damage) {
    if (damage > currentHp)
        currentHp = 0;
    else
        currentHp -= damage;
}

int Player::GetCurrentHp() const{
    return currentHp;
}
int Player::GetMaxHp() const{
    return maxHp;
}