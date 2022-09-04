#include <assert.h>
#include <my_malloc.h>
#include <stdio.h>
#include <sys/mman.h>

// A pointer to the head of the free list.
node_t *head = NULL;

// The heap function returns the head pointer to the free list. If the heap
// has not been allocated yet (head is NULL) it will use mmap to allocate
// a page of memory from the OS and initialize the first free node.
node_t *heap() {
  if (head == NULL) {
    // This allocates the heap and initializes the head node.
    head = (node_t *)mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE,
                          MAP_ANON | MAP_PRIVATE, -1, 0);
    head->size = HEAP_SIZE - sizeof(node_t);
    head->next = NULL;
  }

  return head;
}

// Reallocates the heap.
void reset_heap() {
  if (head != NULL) {
    munmap(head, HEAP_SIZE);
    head = NULL;
    heap();
  }
}

// Returns a pointer to the head of the free list.
node_t *free_list() { return head; }

// Calculates the amount of free memory available in the heap.
size_t available_memory() {
  size_t n = 0;
  node_t *p = heap();
  while (p != NULL) {
    n += p->size;
    p = p->next;
  }
  return n;
}

// Returns the number of nodes on the free list.
int number_of_free_nodes() {
  int count = 0;
  node_t *p = heap();
  while (p != NULL) {
    count++;
    p = p->next;
  }
  return count;
}

// Prints the free list. Useful for debugging purposes.
void print_free_list() {
  node_t *p = heap();
  while (p != NULL) {
    printf("Free(%zd)", p->size);
    p = p->next;
    if (p != NULL) {
      printf("->");
    }
  }
  printf("\n");
}

// Finds a node on the free list that has enough available memory to
// allocate to a calling program. This function uses the "first-fit"
// algorithm to locate a free node.
//
// PARAMETERS:
// size - the number of bytes requested to allocate
//
// RETURNS:
// found - the node found on the free list with enough memory to allocate
// previous - the previous node to the found node
//
void find_free(size_t size, node_t **found, node_t **previous) {
  node_t *curNode = heap(); // get the head of the free list
  node_t *preNode = NULL; // preNOde is NULL because we're on the head
  while(curNode != NULL){ // iterate over the free list
    if((curNode->size + sizeof(node_t)) >= (size + sizeof(header_t) )){ // if the block fit the require size
      *found = curNode; // return found by assigning curNode to the pointer
      *previous = preNode; // return previous by assigning preNode to the pointer
      return; // return upon the first free block because we're using first fit
    }
    preNode = curNode; // else go to the next node
    curNode = curNode->next; 
  }
}

// Splits a found free node to accommodate an allocation request.
//
// The job of this function is to take a given free_node found from
// `find_free` and split it according to the number of bytes to allocate.
// In doing so, it will adjust the size and next pointer of the `free_block`
// as well as the `previous` node to properly adjust the free list.
//
// PARAMETERS:
// size - the number of bytes requested to allocate
// previous - the previous node to the free block
// free_block - the node on the free list to allocate from
//
// RETURNS:
// allocated - an allocated block to be returned to the calling program
//
void split(size_t size, node_t **previous, node_t **free_block,
           header_t **allocated) {
  assert(*free_block != NULL);

  if(((*free_block)->size + sizeof(node_t)) == (size + sizeof(header_t))){ // if the block size equal the size we want to allocate, 
    *allocated = (header_t *) *free_block; // change the block to header_t and the size stay the same
    (*allocated)->size = size;
    (*allocated)->magic = MAGIC;
  }
  else{ // else, we need to split the block
    node_t *original_block = *free_block;  // pointer to where the free block was originally 
    *free_block = (node_t *)(((char *)*free_block) + (size + sizeof(header_t))); // adjust the free block pointer foward
    (*free_block)->size = (original_block->size) - (size + (sizeof(header_t))); // adjust the free block size

    *allocated = (header_t *) original_block; // embed header_t to the star of the free_block, which we saved as "original_block"
    (*allocated)-> size = size; // update size and magic
    (*allocated)-> magic = MAGIC;
  }
  
  if(*previous == NULL){ // if we are allocating the first node in the free_list, set the new free node as head
    head = *free_block;
  }
  else{ // if there is a previous node, assign next pointer of previous to new node
    (*previous)->next = *free_block; 
  }

}

// Returns a pointer to a region of memory having at least the request `size`
// bytes.
//
// PARAMETERS:
// size - the number of bytes requested to allocate
//
// RETURNS:
// A void pointer to the region of allocated memory
//
void *my_malloc(size_t size) {
  node_t *found = NULL; // Initializing found, previous and allocated
  node_t *previous = NULL;
  header_t *allocated = NULL;

  find_free(size, &found, &previous); // find the free_node
  if(found == NULL){ // return null if free_node not found.
    return NULL;
  }
  split(size, &previous, &found, &allocated); // call split to get the allocated block
  return (header_t *)(((char *)allocated) + sizeof(header_t)); // return allocated block with pointer adjust to after the block header
}

// Merges adjacent nodes on the free list to reduce external fragmentation.
//
// This function will only coalesce nodes starting with `free_block`. It will
// not handle coalescing of previous nodes (we don't have previous pointers!).
//
// PARAMETERS:
// free_block - the starting node on the free list to coalesce
//
void coalesce(node_t *free_block) {
  bool done = false;
  while(!done){ // loop until no block can be coalesced
    done = true;
    node_t *curr_address = free_block; // pointer to free block
    node_t *next_address = curr_address->next; // adjance block we wish to coalesce
    size_t block_size = curr_address->size + sizeof(node_t);  
    while(next_address != NULL){
      if (((char *)curr_address) + block_size == (char *)next_address){ // if the next pointer is the same as the address of next_address
        done = false; // there is block coalesced
        curr_address->next = next_address->next; // merge two block into one
        curr_address->size = block_size + next_address->size;
        block_size = curr_address->size + sizeof(node_t); // update the new block size
        continue;
      }
    curr_address = next_address; // else go next
    next_address = curr_address->next;
    }
  }
}

// Frees a given region of memory back to the free list.
//
// PARAMETERS:
// allocated - a pointer to a region of memory previously allocated by my_malloc
//
void my_free(void *allocated) {
  header_t *alloc = (header_t *)(((char *)allocated) - sizeof(header_t)); // cast allocated to header_t type and adjust pointer to before the header
  assert(alloc->magic == MAGIC); // assert to check if the magic field is MAGIC
  node_t *free_block = (node_t *)alloc; // cast alloc to "node_t"
  free_block->next = free_list(); // link the free node to the list
  head = free_block; // assign the free node the head 
  coalesce(head); // called coalesce on the head.
}
