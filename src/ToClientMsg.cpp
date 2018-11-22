#include <vector>
#include "ToClientMsg.h"
#include "Main.h"
#include <string>
#include <assert.h>

namespace DsprMessage
{
    ToClientMsg::ToClientMsg(std::shared_ptr<CStr> fromString) {
        this->Unpack(fromString);
    }

    std::shared_ptr<CStr> ToClientMsg::Serialize()
    {
        std::shared_ptr<CharVector> charVector = DsprMessage::CharVector::make_charVector();
        this->msgType.serialize(charVector);
        this->msgBytes.serialize(charVector);
        return DsprMessage::CStr::make_cstr(charVector);
    }

    std::shared_ptr<CStr> ToClientMsg::Pack()
    {
        std::shared_ptr<CharVector> charVector = DsprMessage::CharVector::make_charVector();
        this->msgType.serialize(charVector);
        this->msgBytes.serialize(charVector);

        for (int i=0;i<charVector->size();i++)
        {
            charVector->addAt(DsprMessage::Modifier, i); //increment everything by our modifier
        }

        charVector->push_back((unsigned char) DsprMessage::EscapeCharacter); //add escape character

        return DsprMessage::CStr::make_cstr(charVector);
    }

    void ToClientMsg::Unpack(std::shared_ptr<DsprMessage::CStr> cstr) {
        for (int i=0;i<cstr->size()-1;i++)
        {
            cstr->subtractAt(DsprMessage::Modifier, i);
        }
        if (cstr->at(cstr->size()-1) == DsprMessage::EscapeCharacter)
        {
            cstr->subtractAt(DsprMessage::EscapeCharacter, cstr->size()-1);
        }
        else
            cstr->subtractAt(DsprMessage::Modifier, cstr->size()-1);
        this->Deserialize(cstr);
    }

