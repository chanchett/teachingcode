#include <SDL.h>
#include <SDL_ttf.h>

#undef main




#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64

#include <stdio.h>
#include <string>
#include <cmath>


#define uint32 unsigned int
#define uint64 unsigned long

#define int32 int
#define int64 long

#define uint8 unsigned char
#define uint16 unsigned short

#define int8 signed char
#define int16 signed short

#define real32 float
#define real64 double

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))


// MSVC defines this in winsock2.h!?
typedef struct timeval_hack {
    long tv_sec;
    long tv_usec;
} timeval_hack;

int gettimeofday(struct timeval_hack * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}

struct time_data {
  timeval_hack old;
  timeval_hack current;
  uint32 delta_index=0;
  uint32 delta_array[10];

  real32 frame_delta;
  real32 frame_avg;

  bool init=false;
};

bool shouldUpdate(time_data *time){
  if(!time->init){
    gettimeofday(&time->old, NULL);
    time->init=true;
  }
  
  gettimeofday(&time->current, NULL);
  int32 time_delta=(time->current.tv_sec-time->old.tv_sec)*1000000+time->current.tv_usec-time->old.tv_usec;
  if(time_delta<15000){ return false; }

  time->old=time->current;
  
  time->delta_array[time->delta_index++]=time_delta;
  if(time->delta_index>ArrayCount(time->delta_array)){ time->delta_index=0; }

  time->frame_delta=time_delta/1000000.f;
  
  for(int i=0;i<ArrayCount(time->delta_array);i++){
    time->frame_avg+=time->delta_array[i];
  }
  time->frame_avg=time->frame_avg/ArrayCount(time->delta_array);
  time->frame_avg=1000000/time->frame_avg;
  
  return true;
}





struct key_state {
  int key_changed;
  bool is_down;
};

#define VISUALS_INPUT_KEYS(keystates)		\
struct game_input { \
  bool quit_requested;				\
  union{ \
    key_state keys[VISUALS_NUM_KEYS]; \
    struct { \
      keystates \
    }; \
  }; \
}; \

#define VISUALS_INPUT_MAPPING(...) \
  const int VISUALS_KEY_MAPPING[VISUALS_NUM_KEYS]={__VA_ARGS__};




#define VISUALS_NUM_KEYS 8

bool DRAW_DEBUG=true;
bool PAUSE_DRAW=false;

VISUALS_INPUT_KEYS(
      key_state up;
      key_state down;
      key_state left;
      key_state right;
      key_state action1;
      key_state action2;
      key_state mapKey;
      key_state debugView;
      )

VISUALS_INPUT_MAPPING(
      SDLK_UP,
      SDLK_DOWN,
      SDLK_LEFT,
      SDLK_RIGHT,
      SDLK_z,
      SDLK_x,
      SDLK_q,
      SDLK_w
      )


time_data td;
int count=0;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 700;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

TTF_Font* font;

char *current_string;

union Color {
  struct {
    int32 r, g, b;
  };
  int32 E[3];
};

void clear_game_input(game_input* keys){
  keys->quit_requested=false;
  for(int i=0;i<VISUALS_NUM_KEYS;i++){
    keys->keys[i].key_changed=0;
  }
}

inline bool pressed(key_state ks){
  return ks.is_down && ks.key_changed>0;
}

char font_name[64];

bool init()
{
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				/*
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
					}*/

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				  {
				    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				    success = false;
				  }
				else
				  {
				    font=TTF_OpenFont(font_name, 16);
				    
				    if(font==NULL){
				      printf("No font loaded\n");
				      success = false;
				    }
				  }
			}
		}
	}

	return 0;
}

bool SDL_inited=false;

bool setupSDL(char* font_n){
  memcpy(font_name, font_n, 64);
  SDL_inited=init();
  return SDL_inited;
}

bool open_a_window(){
  SDL_inited=setupSDL("./Samson.ttf");
  return SDL_inited;
}

void closeSDL()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	SDL_Quit();
}

void drawRect(int32 minX, int32 minY, int32 maxX, int32 maxY, int32 R, int G, int B){
  SDL_Rect fillRect = { minX, minY, maxX-minX, maxY-minY };
  SDL_SetRenderDrawColor( gRenderer, R, G, B, 0xFF );		
  SDL_RenderFillRect( gRenderer, &fillRect );
}

void drawRect(int32 minX, int32 minY, int32 maxX, int32 maxY, Color c){
  drawRect(minX, minY, maxX, maxY, c.r, c.g, c.b);
}

void drawLine(int32 minX, int32 minY, int32 maxX, int32 maxY, int32 R, int G, int B){
  SDL_SetRenderDrawColor( gRenderer, R, G, B, 0xFF );
  SDL_RenderDrawLine( gRenderer, minX, minY, maxX, maxY);
}

