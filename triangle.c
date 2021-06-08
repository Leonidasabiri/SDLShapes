#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window   *window   = NULL;
SDL_Renderer *renderer = NULL;

SDL_bool quit = SDL_FALSE; 
SDL_Event e;

float playPosX, playPosY;

typedef struct triangle
{
 void(*draw)(SDL_Renderer *render,float length);
}Triangle;

void drawTriangle(SDL_Renderer *render,float length)
{
	float y;
	float decFactor = 300-(length/2); 
	float rightSim  = 300+length/2;
	float pos = 300;
	for(float x = 300-(length/2); x < 300; x+=0.5)
	{	
		SDL_RenderDrawPoint(render,x,300);
		SDL_RenderDrawPoint(render,rightSim-(x-(decFactor)),300);
		pos -= 1;
		SDL_RenderDrawPoint(render,x,pos);
		SDL_RenderDrawPoint(render,rightSim-(x-(decFactor)),pos);
		SDL_RenderPresent(render);
	}	
}

int main(int ac,char **av)
{
   window   = SDL_CreateWindow("Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,600,SDL_WINDOW_RESIZABLE); 
   renderer = SDL_CreateRenderer(window,-1,0);

   Triangle tri = {drawTriangle};
	
   while(!quit)
   {
     SDL_SetRenderDrawColor(renderer,255,0,0,0);
     tri.draw(renderer,140);

     SDL_WaitEvent(&e);
     if(e.type == SDL_QUIT)
	  quit = SDL_TRUE;
   }   
   
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   SDL_Quit();
   return EXIT_SUCCESS;
}
