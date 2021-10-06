# Embedded-Systems--2020
Coursework for university Embedded Systems module using an Arduino

The goal of this coursework was to use the Arduino as a controller for a home. The user should be able to navigate the rooms in the home using buttons on the Arduino LCD shield and set levels and on and off times using the serial monitor, these should be saved in an appropriate data structure. The program should monitor input from the serial port so that if the user inputs the letter Q the current state of each device around the house to the serial monitor.

To enable the the user to navigate the house I made use of a Finite State Machine and to store the data I used an array of custom data type houseDataType. 
