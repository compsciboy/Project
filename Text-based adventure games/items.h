#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Item{
    char* name;
    char* description;
    struct Item* next;
};

struct Item* item(char* name, char* description, struct Item* next);
struct Item* item_take(struct Item* head, char* name);
void item_insert(struct Item* head, struct Item* input);
void item_free(struct Item* head);
void inv_print(struct Item* head);
struct Item* noItem();
struct Item* flask();
struct Item* gold();
struct Item* doll();
struct Item* glonk();
int sizeOf(struct Item* head);