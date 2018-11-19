#pragma once

//
// Created by connor on 11/18/18.
//

namespace DsprMessage
{
    class ToClientMsg {
    public:
        ToClientMsg();
        ToClientMsg(char* fromString);
        char* Serialize();

    private:
        void Deserialize(char* fromString);
    };
}