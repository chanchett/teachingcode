#include <stdio.h>

#define IGNORE_THIS int main(){ printf("I am a computer, beep boop."); return 0; }

#define display_message(output) printf(output "\n");

#define I_WILL_CAUSE_AN_ERROR #error

#define integer int
