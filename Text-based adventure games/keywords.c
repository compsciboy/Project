#include "keywords.h"

/*create a struct key*/
struct Key* key(char* command, char* description, struct Key* next){
    struct Key *out=(struct Key*) malloc(sizeof(struct Key));   
    out->command=command;
    out->description=description;
    out->next=next;
}

/*add a key to the end of the linked list*/
void add_key(struct Key* head, struct Key* input){
    while(head->next!=NULL){
        head=head->next;
    }
    head->next=input;
}

/*create a linked list of key*/
void init_key(struct Key* out){
    add_key(out, key("inventory","See the items in the inventory", NULL));
    add_key(out, key("take ITEM", "take ITEMS from the romm to the inventory", NULL));
    add_key(out, key("drop ITEM", "drop ITEMS from the inventory to the room", NULL));
    add_key(out, key("go DIRECTION", "go to the room in the given DIRECTION", NULL));
}

/*print out every element in the linked list*/
void print_key(struct Key* out){
    printf("Here is a list of command:\n");
    while(out!=NULL){
        printf("%s: %s \n", out->command, out->description);
        out=out->next;
    }
    printf("\n");
}

/*deallocate memory*/
void key_free(struct Key* head){
    while(head!=NULL){
        free(head);
        head=head->next;
    }
}