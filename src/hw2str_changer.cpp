/* Thomas Brefeld Jr.
Topics in CS: Intelligent Robotics with ROS
02/05/2020
CJ Chung, PhD and Nick Paul, MSCS
Homework Assignment #2  */

#include <ros/ros.h>
#include <std_msgs/String.h>
#include "my_ros_test/MyStr.h"
#include <string>

//creates global var to hold publisher
ros::Publisher pub;

void callback_topic(const my_ros_test::MyStr& msg){
    //creates a string of temp
    std_msgs::String temp;
    //switch statment to compare the command values
    switch(msg.com){
        case(1):
            //prints the string in all caps
            for(int x = 0; x < msg.str.length(); ++x){
                temp.data += toupper(msg.str[x]);
            }
            break;
        case(2):
            //prints the string in reverse
            for(int x = msg.str.length() - 1; x >= 0; --x){
                temp.data += msg.str[x];
            }
            break;
        default:
            //prints the string as normal
            temp.data += msg.str;
        }
    //publishes the new string
    pub.publish(temp);
}


int main(int argc, char **argv){
    ros::init(argc, argv, "hw2str_changer");
    ros::NodeHandle nh;
    
    //subscribes to topic /hw2_topic
    ros::Subscriber sub = nh.subscribe("/hw2_topic", 1000, callback_topic);
    //publishes to /hw2_topic_str_changed
    pub = nh.advertise<std_msgs::String>("/hw2topic_str_changed", 10);
    ros::spin();
}