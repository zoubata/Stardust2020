cmake_minimum_required(VERSION 2.8.3)
project(sd_main)

find_package(catkin REQUIRED COMPONENTS
)

catkin_package(
)

install(DIRECTORY
  config
  launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
