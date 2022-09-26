#include "hippo_control/geometric_attitude_control.hpp"

namespace hippo_control {
Eigen::Vector3d Update(const Eigen::Quaterniond &_orientation,
                       const Eigen::Quaterniond &_orientation_target,
                       const Eigen::Vector3d &_rotation_velocity,
                       const Eigen::Vector3d &_rotation_velocity_target) {
  Eigen::Vector3d torque;
  return torque;
}
}  // namespace hippo_control
