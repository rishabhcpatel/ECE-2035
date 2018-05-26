// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
void init_main_map2 ();
int main ();


Timer t;

float timeTaken;

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define RESTART 7
#define QUIT 8
//#define OMNI 7

int omni = 0; // set omnipotent mode to 0;

int actionPress = 0; 

int talk1 = 0;

int talk1Finished = 0;

int swordAcquired = 0;

int enemyDefeated = 0; 

int talk2 = 0;

int keyAcquired = 0;

int talk2Finished = 0;

int onTime = 1;

int gameOver = 0;

int quitGame = 0;

int restartGame = 0;

int menuAction = 0;

int map2 = 0;

int lives = 2;

int xPos = 10;

int yPos = 39;

int yInc = 0;

int showMenu = 0;

int performAction = 0;

int breakLoop = 0;

int get_action(GameInputs inputs)
{
    if (inputs.b2 == 0 && inputs.b1 == 1 && inputs.b3 == 1)
    {
        //mySpeaker.PlayNote(1200.0, 0.25, 0.5);
        omni = 1;
        if(menuAction)
        {
            uLCD.printf("b2 pressed");
            restartGame = 1;   
        }
        if(performAction)
        {
            uLCD.cls();
            mySpeaker.PlayNote(1200.0, 0.25, 0.5);
            uLCD.printf("\n\n\n You quit");
            wait(3.0);
            onTime = 0;   
        }
    }
    if (inputs.b2 == 1 && inputs.b1 == 1 && inputs.b3 == 0)
    {
        //mySpeaker.PlayNote(1200.0, 0.25, 0.5);
        if(performAction)
        {
            uLCD.printf("b3 pressed");
            quitGame = 1;   
        }
        showMenu = 1;
        breakLoop = 1;
    }
    if (inputs.b2 == 1 && inputs.b1 == 0 && inputs.b3 == 1)
    {
        omni = 0;
        //Menu
        if(performAction)
        {
            uLCD.cls();
            mySpeaker.PlayNote(1200.0, 0.25, 0.5);
            uLCD.printf("\n\n\n You restarted");
            wait(3.0);
            uLCD.reset();               
        }
        //Bowl1
        if ((Player.x == 17 && (Player.y == 16 || Player.y == 18)) || (Player.y == 17 && (Player.x == 18 || Player.x == 16)) || (Player.y == 18 && (Player.x == 18 || Player.x == 16)) || (Player.y == 16 && (Player.x == 16 || Player.x == 18)))
        {
            //uLCD.locate(0,17);
            //uLCD.printf("Printing Here");
            mySpeaker.PlayNote(1900.0, 0.50, 0.8);
            if(!swordAcquired)
            {             
            char *line1 = "You dont have the ";
            char *line2 = "  KEY!! GO Defeat ";
            speech(line1,line2);
                          
            char *line3 = "  The Enemy  with ";
            char *line4 = "     a sword      ";
            speech(line3,line4);
                          
            char *line5 = " Sword is at 1 38 ";
            char *line6 = "  Get Back to me! ";
            speech(line5,line6);
            }
            talk1 = 1;
            actionPress = 1;   
            if(swordAcquired && !enemyDefeated)
            {                 
                char *line5 = "Its time to find  ";
                char *line6 = " enemy (45,27) and";
                speech(line5,line6);
                
                char *line7 = "defeat him. I will";
                char *line8 = "then show you the ";
                speech(line7,line8);             
                
                char *line9 = "way to the key... ";
                char *line10= "but do this first ";
                speech(line9,line10);   
                              
                char *line1 = "You have 20 Sec to";
                char *line2 = "finish the task GO";
                speech(line1,line2);
                
                t.start();
            }
            if(enemyDefeated)
            {
                char *line5 = "  You did it! I   ";
                char *line6 = "didnt expect that ";
                speech(line5,line6);
                
                char *line7 = "from you at all. I";
                char *line8 = " will you +1 live ";
                speech(line7,line8);    
                ++lives;
                char *line9 = " A different well ";
                char *line10= "has the way to KEY";
                speech(line9,line10);
                
                talk1Finished = 1;
                         
            }
        }
        //Bowl2
        if ((Player.x == 34 && (Player.y == 1 || Player.y == 3)) || (Player.y == 2 && (Player.x == 33 || Player.x == 35)))
        {
            actionPress = 1;   
            mySpeaker.PlayNote(1900.0, 0.50, 0.8);
            if(!talk1Finished && !keyAcquired)
            {
                char *line5 = "  GO do the task  ";
                char *line6 = "  that the first  ";
                speech(line5,line6);
                              
                char *line7 = "well told you to  ";
                char *line8 = "   complete!!     ";
                speech(line7,line8);                   
            }
            if(talk1Finished && !keyAcquired)
            {                  
                char *line5 = "  So you made it  ";
                char *line6 = "  this far in the ";
                speech(line5,line6);
                              
                char *line7 = "quest. You are get";
                char *line8 = "ting close to your";
                speech(line7,line8);
                              
                char *line9 = "destiny. Key is at";
                char *line10= "....... 45  ...  7";
                speech(line9,line10);
                
                talk2 = 1;
            }
            if(keyAcquired)
            {                 
                char *line5 = "Congrats! You are ";
                char *line6 = "almost done   :)  ";
                speech(line5,line6);
                              
                char *line7 = "Use the key to un-";
                char *line8 = "   lock map 2     ";
                speech(line7,line8);
                
                talk2Finished = 1;
                
                map_erase(17,17);               
            }
            if(talk2Finished)
            {
                add_gateL(37,1);
                add_gateR(38,1);   
            }
            
            
        }
        //NPC
        if ((Player.x == 45 && (Player.y == 26 || Player.y == 28)) || (Player.y == 27 && (Player.x == 44 || Player.x == 46)))
        {
            actionPress = 1;   
            
            mySpeaker.PlayNote(1900.0, 0.50, 0.8);
        
            if(!swordAcquired) 
            {                 
                char *line5 = " You Cant Beat me ";
                char *line6 = " without a sword! ";
                speech(line5,line6);
                
            }
            if(swordAcquired)
            {
                t.stop();
                
                timeTaken = t.read();
                
                if(t.read() > 20)
                {                 
                    char *line5 = "  You failed my   ";
                    char *line6 = "   challenge :(   ";
                    speech(line5,line6);
                    onTime = 0;   
                }
                else
                {             
                char *line5 = "Please spare me...";
                char *line6 = "...please         ";
                speech(line5,line6);
                
                map_erase(45,27);
                              
                char *line7 = "You  successfully ";
                char *line8 = "defeated enemy!!!!";
                speech(line7,line8);
                               
                char *line9  = "Go back, the magic";
                char *line10 = "well needs you....";
                speech(line9,line10);
                
                enemyDefeated = 1;
                }
                
            }
            
            
        }
        if(!talk1 && !keyAcquired)
        {                 
            char *line5 = "First Talk to the ";
            char *line6 = "Magic Well (17,17)";
            speech(line5,line6);
        }
        if(talk1)
        {
            add_sword(1,26);   
        }
        //Lives -- 
        if (((Player.x == 1 && (Player.y == 25 || Player.y == 27)) || (Player.x == 2 && ((Player.y == 25 || Player.y == 26) || Player.y == 27))) && talk1)
        {
            //add_sword(1,26);
            char *line5 = " You fell for the ";
            char *line6 = "  trap. You chose ";
            speech(line5,line6);
                
            char *line7 = " the wrong sword  ";
            char *line8 = "   -1 live        ";
            speech(line7,line8); 
                    
            --lives;
        }
        //Sword
        if (((Player.x == 1 && (Player.y == 37 || Player.y == 39)) || (Player.x == 2 && ((Player.y == 37 || Player.y == 38) || Player.y == 38))) && talk1)
        {
            actionPress = 1;
            mySpeaker.PlayNote(1900.0, 0.50, 0.8);
                          
            char *line5 = "  Sword Acquired  ";
            char *line6 = "   Successfully   "; 
            swordAcquired = 1;
            wait(3.0);
            map_erase(1,38);
            speech(line5,line6);  
        }
        if(swordAcquired)
        {
            add_bowl(17,10);
                if( (Player.y == 10 && (Player.x == 16 || Player.x == 18)) || (Player.x == 17 && (Player.y == 9 || Player.y == 11)))
                {
                    char *line5 = "You talked to the ";
                    char *line6 = "   wrong well..   ";
                    speech(line5,line6);
                
                    char *line7 = "   You loose one  ";
                    char *line8 = "       live       ";
                    speech(line7,line8); 
                    
                    --lives;                   
                }   
        }
        if(talk2)
        {
            mySpeaker.PlayNote(900,0.5,0.8);
            add_key(45,7);
        }
        if(keyAcquired)
        {
            map_erase(17,17);
            map_erase(45,7);
        }
        //Key
        if ( ((Player.x == 44 && (Player.y == 6 || Player.y == 7 || Player.y == 8)) || (Player.x == 45 && (Player.y == 6 || Player.y == 7 || Player.y == 8)) || (Player.x == 46 && (Player.y == 6 || Player.y == 7 || Player.y == 8))) && talk1Finished )
        {
            mySpeaker.PlayNote(1900.0, 0.50, 0.8);
            char *line7 = "I hold your desti-";
            char *line8 = "ny use me wisely..";
            speech(line7,line8);
            
            add_empty(45,7);
                          
            char *line5 = "You have the key!!";
            char *line6 = "unlock your future";
            speech(line5,line6);
            
            char *line3 = "Go to the second..";
            char *line4 = "    magic well    ";
            speech(line3,line4); 
            
            keyAcquired = 1;
            
            //map_erase(17,17);
           add_empty(17,17);
            
               
        }
        //Gate
        if((Player.x == 37 && Player.y == 1) || (Player.x == 38 && Player.y == 1))
        {
            gameOver = 1;
            char *line5 = " You unlocked the ";
            char *line6 = " the treasure!!!  ";
            speech(line5,line6);
            map2 = 1;
        }
        //MOVE OBJECT
        if( (Player.x == 10) && (Player.y == 40 + yInc) )
        {
             
            char *line5 = "     You are      ";
            char *line6 = "    moving me     ";
            speech(line5,line6);
            map_erase(xPos,Player.y-1);
            --yInc;
            yPos = yPos-1;                   
        }
        return ACTION_BUTTON;   
    }
    if(((inputs.ax)*(inputs.ax)) > ((inputs.ay)*(inputs.ay)))
    {
        if (inputs.ax < 0)
        {            
            if(inputs.ax < -0.2)
                return GO_UP;
        }
        else if(inputs.ax > 0)        
        {   
            if(inputs.ax > 0.2)
                return GO_DOWN;
        }   
    }
    if(((inputs.ax)*(inputs.ax)) < ((inputs.ay)*(inputs.ay)))
    {
        if (inputs.ay < 0)
        {
            if(inputs.ay < -0.2)
                return GO_LEFT;
        }
        else if(inputs.ay > 0)
        {
            if (inputs.ay > 0.2)
                return GO_RIGHT;
        }
    }                 
    return NO_ACTION;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    uLCD.locate(0,0);
    uLCD.printf("(%i,%i)",Player.x,Player.y);
    
    uLCD.locate(0,15);
    uLCD.printf("Lives: %i",lives);
    //uLCD.filled_rectangle(60,0,128,6,BLACK);
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    MapItem * ptr;
    switch(action)
    {
        case GO_UP:     
            ptr = get_north(Player.x, Player.y);
            if(omni) Player.y--;
            if (ptr->walkable)
                Player.y--;
            break;    
        case GO_LEFT:   
            ptr = get_west(Player.x, Player.y);
            if(omni) Player.x--;
            if (ptr->walkable)
                Player.x--;
            break;            
        case GO_DOWN:   
            ptr = get_south(Player.x, Player.y);
            if(omni) Player.y++;
            if(ptr->walkable)
                Player.y++;
            break;
        case GO_RIGHT:  
            ptr = get_east(Player.x, Player.y);
            if(omni) Player.x++;          
            if(ptr->walkable)
                Player.x++;
            break;
        //Implemented ACTION_BUTTON AND MENU_BUTTON in a different way          
        case ACTION_BUTTON: break;
        case MENU_BUTTON: break;            
        default:        break;
    }
    return FULL_DRAW;
}


