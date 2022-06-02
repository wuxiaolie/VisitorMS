#!/bin/sh

# 打印系统信息
echo "This is VisitorMS by HQ."

# 建立软链接
echo "----------------------------------"
echo "Configure library files ..."
cd ./src/lib/libcurl/lib
if [ -L libcurl.so ]
then
    echo "the libcurl.so exist"
else
    ln -s libcurl.so.4.6.0 libcurl.so
fi
if [ -L libcurl.so.4 ]
then
    echo "the libcurl.so.4 exist"
else
    ln -s libcurl.so.4.6.0 libcurl.so.4
fi
echo "Configuration library file succeeded!"

# 编译ftp程序
echo "----------------------------------"
echo "Start compile FTP module ..."
cd ../../ftp/
gcc ftp_client.c -o client -lpthread
gcc ftp_server.c -o server -lpthread
chmod 777 ftp_client_start.sh
chmod 777 ftp_server_start.sh
echo "FTP module compiled successfully!"

# 编译chat程序
echo "----------------------------------"
echo "Start compile chat module ..."
cd ../chat
chmod 777 *.sh
./gcc.sh
echo "Chat module compiled successfully!"

# 编译主程序
echo "----------------------------------"
echo "Start compile the VisitorMS ..."
cd ../../
make
mv VisitorMS ../
echo "VisitorMS created successfully!"
echo "----------------------------------"