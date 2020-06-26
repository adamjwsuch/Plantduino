# Plantduino
An Aquaponics system using Raspberry Pi brain and an Arduino controller

#Setting up as a service
Compile the plantduino executible, this is what the service will try to run.
`go build plantduino.go`

Copy plantduino.service to /lib/systemd/system/
`cp plantduino.service /lib/systemd/system/`

Reload daemon and add the new service
`sudo systemctl daemon-reload
sudo systemctl enable plantduino.service`

Now either restart the system:
`sudo reboot`
Or just start the service:
`sudo systemctl start plantduino.service`

#Compiling and uploading to arduino from the Raspberry Pi
I used the Arduino CLI so I did not have to have a UI.

Install the CLI by running:
`curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/usr/bin sh`
Full official instructions here: https://arduino.github.io/arduino-cli/installation/

Check it is installed correctly by just calling:
`arduino-cli`
This should give you the help message

Create a config file:
`arduino-cli config init`

Move to the Plantduino Arduino code directory:
`cd Arduino`
The Arduino CLI requires you to be at the top level of project, do not go into the "plantduino" dorectory where the code actually is of the compile and upload commands will not work.

Get the CLI index
`arduino-cli core update-index`

Check if your Arduino is found
`arduino-cli board list`
If your arduino is a cheap rip off one like mine it will not be identified in the FQBN section, this is fine we can specify it.

Download the core for our board
`arduino-cli board listall arduino:avr`
(This was fairly slow of my RPi, it looked like it had crashed but eventually just finished)

Compile the sketch
`arduino-cli compile --fqbn arduino:avr:nano plantduino`

Upload to the Arduino
`arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano plantduino`
Replace ttyUSB0 with the ID you got from the `arduino-cli board list` command
