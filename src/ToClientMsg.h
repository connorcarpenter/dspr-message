#pragma once

//
// Created by connor on 11/18/18.
//

#include "Number.h"
#include <string>

namespace DsprMessage
{
    class ToClientMsg
    {
    public:

        ToClientMsg();

        //Serialization
        explicit ToClientMsg(std::shared_ptr<CStr> fromString);
        std::shared_ptr<CStr> Serialize();

        //Variables
        enum VariableName
        {
            MsgType = 1,
            MsgBytes = 2,
            VariableNameMaxValue = 3,
        };

        enum MessageType
        {
            ChatSend = 1,
            EconomyUpdate = 2,
            TribeSet = 3,
            TileCreate = 3,
            GridCreate = 4,
            ItemCreate = 5,
            ItemDelete = 6,
            UnitCreate = 7,
            UnitUpdate = 8,
            UnitDelete = 9,
            StandardMessage = 10,
            AuthGameToken = 11,
            MessageTypeMaxValue = 12,
        };

        Number msgType = Number((unsigned char) VariableName::MsgType);
        Array msgBytes = Array((unsigned char) VariableName::MsgBytes);

        static bool Equals(const ToClientMsg& pMsg, const ToClientMsg& pClientMsg);

        std::shared_ptr<CStr> Pack();
        void Unpack(std::shared_ptr<CStr> cstr);

    private:

        void Deserialize(std::shared_ptr<CStr> fromString);


    };

    /////////////////////////////////////////////////////////////////////////

    class ChatSendClientMsgV1
    {
    public:

        ChatSendClientMsgV1();

        //Serialization
        ChatSendClientMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            ChatMessage = 1,
            TribeIndex = 2,
        };
        Array chatMsg = Array(VariableName::ChatMessage);

        Number tribeIndex = Number(VariableName::TribeIndex);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class EconomyUpdateMsgV1
    {
    public:

        EconomyUpdateMsgV1();

        //Serialization
        explicit EconomyUpdateMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            Pop = 1,
            PopMax = 2,
            Mana = 3,
        };
        Number pop = Number(VariableName::Pop);

        Number popMax = Number(VariableName::PopMax);

        Number mana = Number(VariableName::Mana);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class TribeSetMsgV1
    {
    public:

        TribeSetMsgV1();

        //Serialization
        TribeSetMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            TribeIndex = 1,
        };
        Number tribeIndex = Number(VariableName::TribeIndex);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class TileCreateMsgV1
    {
    public:

        TileCreateMsgV1();

        //Serialization
        TileCreateMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            X = 1,
            Y = 2,
            Frame = 3,
        };
        Number frame = Number(VariableName::Frame);
        Number x = Number(VariableName::X);
        Number y = Number(VariableName::Y);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class GridCreateMsgV1
    {
    public:

        GridCreateMsgV1();

        //Serialization
        GridCreateMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            Width = 1,
            Height = 2,
        };
        Number width = Number(VariableName::Width);
        Number height = Number(VariableName::Height);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ItemCreateMsgV1
    {
    public:

        ItemCreateMsgV1();

        //Serialization
        ItemCreateMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            X = 2,
            Y = 3,
            TemplateIndex = 4,
        };
        Number x = Number(VariableName::X);
        Number y = Number(VariableName::Y);
        Number id = Number(VariableName::Id);
        Number templateIndex = Number(VariableName::TemplateIndex);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ItemDeleteMsgV1
    {
    public:

        ItemDeleteMsgV1();

        //Serialization
        ItemDeleteMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
        };
        Number id = Number(VariableName::Id);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitCreateMsgV1
    {
    public:

        UnitCreateMsgV1();

        //Serialization
        UnitCreateMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            X = 2,
            Y = 3,
            TemplateIndex = 4,
            TribeIndex = 5,
        };
        Number id = Number(VariableName::Id);
        Number templateIndex = Number(VariableName::TemplateIndex);
        Number tribeIndex = Number(VariableName::TribeIndex);
        Number x = Number(VariableName::X);
        Number y = Number(VariableName::Y);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ConstructionQueueMsgV1
    {
    public:

        ConstructionQueueMsgV1();

        //Serialization
        ConstructionQueueMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            BuildTime = 1,
            Queue = 2,
        };
        Number buildTime = Number(VariableName::BuildTime);
        Array queue = Array(VariableName::Queue);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitUpdateMsgV1
    {
    public:

        UnitUpdateMsgV1();

        //Serialization
        UnitUpdateMsgV1(std::shared_ptr<CStr> fromString);
        std::shared_ptr<CStr> Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            NextPosition = 2,
            MoveTarget = 3,
            AnimationState = 4,
            Health = 5,
            Bleed = 6,
            TargetUnitId = 7,
            GatherYield = 8,
            ConstructionQueue = 9,
            RallyPoint = 10,
            RallyUnitId = 11,
            Inventory = 12,
        };
        Number id = Number(VariableName::Id);
        Array nextPosition = Array(VariableName::NextPosition);
        Array moveTarget = Array(VariableName::MoveTarget);
        Array animationState = Array(VariableName::AnimationState);
        Number health = Number(VariableName::Health);
        Number bleed = Number(VariableName::Bleed);
        Number targetUnitId = Number(VariableName::TargetUnitId);
        Array gatherYield = Array(VariableName::GatherYield);
        Array constructionQueue = Array(VariableName::ConstructionQueue);
        Array rallyPoint = Array(VariableName::RallyPoint);
        Number rallyUnitId = Number(VariableName::RallyUnitId);
        Array inventory = Array(VariableName::Inventory);

        static bool Equals(const UnitUpdateMsgV1& a, const UnitUpdateMsgV1& b);

        std::shared_ptr<DsprMessage::ToClientMsg> getToClientMessage();

    private:

        void Deserialize(std::shared_ptr<CStr> fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitDeleteMsgV1
    {
    public:

        UnitDeleteMsgV1();

        //Serialization
        UnitDeleteMsgV1(std::shared_ptr<DsprMessage::CStr> fromString);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            Dead = 2,
        };
        Number id = Number(VariableName::Id);
        Number dead = Number(VariableName::Dead);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);
    };
}