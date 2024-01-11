#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdio.h>
#include "main.h"

char input_map[12];

int last_frame;
int delta_time;

SDL_Event event;
SDL_Window *window;
SDL_Renderer *renderer;

void draw(float x,float y) {
  SDL_RenderDrawPoint(renderer,round(x),round(y));
}

void set_color(char color) {
  if (color) SDL_SetRenderDrawColor(renderer,199,240,216,255);
  else SDL_SetRenderDrawColor(renderer,67,82,61,255);
}

int init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr,"SDL initialization failed: %s\n",SDL_GetError());
    return -1;
  }
  
  if (SDL_CreateWindowAndRenderer(84,48,0,&window,&renderer)) {
    fprintf(stderr,"Window or renderer initialization failed: %s\n",SDL_GetError());
    return -1;
  }

  SDL_SetWindowTitle(window,"Game!");
  SDL_ShowCursor(0);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");

  return 0;
}

void event_handler() {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_w:
          input_map[0] = 1;
        case SDLK_a:
          input_map[1] = 1;
        case SDLK_s:
          input_map[2] = 1;
        case SDLK_d:
          input_map[3] = 1;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_w:
          input_map[0] = 0;
        case SDLK_a:
          input_map[1] = 0;
        case SDLK_s:
          input_map[2] = 0;
        case SDLK_d:
          input_map[3] = 0;
      }
      break;
  }
}

void render() {
  SDL_SetWindowMinimumSize(window,84,48);
  SDL_SetWindowMinimumSize(window,84,48);
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);
 
  set_color(0);
  SDL_Rect rect = {0,0,84,48};
  SDL_RenderFillRect(renderer,&rect);
  
  set_color(1);
  for (int i = 0 ; i < 84 ; ++i) draw(i,47);

  SDL_RenderPresent(renderer);
}

void update() {
  last_frame = SDL_GetTicks();
  char quit = 0;

  SDL_Delay(10);

  while (!quit) {
    delta_time = SDL_GetTicks() - last_frame;
    last_frame += delta_time;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = 1;
        break;
      }
    }

    render();
  }
}

void quit() {
  if (window) SDL_DestroyWindow(window);
  if (renderer) SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  int error = init();
  if (error) return error;

  update();
  quit();

  return 0;
}