/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    
    add_weed(xPos,yPos);
    
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            if((u == 37 && v == 1) || (u == 38 && v == 1))
            {
                mySpeaker.PlayNote(1900.0, 0.50, 0.8);
                draw_gateL(u,v);
                draw_gateR(u,v);   
            }
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                if(!(Player.x == 37 && Player.y == 1) || (Player.x == 38 && Player.y == 1))
                {
                if(!swordAcquired)draw_player(u, v, Player.has_key);
                if(swordAcquired) draw_player2(u, v, Player.has_key);
                if(keyAcquired) draw_player3(u, v, Player.has_key);
                }
                if((Player.x == 37 && Player.y == 1) || (Player.x == 38 && Player.y == 1))
                {
                    if(Player.x == 37 && Player.y == 1)
                    draw_gateL(u,v);
                    if(Player.x == 38 && Player.y == 1)
                    draw_gateR(u,v);                                     
                }
                if(Player.x == 46 && Player.y == 17) draw_entrance(u,v);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }
    
    // Draw status bars    
    draw_upper_status();
    draw_lower_status();
}

//------------------------------------------------------------------------------
void init_main_map2()
{
    // "Random" plants
    Map* map = set_active_map(1);
        
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");

    print_map();
}
//------------------------------------------------------------------------------

