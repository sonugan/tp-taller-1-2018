#define MSG_ENTER_USERNAME      "Ingrese usuario y presione enter:"
#define MSG_ENTER_PASSWORD      "Ingrese clave y presione enter:"
#define MSG_INVALID_PASSWORD    "Error de autenticacion. Presione ESC para salir o ENTER para volver al menu principal"

#include "login-view.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../shared/logger.h"

LoginView::LoginView(SDL_Renderer* renderer, int height, int width)
{
    this->screenHeight = height;
    this->screenWidth = width;

    this->userName = "";
    this->userPassword = "";

    this->userAuthenticated = false;
    this->userQuit = false;

    this->renderer = renderer;

    //Cargando el .ttf
    this->fontStyle = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 18 );
    if( this->fontStyle == NULL )
    {
        Logger::getInstance()->error(string("No se pudo cargar la fuente. SDL_TTF Error: ") + TTF_GetError());
    }
    else
    {
        SDL_Color msgTextColor = { 255, 255, 255, 0xFF };
        this->textSprite = new SpriteText(this->renderer, this->fontStyle, MSG_ENTER_USERNAME, msgTextColor);
    }

    this->backgroundSprite = new SpriteSheet(this->renderer, this->BACKGROUND_IMAGE);
}

void LoginView::Free()
{
    this->textSprite->Free();
    this->inputTextSprite->Free();
    this->backgroundSprite->Free();

    TTF_CloseFont( this->fontStyle );
    this->fontStyle = NULL;
    Logger::getInstance()->debug("Liberando recursos de LoginView");
}

bool LoginView::IsUserAuthenticated()
{
    return this->userAuthenticated;
}

bool LoginView::IsUserQuit()
{
    return this->userQuit;
}

void LoginView::Open(Configuration* game_configuration)
{
    bool quit = false;

    bool writingUserName = true;

    SDL_Event e;

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    std::string inputText = "";
    this->inputTextSprite = new SpriteText(this->renderer, this->fontStyle, " ", textColor);

    this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_USERNAME, textColor, false );

    SDL_StartTextInput();

    //Loop de login-view
    while( !quit )
    {
        bool renderText = false;

        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                //Borra caracter
                if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
                {
                    inputText.pop_back();
                    renderText = true;
                }
                //CTRL + C
                else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                {
                    SDL_SetClipboardText( inputText.c_str() );
                }
                //CTRL + V
                else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                {
                    inputText = SDL_GetClipboardText();
                    renderText = true;
                }
                //ENTER
                else if ( e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER || e.key.keysym.scancode == SDL_SCANCODE_RETURN)
                {
                    if ( writingUserName )
                    {
                        writingUserName = false;
                        this->userName = inputText;
                        inputText = "";
                        //Cambio el texto
                        this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_PASSWORD, textColor, false );
                        renderText = true;
                    }
                    else
                    {
                        this->userPassword = inputText;
                        //Aca enviar mensaje socket pidiendo conexion con user y password y, en base a eso, hacer quit o no
                        if (game_configuration->IsValidCredential(this->userName, this->userPassword ))
                        {
                            this->userAuthenticated = true;
                        }
                        else
                        {
                            this->userAuthenticated = false;
                        }

                        /**
                        if (!this->logUser(userName, userPassword))
                        {
                            //Reinicio el formulario de login
                            this->inputText = "";
                            this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_USERNAME, textColor )

                            this->userName = "";
                            this->userPassword = "":
                            writingUserName = true;
                            renderText = true;
                        }
                        else
                        {
                            quit = true;
                        }
                        */
                        quit = true;
                    }
                }
            }
            else if( e.type == SDL_TEXTINPUT )
            {
                if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
                {
                    inputText += e.text.text;
                    renderText = true;
                }
            }
        }

        if( renderText )
        {
            if( inputText != "" )
            {
                this->inputTextSprite->LoadFromRenderedText( this->fontStyle, inputText.c_str(), textColor, false);
            }
            else
            {
                this->inputTextSprite->LoadFromRenderedText( this->fontStyle, " ", textColor, false );
            }
        }


        SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( this->renderer );

        this->backgroundSprite->Render( ( this->screenWidth - this->backgroundSprite->GetWidth() ) / 2, 0 );
        this->textSprite->Render( ( this->screenWidth - this->textSprite->GetWidth() ) / 2, 350 );
        this->inputTextSprite->Render( ( this->screenWidth - this->inputTextSprite->GetWidth() ) / 2, 350 + this->textSprite->GetHeight() );

        SDL_RenderPresent( this->renderer );

    }
    SDL_StopTextInput();
}

string LoginView::GetUserName()
{
    return this->userName;
}

string LoginView::GetUserPassword()
{
    return this->userPassword;
}

void LoginView::OpenErrorPage(Configuration* game_configuration)
{
    bool quit = false;

    bool backHome = false;

    SDL_Event e;

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    // Loggeo que el usuario o pass eran erroneos
    Logger::getInstance()->error("El usuario " + this->GetUserName() + " o la password " + this->GetUserPassword() + " son incorrectos.");


    // Limpio el texto que quedo del usuario
    this->inputTextSprite->LoadFromRenderedText( this->fontStyle, " ", textColor, false );

    // Cargo mensaje de autenticacion erronea
    this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_INVALID_PASSWORD, textColor, true );

    SDL_StartTextInput();

    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if ( e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                // SI PRESIONA ESC SALE DEL JUEGO
                quit = true;
                this->userQuit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                // SI PRESIONA ENTER VUELVE AL MENU PRINCIPAL
                if ( e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER || e.key.keysym.scancode == SDL_SCANCODE_RETURN)
                {
                    quit = true;
                    backHome = true;
                }
            }
        }


        SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( this->renderer );

        this->backgroundSprite->Render( ( this->screenWidth - this->backgroundSprite->GetWidth() ) / 2, 0 );
        this->textSprite->Render( ( this->screenWidth - this->textSprite->GetWidth() ) / 2, 350 );
        this->inputTextSprite->Render( ( this->screenWidth - this->inputTextSprite->GetWidth() ) / 2, 350 + this->textSprite->GetHeight() );

        SDL_RenderPresent( this->renderer );

    }

    SDL_StopTextInput();

    if (backHome)
    {
        this->Open(game_configuration);
    }
}

TEAM_NUMBER LoginView::GetTeamNumber()
{
    this->team_number = TEAM_NUMBER::TEAM_B;
    return this->team_number;
}
