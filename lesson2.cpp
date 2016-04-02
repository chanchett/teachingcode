// COMMENTS
// --------
// Programming languages have syntaxes that code needs to conform to. If it doesn't, the computer is like "beep boop, error!".
// This is where these -> // <- guys come in. Anything written after those slashes (on the same line) is completely ignored by
// the compiler. This is handy for writing notes to yourself/other people about what some code is or for ignoring code
// you might want later but not right now. The text the compiler ignores is called a comment.

// So, single line comments are fine for a single line of text, but what you wanted to write a novel?
// You can use these guys -> /* <- and these guys -> */ <-. The compiler will ignore everything
// we write in between them.


// So this is a comment

/*
And this is also a comment,
but it can go on a lot longer without extra typing.
blah blahh blah
*/


// ERRORS AND THE MAIN METHOD
// --------------------------

/* Try compiling this lesson by typing "compile.bat lesson2.cpp" and pressing enter.
   You'll get this error:



Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23026 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

lesson2.cpp
Microsoft (R) Incremental Linker Version 14.00.23026.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:lesson2.exe
lesson2.obj
LINK : fatal error LNK1561: entry point must be defined
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   This guy right here is the problem. 
   When the program is compiled, the compiler looks for a line that says "int main()". This is where your program is gonna start.
   Remove the lines below that say REMOVE THIS LINE to uncomment the main method.


*/


/* REMOVE THIS LINE
int main() // The compiler looks for this line, that says "int main()" on it.
{ // And then it runs the code from the first "{" (opening brace) after main until the matching "}" (closing brace) below.
  
  printf("I will display first.\n");
  printf("I will display second.\n");
  //printf("I will never display! (unless you remove the slashes in front of this line)\n");
  printf("and so on...\n");
  
  return 0;
} // This is the matching closing brace.
AND REMOVE THIS LINE */



// You can try compiling this program again by typing "compile.bat lesson2.cpp" and pressing enter. The error should be gone!
// And run it by typing "compiled_programs\lesson2.exe" and pressing enter.
