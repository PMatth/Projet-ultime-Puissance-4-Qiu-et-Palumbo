#ifndef __SDLP4__CSurface__
#define __SDLP4__CSurface__

#include <stdio.h>
#include "SDL/SDL.h"

// Surface management purposes

class CSurface {
public:
    CSurface();
    
    static SDL_Surface* OnLoad(char*File);
    
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_src, int X, int Y);
        
    static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
  
};




#endif /* defined(__SDLP4__CSurface__) */
