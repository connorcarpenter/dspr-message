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
        _array authToken = _array(VariableName::AuthToken);

        enum MessageType
        {
            StartGame = 1,
            UnitOrder = 2,
            ChatSend = 3,
        };
        _number msgType = _number(VariableName::MsgType);

        _array msgBytes = _array(VariableName::MsgBytes);

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
        _array chatMsg = _array(VariableName::ChatMessage);

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
        _array unitIds = _array(VariableName::UnitIds);

        _number orderIndex = _number(VariableName::OrderIndex);

        _array otherNumbers = _array(VariableName::OtherNumbers);

    private:

        void Deserialize(_cstr fromString);
    };
}