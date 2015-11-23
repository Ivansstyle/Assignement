#ifndef INVADER_H__
#define INVADER_H__

enum InvaderType{TYPE1,TYPE2,TYPE3};

#define SPRITEWIDTH 30
#define SPRITEHEIGHT 30
#define COLS 11
#define ROWS 5
#define GAP 10

typedef struct
{
  SDL_Rect pos;
  int active;
  int frame;
  enum InvaderType type;
}Invader;



//Creating a new structure for the defender;
enum InputControl{MOVE_LEFT,MOVE_RIGHT,SHOOT};

typedef struct
{
    SDL_Rect pos_def; //chech for correctness!
    int alive; //if 0 = print game over on the screen
    enum InputControl defender_event;
}Defender;

//Structure for info display;
typedef struct
{
    int lives;
}Display; //Will work on it after.

#endif

