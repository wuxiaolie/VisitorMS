#!/bin/bash
cd ./chat_server/   
make
mv ./bin/server ../ 

cd ../chat_client/
make
mv ./bin/client ../
