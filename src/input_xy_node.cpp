#include "ros/ros.h"
#include "geometry_msgs/Point.h"

using namespace std;

ros::Publisher point_pub;

int main(int argc, char **argv){
    ros::init(argc,argv, "input_xy_node");
    ros::NodeHandle nh;

    geometry_msgs::Point point_msg;

    point_pub = nh.advertise<geometry_msgs::Point>("/goal",1000);

    //loops while ros is open
    while(ros::ok){
        cout << "-------------------" << endl;
        cout << "Enter X-point: ";
        cin >> point_msg.x;
        cout << "Enter Y-point: ";
        cin >> point_msg.y;
        //takes the user inputs and publishes them to goal topic
        point_pub.publish(point_msg);
    }
}