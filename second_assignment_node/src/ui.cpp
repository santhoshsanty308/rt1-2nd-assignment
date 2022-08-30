#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include "services/Service.h"

// Publisher
ros::Publisher pub;

// Service clients
ros::ServiceClient client1;
ros::ServiceClient client2;

// Global variable
float robot_speed = 0.0; // Robot velocity

int main(int argc, char **argv) {
    // Initialize the node
    ros::init(argc, argv, "user_interface");
    ros::NodeHandle rc;
    
    // Clients
    client1 = rc.serviceClient<services::Service>("/user_control");
    client2 = rc.serviceClient<std_srvs::Empty>("/reset_positions");
    
    int in = -1; // User's input

    // Show list of commands 
    printf("Type a command:\n\n"
        "0 - Reset robot position\n"
        "1 - Increase robot velocity\n"
        "2 - Decrease robot velocity\n"
        "3 - Stop the robot\n"
        "4 - Exit\n\n"
        "-------------------------------\n\n"
    );

    while (in != 4) {
        in = -1;

        // Take input value
        printf("Input: ");
        std::cin >> in;

        // Reset
        if (in == 0) {
            std_srvs::Empty res;
            client2.waitForExistence();
            client2.call(res);
            printf("Robot position reset.\n");
        }

        // Manage robot's velocity
        else if (in == 1 || in == 2 || in == 3) {
            // Command
            services::Service ser;

            // Increase velocity
            if (in == 1) {
                printf("Increasing velocity...");
                ser.request.input = 1.0;
                ser.request.robot_speed = robot_speed;
            }
            // Decrease velocity
            else if (in == 2) {
                printf("Decreasing velocity...");
                ser.request.input = 2.0;
                ser.request.robot_speed = robot_speed;
            }
            // Stop the robot
            else {
                printf("Stopping the robot... ");
                ser.request.input = 3.0;
                ser.request.robot_speed = 0;
            }

            // Send the request to the server and wait for the response
            client1.waitForExistence();
            client1.call(ser);
            robot_speed = ser.response.robot_speed;
            printf("New speed: %f\n", robot_speed);
        }
        // Exit 
        else if (in == 4) {
            continue;
        }
        // Manage wrong inputs
        else {
            printf("ERROR! Command not valid: type '0', '1', '2', '3' or '4'.\n");
        }
    }
    return 0;
}
