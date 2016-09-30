#ifndef TRANSFORM_TO_TF_H_
#define TRANSFORM_TO_TF_H_

#include <string>
#include <vector>

#include <ros/ros.h>
#include <Eigen/Geometry>

#include <eigen_conversions/eigen_msg.h>
#include <minkindr_conversions/kindr_msg.h>
#include <minkindr_conversions/kindr_tf.h>
#include <kindr/minimal/quat-transformation.h>
#include <tf/transform_broadcaster.h>

namespace transform_to_tf {

// Default values for parameters
static const bool kDefaultVerbose = true;
static const std::string kDefaultLocalFrameName = "body";
static const std::string kDefaultGlobalFrameName = "world";

// Convenience typedef
typedef kindr::minimal::QuatTransformation Transformation;

struct TransformationStamped {
  ros::Time stamp;
  Transformation transformation;
};

// Class handling global alignment calculation and publishing
class TransformToTf {
 public:
  // Constructor
  TransformToTf(const ros::NodeHandle& nh, const ros::NodeHandle& nh_private);

 protected:

  // Subscribes and Advertises to the appropriate ROS topics
  void subscribeToTopics();
  void advertiseTopics();
  void getParametersFromRos();

  // Publishes the resulting transform
  void publishTFTransform(const ros::TimerEvent& event);

  // Callbacks
  // Subscribing to the transforms
  void transformCallback(const geometry_msgs::TransformStampedConstPtr& msg);

  // Node handles
  ros::NodeHandle nh_;
  ros::NodeHandle nh_private_;

  // Subscribers
  ros::Subscriber transform_sub_;

  // TF publishing timer and broadcaster object.
  tf::TransformBroadcaster tf_broadcaster_;
  ros::Timer tf_timer_;

  // Stores the position of the current hoop in the world frame
  TransformationStamped transform_;


  // Parameters
  bool verbose_;
  std::string local_frame_name_;
  std::string global_frame_name_;

};

}  // namespace transform_to_tf

#endif /* TRANSFORM_TO_TF_H_ */
