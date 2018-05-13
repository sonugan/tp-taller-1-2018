#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstring>

#include "iserializable.h"

using namespace std;

enum MESSAGE_TYPE {
            LOGIN_REQUEST,
            KICK_REQUEST,
            RECOVER_REQUEST,
            SELECT_REQUEST,
            PASS_REQUEST,
            MOVE_REQUEST,
            QUIT_REQUEST,
            LOGIN_RESPONSE,
            GAME_STATE_RESPONSE};
class Message
{
    public:
        Message(char* data, int size);
        Message(string data);
        Message(ISerializable* serializable);
        char* GetData();
        int GetDataSize();
        ISerializable* GetDeserializedData(ISerializable* serializable);
        virtual ~Message();
    protected:
    private:
        string data;
};

#endif // MESSAGE_H
