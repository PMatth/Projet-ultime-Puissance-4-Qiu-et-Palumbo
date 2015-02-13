
#include "2Gamers.h"
#include "CSurface.h"
#include "Start.h"

// We define the width and height

const int WIDTH = 700;
const int HEIGHT = 600;

// Here is the constructor. By default, the first player plays with the red tiles while the second player plays with the yellow tiles.

TwoPlayers::TwoPlayers(){
    
    Running = 1;
    red = NULL;
    yellow = NULL;
    empty = NULL;
    
    for (int i = 0; i<6; i++) {
        for (int j=0; j<7; j++) {
            Grid[i][j] = Empty;
        }
    }
    
    Winner = None;
    
    Firstplayer = player1;
    Currentplayer = player1;
    
// Defining each player's tile
    
    P1_Tile = Red;
    P2_Tile = Yellow;
    
    CurrentTile = P1_Tile;
}

// Here is the initialization for the sprites.

bool TwoPlayers::OnInit(){
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    
    if ((Surf_Display = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    
    if ((empty = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/emptyboard.bmp")) == NULL) {
        return false;
    }
    
    if ((red = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/boardred.bmp")) == NULL) {
        return false;
    }
    
    if ((yellow = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/boardyellow.bmp")) == NULL) {
        return false;
    }
    
    if ((redh = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/redh.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowh = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/yellowh.bmp")) == NULL) {
        return false;
    }
    
    if ((redv = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/redv.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowv = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/yellowv.bmp")) == NULL) {
        return false;
    }
    
    if ((redad = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/redad.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowad = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/yellowad.bmp")) == NULL) {
        return false;
    }
    
    if ((reddd = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/reddd.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowdd = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/yellowdd.bmp")) == NULL) {
        return false;
    }
    
    if ((gameover = CSurface::OnLoad("W:/Projets/Puissance4/Debug/Newsprites/GameOver.bmp")) == NULL) {
        return false;
    }

    
    // The following (backmain and quit) are for the "Game Over" Surface that occurs at the end. They are the coordinates for the "Back to Main Menu" button and "Quit Game" button.
    
    backmain.x = 93;
    backmain.y = 505;
    backmain.w = 167;
    backmain.h = 15;
    
    quit.x = 502;
    quit.y = 506;
    quit.w = 74;
    quit.h = 15;
    
    CSurface::Transparent(red, 255, 0, 255);
    CSurface::Transparent(redh, 255, 0, 255);
    CSurface::Transparent(redv, 255, 0, 255);
    CSurface::Transparent(redad, 255, 0, 255);
    CSurface::Transparent(reddd, 255, 0, 255);
    CSurface::Transparent(yellow, 255, 0, 255);
    CSurface::Transparent(yellowh, 255, 0, 255);
    CSurface::Transparent(yellowv, 255, 0, 255);
    CSurface::Transparent(yellowad, 255, 0, 255);
    CSurface::Transparent(yellowdd, 255, 0, 255);
    CSurface::Transparent(gameover, 255, 0, 255);
    
    
    Reset();
    
    return true;
}

// Beginning setting of the game.

void TwoPlayers::Reset(){
    int w = WIDTH/7, h= HEIGHT/6, i, j, k, l;
    
    SDL_Rect r = {0};
    
    for (k= 0, i=0; i<HEIGHT; i+=h,k++) {
        r.y = i;
        for (l=0,j=0; j<WIDTH; j+=w,l++) {
            r.x = j;
            SDL_BlitSurface(empty,NULL,Surf_Display,&r);
        }
    }
}

//OnExecute is the Core of our Game Execution. It implements the Events management that serves us to make the game moves, mostly.

int TwoPlayers::OnExecute(){
    
    if(OnInit() == false){
        return -1;
    }
    
    SDL_Flip(Surf_Display);
    SDL_Event Event;
    
    while(Running == 1){
        SDL_WaitEvent(&Event);
        switch (Event.type) {
                
            case SDL_QUIT:
                Running = 0;
                break;
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Running = 0;
                        break;
                }
            case SDL_MOUSEBUTTONDOWN:
                
                if (Event.button.button == SDL_BUTTON_LEFT) {
                    
                    if (IsGameOver(Grid) == true){
                        Running = 0;
                        break;
                    }
                    
                    // Watchdog is a "key" variable : if the column is full and that a player clicked on it all the same, it won't make the player skip the turn.
                    
                    int watchdog = 0;
                    
                    if (Currentplayer == player1) {
                        checkmouse(&Event.button, watchdog);
                        
                        
                        if (watchdog == 0) { // if the player clicked on a full column
                            break;
                        }
                        
                        // Check if Game is Won or Draw
                        
                        if (IsGameWon(Grid) == true || IsBoardFull(Grid) == true) {
                            if (HorizontalWin(Grid) == true) {
                                MarkHorizontal(Grid);
                            }
                            
                            if (VerticalWin(Grid) == true) {
                                MarkVertical(Grid);
                            }
                            
                            if (ADWin(Grid) == true) {
                                MarkAD(Grid);
                            }
                            
                            if (DDWin(Grid) == true) {
                                MarkDD(Grid);
                            }
                            
                            // If the game was won, the board displays the winning combination and waits 3 seconds before it returns the Game Over Surface.
                            
                            OnRender();
                            SDL_Delay(3000);
                            
                            if (HorizontalWin(Grid) == true || VerticalWin(Grid) == true || ADWin(Grid) == true || DDWin(Grid) == true || IsBoardFull(Grid) == true) { // Just to make sure
                                
                                // Draw the gameover screen if won
                                
                                CSurface::OnDraw(Surf_Display, gameover, 0, 0);
                                SDL_Flip(Surf_Display);
                                
                                int finalrun = 1;
                                
                                // The following loop awaits for a player's move
                                
                                while (finalrun == 1) {
                                    SDL_WaitEvent(&Event);
                                    
                                    if (Event.type == SDL_QUIT) {
                                        finalrun = 0;
                                        OnCleanup();
                                        OnExit();
                                        Running = 0;
                                        return 0;
                                    }
                                    
                                    if (Event.type==SDL_KEYDOWN){
                                        switch (Event.key.keysym.sym) {
                                            case SDLK_ESCAPE:
                                                finalrun = 0;
                                                OnCleanup();
                                                OnExit();
                                                Running = 0;
                                                return 0;
                                        }
                                    }
                                    
                                    if (Event.type==SDL_MOUSEBUTTONDOWN){
                                        
                                        // If the player pressed a button, the code returns the coordinates of the player and checks if the player clicked on a button or not.
                                        
                                        int mousex = Event.motion.x;
                                        int mousey = Event.motion.y;
                                        
                                        // Two booleans to check if the mouse clicked on the button
                                        
                                        bool bback =(mousex>backmain.x) && (mousex< (backmain.x+backmain.w)) && (mousey>backmain.y) && (mousey<(backmain.y + backmain.h));
                                        
                                        bool bquit = (mousex>quit.x) && (mousex< (quit.x+quit.w)) && (mousey>quit.y) && (mousey<(quit.y + quit.h));
                                        
                                        // If clicked on "Back to Main Menu" then return a new StartMenu.
                                        
                                        if (bback == true){
                                            
                                            OnCleanup();
                                            StartMenu menu;
                                            menu.showmenu();
                                            finalrun = 0;
                                            Running = 0;
                                            return 0;
                                            
                                        }
                                        
                                        // If clicked on "Quit" then quits the program.
                                        
                                        if (bquit == true) {
                                            OnCleanup();
                                            finalrun = 0;
                                            Running = 0;
                                            return 0;
                                        }
                                    }
                                    
                                }
                                
                            }
                        }

                        else{
                        
                            // Change player and tile type.
                            
                            Currentplayer = player2;
                            CurrentTile = P2_Tile;
                            break;
                        }
                    }
                    
                    else{
                        
                        /// The exact same thing for the other player
                        
                        checkmouse(&Event.button, watchdog);
                        if (watchdog == 0) {
                            break;
                        }
                        if (IsGameWon(Grid) == true) {
                            if (HorizontalWin(Grid) == true) {
                                MarkHorizontal(Grid);
                            }
                            
                            if (VerticalWin(Grid) == true) {
                                MarkVertical(Grid);
                            }
                            
                            if (ADWin(Grid) == true) {
                                MarkAD(Grid);
                            }
                            
                            if (DDWin(Grid) == true) {
                                MarkDD(Grid);
                            }
                            
                            OnRender();
                            SDL_Delay(3000);
                            if (HorizontalWin(Grid) == true || VerticalWin(Grid) == true || ADWin(Grid) == true || DDWin(Grid) == true) {
                                
                                // Draw the gameover screen if won
                                
                                CSurface::OnDraw(Surf_Display, gameover, 0, 0);
                                SDL_Flip(Surf_Display);
                                
                                int finalrun = 1;
                                
                                while (finalrun == 1) {
                                    SDL_WaitEvent(&Event);
                                    
                                    if (Event.type == SDL_QUIT) {
                                        finalrun = 0;
                                        OnCleanup();
                                        return 0;
                                    }
                                    
                                    if (Event.type==SDL_KEYDOWN){
                                        switch (Event.key.keysym.sym) {
                                            case SDLK_ESCAPE:
                                                finalrun = 0;
                                                OnCleanup();
                                                return 0;

                                        }
                                    }
                                    
                                    if (Event.type==SDL_MOUSEBUTTONDOWN){
                                        int mousex = Event.motion.x;
                                        int mousey = Event.motion.y;
                                        
                                        bool bback =(mousex>backmain.x) && (mousex< (backmain.x+backmain.w)) && (mousey>backmain.y) && (mousey<(backmain.y + backmain.h));
                                        
                                        bool bquit = (mousex>quit.x) && (mousex< (quit.x+quit.w)) && (mousey>quit.y) && (mousey<(quit.y + quit.h));
                                        
                                        if (bback == true){
                                            
                                            OnCleanup();
                                            StartMenu menu;
                                            menu.showmenu();
                                            finalrun = 0;
                                            Running = 0;
                                            break;
                                            
                                        }
                                        
                                        if (bquit == true) {
                                            OnCleanup();
                                            finalrun = 0;
                                            Running = 0;
                                            return 0;
                                        }
                                    }
                                    
                                }
                                
                            }
                        }
                        
                        else{
                        
                            Currentplayer = player1;
                            CurrentTile = P1_Tile;
                            break;
                        }
                    }

                }
            }
        OnRender();
    }
    
    OnCleanup();
    return 0;
}

// RowforPlay returns the row number of the selected column.

int TwoPlayers::RowforPlay(int ColID){
    
    int row;
    
    for (int i=5; i>=0; i--) {
        if (Grid[i][ColID] == Empty) {
            row = i;
            break;
        }
    }
    return row;
}

// IsColFull tells if the column is full

bool TwoPlayers::IsColFull(int ColID){
    
    if (Grid[0][ColID] != Empty) {
        return true;
    }
    
    else{
        return false;
    }
}


// Checkmouse makes the SetCell operation and returns a watchdog = 0 if the player clicked on a full column

void TwoPlayers::checkmouse(SDL_MouseButtonEvent *mouse, int &watchdog){
    
    float mousex = mouse->x;
    
    int colID = floor(mousex/100);
    
    if (IsColFull(colID) == true) {
        watchdog = 0;
        return;
    }
    
    else{
        watchdog = 1;
    }
    
    int rowID = RowforPlay(colID);
    
    SetCell(rowID,colID, CurrentTile);
}

// Rendering function, e.g. associates a red tile to a spot where red is played.

void TwoPlayers::OnRender(){
    
    CSurface::OnDraw(Surf_Display,empty,0,0);
    
    int w = WIDTH/7, h= HEIGHT/6, i, j, k, l;
    
    SDL_Rect r = {0};
    
    for (k= 0, i=0; i<HEIGHT; i+=h,k++) {
        r.y=i;
        for (l=0,j=0; j<WIDTH; j+=w,l++) {
            r.x=j;
            
            if (Grid[k][l]==Red) {
                SDL_BlitSurface(red,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l]==Yellow){
                SDL_BlitSurface(yellow,NULL,Surf_Display,&r);
            }
            
            
            else if (Grid[k][l] == Redh){
                SDL_BlitSurface(redh,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowh){
                SDL_BlitSurface(yellowh,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Redv){
                SDL_BlitSurface(redv,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowv){
                SDL_BlitSurface(yellowv,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Redad){
                SDL_BlitSurface(redad,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowad){
                SDL_BlitSurface(yellowad,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Reddd){
                SDL_BlitSurface(reddd,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowdd){
                SDL_BlitSurface(yellowdd,NULL,Surf_Display,&r);
            }
        }
    }
    
    SDL_Flip(Surf_Display);
    
}

// Exit SDL function

void TwoPlayers::OnExit(){
    SDL_Quit();
}

// Makes the turn by playing at a cell address.

void TwoPlayers::SetCell(int RowID, int ColID, TwoPlayers::Tiles Type){
    if(RowID<0 || RowID>5 || ColID <0 || ColID > 7) return;
    
    Grid[RowID][ColID]=Type;
}

//////// 4 void functions to set a mark for winning combinations.

void TwoPlayers::MarkHorizontal(TwoPlayers::Tiles tab[6][7]){
    int start;
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Redh;
                    tab[i][start+1] = Redh;
                    tab[i][start+2] = Redh;
                    tab[i][start+3] = Redh;
                }
                
                else{
                    tab[i][start] = Yellowh;
                    tab[i][start+1] = Yellowh;
                    tab[i][start+2] = Yellowh;
                    tab[i][start+3] = Yellowh;
                }
                break;
            }
        }
    }
}

void TwoPlayers::MarkVertical(TwoPlayers::Tiles tab[6][7]){
    int start;
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                
                if (tab[start][j] == Red) {
                    
                    tab[start][j] = Redv;
                    tab[start+1][j] = Redv;
                    tab[start+2][j] = Redv;
                    tab[start+3][j] = Redv;
                }
                
                else{
                    tab[start][j] = Yellowv;
                    tab[start+1][j] = Yellowv;
                    tab[start+2][j] = Yellowv;
                    tab[start+3][j] = Yellowv;
                }
                break;
            }
        }
    }
}

void TwoPlayers::MarkAD(TwoPlayers::Tiles tab[6][7]){
    int start;
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Redad;
                    tab[i-1][start+1] = Redad;
                    tab[i-2][start+2] = Redad;
                    tab[i-3][start+3] = Redad;
                }
                
                else{
                    tab[i][start] = Yellowad;
                    tab[i-1][start+1] = Yellowad;
                    tab[i-2][start+2] = Yellowad;
                    tab[i-3][start+3] = Yellowad;
                }
                break;
            }
        }
    }
    
}

void TwoPlayers::MarkDD(TwoPlayers::Tiles tab[6][7]){
    int start;
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Reddd;
                    tab[i+1][start+1] = Reddd;
                    tab[i+2][start+2] = Reddd;
                    tab[i+3][start+3] = Reddd;
                }
                
                else{
                    tab[i][start] = Yellowdd;
                    tab[i+1][start+1] = Yellowdd;
                    tab[i+2][start+2] = Yellowdd;
                    tab[i+3][start+3] = Yellowdd;
                }
                break;
            }
        }
    }
}

