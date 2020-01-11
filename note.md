
## PC install

## instal Windows subsystem for linux ubuntu 16.04
### Xming
export DISPLAY=:0.0

###

## git
 ssh-keygen -t rsa -b 4096 -C "zoubata@yahoo.com"
  git clone git@github.com:zoubata/Stardust2020.git
  
  

## start robot

### for telecommand :
wifi startdust startdust2019
ssh r1@10.42.0.1

  cd stardust_v1_pierre/
  cd scripts/
  sudo rm /tmp/ros.pid
  ./start.sh

...

 ./stop.sh
 
 
 
 sudo kill -9 1530 1566 1577
ps -aux | grep ros

### serial port
#### linux
sudo usermod -a -G uucp username
sudo usermod -a -G dialout username
sudo usermod -a -G lock username
sudo usermod -a -G tty username
#### java :
https://fazecast.github.io/jSerialComm/
https://github.com/Fazecast/jSerialComm.git
