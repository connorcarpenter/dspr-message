#pragma once

//
// Created by connor on 11/18/18.
//

#include "DataTypes.h"

namespace DsprMessage
{
    class ToServerMsg
    {
    public:

        ToServerMsg();

        //Serialization
        ToServerMsg(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            AuthToken = 1,
            MsgType = 2,
            MsgBytes = 3,
        };
        _bytes authToken = _bytes(VariableName::AuthToken);

        enum MessageType
        {
            StartGame = 1,
            UnitOrder = 2,
            ChatSend = 3,
        };
        _soloByte msgType = _soloByte(VariableName::MsgType);

        _bytes msgBytes = _bytes(VariableName::MsgBytes);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ChatSendMsgV1
    {
    public:

        ChatSendMsgV1();

        //Serialization
        ChatSendMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            ChatMessage = 1,
        };
        _bytes chatMsg = _bytes(VariableName::ChatMessage);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitOrderMsgV1
    {
    public:

        UnitOrderMsgV1();

        //Serialization
        UnitOrderMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            UnitIds = 1,
            OrderIndex = 2,
            OtherNumbers = 3,
        };
        _bytes unitIds = _bytes(VariableName::UnitIds);

        _soloByte orderIndex = _soloByte(VariableName::OrderIndex);

        _bytes otherNumbers = _bytes(VariableName::OtherNumbers);

    private:

        void Deserialize(char* fromString);
    };
}