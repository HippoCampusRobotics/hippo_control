#pragma once
#include <eigen3/Eigen/Dense>
#include <vector>
namespace hippo_control {
class GeometricAttitudeControl {
 public:
  Eigen::Vector3d Update(const Eigen::Quaterniond &_orientation,
                         const Eigen::Quaterniond &_orientation_target,
                         const Eigen::Vector3d &_rotation_velocity,
                         const Eigen::Vector3d &_rotation_velocity_target);

 private:
  Eigen::Vector3d p_gains_{1.0, 1.0, 1.0};
  Eigen::Vector3d d_gains_{0.1, 0.1, 0.1};
};
}  // namespace hippo_control
