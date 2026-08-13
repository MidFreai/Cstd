#include <trait.h>

#include <stdio.h>

#define TRAIT typedef struct
#define TRAIT_ID static const char

TRAIT{
  void(*show)(void* self);
}Show;
static const char Show_id;

void show(void* self){
  Trait_Object* obj = self;
  Show* trait = trait_find(self, &Show_id);

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
  trait_append(&t.traits, (Trait_entry){ &Show_id, &(Show){ typeshow } });

  t.cap = 69;
  show(&t);

  return 0;
}
