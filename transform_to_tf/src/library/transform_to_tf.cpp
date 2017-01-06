#include "transform_to_tf/transform_to_tf.hpp"

namespace transform_to_tf {

TransformToTf::TransformToTf(const ros::NodeHandle& nh,
                             const ros::NodeHandle& nh_private)
    : nh_(nh),
      nh_private_(nh_private),
      verbose_(kDefaultVerbose),
      local_frame_name_(kDefaultLocalFrameName),
      global_frame_name_(kDefaultGlobalFrameName) {
  // Getting data and params
  subscribeToTopics();
  advertiseTopics();
  getParametersFromRos();
}

void TransformToTf::subscribeToTopics() {
  // Subscribing to the required data topics
  transform_sub_ = nh_.subscribe("transform_to_be_converted", 1,
                                 &TransformToTf::transformCallback, this);
}

void TransformToTf::advertiseTopics() {
  // Advertising topics
  tf_timer_ = nh_.createTimer(ros::Duration(0.01),
                              &TransformToTf::publishTFTransform, this);
}

void TransformToTf::getParametersFromRos() {
  // Retrieving the parameters
  nh_private_.getParam("verbose", verbose_);
  nh_private_.getParam("local_frame_name", local_frame_name_);
  nh_private_.getParam("global_frame_name", global_frame_name_);
}

void TransformToTf::transformCallback(
    const geometry_msgs::TransformStampedConstPtr& msg) {
  // Converting and storing the transform
  transform_.stamp = msg->header.stamp;
  tf::transformMsgToKindr(msg->transform, &transform_.transformation);
}

void TransformToTf::publishTFTransform(const ros::TimerEvent& event) {
  tf::Transform tf_transform;
  tf::transformKindrToTF(transform_.transformation, &tf_transform);
  tf_broadcaster_.sendTransform(tf::StampedTransform(
      tf_transform, ros::Time::now(), global_frame_name_, local_frame_name_));
}

}  // namespace transform_to_tf