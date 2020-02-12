#include <ros/ros.h>
#include <std_msgs/String.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <string>

//Thomas Brefeld

ros::Publisher pub;

void callback_func_name(const std_msgs::String& msg){
    int random_num = rand() % msg.data.length();

    std_msgs::String word_test;

    for (int x = 0; x < msg.data.length(); ++x){
        if(x == random_num)
            word_test.data += " ";
        else
            word_test.data += msg.data[x];
    }
    pub.publish(word_test);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "hw1_changer");
	ros::NodeHandle nh;

    srand(time(NULL));
    
    ros::Subscriber sub = nh.subscribe("/hw1_topic", 1000, callback_func_name);
    pub = nh.advertise<std_msgs::String>("/hw1_topic_changed", 10);
    ros::spin();
}