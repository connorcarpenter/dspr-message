#pragma once

//
// Created by connor on 11/18/18.
//

#include "DataTypes.h"

namespace DsprMessage
{
    class ToClientMsg
    {
    public:

        ToClientMsg();

        //Serialization
        ToClientMsg(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            MsgType = 1,
            MsgBytes = 2,
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
            TribeIndex = 2,
        };
        _bytes chatMsg = _bytes(VariableName::ChatMessage);

        _soloByte tribeIndex = _soloByte(VariableName::TribeIndex);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class EconomyUpdateMsgV1
    {
    public:

        EconomyUpdateMsgV1();

        //Serialization
        EconomyUpdateMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            Pop = 1,
            PopMax = 2,
            Mana = 3,
        };
        _soloByte pop = _soloByte(VariableName::Pop);

        _soloByte popMax = _soloByte(VariableName::PopMax);

        _duoByte mana = _duoByte(VariableName::Mana);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class TribeSetMsgV1
    {
    public:

        TribeSetMsgV1();

        //Serialization
        TribeSetMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            TribeIndex = 1,
        };
        _soloByte tribeIndex = _soloByte(VariableName::TribeIndex);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class TileCreateMsgV1
    {
    public:

        TileCreateMsgV1();

        //Serialization
        TileCreateMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            X = 1,
            Y = 2,
            Frame = 3,
        };
        _soloByte frame = _soloByte(VariableName::Frame);
        _duoByte x = _duoByte(VariableName::X);
        _duoByte y = _duoByte(VariableName::Y);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class GridCreateMsgV1
    {
    public:

        GridCreateMsgV1();

        //Serialization
        GridCreateMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            Width = 1,
            Height = 2,
        };
        _duoByte width = _duoByte(VariableName::Width);
        _duoByte height = _duoByte(VariableName::Height);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ItemCreateMsgV1
    {
    public:

        ItemCreateMsgV1();

        //Serialization
        ItemCreateMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            X = 2,
            Y = 3,
            TemplateIndex = 4,
        };
        _duoByte x = _duoByte(VariableName::X);
        _duoByte y = _duoByte(VariableName::Y);
        _soloByte id = _soloByte(VariableName::Id);
        _soloByte templateIndex = _soloByte(VariableName::TemplateIndex);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ItemDeleteMsgV1
    {
    public:

        ItemDeleteMsgV1();

        //Serialization
        ItemDeleteMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
        };
        _soloByte id = _soloByte(VariableName::Id);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitCreateMsgV1
    {
    public:

        UnitCreateMsgV1();

        //Serialization
        UnitCreateMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            X = 2,
            Y = 3,
            TemplateIndex = 4,
            TribeIndex = 5,
        };
        _soloByte id = _soloByte(VariableName::Id);
        _soloByte templateIndex = _soloByte(VariableName::TemplateIndex);
        _soloByte tribeIndex = _soloByte(VariableName::TribeIndex);
        _duoByte x = _duoByte(VariableName::X);
        _duoByte y = _duoByte(VariableName::Y);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class ConstructionQueueMsgV1
    {
    public:

        ConstructionQueueMsgV1();

        //Serialization
        ConstructionQueueMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            BuildTime = 1,
            Queue = 2,
        };
        _soloByte buildTime = _soloByte(VariableName::BuildTime);
        _bytes queue = _bytes(VariableName::Queue);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitUpdateMsgV1
    {
    public:

        UnitUpdateMsgV1();

        //Serialization
        UnitUpdateMsgV1(char* fromString);
        char* Serialize();

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
        _soloByte id = _soloByte(VariableName::Id);
        _soloByte bleed = _soloByte(VariableName::Bleed);
        _soloByte targetUnitId = _soloByte(VariableName::TargetUnitId);
        _soloByte rallyUnitId = _soloByte(VariableName::RallyUnitId);
        _duoByte health = _duoByte(VariableName::Health);
        _bytes inventory = _bytes(VariableName::Inventory);
        _bytes constructionQueue = _bytes(VariableName::ConstructionQueue);
        _pair<_duoByte,_duoByte> nextPosition = _pair<_duoByte,_duoByte>(VariableName::NextPosition);
        _pair<_duoByte,_duoByte> moveTarget = _pair<_duoByte,_duoByte>(VariableName::MoveTarget);
        _pair<_duoByte,_duoByte> rallyPoint = _pair<_duoByte,_duoByte>(VariableName::RallyPoint);
        _pair<_soloByte,_soloByte> animationState = _pair<_soloByte,_soloByte>(VariableName::AnimationState);
        _pair<_soloByte,_duoByte> gatherYield = _pair<_soloByte,_duoByte>(VariableName::GatherYield);

    private:

        void Deserialize(char* fromString);
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitDeleteMsgV1
    {
    public:

        UnitDeleteMsgV1();

        //Serialization
        UnitDeleteMsgV1(char* fromString);
        char* Serialize();

        //Variables
        enum VariableName
        {
            Id = 1,
            Dead = 2,
        };
        _soloByte id = _soloByte(VariableName::Id);
        _soloByte dead = _soloByte(VariableName::Dead);

    private:

        void Deserialize(char* fromString);
    };
}