void drawLine(int32 minX, int32 minY, int32 maxX, int32 maxY, Color c){
  drawLine(minX, minY, maxX, maxY, c.r, c.g, c.b);
}

Color visuals_background_color = {0xFF, 0xFF, 0xFF};

void clearScreen(){
  SDL_SetRenderDrawColor( gRenderer, visuals_background_color.r, visuals_background_color.g, visuals_background_color.b, 0xFF );
  SDL_RenderClear( gRenderer );
}

void drawRectOutline(int32 minX, int32 minY, int32 maxX, int32 maxY, int32 R, int G, int B){
  drawLine(minX, minY, minX, maxY, R, G, B);
  drawLine(maxX, minY, maxX, maxY, R, G, B);
  drawLine(minX, minY, maxX, minY, R, G, B);
  drawLine(minX, maxY, maxX, maxY, R, G, B);
}

void drawRectOutline(int32 minX, int32 minY, int32 maxX, int32 maxY, Color c){
  drawRectOutline(minX, minY, maxX, maxY, c.r, c.g, c.b);
}

void drawRectToggle(int32 minX, int32 minY, int32 maxX, int32 maxY, int32 R, int G, int B, bool b){
  if(b){
    drawRectOutline(minX, minY, maxX, maxY, R, G, B);
  }else{
    drawRect(minX, minY, maxX, maxY, R, G, B);
  }
}

void drawRectToggle(int32 minX, int32 minY, int32 maxX, int32 maxY, Color c, bool b){
  drawRectToggle(minX, minY, maxX, maxY, c.r, c.g, c.b, b);
}

void drawText(int32 minX, int32 minY, char * text, uint8 R, uint8 G, uint8 B){
  SDL_Color color = {R, G, B};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);

  SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
  
  SDL_Rect Message_rect;
  Message_rect.x = minX;
  Message_rect.y = minY;
  Message_rect.w = 16*strlen(text);
  Message_rect.h = 16;
  
  SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);

  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceMessage);
  //SDL_RenderDrawLine( gRenderer, minX, minY, maxX, maxY);
}

void update(game_input *input, unsigned int32 milliseconds);

void handleSDLEvents(game_input *ks){
	  
  //Event handler
  SDL_Event e;
  
  //Handle events on queue
  while( SDL_PollEvent( &e ) != 0 )
    {
      //User requests quit
      if( e.type == SDL_QUIT )
	{
	  ks->quit_requested = true;
	}
      //User presses a key
      else if( e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
	{
	  bool state=e.type == SDL_KEYDOWN;
	  bool matched=false;
	  // A switch is technically more efficient
	  // But this is much more versatile, good enough for now
	  for(int i=0;i<VISUALS_NUM_KEYS;i++){
	    if(VISUALS_KEY_MAPPING[i]==e.key.keysym.sym){
	      ks->keys[i].is_down=state;
	      ks->keys[i].key_changed++;
	      matched=true;
	      break;
	    }
	  }

	  if(current_string!=NULL){
	    if( e.type == SDL_KEYDOWN ){
	      // Using strlen is wasteful, and doesn't allow the cursor inside the text
	      // Should track cursor position
	      int cursor=strlen(current_string);
	      if((e.key.keysym.sym>='a' && e.key.keysym.sym<='z') ||
		 (e.key.keysym.sym>='0' && e.key.keysym.sym<='9') ||
		 e.key.keysym.sym==' ' ||
		 e.key.keysym.sym=='-'
		 ){
		if(cursor<64-1){
		  if(current_string[cursor]=='\0'){
		    current_string[cursor+1]='\0';
		  }
		  current_string[cursor]=e.key.keysym.sym;
		}
	      }else if(e.key.keysym.sym==8){
		if(cursor!=0){
		  current_string[cursor-1]='\0';
		}
	      }else{
		printf("%i\n", e.key.keysym.sym);
	      }
	    }
	  }else if(!matched){
	    printf("OTHER\n");
	    ks->quit_requested = true;
	    break;
	  }
	}
    }

  current_string=NULL;
}

void renderFrame(game_input *ks){
  clear_game_input(ks);
  
  //Update screen
  SDL_RenderPresent( gRenderer );
}


void deal_with_the_window()
{ 
  // TODO (hcharles): this needs to be setup someplace else? do we need access to it in main thread?
  game_input ks={};
  
  bool quit = false;
  //ks.quit_requested=false;

  while( !quit )
    {
      if(shouldUpdate(&td)){ 
	handleSDLEvents(&ks);
	
	quit=ks.quit_requested;
	
	//update(&ks, SDL_GetTicks());
	
	renderFrame(&ks);
      }else{
	// No guarantee we'll actually get this level of granularity (SDL says delay is ~10 ms) but we can ask
	SDL_Delay(1);
      }
    }
  
  //Free resources and close SDL
  closeSDL();
}

void open_a_window_and_deal_with_it(){
  open_a_window();
  deal_with_the_window();
}
