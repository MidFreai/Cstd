#ifndef TRAIT_H
#define TRAIT_H

// for size_t
#include <stddef.h>

//for realloc
#include <stdlib.h>

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

static const size_t Trait_da_capacity = 1;

bool trait_da_reserve(Trait_da* da, size_t expected_capacity);
bool trait_da_append(Trait_da* da, Trait_entry entry);
bool trait_append(void* self, Trait_entry entry);

void* trait_find(void* self, const void* id);
void* trait_da_find(Trait_da* da, const char* id);

#endif //TRAIT_H

#ifdef TRAIT_IMPL

void* trait_find(void* self, const void* id){
  Trait_da* da = self;
  if(!da) { return NULL; };

  for(size_t i = 0; i < da->count; i++){
    if(da->data[i].id == id){
      return da->data[i].trait;
    }
  }

  return NULL;
}

void* trait_da_find(Trait_da* da, const char* id){
  for(size_t i = 0; i < da->count; i++){
    if(da->data[i].id == id){
      return da->data[i].trait;
    }
  }

  return NULL;
}

bool trait_da_reserve(Trait_da* da, size_t expected_capacity){
  if(expected_capacity > da->capacity){
    if(da->capacity == 0){
      da->capacity = Trait_da_capacity;
    }

    while (expected_capacity > da->capacity) {
      da->capacity *= 2;
    }

    da->data = realloc(da->data, da->capacity * sizeof(*da->data));

    if (da->data == NULL) {
      return false;
    }
  }
  return true;
}

bool trait_da_append(Trait_da* da, Trait_entry entry){
  if(!trait_da_reserve(da, da->count + 1)) return false;
  da->data[da->count++] = entry;
  return true;
}

bool trait_append(void* self, Trait_entry entry){
  Trait_da* da = self;
  if(!da) return false;
  if(!trait_da_reserve(da, da->count + 1)) return false;
  da->data[da->count++] = entry;
  return true;
}

#endif // TRAIT_IMPL
