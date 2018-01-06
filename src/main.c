#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

SDL_Window *get_window(void)
{
  static SDL_Window *window;
  if (!window)
  {
    window = SDL_CreateWindow(
      "SDL2 window",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      SDL_WINDOW_OPENGL
      );

    if (window == NULL)
      errx(1, "Could not create window: %s\n", SDL_GetError());
  }
  return window;
}

SDL_Renderer *get_renderer(void)
{
  static SDL_Renderer *renderer;
  if (!renderer)
    renderer = SDL_CreateRenderer(get_window(), -1, SDL_RENDERER_ACCELERATED);
  return renderer;
}

int main(void)
{
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

  SDL_Window *window = get_window();
  SDL_Renderer *ren = get_renderer();
 
  SDL_Surface *surface = IMG_Load("data/img/mario.png");
  if (!surface)
    err(1, "Image couldn't be loaded: %s", IMG_GetError());
  SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
  SDL_FreeSurface(surface);

  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = 200;
  rect.h = 200;

  while (1)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        break;
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, texture, NULL, &rect);
    SDL_RenderPresent(ren);
  }

  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
