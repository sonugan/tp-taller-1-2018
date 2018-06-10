#define MSG_ENTER_USERNAME      "Ingrese usuario y presione enter:"
#define MSG_ENTER_PASSWORD      "Ingrese clave y presione enter:"
#define MSG_ENTER_TEAM          "Ingrese equipo (A o B) y presione enter:"
#define MSG_ENTER_SERVER_IP     "Ingrese la direccion IP del server:"
#define MSG_INVALID_PASSWORD    "Error de autenticacion. Presione ESC para salir o ENTER para volver al menu principal"
#define MSG_TOO_MANY_USERS      "Lo siento, no es posible conectarse en este momento! Cantidad maxima de usuarios alcanzada. Presione ESC para salir."
#define MSG_INVALID_TEAM        "Error: ha elegido un equipo invalido. Presione ESC para salir o ENTER para volver al menu principal"
#define MSG_NON_EXISTENT_USER   "Error: el usuario no existe en la partida"
#define MSG_WAITING             "Esperando que se conecten todos los jugadores..."
#define MSG_CHOOSE_FORMATION    "Ingrese formacion a usar: "
#define MSG_INVALID_FORMATION   "Formacion invalida. Presione ENTER para ingresar una nueva."

#include "login-view.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../shared/logger.h"

LoginView::LoginView(SDL_Renderer* renderer, int height, int width, LoginRequest* login_request)
{
    this->screenHeight = height;
    this->screenWidth = width;

    this->userAuthenticated = false;
    this->userQuit = false;

    this->renderer = renderer;
    this->login_request = login_request;

    //Cargando el .ttf
    this->fontStyle = TTF_OpenFont( this->DISPLAY_FONT.c_str(), 18 );
    if ( this->fontStyle == NULL )
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

LoginView::~LoginView()
{
    Logger::getInstance()->debug("DESTRUYENDO LOGINVIEW");
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

    SDL_Event e;

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    std::string inputText = "";
    this->inputTextSprite = new SpriteText(this->renderer, this->fontStyle, " ", textColor);

    this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_USERNAME, textColor, false );

    SDL_StartTextInput();


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
                if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
                {
                    inputText.pop_back();
                    renderText = true;
                }
                else if ( e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER || e.key.keysym.scancode == SDL_SCANCODE_RETURN)
                {
                    if ( this->login_request->GetUsername().empty() )
                    {
                        cout << "setting username: " << inputText << "\n";
                        login_request->SetUsername(inputText);
                        cout << login_request->ToString() << "\n";
                        if (!inputText.empty())
                        {
                            this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_PASSWORD, textColor, false );
                            renderText = true;
                        }
                        inputText = "";
                    }
                    else if (this->login_request->GetPassword().empty())
                    {
                        cout << "setting password: " << inputText << "\n";
                        login_request->SetPassword(inputText);
                        cout << login_request->ToString() << "\n";
                        if (!inputText.empty())
                        {
                            this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_TEAM, textColor, false );
                            renderText = true;
                        }
                        inputText = "";
                    }