// Checks if the game is won by a player.

bool TwoPlayers::IsGameWon(TwoPlayers::Tiles tab[6][7]){
    int start;
    bool won = false;
    
    ///// HORIZONTAL
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                won = true;
                
                if (tab[i][start] == Red) {
                    Winner = player1;
                    
                }
                
                else{
                    Winner = bot;
                    
                }
                
                break;
            }
        }
    }
    
    ////// VERTICAL
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                won = true;
                
                if (tab[start][j] == Red) {
                    Winner = player1;
                }
                
                else{
                    Winner = bot;
                }
                break;
            }
        }
    }
    
    ///// Ascending diagonal
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                won = true;
                if (tab[i][start] == Red) {
                    Winner = player1;
                }
                
                else{
                    Winner = bot;
                }
                break;
            }
        }
    }
    
    ///// Descending diagonal
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                won = true;
                if (tab[i][start] == Red) {
                    Winner= player1;
                }
                
                else{
                    Winner = bot;
                }
                break;
            }
        }
    }
    
    return won;
}

// Cleanup fonction

void TwoPlayers::OnCleanup(){
    SDL_FreeSurface(Surf_Display);
    SDL_FreeSurface(red);
    SDL_FreeSurface(yellow);
    SDL_FreeSurface(empty);
    SDL_FreeSurface(redh);
    SDL_FreeSurface(redv);
    SDL_FreeSurface(reddd);
    SDL_FreeSurface(redad);
    SDL_FreeSurface(yellowh);
    SDL_FreeSurface(yellowv);
    SDL_FreeSurface(yellowad);
    SDL_FreeSurface(yellowdd);
    SDL_FreeSurface(gameover);
}

