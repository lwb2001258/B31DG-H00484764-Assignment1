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
  ![image]https://github.com/lwb2001258/B31DG-H00484764-Assignment1/blob/main/Screenshot%202025-02-16%20203304.png
- Click the "Upload" button (right arrow icon) to compile and upload the code to the ESP32.

## 7. Monitor Serial Output
- After uploading the code, open the Serial Monitor by going to `Tools` > `Serial Monitor`.
- Set the baud rate to match the one used in your code (commonly 115200).
- You should see the output from your ESP32 in the Serial Monitor.

By following these steps, you can successfully set up and run the Arduino IDE for the ESP32-WROOM-32, allowing you to develop and upload code to this powerful microcontroller.
