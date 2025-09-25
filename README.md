# Smart-Trash-Can-BINBOT
An intelligent and hygienic waste management system designed to automate lid opening, monitor waste levels, and calculate trash weight for enhanced convenience and sustainability.

Features
Automated Lid Mechanism: Hands-free lid operation using ultrasonic sensors and a servo motor.
Waste Level Monitoring: Real-time detection of trash levels categorized as Low, Medium, or High.
Weight Calculation: Estimates the weight of trash using depth, volume, and density values.
Compact and Efficient Design: Ideal for homes, offices, and public spaces.

**Table of Contents**

Introduction

Hardware Requirements

Software Requirements

Setup and Installation

How It Works

Code

Future Enhancements

Contributing

License


**Hardware Requirements**

Arduino Uno

Ultrasonic Sensors (2x)

Servo Motor

Breadboard and Jumper Wires

Power Supply

Dustbin (Customized for project dimensions)



**Software Requirements**

Arduino IDE (Version 1.8.19 or later)

Serial Monitor for data visualization


**How It Works**

Lid Control:

An ultrasonic sensor detects when a user approaches the bin (within 20 cm).

The servo motor automatically opens the lid, waits for 3 seconds, and then closes it.

Waste Level Detection:


Another ultrasonic sensor measures the depth of trash in the bin.

Categorizes waste levels as Low, Medium, or High.

Weight Calculation:


Calculates trash weight using the measured depth, volume of the bin, and a predefined density constant.


A Test Change