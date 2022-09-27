#pragma once
#include <eigen3/Eigen/Dense>
#include <vector>
namespace hippo_control {
namespace attitude_control {
class GeometricAttitudeControl {
 public:
  /**
   * @brief Computes the controller output.
   *
   * @param _orientation Current orientation as quaternion.
   * @param _orientation_target Target orientation as quaternion.
   * @param _angular_velocity Current angular velocity (rad/s).
   * @param _angular_velocity_target Target angular velocity (rad/s).
   * @param _scale Toggles between clip and scale mode to get output values in
   * range [-1.0, 1.0].
   * @return Eigen::Vector3d Control output as vector of roll, pitch and yaw
   * torque normalized to a maximum of 1.0.
   */
  Eigen::Vector3d Update(const Eigen::Quaterniond &_orientation,
                         const Eigen::Quaterniond &_orientation_target,
                         const Eigen::Vector3d &_angular_velocity,
                         const Eigen::Vector3d &_angular_velocity_target,
                         bool _scale = true);

  /**
   * @brief Set proportional gains for roll, pitch and yaw angle.
   *
   * @param _gains
   */
  void SetPgains(const Eigen::Array3d &_gains) {
    p_gains_ = Eigen::Array3d(_gains);
  }
  /**
   * @overload
   */
  void SetPgains(const std::vector<double> &_gains) {
    p_gains_ = Eigen::Array3d(_gains.data());
  }
  /**
   * @overload
   */
  void SetPgains(const std::array<double, 3> &_gains) {
    p_gains_ = Eigen::Array3d(_gains.data());
  }

  /**
   * @brief Set the derivate gains for roll, pitch and yaw angular velocity.
   *
   * @param _gains
   */
  void SetDgains(const Eigen::Array3d &_gains) {
    d_gains_ = Eigen::Array3d(_gains);
  }
  /**
   * @overload
   */
  void SetDgains(const std::vector<double> &_gains) {
    d_gains_ = Eigen::Array3d(_gains.data());
  }
  /**
   * @overload
   */
  void SetDgains(const std::array<double, 3> &_gains) {
    d_gains_ = Eigen::Array3d(_gains.data());
  }

 private:
  // use array instead of vector to simplify coefficient wise multiplication
  Eigen::Array3d p_gains_{1.0, 1.0, 1.0};
  Eigen::Array3d d_gains_{0.1, 0.1, 0.1};
};
}  // namespace attitude_control
}  // namespace hippo_control
