Pitt's Electrical and Computer Engineering departments Junior Design course allows the final project to be one that the student comes up with and chooses. I was inspired to create the Plant Pal. The idea was to have a way to monitor your plants, to ensure that you remember to water them and keep them safe from animals. The idea was to have a visible light near the plant that would turn on when the soil was to dry to signify it needs watered, sound an audio if movement near the plant is detected to scare away your cat that loves to bite your plants, and also create a way to track your plants status online while you are away. I did take this course over a summer semester, which is a few weeks shorter than the course is typically planned for. This resulted in a struggle for myself and most of the class as out time to spend on the final project was shorter than intended. This mainly showed in the timing of assembling a BOM, getting parts from the BOM ordered through the department, and having a short turn around time to build and test the project once the parts came in. There was no time to be able to properly breadboard and test components or find replacements if anything went wrong. With parts of mine arriving just days before the project due date, this project faced me with many obstacles. 

 Below you will find a highlighted version of my final report for my Plant Pal project, with the actual report I submitted for class and the presentation slideshow attatched to the end for a more in dpeth view. 

I did research into what components I would need to make this possible, and put together a rough sketch of the system

<img width="1443" height="712" alt="image" src="https://github.com/user-attachments/assets/0ff85551-212b-4fc8-ac7e-83e515e385db" />

Using an ESP8266 Wifi module, I could connect the outputs of a motion sensor and a capacitive soil mositure sensor to the systems visual and audio outputs of the sound, LED, and webpage. 

This was my first time using a board that I could program to work wirlessly not connected to my computer and with Wifi capabilities. So, when I first recieved the module and my components I started my testing process by testing smaller pieces at a time. First learning how to assemble HTML code into Arduino, and creating a simple page that would allow me to turn an LED on and off with a click of a button. Once I new that was functioning I connected the board to a power supply and ran it not connected to my laptop. With this functioning, I moved on programming the module to read in data from the motion sensor, and display it's outputs onto the website. True if there was movement detected, and false if not. I then finally tested playing audio out of my MP3 player using sounds saved to an SD card. 

Once I confirmed that all of these pieces were working individually, I started to integrate them together, and expand the webpage to display all of my desired information in a user friendly way. Having already tested everything individually, besides the mositure sensors, most of the final assembly went easily. My biggest stuggle came with the audio outputs. My professor suggested playing a sound both when the plant needed water and when there was motion detected. It took a good amount of research, and a lot of trial and error to figure out how to set up 2 different audios to play by two different triggers. Another major obstacle was the soil mositure sensors themselves. I was attempting to use them by measuring "moist soil" as a cup of water with salt, and "dry soil" to be in the air and not in the water. The sensor ideally would then output a number within a certain range for each soil type and I would be able to use a comparison that number to tell the current state of the soil. The sensors I was using though did not work well, I would get differnet ranges for each soil type everytime I tried to test it, so it made a comparison impossible to get functioning. I had multiple in order to test them, but I recieved similar "random" outputs with each. Some of them I was also experiencing extreme over heating issues with, so I had to use them carefully. 

I was able to get eveything to function for a short period of time, where I could gather some demonstrations of the system fuctioning and all the parts working together and testing all of the inputs/outs back to back or simultaneously. 

The final view of the website visual 
<img width="2348" height="574" alt="image" src="https://github.com/user-attachments/assets/9157b589-3b57-49ba-b23e-9247c9dda883" />

The final look and set up of the project 
<img width="1575" height="867" alt="image" src="https://github.com/user-attachments/assets/48d0e816-180c-462e-b80a-b6c903008215" />


While I personally am not a plant or animal care taker, I have had my share of roomates who struggle to remember to water their plant and keep their chew happy cats from eating what they shouldn't. Future work I can do on this project includes finding a more suitable and reliable mositure sensor, creating an appropriate enclosure, and have my roomates test out a prototype version and provide any feedback. 

Thank you for taking the time to look at my project! 

[Plant Pal Presentation.pdf](https://github.com/user-attachments/files/21273571/Plant.Pal.Presentation.pdf)

[Plant Pal Report.pdf](https://github.com/user-attachments/files/21271861/Plant.Pal.Report.pdf)
