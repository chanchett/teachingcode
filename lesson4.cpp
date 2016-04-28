int main(){
  // BOOLEAN VARIABLES
  // -----------------
  // So there are integer variables; and based on that grammar, you can probably guess there are variables that aren't integers. Which is true.
  // Another type of variable is called a "boolean" (or "bool", for short). Boolean variables have two possible values, "true" and "false".

  bool is_the_earth_round=true;
  bool is_lemurday_fake=false;

  bool are_you_awesome = is_the_earth_round;

  // (Side note: The rules we learned about integer variables are true for basically all other variable types; the naming rules are the same,
  // you can use them to give values to other variables. The major difference between types of variables is the values they can
  // store, and the operations you can do on those variables.)
  

  // EQUALITY
  // --------
  // Booleans are particularly important, because equality operators (and comparison operators) return boolean results.
  // So... what's an equality operator? Equality operators are the symbols "==" and "!=". "==" can be used to checked
  // whether two things are equal, and "!=" can be used to check whether two things are not equal.

  bool definitely_false=true==false;
  // Since true does not equal false, definitely_false has a value of false.

  bool definitely_true=true==true;
  // Since true does equal true, definitely_true has a value of true.
  
  definitely_true=true!=false;
  // Since true does not equal false, and we're using the "!=" operator, definitely_true still has a value of true.

  // But equality doesn't just apply to booleans. We can also use it on integers.

  int thirteen=13;
  int twelve=12;
  int seven_plus_six=7 + 6; // Also 13

  bool answer=thirteen==twelve;
  // 13 does not equal twelve, so answer has a value of false.
  
  answer=thirteen==seven_plus_six;
  // 13 does equals 7+6, so answer has a value of true.

  answer= 27!=81;
  // 27 does not equal 81, so answer has a value of true.
  
  
  // COMPARISON OPERATORS
  // --------------------
  // Instead of just checking whether things are equal, with integers we can check whether they're greater or less than each other,
  // using the ">", "<", ">=" and "<=" symbols. Just like equality, these operators return booleans.
  
  int legs_on_a_car=0;
  int wheels_on_a_car=4;
  int legs_on_a_horse=4;
  int legs_on_a_human=2;
  
  // ">" and "<" are "greater than" and "less than", respectively.
  
  answer = legs_on_a_horse > legs_on_a_car;
  // 4 is greater than 0, so answer has a value of true.

  bool is_six_greater_than_seven= 6 > 7;
  // Now is_six_greater_than_seven = false;

  
  // The ">=" and "<=" operators are "greater than or equal to" and "less than or equal to". These do exactly what the name makes you expect.

  answer= 2<=4;
  // answer = true.
  answer= 3<=4;
  // answer = true.
  answer= 4<=4;
  // answer = true.
  answer= 5<=4;
  // answer = false.


  

  
  // Try removing the beginning comment from the code below. If you compile "lesson4.cpp", the compiler will complain about "??" in your program.
  // Replace the "??" with equality and comparison operators to make all of the statements true.
  // Once you've replaced all the question marks, you can compile and run the program to see which of the statements should be changed to be true.
  
  /* REMOVE THIS LINE

  // Here, replace ?? with == and !=
  bool answer1_1=        23 ?? 44;
  bool answer1_2=       200 ?? 200;
  bool answer1_3=answer_1_2 ?? false;
  bool answer1_4=      true ?? true;
  bool answer1_5=        16 ?? 4*4;
  bool answer1_6=       3+6 ?? 8;


  
  // This time, replace ?? with >, <, <=, >=
  bool answer2_1=        23 ?? 44;
  bool answer2_2=       200 ?? 200;
  bool answer2_3=         0 ?? 1000;
  bool answer2_4=       899 ?? 998;
  bool answer2_5=        16 ?? 4*4;
  bool answer2_6=       3+6 ?? 8;



  
  // This is the code that shows you your answers (it'll be explained later)
  printf("answer1_1 has a value of %s.\n", answer1_1 ? "true" : "false");
  printf("answer1_2 has a value of %s.\n", answer1_2 ? "true" : "false");
  printf("answer1_3 has a value of %s.\n", answer1_3 ? "true" : "false");
  printf("answer1_4 has a value of %s.\n", answer1_4 ? "true" : "false");
  printf("answer1_5 has a value of %s.\n", answer1_5 ? "true" : "false");
  printf("answer1_6 has a value of %s.\n\n", answer1_6 ? "true" : "false");
  
  printf("answer2_1 has a value of %s.\n", answer2_1 ? "true" : "false");
  printf("answer2_2 has a value of %s.\n", answer2_2 ? "true" : "false");
  printf("answer2_3 has a value of %s.\n", answer2_3 ? "true" : "false");
  printf("answer2_4 has a value of %s.\n", answer2_4 ? "true" : "false");
  printf("answer2_5 has a value of %s.\n", answer2_5 ? "true" : "false");
  printf("answer2_6 has a value of %s.\n", answer2_6 ? "true" : "false");
  // End of code that shows answers

  /* YOU ACTUALLY DON'T NEED TO REMOVE THIS LINE..... BUT WHY IS THAT? */





  

  // If all answers print out true when you compile "lesson4.cpp" and run "compiled_programs\lesson4.exe", you're done!

  // now ONTO lesson5.cpp !!!!!!!!!!!
  
  
  return 0;
}
