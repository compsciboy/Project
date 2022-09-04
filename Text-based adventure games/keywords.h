#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Key{
    char* command;
    char* description;
    struct Key* next;
};
struct Key* key(char* command, char* description, struct Key* next);
void add_key(struct Key* head, struct Key* input);
void init_key(struct Key* out);
void print_key(struct Key* out);
void key_free(struct Key* head);