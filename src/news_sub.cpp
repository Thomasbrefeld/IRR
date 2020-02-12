#include <ros/ros.h>
#include <std_msgs/String.h>

void callback_receive_topic1data(const std_msgs::String& msg)
{ 
    ROS_INFO_STREAM("Message received: " << msg.data);
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "news_sub");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/news_topic1", 1000, 
                          callback_receive_topic1data);
    ros::spin();
}

