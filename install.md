This file describe the install point to take care.
 
 
# install information

it include :
* sotf :
- arduino tools
- eclipse
- ros
- ros java
* hard :
- video
- lidar x4
- lidar x2
- joy
. 
 
 
 

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
### install on windows 10 oof melodic.
follow : http://wiki.ros.org/Installation/Windows
once done, start cmd in administrator mode.
run :
"C:\Program Files (x86)\Microsoft Visual Studio\VC98\Bin\VCvars32.BAT"  -arch=amd64 -host_arch=amd64
C:\opt\ros\melodic\x64\setup.bat

you are ready.


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


#### build
cd ..
catkin_make
source devel/setup.bash
history
cat ~/.bashrc
source /opt/ros/kinetic/setup.bash
  
  

## rosjava

### install
after ros installation
sudo apt-get install ros-kinetic-rosjava

#### install java 11
sudo apt-get update && apt-get upgrade
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:linuxuprising/java
sudo apt-get update
sudo apt-get install oracle-java13-installer

### use it from a template project with eclipse :

#### get a project copy :
download : https://github.com/zoubata/rosjavaTemplate/archive/master.zip
curl https://github.com/zoubata/rosjavaTemplate/archive/master.zip>master.zip

import project in eclipse
make a run config : 
- main class : org.ros.RosRun
- arguments  : com.github.rosjava.com_zoubworld_odometry.com_zoubworld_odometry.Talker
start a roscore & on a shell
run it!
 

### use it from scratf
#### create workspace
mkdir -p ~/myjava/src
cd ~/myjava/src
source /opt/ros/kinetic/setup.bash
catkin_init_workspace
cd ~/myjava
catkin_make

#### create  package
cd src
 catkin_create_rosjava_pkg rosjava_catkin_package_a
 cd ..
 catkin_make
 source devel/setup.bash
 
#### create binary project
cd src/rosjava_catkin_package_a
catkin_create_rosjava_project rosjava_gradle_subproject_a
cd ../..
catkin_make


#### create library project
 cd src/rosjava_catkin_package_a
 catkin_create_rosjava_library_project rosjava_gradle_subproject_b
 cd ../..
 catkin_make
 
 
#### generate eclipse project
cd package
nano build.gradle
uncomment  apply plugin: "eclipse"
./gradlew eclipse




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
ffmpeg -f oss -t 12 -f video4linux2 -s 320x240 -i /dev/video0 ~/video/out.mpg

ffmpeg -f x11grab -t 10  -r 25 -f video4linux2 -s 1920x1080 -i /dev/video0 -vcodec libx264  ~/video/out$(date +%Y-%m-%d_%H-%M-%S).mpg

-f pulse -ac 2  -f x11grab -r 30 -s 1920x1080

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
define by pid/vid/serial
	SUBSYSTEM=="tty", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", ATTRS{serial}=="0001", SYMLINK+="ydlidar"
define by usb path :
	KERNEL=="ttyUSB*", KERNELS=="1-4:1.0", SYMLINK+="ydlidar"
	KERNEL=="ttyUSB*", KERNELS=="1-3:1.0", SYMLINK+="ydlidarX2"

udevadm info -a -n /dev/ttyUSB1 | grep '{serial}' | head -n1
udevadm info -a -n /dev/ttyUSB1 | grep '{idVendor}' 
udevadm info -a -n /dev/ttyUSB1 | grep '{idProduct}' 
udevadm info -a -n /dev/ttyUSB1 | grep '{serial}' 

##### give access rigth to tty
sudo chmod a+rw /dev/ydlidar 
sudo chmod a+rw /dev/ttyUSB0 
sudo usermod -a -G dialout $USER
groups $USER

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



## install lidar x2
download on http://www.ydlidar.com/download X2 files
unzip Ros.zip 


#### on utunbu 16.04
follow Reamdme.md 
#### on wsl : Win10 Wsl ubuntu 16.04
on catkin_ws\src\launch\display.launch & catkin_ws\src\launch\lidar.launch rename :
 <param name="port"         type="string" value="/dev/ydlidar"/>  
  <param name="port"         type="string" value="/dev/ttyS5"/>  

if com5 so it is ttyS5
rm /var/lock/LCK..ttyS5
sudo chmod 666 /dev/ttyS5
sudo apt install cu
stty -F /dev/ttyS5 raw 115200
sudo cu -l /dev/ttyS5 -s 115200
ctrl+c

roslaunch ydlidar lidar_view.launch
 
 
 
 

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
  
# specific for robot/mat


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
  

###ftp server


707  sudo apt-get install vsftpd
  708  sudo cp /etc/vsftpd.conf /etc/vsftpd.conf.orig
  709  sudo ufw status
  710  sudo ufw allow 20/tcp
  711  sudo ufw allow 21/tcp
  712  sudo ufw allow 990/tcp
  713  sudo ufw allow 40000:50000/tcp
  714  sudo ufw status
  715  sudo mkdir ~/ftp
  716  sudo chown nobody:nogroup ~/ftp
  717  sudo nano /etc/vsftpd.conf
  718  exit
  719  fg
  720  sudo systemctl restart vsftpd
