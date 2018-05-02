#define MSG_ENTER_USERNAME      "Ingrese usuario y presione enter:"
#define MSG_ENTER_PASSWORD      "Ingrese clave y presione enter:"
//#define MSG_INVALID_PASSWORD    "Datos incorrectos"

#include "login-view.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

LoginView::LoginView(SDL_Renderer* renderer, int height, int width)
{
    this->screenHeight = height;
    this->screenWidth = width;

    this->userName = "";
    this->userPassword = "";

    this->userAuthenticated = false;

    this->renderer = renderer;

    //Cargando el .ttf
	this->fontStyle = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 18 );
	if( this->fontStyle == NULL )
	{
		//printf( "Failed to load '" + this->DISPLAY_FONT.c_str() + "' font! SDL_ttf Error: " + TTF_GetError() );
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		SDL_Color msgTextColor = { 255, 255, 255, 0xFF };
		this->textSprite = new SpriteSheet(this->renderer, "", false);
		if( !this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_USERNAME, msgTextColor ) )
		{
			printf( "Failed to render prompt text!\n" );
		}
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
}

bool LoginView::IsUserAuthenticated()
{
    return this->userAuthenticated;
}

void LoginView::Open()
{
	bool quit = false;

	bool writingUserName = true;

	SDL_Event e;

	SDL_Color textColor = { 255, 255, 255, 0xFF };

	std::string inputText = " ";
	this->inputTextSprite = new SpriteSheet(this->renderer, "", false);
	this->inputTextSprite->LoadFromRenderedText( this->fontStyle, inputText.c_str(), textColor );

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
				else if ( e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER || e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    if ( writingUserName ) {
                        writingUserName = false;
                        this->userName = inputText;
                        inputText = " ";
                        //Cambio el texto
                        this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_PASSWORD, textColor );
                        renderText = true;
                    }
                    else {
                        this->userPassword = inputText;
                        //Aca enviar mensaje socket pidiendo conexion con user y password y, en base a eso, hacer quit o no
                        this->userAuthenticated = true;
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
				this->inputTextSprite->LoadFromRenderedText( this->fontStyle, inputText.c_str(), textColor );
			}
			else
			{
				this->inputTextSprite->LoadFromRenderedText( this->fontStyle, " ", textColor );
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
