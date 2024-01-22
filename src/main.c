#include <math.h>
#include <stdio.h>
#include "main.h"

const char player_bitmap[8][8] = {
  "00011000",
  "00111100",
  "01111110",
  "11111111",
  "11111111",
  "01111110",
  "00111100",
  "00011000",
};

struct vec2 {double x,y;};
struct object {struct vec2 position,size;};
struct object player;

char input_map[12];

double last_frame;
double delta_time;

SDL_Event event;
SDL_Window *window;
SDL_Renderer *renderer;

void draw(double x,double y) {
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

  window = SDL_CreateWindow(
    "Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    84,48,SDL_WINDOW_MAXIMIZED);

  if (!window) {
    fprintf(stderr, "Window creation failed: %s\n",SDL_GetError());
    SDL_Quit();
    return -1;
  }

  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    fprintf(stderr, "Renderer creation failed: %s\n",SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  } 

  return 0;
}

void events() {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_w:
          input_map[0] = 1;
          break;
        case SDLK_a:
          input_map[1] = 1;
          break;
        case SDLK_s:
          input_map[2] = 1;
          break;
        case SDLK_d:
          input_map[3] = 1;
          break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_w:
          input_map[0] = 0;
          break;
        case SDLK_a:
          input_map[1] = 0;
          break;
        case SDLK_s:
          input_map[2] = 0;
          break;
        case SDLK_d:
          input_map[3] = 0;
          break;
      }
      break;
  }
}

void physics() {
  struct vec2 input_direction = {0.0,0.0};
  if (input_map[1]) --input_direction.x;
  if (input_map[3]) ++input_direction.x;

  player.position.x += input_direction.x * delta_time * 10;
  player.position.y += input_direction.y * delta_time * 10;
}

void render() {
  int width,height;
  SDL_RenderSetLogicalSize(renderer,84,48); 
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);
 
  set_color(0);
  SDL_Rect rect = {0,0,84,48};
  SDL_RenderFillRect(renderer,&rect);
  
  set_color(1);
  //draw(player.position.x,player.position.y);
  for (int i = 0 ; i ^ 8 ; ++i) for (int j = 0 ; j ^ 8 ; ++j) {
    if (player_bitmap[i][j] == '1') draw(i,j);
  }

  SDL_RenderPresent(renderer);
}

void update() {
  last_frame = SDL_GetTicks();
  char quit = 0;

  SDL_Delay(10);

  while (!quit) {
    delta_time = SDL_GetTicks() - last_frame;
    last_frame += delta_time;
    delta_time = delta_time / 1000.0;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = 1;
        break;
      }
      events();
    }
    physics();
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
