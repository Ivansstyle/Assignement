#ifndef INVADER_H__
#define INVADER_H__

//ENUMERATORS
enum InvaderType{TYPE1,TYPE2,TYPE3};
enum BOOL{FALSE,TRUE};
enum InputControl{NONE,MOVE_LEFT,MOVE_RIGHT,SHOOT};

//DEFENITIONS
#define SPRITEWIDTH 30
#define SPRITEHEIGHT 30
#define COLS 11
#define ROWS 5
#define GAP 10
#define DefenderSPEED 30
#define MissileSPEED 5

//Creating a new structure for the defender
typedef struct
{
  SDL_Rect pos;
  int active;
  int frame;
  enum InvaderType type;
}Invader;

//Missile structure
typedef struct{
    SDL_Rect pos;
    enum BOOL active;
}TypeMissile;



typedef struct
{
    SDL_Rect pos; //chech for correctness!
    enum BOOL alive; //if 0 = print game over on the screen
    enum InputControl defender_event;

}TypeDefender;

//Structure for info display;
#endif

