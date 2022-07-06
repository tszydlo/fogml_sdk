# FogML-SDK

SDK implements FogML [https://github.com/tszydlo/FogML] machine learning algorithms for resource-constrained devices.

Available modules and algorithms:
* `anomaly_rt`
  * reservoir sampling
  * Local Outliner Factor

* `classifier`
  * header file for the source code generated with FogML

* `dsp`
  * digital signal processing algorithms for initial time series analysis

* `ports`
  * code needed to port the SDK to various frameworks - supports Arduino and Zephyr OS

* `rl`
  * header files for the reinforcement learning source code generated with FogML

Examples:
* Arduino - an application that detects anomalies and classifies the fan rotation speed
  * https://github.com/tszydlo/FogML-Arduino
* Zephyr OS - an application that detects gestures performed by the device
  * WiP
