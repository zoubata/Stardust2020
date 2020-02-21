#!/usr/bin/env python
#coding: utf-8

'''
author: pierre valleau
date: 10/01/2020
description: Node used to start command on unix/windows shell
The goal is to execute command a specific time on host of the node.

for example to record something:

rostopic pub /mat_central/execute std_msgs/String "ffmpeg -f x11grab -t 120  -r 25 -f video4linux2 -s 1280x720 -i /dev/video0 -vcodec libx264 ~/video/out$(date +%Y-%m-%d_%H-%M-%S).mpg" --once

rostopic pub /mat_central/execute std_msgs/String "rosbag record --all --bz2 --output-name=/home/robot/video/bag$(date +%Y-%m-%d_%H-%M-%S).bag --duration=120.0" --once

'''

import numpy as np
import cv2
import datetime
import rospy
import os
from os.path import expanduser
from std_msgs.msg import String
from time import sleep


reccord = False
host = os.getenv('HOST') 
loop = True
def callBackEndRecording(data):
	print ("recieve ")
	print (data.data)
	os.system(data.data)
	reccord = True


if __name__ == '__main__':
	# init node
	#rospy.init_node(str(host)+"cmd_executor")
	rospy.init_node("sd_execute_node")

	# get param names
	TOPIC_END_RECORD = rospy.get_param('~topic_execute')
	rospy.Subscriber(TOPIC_END_RECORD, String, callBackEndRecording)

	# get the folder name
	FOLDER_NAME = rospy.get_param('~identity')
	home = expanduser("~")
	pathFolder = home + "/outputMemory/" + FOLDER_NAME
	# create directory if does not exists
	#try:
	#	os.stat(pathFolder)
	#except:
	#	os.makedirs(pathFolder)
	print ("Welcome to node sd_execute_node")

	# cretae video file
	#date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
	#path = pathFolder + "/outputVideo_" + date + ".avi"

	

	while loop == True:
		sleep(0.10)
	#	os.system("rostopic list")
		if reccord==True:
			print ("start")
		#	os.system("rosnode list")
			reccord=False
	rospy.spin()





