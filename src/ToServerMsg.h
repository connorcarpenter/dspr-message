#pragma once

//
// Created by connor on 11/18/18.
//

namespace DsprMessage
{
    class ToServerMsg {
    public:
        ToServerMsg();
        ToServerMsg(char* fromString);
        char* Serialize();

    private:
        void Deserialize(char* fromString);

    };
}