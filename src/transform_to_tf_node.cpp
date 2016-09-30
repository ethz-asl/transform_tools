//#include <memory.h>
//#include <string>

#include <ros/ros.h>
#include <glog/logging.h>

#include "transform_to_tf/transform_to_tf.hpp"

// Standard C++ entry point
int main(int argc, char** argv) {
  // Starting the logging
  google::InitGoogleLogging(argv[0]);
  // Announce this program to the ROS master
  ros::init(argc, argv, "track_aligner");
  // Creating the node handles
  ros::NodeHandle nh;
  ros::NodeHandle nh_private("~");

  transform_to_tf::TransformToTf transform_to_tf(nh, nh_private);

  // Spinning
  ros::spin();
  // Exit tranquilly
  return 0;
}
