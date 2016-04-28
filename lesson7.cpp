// Here's our include, cause we're using a window and graphics again.
#include "window/window_and_graphics.h"





// Now, this time when we include "window/window_and_graphics.h", it expects us to have a function defined.
// Below is the function we're defining. Since I've been trying to name these functions (and everything)
// with obvious names, you might be able to guess that the function's going to be called 60 times a second. (The
// code that will actually call it is inside deal_with_the_window(), if you're wondering) The fact that this
// function will be called repeatedly and consistently means that we can use it to get a more interactive view
 // of what our code is doing!

void called_sixty_times_a_second(int milliseconds, int x, int y, bool clicked, bool z_down, bool x_down){
  // So this function is going to get called... But what are the values of the arguments it's passing in?


  
  // The first argument is milliseconds (which is thousandths of a second) since the program has been started.

  // The second and third arguments are the coordinates in pixels of the mouse.

  // The fourth argument is a bool representing whether the left mouse button is being held down.

  // The fifth and sixth arguments are bools representing whether the z and x keys on the keyboard are being
  // pressed down.

  
  // For this lesson, we're just going to look at the coordinates of the mouse, x and y.

  // Let's draw somethings based on the coordinates of the mouse.
  int x_minus_20=x-20;
  int y_minus_20=y-20;
  drawRectangle(x_minus_20, y_minus_20, 40, 40, green);
  
  int half_y=y/2;
  drawRectangle(20, half_y, 30, half_y, orange);

  drawLine(x-20, half_y,    x,    half_y-20, red);
  drawLine(x,    half_y-20, x,    half_y+20, red);
  drawLine(x,    half_y+20, x+20, half_y,    red);
  
  drawLine(x,    half_y+40, x,    y-40,      red);
  
  int tenth_y=y/10;
  int tenth_x=x/10;
  drawRectangle(300, 300, 200, 200, blue);

  int top_square_x=300+tenth_x;
  int top_square_y=300+tenth_y;
  int bottom_square_x=300+200-10-tenth_x;
  int bottom_square_y=300+200-10-tenth_y;
  drawRectangle(top_square_x,    top_square_y,    10, 10, purple);
  drawRectangle(bottom_square_x, bottom_square_y, 10, 10, purple);
  

  // Try compiling and running this lesson...




  
  
  // When you move the mouse around the screen, stuff follows and reacts to it, right? Look at the code that's
  // written, and see if you can figure out how the various pieces are working the way they are. (Try commenting
  // out sections of code till you have isolated the thing you want to figure out if there's too much going on
  // otherwise).









  









  
  // Now you've had a chance to look at how things get drawn on the screen in reaction to the mouse...
  
  // Commented out below is a ~mysterious~ function that draws some things to the screen.
  // Comment out the drawing code above, and uncomment the mystery function. Compile and run the program, and look at what's
  // drawn on the screen (move the mouse). Then! Try and write code to reproduce what the function does!

  
  // (Hints: Try just taking it one shape at a time;
  //         think about the mathematical operations available to you;
  //         you can always compile and run your code if you're not sure if you're doing something right;
  //         Everything that gets drawn is dependent on x and y in some way, try to figure out how!
  //         Most importantly, just try things)
  


  
  //some_mysterious_function_that_draws_things(x, y);
}

int main(){
  open_a_window();
  deal_with_the_window();
}



// When you've got something that's close to what the function is drawing, you're done! Lesson 7 in the bag!

// Congratulations!





// And onward to lesson 8!




































































void some_mysterious_function_that_draws_things(int x, int y){
  // The expanding rectangles at the top of the screen
  int d=x/4;
  drawRectangle(0*d, 20, d, 40, green);
  drawRectangle(1*d, 20, d, 40, yellow);
  drawRectangle(2*d, 20, d, 40, orange);
  drawRectangle(3*d, 20, d, 40, red);



  
  // The diamond that follows the cursor
  int y1=y-30;
  int x1=x-30;
  int y2=y+30;
  int x2=x+30;
  drawLine(x, y1, x, y2, purple);
  drawLine(x1, y, x2, y, purple);
  drawLine(x, y1, x1, y, purple);
  drawLine(x, y2, x2, y, purple);
  drawLine(x, y1, x2, y, purple);
  drawLine(x, y2, x1, y, purple);



  
  // The diagonally stretching square
  int k=y+300;
  drawLine(0, 260, y+40, k,    blue);
  drawLine(0, 300, y,    k,    blue);
  drawLine(0, 340, y,    k+40, blue);
  drawRectangle(y, k, 40, 40, blue);




  // The black outline
  drawRectangle(600, 400, 200, 200, black);
  drawRectangle(600+10, 400+10, 200-20, 200-20, white);

  // The bars that change depending on x and y
  int x_divided=x/10;
  int y_divided=y/10;
  drawRectangle(600+20,           400+30,  y_divided, 20, black);
  drawRectangle(800-20-x_divided, 400+30,  x_divided, 20, black);
  drawRectangle(600+20,           400+60,  x_divided, 20, black);
  drawRectangle(800-20-y_divided, 400+60,  y_divided, 20, black);
  drawRectangle(600+20,           400+90,  y_divided, 20, black);
  drawRectangle(800-20-x_divided, 400+90,  x_divided, 20, black);
  drawRectangle(600+20,           400+120, x_divided, 20, black);
  drawRectangle(800-20-y_divided, 400+120, y_divided, 20, black);
  drawRectangle(600+20,           400+150, y_divided, 20, black);
  drawRectangle(800-20-x_divided, 400+150, x_divided, 20, black);
}
