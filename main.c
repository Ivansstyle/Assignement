#include <SDL.h>
//#include "/usr/local/include/SDL2/SDL_image.h"
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "invader.h"



// include the map for the maze.
// the width of the screen taking into account the maze and block
#define WIDTH 800
// the height of the screen taking into account the maze and block
#define HEIGHT 600


int test = 0;

void PrintDebug(TypeDefender *Defender);
void Controls(TypeDefender *Defender);
int quit=0;

void initializeDefender(TypeDefender *Defender);
void initializeMissile(TypeMissile *Missile);
void updateDefender(TypeDefender *Defender,TypeMissile *Missile);
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex,TypeDefender *Defender);
void drawMissile(SDL_Renderer *ren, SDL_Texture *tex,TypeMissile *Missile);



void initializeInvaders(Invader invaders[ROWS][COLS]);
void updateInvaders(Invader invaders[ROWS][COLS]);
void drawInvaders(SDL_Renderer *ren, SDL_Texture *tex,Invader invaders[ROWS][COLS]);
void CollisionDetection(Invader invaders[ROWS][COLS], TypeMissile *Missile);
int main()
{
  Invader invaders[ROWS][COLS];
  TypeDefender Defender;
  TypeMissile Missile;
  printf("Programm Started.\n");

  initializeDefender(&Defender);
  initializeInvaders(invaders);
  initializeMissile(&Missile);

  // initialise SDL and check that it worked otherwise exit
  // see here for details http://wiki.libsdl.org/CategoryAPI
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    printf("%s\n",SDL_GetError());
    return EXIT_FAILURE;
  }
  // we are now going to create an SDL window

  SDL_Window *win = 0;
  win = SDL_CreateWindow("Invaders", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (win == 0)
  {
    printf("%s\n",SDL_GetError());
    return EXIT_FAILURE;
  }
  // the renderer is the core element we need to draw, each call to SDL for drawing will need the
  // renderer pointer
  SDL_Renderer *ren = 0;
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // check to see if this worked
  if (ren == 0)
  {
    printf("%s\n",SDL_GetError() );
    return EXIT_FAILURE;
  }
  // this will set the background colour to white.
  // however we will overdraw all of this so only for reference
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

//  // SDL image is an abstraction for all images
  SDL_Surface *image;
//  // we are going to use the extension SDL_image library to load a png, documentation can be found here
//  // http://www.libsdl.org/projects/SDL_image/
  image=IMG_Load("InvaderA2.bmp");
  if(!image)
  {
    printf("IMG_Load: %s\n", IMG_GetError());
    return EXIT_FAILURE;
  }
//  // SDL texture converts the image to a texture suitable for SDL rendering  / blitting
//  // once we have the texture it will be store in hardware and we don't need the image data anymore

  SDL_Texture *tex = 0;
  tex = SDL_CreateTextureFromSurface(ren, image);
  // free the image
  SDL_FreeSurface(image);



  // now we are going to loop forever, process the keys then draw


  while (quit !=1)
  {
     Controls(&Defender);
     PrintDebug(&Defender);

     // now we clear the screen (will use the clear colour set previously)
     SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
     SDL_RenderClear(ren);

  updateDefender(&Defender, &Missile);
  updateInvaders(invaders);
  CollisionDetection(invaders, &Missile);

    drawDefender(ren,tex,&Defender);
    drawInvaders(ren,tex,invaders);
    drawMissile(ren,tex,&Missile);

  // Up until now everything was drawn behind the scenes.
  // This will show the new, red contents of the window.
   SDL_RenderPresent(ren);

  }

  SDL_Quit();
  return 0;
}
// Inintialising Defender.
void initializeDefender(TypeDefender *Defender)
{
  SDL_Rect pos;
  pos.w=SPRITEWIDTH;
  pos.h=SPRITEHEIGHT;
  pos.x=WIDTH/2-30;
  pos.y=HEIGHT-50;

  Defender->defender_event = NONE;
  Defender->alive = TRUE;
  Defender->pos = pos;

}

//Initializing Missile
void initializeMissile(TypeMissile *Missile)
{
    SDL_Rect pos;
    pos.w=SPRITEHEIGHT;
    pos.h=SPRITEHEIGHT;
    pos.x=WIDTH/2-30;
    pos.y=HEIGHT-SPRITEHEIGHT-50;

    Missile->active = FALSE;
    Missile->pos = pos;
}

