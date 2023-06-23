#pragma once

#include <rclcpp/rclcpp.hpp>

namespace hippo_control {
namespace trajectory_tracking {
class TrackingControllerNode : public rclcpp::Node {
 public:
  explicit TrackingControllerNode(rclcpp::NodeOptions const &_options);
};
}  // namespace trajectory_tracking
}  // namespace hippo_control

