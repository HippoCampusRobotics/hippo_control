#include <hippo_common/param_utils.hpp>
#include <hippo_msgs/msg/actuator_controls.hpp>
#include <hippo_msgs/msg/attitude_target.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <rcl_interfaces/msg/set_parameters_result.hpp>
#include <rclcpp/rclcpp.hpp>

#include "hippo_control/attitude_control/geometric_attitude_control.hpp"

using namespace hippo_control::attitude_control;
using namespace hippo_common;
using namespace hippo_msgs::msg;
using namespace rcl_interfaces::msg;
using namespace geometry_msgs::msg;
using nav_msgs::msg::Odometry;
using std::placeholders::_1;

class AttitudeControlNode : public rclcpp::Node {
 public:
  AttitudeControlNode() : Node("attitude_controller") {
    RCLCPP_INFO(get_logger(), "Declaring parameters.");
    DeclareParams();
    InitPublishers();
    InitSubscriptions();
  }
  void DeclareParams() {
    std::string name;
    rcl_interfaces::msg::ParameterDescriptor descr;
    std::string descr_text;

    name = "p_gains";
    descr_text = "Proportional gains for roll, pitch and yaw.";
    descr = param_utils::Description(descr_text);
    {
      std::lock_guard<std::mutex> lock(mutex_);
      p_gains_ = std::vector<double>({1.0, 1.0, 1.0});
      p_gains_ = declare_parameter(name, p_gains_, descr);
      controller_.SetPgains(p_gains_);
    }

    name = "d_gains";
    descr_text = "Derivate gains for the vehicle's body rates.";
    descr = param_utils::Description(descr_text);
    {
      std::lock_guard<std::mutex> lock(mutex_);
      d_gains_ = std::vector<double>({0.1, 0.1, 0.1});
      d_gains_ = declare_parameter(name, d_gains_, descr);
      controller_.SetDgains(d_gains_);
    }
    paramter_callback_handle_ = add_on_set_parameters_callback(
        std::bind(&AttitudeControlNode::OnSetParameters, this, _1));
  }

  void InitPublishers() {
    std::string topic;
    rclcpp::QoS qos = rclcpp::SystemDefaultsQoS();

    topic = "actuator_control";
    control_output_pub_ = create_publisher<ActuatorControls>(topic, qos);
  }

  void InitSubscriptions() {
    std::string topic;
    rclcpp::QoS qos = rclcpp::SystemDefaultsQoS();

    topic = "attitude_target";
    target_sub_ = create_subscription<AttitudeTarget>(
        topic, qos,
        std::bind(&AttitudeControlNode::OnAttitudeTarget, this, _1));

    topic = "odometry";
    odometry_sub_ = create_subscription<Odometry>(
        topic, qos, std::bind(&AttitudeControlNode::OnOdometry, this, _1));
  }

  void OnAttitudeTarget(const AttitudeTarget::SharedPtr _msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    attitude_target_ = *_msg;
  }

  void OnOdometry(const Odometry::SharedPtr _msg) {
    // TODO(lennartalff): Either update the controller directly in here or just
    // store the message and update the controller in an synchronuous loop
  }

  SetParametersResult OnSetParameters(
      const std::vector<rclcpp::Parameter> &parameters) {
    SetParametersResult result;

    for (const rclcpp::Parameter &parameter : parameters) {
      std::lock_guard<std::mutex> lock(mutex_);

      if (param_utils::AssignIfMatch(parameter, "p_gains", p_gains_)) {
        controller_.SetPgains(p_gains_);
        continue;
      }
      if (param_utils::AssignIfMatch(parameter, "d_gains", d_gains_)) {
        controller_.SetDgains(d_gains_);
        continue;
      }

      RCLCPP_WARN(get_logger(), "Unhandled parameter was set: [%s]",
                  parameter.get_name().c_str());
    }
    result.successful = true;
    return result;
  }

 private:
  std::mutex mutex_;
  std::vector<double> p_gains_;
  std::vector<double> d_gains_;
  GeometricAttitudeControl controller_;
  AttitudeTarget attitude_target_;

  rclcpp::Publisher<ActuatorControls>::SharedPtr control_output_pub_;
  rclcpp::Subscription<AttitudeTarget>::SharedPtr target_sub_;
  rclcpp::Subscription<Odometry>::SharedPtr odometry_sub_;
  OnSetParametersCallbackHandle::SharedPtr paramter_callback_handle_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<AttitudeControlNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