//Updating defender/Missile
void updateDefender(TypeDefender *Defender, TypeMissile *Missile)
{

    if (Defender->defender_event == MOVE_LEFT)
    {
        if (Defender->pos.x > DefenderSPEED)
        {
            Defender->pos.x-=DefenderSPEED;
        }
    }
    if (Defender->defender_event == MOVE_RIGHT)
    {
        if (Defender->pos.x < WIDTH - Defender->pos.w - DefenderSPEED)
        {
            Defender->pos.x+=DefenderSPEED;
        }
    }


    if (Defender->defender_event == SHOOT)
    {
        Missile->active = TRUE;
    }

    if (Missile->active == FALSE)
    {
        Missile->pos.x = Defender->pos.x + ((Defender->pos.w - Missile->pos.w) / 2);
        Missile->pos.y = Defender->pos.y - Defender->pos.h;
    }
    if (Missile->active == TRUE)
    {
        if (Missile->pos.y> 0 - Missile->pos.h)
        {
            Missile->pos.y = Missile->pos.y - MissileSPEED;
        }
        else {Missile->active = FALSE;}

       Defender->defender_event = NONE;
       if (Missile->active == TRUE){
           printf ("missile active\t");
           printf ("Missile X:%d Missile Y:%d\n", Missile->pos.x, Missile->pos.y);
       }
    }
    Defender->defender_event = NONE;
}

//Detecting Collision
void CollisionDetection(Invader invaders[ROWS][COLS], TypeMissile *Missile)
{
       // A - invader B - missile //
       // Adl - means A DOWN LEFT //
    int A_dlX = 0; // A Down left
    int A_drX = 0; // A Down right
    int A_dlY = 0;
    int A_ulY = 0;

    int B_ulX = 0;
    int B_urX = 0;
    int B_ulY = 0;
    int B_dlY = 0;

    B_ulX = Missile->pos.x;
    B_urX = Missile->pos.x + Missile->pos.w;
    B_dlY = Missile->pos.y + Missile->pos.h;
    B_ulY = Missile->pos.y;

    if (Missile->active == TRUE)
    {
        printf("!!!invader X: %3d\n",invaders[3][9].pos.x);
        printf("!!!invader Y: %3d\n",invaders[3][9].pos.y);
        //int collision = 0;
        for (int r=ROWS;r>=0; --r)
        {

            for (int c=COLS;c>=0; --c)
            {
                A_dlX = invaders[r][c].pos.x;
                A_drX = invaders[r][c].pos.x + invaders[r][c].pos.w;
                A_dlY = invaders[r][c].pos.y + invaders[r][c].pos.h;
                A_ulY = invaders[r][c].pos.y;

                if (B_ulX >= A_dlX)
                {
                    if (B_urX <= A_drX)
                    {
                        if (B_ulY >= A_dlY)
                        {
                            if (B_ulY <= A_ulY)
                            {
                                printf("invader X: %3d\n",invaders[r][c].pos.x);
                                printf("invader Y: %3d\n",invaders[r][c].pos.y);


                                //Collision
                                printf("Collision!!!\n");
                                printf("A_dlX = %3d A_drX = %3d A_dlY = %3d A_ulY = %3d \nB_ulX = %3d B_urX = %3d B_dlY = %3d B_ulY = %3d\n",
                                        A_dlX, A_drX, A_dlY, A_ulY, B_ulX, B_urX, B_dlY, B_ulY);
                            }
                        }
                    }
                }


//                if (invaders[r][c].pos.x <= Missile->pos.x)
//                {
//                    if (invaders[r][c].pos.x + invaders[r][c].pos.w >= Missile->pos.x)
//                    {
//                        if (invaders[r][c].pos.y >= Missile->pos.y)
//                        {
//                            if(invaders[r][c].pos.y + invaders[r][c].pos.h <= Missile->pos.y)
//                            {
//                                //Collision
//                                collision = 1;
//                                invaders[r][c].active = 0;
//                            }
//                        }
//                    }
//                }
//                if (invaders[r][c].pos.x + invaders[r][c].pos.w >= Missile->pos.x + Missile->pos.w)
//                {
//                    if (invaders[r][c].pos.x <= Missile->pos.x + Missile->pos.w)
//                    {
//                        if (invaders[r][c].pos.y >= Missile->pos.y)
//                        {
//                            if(invaders[r][c].pos.y + invaders[r][c].pos.h <= Missile->pos.y)
//                            {
//                                //Collision
//                                if (collision == 0)
//                                    collision = 1;
//                                if (invaders[r][c].active == 1)
//                                    invaders[r][c].active = 0;
//                            }
//                        }
//                    }
//                }
//            if (collision == 1)
//                {
//                    r = -1;
//                Missile->active = FALSE;
//                }
            }
        }

    }
}

