# Stepper Motor Metronome

We designed a digital metronome using GPIO, hardware interrupts, a timer (FTM3), and a stepper motor on a FRDM-K64F microcontroller. The system is controlled by 3 physical buttons wired to interrupts to increase
or decrease the BPM or turn the the motor on/off. 

The circuit also displays the current bpm of the stepper motor metronome using a 7-segment display. 
Arduino is only used for producing the tick sound with a buzzer. 

**[Watch the Demo Video on YouTube](https://youtu.be/edP20gJBEIU)**

## Hardware Diagram

![hardware diagram](block%20diagram.png)

## Software Flowchart

![software flowchart](software%20flowchart.png)

## Setup

![setup](setup.png)
