#define MSG_ERROR_DESCONECT "Se ha producido un error con la conexión. Presione enter para volver a conectarse y esc para salir"
#define MSG_CONNECTING "Intentando reconectarse al servidor. Por favor espere"


#include "login-view.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../shared/logger.h"
#include "disconect-view.h"

DisconetView::DisconetView(SDL_Renderer* renderer, int height, int width)
{
    this->screenHeight = height;
    this->screenWidth = width;
    this->renderer = renderer;
    this->backgroundSprite = new SpriteSheet(this->renderer, this->BACKGROUND_IMAGE);

    this->fontStyle = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 18 );
    if ( this->fontStyle == NULL )
    {
        Logger::getInstance()->error(string("(DisconetView::DisconetView) No se pudo cargar la fuente. SDL_TTF Error: ") + TTF_GetError());
    }
    else
    {
        SDL_Color msgTextColor = { 255, 255, 255, 0xFF };
        this->textSprite = new SpriteText(this->renderer, this->fontStyle, MSG_ERROR_DESCONECT, msgTextColor);
    }

    this->exit_game = false;
    this->reconnect = false;
}

DisconetView::~DisconetView()
{
    Logger::getInstance()->debug("DESTRUYENDO DISCONECTVIEW");
}

void DisconetView::Free()
{
    this->backgroundSprite->Free();
    Logger::getInstance()->debug("(DisconetView::DisconetView) Liberando recursos de DisconetView");
    this->textSprite->Free();
    TTF_CloseFont( this->fontStyle );
    this->fontStyle = NULL;
}

void DisconetView::OpenConectionErrorPage()
{
    Logger::getInstance()->debug("(DisconetView:OpenConectionErrorPage) Abriendo pantalla de desconexion.");

    SDL_Color textColor = { 255, 255, 255, 0xFF };
    this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ERROR_DESCONECT, textColor, true );

    SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( this->renderer );

    this->backgroundSprite->Render( ( this->screenWidth - this->backgroundSprite->GetWidth() ) / 2, 0 );
    this->textSprite->Render( ( this->screenWidth - this->textSprite->GetWidth() ) / 2, 350 );

    SDL_RenderPresent( this->renderer );

    bool quit = false;
    SDL_Event e;
    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if ( e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                this->exit_game = true;
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                if ( e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER)
                {
                    this->reconnect = false;
                    quit = true;
                }
            }
        }
    }
}

void DisconetView::OpenConectingPage()
{
    Logger::getInstance()->debug("(DisconetView:OpenConectingPage) Abriendo pantalla de reconexion.");

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    bool quit = false;
    int points = 0;
    while( !quit )
    {
        string message = MSG_CONNECTING;
        for(int i = 0; i < points; i++)
        {
            message = message + ".";
        }

        this->textSprite->LoadFromRenderedText( this->fontStyle, message, textColor, true );

        SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( this->renderer );

        this->backgroundSprite->Render( ( this->screenWidth - this->backgroundSprite->GetWidth() ) / 2, 0 );
        this->textSprite->Render( ( this->screenWidth - this->textSprite->GetWidth() ) / 2, 350 );

        SDL_RenderPresent( this->renderer );

        points++;
        if(points > 5)
        {
            points = 0;
        }
    }
}

bool DisconetView::ExitGame()
{
    return this->exit_game;
}

bool DisconetView::Reconnect()
{
    return this->reconnect;
}
