/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
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
SDL_Surface *screen = NULL;
SDL_Surface *Title_Scrn = NULL;

Mix_Music *BGM = NULL;
Mix_Chunk *Begin_Game_sound = NULL;
Mix_Chunk *got_hit_sound = NULL;
Mix_Chunk *game_won_sound = NULL;
Mix_Chunk *game_over_sound = NULL;

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
    Title_Scrn = load_image("Title_Screen.png");

    winground = load_image("won.png");
    loseground = load_image("lose.png");
    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 72 );

    Begin_Game_sound = Mix_LoadWAV("Begin2.wav");
    got_hit_sound = Mix_LoadWAV("Got_Hit2.wav");
    game_won_sound = Mix_LoadWAV("Game_Won2.wav");
    game_over_sound = Mix_LoadWAV("Game_Over2.wav");

    if( ( Begin_Game_sound == NULL ) || ( got_hit_sound == NULL ) || ( game_won_sound == NULL ) || ( game_over_sound == NULL ) )
    {
        return false;
    }
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
    SDL_FreeSurface( screen );
    SDL_FreeSurface( loseground );
    SDL_FreeSurface( winground );
    SDL_FreeSurface( Title_Scrn);

    //Close the font
    TTF_CloseFont( font );

    Mix_FreeMusic( BGM );

    Mix_FreeChunk( Begin_Game_sound );
    Mix_FreeChunk( game_over_sound );
    Mix_FreeChunk( game_won_sound );
    Mix_FreeChunk( got_hit_sound );

    Mix_CloseAudio();

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return 1;
    }

    BGM = Mix_LoadMUS( "BGM.mp3" );

    if( BGM == NULL )
    {
        return 1;
    }
    bool first_time = true, first_it = true;
    Mix_PlayMusic(BGM, -1);

    if(first_time)
    {
        goto CYCLE;
        FIRST:
        bool quit2 = false;
        if(quit2 == false)
        {
            while(quit2 == false)
            {
                while( SDL_PollEvent( &event ) )
                {
                    //If the user has Xed out the window
                    if( event.type == SDL_QUIT )
                    {
                        //Quit the program
                        return 0;
                    }
                }
                Uint8 *keystates2 = SDL_GetKeyState( NULL );
                apply_surface( 0, 0, Title_Scrn, screen );
                if( SDL_Flip( screen ) == -1 )
                {
                    return 1;
                }
                if(keystates2[SDLK_RETURN])
                {
                    quit2=true;
                    SDL_FreeSurface( Title_Scrn);
                }
            }
        }
        first_time=false;
        first_it=false;
    }

    CYCLE:
    bool quit = false;
    if(!first_it)
    {
        first_it=true;
        goto LAST;
    }
    //Quit flag



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
    if(first_time)
    {
        goto FIRST;
    }
    LAST:
    Personaje *player = new Personaje(0,0);

    Roshi *roshi = new Roshi(570, 395);

    vector<Enemigo*>enemies;
    enemies.push_back(new Gogeta(player));
    enemies.push_back(new Kaiyo);
    enemies.push_back(new Saiya(320, 150));
    enemies.push_back(new Saiya(320, 250));
    enemies.push_back(new Broley);

    bool game_over = false;
    bool game_won = false;
    if( Mix_PlayChannel( -1, Begin_Game_sound, 0 ) == -1 )
    {
        return 1;
    }
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

        player->moving=false;
        //If up is pressed
        if( keystates[ SDLK_UP ] )
        {
            player->in_battle = false;
            player->moving = true;
            player->current_frame = 11;
            player->y-=4;
            if(player->y < -30)
                player->y = -30;
        }

        //If down is pressed
        if( keystates[ SDLK_DOWN ] )
        {
            player->in_battle = false;
            player->moving = true;
            player->current_frame = 12;
            player->y+=4;
            if(player->y>395)
                player->y=395;
        }

        //If left is pressed
        if( keystates[ SDLK_LEFT ] )
        {
            player->in_battle = false;
            player->moving = true;
            player->current_frame = 12;
            player->x-=4;
            if(player->x<-30)
                player->x=-30;
        }

        //If right is pressed
        if( keystates[ SDLK_RIGHT ] )
        {
            player->in_battle = false;
            player->moving = true;
            player->current_frame = 11;
            player->x+=4;
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
        player->logic();

        player->dibujar(screen);
        roshi->dibujar(screen);

        for(int i=0;i<enemies.size();i++)
            enemies[i]->dibujar(screen);



        for(int i=0;i<enemies.size();i++)
        {
            enemies[i]->logic();
            if(!player->hit_anim)
                player->got_hit = enemies[i]->collision_logic(player);
            if(player->got_hit)
            {
                if( Mix_PlayChannel( -1, got_hit_sound, 0 ) == -1 )
                {
                    return 1;
                }
                break;
            }
        }
        if(player->HP == 0)
        {
            game_over=true;
            if( Mix_PlayChannel( -1, game_over_sound, 0 ) == -1 )
            {
                return 1;
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
            if(game_won)
            {
                if( Mix_PlayChannel( -1, game_won_sound, 0 ) == -1 )
                {
                    return 1;
                }
            }
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
                if(itt >= 200)
                {
                    SDL_FreeSurface( background );
                    SDL_FreeSurface( screen );
                    SDL_FreeSurface( loseground );
                    SDL_FreeSurface( winground );
                    Mix_FreeChunk( Begin_Game_sound );
                    Mix_FreeChunk( game_over_sound );
                    Mix_FreeChunk( game_won_sound );
                    Mix_FreeChunk( got_hit_sound );
                    enemies.clear();
                    delete player;
                    delete roshi;
                    delete keystates;
                    goto CYCLE;
                }
            }
        }
    }


    //Clean up
    clean_up();

    return 0;
}
