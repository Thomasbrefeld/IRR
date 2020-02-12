/* Thomas Brefeld Jr.
Topics in CS: Intelligent Robotics with ROS
02/05/2020
CJ Chung, PhD and Nick Paul, MSCS
Homework Assignment #2  */

#include <ros/ros.h>
#include "my_ros_test/MyStr.h"
#include <ctime>

int main(int argc, char **argv){
    ros::init(argc, argv, "hw2str_pub");
    ros::NodeHandle nh;
    //creates a publisher that publishes to /hw2_topic
    ros::Publisher pub = nh.advertise<my_ros_test::MyStr>("/hw2_topic", 10);

    //sets the rate at which the data is sent to 1 second
    ros::Rate rate(1);

    //resets the random nuber gen to new values
    srand(time(NULL));

    //loops while ros is not exited
    while(ros::ok()){
        //sleeps for the rate which is 1 second
        rate.sleep();
        //creates a string called MyStr
        my_ros_test::MyStr msg;
        //sets MyStr to a local string
        msg.str = "thomasbrefeld";
        //generates a random number and mod it by 3
        msg.com = rand()%3;
        //publishes the string and command to /hw2_topic
        pub.publish(msg);
    }
}