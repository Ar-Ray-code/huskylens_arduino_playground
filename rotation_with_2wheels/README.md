# rotation_with_2wheels(huskylens_arduino_playground)

How to track object by HUSKYLENS ?

![how_to_track](example_image/how_to_track.png)

Arduino UNO's GPIO connection

- 10：Software Serial RX to HUSKYLENS's TX
- 11：Software Serial TX to HUSKYLENS's RX
- A4：I2C SDA to PCA9685's SDA
- A5：I2C SCL to PCA9685's SCL
- 5V：Connect to HUSKYLENS's Power
- GND：Connect to HUSKYLENS's GND
- Battery : 2-cell 300mAh Lipo battery

#### Demo

![data1](example_image/data1.gif)

![data1](example_image/data2.gif)