#include "ros/ros.h" 
#include "sensor_msgs/LaserScan.h"
#include "services/Service.h"

float robot_speed = 0;

bool userinput_function(services::Service::Request& req, services::Service::Response& res)
{
    if (req.input == 1)
    {
        res.robot_speed = req.robot_speed + 0.5;
    }
    // Decrease speed 
    else if (req.input == 2)
    {
        res.robot_speed = req.robot_speed - 0.5;
    }
    // Stop the robot
    else if (req.input == 3)
    {
        res.robot_speed = req.robot_speed;
    }
    // Return the actual robot velocity
    else if (req.input == 4)
    {
        res.robot_speed = robot_speed;
    }

    robot_speed = res.robot_speed;

    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "server");
    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService("/user_control", userinput_function);
    ros::spin();
    return 0;
}
