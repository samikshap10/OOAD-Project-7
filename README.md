# SmartHomeSim

SmartHomeSim is a C++-based command-line simulator for managing and interacting with smart home devices. It allows users to simulate real-world behaviors of devices like lights, fans, and thermostats, apply behavior strategies, and observe responses to environmental changes through sensors.

## Demo Videos

- 🔗 **Demo Video From Project 6** – [View on Google Drive](https://drive.google.com/file/d/1RGMu4TbikQrhSctLRyjn1CwyUQJIdqyg/view?usp=drive_link)
- 🔗 **CMI (CLI) Walkthrough Covering All Use Cases** – [Watch Full Use Case Demo](https://o365coloradoedu-my.sharepoint.com/:v:/g/personal/sapa6655_colorado_edu/EWKvrvXR1gRFsrf7V1Oj9hkBgEkS0O7JQ-bSmXc5n9I5hw?e=GISOfz)
- 🔗 **Additional Features added after Project 6 in Project 7** – [Watch Feature Add-ons Video](https://o365coloradoedu-my.sharepoint.com/:v:/g/personal/sapa6655_colorado_edu/EWTFCvS-FdFNrovHbBo4-DIB7s47E8kaQ5vpDTJ546Tm8w?e=0wF6NP)

## Project Goals

- Simulate a smart home environment using object-oriented principles
- Support device addition, toggling, scheduling, and event-based control
- Demonstrate key OO design patterns: **Factory**, **Observer**, **Strategy**
- Provide a clean CLI for users to interact with and manage the system
- Emphasize modularity, extensibility, and simulation of real-world behavior

---

## Features

- **Add Smart Devices**: Dynamically create Lights, Fans, and Thermostats using the Factory Pattern
- **Toggle Devices**: Turn devices on or off using their names via the command-line interface
- **Sensor Simulation**: Simulate environmental changes (e.g., temperature rise) and notify subscribed devices
- **Thermostat Behavior Modes**: Use Strategy Pattern to switch thermostat logic between `EcoMode` and `ComfortMode`
- **Logging System**: All device actions are logged using an Observer-based `DeviceLogger`
- **Device Listing**: View all currently registered smart devices
- **Scheduling System**: Automate device behavior with one-time, delayed, and periodic triggers using `SchedulingStrategy`
- **Manual Time Simulation**: Advance time manually in the CLI to simulate future events without threading

---

## Object-Oriented Design & Patterns

| Design Pattern                | Implementation                                                                         |
| ----------------------------- | -------------------------------------------------------------------------------------- |
| **Factory**                   | `DeviceFactory` creates `Light`, `Fan`, and `Thermostat` instances based on type       |
| **Observer**                  | `Sensor` notifies subscribed `SmartDevice`s and `DeviceLogger` of triggered events     |
| **Strategy**                  | `Thermostat` uses `TemperatureStrategy` (Eco/Comfort) to determine behavior            |
| **Custom Scheduling Pattern** | `Scheduler` uses a `SchedulingStrategy` hierarchy to control time-based device actions |

---

## OOAD Process Reflection

- **Iterative Design Growth**: The initial class structure from Project 5 evolved through Projects 6 and 7 to support modularity and real-time simulation capabilities. This included separating concerns between device control and scheduling.
- **Pattern Integration Challenges**: Integrating multiple design patterns like Observer and Strategy required careful coordination to prevent tight coupling. These were thoughtfully applied where they added clarity and extensibility.
- **Balancing Realism and Scope**: An attempt was made to add a real-time automatic timer using threads, but it was ultimately excluded to avoid unnecessary complexity. Instead, a manual tick system was used to simulate time progression in a more controlled and course-appropriate way.

---

## Third-Party Code Statement

All source code in this project was written originally by the developer. No external frameworks or third-party libraries were used. For reference and conceptual understanding, the following sources were consulted:

- [cplusplus.com](https://www.cplusplus.com/) — C++ syntax and STL usage
- [Refactoring Guru](https://refactoring.guru/design-patterns) — Design pattern principles

Additionally, OpenAI’s ChatGPT was used to brainstorm implementation approaches and review documentation wording.

---
