#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

extern struct vec2;
extern struct object;
extern struct object player;

extern char input_map[12];

extern double last_frame;
extern double delta_time;

extern SDL_Event event;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

void draw(double x,double y);
void set_color(char color);

int init();

void events();
void physics();
void render();

void update();

void quit();

int main(int argc, char *argv[]);

#endif
