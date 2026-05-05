#include "Player.hpp"
#include <raymath.h>

Player::Player(int screenWidth, int screenHeight)
    : hitBox{screenWidth/2.0f, screenHeight/2.0f, 70, 70} {
}
void Player::DrawHitBox() const {
    if (!isDead)
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, BLACK);
    else
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, GRAY);
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
    if (Vector2Length(inputDirection) != 0) // if the vector is null (no inputs) it's length will be zero
        direction = Vector2Normalize(inputDirection); // We won't try to normalize a null vector
    else
        direction = {0,0};
    }

void Player::ApplyMovement() {
    float dt = GetFrameTime(); // time passed since last frame
    hitBox.x += speed*direction.x*dt; // velocity per second won't change if FPS are different, because it's multiplied by dt
    hitBox.y+= speed*direction.y*dt; // 
}

void Player::Update(int ScreenWidth, int ScreenHeigth) {
    if (!isDead) {
        setAimDirectionMouse();
        if (state != State::Recovery){
            Move();
            ApplyMovement();
        }
        if (state == State::Recovery) {
            timeInRecovery += GetFrameTime();
            if (timeInRecovery >= recoveryTime) {
                timeInRecovery = 0.0f;
                state = State::Idle;
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && state == State::Idle) {
            attackedThisFrame = true;
            state = State::Recovery;
        }
        CheckCollisionWithBorders(ScreenWidth, ScreenHeigth);
        DrawAttackHitbox();
    }
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
    if (damage >= currentHp){
        currentHp = 0;
        isDead = true;
    } else
        currentHp -= damage;
}

int Player::GetCurrentHp() const{
    return currentHp;
}
int Player::GetMaxHp() const{
    return maxHp;
}

Rectangle Player::GetAttackHitbox() const {
    Vector2 attackCenter = GetPosition() + aimDirection*(hitBox.width/ 2.0f + attackSize.x / 2.0f);
    Rectangle attackRect {attackCenter.x - attackSize.x/ 2.0f, 
                    attackCenter.y - attackSize.y/ 2.0f,
                    attackSize.x,
                    attackSize.y};
    return attackRect;
}

void Player::DrawAttackHitbox() const {
    switch (state) {
    case State::Idle:
        DrawRectangleRec(GetAttackHitbox(), GRAY);
        break;
    case State::Recovery:
        DrawRectangleRec(GetAttackHitbox(), GREEN);
        break;
    default:
        break;
    }
    
}

void Player::setAimDirectionMouse() {
    Vector2 mousePos = GetMousePosition();
    aimDirection = Vector2Normalize(mousePos - GetPosition());
}

bool Player::ConsumeAttack() {
    // if attacked this frames, sets the flag to true and returns true, else, it'll return true
    if (attackedThisFrame) {
        attackedThisFrame = false;
        return true;
    }
    return false;
}

void Player::Reset() {
    currentHp = maxHp;
    Vector2 direction {0,0};
    Vector2 aimDirection {0,0};
    bool isDead = false;
}