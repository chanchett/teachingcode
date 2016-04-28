int main()
{
  // VARIABLES AND INTEGERS
  // ----------------------
  // So the computer is gonna the commands inside the curly braces after main. So what do we tell it?
  // Things like...
  
  int five=5;

  // This declares a variable, which is a place where we can store values.
  // What kind of values? In this case, an "integer" (or "int", for short).
  // (An integer is just a number with nothing after the decimal point, like 1 or 113)
  // The variable is named "five", and is given a value of 5.
  // The semicolon (;) at the end of the declaration tells the compiler we're done with that command.

  int another_variable=five;

  // We can use variables we've already assigned values to define other variables, so "another_variable" now has a value of 5.
  // Okay, cool, but why do we care?
  // Well, we care because we can do operations on variables to give us results. In particular, we can do math, like:

  int ten=five+five;         // Addition
  int zero=five-five;        // Subtraction
  int twenty_five=five*five; // Multiplication
  int one=five/five;         // Division

  // You can chain as many operations together as you like:

  another_variable=(ten+ten)*(ten+ten)-4+27*13;

  // And we can tell the compiler to show us the value of another_variable (how this works will be explained later).
  printf("The value of another variable is %i\n\n", another_variable);


  
  // Some other quick notes about variables
  // --------------------------------------
  
  // Variable names can be any combination of uppercase letters, lowercase letters, numbers, and underscores, as long as
  // the variable doesn't start with a number, and the variable name isn't something the compiler is already using. So
  int sadghjjh65765KHKJHUIHIUHIH__yhkj_jhgj=2;
  // is totally valid, though probably hard to read and/or type.

  // Variables can be declared without a value
  int no_value;

  // Though in reality, no_value actually DOES have a value; it's just whatever the computer was using before we asked
  // for a variable, which ends up giving it a fairly random and useless value.
  printf("no_value actually has a value of %i\n", no_value);


  // Try compiling "lesson3.cpp" and running "compiled_programs\lesson3.exe" to see what "no_value" ends up being.
  // (if you look at what the compiler tells you, it will in fact warn you that we've used no_value without giving it a value.
  // It calls the variable "uninitialized". For now, we can just ignore that, it won't stop us from compiling or running)



  



  
  



  
  // Below is some code that has errors, and is commented out.
  // Try uncommenting the code (removing just /* and */, not any of the //) and fixing all the errors.
  
  // (the code has some new parts, which you'll figure because you're smart!)
  // (uncomment the code and then compile to get a list of the errors...)

  /*
  int apples=20, oranges=32, bananas, grapes, mango;
  int apples_plus_oranges=apples+orange;
  int grapes=oranges-apples ;
  apples=bananas;
  bananas=oranges;
  
  int a=8;
  int b=4;
  int c=2;
  int d=1;
  a=c+d; b=14+18; a=b+b;
  b=a+b c=d;
  
  a=b=c=d;
  


  // Some questions after you've fixed the compiler errors:
  // Does bananas have a meaningful value?
  printf("value of bananas: %i\n", bananas);
  // Does apples?
  printf("value of apples: %i\n", apples);
  // Does apples_plus_oranges equal apples + oranges?
  printf("%i equals %i\n", apples_plus_oranges, apples+oranges);
  // Why do a, b, c, and d all equal the same thing?
  printf("a:%i b:%i c:%i d:%i\n", a, b, c, d);
  */

  
  // And that's the end of lesson 3!
  // Onward!!!!!!!!111!!!!!!!!!!!!!!
}
