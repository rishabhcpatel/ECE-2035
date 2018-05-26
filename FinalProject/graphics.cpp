#include "graphics.h"

#include "globals.h"


#define ALIEN_HEIGHT 8
#define ALIEN_WIDTH 11
#define X 0x00FF00 // Green
#define _ 0x000000
#define B 0x0000FF 
#define G 0x008000
#define N 0x7F6000
#define R 0xFF0000
#define W 0x9900FF // purple
#define C 0x61A6B5 // cyan
#define Y 0xFFDC15 // yellow-gold
#define S 0x4D8AC0 //Sword Blade
#define H 0xD78484 //Sword Handle

#define L 0x7F6000 // Wall color


int alienBobDown_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
 _,_,X,_,_,_,_,_,X,_,_,
 _,_,_,X,_,_,_,X,_,_,_,
 _,_,X,X,X,X,X,X,X,_,_,
 _,X,X,_,X,X,X,_,X,X,_,
 X,X,X,X,X,X,X,X,X,X,X,
 X,_,X,X,X,X,X,X,X,_,X,
 X,_,X,_,_,_,_,_,X,_,X,
 _,_,_,X,X,_,X,X,_,_,_
};

int character_sprite[11 * 11] = {
 _,_,_,_,R,R,R,_,_,_,_,
 _,_,_,R,R,R,R,R,_,_,_,
 _,_,_,R,R,R,R,R,_,_,_,
 _,_,_,_,R,R,R,_,_,_,_,
 _,_,_,_,_,R,_,_,_,_,_,
 _,_,_,R,R,R,R,R,_,_,_,
 _,_,_,R,R,R,R,R,_,_,_,
 _,_,_,R,R,R,R,R,_,_,_,
 _,_,_,_,R,R,R,_,_,_,_,
 _,_,_,_,R,R,R,_,_,_,_,
 _,_,_,_,R,R,R,_,_,_,_,  

};

int NPCcharacter_sprite[11 * 11] = {
 _,_,_,_,C,C,C,_,_,_,_,
 _,_,_,C,C,C,C,C,_,_,_,
 _,_,_,C,C,C,C,C,_,_,_,
 _,_,_,_,C,C,C,_,_,_,_,
 _,_,_,_,_,C,_,_,_,_,_,
 _,_,_,C,C,C,C,C,_,_,_,
 _,_,_,C,C,C,C,C,_,_,_,
 _,_,_,C,C,C,C,C,_,_,_,
 _,_,_,_,C,C,C,_,_,_,_,
 _,_,_,_,C,C,C,_,_,_,_,
 _,_,_,_,C,C,C,_,_,_,_,   

};

int plant_sprite[11 * 11] = {
 _,_,G,G,G,G,G,G,G,_,_,
 _,G,G,G,G,G,G,G,G,G,_,
 G,G,G,G,G,G,G,G,G,G,G,
 G,G,G,G,G,G,G,G,G,G,G,
 _,G,G,G,G,G,G,G,G,G,_,
 _,_,G,G,G,G,G,G,G,G,_,
 _,_,_,_,N,N,N,_,_,_,_,
 _,_,_,_,N,N,N,_,N,N,_,
 _,N,N,N,N,N,N,N,N,N,_,
 _,N,N,_,N,N,N,_,_,_,_,
 _,_,_,_,N,N,N,_,_,_,_,
};

int empty_sprite[11 * 11] = {
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
};

int npc1_sprite[11 * 11] = {
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,R,R,R,R,R,R,R,_,_,
 _,R,R,R,R,R,R,R,R,R,_,
 R,R,R,_,_,_,_,_,R,R,R,
 _,R,R,_,_,_,_,_,R,R,_,
 _,R,R,R,R,R,R,R,R,R,_,
 _,_,R,R,R,R,R,R,R,_,_,
 _,_,_,R,R,R,R,R,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
};

int npc2_sprite[11 * 11] = {
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,
 _,_,W,W,W,W,W,W,W,_,_,
 _,W,W,W,W,W,W,W,W,W,_,
 W,W,W,_,_,_,_,_,W,W,W,
 _,W,W,_,_,_,_,_,W,W,_,
 _,W,W,W,W,W,W,W,W,W,_,
 _,_,W,W,W,W,W,W,W,_,_,
 _,_,_,W,W,W,W,W,_,_,_,
 _,_,_,_,_,_,_,_,_,_,_,  
};

