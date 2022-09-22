#pragma once
#include <array>
#include <vector>

namespace hippo_control {
static constexpr int kChannels = 8;
enum class Channel {
  kRoll,
  kPitch,
  kYaw,
  kThrust,
  kVerticalThrust,
  kLateralThrust,
  kMaxChannel,
};

struct Mapping {
  double limits[kChannels] = {0.0};
  double scalings[kChannels] = {0.0};
};

struct Output {
  double total = 0.0;
  double channels[kChannels] = {0.0};
};

class SimpleMixer {
 public:
  SimpleMixer();
  double test;

  void SetMapping(int _index, const Mapping &_mapping);

  std::array<double, kChannels> Mix(
      const std::array<double, kChannels> &_actuator_controls);
  private:

  Mapping mappings_[kChannels];
  Output outputs_[kChannels];
  void ApplyInput(const std::array<double, kChannels> &_actuator_controls);
  void ScaleToLimits();
  void ResetOutputs();
};

}  // namespace hippo_control
