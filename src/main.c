#include "main.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr,"SDL initialization failed: %s\n",SDL_GetError());
    return -1;
  }
  
  SDL_Window *window = SDL_CreateWindow(
    "Game",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    800,
    600,
    SDL_WINDOW_SHOWN);

  if (!window) {
    fprintf(stderr, "Window creation failed: %s\n",SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED
  );

  if (!renderer) {
    fprintf(stderr, "Renderer creation failed: %s\n",SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_SetRenderDrawColor(renderer,255,0,0,255);
  SDL_RenderClear(renderer);

  SDL_Rect rect = {100,100,200,200};
  SDL_RenderFillRect(renderer,&rect);

  SDL_RenderPresent(renderer);

  SDL_Delay(10000);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