    void ToClientMsg::Deserialize(std::shared_ptr<CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            unsigned char name = fromString->at(index);
            switch(name)
            {
                case VariableName::MsgType:
                    index = this->msgType.deserialize(index+1, fromString);
                    break;
                case VariableName::MsgBytes:
                    index = this->msgBytes.deserialize(index+1, fromString);
                    break;
                case '\0': {
                    int i = 10;
                    index = fromString->size();
                }
                    break;
                default: {
                    int i = 10;//blah... :(
                    index = fromString->size();
                }
                    break;
            }
        }
    }

    bool ToClientMsg::Equals(const ToClientMsg& a, const ToClientMsg& b) {
        if (a.msgType.get() != b.msgType.get())
        {
            return false;
        }

        ///TODO: MAKE THIS WORK FOR ALL TYPES OF MESSAGES!

//        UnitUpdateMsgV1 aUU = UnitUpdateMsgV1(a.msgBytes);
//        UnitUpdateMsgV1 bUU = UnitUpdateMsgV1(b.msgBytes);
//        if (!UnitUpdateMsgV1::Equals(aUU, bUU))
//        {
//            return false;
//        }

        ///TODO: MAKE THIS WORK FOR ALL TYPES OF MESSAGES!

        return true;
    }

    ////////////////////////////////////////////////

    ChatSendClientMsgV1::ChatSendClientMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> ChatSendClientMsgV1::Serialize() {

    }

    void ChatSendClientMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {

    }

    ////////////////////////////////////////////////

    EconomyUpdateMsgV1::EconomyUpdateMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> EconomyUpdateMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->mana.serialize(charVector);
        this->pop.serialize(charVector);
        this->popMax.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void EconomyUpdateMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::Mana:
                    index = this->mana.deserialize(index+1, fromString);
                    break;
                case VariableName::Pop:
                    index = this->pop.deserialize(index+1, fromString);
                    break;
                case VariableName::PopMax:
                    index = this->popMax.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////

    TribeSetMsgV1::TribeSetMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> TribeSetMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->tribeIndex.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void TribeSetMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::TribeIndex:
                    index = this->tribeIndex.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////

    TileCreateMsgV1::TileCreateMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> TileCreateMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->x.serialize(charVector);
        this->y.serialize(charVector);
        this->frame.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void TileCreateMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::X:
                    index = this->x.deserialize(index+1, fromString);
                    break;
                case VariableName::Y:
                    index = this->y.deserialize(index+1, fromString);
                    break;
                case VariableName::Frame:
                    index = this->frame.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////

    GridCreateMsgV1::GridCreateMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> GridCreateMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->width.serialize(charVector);
        this->height.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void GridCreateMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::Width:
                    index = this->width.deserialize(index+1, fromString);
                    break;
                case VariableName::Height:
                    index = this->height.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////////////

    ItemCreateMsgV1::ItemCreateMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> ItemCreateMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->id.serialize(charVector);
        this->x.serialize(charVector);
        this->y.serialize(charVector);
        this->templateIndex.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void ItemCreateMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::Id:
                    index = this->id.deserialize(index+1, fromString);
                    break;
                case VariableName::X:
                    index = this->x.deserialize(index+1, fromString);
                    break;
                case VariableName::Y:
                    index = this->y.deserialize(index+1, fromString);
                    break;
                case VariableName::TemplateIndex:
                    index = this->templateIndex.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////////////

    ItemDeleteMsgV1::ItemDeleteMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> ItemDeleteMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->id.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void ItemDeleteMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::Id:
                    index = this->id.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////////////

    UnitCreateMsgV1::UnitCreateMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> UnitCreateMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->id.serialize(charVector);
        this->x.serialize(charVector);
        this->y.serialize(charVector);
        this->tribeIndex.serialize(charVector);
        this->templateIndex.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void UnitCreateMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::Id:
                    index = this->id.deserialize(index+1, fromString);
                    break;
                case VariableName::X:
                    index = this->x.deserialize(index+1, fromString);
                    break;
                case VariableName::Y:
                    index = this->y.deserialize(index+1, fromString);
                    break;
                case VariableName::TribeIndex:
                    index = this->tribeIndex.deserialize(index+1, fromString);
                    break;
                case VariableName::TemplateIndex:
                    index = this->templateIndex.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////////////

    ConstructionQueueMsgV1::ConstructionQueueMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> ConstructionQueueMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->buildTime.serialize(charVector);
        this->queue.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void ConstructionQueueMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
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

    UnitUpdateMsgV1::UnitUpdateMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<CStr> UnitUpdateMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
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

        return CStr::make_cstr(charVector);
    }

    void UnitUpdateMsgV1::Deserialize(std::shared_ptr<CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
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

    bool UnitUpdateMsgV1::Equals(const UnitUpdateMsgV1& a, const UnitUpdateMsgV1& b) {
        if (!DsprMessage::Array::Equals(a.nextPosition, b.nextPosition))
            return false;
        if (!DsprMessage::Array::Equals(a.moveTarget, b.moveTarget))
            return false;
        if (!DsprMessage::Array::Equals(a.animationState, b.animationState))
            return false;
        if (!DsprMessage::Number::Equals(a.health, b.health))
            return false;
        if (!DsprMessage::Number::Equals(a.bleed, b.bleed))
            return false;
        if (!DsprMessage::Number::Equals(a.targetUnitId, b.targetUnitId))
            return false;
        if (!DsprMessage::Array::Equals(a.gatherYield, b.gatherYield))
            return false;
        if (!DsprMessage::Array::Equals(a.constructionQueue, b.constructionQueue))
            return false;
        if (!DsprMessage::Array::Equals(a.rallyPoint, b.rallyPoint))
            return false;
        if (!DsprMessage::Number::Equals(a.rallyUnitId, b.rallyUnitId))
            return false;
        if (!DsprMessage::Array::Equals(a.inventory, b.inventory))
            return false;
        return true;
    }

    ////////////////////////////////////////////////////////

    UnitDeleteMsgV1::UnitDeleteMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> UnitDeleteMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->id.serialize(charVector);
        this->dead.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void UnitDeleteMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::Id:
                    index = this->id.deserialize(index+1, fromString);
                    break;
                case VariableName::Dead:
                    index = this->dead.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////////////

    std::shared_ptr<DsprMessage::ToClientMsg> ToClientSubMessage::getToClientMessage() {
        std::shared_ptr<CStr> serializedUnitUpdateMsg = this->Serialize();
        DsprMessage::ToClientMsg* clientMsg = new DsprMessage::ToClientMsg();
        assert(DsprMessage::ToClientMsg::MessageType::MessageTypeMaxValue < DsprMessage::MaxByteValue);
        clientMsg->msgType.set((unsigned char) this->getMessageType());
        clientMsg->msgBytes.loadFromCstr(serializedUnitUpdateMsg);

        //and, quickly test it comin back out again
        ////TODO: REMOVE THIS FOR PRODUCTION!!!!
        DsprMessage::ToClientMsg testMsg = DsprMessage::ToClientMsg(clientMsg->Pack());

        if (!DsprMessage::ToClientMsg::Equals(*clientMsg, testMsg))
        {
            int i = 12; //:(
        }
        ////TODO: REMOVE THIS FOR PRODUCTION!!!!

        return std::shared_ptr<DsprMessage::ToClientMsg>(clientMsg);
    }
}