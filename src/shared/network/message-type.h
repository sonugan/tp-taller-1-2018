#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

enum MESSAGE_TYPE
{
    HEALTH_CHECK = 0,
    LOGIN_REQUEST = 1,
    KICK_REQUEST = 2,
    RECOVER_REQUEST = 3,
    SELECT_REQUEST = 4,
    PASS_REQUEST = 5,
    MOVE_REQUEST = 6,
    QUIT_REQUEST = 7,
    LOGIN_RESPONSE = 8,
    GAME_STATE_RESPONSE = 9,
    CHANGE_FORMATION_REQUEST = 10,
    LONG_PASS_REQUEST = 11
};

#endif // MESSAGETYPE_H
