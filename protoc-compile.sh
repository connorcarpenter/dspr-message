#!/usr/bin/env bash

./protoc -I=. --cpp_out=. ./dspr-message-toclient.proto
./protoc -I=. --cpp_out=. ./dspr-message-toserver.proto