//Thomas Brefeld Jr.
//Homework 0
//January 22, 2020
//ROS

#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char **argv){
	ros::init(argc, argv, "homework0_cpp_node");
	ros::NodeHandle nh;
	ROS_INFO("homework0_cpp_node has started");
	std_msgs::String msg;
	msg.data = "Thomas Brefeld";
	ROS_INFO_STREAM("My message is: " << msg.data);
	ROS_INFO_STREAM("The length of my message is: " << msg.data.length());
	ROS_INFO_STREAM("The 3rd char in my message is: " << msg.data[2]);
	ROS_INFO_STREAM("The last char in my message is: " << msg.data[msg.data.length() - 1]);

	//Convert the string msg to upper
	for (int x = 0; x < msg.data.length(); ++x){
		msg.data[x] = toupper(msg.data[x]);
	}
	ROS_INFO_STREAM("My message in upper case is: " << msg.data);

	//Reverse the converted string msg
	//sets a variable len to hold the length of the msg
	int len = msg.data.length();
	//ROS_INFO_STREAM((len / 2) << " " << len); //Used for testing
	//loops through the list are reverses it
	for (int x = 0; x < len / 2 ; ++x){
		char temp = msg.data[x];
		//ROS_INFO_STREAM(temp << " " << msg.data[len - x - 1]); //Used for testing
		msg.data[x] = msg.data[len - x - 1];
		msg.data[len - x - 1] = temp;
	}
	ROS_INFO_STREAM("My message in upper case and reversed is: " << msg.data);
}
