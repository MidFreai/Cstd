#include "dasb.h"

#include <stdio.h>

#define TRAIT typedef struct

typedef struct{
  const char* name;
  void* trait;
}Trait_entry;

typedef struct{
  Trait_entry* data;
  size_t count;
  size_t capacity;
}Trait_da;

// Base model for casting void*
typedef struct{
  Trait_da traits;
}Trait_Object;

void* trait_find(Trait_da* da, const char* id){
  //Trait_Object* obj = self;
  //Trait_da* da = obj->traits;

  for(size_t i = 0; i < da->count; i++){
    if(!strcmp(da->data[i].name, id)){
      return da->data[i].trait;
    }
  }

  return NULL;
}

void* trait___find(void* self, const char* id){
  Trait_Object* obj = self;
  //return trait_da_find(&obj->traits, id);
}

TRAIT{
  void(*show)(void* self);
}Show;
static const char Show_id;

void show(void* self){
  Trait_Object* obj = self;
  Show* trait = trait_find(&obj->traits, "Show");

  if(!trait) return;

  trait->show(self);
}

typedef struct{
  Trait_da traits;
  int cap;
}Type;

void typeshow(void* self){
  Type* t = self;
  printf("%d\n", t->cap);
}

int main(void){
  Type t = {0};
  da_append(&t.traits, ((Trait_entry){ "Show", &(Show){ typeshow } }));

  t.cap = 69;
  show(&t);

  //Show* s = trait_find(&t, "Show");
  //s->show(&t);
  return 0;
}
