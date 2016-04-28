#include <stdio.h>

#define IGNORE_THIS int main(){ printf("I am a computer, beep boop."); return 0; }

#define display_message(output) printf(output "\n");

#define integer int

#ifndef SECTION_2
bool SECTION_DEFINED_2=false;
#else
bool SECTION_DEFINED_2=true;
#endif

#define BEGIN_SECTION(section) if(SECTION_DEFINED_##section){

#define END_SECTION(section) }

#ifdef LESSON_lesson7
#define FUNCTIONS_ARE_DEFINED
void some_mysterious_function_that_draws_things(int x, int y);
#endif

#ifdef LESSON_lesson8
#define FUNCTIONS_ARE_DEFINED
void some_mysterious_function_that_draws_things(int x, int y);
#endif
