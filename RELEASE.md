### CYW920829-MOUSE BSP
The AIROC™ CYW20829 Bluetooth® LE SoC is a Bluetooth® 5.3 core spec-compliant for IoT, HID, smart home and industrial applications. It comes with the right combination of low power and high performance dual core Arm® Cortex® M33 to meet the high demands of Bluetooth® LE Applications.

NOTE: BSPs are versioned by family. This means that version 1.2.0 of any BSP in a family (eg: PSoC™ 6) will have the same software maturity level. However, not all updates are necessarily applicable for each BSP in the family so not all version numbers will exist for each board. Additionally, new BSPs may not start at version 1.0.0. In the event of adding a common feature across all BSPs, the libraries are assigned the same version number. For example if BSP_A is at v1.3.0 and BSP_B is at v1.2.0, the event will trigger a version update to v1.4.0 for both BSP_A and BSP_B. This allows the common feature to be tracked in a consistent way.

### What's Included?
The CYW920829-MOUSE library includes the following:
* BSP specific makefile to configure the build process for the board
* cybsp.c/h files to initialize the board and any system peripherals
* cybsp_types.h file describing basic board setup
* Linker script & startup code for GCC, IAR, and ARM toolchains
* Configurator design files (and generated code) to setup board specific peripherals
* .lib file references for all dependent libraries
* API documentation

### What Changed?
#### v1.0.0 Beta 1
Note: This revision is only compatible with ModusToolbox Tools 3.0 and newer.
* Updated pre-production release supporting ModusToolbox 3.0.
#### v0.5.0
* Initial pre-production release

### Supported Software and Tools
This version of the CYW920829-MOUSE BSP was validated for compatibility with the following Software and Tools:

| Software and Tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox™ Software Environment        | 3.0.0   |
| GCC Compiler                              | 10.3.1  |
| IAR Compiler                              | 9.30.1  |
| ARM Compiler                              | 6.16    |

Minimum required ModusToolbox™ Software Environment: v3.0.0

### More information
* [CYW920829-MOUSE BSP API Reference Manual][api]
* [CYW920829-MOUSE Documentation](https://www.infineon.com/cms/en/product/promopages/airoc20829/)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

[api]: https://infineon.github.io/TARGET_CYW920829-MOUSE/html/modules.html

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2022.