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

        ToServerMsg(){};

        //Serialization
        ToServerMsg(_cstr fromString);
        _cstr Serialize();

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

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ChatSendServerMsgV1
    {
    public:

        ChatSendServerMsgV1();

        //Serialization
        ChatSendServerMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            ChatMessage = 1,
        };
        _bytes chatMsg = _bytes(VariableName::ChatMessage);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitOrderMsgV1
    {
    public:

        UnitOrderMsgV1();

        //Serialization
        UnitOrderMsgV1(_cstr fromString);
        _cstr Serialize();

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

        void Deserialize(_cstr fromString);
    };
}