//                    else if (this->login_request->GetServerIp().empty())
//                    {
//                        cout << "setting server_ip: " << inputText << "\n";
//                        login_request->SetServerIp(inputText);
//                        cout << login_request->ToString() << "\n";
//                        if (!inputText.empty())
//                        {
//                            this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_ENTER_TEAM, textColor, false );
//                            renderText = true;
//                        }
//                        inputText = "";
//                    }
                    else if (this->login_request->GetTeam().empty())
                    {
                        cout << "setting team: " << inputText << "\n";
                        login_request->SetServerIp(game_configuration->GetServerHostname());
                        login_request->SetTeam(inputText);
                        cout << login_request->ToString() << "\n";
                        if (!inputText.empty())
                        {
                            quit = true;
                        }
                        inputText = "";

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

void LoginView::OpenErrorPage(Configuration* game_configuration, const std::string& login_response)
{
    bool quit = false;

    bool backHome = false;

    SDL_Event e;

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    string error_message = MSG_INVALID_PASSWORD;

    if ("login-fail" == login_response)
    {
        // Loggeo que el usuario o pass eran erroneos
        Logger::getInstance()->error("El usuario " + login_request->GetUsername() + " o la password " + login_request->GetPassword() + " son incorrectos.");
    }
    else if ("too-many-users" == login_response)
    {
        error_message = MSG_TOO_MANY_USERS;
        Logger::getInstance()->error("(LoginView:OpenErrorPage) No se puede conectar. Cantidad maxima de usuarios alcanza.");
    }
    else if ("invalid-team" == login_response)
    {
        error_message = MSG_INVALID_TEAM;
        Logger::getInstance()->error("(LoginView:OpenErrorPage) No se puede conectar. El equipo elegido es invalido.");
    }
    else if(login_response == "non-existent-user")
    {
        error_message = MSG_NON_EXISTENT_USER;
        Logger::getInstance()->error("(LoginView:OpenErrorPage) El usuario no existe en la partida");
    }


    // Limpio el texto que quedo del usuario
    this->inputTextSprite->LoadFromRenderedText( this->fontStyle, " ", textColor, false );

    // Cargo mensaje de error
    this->textSprite->LoadFromRenderedText( this->fontStyle, error_message, textColor, true );

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

        this->login_request->SetUsername("");
        this->login_request->SetPassword("");
        this->login_request->SetTeam("");
        this->login_request->SetServerIp("");


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

void LoginView::OpenWaitingPage()
{
    Logger::getInstance()->debug("(LoginView:OpenWaitingPage) Abriendo pantalla de espera.");

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    // Limpio el texto que quedo del usuario
    this->inputTextSprite->LoadFromRenderedText( this->fontStyle, " ", textColor, false );

    // Cargo mensaje de autenticacion erronea
    this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_WAITING, textColor, true );

    SDL_StartTextInput();

    SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( this->renderer );

    this->backgroundSprite->Render( ( this->screenWidth - this->backgroundSprite->GetWidth() ) / 2, 0 );
    this->textSprite->Render( ( this->screenWidth - this->textSprite->GetWidth() ) / 2, 350 );
    this->inputTextSprite->Render( ( this->screenWidth - this->inputTextSprite->GetWidth() ) / 2, 350 + this->textSprite->GetHeight() );

    SDL_RenderPresent( this->renderer );

//    }

    SDL_StopTextInput();

//    if (backHome) {
//        this->Open(game_configuration);
//    }
}

TEAM_NUMBER LoginView::GetTeamNumber()
{
    this->team_number = TEAM_NUMBER::TEAM_B; // TODO ESTO LO TIENE QUE TRAER DE LA PANTALLA DE LOGIN
    return this->team_number;
}

bool LoginView::OpenFormationPage(ChangeFormationRequest* cfRequest)
{
    Logger::getInstance()->debug("(LoginView:OpenFormationPage) Abriendo pantalla de seleccion de formacion.");
    bool quit = false, invalid_formation = false, x_pressed = false;

    SDL_Event e;

    SDL_Color textColor = { 255, 255, 255, 0xFF };

    std::string inputText = "";
    this->inputTextSprite = new SpriteText(this->renderer, this->fontStyle, " ", textColor);

    this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_CHOOSE_FORMATION, textColor, false );

    SDL_StartTextInput();

    while( !quit )
    {
        bool renderText = false;

        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                x_pressed = true;
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
                {
                    inputText.pop_back();
                    renderText = true;
                }
                else if ( e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER || e.key.keysym.scancode == SDL_SCANCODE_RETURN)
                {
                    if (invalid_formation) {
                        invalid_formation = false;
                        this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_CHOOSE_FORMATION, textColor, false );
                    }
                    else {
                        //ENVIA INFORMACION DE LA FORMACION ELEGIDA
                        if (inputText != "3-3" && inputText != "3-2-1" && inputText != "3-1-2")
                        {
                            //Reinicio el texto ingresado
                            inputText = "";
                            renderText = true;
                            invalid_formation = true;
                            this->textSprite->LoadFromRenderedText( this->fontStyle, MSG_INVALID_FORMATION, textColor, true );
                        }
                        else
                        {
                            //Envio mensaje de formacion
                            cfRequest->SetFormation(inputText);
                            cout << "Change formation request: " + cfRequest->ToString() << "\n";
                            quit = true;
                        }
                    }
                }
            }
            else if( e.type == SDL_TEXTINPUT && !invalid_formation)
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

    return x_pressed;
}
