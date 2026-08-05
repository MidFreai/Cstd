#include <stdio.h>
//#include <dasb.h>
#define DCSTR_IMPL
#include <dcstring.h>

int main(){
  String teste = newstring("minha nossa memory averlay the ocean");
  char* testecstr = newcstr("nossa nossa nossa");
  //dcstr_append(&teste, testecstr);
  dcstr_pop(&teste);
  printf("%s\n%s\n", teste.data, testecstr);
  return 0;
}
