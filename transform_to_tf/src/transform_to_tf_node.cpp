#include <ros/ros.h>
#include "transform_to_tf/transform_to_tf.hpp"

// Standard C++ entry point
int main(int argc, char** argv) {
  // Announce this program to the ROS master
  ros::init(argc, argv, "transform_to_tf");
  // Creating the node handles
  ros::NodeHandle nh;
  ros::NodeHandle nh_private("~");
  // Creating the object to do the work
  transform_to_tf::TransformToTf transform_to_tf(nh, nh_private);
  // Spinning
  ros::spin();
  // Exit tranquilly
  return 0;
}
