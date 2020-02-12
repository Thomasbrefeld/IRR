#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "cmath"

ros::Publisher cmd_pub_1;
ros::Subscriber pose_sub;
ros::Subscriber point_sub;

turtlesim::Pose turtlesim_pose;
geometry_msgs::Point goal_point;

void pose_call_back(const turtlesim::Pose::ConstPtr& msg){
    turtlesim_pose.x = msg->x;
    turtlesim_pose.y = msg->y;
    turtlesim_pose.theta = msg->theta;
}

void  goal_call_back(const geometry_msgs::Point::ConstPtr& msg){
    goal_point.x = msg->x;
    goal_point.y = msg->y;
}

void move(){
    geometry_msgs::Twist vel_msg;

    vel_msg.linear.y = 0;
    vel_msg.linear.z = 0;
    vel_msg.angular.x = 0;
    vel_msg.angular.y = 0;

    std::cout << "to-x: " << goal_point.x << "  to-y: " << goal_point.y << "  x: " << turtlesim_pose.x << "  y:" <<turtlesim_pose.y << std::endl;

    ros::Rate loop_rate(0.2);
    do{
        double sum_x = turtlesim_pose.x - goal_point.x;
        double sum_y = turtlesim_pose.y - goal_point.y;
        double x_temp = pow(sum_x,2);
        double y_temp = pow(sum_y,2);
        double combined = x_temp + y_temp;
        double sqrt_comb = sqrt(combined);
        std::cout << "sum_x: " << sum_x << " sum_y: " << sum_y << " x_pow: " << x_temp << " y_temp: " << y_temp << " combined: " << combined << " sqrt_comb: " << sqrt_comb << std::endl;
        vel_msg.linear.x = .5 * sqrt_comb;

        
        if(goal_point.x - turtlesim_pose.x != 0){
            double calc_theta = atan((goal_point.y - turtlesim_pose.y) / (goal_point.x - turtlesim_pose.x));
            vel_msg.angular.z = 2 * (calc_theta - turtlesim_pose.theta);
        }

        std::cout << vel_msg.linear.x << vel_msg.angular.z << vel_msg.linear.y << vel_msg.linear.z << vel_msg.angular.x << vel_msg.angular.y << std::endl;
        
        loop_rate.sleep();
        cmd_pub_1.publish(vel_msg);
        ros::spinOnce();
    } while ((vel_msg.linear.x != goal_point.x) && (vel_msg.linear.y != goal_point.y));
}

int main(int argc, char **argv){
    ros::init(argc,argv, "go2xy_node");
    ros::NodeHandle nh;

    cmd_pub_1 = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    pose_sub = nh.subscribe("/turtle1/pose", 10, pose_call_back);
    point_sub = nh.subscribe("/goal", 10, goal_call_back);

    goal_point.x = turtlesim_pose.x;
    goal_point.y = turtlesim_pose.y;

    ros::Rate loop_rate(1);
    while(ros::ok()){
            ros::spinOnce();
            move();
            loop_rate.sleep();
            std::cout << "to-x: " << goal_point.x << "  to-y: " << goal_point.y << "  x: " << turtlesim_pose.x << "  y:" <<turtlesim_pose.y << std::endl;
    }
}