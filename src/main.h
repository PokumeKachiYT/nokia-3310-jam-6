#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

extern char input_map[12];

extern int last_frame;
extern int delta_time;

extern SDL_Event event;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

void draw(float x,float y);
void set_color(char color);

int init();

void event_handler();
void render();
void update();

void quit();

int main(int argc, char *argv[]);

#endif
