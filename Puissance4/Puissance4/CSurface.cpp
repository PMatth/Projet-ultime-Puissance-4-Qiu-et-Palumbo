
#include "SDL/SDL.h"
#include "CSurface.h"
#include <math.h>

CSurface::CSurface(){
    
}

// Function that returns a picture loaded from a certain directory

SDL_Surface* CSurface::OnLoad(char* File){
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;
    
    if ((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
        return NULL;
    }
    
    Surf_Return = SDL_DisplayFormat(Surf_Temp); // Display le temporaire
    SDL_FreeSurface(Surf_Temp); // Libérer l'espace
    
    return Surf_Return;
}

// Function that draws ("blits") a surface according to coordinates

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y){
    if (Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }
    
    SDL_Rect DestR;
    
    DestR.x = X;
    DestR.y = Y;
    
    SDL_BlitSurface(Surf_Src,NULL,Surf_Dest,&DestR);
    
    return true;
}

///// Making the "background" of a sprite transparent. 

bool CSurface::Transparent(SDL_Surface *Surf_Dest, int R, int G, int B){
    
    if (Surf_Dest == NULL) {
        return false;
    }
    
    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));
    
    return true;
    
}
