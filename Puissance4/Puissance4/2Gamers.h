
#ifndef __SDLP4___pGame__
#define __SDLP4___pGame__

#include <stdio.h>
#include "SDL/SDL.h"
#include <cmath>
#include "CSurface.h"

class TwoPlayers{
    
private:
    
    // We enumerate the tiles type.
    
    enum Tiles{
        Empty= 0,
        
        Red,
        Redh,
        Redv,
        Redad,
        Reddd,
        
        Yellow,
        Yellowh,
        Yellowv,
        Yellowad,
        Yellowdd
    };
    
    // We enumerate the players type (can be Bot, Human player # 1 or 2, or no one)
    
    enum PlayerT{
        None = 0,
        player1,
        player2,
        bot
    };
    
    bool Running;
    
    bool win;
    
    // We set a Grid to modelize our game; it's easier !
    
    Tiles Grid[6][7];
    
    // Here are a couple of surfaces
    
    SDL_Surface* Surf_Display; // The main display
    
    SDL_Surface *red, *yellow, *empty; // Red tile, Yellow tile or empty tile.
    
    SDL_Surface *redh, *redv, *redad, *reddd; // Red with horizontal band, resp. vertical, ascending diagonal, descending diagonal.
    SDL_Surface *yellowh, *yellowv, *yellowad, *yellowdd; // Same with yellow
    
    SDL_Surface *gameover; // Game over surface
    
    SDL_Rect backmain, quit; // Surfaces with "Back to Main" and "Quit" on the Game over surface.
    
    PlayerT Currentplayer;
    PlayerT Winner;
    PlayerT Firstplayer;
    
    Tiles P1_Tile;
    Tiles P2_Tile;
    Tiles Bot_Tile;
    Tiles CurrentTile;
    
public:
    
    TwoPlayers();
    
    int OnExecute(); // Management of events
    
    bool OnInit(); // Initialization of sprites
    
    void OnRender(); // Render the playboard
    
    void OnCleanup(); // Clearing memory
    
    void OnExit(); // Exiting SDL
    
    void Reset(); // Setting the initial game
    
    void checkmouse(SDL_MouseButtonEvent *mouse, int &watchdog); // Make the move
    
    int RowforPlay(int ColID); // Derives the row for available play
    
    bool IsColFull(int ColID); // Checks if col is full
    
    bool IsGameWon(Tiles tab[6][7]); // Checks if Game is Won
    
    bool IsBoardFull(Tiles tab[6][7]); // Check if Draw
    
    bool IsGameOver(Tiles tab[6][7]);
    
    // Determination for winning combos in respective possibilities
    
    bool HorizontalWin(Tiles tab[6][7]);
    bool VerticalWin(Tiles tab[6][7]);
    bool ADWin(Tiles tab[6][7]);
    bool DDWin(Tiles tab[6][7]);
    
    // Mark the winning combos
    
    void MarkHorizontal(Tiles tab[6][7]);
    void MarkVertical(Tiles tab[6][7]);
    void MarkAD(Tiles tab[6][7]);
    void MarkDD(Tiles tab[6][7]);
    
    // Makes the move "physically"
    
    void SetCell(int RowID, int ColID, Tiles Type);
    
};


#endif /* defined(__SDLP4___pGame__) */
