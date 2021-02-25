## InAccel Coral - Runtime specification

InAccel provides a runtime specification that you can use to advertise system
hardware resources to Coral.

### Abstract

The InAccel Coral runtime specification aims to specify the configuration, and
execution interface for the efficient management of any accelerator-based
hardware resource.

Without customizing the code for InAccel Coral itself, vendors can implement a
custom runtime that you install as a common library. The targeted cases include
custom (non-OpenCL) implementations, new FPGA families, and other similar
computing resources that may require vendor specific initialization and setup.

### Use Cases

To provide more context for users the following section gives example use cases
for each part of the spec.

#### Hook Developers

Hook developers can extend the functionality of a compliant runtime by hooking
into an accelerator's lifecycle with an external application. Example use cases
include sophisticated hardware configuration, advanced logging, IP licensing
(hardware identification - authentication - decryption), etc.

#### Runtime Developers

Runtime developers can build runtime implementations that expose diverse
hardware resources and system configuration, containing low-level OS and
hardware-specific details, on a particular platform.
