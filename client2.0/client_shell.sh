#!bin/bash
#client_shell.sh
#sleep 3
export LD_LIBRARY_PATH="/home/junyu/Desktop/client2.0/HCNetSDKCom" 
cd /home/junyu/Desktop/client2.0/build
./client 192.168.1.65 8000 admin 1234567890a 127.0.0.1 6666
