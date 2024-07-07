#include <SDL2/SDL.h>
#include <stdio.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *initWindow(void);
SDL_Surface *loadImage(void);
void close(SDL_Surface *, SDL_Window *);

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;

  window = initWindow();
  if (window == NULL) {
    printf("Window failed: %s", SDL_GetError());
    return 0;
  }

  screenSurface = SDL_GetWindowSurface(window);
  SDL_Surface *loadedImage = loadImage();

  if (loadedImage == NULL) {
    printf("Image loading failed: %s", SDL_GetError());
  }

  SDL_BlitSurface(loadedImage, NULL, screenSurface, NULL);
  SDL_UpdateWindowSurface(window);

  SDL_Event e;
  int quit = 0;
  while (quit == 0) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = 1;
    }
  }
  close(loadedImage, window);
}

SDL_Window *initWindow(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return NULL;
  }

  return SDL_CreateWindow("ascC", SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_SHOWN);
}

SDL_Surface *loadImage(void) { return SDL_LoadBMP("./assets/gato.bmp"); }
void close(SDL_Surface *image, SDL_Window *window) {
  SDL_FreeSurface(image);

  SDL_DestroyWindow(window);

  SDL_Quit();
}
