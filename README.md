# Stardust2020
Stardust2020 robot for 2020




## to record visdeo with web cam
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


#### launch

roslaunch ydlidar lidar_view.launch
rosrun ydlidar ydlidar_client
roslaunch ydlidar lidar.launch

## joy
to compile ros joystick_drivers without:
-  fatal error: cwiid.h
-  fatal error: bluetooth/bluetooth.h:
-  fatal error: spnav.h:
-  libusb not found
.
install :

sudo apt-get install libusb-1.0-0-dev
sudo apt-get install libspnav-dev
sudo apt-get install libbluetooth-dev
sudo apt-get install libcwiid-dev


cd ros
catkin_make
source ./devel/setup.sh
roscd ydlidar/startup





	static public final int PS3_BUTTON_SELECT   =         0;
	static public final int  PS3_BUTTON_STICK_LEFT      =  1;
	static public final int  PS3_BUTTON_STICK_RIGHT     =  2;
	static public final int  PS3_BUTTON_START           =  3;
	static public final int  PS3_BUTTON_CROSS_UP        =  4;
	static public final int  PS3_BUTTON_CROSS_RIGHT     =  5;
	static public final int  PS3_BUTTON_CROSS_DOWN      =  6;
	static public final int  PS3_BUTTON_CROSS_LEFT      =  7;
	static public final int  PS3_BUTTON_REAR_LEFT_2     =  8;
	static public final int  PS3_BUTTON_REAR_RIGHT_2    =  9;
	static public final int  PS3_BUTTON_REAR_LEFT_1     =  10;
	static public final int PS3_BUTTON_REAR_RIGHT_1     = 11;
	static public final int  PS3_BUTTON_ACTION_TRIANGLE =  12;
	static public final int  PS3_BUTTON_ACTION_CIRCLE   =  13;
	static public final int  PS3_BUTTON_ACTION_CROSS    =  14;
	static public final int  PS3_BUTTON_ACTION_SQUARE   =  15;
	static public final int  PS3_BUTTON_PAIRING         =  16;

	static public final int  PS3_AXIS_STICK_LEFT_LEFTWARDS  =  0;
	static public final int  PS3_AXIS_STICK_LEFT_UPWARDS    =  1;
	static public final int  PS3_AXIS_STICK_RIGHT_LEFTWARDS =  2;
	static public final int  PS3_AXIS_STICK_RIGHT_UPWARDS   =  3;
	static public final int  PS3_AXIS_BUTTON_CROSS_UP       =  4;
	static public final int  PS3_AXIS_BUTTON_CROSS_RIGHT    =  5;
	static public final int  PS3_AXIS_BUTTON_CROSS_DOWN     =  6;
	static public final int PS3_AXIS_BUTTON_CROSS_LEFT      = 7;
	static public final int  PS3_AXIS_BUTTON_REAR_LEFT_2    =  8;
	static public final int  PS3_AXIS_BUTTON_REAR_RIGHT_2   =  9;
	static public final int  PS3_AXIS_BUTTON_REAR_LEFT_1    =  10;
	static public final int  PS3_AXIS_BUTTON_REAR_RIGHT_1   =  11;
	static public final int  PS3_AXIS_BUTTON_ACTION_TRIANGLE=  12;
	static public final int  PS3_AXIS_BUTTON_ACTION_CIRCLE  =  13;
	static public final int  PS3_AXIS_BUTTON_ACTION_CROSS   =  14;
	static public final int  PS3_AXIS_BUTTON_ACTION_SQUARE  =  15;
	static public final int  PS3_AXIS_ACCELEROMETER_LEFT    =  16;
	static public final int  PS3_AXIS_ACCELEROMETER_FORWARD  = 17;
	static public final int  PS3_AXIS_ACCELEROMETER_UP      =  18;
	static public final int  PS3_AXIS_GYRO_YAW              =  19;
	
	static public final int PS4_BUTTON_OPTION   =         9;//option
	static public final int  PS4_BUTTON_STICK_LEFT      =  10;
	static public final int  PS4_BUTTON_STICK_RIGHT     =  11;
	static public final int  PS4_BUTTON_START           =  12;//ps4
	static public final int  PS4_BUTTON_PADDLE        =  13;
	/*
	static public final int  PS4_BUTTON_CROSS_UP        =  ;
	static public final int  PS4_BUTTON_CROSS_RIGHT     =  ;
	static public final int  PS4_BUTTON_CROSS_DOWN      =  ;
	static public final int  PS4_BUTTON_CROSS_LEFT      =  ;*/
	static public final int  PS4_BUTTON_REAR_LEFT_2     =  6;
	static public final int  PS4_BUTTON_REAR_RIGHT_2    =  7;
	static public final int  PS4_BUTTON_REAR_LEFT_1     =  4;
	static public final int PS4_BUTTON_REAR_RIGHT_1     = 5;
	static public final int  PS4_BUTTON_ACTION_TRIANGLE =  3;
	static public final int  PS4_BUTTON_ACTION_CIRCLE   =  2;
	static public final int  PS4_BUTTON_ACTION_CROSS    =  1;
	static public final int  PS4_BUTTON_ACTION_SQUARE   =  0;
	static public final int  PS4_BUTTON_SHARE         =  8;//share

	static public final int  PS4_AXIS_STICK_LEFT_LEFTWARDS  =  0;
	static public final int  PS4_AXIS_STICK_LEFT_UPWARDS    =  1;
	static public final int  PS4_AXIS_STICK_RIGHT_LEFTWARDS =  2;
	static public final int  PS4_AXIS_STICK_RIGHT_UPWARDS   =  5;
	static public final int  PS4_AXIS_BUTTON_CROSS_UPWARDS       =  10;
/*	static public final int  PS4_AXIS_BUTTON_CROSS_RIGHT    =  10;
	static public final int  PS4_AXIS_BUTTON_CROSS_DOWN     =  9;*/
	static public final int  PS4_AXIS_BUTTON_CROSS_LEFTWARDS      = 9;
	static public final int  PS4_AXIS_BUTTON_REAR_LEFT_2    =  3;
	static public final int  PS4_AXIS_BUTTON_REAR_RIGHT_2   =  4;
	/*
	static public final int  PS4_AXIS_BUTTON_REAR_LEFT_1    =  10;
	static public final int  PS4_AXIS_BUTTON_REAR_RIGHT_1   =  11;*//*
	static public final int  PS4_AXIS_BUTTON_ACTION_TRIANGLE=  12;
	static public final int  PS4_AXIS_BUTTON_ACTION_CIRCLE  =  13;
	static public final int  PS4_AXIS_BUTTON_ACTION_CROSS   =  14;
	static public final int  PS4_AXIS_BUTTON_ACTION_SQUARE  =  15;*/
	static public final int  PS4_AXIS_ACCELEROMETER_LEFT    =  6;
	static public final int  PS4_AXIS_ACCELEROMETER_FORWARD  = 7;
	static public final int  PS4_AXIS_ACCELEROMETER_UP      =  8;
	static public final int  PS4_AXIS_GYRO_XAW              =  13;
	static public final int  PS4_AXIS_GYRO_YAW              =  11;
	static public final int  PS4_AXIS_GYRO_ZAW              =  12;
	
	
	
