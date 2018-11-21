#pragma once

//
// Created by connor on 11/18/18.
//

#include "DataTypes.h"
#include <string>

namespace DsprMessage
{
    class ToClientMsg
    {
    public:

        ToClientMsg();

        //Serialization
        explicit ToClientMsg(_cstr fromString);
        _cstr Serialize();

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
        _number msgType = _number(VariableName::MsgType);

        _array msgBytes = _array(VariableName::MsgBytes);

        static bool Equals(ToClientMsg *pMsg, ToClientMsg *pClientMsg);

        _cstr Pack();
        void Unpack(_cstr cstr);

    private:

        void Deserialize(_cstr fromString);


    };

    /////////////////////////////////////////////////////////////////////////

    class ChatSendClientMsgV1
    {
    public:

        ChatSendClientMsgV1();

        //Serialization
        ChatSendClientMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            ChatMessage = 1,
            TribeIndex = 2,
        };
        _array chatMsg = _array(VariableName::ChatMessage);

        _number tribeIndex = _number(VariableName::TribeIndex);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class EconomyUpdateMsgV1
    {
    public:

        EconomyUpdateMsgV1();

        //Serialization
        explicit EconomyUpdateMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            Pop = 1,
            PopMax = 2,
            Mana = 3,
        };
        _number pop = _number(VariableName::Pop);

        _number popMax = _number(VariableName::PopMax);

        _number mana = _number(VariableName::Mana);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class TribeSetMsgV1
    {
    public:

        TribeSetMsgV1();

        //Serialization
        TribeSetMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            TribeIndex = 1,
        };
        _number tribeIndex = _number(VariableName::TribeIndex);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class TileCreateMsgV1
    {
    public:

        TileCreateMsgV1();

        //Serialization
        TileCreateMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            X = 1,
            Y = 2,
            Frame = 3,
        };
        _number frame = _number(VariableName::Frame);
        _number x = _number(VariableName::X);
        _number y = _number(VariableName::Y);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class GridCreateMsgV1
    {
    public:

        GridCreateMsgV1();

        //Serialization
        GridCreateMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            Width = 1,
            Height = 2,
        };
        _number width = _number(VariableName::Width);
        _number height = _number(VariableName::Height);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ItemCreateMsgV1
    {
    public:

        ItemCreateMsgV1();

        //Serialization
        ItemCreateMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            X = 2,
            Y = 3,
            TemplateIndex = 4,
        };
        _number x = _number(VariableName::X);
        _number y = _number(VariableName::Y);
        _number id = _number(VariableName::Id);
        _number templateIndex = _number(VariableName::TemplateIndex);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ItemDeleteMsgV1
    {
    public:

        ItemDeleteMsgV1();

        //Serialization
        ItemDeleteMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
        };
        _number id = _number(VariableName::Id);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitCreateMsgV1
    {
    public:

        UnitCreateMsgV1();

        //Serialization
        UnitCreateMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            X = 2,
            Y = 3,
            TemplateIndex = 4,
            TribeIndex = 5,
        };
        _number id = _number(VariableName::Id);
        _number templateIndex = _number(VariableName::TemplateIndex);
        _number tribeIndex = _number(VariableName::TribeIndex);
        _number x = _number(VariableName::X);
        _number y = _number(VariableName::Y);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ConstructionQueueMsgV1
    {
    public:

        ConstructionQueueMsgV1();

        //Serialization
        ConstructionQueueMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            BuildTime = 1,
            Queue = 2,
        };
        _number buildTime = _number(VariableName::BuildTime);
        _array queue = _array(VariableName::Queue);

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitUpdateMsgV1
    {
    public:

        UnitUpdateMsgV1();

        //Serialization
        UnitUpdateMsgV1(_cstr fromString);
        _cstr Serialize();

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
        _number id = _number(VariableName::Id);
        _array nextPosition = _array(VariableName::NextPosition);
        _array moveTarget = _array(VariableName::MoveTarget);
        _array animationState = _array(VariableName::AnimationState);
        _number health = _number(VariableName::Health);
        _number bleed = _number(VariableName::Bleed);
        _number targetUnitId = _number(VariableName::TargetUnitId);
        _array gatherYield = _array(VariableName::GatherYield);
        _array constructionQueue = _array(VariableName::ConstructionQueue);
        _array rallyPoint = _array(VariableName::RallyPoint);
        _number rallyUnitId = _number(VariableName::RallyUnitId);
        _array inventory = _array(VariableName::Inventory);

        static bool Equals(UnitUpdateMsgV1 *a, UnitUpdateMsgV1 *b);

        _cstr SerializeFinal();

    private:

        void Deserialize(_cstr fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitDeleteMsgV1
    {
    public:

        UnitDeleteMsgV1();

        //Serialization
        UnitDeleteMsgV1(_cstr fromString);
        _cstr Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            Dead = 2,
        };
        _number id = _number(VariableName::Id);
        _number dead = _number(VariableName::Dead);

    private:

        void Deserialize(_cstr fromString);
    };
}