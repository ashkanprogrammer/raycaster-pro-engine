#include <stdio.h>
#include <math.h>
#include "raylib.h"

typedef struct{
    float x;
    float y;
}Vector;

typedef struct{
    Vector pos;
    Vector dir;
    Vector plane;
}Player;

int main() {
    InitWindow(1200, 900, "Hello Raylib!");
    Color cb1 = {0, 50, 250, 80};
    Color cr1 = {180, 0, 0, 255};
    Player player;
    float mini_posx = 1075.0f;
    float mini_posy = 225.0f;
    player.pos.x = 600.0f;
    player.pos.y = 450.0f;
    player.dir.x = 1.0f;
    player.dir.y = 0.0f;
    player.plane.x = 0.0f;
    player.plane.y = 0.66f;
    float angle = 0;
    SetTargetFPS(60);

    int map[15][15]; 
    const int TILE_SIZE = 54;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(i == 0 || i == 14 || j == 0 || j == 14)
                map[i][j] = 1;
            else map[i][j] = 0;
        }
    }

    int u = 45, v = 195, game_state = 0;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        float base_move_speed = 150.0f;
        float base_rot_speed = 5.0f;
        float move_speed = base_move_speed * dt;
        float rot_speed = base_rot_speed * dt;
        if(IsKeyPressed(KEY_M)){
            if(game_state == 0) 
                game_state = 1;
            else game_state = 0;
        }
        if(game_state == 0){
            if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
                int a = GetMouseX();
                int b = GetMouseY();
                if(a >= 195 && a <= 1005 && b >= 45 && b <= 855){
                    a = (a - v)/(TILE_SIZE);
                    b = (b - u)/(TILE_SIZE);
                    map[b][a] = 0;
                }
            }
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                int a = GetMouseX();
                int b = GetMouseY();
                int px = (player.pos.x - v)/(TILE_SIZE);
                int py = (player.pos.y - u)/(TILE_SIZE);
                if(a >= 195 && a <= 1005 && b >= 45 && b <= 855){
                    a = (a - v)/(TILE_SIZE);
                    b = (b - u)/(TILE_SIZE);
                    if(a != px || b != py) map[b][a] = 1;
                }
            }
        }
        if(IsKeyPressed(KEY_F5)){
            FILE *fp = fopen("info.txt", "w");
            fprintf(fp, "%f %f", player.pos.x, player.pos.y);
            fprintf(fp, "\n");
            fprintf(fp, "%f %f", mini_posx, mini_posy);
            fprintf(fp, "\n");
            fprintf(fp, "%f %f", player.dir.x, player.dir.y);
            fprintf(fp, "\n");
            fprintf(fp, "%f %f", player.plane.x, player.plane.y);
            fprintf(fp, "\n");
            for(int i = 0; i < 15; i++){
                for(int j = 0; j < 15; j++)
                    fprintf(fp, "%d ", map[i][j]);
                fprintf(fp, "\n");
            }
        }
        if(IsKeyPressed(KEY_F9)){
            FILE *fp = fopen("info.txt", "r");
            fscanf(fp, "%f %f", &player.pos.x, &player.pos.y);
            fscanf(fp, "%f %f", &mini_posx, &mini_posy);
            fscanf(fp, "%f %f", &player.dir.x, &player.dir.y);
            fscanf(fp, "%f %f", &player.plane.x, &player.plane.y);
            for(int i = 0; i < 15; i++)
                for(int j = 0; j < 15; j++)
                    fscanf(fp, "%d", &map[i][j]);
        }
        if(IsKeyDown(KEY_W)){
            float newx = player.pos.x + (player.dir.x * move_speed);
            float newy = player.pos.y + (player.dir.y * move_speed);
            int newa = (newx - v)/(TILE_SIZE);
            int newb = (newy - u)/(TILE_SIZE);
            int a = (player.pos.x - v)/(TILE_SIZE);
            int b = (player.pos.y - u)/(TILE_SIZE);
            if(map[b][newa] == 0){
                player.pos.x = newx;
                mini_posx = mini_posx + (player.dir.x * move_speed) / 6.0f;
            }
            if(map[newb][a] == 0){
                player.pos.y = newy;
                mini_posy = mini_posy + (player.dir.y * move_speed) / 6.0f;
            }
        }
        if(IsKeyDown(KEY_S)){
            float newx = player.pos.x - (player.dir.x * move_speed);
            float newy = player.pos.y - (player.dir.y * move_speed);
            int newa = (newx - v)/(TILE_SIZE);
            int newb = (newy - u)/(TILE_SIZE);
            int a = (player.pos.x - v)/(TILE_SIZE);
            int b = (player.pos.y - u)/(TILE_SIZE);
            if(map[b][newa] == 0){
                player.pos.x = newx;
                mini_posx = mini_posx - (player.dir.x * move_speed) / 6.0f;
            }
            if(map[newb][a] == 0){
                player.pos.y = newy;
                mini_posy = mini_posy - (player.dir.y * move_speed) / 6.0f;
            }
        }
        if(IsKeyDown(KEY_A)){
            float newx = player.pos.x + (player.dir.y * move_speed);
            float newy = player.pos.y - (player.dir.x * move_speed);
            int newa = (newx - v)/(TILE_SIZE);
            int newb = (newy - u)/(TILE_SIZE);
            int a = (player.pos.x - v)/(TILE_SIZE);
            int b = (player.pos.y - u)/(TILE_SIZE);
            if(map[b][newa] == 0){
                player.pos.x = newx;
                mini_posx = mini_posx + (player.dir.y * move_speed) / 6.0f;
            }
            if(map[newb][a] == 0){
                player.pos.y = newy;
                mini_posy = mini_posy - (player.dir.x * move_speed) / 6.0f;
            }
        }
        if(IsKeyDown(KEY_D)){
            float newx = player.pos.x - (player.dir.y * move_speed);
            float newy = player.pos.y + (player.dir.x * move_speed);
            int newa = (newx - v)/(TILE_SIZE);
            int newb = (newy - u)/(TILE_SIZE);
            int a = (player.pos.x - v)/(TILE_SIZE);
            int b = (player.pos.y - u)/(TILE_SIZE);
            if(map[b][newa] == 0){
                player.pos.x = newx;
                mini_posx = mini_posx - (player.dir.y * move_speed) / 6.0f;
            }
            if(map[newb][a] == 0){
                player.pos.y = newy;
                mini_posy = mini_posy + (player.dir.x * move_speed) / 6.0f;
            }
        }
        if(IsKeyDown(KEY_RIGHT)){
            float pdx = player.dir.x;
            float pdy = player.dir.y;
            float ppx = player.plane.x;
            float ppy = player.plane.y;
            player.dir.x = pdx * cos(rot_speed) - pdy * sin(rot_speed);
            player.dir.y = pdx * sin(rot_speed) + pdy * cos(rot_speed);
            player.plane.x = ppx * cos(rot_speed) - ppy * sin(rot_speed);
            player.plane.y = ppx * sin(rot_speed) + ppy * cos(rot_speed);
        }
        if(IsKeyDown(KEY_LEFT)){
            float pdx = player.dir.x;
            float pdy = player.dir.y;
            float ppx = player.plane.x;
            float ppy = player.plane.y;
            player.dir.x = pdx * cos(rot_speed) + pdy * sin(rot_speed);
            player.dir.y = pdy * cos(rot_speed) - pdx * sin(rot_speed);
            player.plane.x = ppx * cos(rot_speed) + ppy * sin(rot_speed);
            player.plane.y = ppy * cos(rot_speed) - ppx * sin(rot_speed);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        if(game_state == 0){
            for(int i = 0; i < 15; i++){
                for(int j = 0; j < 15; j++){
                    if(map[j][i] == 0) DrawRectangle(v + i * TILE_SIZE, u + j * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
                    else DrawRectangle(v + i * TILE_SIZE, u + j * TILE_SIZE, TILE_SIZE, TILE_SIZE, cb1);
                    DrawRectangleLines(v + i * TILE_SIZE, u + j * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                }
            }
            float xe = 60.0f * player.dir.x;
            float ye = 60.0f * player.dir.y;
            DrawCircle(player.pos.x, player.pos.y, 18, cr1);
            DrawLine(player.pos.x, player.pos.y, player.pos.x + xe, player.pos.y + ye, cr1);
            DrawText("Save map(F5)", 195, 15, 20, WHITE);
            DrawText("Reload map(F9)", 855, 15, 20, WHITE);
        }
        else{
            double screen_width = 1200.0f;
            double screen_height = 900.0f;
            for(int x = 0; x < 1200; x++){
                double cameraX = (2 * ((double)x / screen_width)) - 1.0f;
                double raydirX = player.dir.x + player.plane.x * cameraX;
                double raydirY = player.dir.y + player.plane.y * cameraX;
                int mapX = (player.pos.x - v)/(TILE_SIZE);
                int mapY = (player.pos.y - u)/(TILE_SIZE);
                double posX = (player.pos.x - v)/(double)(TILE_SIZE);
                double posY = (player.pos.y - u)/(double)(TILE_SIZE);
                double sidedistX, sidedistY;
                double deltadistX = (raydirX == 0) ? 1e30 : fabs(1 / raydirX);
                double deltadistY = (raydirY == 0) ? 1e30 : fabs(1 / raydirY);
                double perpWallDist;
                int stepX, stepY;
                int hit = 0, side;
                if (raydirX < 0){
                    sidedistX = (posX - mapX) * deltadistX;
                    stepX = -1;
                }
                else{
                    sidedistX = (mapX + 1.0 - posX) * deltadistX;
                    stepX = 1;
                }
                if (raydirY < 0){
                    sidedistY = (posY - mapY) * deltadistY;
                    stepY = -1;
                }
                else{
                    sidedistY = (mapY + 1.0 - posY) * deltadistY;
                    stepY = 1;
                }
                while (hit == 0){
                    if (sidedistX < sidedistY){
                        sidedistX += deltadistX;
                        mapX += stepX;
                        side = 0;
                    }
                    else{
                        sidedistY += deltadistY;
                        mapY += stepY;
                        side = 1;
                    }
                    if (map[mapY][mapX] == 1) hit = 1;
                }
                if (side == 0){
                    perpWallDist = sidedistX - deltadistX;
                    int lineHeight = (screen_height / perpWallDist);
                    int drawStart = (screen_height / 2) - (lineHeight / 2);
                    int drawEnd = (screen_height / 2) + (lineHeight / 2);
                    if(drawStart < 0) drawStart = 0;
                    if(drawEnd >= screen_height) drawEnd = screen_height - 1;
                    DrawLine(x, 0, x, drawStart, SKYBLUE);
                    DrawLine(x, drawStart, x, drawEnd, GRAY);
                    DrawLine(x, drawEnd, x, screen_height, cb1);
                }
                else{
                    perpWallDist = sidedistY - deltadistY;
                    int lineHeight = (screen_height / perpWallDist);
                    int drawStart = (screen_height / 2) - (lineHeight / 2);
                    int drawEnd = (screen_height / 2) + (lineHeight / 2);
                    if(drawStart < 0) drawStart = 0;
                    if(drawEnd >= screen_height) drawEnd = screen_height - 1;
                    DrawLine(x, 0, x, drawStart, SKYBLUE);
                    DrawLine(x, drawStart, x, drawEnd, DARKGRAY);
                    DrawLine(x, drawEnd, x, screen_height, cb1);
                }
            }
            const int MINI_TILE = 10;
            int mu = 150, mv = 1000;
            for(int i = 0; i < 15; i++){
                for(int j = 0; j < 15; j++){
                    if(map[j][i] == 0) DrawRectangle(mv + i * MINI_TILE, mu + j * MINI_TILE, MINI_TILE, MINI_TILE, WHITE);
                    else DrawRectangle(mv + i * MINI_TILE, mu + j * MINI_TILE, MINI_TILE, MINI_TILE, cb1);
                    DrawRectangleLines(mv + i * MINI_TILE, mu + j * MINI_TILE, MINI_TILE, MINI_TILE, DARKGRAY);
                }
            }
            float xe = 10.0f * player.dir.x;
            float ye = 10.0f * player.dir.y;
            DrawCircle(mini_posx, mini_posy, 4, cr1);
            DrawLine(mini_posx, mini_posy, mini_posx + xe, mini_posy + ye, cr1);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}