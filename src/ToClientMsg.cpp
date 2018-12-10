#include <vector>
#include "ToClientMsg.h"
#include "Main.h"
#include <string>
#include <assert.h>
#include <iostream>

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

        UnitUpdateMsgV1 aUU = UnitUpdateMsgV1(a.msgBytes);
        UnitUpdateMsgV1 bUU = UnitUpdateMsgV1(b.msgBytes);
        if (!UnitUpdateMsgV1::Equals(aUU, bUU))
        {
            return false;
        }

        ///TODO: MAKE THIS WORK FOR ALL TYPES OF MESSAGES!

        return true;
    }

    ////////////////////////////////////////////////

    ChatSendClientMsgV1::ChatSendClientMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> ChatSendClientMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->tribeIndex.serialize(charVector);
        this->chatMsg.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void ChatSendClientMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::TribeIndex:
                    index = this->tribeIndex.deserialize(index+1, fromString);
                    break;
                case VariableName::ChatMessage:
                    index = this->chatMsg.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    void ChatSendClientMsgV1::PrintMsg() {
        std::cout << "Sent: ChatMessage: " << this->chatMsg.toStdString() << std::endl;
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

    void EconomyUpdateMsgV1::PrintMsg() {
        std::cout << "Sent: EconomyUpdate: ";
        if (this->mana.getWasSet())
            std::cout << "mana: " << this->mana.get();
        if (this->pop.getWasSet())
            std::cout << "pop: " << this->pop.get();
        if (this->popMax.getWasSet())
            std::cout << "popMax: " << this->popMax.get();
        std::cout << std::endl;
    }

    ////////////////////////////////////////////////

    TribeSetMsgV1::TribeSetMsgV1(const Array& fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> TribeSetMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->tribeIndex.serialize(charVector);
        this->status.serialize(charVector);

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
                case VariableName::Status:
                    index = this->status.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    void TribeSetMsgV1::PrintMsg() {
        std::cout << "Sent: TribeSet: index: " << this->tribeIndex.get() << ", status: " << this->status.get() << std::endl;
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

    void TileCreateMsgV1::PrintMsg() {
        std::cout << "Sent: TileCreate: x: " << this->x.get() << " y: " << this->y.get() << " frame: " << this->frame.get() << std::endl;
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

    void GridCreateMsgV1::PrintMsg() {
        std::cout << "Sent: GridCreate: width: " << this->width.get() << " y: " << this->height.get() << std::endl;
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

    void ItemCreateMsgV1::PrintMsg() {
        std::cout << "Sent: ItemCreate: id: " << this->id.get() << " x: " << this->x.get() << " y: " << this->y.get() << " templateIndex: " << this->templateIndex.get() << std::endl;
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

    void ItemDeleteMsgV1::PrintMsg() {
        std::cout << "Sent: ItemDelete: id: " << this->id.get() << std::endl;
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

    void UnitCreateMsgV1::PrintMsg() {
        std::cout << "Sent: UnitCreate: id: " << this->id.get() << " x: " << this->x.get() << " y: " << this->y.get() << " tribeIndex: " << this->tribeIndex.get() << " templateIndex: " << this->templateIndex.get() << std::endl;
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

    void ConstructionQueueMsgV1::PrintMsg()
    {
        std::cout << " cq:";
        if (this->buildTime.getWasSet())
            std::cout << " buildTime: " << this->buildTime.get();
        if (this->queue.getWasSet())
        {
            std::cout << " queue: ";
            for(int i=0;i<queue.size();i++)
                std::cout << "," << this->queue.get(i);
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
                    auto realstr = fromString.get();
                    int i = 12;
                    break;
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

    void UnitUpdateMsgV1::PrintMsg() {
        std::cout << "Sent: UnitUpdate: id: " << this->id.get();
        if (this->nextPosition.getWasSet()) std::cout << " nextPosition: " << this->nextPosition.get(0) << "," << this->nextPosition.get(1);
        if (this->moveTarget.getWasSet()) std::cout << " moveTarget: " << this->moveTarget.get(0) << "," << this->moveTarget.get(1);
        if (this->animationState.getWasSet()) std::cout << " animationState: " << this->animationState.get(0) << "," << this->animationState.get(1);
        if (this->health.getWasSet()) std::cout << " health: " << this->health.get();
        if (this->bleed.getWasSet()) std::cout << " bleed: " << this->bleed.get();
        if (this->targetUnitId.getWasSet()) std::cout << " targetUnitId: " << this->targetUnitId.get();
        if (this->gatherYield.getWasSet()) std::cout << " gatherYield: " << this->gatherYield.get(0) << "," << this->gatherYield.get(1);
        if (this->constructionQueue.getWasSet()) {
            ConstructionQueueMsgV1 constructionQueueMsgV1 = ConstructionQueueMsgV1(this->constructionQueue);
            constructionQueueMsgV1.PrintMsg();
        }
        if (this->rallyPoint.getWasSet()) std::cout << " rallyPoint: " << this->rallyPoint.get(0) << "," << this->rallyPoint.get(1);
        if (this->rallyUnitId.getWasSet()) std::cout << " rallyUnitId: " << this->rallyUnitId.get();
        if (this->inventory.getWasSet()){
            std::cout << " inventory: ";
            for(int i = 0;i<this->inventory.size();i++)
            {
                std::cout << "," << this->inventory.get(i);
            }
        }
        std::cout << std::endl;
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

    void UnitDeleteMsgV1::PrintMsg() {
        std::cout << "Sent: UnitDelete: id: " << this->id.get() << " bleed: " << this->dead.get() << std::endl;
    }

    //////////////////////////////////////////////////////////////

    ProjectileCreateMsgV1::ProjectileCreateMsgV1(const Array &fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> ProjectileCreateMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->from.serialize(charVector);
        this->to.serialize(charVector);
        this->index.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void ProjectileCreateMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::From:
                    index = this->from.deserialize(index+1, fromString);
                    break;
                case VariableName::To:
                    index = this->to.deserialize(index+1, fromString);
                    break;
                case VariableName::Index:
                    index = this->index.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    void ProjectileCreateMsgV1::PrintMsg() {
        std::cout << "Sent: ProjectileCreate: (" << this->from.get(0) << "," << this->from.get(1) << ")->(" << this->to.get(0) << "," << this->to.get(1) << "), index: " << this->index.get() << std::endl;
    }

    ////////////////////////////////////////////////////////

    UnitSpecialActionMsgV1::UnitSpecialActionMsgV1(const Array &fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> UnitSpecialActionMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->id.serialize(charVector);
        this->actionIndex.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void UnitSpecialActionMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::Id:
                    index = this->id.deserialize(index+1, fromString);
                    break;
                case VariableName::ActionIndex:
                    index = this->actionIndex.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    void UnitSpecialActionMsgV1::PrintMsg() {
        std::cout << "Sent: UnitSpecialAction: id:" << this->id.get() << ", actionIndex: " << this->actionIndex.get() << std::endl;
    }

    ////////////////////////////////////////////////////////

    std::shared_ptr<DsprMessage::ToClientMsg> ToClientSubMessage::getToClientMessage() {

        this->PrintMsg();

        std::shared_ptr<CStr> serializedUnitUpdateMsg = this->Serialize();
        DsprMessage::ToClientMsg* clientMsg = new DsprMessage::ToClientMsg();
        assert(DsprMessage::ToClientMsg::MessageType::MessageTypeMaxValue < DsprMessage::MaxByteValue);
        clientMsg->msgType.set((unsigned char) this->getMessageType());
        clientMsg->msgBytes.loadFromCstr(serializedUnitUpdateMsg);

        //and, quickly test it comin back out again
        ////TODO: REMOVE THIS FOR PRODUCTION!!!!
        if (clientMsg->msgType.get() == DsprMessage::ToClientMsg::MessageType::UnitUpdate) {
            DsprMessage::ToClientMsg testMsg = DsprMessage::ToClientMsg(clientMsg->Pack());

            if (!DsprMessage::ToClientMsg::Equals(*clientMsg, testMsg))
            {
                int i = 12; //:(
            }
        }
        ////TODO: REMOVE THIS FOR PRODUCTION!!!!

        return std::shared_ptr<DsprMessage::ToClientMsg>(clientMsg);
    }


}