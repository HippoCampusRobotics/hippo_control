^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package hippo_control
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* moved to separate repo
* launch file cleanup
* refactoring
* migrated to hippo_control_msgs
* ditched yapf
* migrated to hippo_control_msgs
* fixed unused variables
* Niklas' changes squashed
* renamed PassLaunchArguments to something more descriptive
* added pre-commit hooks
* fixed formatting errors after latest merge
* use the free-function version of create_timer to keep humble compatibilty
* snapshot for paper
* added support for multi-phase motor failure control experiments
* added two-motor case and parameters
* added path following launch file for the quaternoin controller
* publish attitude debug message as pose to be visualizable in rviz
* just feed through thrust setpoint
* change structure of system of equations
* moved update method to source file and fixed erroor regarding frame conversions
* more reasonable gains for quaternion control
* changed rate control config to more reasonable defaults
* fixed error in rate_controller subscription topic
* feed rate_controller with odometry instead of px4_msg
* removed unused dependencies
* restructured rate_control
* greatly simplified rate_controller params by using macros
* changed gains to reasonable default
* initial implementation ofmotor failure control
* added missing parameter declaration
* deleted carrot-control related files
* added licenses and applied formatting to all source files
* completed path-follower setup to replace carrot_control
* set controller gains after parameter initialization
* added path_follower
* added quaternion based attitude control node
* added missing px4_msgs dependency export
* inlined template specializations and added conversion for actuator-setpoint message
* new attitude control structure
* added missing normalization
* added setter/getter for gains
* made non interface methods private
* added quaternion based attitude controller
* convenience replacement
* simplified control launch files
* added path visualizer and thrust subscription
* moved carrot control header to local dir
* moved mixer config in subdir
* added params to carrot control and launch files
* path planning package added
* minor update
* fixed that thrust not stored as member
* added parameter handling and some code cleanup
* minimal implementation of trajectory tracker
* added missing pragmas and moved component registration to source
* added tracking_controller component template
* simplified tracking controller's interface
* geometric tracking control library added
* adapted mixer matrix and thruster mapping to physical model
* adapted to upstream
* commit before upstream pull request
* fixed wrong thruster mapping, manipulator compensation + added accelerations, restructured velocity controller auv
* added acceleration estimation to manipulator, PI->PID controller
* adapted namespace actuator_mixer, submodule path
* mixer config for normalized instead of physical units
* removed doubled namespace
* added control target msg type
* removed unused variable
* thrusters params from data sheet
* restructuring mixer node and integrating bluerov
* rate controller fix
* default gains adapted
* debug msgs
* avoid divergence
* frame conversion fixed
* changed msg type for body rates
* updated parameters according to thruster measurements
* added compiler optimizations
* mixer overhaul
* full rate controller setup
* rate control added
* added timeout
* reversed mixer matrix to match reality
* made mixer thrust function parametrical
* fixed thruster params and adapted mixer matrix.
  Scale the inputs depending in number of participating motors in that
  degree of freedom.
* mixer now maps physical thrust values to normalized thruster commands
* added cmake definition for clang-tidy
* added missing return
* use body rates for feedthrough
* added compiler flags
* initial commit
* Contributors: Niklas T, Thies Lennart Alff, niklastkl
