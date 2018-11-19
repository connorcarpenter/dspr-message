#pragma once

//
// Created by connor on 11/18/18.
//

namespace DsprMessage
{
    namespace ToServer {
        class ToServerMsg {
        public:
            void SetChatMsg(const char* cstr, int length) {}
            //std::string SerializeAsString();
        };
    }
}