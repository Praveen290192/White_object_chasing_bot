#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

//Define a global client that can request services
ros::ServiceClient client;

//This function calls the command_robot service to drive the robot inthte specified direction
void drive_robot(float lin_x, float ang_z)
{
	//TODO: Request a service and pass the velocities to it to drive the robot
	//ROS_INFO_STREAM("ROBOT is moving");

	ball_chaser::DriveToTarget srv;
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	if(!client.call(srv))
	{
		ROS_ERROR("Failed to call service safe_move");	
	}
	
}


//This callback function continously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
	int white_pixel = 255;
	
	//TODO: Loop through each pixel in the image and check if there's a bright whiet one
	//Then, indentify if this pixel falls in the left, mid, or right side of the image
	//Depending on the white ball position, call the drive_bot function and pass velocities to it
	//Request a stop when there's no white ball seen by the camera

	bool white_ball = false;

	int left = img.step / 3;
	int middle = 2*img.step / 3;
	int right = img.step;
	int section=0;

	for(int i = 0; i < img.height * img.step; i+=3)
	{
		
		//ROS_INFO_STREAM(section);		
		if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2]==white_pixel)
		{
			//ROS_INFO_STREAM("White ball found");
			section = i%img.step;
			//ROS_INFO_STREAM(section);			
			white_ball = true;
			break;		
		}	
	}
	

	if(white_ball == true && section < left)
	{
		//ROS_INFO_STREAM("left drive");		
		drive_robot(0.1,0.1);	
	}
	else if (white_ball == true && section > left && section < middle)
	{
		//ROS_INFO_STREAM("straight drive");		
		drive_robot(0.1,0.0);	
	}
	else if (white_ball == true && section > middle)
	{
		//ROS_INFO_STREAM("right drive");
		drive_robot(0.1,-0.1);
	}
	else if (white_ball == false)
	{
		//ROS_INFO_STREAM("stop");		
		drive_robot(0.0,0.0);	
	}
}

int main(int argc, char** argv)
{
	//Initialize the process_image node and create a handle to it	
	ros::init(argc, argv, "process_image");
	ros::NodeHandle n;
	
	//Define a client service capable of requesting services from command_robot
	client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

	//Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
	ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw",10,process_image_callback);

	//Handle ROS communication events
	ros::spin();

	return 0;	

}
