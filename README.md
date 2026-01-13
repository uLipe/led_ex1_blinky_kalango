# Kalango RTOS – C29x Blinky Example (CCS 20)

## Overview

This project is a **Code Composer Studio (CCS) 20 example** that illustrates how to **use the Kalango RTOS on Texas Instruments C2000 C29x (64-bit) devices**.

It is intended for **users of the Kalango RTOS** who want a concrete, working reference showing:

* How to integrate **Kalango RTOS** into a CCS project
* How to run Kalango on the **C29x architecture**
* How to create and run threads using Kalango

The application itself implements a simple **LED blinky**, serving as a clear and observable demonstration of a Kalango-managed system running on real hardware.

This repository should be viewed as a **usage and integration example**, not as a description of the RTOS internals.

---

## What This Project Illustrates

From a **Kalango RTOS user perspective**, this project demonstrates:

* ✅ Using **Kalango RTOS** on a **C2000 C29x (64-bit)** target
* ✅ Creating and running RTOS threads
* ✅ Thread stack allocation and configuration
* ✅ Cooperative scheduling under Kalango RTOS
* ✅ A complete CCS 20 workflow (import, build, debug, run)
* ✅ RAM and FLASH build configurations

The LED blinky provides immediate visual feedback that the RTOS and scheduler are running correctly.

---

## Repository Structure

```
led_ex1_blinky_kalango/
├── app_source/              # Application code (tasks, main, startup)
├── kalango_rtos_config/     # RTOS configuration (tasks, stacks, hooks)
├── KalangoRTOS/             # Kalango RTOS (Git submodule)
├── device/                  # Device‑specific support files
├── RAM/                     # RAM build output
├── FLASH/                   # FLASH build output
├── targetConfigs/           # CCS target configuration (.ccxml)
├── f29h85x_ram_lnk.cmd      # RAM linker command file
├── f29h85x_flash_lnk.cmd    # FLASH linker command file
├── led_ex1_blinky.syscfg    # SysConfig file
└── README.md
```

---

## Requirements

* **Code Composer Studio 20.x or newer**
* **C2000 C29x device support installed**
* **TI F29H LaunchPad development board**

The example is designed and validated specifically for the **LAUNCHXL-F29H85X** development board.

The **LAUNCHXL-F29H85X** is a Texas Instruments LaunchPad evaluation board for the **C2000 F29H85x C29x (64-bit)** family. It provides a convenient platform for running, debugging, and validating applications and RTOS-based systems on the new C29x architecture.

More information about the board can be found here:

[https://www.ti.com/tool/LAUNCHXL-F29H85X](https://www.ti.com/tool/LAUNCHXL-F29H85X)

---

## Cloning the Project

This project uses **Kalango RTOS as a Git submodule**, so make sure to clone recursively.

```bash
git clone --recurse-submodules https://github.com/<your-username>/led_ex1_blinky_kalango.git
```

If you already cloned without submodules:

```bash
git submodule update --init --recursive
```

---

## Importing into CCS

1. Open **Code Composer Studio 20**
2. Go to **File → Import**
3. Select **C/C++ → Existing Code as CCS Project**
4. Browse to the cloned `led_ex1_blinky_kalango` directory
5. Finish the import

CCS will automatically pick up:

* `.ccsproject`
* `.project` / `.cproject`
* SysConfig and linker files

---

## Build & Run

* Select **RAM** or **FLASH** build configuration
* Build the project
* Launch the debugger
* Run

You should see the LED toggling under **RTOS control**.

---

## Notes for Kalango RTOS Users

This project assumes you are interested in **using Kalango RTOS on C29x-based C2000 devices**.

It shows how Kalango can be:

* Integrated as a **Git submodule**
* Built and linked inside a CCS project
* Used to run application threads on real C29x hardware

The application logic is intentionally simple so users can focus on **how to use Kalango RTOS**, not on application complexity.

---

## License

This project is provided for educational and experimental purposes.

Refer to the Kalango RTOS repository for RTOS‑specific licensing information.

---

## Contributions

Contributions are welcome.

If you are interested in improving the example, extending support, or adding new Kalango RTOS use cases on C29x, feel free to open issues or submit pull requests.
