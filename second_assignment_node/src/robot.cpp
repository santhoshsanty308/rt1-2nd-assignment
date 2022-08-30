#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h" 
#include "services/Service.h"


ros::Publisher pub;
ros::ServiceClient client;
int flag = 0;
float robot_speed = 0;


void call_back(const sensor_msgs::LaserScan::ConstPtr& msg) 
{
    float center = 30;
    float right = 0;
    float left = 0; 
    services::Service ser;
    ser.request.input = 4.0;
    //client.request.input=user_input;
    client.waitForExistence();
    client.call(ser);

    if (robot_speed != ser.response.robot_speed)
    {
        robot_speed = ser.response.robot_speed;
        printf("Actual robot velocity: %f\n", robot_speed);
    }

    // 2. Take the maximum value on the left
    int i = 0;
    while (i < 120)
    {
        if (msg->ranges[i] > right)
            right = msg->ranges[i];
        i++;
    }

    // Take the minimum value in the middle
    i = 300;
    while (i < 420)
    {
        if (msg->ranges[i] < center)
            center = msg->ranges[i];
        i++;
    }

    // Take the minimum value on the right
    i = 600;
    while (i <= 720)
    {
        if (msg->ranges[i] > left)
            left = msg->ranges[i];
        i++;
    }

    float val=left-right;
    float min_val=val;
    if(min_val<0)
    {
        min_val *= -1;
    }
    if(min_val>1)
    {
        min_val = 1;
    }
    else if (min_val<-1)
    {
        min_val = -1;
    }
        geometry_msgs::Twist vel;

    if(center < 1)
    {
        if(flag == 1)
            printf("Obstacle detected going to turn!\n");

        if(val < 0)
        {
            printf("turning right...\n");
            if(val < -1)
            {
                vel.linear.x = 0;
                vel.angular.z =val;
            }
            else
            {
                vel.angular.z = -1;
                vel.linear.x = min_val;
                
            }
        }

        else if(val>0)
        {
            printf("turning left....\n");
            if(val>1)
            {
                vel.linear.x= 0;
                vel.angular.z = val;
            }
            else
            {
                vel.angular.z =1;
                vel.linear.x = min_val;
                
            }
        }
        flag=0;
    }

    else
    {
        if(flag==0)
        {
            printf("Moveing forward...\n");
            flag = 1;
        }
        if(robot_speed + (center/3)>= robot_speed)
        {
            vel.linear.x = robot_speed;
        }
        else 
        {
            vel.linear.x = robot_speed + (center/3);
            vel.angular.z = 0.0;
        }
        
    }
        pub.publish(vel);
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot" );
    ros::NodeHandle nh;
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    client = nh.serviceClient<services::Service>("user_control");
    ros::Subscriber sub_basescan = nh.subscribe("/base_scan", 1000, call_back);
    ros::spin();
    return 0;
}
