
This explain the basic with the robot.
- how to connect to each computer.


### connection to master ros :
This is a quad core  Intel(R) Core(TM) i7-6500U CPU @ 2.50GHz with 8Go ram, 16Go SSD.

host name : pierre-mensa

	wifi : mensa-host 301...
	windows : git shell
	linux : a terminal 
		ssh robot@10.42.0.1 
		pwd : r.
		

	windows : mstsc 
		host : 10.42.0.1
		module sesman-Xvnc
		login : pierre / you user
		pwd P!...
		nb : limitation just 1 x account open at the time
		
		
	VNC : 10.42.0.1:1 bele...
		n.b. : connection share



### connection to robot ros :
This is a raspberry pi 3+

host name : r1

wifi startdust startdust2019

	windows : git shell
	linux : a terminal 
		ssh r1@10.42.0.1
		pwd : r.
	
### ros connection :

#### work alone without the robot
on your envronement setup env variable :
ROS_MASTER_URI=http://localhost:11311
#### work on the robot :
kill roscore on our pc, if it is running
on your envronement setup env variable :
ROS_MASTER_URI=http://10.42.0.1:11311
connect to master ros computer.

#### test :
to check that your config is ok.
 ping 10.42.0.1 -c 3 -W 3
 rostopic list
 if you fail on ping, double check the wifi connection.
 if rostopic fail double check the env var, and state of robot.


### network wifi config:

    Open the terminal.
    Type ifconfig wlan0 and press Enter. You will not see any output in the terminal, as this command just turns your wireless card on. Most wireless cards are designated wlan0. If yours has a different designation, use that instead.
    Type iwconfig wlan0 essid name key password and press Enter. Replace name with the actual network name, and replace password with the actual security key for the network. If your wireless network does not require a security key, do not enter key password.
    Note: If you want to type the ASCII password, you would use iwconfig wlan0 essid name key s:password.
    Type dhclient wlan0 and press Enter to obtain an IP address and connect to the WiFi network.
