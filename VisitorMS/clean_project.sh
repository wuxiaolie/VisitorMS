#!/bin/sh

# 打印系统信息
echo "This is VisitorMS by HQ."

# 清理ftp程序
echo "----------------------------------"
echo "Start clean FTP module ..."
cd ./src/lib/ftp
rm client server
echo "FTP module cleanup succeeded!"

# 卸载驱动模块
echo "----------------------------------"
echo "rmmod pin4driver.ko ..."
cd ../drivers
sudo rmmod pin4driver.ko
echo "Driver module uninstalled successfully!"
rm pin4driver
echo "Driver module cleanup succeeded!"

# 清理chat程序
echo "----------------------------------"
echo "Start clean chat module ..."
cd ../chat
./clean.sh
echo "Chat module cleanup succeeded!"

# 编译主程序
echo "----------------------------------"
echo "Start clean the VisitorMS ..."
cd ../../
make clean
cd ../
rm VisitorMS
echo "VisitorMS cleanup succeeded!"
echo "----------------------------------"