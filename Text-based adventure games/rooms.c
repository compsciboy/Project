#include "rooms.h"

/*create a struct room*/
struct Room *room(char* name, char *description, struct Item *items, struct Room *north, struct Room *south, struct Room *east, struct Room *west, struct Room *up, struct Room *down, struct Room* next){
    struct Room *out=(struct Room*) malloc(sizeof(struct Room));
    out->name=name;
    out->description= description;
    out->items=items;
    out->north=north;
    out->south=south;
    out->east=east;
    out->west=west;
    out->up=up;
    out->down=down;
    out->next=next;
    return out;
}

/*set the north direction of a room to a given room*/
void room_exit_north(struct Room* current, struct Room* other){
    current->north=other;
    other->south=current;
    other->next=current;
}

/*set the south direction of a room to a given room*/
void room_exit_south(struct Room* current, struct Room* other){
    current->south=other;
    other->north=current;
    other->next=current;
}

/*set the east direction of a room to a given room*/
void room_exit_east(struct Room* current, struct Room* other){
    current->east=other;
    other->west=current;
    other->next=current;
}

/*set the west direction of a room to a given room*/
void room_exit_west(struct Room* current, struct Room* other){
    current->west=other;
    other->east=current;
    other->next=current;
}

/*set the up direction of a room to a given room*/
void room_exit_up(struct Room* current, struct Room* other){
    current->up=other;
    other->down=current;
    other->next=current;
}

/*set the down direction of a room to a given room*/
void room_exit_down(struct Room* current, struct Room* other){
    current->down=other;
    other->up=current;
    other->next=current;
}

/*call function item_acq denpending on the name of item*/
void drop_item(struct Item* inv, struct Room* curR, char* name){
    if(strncmp(name, "doll", 4)==0){
        item_acq(inv, curR->items, "Doll");
    }
    else if(strncmp(name, "flask", 5)==0){
        item_acq(inv, curR->items, "Flask");
    }
    else if(strncmp(name, "gold", 4)==0){
        item_acq(inv, curR->items, "Gold");
    }
    else if(strncmp(name, "glonk", 5)==0){
        item_acq(inv, curR->items, "Glonk");
    }
    else{
        item_acq(inv, curR->items, "asdfas");
    }
}

/*call function item_acq denpending on the name of item*/
void acq_item(struct Room* curR, struct Item* inv, char* name){
    if(strncmp(name, "doll", 4)==0){
        item_acq(curR->items, inv, "Doll");
    }
    else if(strncmp(name, "flask", 5)==0){
        item_acq(curR->items, inv, "Flask");
    }
    else if(strncmp(name, "gold", 4)==0){
        item_acq(curR->items, inv, "Gold");
    }
    else if(strncmp(name, "glonk", 5)==0){
        item_acq(curR->items, inv, "Glonk");
    }
    else{
        item_acq(curR->items, inv, "asdfas");
    }
}

/*remove an item from a linked list and add it to another linked list*/
void item_acq(struct Item* curR, struct Item* inv, char* name){
    struct Item* tar=item_take(curR, name);
    if(tar==NULL){
        printf("%s\n\n", "No such item");
    }
    else{
        item_insert(inv, tar);
    }
}

