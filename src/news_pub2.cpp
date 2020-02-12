#include <ros/ros.h>
#include <std_msgs/String.h>

int main (int argc, char **argv)
{
    ros::init(argc, argv, "news_pub2");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::String>("/news_topic1", 10);
    // 10: outgoing message queue size (required)
    double pub_freq = 1; // defualt freq is 1 Hz
    nh.getParam("news_topic1_pub_freq", pub_freq);
    ros::Rate rate(pub_freq);
    
    int i = 0;
    while (ros::ok()) {
        rate.sleep(); // sleep first not to loose the 1st message
        std_msgs::String msg;
        msg.data = "Hello World " + std::to_string(i++); // c++11
        pub.publish(msg); 
    }
}

