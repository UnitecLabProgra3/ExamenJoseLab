/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Personaje.h"
#include "Kaiyo.h"
#include "Gogeta.h"
#include "Saiya.h"
#include "Broley.h"
#include "Roshi.h"
#include <string>
#include <vector>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *winground = NULL;
SDL_Surface *loseground = NULL;
SDL_Surface *up = NULL;
SDL_Surface *down = NULL;
SDL_Surface *left = NULL;
SDL_Surface *right = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
{
    return IMG_Load( filename.c_str() );
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Save Master Roshi from Broley's Saiyan Army!", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "bk.png" );

    winground = load_image("won.png");
    loseground = load_image("lose.png");
    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 72 );

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( up );
    SDL_FreeSurface( down );
    SDL_FreeSurface( left );
    SDL_FreeSurface( right );

    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }
    //Render the text
    up = TTF_RenderText_Solid( font, "Up", textColor );
    down = TTF_RenderText_Solid( font, "Down", textColor );
    left = TTF_RenderText_Solid( font, "Left", textColor );
    right = TTF_RenderText_Solid( font, "Right", textColor );

    Personaje *player = new Personaje(0,0);

    Roshi *roshi = new Roshi(570, 395);

    vector<Enemigo*>enemies;
    enemies.push_back(new Gogeta);
    enemies.push_back(new Kaiyo);
    enemies.push_back(new Saiya);
    enemies.push_back(new Broley);

    bool game_over = false;
    bool game_won = false;
    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Apply the background
        apply_surface( 0, 0, background, screen );

        //Get the keystates
        Uint8 *keystates = SDL_GetKeyState( NULL );

        //If up is pressed
        if( keystates[ SDLK_UP ] )
        {
            player->in_battle = false;
            player->moving = true;
            player->current_frame = 11;
            player->y--;
            if(player->y < -30)
                player->y = -30;
        }

        //If down is pressed
        if( keystates[ SDLK_DOWN ] )
        {
            player->in_battle = false;
            player->moving = true;
            player->current_frame = 12;
            player->y++;
            if(player->y>395)
                player->y=395;
        }

        //If left is pressed
        if( keystates[ SDLK_LEFT ] )
        {
            player->in_battle = false;
            player->moving = true;
            player->current_frame = 12;
            player->x--;
            if(player->x<-30)
                player->x=-30;
        }

        //If right is pressed
        if( keystates[ SDLK_RIGHT ] )
        {
            player->in_battle = false;
            player->moving = true;
            player->current_frame = 11;
            player->x++;
            if(player->x>570)
                player->x=570;
        }

        if(keystates['x'])
        {
            if(player->in_battle)
            {
                player->in_battle=false;
            }else
            {
                player->in_battle=true;
            }

        }

        player->dibujar(screen);
        roshi->dibujar(screen);

        for(int i=0;i<enemies.size();i++)
            enemies[i]->dibujar(screen);

        player->logic();

        for(int i=0;i<enemies.size();i++)
        {
            enemies[i]->logic();
            game_over = enemies[i]->collision_logic(player);
            if(game_over)
            {
                break;
            }
        }

        game_won = roshi->collision_logic(player);

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
        if(game_over || game_won)
        {
            int itt = 0;
            while(!quit)
            {
                //While there's events to handle
                while( SDL_PollEvent( &event ) )
                {
                    //If the user has Xed out the window
                    if( event.type == SDL_QUIT )
                    {
                        //Quit the program
                        quit = true;
                    }
                }
                if(game_over)
                {
                    apply_surface( 0, 0, loseground, screen );
                }else if(game_won)
                {
                    apply_surface( 0, 0, winground, screen );
                }
                if( SDL_Flip( screen ) == -1 )
                {
                    return 1;
                }
                itt++;
                if(itt >= 500)
                {
                    quit = true;
                }
            }
        }
    }


    //Clean up
    clean_up();

    return 0;
}
