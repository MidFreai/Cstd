// Dinamic C String
// Make Strings without memory alloc
// using the String type or native c strings with the newcstr()

#ifndef DCSTR_H
#define DCSTR_H

// Macros for swap std libs

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

typedef struct{
  char* data;
  size_t count;
  size_t capacity;
}String;

// Take an string literal and return a string literal
DCSTRDEF char* newcstr(char* t);

// Check the capacity of the String and allocate memory // Returns false if cannot allocate
DCSTRDEF bool dcstr_reserve(String* s, size_t expected_capacity);

// Call reserve and add the string loteral
DCSTRDEF bool dcstr_append(String* s, char* t);

// Append a null caracter in the end
DCSTRDEF bool dcstr_append_null(String* s);

// Overwrite the content of the String
DCSTRDEF bool dcstr_overwrite(String* s, char* t);

// Call Overwrite on a new String and return a pointer to this new String
DCSTRDEF String newstring(char* t);

// TODO: is not working
DCSTRDEF char dcstr_pop(String* s);

// Free the data of the String
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

DCSTRDEF bool dcstr_overwrite(String* s, char* t){
  size_t new_count = strlen(t);
  if(!dcstr_reserve(s, new_count)) return false;
  memcpy(s->data, t, new_count*sizeof(s->data));
  s->count = new_count;
  return true;
}

DCSTRDEF String newstring(char* t){
  String holder = {0};
  dcstr_overwrite(&holder, t);
  return holder;
}

DCSTRDEF char* newcstr(char* t){
  String holder = {0};
  dcstr_overwrite(&holder, t);
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
  s->count = 0;
}

#endif // IMPL
#ifdef STRIP_DCSTR_PREFIX

#endif
