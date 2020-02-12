/* Thomas Brefeld Jr.
Topics in CS: Intelligent Robotics with ROS
02/05/2020
CJ Chung, PhD and Nick Paul, MSCS
Homework Assignment #2  */

#include <ros/ros.h>
#include <std_msgs/String.h>
#include "my_ros_test/MyStr.h"

//creates a global var to hold the loop count
int x = 0;

void callback_topic(const std_msgs::String& msg){
    ++x;
    //prints the msg and how many times its has looped
    ROS_INFO_STREAM(" Msg received: " << msg.data << ", " << x);
}


int main(int argc, char **argv){
    ros::init(argc, argv, "hw2str_sub");
    ros::NodeHandle nh;
    //subscribes to /hw2topic_str_changed
    ros::Subscriber sub = nh.subscribe("/hw2topic_str_changed", 1000, callback_topic);
    ros::spin();
}