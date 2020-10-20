#include <fstream>
#include <iostream>
using namespace std;

int main() {
  // printf("hola mundo, soy Aldito\nHola soy papá\nmi primer .exe o mi ultimo
  // sera de sonic.exe\n");
  int edad;
  printf("Escribe tu edad:\n");
  scanf("%d", &edad);

  if (edad < 12) {
    printf("Hola, eres un niño.\n");
  }

  if (edad >= 12 and edad <= 18) {
    printf("Hola, eres un adolescente.\n");
  }

  if (edad > 18) {
    printf("Hola, eres un adulto.\n");
  }
}