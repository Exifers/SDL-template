#ifndef STRUCT_H
# define STRUCT_H

#include <SDL2/SDL.h>

struct scene;

struct obj
{
  SDL_Texture *tex;
  SDL_Rect *rect;
  void (*update)(struct obj *self, struct scene *s);
  struct obj *next;
};

struct scene
{
  SDL_Renderer *ren;
  SDL_Event *e;
  struct obj *obj_list;
};

#endif /* !STRUCT_H */
