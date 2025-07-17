Pitt's Electrical and Computer Engineering departments Junior Design course allows the final project to be one that the student comes up with and chooses. I was inspired to create the Plant Pal. The idea was to have a way to monitor your plants, to ensure that you remember to water them and keep them safe from animals. The idea was to have a visible light near the plant that would turn on when the soil was to dry to signify it needs watered, sound an audio if movement near the plant is detected to scare away your cat that loves to bite your plants, and also create a way to track your plants status online while you are away. I did take this course over a summer semester, which is a few weeks shorter than the course is typically planned for. This resulted in a struggle for myself and most of the class as out time to spend on the final project was shorter than intended. This mainly showed in the timing of assembling a BOM, getting parts from the BOM ordered through the department, and having a short turn around time to build and test the project once the parts came in. There was no time to be able to properly breadboard and test components or find replacements if anything went wrong. With parts of mine arriving just days before the project due date, this project faced me with many obstacles. 
At the end of this README section, you can find the official report I submitted for the class, but below you will find a highlighted version. 

I did research into what components I would need to make this possible, and put together a rough sketch of the system

<img width="1443" height="712" alt="image" src="https://github.com/user-attachments/assets/0ff85551-212b-4fc8-ac7e-83e515e385db" />

Using an ESP8266 Wifi module, I could connect the outputs of a motion sensor and a capacitive soil mositure sensor to the systems visual and audio outputs of the sound, LED, and webpage. 

This was my first time using a board that I could program to work wirlessly not connected to my computer and with Wifi capabilities. So, when I first recieved the module and my components I started my testing process by testing smaller pieces at a time. First learning how to assemble HTML code into Arduino, and creating a simple page that would allow me to turn an LED on and off with a click of a button. Once I new that was functioning I connected the board to a power supply and ran it not connected to my laptop. With this functioning, I moved on programming the module to read in data from the motion sensor, and display it's outputs onto the website. True if there was movement detected, and false if not. I then finally tested playing audio out of my MP3 player using sounds saved to an SD card. 

Once I confirmed that all of these pieces were working individually, I started to integrate them together, and expand the webpage to display all of my desired information in a user friendly way.


[Plant Pal Report.pdf](https://github.com/user-attachments/files/21271861/Plant.Pal.Report.pdf)
