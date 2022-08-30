
## RESEARCHTRACK1-ASSIGNMENT-2
## OBJECTIVE:
This Assignment-2 is a C++ program which achives a robot's behaviour ( using laser scanners ) by driving around the given circuit.

We are using ROS for controlling the robot which is responsible to interact with the user to increase or decrease the speed of the robot and its position.

## HOW IT WORKS:
Basically there are three nodes second_assignment, second_assignment_node and services. 

1.second_assignment contains the world (circuit) where the robot runs. 

2.second_assignment_node contains two piece of codes for main robot operation (robot.cpp) which gets datas from Laser scanners and uses for the prioritised turn of the robot and other one for user to control the robot (ui.cpp) that invokes the service for the User Interface to change the course of the robot movement.

3.services contains the user input commands to condition the robot movements.

STEP1: Open the terminal and go to src of your ROS workspace and run

<pre><code>git clone https://github.com/santhoshsanty308/Rt1.git </code></pre>

STEP2 : Now to build your clonned code run the command - 

<pre><code>catkin_make</code></pre>
STEP 3: Open a new terminal each for the following commands seperatly

Terminal-1.
<pre><code>roscore</code></pre>

Terminal-2.

<pre><code>rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world</code></pre>

Terminal-3.

<pre><code>rosrun services server</code></pre>

Terminal-4.

In this Terminal You need to enter the commands listed which will make the robot move accordingly.

<pre><code>rosrun second_assignment_node ui</code></pre>


Terminal-5.

<pre><code>rosrun second_assignment_node robot</code></pre>


