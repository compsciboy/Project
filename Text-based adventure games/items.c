#include"items.h"

/*create a struct item*/
struct Item* item(char* name, char* description, struct Item* next){
    struct Item* out=(struct Item*) malloc(sizeof(struct Item));
    out->name=name;
    out->description=description;
    out->next=next;
    return out;
}

/*remove and return an item from a linked list*/
struct Item* item_take(struct Item* head, char* name){
    struct Item* out,*cur;
    out=head->next;
    cur=head;
    while(out!=NULL){
        if(strcmp(out->name, name)==0){
            cur->next=out->next;
            out->next=NULL;
            return out;
        }
        else{
            out=out->next;
            cur=cur->next;
        }
    }return NULL;
}

/*insert an intem into a linked list*/
void item_insert(struct Item* head, struct Item* input){
    while(head->next!=NULL){
        head=head->next;
    }
    head->next=input;
}

/*print every items in the linked list*/
void inv_print(struct Item* head){
    printf("Inventory:\n");
    if(head==NULL){
        printf("Empty");
    }
    else{
        while(head!=NULL){
            printf("%s: %s\n", head->name, head->description);
            head=head->next;
        }
    }
    printf("\n");
}

/*deallocate memory*/
void item_free(struct Item* head){
    while(head!=NULL){
        free(head);
        head=head->next;
    }
}

struct Item* noItem(){
    struct Item* null=item("","", NULL);
    return null;
}

struct Item* flask(){
  struct Item* flask=item("", "", item("Flask", "A flask fill with estus", NULL));
  return flask;
}

struct Item* doll(){
  struct Item* doll=item("", "", item("Doll", "A strange doll in strange dress", NULL));
  return doll;
}

struct Item* gold(){
  struct Item* gold=item("", "", item("Gold", "golden gold", NULL));
  return gold;
}

struct Item* glonk(){
  struct Item* glonk=item("", "", item("Glonk", "Does absolutely nothing and dies", NULL));
  return glonk;
}

/*return the number of item in the linked list*/
int sizeOf(struct Item* head){
    int out=0;
    while(head!=NULL){
        out++;
        head=head->next;
    }
    return out;
}