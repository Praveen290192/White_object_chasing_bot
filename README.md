# White_object_chasing_bot
In this project bot is using rbg image for identifying white color object in Gazebo environment and chasing it.

## Video link
https://youtu.be/vngkr6VoVbM

## Building  
Clone `ball_chaser` and `my_robot` into the `src` directory of the catkin_workspace `catkin_ws`
then use below commands to build and source from the catkin_workspace directory
$ catkin_make
$ source devel/setup.bash

## Launching
Launch world.launch from terminal using below command
$ roslaunch my_robot world.launch

Open new terminal and make sure to source it 
$ cd ~/catkin_ws
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch

## Testing
In gazebo bring the ball in front of the robot camera, you should see robot moving towards the ball.
