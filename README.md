# Stardust2020
Stardust2020 robot for 2020





## to record video with web cam

### install video

sudo apt-get install mplayer
sudo apt-get install vlc xawtv
sudo apt-get install vlc xawtv streamer ffmpeg
sudo apt install camorama
sudo apt install libav-tools
sudo apt-get install mplayer mencoder
sudo apt install mencoder

avconv -f oss -i /dev/dsp -f video4linux2 -s 320x240 -i /dev/video0 out.mpg
avconv -f oss -f video4linux2 -s 320x240 -i /dev/video0 out.mpg
ffmpeg -f oss -t 12 -f video4linux2 -s 320x240 -i /dev/video0 out.mpg


ls /dev/vide*
ls /dev/audio*

mplayer tv:// -tv driver=v4l2:device=/dev/video0:width=640:height=480
camorama
vlc v4l2:///dev/video0


### record video
streamer -q -c /dev/video0 -f rgb24 -r 3 -t 00:02:30 -o ~/outfile.avi

vlc v4l2:// :v4l-vdev="/dev/video0" :v4l-adev="/dev/audio2" :v4l-norm=3 :v4l-frequency=-1 :v4l-caching=300 :v4l-chroma="" :v4l-fps=-1.000000 :v4l-samplerate=44100 :v4l-channel=0 :v4l-tuner=-1 :v4l-audio=-1 :v4l-stereo :v4l-width=640 :v4l-height=480 :v4l-brightness=-1 :v4l-colour=-1 :v4l-hue=-1 :v4l-contrast=-1 :no-v4l-mjpeg :v4l-decimation=1 :v4l-quality=100



### ros & video

the package : cv_camera usb_cam




## lidar
### link until
http://wiki.ros.org/rplidar
http://www.ydlidar.com/download
https://github.com/YDLIDAR/ydlidar_ros/tree/s2


### install the lidar :

#### manual :
lsusb
ls /dev/ttyUSB*
udevadm info -a -n /dev/ttyUSB0 | grep '{serial}' | head -n1
udevadm info -a -n /dev/ttyUSB0 | grep '{idVendor}' 
udevadm info -a -n /dev/ttyUSB0 | grep '{idProduct}' 
udevadm info -a -n /dev/ttyUSB0 | grep '{serial}' 
sudo nano /etc/udev/rules.d/99-usb-serial.rules
or sudo nano /etc/udev/rules.d/70-snap.core.rules 
add line :
SUBSYSTEM=="tty", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", ATTRS{serial}=="0001", SYMLINK+="ydlidar"
sudo chmod a+rw /dev/ydlidar 
sudo chmod a+rw /dev/ttyUSB0 

