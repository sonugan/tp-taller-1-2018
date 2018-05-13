#define MSG_ENTER_USERNAME      "Ingrese usuario y presione enter:"
#define MSG_ENTER_PASSWORD      "Ingrese clave y presione enter:"
#define MSG_ENTER_TEAM          "Ingrese equipo (A o B) y presione enter:"
#define MSG_ENTER_SERVER_IP     "Ingrese la direccion IP del server:"
#define MSG_INVALID_PASSWORD    "Error de autenticacion. Presione ESC para salir o ENTER para volver al menu principal"


#include "login-view.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../shared/logger.h"

LoginView::LoginView(SDL_Renderer* renderer, int height, int width, Login* login) {
    this->screenHeight = height;
    this->screenWidth = width;

    this->userAuthenticated = false;
    this->userQuit = false;

    this->renderer = renderer;
    this->login = login;

    //Cargando el .ttf
    this->fontStyle = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 18 );
    if ( this->fontStyle == NULL ) {
        Logger::getInstance()->error(string("No se pudo cargar la fuente. SDL_TTF Error: ") + TTF_GetError());
    } else {
        SDL_Color msgTextColor = { 255, 255, 255, 0xFF };
        this->textSprite = new SpriteText(this->renderer, this->fontStyle, MSG_ENTER_USERNAME, msgTextColor);
    }

    this->backgroundSprite = new SpriteSheet(this->renderer, this->BACKGROUND_IMAGE);
}

LoginView::~LoginView() {
	Logger::getInstance()->debug("DESTRUYENDO LOGINVIEW");
}

void LoginView::Free() {
    this->textSprite->Free();
    this->inputTextSprite->Free();
    this->backgroundSprite->Free();

    TTF_CloseFont( this->fontStyle );
    this->fontStyle = NULL;
    Logger::getInstance()->debug("Liberando recursos de LoginView");
}

bool LoginView::IsUserAuthenticated() {
    return this->userAuthenticated;
}

bool LoginView::IsUserQuit() {
    return this->userQuit;
}

void LoginView::Open(Configuration* game_configuration) {
    bool quit = false;

    SDL_Event e;

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    std::string inputText = "";
    this->inputTextSprite = new SpriteText(this->renderer, this->fontStyle, " ", textColor);

    this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_USERNAME, textColor, false );

    SDL_StartTextInput();


    while( !quit ) {
        bool renderText = false;

        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) {
                quit = true;
            } else if( e.type == SDL_KEYDOWN ) {
                if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 ) {
                    inputText.pop_back();
                    renderText = true;
                } else if ( e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER || e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    if ( this->login->GetUsername().empty() ) {
                        cout << "setting username: " << inputText << "\n";
                        login->SetUsername(inputText);
                        cout << login->ToString() << "\n";
                        if (!inputText.empty()) {
                            this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_PASSWORD, textColor, false );
                            renderText = true;
                        }
                        inputText = "";
                    } else if (this->login->GetPassword().empty()) {
                        cout << "setting password: " << inputText << "\n";
                        login->SetPassword(inputText);
                        cout << login->ToString() << "\n";
                        if (!inputText.empty()) {
                            this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_SERVER_IP, textColor, false );
                            renderText = true;
                        }
                        inputText = "";
                    } else if (this->login->GetServerIp().empty()) {
                        cout << "setting server_ip: " << inputText << "\n";
                        login->SetServerIp(inputText);
                        cout << login->ToString() << "\n";
                        if (!inputText.empty()) {
                            this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_TEAM, textColor, false );
                            renderText = true;
                        }
                        inputText = "";
                    } else if (this->login->GetTeam().empty()) {
                        cout << "setting team: " << inputText << "\n";
                        login->SetTeam(inputText);
                        cout << login->ToString() << "\n";
                        if (!inputText.empty()) {
//                            if (game_configuration->IsValidCredential(login->GetUsername(), login->GetPassword() )) {
//                                this->userAuthenticated = true;
//                            } else {
//                                this->userAuthenticated = false;
//                            }
                            quit = true;
                        }
                        inputText = "";

                    }
                }
            } else if( e.type == SDL_TEXTINPUT ) {
                if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) ) {
                    inputText += e.text.text;
                    renderText = true;
                }
            }
        }

        if( renderText ) {
            if( inputText != "" ) {
                this->inputTextSprite->LoadFromRenderedText( this->fontStyle, inputText.c_str(), textColor, false);
            } else {
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

void LoginView::OpenErrorPage(Configuration* game_configuration)
{
    bool quit = false;

    bool backHome = false;

    SDL_Event e;

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    // Loggeo que el usuario o pass eran erroneos
    Logger::getInstance()->error("El usuario " + login->GetUsername() + " o la password " + login->GetPassword() + " son incorrectos.");


    // Limpio el texto que quedo del usuario
    this->inputTextSprite->LoadFromRenderedText( this->fontStyle, " ", textColor, false );

    // Cargo mensaje de autenticacion erronea
    this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_INVALID_PASSWORD, textColor, true );

    SDL_StartTextInput();

    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if ( e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                // SI PRESIONA ESC SALE DEL JUEGO
                quit = true;
                this->userQuit = true;
            } else if( e.type == SDL_KEYDOWN ) {
                // SI PRESIONA ENTER VUELVE AL MENU PRINCIPAL
                if ( e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER || e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    quit = true;
                    backHome = true;
                }
            }
        }

        this->login->SetUsername("");
        this->login->SetPassword("");
        this->login->SetTeam("");
        this->login->SetServerIp("");


        SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( this->renderer );

        this->backgroundSprite->Render( ( this->screenWidth - this->backgroundSprite->GetWidth() ) / 2, 0 );
        this->textSprite->Render( ( this->screenWidth - this->textSprite->GetWidth() ) / 2, 350 );
        this->inputTextSprite->Render( ( this->screenWidth - this->inputTextSprite->GetWidth() ) / 2, 350 + this->textSprite->GetHeight() );

        SDL_RenderPresent( this->renderer );

    }

    SDL_StopTextInput();

    if (backHome) {
        this->Open(game_configuration);
    }
}
