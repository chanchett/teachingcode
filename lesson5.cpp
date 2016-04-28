// SKIP DOWN TO main() FOR A SEC, OKAY?
// We'll get back to here in a second.

void function_that_displays_stuff(){
  // This is what a function declaration looks like. The first part, that says "void" is called the
  // "return type" of the function. We don't need to think about that just yet.
  
  // The next part, "function_that_displays_stuff", is the name of the function, and how we'll be able to talk
  // about it. Function names follow the exact same rules as variable names: Capital letters, lowercase letters,
  // numbers and underscores, don't start with a number, and don't use a name the compiler's using for something
  // else.

  // Then we got some parentheses "()". Ignore those for now also. Then we got some curly braces "{"
  // and some code down here.

  int number=444444444;
  printf("STUFF\n");
  printf("I am a function that prints STUFF\n");
  printf("number is %i\n\n", number);

  // After the code, we got an ending curly brace. Now let's jump back to where we were in main.
}




void function_with_arguments(int arg1, bool arg2, int birds){
  // This is a function defined with arguments. An argument is defined by a type, like "int" or "bool", and
  // then a name for the argument. If you want multiple arguments, you can have a list of arguments separated by commas.
  // What defining an argument does is it tells the compiler "hey, this function needs some extra information."
  // The arguments can then be used just like variables in the code:

  int not_used_for_anything=arg1*27+birds;
  
  printf("There are %i birds in my locker.\n", birds);
  printf("I think that this is %s.\n\n", arg2 ? "lovely" : "grandiose");

  // "But good sir," you may ask, "Pray tell where the values for these functions come from? Are they pulled
  // haphazardly from the ether?" Nope! They'll be defined at the function call, so let's go back to main and
  // look at that.
}





void the_function_we_actually_wanted(int some_integer){
  bool greater_than_10=some_integer > 10;
  bool square_root_of_16=some_integer*some_integer == 16;
  int some_integer_times_9=some_integer*9;
  printf("some_integer has a value of %i.\n", some_integer);
  printf("is some_integer greater than 10? %s.\n", greater_than_10 ? "yes" : "no");
  printf("is some_integer the square root of 16? %s.\n", square_root_of_16 ? "yes" : "no");
  printf("what's some_integer times 9? %i.\n", some_integer_times_9);
}












void a_function_with_no_effect(){
  // This function doesn't do anything
  int a, b, c;
  b=3;
  c=b; a=c;
}






























int main(){
  // FUNCTIONS
  // --------
  // Hypothetically, let's say you wanted to find out some facts about an integer.
  // (Yeah, the examples are kinda contrived, but we're building to something more interesting soon!)
  
  
  // We have an integer here
  
  int some_integer=4;
  
  // Let's find out some stuff
  bool greater_than_10=some_integer > 10;
  bool square_root_of_16=some_integer*some_integer == 16;
  int some_integer_times_9=some_integer*9;
  printf("some_integer has a value of %i.\n", some_integer);
  printf("is some_integer greater than 10? %s.\n", greater_than_10 ? "yes" : "no");
  printf("is some_integer the square root of 16? %s.\n", square_root_of_16 ? "yes" : "no");
  printf("what's some_integer times 9? %i.\n", some_integer_times_9);

  // Buuuut... What if we wanted to do it multiple times? With multiple numbers? Maybe even at different places in the program?
  // We could like copy and paste it, and then change the variable it's using, or retype it... But is there an easier way?
  // Yes! What we want is called a function. There are two parts to using a function, the "function declaration" and the
  // "function call". In order to "call" the function, we need to place the "declaration" in the file first (which is why this
  // lesson is formatted a little weird, what with you having to skip here down to main).

  // Let's jump back up to the top of the file, to the line that says
  
  // void function_that_displays_stuff(){

  // to look at the function declaration there.





  
  // Once you've look at the function declaration, start reading here again:
  // So, it looks a lot like we've basically got some code with a name, and that's basically what the function declaration
  // is, it tells the compiler "here's some code, and here's a name for that code".
  // Once that function has been declared, we can "call" the function, using a function call, which tells the computer
  // to run the function at that point in the program.

  function_that_displays_stuff();
  // This a function call to the function called "function_that_displays_stuff". The function call is just the name of
  // the function, the parentheses "()" and a semicolon to tell the compiler where the end of that statement is,
  // We can now call the function as many times as we'd like:

  function_that_displays_stuff();
  function_that_displays_stuff();
  function_that_displays_stuff();

  // Try compiling and running this and seeing what it does! ("compile.bat lesson5.cpp")


  
  // It prints out stuff about some_integer once, and then runs "function_that_displays_stuff()" 4 times. Now
  // we're halfway to what we want... We can call code multiple times. But every time the code runs, it's going
  // to run the exact same way, which doesn't help us much. This is where the next part of functions comes
  // in: "arguments". Let's jump backwards up to the function declaration of

  // function_with_arguments()

  // So here we call "function_with_arguments", and we're passing in some values to the arguments
  
  function_with_arguments(23, true, 1);

  // Since the function has been defined to take an integer, a boolean, and another integer, we've passed it values
  // of those types, in that order. When that function call is run, the argument variables will have the values
  // passed into it, and run accordingly.

  // Like before, we can now call this function over and over again, except this time we can pass in different arguments.
  function_with_arguments(8, 5<8, 2);
  function_with_arguments(16, true==false, 4);
  function_with_arguments(32, false!=true!=true, 8);




  
  // Sweet! So now we can actually do what we wanted to. There's a third function declaration "the_function_we_actually_wanted"
  // defined up there that you can look at. It takes one integer argument, and prints out the things we wanted to know
  // about that integer, just like we wanted!

  the_function_we_actually_wanted(4);
  the_function_we_actually_wanted(8);
  the_function_we_actually_wanted(16);

  // So there we go! We can reuse that code as many times as we'd like, wherever we want.






  
  // Some miscellaneous stuff about functions:
  
  // The block of code we're in right now, the one that starts with "main()"? You might have notice that that's structured like
  // a function declaration, since it has a return type ("int"), it has a name ("main"), it has the parentheses with no
  // arguments, and it has a block of code with no arguments (the code we're in the middle of right now). "main" even
  // is called a function; when we ask the operating system to run our program, the operating system actually calls
  // "main()" from outside our code to start it running.

















  

  

  // Like some of the other lessons, this lesson has a commented out block of code below with some errors in it.
  // Uncomment it, and use the compiler to find the errors in it, and fix them!


  /*

  function_that_dispays_stuff();
  
  the_function_we_actually_wanted( 7-9- );
  
  function_that_displays_stuff()
  function_that_displays_stuff();
  
  function_with_arguments(333, true);
  
  a_function_with_no_effect(22, 44, 55, 6, 7);
  
  a_function_with_no_effect;

   */



  










  
  // And that's everything we need to know about functions for now!!! There's some other stuff that we haven't covered yet, like
  // what the return type is for, but that'll be covered later.


  // You're done with lesson5.cpp!
  
  // Wingardium le-sson6.cpp!
}