int key_sprite[11 * 11] = {
 _,_,_,_,_,_,_,_,Y,Y,_,
 _,_,_,_,_,_,_,Y,Y,Y,Y,
 _,_,_,_,_,_,Y,Y,_,_,_,
 _,_,_,_,_,Y,Y,Y,_,_,_,
 _,_,_,_,Y,Y,_,Y,Y,_,_,
 _,_,_,Y,Y,Y,_,_,_,_,_,
 _,Y,Y,Y,_,Y,Y,_,_,_,_,
 _,_,_,Y,_,_,_,_,_,_,_,
 Y,_,_,Y,_,_,_,_,_,_,_,
 _,Y,Y,_,_,_,_,_,_,_,_,  
};

int sword_sprite[11 * 11] = {
 _,_,_,_,_,S,_,_,_,_,_,
 _,_,_,_,S,S,S,_,_,_,_,
 _,_,_,_,S,S,S,_,_,_,_,
 _,_,_,_,S,S,S,_,_,_,_,
 _,_,_,_,S,S,S,_,_,_,_,
 _,_,_,_,S,S,S,_,_,_,_,
 _,_,_,_,S,S,S,_,_,_,_,
 _,_,_,_,S,S,S,_,_,_,_,
 _,_,_,_,H,H,H,_,_,_,_,
 _,_,H,H,H,H,H,H,H,_,_,
 _,_,_,_,_,H,_,_,_,_,_,
};

int characterSword_sprite[11 * 11] = {
 _,R,R,R,_,_,_,S,_,_,_,
 R,R,R,R,R,_,S,S,S,_,_,
 R,R,R,R,R,_,S,S,S,_,_,
 _,R,R,R,_,_,S,S,S,_,_,
 _,_,R,_,_,_,S,S,S,_,_,
 R,R,R,R,R,_,S,S,S,_,_,
 R,R,R,R,R,R,R,R,R,H,_,
 R,R,R,R,R,_,_,H,_,_,_,
 _,R,R,R,_,_,_,H,_,_,_,
 _,R,R,R,_,_,_,_,_,_,_,
 _,R,R,R,_,_,_,_,_,_,_,
 };

int characterKey_sprite[11 * 11] = {
 _,R,R,R,_,_,_,_,Y,Y,_,
 R,R,R,R,R,_,_,_,Y,_,_,
 R,R,R,R,R,_,_,_,Y,Y,Y,
 _,R,R,R,_,_,_,_,Y,_,_,
 _,_,R,_,_,_,_,_,Y,Y,Y,
 R,R,R,R,R,_,_,_,Y,_,_,
 R,R,R,R,R,R,R,R,R,R,_,
 R,R,R,R,R,_,_,_,Y,_,_,
 _,R,R,R,_,_,_,Y,_,Y,_,
 _,R,R,R,_,_,_,Y,_,Y,_,
 _,R,R,R,_,_,_,_,Y,_,_,
 };
 
 int gateL_sprite[11 * 11] = {
 _,_,_,L,L,L,L,L,L,L,L,
 _,L,L,L,L,L,L,L,L,L,L,
 _,L,L,L,L,L,L,L,L,L,L,
 L,L,L,L,L,L,L,L,L,L,L,
 L,L,L,L,L,L,_,_,_,_,_,
 L,L,L,L,L,L,_,_,_,_,_,
 L,L,L,L,L,L,_,_,_,_,_,
 L,L,L,L,L,L,_,_,_,_,_,
 L,L,L,L,L,L,_,_,_,_,_,
 L,L,L,L,L,L,_,_,_,_,_,
 L,L,L,L,L,L,_,_,_,_,_,
};

int gateR_sprite[11 * 11] = {
 L,L,L,L,L,L,L,L,_,_,_,
 L,L,L,L,L,L,L,L,L,L,_,
 L,L,L,L,L,L,L,L,L,L,_,
 L,L,L,L,L,L,L,L,L,L,L,
 _,_,_,_,_,L,L,L,L,L,L,
 _,_,_,_,_,L,L,L,L,L,L,
 _,_,_,_,_,L,L,L,L,L,L,
 _,_,_,_,_,L,L,L,L,L,L,
 _,_,_,_,_,L,L,L,L,L,L,
 _,_,_,_,_,L,L,L,L,L,L,
 _,_,_,_,_,L,L,L,L,L,L,
};

