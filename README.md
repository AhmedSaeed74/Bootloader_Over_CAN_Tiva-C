# Bootloader for TivaC Microcontrollers

## Project Overview

The Bootloader for TivaC Microcontrollers is a versatile system designed for code flashing and execution. This project enables users to send new code to a TivaC microcontroller using the CAN protocol or UART communication. It supports various features and provides flexibility for updating and running the latest code.

## Key Features

1. **Flash Code via CAN**: You can flash new code to the microcontroller using the CAN protocol, providing a reliable and efficient way to update the firmware.

2. **Flash Code via UART**: If you prefer, you can send new code via UART communication, simplifying the process further. Python scripts can be used for UART-based code flashing.

3. **Bootloader Mode**: The microcontroller can enter bootloader mode if it receives a programming session request within the first 5 seconds after reset.

4. **Code Size Handling**: The bootloader receives the code size and the code array over the CAN protocol, ensuring that the code update process is accurate.

5. **Memory Flag**: The bootloader determines which program to run based on the memory flag. This ensures that the latest version of the code is executed.

6. **UART Terminal**: You can monitor all processes using the UART terminal, providing visibility into the bootloader's behavior.

## Usage

1. **Flashing Code**:
   - You can send new code using the Python flasher over UART protocol.
   - If a programming session request is sent within the first 5 seconds after the microcontroller reset, it enters bootloader mode.

2. **Code Size and Array**:
   - The bootloader waits for the command to flash, and it receives both the code size and the code array over the CAN protocol.
   
3. **Execution Decisions**:
   - When there is no flashing request, the bootloader decides which program to run based on the memory flag.
   
4. **Monitoring**:
   - All processes, including flashing and execution decisions, can be monitored using the UART terminal.

## Project Structure

The project consists of two main components:

- Server: The server component, responsible for receiving and transmitting data packets. This script manages the network simulation.

- Client: The client component, designed to generate and send data packets to the server for transmission. Users can customize the packets generated.

## Contributing

Contributions and enhancements to this project are welcome. Feel free to fork the repository and create pull requests to improve the bootloader functionality.

