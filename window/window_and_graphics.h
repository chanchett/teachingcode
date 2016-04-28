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

uint32 makeColor(uint8 r, uint8 g, uint8 b){
  return (r << 16) + (g << 8) + (b << 0);
}

uint32 lightenColor(uint32 color){
  uint8 r=(color & 0xFF0000)>>16;
  uint8 g=(color & 0x00FF00)>>8;
  uint8 b=(color & 0x0000FF)>>0;
  r+=(255-r)>>1;
  g+=(255-g)>>1;
  b+=(255-b)>>1;
  return (r << 16) + (g << 8) + (b << 0);
}

uint32 blue=makeColor(0x00, 0x00, 0xFF);
uint32 red=makeColor(0xFF, 0x00, 0x00);
uint32 green=makeColor(0x00, 0xFF, 0x00);
uint32 orange=makeColor(0xFF, 0x88, 0x00);
uint32 yellow=makeColor(0xFF, 0xFF, 0x00);
uint32 purple=makeColor(0xFF, 0x00, 0xFF);
uint32 black=makeColor(0x00, 0x00, 0x00);
uint32 white=makeColor(0xFF, 0xFF, 0xFF);

void setRenderColorFromUInt32(uint32 c){
  SDL_SetRenderDrawColor( gRenderer, (c & 0xFF0000) >> 16 , (c & 0x00FF00) >> 8, (c & 0x0000FF) >> 0, 0xFF );
}

SDL_Color SDL_ColorFromUInt32(uint32 c){
  SDL_Color result = {(uint8)((c & 0xFF0000) >> 16) , (uint8)((c & 0x00FF00) >> 8), (uint8)((c & 0x0000FF) >> 0)};
  return result;
}

void drawRectangle(int32 minX, int32 minY, int32 maxX, int32 maxY, uint32 c){
  SDL_Rect fillRect = { minX, minY, maxX, maxY };
  setRenderColorFromUInt32(c);
  SDL_RenderFillRect( gRenderer, &fillRect );
}

void drawLine(int32 minX, int32 minY, int32 maxX, int32 maxY, uint32 c){
  setRenderColorFromUInt32(c);
  SDL_RenderDrawLine( gRenderer, minX, minY, maxX, maxY);
}

uint32 visuals_background_color = makeColor(0xFF, 0xFF, 0xFF);

void clearScreen(){
  uint32 c=visuals_background_color;
  setRenderColorFromUInt32(c);
  SDL_RenderClear( gRenderer );
}

void drawRectOutline(int32 minX, int32 minY, int32 maxX, int32 maxY, uint32 c){
  drawLine(minX, minY, minX, maxY, c);
  drawLine(maxX, minY, maxX, maxY, c);
  drawLine(minX, minY, maxX, minY, c);
  drawLine(minX, maxY, maxX, maxY, c);
}

void drawText(int32 minX, int32 minY, char * text, uint32 c){
  SDL_Color color = SDL_ColorFromUInt32(c);
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

void called_sixty_times_a_second(int32 milliseconds, int x, int y, bool clicked, bool a, bool b);


int32 mouse_x=0;
int32 mouse_y=0;
bool mouse_clicked;
bool button_z_down;
bool button_x_down;

  
void handleSDLEvents(game_input *ks){
  SDL_Event e;
  
  //Handle events on queue
  while( SDL_PollEvent( &e ) != 0 )
    {
      if( e.type == SDL_QUIT )
	{
	  ks->quit_requested = true;
	}
      else if( e.type == SDL_MOUSEMOTION)
	{
	  mouse_x=e.motion.x;
	  mouse_y=e.motion.y;
	}
      else if( e.type == SDL_MOUSEBUTTONDOWN)
	{
	  mouse_clicked=true;
	}
      else if( e.type == SDL_MOUSEBUTTONUP)
	{
	  mouse_clicked=false;
	}
      else if( e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
	{
	  bool state=e.type == SDL_KEYDOWN;

	  if(SDLK_z==e.key.keysym.sym){
	    button_z_down=state;
	  }
	  if(SDLK_x==e.key.keysym.sym){
	    button_x_down=state;
	  }

	  
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

	#ifdef FUNCTIONS_ARE_DEFINED
	clearScreen();
	called_sixty_times_a_second(SDL_GetTicks(), mouse_x, mouse_y, mouse_clicked, button_z_down, button_x_down);
	#endif
	
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
