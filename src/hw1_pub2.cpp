#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>

//Thomas Brefeld

int main(int argc, char **argv){
	ros::init(argc, argv, "hw1_pub2");
	ros::NodeHandle nh;
	
	ros::Publisher pub = nh.advertise<std_msgs::String>("/hw1_topic", 10);

	//gets pub freq
	double pub_freq = 1;
	nh.getParam("/hw1_topic_pub_freq", pub_freq);	
	ros::Rate rate(pub_freq);

	std::string local_msg;
	local_msg = "MMMMMMM";

	//gets param
	std::string param_msg;
	nh.getParam("/hw1_str2", param_msg);	
	
	//loops till ros exits
	while(ros::ok()){
		rate.sleep();
		std_msgs::String msg_temp;
		msg_temp.data = local_msg + param_msg;
		pub.publish(msg_temp);
	}
}
