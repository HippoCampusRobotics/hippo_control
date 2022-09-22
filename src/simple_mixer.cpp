#include "simple_mixer.hpp"

using namespace hippo_control;

SimpleMixer::SimpleMixer(){};

void SimpleMixer::SetMapping(int _index, const Mapping &_mapping) {
  if (!(_index < kChannels)) {
    return;
  }
  mappings_[_index] = _mapping;
}

void SimpleMixer::ResetOutputs() {
  for (Output &output: outputs_) {
    output.total = 0.0;
    for (double channel: output.channels) {
      channel = 0.0;
    }
  }
}

void SimpleMixer::ApplyInput(
    const std::array<double, kChannels> &_actuator_controls) {
  ResetOutputs();
  for (int i_out = 0; i_out < kChannels; ++i_out) {
    for (int i_in = 0; i_in < kChannels; ++i_in) {
      outputs_[i_out].total += _actuator_controls[i_in] * mappings_[i_out].scalings[i_in];
    }
  }
}
