# Detailed Introduction to the Setup and Operation of the Arduino IDE Compiler for the ESP32-WROOM-32

To set up and run the Arduino IDE for the ESP32-WROOM-32, follow these steps:

## 1. Install Arduino IDE
- Download and install the latest version of the Arduino IDE from the [official Arduino website](https://www.arduino.cc/en/software).

## 2. Add ESP32 Board Support
- Open the Arduino IDE.
- Go to `File` > `Preferences`.
- In the "Additional Boards Manager URLs" field, add the following URL: https://dl.espressif.com/dl/package_esp32_index.json
- Click "OK" to close the Preferences window.

## 3. Install ESP32 Board Package
- Go to `Tools` > `Board` > `Boards Manager`.
- In the search bar, type "ESP32".
- Find the "ESP32 by Espressif Systems" package and click "Install".

## 4. Select the ESP32-WROOM-32 Board
- After the installation is complete, go to `Tools` > `Board` > `ESP32 Arduino`.
- Select "ESP32 Dev Module" or "ESP32-WROOM-32" from the list.

## 5. Configure the Board Settings
- Go to `Tools` and set the following options:
- **Upload Speed**: "921600"
- **CPU Frequency**: "240MHz (WiFi/BT)"
- **Flash Frequency**: "80MHz"
- **Flash Mode**: "QIO"
- **Partition Scheme**: "Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)"
- **Port**: Select the appropriate COM port where your ESP32 is connected.

## 6. Upload Code
- Open the code file B31_DG_assignment.ino
- Setup the ESP32-Wroom-32 board by the circuit image
  ![image](https://github.com/lwb2001258/B31DG-H00484764-Assignment1/blob/main/circuit_image.png)
- Click the "Upload" button (right arrow icon) to compile and upload the code to the ESP32.
- The flowchart of the application is shown in the following images
   ![image](https://github.com/lwb2001258/B31DG-H00484764-Assignment1/blob/main/flowchart.png)

## 7. Monitor Serial Output
- After uploading the code, open the Serial Monitor by going to `Tools` > `Serial Monitor`.
- Set the baud rate to match the one used in your code (commonly 115200).
- You should see the output from your ESP32 in the Serial Monitor.

By following these steps, you can successfully set up and run the Arduino IDE for the ESP32-WROOM-32, allowing you to develop and upload code to this powerful microcontroller.


# Detailed Introduction to Setting Up and Running VSCode with ESP-IDF for the ESP32-WROOM-32

To set up and run VSCode with ESP-IDF for the ESP32-WROOM-32, follow these steps:

## 1. Install Prerequisites
- **VSCode**: Download and install [Visual Studio Code](https://code.visualstudio.com/).
- **ESP-IDF**: Install the ESP-IDF framework by following the official [ESP-IDF setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).

## 2. Install ESP-IDF Extension in VSCode
- Open VSCode.
- Go to the Extensions Marketplace by clicking the Extensions icon in the Activity Bar or pressing `Ctrl+Shift+X`.
- Search for "ESP-IDF" and install the official ESP-IDF extension by Espressif Systems.

## 3. Configure ESP-IDF in VSCode
- After installing the ESP-IDF extension, open the Command Palette by pressing `Ctrl+Shift+P`.
- Search for and select `ESP-IDF: Configure ESP-IDF extension`.
- Follow the on-screen instructions to set up the ESP-IDF tools. You can choose to download and install the required tools automatically or manually configure an existing ESP-IDF installation.

## 4. Set Up the ESP32-WROOM-32 Board
- Open the Command Palette again (`Ctrl+Shift+P`).
- Search for and select `ESP-IDF: Set Espressif device target`.
- Choose `ESP32` as the target chip.

## 5. Create or Open a Project
- To create a new project, use the Command Palette and select `ESP-IDF: Create new project`.
- To open an existing project, use `File` > `Open Folder` and select the project directory.

## 6. Configure Project Settings
- Open the `CMakeLists.txt` file in the root of your project to configure build settings.
- Ensure the `set(ESP_PLATFORM 1)` line is present and correctly configured for the ESP32-WROOM-32.

## 7. Build the Project
- Open the Command Palette and select `ESP-IDF: Build your project`.
- The extension will compile your project using the ESP-IDF toolchain.

## 8. Flash the Firmware
- Connect your ESP32-WROOM-32 to your computer via USB.
- Open the Command Palette and select `ESP-IDF: Select port to use`.
- Choose the appropriate serial port for your device.
- To flash the firmware, use the Command Palette and select `ESP-IDF: Flash your project`.

## 9. Monitor Serial Output
- Open the Command Palette and select `ESP-IDF: Open the serial monitor`.
- Set the baud rate to match your project configuration (commonly 115200).
- You should see the output from your ESP32-WROOM-32 in the serial monitor.

By following these steps, you can successfully set up and run VSCode with ESP-IDF for the ESP32-WROOM-32, enabling efficient development, and firmware flashing for your projects.
