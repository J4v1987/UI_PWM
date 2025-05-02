# UI_PWM
<h2>Arduino Nano: potentiometer-driven fast PWM implementation</h2>
![VID_20250501_182939-1](https://github.com/user-attachments/assets/00adf983-c324-493b-8f00-3c93333fc21c)
<br></br>
<h3><b>Design considerations:</b></h3>
  <p>G1. Nominal topology shall operate with mains 127VAC @ 60Hz.</p>
<br></br>
<h3><b>Features:</b></h3>
  <p>F1. UI-enabled PWM, based on Arduino Nano (Atmel ATMega328p).</p>
  <p>F2. Leverages Timer/Counter1 register to offer best hardware MCU resolution of 16bit.</p>
  <p>F3. Generates a fast-pwm signal on pin D9 with variable duty cycle, at nominal 120Hz, as provided hereby.</p>
  <p>F4. Leverages direct MCU register manipulation to efficiently adjust PWM waveform in frequency and duty-cycle.</p>
  <p>F5. Provides a UI consisting of a 10kΩ potentiometer to regulate duty-cycle.</p>
  <p>F6. Potentiometer wiper to be sampled at pin A0.</p>
  <p>F7. ADC registeres catch analog input A0 to adjust duty cycle register OCR1A.</p>
  <p>F8. PWM frequency to be adjusted with register ICR1.</p>
  <p>F9. Pulse width updates take place in ISR TIMER1_COMPA vector.</p>
  <p>F10. Schematic and BOM: 20250502 - SCH - UI_PWM.pdf</p>
<br></br>
<p><b>By: Javier.</b></p>
<p>Glad to advise your project:</p>
<p>Portfolio: https://sites.google.com/view/b-eng-jarl/home</p>
<p>Arduino Forums: j4v13r_987</p>
<p>GitHub: J4v1987</p>
<br></br>
<h3><b>History:</b></h3>
  <p>H1. Loaded to Arduino Nano V3 using Arduino IDE 2.3.6. Deemed operational as per read-me media.</p>

<br></br>
<h3><b>Further reading:</b></h3>
  <p>FR1. Atmel (2015). ATmega328P 8-bit AVR Microcontroller with 32K Bytes In-System Programmable Flash DATASHEET. [online] Available at: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf.</p>
  <p>FR2. Monk, S. (2017). Electronics Cookbook: Using PWM Outputs to Control Power Output. [online] https://learning.oreilly.com. Available at: https://learning.oreilly.com/videos/electronics-cookbook/ [Accessed 25 Apr. 2025].</p>
  <p>FR3. Scherz, Paul, and Simon Monk. “Practical Electronics for Inventors.” Https://Learning.oreilly.com, O’Reilly Media, Inc., Apr. 2016, learning.oreilly.com/library/view/practical-electronics-for. Accessed Apr. 2025. ISBN 978-1-25-958754-2, e-ISBN 978-1-25-958755-9.</p>
<br></br>
<h3><b>Acknowledgements:</b></h3>
  <p>ACK1. Harvard-style references: MyBib Contributors (2019). Harvard Referencing Generator – FREE – (updated for 2019). [online] MyBib. Available at: https://www.mybib.com/tools/harvard-referencing-generator.</p>
  <p>ACK2. Peer-checking and internet data scraping: Pi.ai. (2025). AVR PWM [thread]. Pi, your personal AI. [online] Available at: https://pi.ai.</p>
  <p>ACK3. Video editing: Kdenlive project. https://kdenlive.org/.</p>
  <p>ACK4. Operating system: Ubuntu. https://ubuntu.com/.</p>
<br></br>
<h3><b>Discussions:</b></h3>
  <p>DS1. Arduino Forum. (2025). Is the Timer/Counter 0 limited to prescaler of 64? [online] Available at: https://forum.arduino.cc/t/is-the-timer-counter-0-limited-to-prescaler-of-64/1376889?u=j4v13r_987 [Accessed 29 Apr. 2025].</p>
  <p>DS2. Dylan144GT (2018). Setting up Arduino Uno (ATMEGA328P) PWM with Timer1. [online] Stack Overflow. Available at: https://stackoverflow.com/questions/48873501/setting-up-arduino-uno-atmega328p-pwm-with-timer1.</p>

