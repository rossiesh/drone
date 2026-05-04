# ESP32-S3 Drone

## Status

Work in progress.

## Overview

This repository contains the firmware, 3D-print resources and documentation for a drone project based on two XIAO ESP32-S3 boards:

- one ESP32-S3 as the flight controller
- one ESP32-S3 used in the handheld

The long-term goal is a custom drone system with:

- ESP-NOW communication between handheld and flight controller
- a custom flight control stack
- an Android app connected to the handheld via USB-C for displaying telemetry data 
- 3D-printed structural parts

## Current state

The current implementation already covers some core building blocks:

- ESP-NOW communication between handheld and flight controller is set up
- the MPU6500 IMU is connected via SPI and can be read successfully
- gyroscope calibration is implemented
- 3D print resources and assembly-related documentation are included in the repository

The project is still missing major parts required for actual flight, for example:

- control packet/telemetry packet integration
- full flight-control logic
- motor mixer logic
- Android app
- full preflight/safety/failsafe handling

## Repository structure

- [`esp32_fc/`](./esp32_fc/) ESP-IDF project for the flight controller

- [`esp32_handheld/`](./esp32_handheld/) ESP-IDF project for the handheld

- [`protocols/`](./protocols/) shared packet structures for control/telemetry communication

- [`android_app/`](./android_app/) Android application code

- [`print_resources/`](./print_resources/) 3D print files and further information

- [`documentation/`](./documentation/) project documentation such as materials and assembly information

- [`tools/`](./tools/) helper tools

## Documentation

- [Materials](documentation/materials.md)
- [Assembly tutorial](documentation/assembly_tutorial.md)
- [Print resources](print_resources/README.md)

