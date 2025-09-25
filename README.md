# PosProWireless

Wireless configuration and operation of a POSPRO thermal printer using the **ESP32-S3-WROOM-1** module.  
This project demonstrates how to connect, configure, and control POSPRO 80x thermal printers wirelessly over Wi-Fi.

---

## Features
- ESP32-S3 based firmware using PlatformIO/Arduino framework.
- Wireless printing over Wi-Fi (client/server mode).
- Custom formatting commands for POSPRO 80x thermal printers.

---

## Hardware Requirements
- ESP32-S3-WROOM-1 development board.
- POSPRO 80x Series thermal printer.
- Power supply for ESP32 and printer.
- Wi-Fi network for wireless operation.

---

## Software Requirements
- [PlatformIO](https://platformio.org/) with VS Code.
- ESP32 Arduino Core.
- Required libraries (specified in `platformio.ini`).

---

## Repository Structure
PosProWireless/
├── .vscode/ # VSCode workspace settings
├── include/ # Header files
├── lib/ # External libraries
├── src/ # Main application source code
├── test/ # Unit tests
├── platformio.ini # PlatformIO project configuration
└── .gitignore

---

## Getting Started

### 1. Clone the Repository
```bash
git clone https://github.com/hsm-0510/PosProWireless.git
cd PosProWireless
```

### 2. Open in VS Code
Make sure PlatformIO extension is installed.

### 3. Build and Upload
Connect your ESP32-S3 board and run:
```bash
pio run --target upload
```

### 4. Monitor Serial Output
```bash
pio device monitor
```

## Usage
1. Configure Wi-Fi credentials in the source file.
2. ESP32 will connect to the network and expose printing functions.
3. Send ESC/POS or ASCII commands wirelessly to print formatted receipts.
