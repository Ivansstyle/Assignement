#ifndef INVADER_H__
#define INVADER_H__

//ENUMERATORS
enum MissileType{M1,M2,M3};
enum InvaderType{TYPE1,TYPE2,TYPE3};
enum BOOL{FALSE,TRUE};
enum InputControl{NONE,MOVE_LEFT,MOVE_RIGHT,SHOOT};

//DEFENITIONS
#define MISSILEHEIGHT 20
#define MISSILEWIDTH 5
#define SPRITEWIDTH 30
#define SPRITEHEIGHT 30
#define COLS 11
#define ROWS 5
#define GAP 10
#define DefenderSPEED 30
#define MissileSPEED 7
#define SPEED 1
#define ANIMATIONSPEED 15
#define InvadersSPEED_AccIndx 5

//Invader Structure
typedef struct
{
  SDL_Rect pos;
  int active;
//  int frame; // no need for frame
  enum InvaderType type;
}Invader;

//Invader Missile Structure
typedef struct
{
    SDL_Rect posM;
    enum BOOL activeM;
    enum MissileType type;
}InvaderMissile;

//Missile Structure
typedef struct
{
    SDL_Rect pos;
    enum BOOL active;
}TypeMissile;

//Defender Structure
typedef struct
{
    SDL_Rect pos;
    enum BOOL alive; //if 0 = print game over on the screen
    enum InputControl defender_event;
}TypeDefender;

// Function Declaration


void PrintDebug(TypeDefender *Defender);
void Controls(TypeDefender *Defender);

void initializeDefender(TypeDefender *Defender);
void initializeMissile(TypeMissile *Missile);
void initializeInvaders(Invader invaders[ROWS][COLS],InvaderMissile misiiles[ROWS][COLS]);

void drawDefender(SDL_Renderer *ren, SDL_Texture *tex,TypeDefender *Defender);
void drawMissile(SDL_Renderer *ren, SDL_Texture *tex,TypeMissile *Missile);
void drawInvaders(SDL_Renderer *ren, SDL_Texture *tex,Invader invaders[ROWS][COLS]);
void DrawInvaderMissiles(SDL_Renderer *ren, SDL_Texture *tex1, InvaderMissile missiles[ROWS][COLS]);

void updateInvaders(Invader invaders[ROWS][COLS], InvaderMissile missiles[ROWS][COLS]);
void updateDefender(TypeDefender *Defender,TypeMissile *Missile);

void CollisionDetection(Invader invaders[ROWS][COLS], TypeMissile *Missile);
void CollisionDetectionDefender(TypeDefender *Defender, InvaderMissile missiles[ROWS][COLS]);

#endif

