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

        ToClientMsg() = default;

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
            TileCreate = 4,
            GridCreate = 5,
            ItemCreate = 6,
            ItemDelete = 7,
            UnitCreate = 8,
            UnitUpdate = 9,
            UnitDelete = 10,
            UnitSpecialAction = 11,
            AuthGameToken = 12,
            ProjectileCreate = 13,
            MessageTypeMaxValue = 14,
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

    class ToClientSubMessage
    {
    public:
        std::shared_ptr<DsprMessage::ToClientMsg> getToClientMessage();
        virtual std::shared_ptr<DsprMessage::CStr> Serialize() = 0;
        virtual DsprMessage::ToClientMsg::MessageType getMessageType() = 0;
        virtual void PrintMsg() = 0;
    };

    /////////////////////////////////////////////////////////////////////////

    class ChatSendClientMsgV1 : public ToClientSubMessage
    {
    public:

        ChatSendClientMsgV1() = default;

        //Serialization
        ChatSendClientMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

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

        virtual DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::ChatSend; }
    };

    /////////////////////////////////////////////////////////////////////////

    class EconomyUpdateMsgV1 : public ToClientSubMessage
    {
    public:

        EconomyUpdateMsgV1() = default;

        //Serialization
        explicit EconomyUpdateMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

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

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::EconomyUpdate;};
    };

    /////////////////////////////////////////////////////////////////////////

    class TribeSetMsgV1 : public ToClientSubMessage
    {
    public:

        TribeSetMsgV1() = default;

        //Serialization
        TribeSetMsgV1(const Array& fromArray);
        virtual std::shared_ptr<CStr> Serialize() override;
        void PrintMsg() override;

        //Variables
        enum VariableName
        {
            TribeIndex = 1,
            Status = 2
        };
        Number tribeIndex = Number(VariableName::TribeIndex);
        Number status = Number(VariableName::Status);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::TribeSet;}
    };

    /////////////////////////////////////////////////////////////////////////

    class TileCreateMsgV1 : public ToClientSubMessage
    {
    public:

        TileCreateMsgV1() = default;

        //Serialization
        TileCreateMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

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

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::TileCreate; };
    };

    /////////////////////////////////////////////////////////////////////////

    class GridCreateMsgV1 : public ToClientSubMessage
    {
    public:

        GridCreateMsgV1() = default;

        //Serialization
        GridCreateMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

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

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::GridCreate; };
    };

    /////////////////////////////////////////////////////////////////////////

    class ItemCreateMsgV1 : public ToClientSubMessage
    {
    public:

        ItemCreateMsgV1() = default;

        //Serialization
        ItemCreateMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

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

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::ItemCreate; };
    };

    /////////////////////////////////////////////////////////////////////////

    class ItemDeleteMsgV1 : public ToClientSubMessage
    {
    public:

        ItemDeleteMsgV1() = default;

        //Serialization
        ItemDeleteMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

        //Variables
        enum VariableName
        {
            Id = 1,
        };
        Number id = Number(VariableName::Id);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::ItemDelete;};
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitCreateMsgV1 : public ToClientSubMessage
    {
    public:

        UnitCreateMsgV1() = default;

        //Serialization
        UnitCreateMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

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

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::UnitCreate;};
    };

    /////////////////////////////////////////////////////////////////////////

    class ConstructionQueueMsgV1
    {
    public:

        ConstructionQueueMsgV1() = default;

        //Serialization
        ConstructionQueueMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize();

        //Variables
        enum VariableName
        {
            BuildTime = 1,
            Queue = 2,
        };
        Number buildTime = Number(VariableName::BuildTime);
        Array queue = Array(VariableName::Queue);

        void PrintMsg();

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);

    };

    /////////////////////////////////////////////////////////////////////////

    class UnitUpdateMsgV1 : public ToClientSubMessage
    {
    public:

        UnitUpdateMsgV1() = default;

        //Serialization
        UnitUpdateMsgV1(const Array& fromArray);
        virtual std::shared_ptr<CStr> Serialize() override;
        void PrintMsg() override;

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

    private:

        void Deserialize(std::shared_ptr<CStr> fromString);

        virtual DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::UnitUpdate; }
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitSpecialActionMsgV1 : public ToClientSubMessage
    {
    public:

        UnitSpecialActionMsgV1() = default;

        //Serialization
        UnitSpecialActionMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

        //Variables
        enum VariableName
        {
            Id = 1,
            ActionIndex = 2,
        };
        Number id = Number(VariableName::Id);
        Number actionIndex = Number(VariableName::ActionIndex);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::UnitSpecialAction;};
    };

    /////////////////////////////////////////////////////////////////////////

    class UnitDeleteMsgV1 : public ToClientSubMessage
    {
    public:

        UnitDeleteMsgV1() = default;

        //Serialization
        UnitDeleteMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize();
        void PrintMsg() override;

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

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::UnitDelete;};
    };

    /////////////////////////////////////////////////////////////////////////

    class ProjectileCreateMsgV1 : public ToClientSubMessage
    {
    public:

        ProjectileCreateMsgV1() = default;

        //Serialization
        ProjectileCreateMsgV1(const Array& fromArray);
        std::shared_ptr<DsprMessage::CStr> Serialize() override;
        void PrintMsg() override;

        //Variables
        enum VariableName
        {
            From = 1,
            To = 2,
            Index = 3,
        };
        Array from = Array(VariableName::From);
        Array to = Array(VariableName::To);
        Number index = Number(VariableName::Index);

    private:

        void Deserialize(std::shared_ptr<DsprMessage::CStr> fromString);

        DsprMessage::ToClientMsg::MessageType getMessageType() override { return DsprMessage::ToClientMsg::MessageType::ProjectileCreate;};
    };
}