//////// Below are four functions to check if the player won by Horizontal, Vertical, AD or DD.  

bool TwoPlayers::HorizontalWin(TwoPlayers::Tiles tab[6][7]){
    int start;
    bool hwon = false;
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                hwon = true;
                break;
            }
        }
    }
    
    return hwon;
}

bool TwoPlayers::VerticalWin(TwoPlayers::Tiles tab[6][7]){
    int start;
    bool vwon = false;
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                vwon = true;
                break;
            }
        }
    }
    
    return vwon;
    
}

bool TwoPlayers::ADWin(TwoPlayers::Tiles tab[6][7]){
    
    int start;
    bool adwon = false;
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                adwon = true;
                break;
            }
        }
    }
    return adwon;
}

bool TwoPlayers::DDWin(TwoPlayers::Tiles tab[6][7]){
    int start;
    bool ddwon = false;
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                ddwon = true;
            }
        }
    }
    return ddwon;
}

bool TwoPlayers::IsGameOver(TwoPlayers::Tiles tab[6][7]){
    if (IsGameWon(tab) == true || IsBoardFull(tab) == true) {
        return true;
    }
    
    else{
        return false;
    }
}

bool TwoPlayers::IsBoardFull(TwoPlayers::Tiles tab[6][7]){
    bool res = true;
    
    for (int j = 0; j<7; j++) {
        if (tab[0][j] == Empty) {
            res = false;
            break;
        }
    }
    
    return res;
};