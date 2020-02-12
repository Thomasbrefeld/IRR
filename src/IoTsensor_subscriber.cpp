#include <ros/ros.h>
#include <my_ros_msgs/my_IoT.h>

void callback_rcv_topic(const my_ros_msgs::my_IoT& msg) 
{
	ROS_INFO_STREAM("Temp: " << msg.temperature << "  Humidity: " << (int)msg.humidity 
	                << "  Status: " << (int)msg.status << "  Loc: " << msg.location);
}

int main (int argc, char **argv) 
{
	ros::init(argc, argv, "IoTsensor_subscriber");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("/my_IoT/sensorData", 1000,
		callback_rcv_topic);
	ros::spin();
}