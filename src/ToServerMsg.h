#pragma once

//
// Created by connor on 11/18/18.
//

#include "Number.h"

namespace DsprMessage
{
    class ToServerMsg
    {
    public:

        ToServerMsg(){};

        //Serialization
        ToServerMsg(CStr fromString);
        CStr Serialize();

        //Variables
        enum VariableName
        {
            AuthToken = 1,
            MsgType = 2,
            MsgBytes = 3,
        };
        Array authToken = Array(VariableName::AuthToken);

        enum MessageType
        {
            StartGame = 1,
            UnitOrder = 2,
            ChatSend = 3,
        };
        Number msgType = Number(VariableName::MsgType);

        Array msgBytes = Array(VariableName::MsgBytes);

    private:

        void Deserialize(CStr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ChatSendServerMsgV1
    {
    public:

        ChatSendServerMsgV1();

        //Serialization
        ChatSendServerMsgV1(CStr fromString);
        CStr Serialize();

        //Variables
        enum VariableName
        {
            ChatMessage = 1,
        };
        Array chatMsg = Array(VariableName::ChatMessage);

    private:

        void Deserialize(CStr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitOrderMsgV1
    {
    public:

        UnitOrderMsgV1();

        //Serialization
        UnitOrderMsgV1(CStr fromString);
        CStr Serialize();

        //Variables
        enum VariableName
        {
            UnitIds = 1,
            OrderIndex = 2,
            OtherNumbers = 3,
        };
        Array unitIds = Array(VariableName::UnitIds);

        Number orderIndex = Number(VariableName::OrderIndex);

        Array otherNumbers = Array(VariableName::OtherNumbers);

    private:

        void Deserialize(CStr fromString);
    };
}