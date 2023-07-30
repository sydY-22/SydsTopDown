#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int window_width = 384;
    const int window_height = 384;
    InitWindow(window_width, window_height, "Syd's Top-Down!");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    // intance of the Character class
    Character knight(window_width, window_height);

    // enemy variables
    Vector2 enemyPos = {800.f, 300.f}; // window width and window height
    Texture2D idle_enemy = LoadTexture("characters/goblin_idle_spritesheet.png");
    Texture2D run_enemy = LoadTexture("characters/goblin_run_spritesheet.png");

    // instance of the Enemy class
    Enemy goblin(enemyPos, idle_enemy, run_enemy);

    // slime variables
    Vector2 slimePos = {500.f, 700.f};
    Texture2D idle_slime = LoadTexture("characters/slime_idle_spritesheet.png");
    Texture2D run_slime = LoadTexture("characters/slime_run_spritesheet.png");

    // instance of the Enemy class.
    Enemy slime{
        slimePos,
        idle_slime,
        run_slime};

    // Enemy *enemies[]{
    //     &goblin,
    //     &slime
    // };

    // create an array of enemies.
    Enemy* enemies[]{
        new Enemy{Vector2{(32 * 24), (32 * 24)},idle_enemy,run_enemy},
        new Enemy{Vector2{(32 * 50), (32 * 50)},idle_slime,run_slime},
        new Enemy{Vector2{(32 * 1), (32 * 35)},idle_enemy,run_enemy},
        new Enemy{Vector2{(32 * 75), (32 * 90)},idle_slime,run_slime},
        new Enemy{Vector2{(32 * 90), (32 * 40)},idle_enemy,run_enemy}
    };

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }


    // load the prop textures
    // Prop props[2]{
    //     Prop{Vector2{600.f, 350.f}, LoadTexture("TextureFantasyTopDown/TX Plant.png")},
    //     Prop{Vector2{200.f, 450.f}, LoadTexture("TextureFantasyTopDown/TX Plant.png")}
    // };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // -1.f before change
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        // draw the props
        // for(auto prop : props)
        // {
        //     prop.Render(knight.getWorldPos());
        // }

        if (!knight.getAlive()) // character is not alive.
        {
            DrawText("GAME OVER!", 55.f, 45.f, 40, RED); // display game over.
            EndDrawing();
            continue;
        }
        else // character is alive.
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED); // display character health.
        }

        // update character animation frames.
        knight.tick(GetFrameTime());

        // check map bounds.
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + window_width > map.width * mapScale ||
            knight.getWorldPos().y + window_height > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // for(auto prop : props)
        // {
        //    if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
        //    {
        //         knight.undoMovement();
        //    }
        // }

        // update enemy animation frames.
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // check for collision with weapon.
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);

                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    // deallocate memory.
    for (auto enemy : enemies)
    {
        delete enemy;
    }
}