#include <vector>
#include "ToClientMsg.h"
#include <string>
#include <assert.h>

namespace DsprMessage
{
    ToClientMsg::ToClientMsg() {

    }

    ToClientMsg::ToClientMsg(_cstr fromString) {
        this->Unpack(fromString);
    }

    _cstr ToClientMsg::Serialize() {
        _charVector* charVector = new _charVector();
        this->msgType.serialize(charVector);
        this->msgBytes.serialize(charVector);

        return _cstr::finalVector(charVector);
    }

    void ToClientMsg::Deserialize(_cstr fromString) {
        int index = 0;
        while(index < fromString.number)
        {
            if (fromString.innerCstr[index] == '\1')break;
            unsigned char name = fromString.getDs(index);
            switch(name)
            {
                case VariableName::MsgType:
                    index = this->msgType.deserialize(index+1, fromString);
                    break;
                case VariableName::MsgBytes:
                    index = this->msgBytes.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    bool ToClientMsg::Equals(ToClientMsg *a, ToClientMsg *b) {
        if (a->msgType.get() != b->msgType.get())
        {
            return false;
        }
        UnitUpdateMsgV1* aUU = new UnitUpdateMsgV1(a->msgBytes.getCstr());
        UnitUpdateMsgV1* bUU = new UnitUpdateMsgV1(b->msgBytes.getCstr());
        if (!UnitUpdateMsgV1::Equals(aUU, bUU))
        {
            return false;
        }
        return true;

    }

    _cstr ToClientMsg::Pack() {
        _cstr cstr = this->Serialize();
        for (int i=0;i<cstr.number-1;i++)
        {
            cstr.innerCstr[i] += DsprMessage::Modifier;
        }
        return cstr;
    }

    void ToClientMsg::Unpack(_cstr cstr) {
        for (int i=0;i<cstr.number-1;i++)
        {
            cstr.innerCstr[i] -= DsprMessage::Modifier;
        }
        this->Deserialize(cstr);
    }

    ////////////////////////////////////////////////

    ChatSendClientMsgV1::ChatSendClientMsgV1() {

    }

    ChatSendClientMsgV1::ChatSendClientMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr ChatSendClientMsgV1::Serialize() {

    }

    void ChatSendClientMsgV1::Deserialize(_cstr fromString) {

    }

    ////////////////////////////////////////////////

    EconomyUpdateMsgV1::EconomyUpdateMsgV1() {

    }

    EconomyUpdateMsgV1::EconomyUpdateMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr EconomyUpdateMsgV1::Serialize() {
        return _cstr(nullptr, 0);
    }

    void EconomyUpdateMsgV1::Deserialize(_cstr fromString) {

    }

    ////////////////////////////////////////////////
    TribeSetMsgV1::TribeSetMsgV1() {

    }

    TribeSetMsgV1::TribeSetMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr TribeSetMsgV1::Serialize() {

    }

    void TribeSetMsgV1::Deserialize(_cstr fromString) {

    }

    ////////////////////////////////////////////////

    TileCreateMsgV1::TileCreateMsgV1() {

    }

    TileCreateMsgV1::TileCreateMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr TileCreateMsgV1::Serialize() {

    }

    void TileCreateMsgV1::Deserialize(_cstr fromString) {

    }

    ////////////////////////////////////////////////
    GridCreateMsgV1::GridCreateMsgV1() {

    }

    GridCreateMsgV1::GridCreateMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr GridCreateMsgV1::Serialize() {

    }

    void GridCreateMsgV1::Deserialize(_cstr fromString) {

    }

    ////////////////////////////////////////////////////////

    ItemCreateMsgV1::ItemCreateMsgV1() {

    }

    ItemCreateMsgV1::ItemCreateMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr ItemCreateMsgV1::Serialize() {

    }

    void ItemCreateMsgV1::Deserialize(_cstr fromString) {

    }

    ////////////////////////////////////////////////////////

    ItemDeleteMsgV1::ItemDeleteMsgV1() {

    }

    ItemDeleteMsgV1::ItemDeleteMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr ItemDeleteMsgV1::Serialize() {
        return _cstr(nullptr, 0);
    }

    void ItemDeleteMsgV1::Deserialize(_cstr fromString) {

    }

    ////////////////////////////////////////////////////////

    UnitCreateMsgV1::UnitCreateMsgV1() {

    }

    UnitCreateMsgV1::UnitCreateMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr UnitCreateMsgV1::Serialize() {

    }

    void UnitCreateMsgV1::Deserialize(_cstr fromString) {

    }

    ////////////////////////////////////////////////////////

    ConstructionQueueMsgV1::ConstructionQueueMsgV1() {

    }

    ConstructionQueueMsgV1::ConstructionQueueMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr ConstructionQueueMsgV1::Serialize() {
        _charVector* charVector = new _charVector();
        this->buildTime.serialize(charVector);
        this->queue.serialize(charVector);

        return _cstr::fromVector(charVector);
    }

    void ConstructionQueueMsgV1::Deserialize(_cstr fromString) {
        int index = 0;
        while(index < fromString.number)
        {
            char name = fromString.getDs(index);
            switch(name)
            {
                case VariableName::BuildTime:
                    index = this->buildTime.deserialize(index+1, fromString);
                    break;
                case VariableName::Queue:
                    index = this->queue.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////
    UnitUpdateMsgV1::UnitUpdateMsgV1() {

    }

    UnitUpdateMsgV1::UnitUpdateMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr UnitUpdateMsgV1::Serialize() {
        _charVector* charVector = new _charVector();
        this->id.serialize(charVector);
        this->nextPosition.serialize(charVector);
        this->moveTarget.serialize(charVector);
        this->animationState.serialize(charVector);
        this->health.serialize(charVector);
        this->bleed.serialize(charVector);
        this->targetUnitId.serialize(charVector);
        this->gatherYield.serialize(charVector);
        this->constructionQueue.serialize(charVector);
        this->rallyPoint.serialize(charVector);
        this->rallyUnitId.serialize(charVector);
        this->inventory.serialize(charVector);

        return _cstr::fromVector(charVector);
    }

    void UnitUpdateMsgV1::Deserialize(_cstr fromString) {
        int index = 0;
        while(index < fromString.number)
        {
            char name = fromString.getDs(index);
            switch(name)
            {
                case VariableName::Id:
                    index = this->id.deserialize(index+1, fromString);
                    break;
                case VariableName::NextPosition:
                    index = this->nextPosition.deserialize(index+1, fromString);
                    break;
                case VariableName::MoveTarget:
                    index = this->moveTarget.deserialize(index+1, fromString);
                    break;
                case VariableName::AnimationState:
                    index = this->animationState.deserialize(index+1, fromString);
                    break;
                case VariableName::Health:
                    index = this->health.deserialize(index+1, fromString);
                    break;
                case VariableName::Bleed:
                    index = this->bleed.deserialize(index+1, fromString);
                    break;
                case VariableName::TargetUnitId:
                    index = this->targetUnitId.deserialize(index+1, fromString);
                    break;
                case VariableName::GatherYield:
                    index = this->gatherYield.deserialize(index+1, fromString);
                    break;
                case VariableName::ConstructionQueue:
                    index = this->constructionQueue.deserialize(index+1, fromString);
                    break;
                case VariableName::RallyPoint:
                    index = this->rallyPoint.deserialize(index+1, fromString);
                    break;
                case VariableName::RallyUnitId:
                    index = this->rallyUnitId.deserialize(index+1, fromString);
                    break;
                case VariableName::Inventory:
                    index = this->inventory.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    bool UnitUpdateMsgV1::Equals(UnitUpdateMsgV1 *a, UnitUpdateMsgV1 *b) {
        if (!DsprMessage::_array::Equals(a->nextPosition, b->nextPosition))
            return false;
        if (!DsprMessage::_array::Equals(a->moveTarget, b->moveTarget))
            return false;
        if (!DsprMessage::_array::Equals(a->animationState, b->animationState))
            return false;
        if (!DsprMessage::_number::Equals(a->health, b->health))
            return false;
        if (!DsprMessage::_number::Equals(a->bleed, b->bleed))
            return false;
        if (!DsprMessage::_number::Equals(a->targetUnitId, b->targetUnitId))
            return false;
        if (!DsprMessage::_array::Equals(a->gatherYield, b->gatherYield))
            return false;
        if (!DsprMessage::_array::Equals(a->constructionQueue, b->constructionQueue))
            return false;
        if (!DsprMessage::_array::Equals(a->rallyPoint, b->rallyPoint))
            return false;
        if (!DsprMessage::_number::Equals(a->rallyUnitId, b->rallyUnitId))
            return false;
        if (!DsprMessage::_array::Equals(a->inventory, b->inventory))
            return false;
        return true;
    }

    _cstr UnitUpdateMsgV1::SerializeFinal() {
        _cstr serializedUnitUpdateMsg = this->Serialize();
        DsprMessage::ToClientMsg* clientMsg = new DsprMessage::ToClientMsg();
        assert(DsprMessage::ToClientMsg::MessageType::MessageTypeMaxValue < DsprMessage::MaxByteValue);
        clientMsg->msgType.set((unsigned char) DsprMessage::ToClientMsg::MessageType::UnitUpdate);
        clientMsg->msgBytes.setCstr(serializedUnitUpdateMsg);
        auto serializedClientMsg = clientMsg->Pack();

        //and, quickly test it comin back out again
        ////TODO: REMOVE THIS FOR PRODUCTION!!!!
        DsprMessage::ToClientMsg* testMsg = new DsprMessage::ToClientMsg(serializedClientMsg);

        if (!DsprMessage::ToClientMsg::Equals(clientMsg, testMsg))
        {
            int i = 12; //:(
        }
        ////TODO: REMOVE THIS FOR PRODUCTION!!!!

        return serializedClientMsg;
    }

    ////////////////////////////////////////////////////////
    UnitDeleteMsgV1::UnitDeleteMsgV1() {

    }

    UnitDeleteMsgV1::UnitDeleteMsgV1(_cstr fromString) {
        this->Deserialize(fromString);
    }

    _cstr UnitDeleteMsgV1::Serialize() {

    }

    void UnitDeleteMsgV1::Deserialize(_cstr fromString) {

    }
}