#include "raylib.h"
#include "raymath.h"

int main() 
{
    const int window_width = 384;
    const int window_height = 384;
    InitWindow(window_width, window_height, "Syd's Top-Down!");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    // load knight character
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)window_width / 2.0f - 4.0f *(0.5f*(float)knight.width/6.0f), 
        (float)window_height/2.0f - 4.0f*(0.5f*(float)knight.height)
        };
   

    float speed{4.0};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if(IsKeyDown(KEY_A))  direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;
        
        if(Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            
        }
       // draw the map
        DrawTextureEx(map, mapPos, 0, 4.0, WHITE);

        // draw knight character
        Rectangle source{0.f, 0.f, (float)knight.width/6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f*(float)knight.width/6.0f, 4.0f*(float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
    UnloadTexture(knight);
    CloseWindow();

}