#### automatic
roscd ydlidar/startup
sudo chmod 777 ./*
sudo sh initenv.sh

sudo chmod a+rw /dev/ydlidar 
sudo chmod a+rw /dev/ttyUSB0 


#### build & launch
sudo apt-get install libusb-1.0-0-dev
cd ros
catkin_make
source ./devel/setup.sh
roscd ydlidar/startup




roslaunch ydlidar lidar_view.launch
rosrun ydlidar ydlidar_client
roslaunch ydlidar lidar.launch


## joy
### linux install
sudo apt install python3-pip
sudo apt install python3-pyudev
sudo apt install python3-evdev
sudo apt install ds4drv
sudo pip3 install ds4drv
sudo apt install bluez
sudo pip3 install ds4drv
sudo apt-get install libusb-1.0-0-dev
sudo apt-get install libspnav-dev

#### install for ros package:

 sudo apt-get install ros-kinetic-joy
sudo apt-get install ros-kinetic-libusb
sudo apt-get install libusb-1.0-0-dev
 rosdep update
  
to compile ros joystick_drivers without:
-  fatal error: cwiid.h
-  fatal error: bluetooth/bluetooth.h:
-  fatal error: spnav.h:
-  libusb not found
.
sudo apt-get install libusb-1.0-0-dev
sudo apt-get install libspnav-dev
sudo apt-get install libbluetooth-dev
sudo apt-get install libcwiid-dev


sudo apt-get install jstest-gtk

#### test :
sudo ds4drv &
sudo chmod a+rw /dev/input/js0
jstest-gtk
jstest /dev/input/js0

#### test ros package

rosparam set joy_node/dev "/dev/input/js0"
roscore &
rosrun joy joy_node
  
## arduino
sudo apt-get install python-pip arduino
sudo apt-get install picocom
pip install ino
pip install PlatformIO
sudo apt-get install make cmake gcc gcc-avr
sudo apt-get install python-smbus
sudo apt-get install i2c-tools
apt install python3-pip
apt install bluez

## eclipse
sudo apt-get install eclipse gcc make arduino
sudo apt-get install eclipse gcc make arduino
eclipse
sudo apt install default-jdk
snap install eclipse --classic

## ros

### install :
we take ros kinetic on ubuntu 16.04 this is the only version supporting rosjava.


sudo apt-get update
sudo apt-get upgrade

sudo apt-get install gcc eclipse arduino
sudo apt-get install net-tools
sudo apt-get install openssh-server
sudo systemctl status ssh
sudo apt-get install libtiff-dev


sudo apt-get update
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
curl -sSL 'http://keyserver.ubuntu.com/pks/lookup?op=get&search=0xC1CF6E31E6BADE8868B172B4F42ED6FBAB17C654' | sudo apt-key add -
sudo apt-get update
sudo apt-get install ros-kinetic-desktop-full ros-kinetic-desktop
sudo apt-get install ros-kinetic-catkin ros-kinetic-rospack python-wstool openjdk-8-jdk
wstool init -j4 ~/rosjava/src https://raw.githubusercontent.com/rosjava/rosjava/kinetic/rosjava.rosinstall
rm -rf rosjava
mkdir -p ~/rosjava/src
wstool init -j4 ~/rosjava/src https://raw.githubusercontent.com/rosjava/rosjava/kinetic/rosjava.rosinstall
sudo rosdep init
rosdep update
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential
cd ~/rosjava
rosdep update
rosdep install --from-paths src -i -y
catkin_make
mkdir -p ~/rosjava_minimal
source /opt/ros/kinetic/setup.bash
cd ~/rosjava_minimal
rosdep update
rosdep install --from-paths src -i -y -r
catkin_make

sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential


source /opt/ros/kinetic/setup.bash
rosdep update
rosdep install --from-paths src -i -y
catkin_make
wstool merge https://raw.githubusercontent.com/me/rosinstalls/master/my_custom_msg_repos.rosinstall
wstool merge https://raw.githubusercontent.com/me/rosinstalls/master/my_custom_msg_repos.ros install
wstool set my_custom_msgs --git https://github.com/me/my_custom_msgs --version=kinetic-devel
cd ~/rosjava
catkin_make
mkdir -p ~/rosjava_minimal
source /opt/ros/kinetic/setup.bash
cd ~/rosjava_minimal
rosdep install --from-paths src -i -y -r
catkin_make
mkdir -p ~/myjava/src
cd ~/myjava/src
wstool init -j4 https://raw.githubusercontent.com/me/rosinstalls/master/my_custom_msg_repos.rosinstall
ls
wstool init -j4 https://raw.githubusercontent.com/me/rosinstalls/master/my_custom_msg_repos.ros install
wstool init -j4 https://raw.githubusercontent.com/me/rosinstalls/master/my_custom_msg_repos.rosinstall
source ~/rosjava/devel/setup.bash
cd ..
rosdep update
rosdep install --from-paths src -i -y
catkin_make



####
cd ..
catkin_make
source devel/setup.bash
history
cat ~/.bashrc
source /opt/ros/kinetic/setup.bash
  
  
## rosjava
###

## git
 ssh-keygen -t rsa -b 4096 -C "zoubata@yahoo.com"
  git clone git@github.com:zoubata/Stardust2020.git
  
  
  ## VNC
  sudo apt-get install realvnc-vnc-server realvnc-vnc-viewer
  478  sudo apt-get update
  479  sudo apt-get install realvnc-vnc-server realvnc-vnc-viewer
  480  sudo apt-get install tightvncserver
  481  vncserver --help
  482  vncserver :10 - geometry 1280x1024

sudo apt-get install tightvncserver

   sudo systemctl start vncserver@1
  228  sudo systemctl status vncserver@1
  229  sudo apt install openssh-server
  230  udo systemctl status ssh
  231  sudo systemctl status ssh
  
  ## remote connection with windows
  
 
  install xrdp on linux mini pc :
  
 sudo apt-get install xrdp
 sudo service xrdp restart
 ifconfig
 sudo systemctl enable xrdp
 sudo apt-get update
 sudo apt-get install xfce4
 echo xfce4-session > .xsession
  use mstsc on windows, with ip of ifconfig 
  
  ## ad linux user
  sudo adduser cassie
  
  ## swap
  add some swap to your PC
  sudo swapon -s
  cd ..
  sudo fallocate -l 4G /swapfile
  sudo chmod 600 /swapfile
  sudo mkswap /swapfile
  sudo swapon /swapfile
  
