#include "dasb.h"

typedef struct{
  const void* id;
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

void* trait_find(Trait_da* da, const void* id){
  //Trait_Object* obj = self;
  //Trait_da* da = obj->traits;

  for(size_t i = 0; i < da->count; i++){
    if(da->data[i].id == id){
      return da->data[i].trait;
    }
  }

  return NULL;
}

void* trait___find(void* self, const char* id){
  Trait_Object* obj = self;
  //return trait_da_find(&obj->traits, id);
}
