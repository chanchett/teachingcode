// This lesson is little bit unusual. To make the NEXT lesson work, there are some things that need to be
// explained a little bit, but we don't care about the FULL explanation yet. So we're just going to touch on
// a variety of subjects so you know vaguely what they are, and they'll get explained in a lot more detail
// in future lessons.


// INCLUDES
// --------
// The first thing we'll talk about is the "include directive", which looks like this:
#include "window/window_and_graphics.h"

// This tells part of the compiler to find the file "window/window_and_drawing.h" (so from the directory
// "lesson6.cpp" is in, look in the "window" directory at the "window_and_graphics.h") and act like that
// entire file is include in this file. We can use this to separate code that does different things
// in separate files, but still use all of it in the same program.


// EXTERNAL FUNCTIONS
// ------------------
// The particular file we included, "window/window_and_drawing.h" (which you can go look at if you'd like,
// it'll be a bunch of code, unsurprisingly), defines some functions which we can call because we've included
// that file. In the twist of the century, the functions we can now use deal with opening a window
// and drawing stuff on the screen.


// The functions we are going to look at are

//  open_a_window();
//  deal_with_the_window();





// Let's try just calling them to see what they do

int main(){

  printf("called before the function\n");
  
  open_a_window();

  printf("called in between the functions\n");
  
  deal_with_the_window();
  
  printf("called after the function\n");
  }

// Compile "lesson6.cpp" and run "compiled_programs\lesson6.exe" to see what this does.
// As expected given the function names, it'll open up a window, and then run until you close that window.


// open_a_window() opens up a window for our program, but that window will only be open as long as our program
// is running. If we ONLY called open_a_window and that was the whole program, when we ran the program we'd
// see a window pop up, only to close instantly since our program finished running right away. If you look
// at the text that gets printed when the program is run, the first two lines of text get printed right away,
// but the last one doesn't get printed until after you close the window, just like we said.





// GRAPHICS FUNCTIONS
// ------------------
// Okay, we can open a window, but we can't do anything with it yet, which doesn't do us much good.
// We wanted to be able to draw stuff. So now we're going to look at a couple more functions:

// clearScreen
// drawRectangle
// drawLine


// clearScreen is pretty self explanatory: it clears the screen (here to the color white).

// drawRectangle takes 5 arguments: int x, int y, int width, int height, Color color
// x and y are how many pixels to the right and down the rectangle will be drawn from the top left corner of the
// screen.
// width and height are the width and height of the rectangle.
// color is a type of variable we haven't seen before. For now, "window_and graphics.h" defines 8 variables:
// red, orange, yellow, green, blue, purple, black, and white, which we can use to tell the rectangle a color.

// drawLine takes a similar 5 arguments: int x1, int y1, int x2, int y2, Color color
// x1 and y1 are the pixel coordinates of the start of the line
// x2 and y2 are the pixel coordinates of the end of the line
// color is just like the color of rect




// Let's use these functions to do some stuff!
// Comment out the main() function declaration above, and uncomment the one below.

/*
int main(){
  open_a_window();
  // any graphics functions we call need to be in between when we open the window and when we handle input
  // from the window. Call them before, and the window doesn't exist to draw them to; call them after and
  // the window will close because the program has ended.

  // clear the screen, so it's all white instead of black.
  clearScreen();


  // This creates the cascade of rainbow squares
  drawRectangle(  0,  0, 100, 100, red);
  drawRectangle(100, 10, 100, 100, orange);
  drawRectangle(200, 20, 100, 100, yellow);
  drawRectangle(300, 30, 100, 100, green);
  drawRectangle(400, 40, 100, 100, blue);
  drawRectangle(500, 50, 100, 100, purple);



  // This creates the black outline
  drawRectangle(200, 200, 200, 200, black);
  drawRectangle(210, 210, 180, 180, white);



  // This creates the pattern of lines inside the outline.
  drawLine(220, 220, 380, 380, red);
  drawLine(300, 220, 380, 380, orange);
  drawLine(300, 220, 220, 380, yellow);
  drawLine(380, 300, 220, 380, green);
  drawLine(380, 300, 220, 300, blue);
  drawLine(220, 300, 380, 220, purple);

  
  deal_with_the_window();
}
*/


// Awesome! We have a window, and we can draw pretty things. Try messing around with the arguments to the functions
// to start understanding how the arguments affect what's drawn.











// Once you've messed around with the graphics some, move on to lesson7.cpp!
