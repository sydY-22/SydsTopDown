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
    if (!getAlive()) return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);

    // deals damage to character.
    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
    

}

void Enemy::setTarget(Character* gob)
{
    target = gob;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
