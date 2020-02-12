#include <ros/ros.h>
#include <std_msgs/String.h>

//prints msg
void callback_receive_hw1_topic_changed(const std_msgs::String& msg){
    ROS_INFO_STREAM("Changed string: " << msg.data);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "hw1_sub");
	ros::NodeHandle nh;

    //gets sub
    ros::Subscriber sub = nh.subscribe("/hw1_topic_changed", 1000, callback_receive_hw1_topic_changed);
    ros::spin();
}