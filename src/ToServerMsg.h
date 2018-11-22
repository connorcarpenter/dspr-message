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

        ToServerMsg() = default;

        //Serialization
        explicit ToServerMsg(std::shared_ptr<CStr> fromString);
        std::shared_ptr<CStr> Serialize();

        //Variables
        enum VariableName
        {
            AuthToken = 1,
            MsgType = 2,
            MsgBytes = 3,
        };
        Array authToken = Array((unsigned char) VariableName::AuthToken);

        enum MessageType
        {
            StartGame = 1,
            UnitOrder = 2,
            ChatSend = 3,
            StandardMessage = 4,
            MessageTypeMaxValue = 5,
        };
        Number msgType = Number((unsigned char) VariableName::MsgType);

        Array msgBytes = Array((unsigned char) VariableName::MsgBytes);

        std::shared_ptr<CStr> Pack();
        void Unpack(std::shared_ptr<CStr> cstr);

    private:

        void Deserialize(std::shared_ptr<CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////


    class ToServerSubMessage
    {
    public:
        std::shared_ptr<DsprMessage::ToServerMsg> getToServerMessage();
        virtual std::shared_ptr<DsprMessage::CStr> Serialize() = 0;
        virtual DsprMessage::ToServerMsg::MessageType getMessageType() = 0;
    };

    /////////////////////////////////////////////////////////////////////////

    class ChatSendServerMsgV1 : public ToServerSubMessage
    {
    public:

        ChatSendServerMsgV1() = default;

        //Serialization
        ChatSendServerMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;

        //Variables
        enum VariableName
        {
            ChatMessage = 1,
        };
        Array chatMsg = Array(VariableName::ChatMessage);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);

        virtual DsprMessage::ToServerMsg::MessageType getMessageType() override { return DsprMessage::ToServerMsg::MessageType::ChatSend; }
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitOrderMsgV1 : public ToServerSubMessage
    {
    public:

        UnitOrderMsgV1() = default;

        //Serialization
        UnitOrderMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;

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

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);

        virtual DsprMessage::ToServerMsg::MessageType getMessageType() override { return DsprMessage::ToServerMsg::MessageType::UnitOrder; }
    };
}