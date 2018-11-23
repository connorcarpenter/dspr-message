//
// Created by connor on 11/19/18.
//

#include "ToServerMsg.h"
#include "Main.h"

namespace DsprMessage
{
    ToServerMsg::ToServerMsg(std::shared_ptr<CStr> fromString) {
        this->Unpack(fromString);
    }

    std::shared_ptr<CStr> ToServerMsg::Serialize() {
        std::shared_ptr<CharVector> charVector = DsprMessage::CharVector::make_charVector();
        this->authToken.serialize(charVector);
        this->msgType.serialize(charVector);
        this->msgBytes.serialize(charVector);
        return DsprMessage::CStr::make_cstr(charVector);
    }

    std::shared_ptr<CStr> ToServerMsg::Pack() {
        std::shared_ptr<CharVector> charVector = DsprMessage::CharVector::make_charVector();
        this->authToken.serialize(charVector);
        this->msgType.serialize(charVector);
        this->msgBytes.serialize(charVector);

        for (int i=0;i<charVector->size();i++)
        {
            charVector->addAt(DsprMessage::Modifier, i); //increment everything by our modifier
        }

        //charVector->push_back((unsigned char) DsprMessage::EscapeCharacter); //add escape character

        return DsprMessage::CStr::make_cstr(charVector);
    }

    void ToServerMsg::Unpack(std::shared_ptr<CStr> cstr) {
        for (int i=0;i<cstr->size();i++)
        {
            cstr->subtractAt(DsprMessage::Modifier, i);
        }
//        if (cstr->at(cstr->size()-1) == DsprMessage::EscapeCharacter)
//        {
//            cstr->subtractAt(DsprMessage::EscapeCharacter, cstr->size()-1);
//        }
//        else
//            cstr->subtractAt(DsprMessage::Modifier, cstr->size()-1);
        this->Deserialize(cstr);
    }

    void ToServerMsg::Deserialize(std::shared_ptr<CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            unsigned char name = fromString->at(index);
            switch(name)
            {
                case VariableName::AuthToken:
                    index = this->authToken.deserialize(index+1, fromString);
                    break;
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

    ////////////////////////////////////////////////

    ChatSendServerMsgV1::ChatSendServerMsgV1(const Array &fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> ChatSendServerMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->chatMsg.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void ChatSendServerMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::ChatMessage:
                    index = this->chatMsg.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    ////////////////////////////////////////////////

    UnitOrderMsgV1::UnitOrderMsgV1(const Array &fromArray) {
        this->Deserialize(DsprMessage::CStr::make_cstr(fromArray));
    }

    std::shared_ptr<DsprMessage::CStr> UnitOrderMsgV1::Serialize() {
        std::shared_ptr<CharVector> charVector = CharVector::make_charVector();
        this->unitIds.serialize(charVector);
        this->orderIndex.serialize(charVector);
        this->otherNumbers.serialize(charVector);

        return CStr::make_cstr(charVector);
    }

    void UnitOrderMsgV1::Deserialize(std::shared_ptr<DsprMessage::CStr> fromString) {
        int index = 0;
        while(index < fromString->size())
        {
            char name = fromString->at(index);
            switch(name)
            {
                case VariableName::UnitIds:
                    index = this->unitIds.deserialize(index+1, fromString);
                    break;
                case VariableName::OrderIndex:
                    index = this->orderIndex.deserialize(index+1, fromString);
                    break;
                case VariableName::OtherNumbers:
                    index = this->otherNumbers.deserialize(index+1, fromString);
                    break;
                default:
                    int i = 10;//blah... :(
            }
        }
    }

    /////////////////////////////////////////

    std::shared_ptr<DsprMessage::ToServerMsg> ToServerSubMessage::getToServerMessage() {
        std::shared_ptr<CStr> serializedUnitUpdateMsg = this->Serialize();
        DsprMessage::ToServerMsg* serverMsg = new DsprMessage::ToServerMsg();
        assert(DsprMessage::ToServerMsg::MessageType::MessageTypeMaxValue < DsprMessage::MaxByteValue);
        serverMsg->msgType.set((unsigned char) this->getMessageType());
        serverMsg->msgBytes.loadFromCstr(serializedUnitUpdateMsg);

        return std::shared_ptr<DsprMessage::ToServerMsg>(serverMsg);
    }
}