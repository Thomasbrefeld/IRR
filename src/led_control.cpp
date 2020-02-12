/* Thomas Brefeld Jr.
Topics in CS: Intelligent Robotics with ROS
02/05/2020
CJ Chung, PhD and Nick Paul, MSCS
Homework Assignment #3  */

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>

//creates two publishers one for the green led and one for the red
ros::Publisher pub_green;
ros::Publisher pub_red;

//creates a global var to hold the selected color
int color = 1;

void callback_receive_keyboard_input(const std_msgs::Int32& keyinput){
    //creates a var to hold the bool of the state of the led to set
    std_msgs::Bool output;
    //checks if user entered a 1
    if(keyinput.data == 49){
        output.data = true;
    }
    //checks if user entered a 0
    else if(keyinput.data == 48){
        output.data = false;
    }
    
    //publishes to green if color is 1
    if(color == 1){
        pub_green.publish(output);
    }
    //publishes to red otherwise
    else{
        pub_red.publish(output);
    }
}

int main(int argc, char **argv){
	ros::init(argc, argv, "led_control");
	ros::NodeHandle nh;

    //get the param value and sets it to color
    //1 is green, 0 is red
    nh.getParam("led_color", color);

    //subscribed to /keyboard input
    ros::Subscriber sub = nh.subscribe("/keyboard", 1000, callback_receive_keyboard_input);
    //setup publishes for led respective colors topics
    pub_green = nh.advertise<std_msgs::Bool>("/green_led", 10);
    pub_red = nh.advertise<std_msgs::Bool>("/red_led", 10);
    ros::spin();
}