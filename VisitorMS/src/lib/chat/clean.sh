#!/bin/bash
cd ./chat_server/ 
make clean 

cd ../chat_client/ 
make clean 
cd ..
rm server
rm client
