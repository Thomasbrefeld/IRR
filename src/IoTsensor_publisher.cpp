#include <ros/ros.h>
#include <my_ros_msgs/my_IoT.h>

int main (int argc, char **argv) {
	ros::init(argc, argv, "iOTsensor_publisher");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<my_ros_msgs::my_IoT>(
		"/my_IoT/sensorData", 10);

	double pub_freq = 1; // defualt is 1 Hz
    nh.getParam("/IoT_pub_freq", pub_freq);
    ros::Rate rate(pub_freq);  

	std::default_random_engine generator;
	std::normal_distribution<double> normal(0.0, 0.5);
	
	while (ros::ok()) {
		my_ros_msgs::my_IoT msg;
		msg.temperature = 68 + normal(generator);
        msg.humidity = 7 + + normal(generator);
		msg.status = true;
		msg.location = "room 1";
		pub.publish(msg);
		rate.sleep();
	}
}