int entrance_sprite[11 * 11] = {
 _,_,_,_,_,_,_,_,_,L,L,
 _,_,_,_,_,_,_,_,L,L,L,
 _,_,_,_,_,_,_,L,L,L,L,
 _,_,_,_,_,_,L,L,L,_,_,
 _,_,_,_,_,L,L,L,_,_,_,
 _,_,_,_,L,L,L,_,_,_,_,
 _,_,_,L,L,L,_,_,_,_,_,
 _,_,L,L,L,_,_,_,_,_,_,
 _,L,L,L,_,_,_,_,_,_,_,
 L,L,L,_,_,_,_,_,_,_,_,
 L,L,_,_,_,_,_,_,_,_,_,
};

int cannabis_sprite[11 * 11] = {
 _,_,X,_,_,_,_,_,_,_,_,
 X,_,X,_,X,_,_,_,X,_,_,
 _,X,X,X,_,_,X,_,X,_,X,
 _,_,X,_,_,_,_,X,X,X,_,
 _,_,_,_,_,_,_,_,X,_,_,
 _,_,_,X,_,_,_,_,_,_,_,
 _,X,_,X,_,X,_,_,_,X,_,
 _,_,X,X,X,_,_,X,_,X,_,
 _,_,_,X,_,_,_,_,X,X,X,
 _,_,_,_,_,_,_,_,_,X,_,
 _,_,_,_,_,_,_,_,_,_,_,
};

int weed_sprite[11 * 11] = {
 _,X,_,X,_,N,_,X,_,X,_,
 _,_,_,_,X,N,X,_,_,_,_,
 _,_,X,_,_,N,_,_,X,_,_,
 X,_,_,_,_,N,_,_,_,_,X,
 _,X,_,X,_,N,_,X,_,X,_,
 _,_,X,_,_,N,_,_,X,_,_,
 X,_,_,_,N,N,N,_,_,_,X,
 _,_,X,_,_,N,_,_,X,_,_,
 X,_,_,X,_,N,_,X,_,_,X,
 _,_,X,_,N,N,N,_,X,_,_,
 _,X,_,X,_,N,_,X,_,X,_,
};


void draw_player(int u, int v, int key)
{
    //uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    uLCD.BLIT(u,v, 11, 11, character_sprite);
}

void draw_player2(int u, int v, int key)
{
    //uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    uLCD.BLIT(u,v, 11, 11, characterSword_sprite);
}

void draw_player3(int u, int v, int key)
{
    //uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    uLCD.BLIT(u,v, 11, 11, characterKey_sprite);
}

void draw_player4(int u, int v, int key)
{
    //uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    uLCD.BLIT(u,v, 11, 11, empty_sprite);
}

void draw_bowl(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, npc1_sprite);
}

void draw_bowl2(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, npc2_sprite);
}

void draw_npc2(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, NPCcharacter_sprite);
}

void draw_key(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, key_sprite);
}

void draw_sword(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, sword_sprite);
}

void draw_empty(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, empty_sprite);
}

void draw_gateL(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, gateL_sprite);
}

void draw_gateR(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, gateR_sprite);
}

void draw_entrance(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, entrance_sprite);
}

void draw_weed(int u, int v)
{
    uLCD.BLIT(u,v, 11, 11, weed_sprite);
}


#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define DIRT   BROWN
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    //uLCD.filled_rectangle(u, v, u+10, v+10, BLACK); //BLACK -------------------------------------------
    uLCD.BLIT(u,v, 11, 11, cannabis_sprite);
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN); //BROWN
}

void draw_plant(int u, int v)
{
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
    uLCD.BLIT(u,v, 11, 11, plant_sprite);
}

void draw_upper_status()
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 127, 9, GREEN);
    
    // Add other status info drawing code here
    uLCD.line(0, 8, 127, 8, YELLOW);
}

void draw_lower_status()
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);
    
    // Add other status info drawing code here
    uLCD.line(0, 119, 127, 119, YELLOW);
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}