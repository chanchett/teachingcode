// Here's our include, cause we're using a window and graphics again again.
#include "window/window_and_graphics.h"

// "window/window_and_graphics.h" expects us to define "called_sixty_times_a_second" this time as well.







void called_sixty_times_a_second(int milliseconds, int x, int y, bool clicked, bool z_down, bool x_down){
  // CONTROL STRUCTURES/IF STATEMENTS
  // --------------------------------
  // In every program we've looked at so far, any line of code we've written has ALWAYS executed, everytime,
  // unless it was commented out. Now, we're going to look into ways of having the program not always run
  // everything all the time. Structures in the code that change whether or not some code is executed are
  // called "control structures". The first control structure we're going to look at is called an "if statement".
  // If statements look like this:
  /*

  if(boolean expression){
    some code to run
  }

  */
  // If the boolean expression has a value of "true", the code gets run. If the expression is false, the flow
  // of execution just skips past the block of code in the if statement. Let's look at this in action:

  if(clicked){
    drawRectangle(100, 100, 100, 100, red);
  }

  // Try compiling and running this program, and then clicking the mouse inside the window. A red square appears in the top left
  // corner, right? While the mouse is clicked, when this function is called, clicked has a value of true, so it executes the
  // code in the if statement.


  
  

  
  // We can use any boolean statement for expression of an if statement, like if the mouse is on the left half of the window:

  if(x > 500){
    drawLine(x-20, y-20, x+20, y+20, blue);
    drawLine(x-20, y+20, x+20, y-20, blue);
  }

  // And that's the most basic if statement!


  




  
  // Now, suppose we wanted to draw a orange square when the Z key is pressed, and a green one when it's not.
  // Well, we could do something kind of like:
  /*

    if(z_down){
      drawRectangle(100, 100, 400, 400, orange);
    }

    if(z_down==false){
      drawRectangle(100, 100, 400, 400, green);
    }

   */

  // and this would definitely work, but isn't actually necessary. The if statement has a companion structure, called the
  // "else" statement. "else" statements go after if statements (example below), and run at the opposite time as the if statement.
  // If the expression in the if statement is true, the else statement doesn't run. If the expression is false, the else
  // statement runs.

  if(z_down){
    drawRectangle(400, 400, 100, 100, orange);
  }else{
    drawRectangle(400, 400, 100, 100, green);
  }

  // If you run the program and press the z key on the keyboard, the square will change colors, because you're changing the
  // boolean value of z_down, and so changing whether the if or the else statement runs.








  

  // If statements can be nested (meaning you can have if statements inside of other if statements), and you can nest them
  // as deeply as you like.

  if(x_down){
    drawLine(0, 0, x, y, purple);
    if(z_down){
      drawLine(400, 0, x, y, purple);
      if(y>200){
	drawLine(200, 200, x, y, purple);
      }
    }else{
      drawLine(0, 400, x, y, purple);
    }
  }






  // There is also another minor variation of ifs and elses: the combination of the two, called an "else if".
  // The "else if" must come after an if statement, just like the else statement, and must come before the
  // else statement if there is one. This is how it looks:

  if(x<200){
    drawRectangle(10, 400, 20, 200, red);
  }else if(x<300){
    drawRectangle(10, 400, 20, 200, orange);
  }else if(x<400){
    drawRectangle(10, 400, 20, 200, yellow);
  }else if(x<500){
    drawRectangle(10, 400, 20, 200, green);
  }else{
    drawRectangle(10, 400, 20, 200, blue);
  }

  // Only one of these blocks will be run at a time; if x is less 200, the red rectangle is drawn. If x is greater
  // than 200, the first if block won't run, and it will check the next one. If x is less than 300, then that block
  // will be run. If x is greater than 300 and less 400, the next block will be run, and so on.

  // So "if else" statements allow you to have as many possibilities as you want for the program to check, but only
  // one will ever run.

  



  // variable scope
  // not operator
  // test.exercise
}

int main(){
  open_a_window();
  deal_with_the_window();
}
