#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "items.h"
#include "keywords.h"

struct Room{
    char* name;
    char* description;
    struct Item* items;
    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
    struct Room* up;
    struct Room* down;
    struct Room* next;
};

struct Room *room(char* name, char *description, struct Item *items, struct Room *north, struct Room *south, struct Room *east, struct Room *west, struct Room *up, struct Room *down, struct Room* next);
void drop_item(struct Item* inv, struct Room* curR, char* name);
void acq_item(struct Room* curR, struct Item* inv, char* name);
void item_acq(struct Item* curR, struct Item* inv, char* name);
void print_room(struct Room* a);
struct Room* starting_room();
struct Room* room1();
struct Room* room2();
struct Room* omen();
struct Room* omen1();
struct Room* event();
struct Room* event1();
void look(struct Item* it, struct Room* head);
bool isOmen(struct Room* curR);
void add_room(struct Room* head, struct Room* input);
void pile(struct Room* head);
struct Room* rand_room(struct Room* head);
void room_free(struct Room* head);
struct Room* move(struct Room* cur, char* dire, struct Room* pile);