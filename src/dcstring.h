#ifndef DCSTR_H
#define DCSTR_H

#ifndef DCSTR_REALLOC
#include <stdlib.h>
#define DCSTR_REALLOC realloc
#endif /* DCSTR_REALLOC */

#ifndef DCSTR_FREE
#include <stdlib.h>
#define DCSTR_FREE free
#endif /* DCSTR_FREE */

#include <string.h>

#ifndef DCSTRDEF
#define DCSTRDEF
#endif // !DCSTRDEF

#define STRING_INIT_CAP 16

#ifndef STRIP_STRING_STRUCT

typedef struct{
  char* data;
  size_t count;
  size_t capacity;
}String;

#endif // STRIP_STRING_STRUCT

DCSTRDEF bool dcstr_reserve(String* s, size_t expected_capacity);

DCSTRDEF bool dcstr_append(String* s, char* t);
DCSTRDEF bool dcstr_append_null(String* s);
DCSTRDEF bool dcstr_overlay(String* s, char* t);

DCSTRDEF String newstring(char* t);
DCSTRDEF char* newcstr(char* t);

DCSTRDEF char dcstr_pop(String* s);
DCSTRDEF void dcstr_free(String* s);

#endif // !DCSTR_H

#ifdef DCSTR_IMPL

DCSTRDEF bool dcstr_reserve(String* s, size_t expected_capacity){
  if(expected_capacity > s->capacity){
    if(s->capacity == 0){
      s->capacity = STRING_INIT_CAP;
    }
    while(expected_capacity > s->capacity){
      s->capacity *= 2;
    }
    s->data = DCSTR_REALLOC(s->data, s->capacity * sizeof(s->data));
    if(s->data == NULL){
      return false;
    }
  }
  return true;
}

DCSTRDEF bool dcstr_append(String* s, char* t){
  size_t new_count = strlen(t);
  if(!dcstr_reserve(s, s->count + new_count)) return false;
  memcpy(s->data + s->count, t, new_count*sizeof(s->data));
  s->count += new_count;
  return true;
}

DCSTRDEF bool dcstr_append_null(String* s){
  return dcstr_append(s, "");
}

DCSTRDEF bool dcstr_overlay(String* s, char* t){
  size_t new_count = strlen(t);
  if(!dcstr_reserve(s, new_count)) return false;
  memcpy(s->data, t, new_count*sizeof(s->data));
  s->count = new_count;
  return true;
}

DCSTRDEF String newstring(char* t){
  String holder = {0};
  dcstr_overlay(&holder, t);
  return holder;
}

DCSTRDEF char* newcstr(char* t){
  String holder = {0};
  dcstr_overlay(&holder, t);
  return holder.data;
}

DCSTRDEF char dcstr_pop(String* s){
  if(s->count > 0){
    return s->data[--s->count];

  }
  return '\0';
}

DCSTRDEF void dcstr_free(String* s){
  DCSTR_FREE(s->data);
}

#endif // IMPL
#ifdef STRIP_DCSTR_PREFIX

#endif
