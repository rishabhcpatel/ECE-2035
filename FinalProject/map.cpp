#include "map.h"
#include "math.h"
#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};



/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map;
static Map map2;
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y){
    unsigned int num = (0.5*(X+Y)*(X+Y+1))+Y;
    return num;   
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    return key % 10;
}

void maps_init()
{
    // TODO: Implement!    
    // Initialize hash table
    // Set width & height
    if(active_map == 0)
    {
        map.items = createHashTable(map_hash, 10);
        map.w = 50;
        map.h = 50;
    }
    if(active_map == 1)
    {
        map2.items = createHashTable(map_hash, 10);
        map2.w = 50;
        map2.h = 50;
    }   
}

Map* get_active_map()
{
    // There's only one map
    if(active_map == 0)
    {
        return &map;
    }
    if(active_map == 1)
    {
        return &map2;   
    }
}

Map* set_active_map(int m)
{
    active_map = m;
    if(active_map == 0)
    {
        return &map;
    }
    if(active_map == 1)
    {
        return &map2;
    }
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    if(active_map == 0)
    {
        return map.w;
    }
    if(active_map == 1)
    {
        return map2.w;
    }
    
}

int map_height()
{
    if(active_map == 0)
    {
        return map.h;
    }
    if(active_map == 1)
    {
        return map2.h;
    }
}

int map_area()
{
    return ( map_height() ) * ( map_width() );
}

MapItem* get_north(int x, int y)
{
    int xCoor = x;
    int yCoor = y - 1;
    unsigned int num = XY_KEY(xCoor, yCoor);
    if(active_map == 0)
        return (MapItem*)getItem(map.items, num);
    if(active_map == 1)
        return (MapItem*)getItem(map2.items, num);       
     
}

MapItem* get_south(int x, int y)
{
    int xCoor = x;
    int yCoor = y + 1;
    unsigned int num = XY_KEY(xCoor, yCoor);
    if(active_map == 0)
        return (MapItem*)getItem(map.items, num);
    if(active_map == 1)
        return (MapItem*)getItem(map2.items, num);    
}

MapItem* get_east(int x, int y)
{
    int xCoor = x + 1;
    int yCoor = y;
    unsigned int num = XY_KEY(xCoor, yCoor);
    if(active_map == 0)
        return (MapItem*)getItem(map.items, num);
    if(active_map == 1)
        return (MapItem*)getItem(map2.items, num);
}

MapItem* get_west(int x, int y)
{
    int xCoor = x - 1;
    int yCoor = y;
    unsigned int num = XY_KEY(xCoor, yCoor);
    if(active_map == 0)
        return (MapItem*)getItem(map.items, num);
    if(active_map == 1)
        return (MapItem*)getItem(map2.items, num);
}

MapItem* get_here(int x, int y)
{
    unsigned int num = XY_KEY(x, y);
    if(active_map == 0)
        return (MapItem*)getItem(map.items, num);
    if(active_map == 1)
        return (MapItem*)getItem(map2.items, num);
}


void map_erase(int x, int y)
{
    unsigned int num = XY_KEY(x,y);
    if(active_map == 0)
        deleteItem(map.items,num);
    if(active_map == 1)
        deleteItem(map2.items,num);
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_bowl(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = BOWL;
    w1->draw = draw_bowl;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_bowl2(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = BOWL2;
    w1->draw = draw_bowl2;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_npc2(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = NPC2;
    w1->draw = draw_npc2;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_key(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = KEY;
    w1->draw = draw_key;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_sword(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SWORD;
    w1->draw = draw_sword;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_empty(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = EMPTY;
    w1->draw = draw_empty;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_gateL(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GATEL;
    w1->draw = draw_gateL;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_gateR(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GATER;
    w1->draw = draw_gateR;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_entrance(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = ENTRANCE;
    w1->draw = draw_entrance;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_weed(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WEED;
    w1->draw = draw_weed;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}