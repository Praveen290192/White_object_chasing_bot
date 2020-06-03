#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//TODO:Include the ball_chaser "DriveToTarget" header file
#include "ball_chaser/DriveToTarget.h"

//ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

//TODO: Create a handle_driv_request callback function that executes whenever a drive_bot service is requested
//This function should publish the requested linear x and angular velocities to the robot wheel joints
//After publishing the requested veloctities, a message feedback should be returned with the requested wheel velocities
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{
	//ROS_INFO("Driving the bot");

	//Publish clamped joint angles to the arm
	float linearX, angularZ;

	//Creating a motor_command object of type geometery_msgs::Twist
	geometry_msgs::Twist motor_command;

	//Setting the wheel velocities as per request
	linearX = req.linear_x;
	angularZ = req.angular_z;
	motor_command.linear.x = linearX;
	motor_command.angular.z = angularZ;

	//Publishing angles to drive the robot
	motor_command_publisher.publish(motor_command);

	//Wait for 2 seconds for robot to settle
	ros::Duration(0.1).sleep();
	
	//Return a response message
	res.msg_feedback = "Linear velocity set to :"+ std::to_string(linearX) + "Angular velocity for Z is set to :"+ std::to_string(angularZ);

	ROS_INFO_STREAM(res.msg_feedback);
}


int main(int argc, char** argv)
{

	//Initialize a ROS node
	ros::init(argc, argv, "drive_bot");

	//Create a ROS NodeHandle object
	ros::NodeHandle n;

	//Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
	motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);

	//TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
	ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot",handle_drive_request);

	//TODO: Delete the loop, move the code to the inside of the callback funciton and make the necessary changes to publish the requested velocities instead of constant values
	
	/*while(ros::ok())
	{
		//Create a motor_command object of type geometry_msgs::Twist
		geometry_msgs::Twist motor_command;
		//Set wheel velocities, forward [0.5, 0.0]
		motor_command.linear.x = 0.5;
		motor_command.angular.z = 0.0;
		//Publish angles to drive the robot
		motor_command_publisher.publish(motor_command);
	}*/

	//TODO: Handle ROS communication events
	ros::spin();
	
	return 0;

}
