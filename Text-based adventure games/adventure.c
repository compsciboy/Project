#include "rooms.h"
#include <ctype.h>

int win=0;
bool omens =false;
#define MAX 20

int main()
{
    /*print out the instructions for the game */
    printf("Your mission is to explore rooms and come back to the starting room with at least 2 items and 1 omen\n");
    printf("noted that there are 9 rooms including the starting room, and if you want to explore a new room but there is no available room, you lose\n\n");
    /*initialize a linked list of room with struct room*/
    struct Room* p1=room("", "", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    pile(p1);
    /*initialize a linked list of command with struct key*/
    struct Key* k1=key("look", "See the items in the room and rooms in each direction", NULL);
    init_key(k1);
    print_key(k1);
    struct Room* curR=starting_room();
    /*initialize a linked list of item as inventory*/
    struct Item* inventory =item("", "", NULL);
    print_room(curR);
    
    while(!win){
    char buf[MAX];
    /*take the user input*/
    fgets(buf, MAX, stdin);
    printf("\n");
    for(int i = 0; buf[i]; i++){
        buf[i] = tolower(buf[i]);
    }
    if(strncmp(buf, "go", 2)==0){
            char* direction=buf+3;
            /*can not go south*/
            if(strncmp(direction, "south", 5)==0){
                printf("You can not go south");
            }
            /*invaild direction*/
            else if(strncmp(direction, "north", 5)!=0 && 
            strncmp(direction, "west", 4)!=0 && strncmp(direction, "east", 4)!=0 &&
            strncmp(direction, "up", 2)!=0 && strncmp(direction, "down", 4)!=0){
                printf("No such direction");
            }
            else{
                /*called function move, which return the correct room to go to*/
                curR=move(curR, direction, p1);
                if(omens==false){
                    omens=isOmen(curR);
                }
                print_room(curR);
            }
    }
    else if(strncmp(buf, "look", 4)==0){
        /*called funciton look to print out the items in the room and rooms in each direction*/
        look(curR->items->next, curR);
    }
    else if(strncmp(buf, "inventory", 9)==0){
        if(inventory->next==NULL){
            printf("You're not carrying anything\n");
        }
        else{
            /*print out inventory*/
            inv_print(inventory->next);
        }
    }
    else if(strncmp(buf, "take", 4)==0){
        if(curR->items->next==NULL){
            printf("No item in this room\n");
        }
        else{
            char* items=buf+5;
            /*remove an item from the item list of the room and add it to the iventory*/
            acq_item(curR, inventory, items);
        }
    }
    else if(strncmp(buf, "drop", 4)==0){
        if(inventory->next==NULL){
            printf("You're not carrying anything\n");
        }
        else{
            char* items=buf+5;
            /*remove an item from the inventory and add it to the item list of the room*/
            drop_item(inventory, curR, items);
        }
    }
    else{
        printf("Invaild command\n");
    }
    if(strncmp(curR->name, "sr", 2)==0 && sizeOf(inventory->next)>=2 && omens==true){
        /*deallocate memory*/
        room_free(curR);
        item_free(inventory);
        key_free(k1);
        printf("You win");
        /*close the program*/
        exit(0);
    }
    }
}