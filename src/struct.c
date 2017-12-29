#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

#include "struct.h"
#include "main.h"

static struct obj *obj_init(const char *imgfile,
                            void (*update)(struct obj *self, struct scene *s))
{
  struct obj *res = malloc(sizeof(struct obj));
  if (!res)
    perror(NULL);

  SDL_Surface *surf = IMG_Load(imgfile);
  if (!surf)
    perror(NULL);
  res->tex = SDL_CreateTextureFromSurface(get_renderer(), surf);
  if (!res->tex)
    perror(NULL);
  SDL_FreeSurface(surf);

  res->rect = NULL;
  res->update = update;
  res->next = NULL;

  return res;
}

static void obj_free(struct obj *self)
{
  SDL_DestroyTexture(self->tex);
  free(self);
}

static void obj_set_pos(struct obj *self, int x, int y)
{
  self->rect->x = x;
  self->rect->y = y;
}

static void obj_set_dims(struct obj *self, int width, int height)
{
  self->rect->w = width;
  self->rect->h = height;
}

void scene_add_obj(struct scene *s, enum obj_type type)
{
}