//----------------------------------------------------
/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }
    pc.printf("plants\r\n");
        
    pc.printf("Adding walls!\r\n");
    add_wall(25, 0, VERTICAL, 8);
    add_wall(42, 41, VERTICAL, 7);
    add_wall(43, 41, HORIZONTAL, 4);
    add_wall(43, 28, HORIZONTAL, 7);
    add_wall(43, 17, VERTICAL, 11);
    add_wall(25, 7, HORIZONTAL, 8);
    add_wall(44, 17, HORIZONTAL, 2);
    add_wall(47, 17, HORIZONTAL, 2);
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");



    add_bowl(17,17);
    add_bowl2(34,2); // 34,2
    add_npc2(45,27);
    
    add_sword(1,38);    
    
    add_entrance(46,17);
    
    print_map();
}
void startGame()
{
    uLCD.printf("\n\n\n     WELCOME "); 
    uLCD.printf("\n      TO THE ");
    uLCD.printf("\n    Quest Game!");
    uLCD.printf("\n\n    It's Your ");  
    uLCD.printf("\n     turn to ");
    uLCD.printf("\n    complete the");
    uLCD.printf("\n      QUEST!");
    uLCD.printf("\n    GOOD LUCK "); 
    
    wait(5.0);
    uLCD.cls();      
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
 void playMusic()
 {                    
    PwmOut buzzer(p21);
    BusOut led(LED1,LED2,LED3,LED4);    
    float frequency[] = {262,0,262,0,262,0,349,0,523,0,466,0,440,0,392,0,698,0,523,0,466,0,440,0,392,0,698,0,523,0,466,0,440,0,466,0,392,0,/**/};
    float beat[] = {.3,0,.3,0,.3,0,2,0,2,0,.3,0,.3,0,.3,0,2,0,1,0,.3,0,.3,0,.3,0,2,0,1,0,.3,0,.3,0,.3,0,2,0/**/};
    float frequency2[] = {262,0,262,0,294,0,294,0,466,0,440,0,392,0,349,0,349,0,392,0,440,0,392,0,294,0,330,0,523,0,523,0,698,0,622,0,554,0,523,0,466,0,415,0,392,0,349,0,523,0};
    float beat2[] = {.75,0,.25,0,1.5,0,.5,0,.5,0,.5,0,.5,0,.5,0,.3,0,.3,0,.3,0,1,0,.5,0,1,0,.75,0,.25,0,1,0,.5,0,1,0,.5,0,1,0,.5,0,1,0,.5,0,4,0};
 
        for(int i=0; i<= 37;i++)
        {
            buzzer.period(2/(frequency[i]));
            buzzer = 0.5;
            
            wait(0.4*beat[i]); 
            if(beat[i]==0)
            {wait(.05);}
          
        }
        
        for(int i=0; i<= 49;i++)
        {
            buzzer.period(2/(frequency2[i]));
            buzzer = 0.5;
            
            wait(0.4*beat2[i]); 
            if(beat2[i]==0)
            {wait(.05);}
          
        }
}
 
int determineChoice(GameInputs selection)
{
    uLCD.printf("performed this 1");
    if (selection.b2 == 1 && selection.b1 == 1 && selection.b3 == 0)
    {
        quitGame = 1;
        mySpeaker.PlayNote(1900.0, 0.50, 0.8);
        uLCD.printf("performed this 2");
        return QUIT;
            
    }
    if (selection.b2 == 0 && selection.b1 == 1 && selection.b3 == 1)
    {
        restartGame = 1;
        mySpeaker.PlayNote(1900.0, 0.50, 0.8);
        uLCD.printf("performed this 3");
        return RESTART;
    }
} 
 
void displayMenu()
{
    uLCD.cls();
    
    uLCD.printf("\n\n  GAME MENU");
    uLCD.printf("\n\n  --> Restart");
    uLCD.printf("\n\n  --> Quit   ");
    
    GameInputs choice = read_inputs();
    int action1 = determineChoice(choice);
    switch(action1)
    {
        case QUIT:
            break;
        case RESTART:
            uLCD.reset();
            break;
        default:
            break;            
    }
    wait(20); 
} 
 
 
int main()
{
    startGame();
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    // Initialize the maps
    maps_init();
    init_main_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;

    // Initial drawing
    draw_game(1);

    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actuall do the game update:
        // 1. Read inputs        
        // 2. Determine action (get_action)        
        // 3. Update game (update_game)
        // 3b. Check for game over
        // 4. Draw frame (draw_game)
        //uLCD.printf("(%d,%d)",Player.x,Player.y);
        //speech(Player.x,Player.y);
        GameInputs in = read_inputs();
        int action = get_action(in);
        int update = update_game(action);
        draw_game(update);       
        
        if (!onTime || lives == 0)
        {
            uLCD.cls();
            uLCD.printf("\n\n\n   You failed :(");
            uLCD.printf("\n\n\n   GAME OVER");
            
            break;
        }
        if(breakLoop)
        {
            mySpeaker.PlayNote(800,.5,.5);
            break;
        }
        if(gameOver)
        {
            uLCD.cls();
            uLCD.printf("\n\n\n You Successfully");
            uLCD.printf("\n\n\nfinished the quest");
            uLCD.printf("\n\n\n  Congrats!!!!!!");
            playMusic();        
            break;     
        }
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    } //While 2 END
    while(1)
    {
        GameInputs in = read_inputs();
        int action = get_action(in);  
        if(showMenu)
        {
            uLCD.cls();
            uLCD.printf("\n\n      Menu:     ");
            uLCD.printf("\n\n  --> Restart B1");
            uLCD.printf("\n\n  --> Quit    B2  ");
            performAction = 1;
            
        }
        if (!onTime || lives == 0)
        {
            uLCD.cls();
            uLCD.printf("\n\n\n   You failed :(");
            uLCD.printf("\n\n\n   GAME OVER");
            break;
        }
    } //While 2 END
}