// Drawing defender
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex,TypeDefender *Defender)
{
  SDL_Rect SrcR;
  SrcR.x=0;
  SrcR.y=0;
  SrcR.w=88;
  SrcR.h=64;
  SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
  SDL_RenderFillRect(ren,&Defender->pos);
  SDL_RenderCopy(ren, tex,&SrcR, &Defender->pos);

}
//Drawing Missile
void drawMissile(SDL_Renderer *ren, SDL_Texture *tex,TypeMissile *Missile)
{
  SDL_Rect SrcR;
  SrcR.x=0;
  SrcR.y=0;
  SrcR.w=88;
  SrcR.h=64;
  SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
  SDL_RenderFillRect(ren,&Missile->pos);
  SDL_RenderCopy(ren, tex,&SrcR, &Missile->pos);
}

void initializeInvaders(Invader invaders[ROWS][COLS])
{
  SDL_Rect pos;
  pos.w=SPRITEWIDTH;
  pos.h=SPRITEHEIGHT;
  int ypos=GAP;

  for(int r=0; r<ROWS; ++r)
  {
    int xpos=GAP;
    for(int c=0; c<COLS; ++c)
    {
      pos.x=xpos+SPRITEWIDTH;
      pos.y=ypos+SPRITEHEIGHT;
      xpos+=(GAP+SPRITEWIDTH);
      invaders[r][c].pos=pos;
      invaders[r][c].active=1;
      invaders[r][c].frame=0;
      if(r==0)
        invaders[r][c].type=TYPE1;
      else if(r==1 || r==2)
        invaders[r][c].type=TYPE2;
      else
        invaders[r][c].type=TYPE3;

    }
    ypos+=(GAP+SPRITEHEIGHT);
  }
}


void drawInvaders(SDL_Renderer *ren, SDL_Texture *tex, Invader invaders[ROWS][COLS])
{
  SDL_Rect SrcR;
  SrcR.x=0;
  SrcR.y=0;
  SrcR.w=88;
  SrcR.h=64;
  for(int r=0; r<ROWS; ++r)
  {
    for(int c=0; c<COLS; ++c)
    {
      switch(invaders[r][c].type)
      {
      case TYPE1 : SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); break;
      case TYPE2 : SDL_SetRenderDrawColor(ren, 0, 255, 0, 255); break;
      case TYPE3 : SDL_SetRenderDrawColor(ren, 0, 0, 255, 255); break;
      }
      SDL_RenderFillRect(ren,&invaders[r][c].pos);
      SDL_RenderCopy(ren, tex,&SrcR,&invaders[r][c].pos);


    }
  }
}


void updateInvaders(Invader invaders[ROWS][COLS])
{
  enum DIR{FWD,BWD};
  static int DIRECTION=FWD;
  int yinc=0;
  if(invaders[0][COLS].pos.x>=(WIDTH-SPRITEWIDTH)-(COLS*(SPRITEWIDTH+GAP)))
  {
    DIRECTION=BWD;
    yinc=GAP;

  }
  else if(invaders[0][0].pos.x<=SPRITEWIDTH)
  {
    DIRECTION=FWD;
    yinc=GAP;

  }

  for(int r=0; r<ROWS; ++r)
  {
    for(int c=0; c<COLS; ++c)
    {
      if(DIRECTION==FWD)
        invaders[r][c].pos.x+=1;
      else
        invaders[r][c].pos.x-=1;
      invaders[r][c].pos.y+=yinc;

    }
  }
}

void PrintDebug(TypeDefender *Defender)
{
    if (Defender->defender_event == SHOOT){
        printf("Defender: command shoot\n");
    }
    if (Defender->defender_event == MOVE_LEFT){
        printf ("Defender: command left\n");
    }
    if (Defender->defender_event == MOVE_RIGHT){
        printf("Defender: command right\n");
    }
}

//All SDL_Events now moved here,so not to interrupt with other calculations and for easy access.
void Controls(TypeDefender *Defender)
{
    SDL_Event event;
    // grab the SDL even (this will be keys etc)
    while (SDL_PollEvent(&event))
    {
      // look for the x of the window being clicked and exit
      if (event.type == SDL_QUIT)
        quit = 1;
      // check for a key down
      if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        // if we have an escape quit
        case SDLK_ESCAPE : quit=1;
            break;

        case SDLK_LEFT : Defender->defender_event = MOVE_LEFT;
            break;
        case SDLK_RIGHT : Defender->defender_event = MOVE_RIGHT;
            break;
        case SDLK_SPACE : Defender->defender_event = SHOOT;
            break;


         // else Defender.defender_event = NONE;
        }
      }
    }
    if (test == 1){
        Defender->defender_event = SHOOT;
        test = 0;
    }
}