struct Room* starting_room(){
    struct Room* start=room("sr", "the starting room", noItem(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return start;
}

struct Room* room1(){
    struct Room* r1=room("r1", "a room with a bonfire in the middle", flask(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return r1;
}

struct Room* room2(){
    struct Room* r2=room("r2", "a dusty room that may have items in it", gold(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return r2;
}

struct Room* room3(){
    struct Room* r3=room("r3", "a room with a dead body in the corner", doll(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return r3;
}

struct Room* room4(){
    struct Room* r4=room("r4", "an absolutely useless room", glonk(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return r4;
}

struct Room* omen(){
    struct Room* omen=room("omen", "an omen room without omen", noItem(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return omen;
}

struct Room* omen1(){
    struct Room* omen1=room("omen", "an omen room without omen", noItem(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return omen1;
}

struct Room* event(){
    struct Room* event=room("event", "an event room without event", noItem(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return event;
}

struct Room* event1(){
    struct Room* event1=room("event", "an event room without event", noItem(),NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    return event1;
}

/*add a room to the end of the linked list*/
void add_room(struct Room* head, struct Room* input){
    while(head->next!=NULL){
        head=head->next;
    }
    head->next=input;
}

/*create a pile of linked room*/
void pile(struct Room* head){
    add_room(head, event());
    add_room(head, room2());
    add_room(head, room3());
    add_room(head, room4());
    add_room(head, omen());
    add_room(head, room1());
    add_room(head, omen1());
    add_room(head, event1());
}

/*randomly pick a room out of the linked pile*/
int pSize=8;
struct Room* rand_room(struct Room* head){
    if(head->next==NULL){
        return NULL;
    }
    srand(time(NULL));
    int randomnumber = rand() % pSize;
    struct Room* out,*cur;
    out=head->next;
    cur=head;
    int i=0;
    while(cur!=NULL){
        if(i==randomnumber){
            cur->next=out->next;
            pSize--;
            out->next=NULL;
            return out;
        }
        else{
            i++;
            out=out->next;
            cur=cur->next;
        }
    }
}

/*print the room*/
void print_room(struct Room* a){
    printf("%s\n\n", a->description);
}

/*deallocate memory*/
void room_free(struct Room* head){
    while(head!=NULL){
        free(head);
        head=head->next;
    }
}

/*return the pointer to the starting room*/
struct Room* getSr(struct Room* head){
    while(head->next!=NULL){
        head=head->next;
    }
    return head;
}

/*return true if the curR is omen room*/
bool isOmen(struct Room* curR){
    if(strncmp(curR->name, "omen", 4)==0){
        printf("you're blessed\n");
        return true;
    }
    return false;
}

/*print the items in current room and the room in each direction*/
void look(struct Item* it, struct Room* head){
    if(it==NULL){
        printf("There is no items in this room\n\n");   
    }
    else{
        printf("Items:\n");
        while(it!=NULL){
            printf("%s: %s\n", it->name, it->description);
            it=it->next;
        }
        printf("\n");
    }
    printf("North: ");
    if(head->north==NULL){
        printf("a room coverd in mist\n");
    }
    else printf("%s\n", head->north->description);
    printf("South: ");
    if(head->south==NULL){
        printf("a room coverd in mist\n");
    }
    else printf("%s\n", head->south->description);
    printf("East: ");
    if(head->east==NULL){
        printf("a room coverd in mist\n");
    }
    else printf("%s\n", head->east->description);
    printf("West: ");
    if(head->west==NULL){
        printf("a room coverd in mist\n");
    }
    else printf("%s\n", head->west->description);
    printf("Up: ");
    if(head->up==NULL){
        printf("a room coverd in mist\n");
    }
    else printf("%s\n", head->up->description);
    printf("Down: ");
    if(head->down==NULL){
        printf("a room coverd in mist\n");
    }
    else printf("%s\n", head->down->description);
    printf("\n");
}

/*linked the event room with the starting room*/
struct Room* eventNext(char* dire, struct Room* curR, struct Room* sr, struct Room* temp){
    if(sr->south==NULL){
        room_exit_south(sr, temp);
        printf("You just triggered an event, the current room have been connect to the south of starting room and you're teleported to the starting room\n");
        return temp;
    }
    else if(sr->north==NULL){
        room_exit_north(sr, temp);
        printf("You just triggered an event, the current room have been connect to the north of starting room and you're teleported to the starting room\n");
        return temp;
    }
    else if(sr->east==NULL){
        room_exit_east(sr, temp);
        printf("You just triggered an event, the current room have been connect to the east of starting room and you're teleported to the starting room\n");
        return temp;
    }
    else if(sr->west==NULL){
        room_exit_west(sr,temp);
        printf("You just triggered an event, the current room have been connect to the west of starting room and you're teleported to the starting room\n");
        return temp;
    }
    else if(sr->down==NULL){
        room_exit_down(sr, temp);
        printf("You just triggered an event, the current room have been connect to the down of starting room and you're teleported to the starting room\n");
        return temp;
    }
    else if(sr->up==NULL){
        room_exit_up(sr, temp);
        printf("You just triggered an event, the current room have been connect to the up of starting room and you're teleported to the starting room\n");
        return temp;
    }
    else{
        if(strncmp(dire, "north", 5)==0){
            room_exit_north(curR, temp);
            return curR->down;
        }
        else if(strncmp(dire, "west", 4)==0){
            room_exit_west(curR, temp);
            return curR->west;
        }
        else if(strncmp(dire, "east", 4)==0){
            room_exit_east(curR, temp);
            return curR->east;
        }
        else if(strncmp(dire, "up", 2)==0){
            room_exit_up(curR, temp);
            return curR->up;
        }
        else if(strncmp(dire, "down", 4)==0){
            room_exit_down(curR, temp);
            return curR->down;
        }
    }
}

/*move to the next room depending on the input direction*/
struct Room* move(struct Room* cur, char* dire, struct Room* pile){
    if(strncmp(dire, "north", 5)==0){
        if(cur->north==NULL){
            if(pile->next==NULL){
                printf("you lose");
                exit(0);
            }
            struct Room* temp=rand_room(pile);
            room_exit_north(cur, temp);
            if(strncmp(temp->name, "event", 5)==0){
                cur->north=NULL;
                temp->south=NULL;
                struct Room* sr= getSr(cur);
                return eventNext("north", cur, sr, temp);
            }
            else {
                room_exit_north(cur, temp);
                return cur->north;
            }
        }
        else {return cur->north;}
    }
    else if(strncmp(dire, "east", 4)==0){
        if(cur->east==NULL){
            if(pile->next==NULL){
                printf("you lose");
                exit(0);
            }
            struct Room* temp=rand_room(pile);
            room_exit_east(cur, temp);
            if(strncmp(temp->name, "event", 5)==0){
                cur->east=NULL;
                temp->west=NULL;
                struct Room* sr= getSr(cur);
                return eventNext("east", cur, sr, temp);
            }
            else {
                room_exit_east(cur, temp);
                return cur->east;
            }
        }
        else {return cur->east;}
    }
    else if(strncmp(dire, "west", 4)==0){
        if(cur->west==NULL){
            if(pile->next==NULL){
                printf("you lose");
                exit(0);
            }
            struct Room* temp=rand_room(pile);
            room_exit_west(cur, temp);
            if(strncmp(temp->name, "event", 5)==0){
                cur->west=NULL;
                temp->east=NULL;
                struct Room* sr= getSr(cur);
                return eventNext("west", cur, sr, temp);
            }
            else {
                room_exit_west(cur, temp);
                return cur->west;
            }
        }
        else {return cur->west;}
    }
    else if(strncmp(dire, "up", 2)==0){
        if(cur->up==NULL){
            if(pile->next==NULL){
                printf("you lose");
                exit(0);
            }
            struct Room* temp=rand_room(pile);
            room_exit_up(cur, temp);
            if(strncmp(temp->name, "event", 5)==0){
                cur->up=NULL;
                temp->down=NULL;
                struct Room* sr= getSr(cur);
                return eventNext("up", cur, sr, temp);
                
            }
            else {
                room_exit_up(cur, temp);
                return cur->up;
            }
        }
        else {return cur->up;}
    }
    else if(strncmp(dire, "down", 4)==0){
        if(cur->down==NULL){
            if(pile->next==NULL){
                printf("you lose");
                exit(0);
            }
            struct Room* temp=rand_room(pile);
            if(strncmp(temp->name, "event", 5)==0){
                cur->down=NULL;
                temp->up=NULL;
                struct Room* sr= getSr(cur);
                return eventNext("down", cur, sr, temp);
            }
            else {
                room_exit_down(cur, temp);
                return cur->down;
            }
        }
        else {return cur->down;}
    }
}
