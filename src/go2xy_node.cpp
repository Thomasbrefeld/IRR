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

void goal_call_back(const geometry_msgs::Point::ConstPtr& msg){
    goal_point.x = msg->x;
    goal_point.y = msg->y;
}

double dis_to_go(){
    //calculates the distance from the turtle to the goal points
    return sqrt(pow(turtlesim_pose.x - goal_point.x, 2) + pow(turtlesim_pose.y-goal_point.y,2));
}

int move(){
    geometry_msgs::Twist vel_msg;

    //checks if the next goal point has the same y-point and checks if that y-point in to the left of the robot 
    //this would cause the arctan function to return 0 and send the robot to the right. 
    //I ran out of time to figure out how to solve this issue, so the program only catches it and breaks out of the move.
    if(goal_point.y < turtlesim_pose.y + .5 && goal_point.y > turtlesim_pose.y - .5 && goal_point.x < turtlesim_pose.x){
        std::cout << " Break: bad y-point, y is the same and to the left of proir y-point" << std::endl;
        return 0;
    }
    
    //will loop "do" loop at 60 times a second
    ros::Rate loop_rate(60);

    //sets all unused variables to 0
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;

    do{
        //sets the x linear movement to 1.5 times the distance to go
        vel_msg.linear.x = 1.5 * dis_to_go();

        //sets the angular z to the angle to go times 8
        vel_msg.angular.z = 8 * (atan2(goal_point.y - turtlesim_pose.y, goal_point.x - turtlesim_pose.x) - turtlesim_pose.theta);

        //publishes the commands to cmd_vel
        cmd_pub_1.publish(vel_msg);
        loop_rate.sleep();
        ros::spinOnce();
        //loops until in a reasonable distance from target
    } while (dis_to_go() > .01);

    //sets everything to zero to completely stop the robot
    vel_msg.linear.x = 0;
    vel_msg.angular.z = 0;
    cmd_pub_1.publish(vel_msg);
    //return 1 to confirm the function ran successfully
    return 1;
}

int main(int argc, char **argv){
    ros::init(argc,argv, "go2xy_node");
    ros::NodeHandle nh;
    

    cmd_pub_1 = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    pose_sub = nh.subscribe("/turtle1/pose", 1, pose_call_back);
    point_sub = nh.subscribe("/goal", 1, goal_call_back);

    //will loop through the while function 10 times a second
    ros::Rate loop_rate(10);

    //creates a variable to hold the prior point
    geometry_msgs::Point last_point;

    //sets the prior point to the current goal
    last_point.x = goal_point.x;
    last_point.y = goal_point.y; 

    while(ros::ok()){
        //loops until the new points are different
        while (last_point.x == goal_point.x && last_point.y == goal_point.y){
            loop_rate.sleep();
            ros::spinOnce();
        }
        //checks if the new points are inside the boundaries
        if(goal_point.x < 11 && goal_point.x > 0 && goal_point.y < 11 && goal_point.y > 0)
            std::cout << move() << std::endl; //calls the move function and prints 1 is successful
        
        //sets the new last points to the current goal points
        last_point.x = goal_point.x;
        last_point.y = goal_point.y;
    }
}