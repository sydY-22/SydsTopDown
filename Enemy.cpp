#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    running = run_texture;
    width = texture.width/maxFrames;
    height = texture.height;
    speed = 2.5f;
}

void Enemy::tick(float deltaTime)
{
    // Get toTarget()
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    // Vector2Normalize toTarget() to length of 1
    toTarget = Vector2Normalize(toTarget);
    // Vector2Scale toTarget() * speed
    toTarget = Vector2Scale(toTarget, speed);
    // Set Enemy worldPos (move enemy to character)
    worldPos = Vector2Add(worldPos, toTarget);

    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(deltaTime);

}

void Enemy::setTarget(Character* gob)
{
    target = gob;
}
