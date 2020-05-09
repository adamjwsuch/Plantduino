package main

import (
	"github.com/d2r2/go-i2c"
	"github.com/robfig/cron"
	"fmt"
	"time"
)

const ArduinoAddress = 0x08

func main() {
	i2c, err := i2c.NewI2C(ArduinoAddress, 1)
	if err != nil {
		fmt.Println("error opening i2c")
	}
	defer i2c.Close()

	c := cron.New()

	c.AddFunc("00 10 * * *", func() {
		//Lights on
		fmt.Println("Turning lights on at: ", time.Now())
		_, err := i2c.WriteBytes([]byte{0x5})
		if err != nil {
			fmt.Println("error writing to i2c")
		}
	} )
	c.AddFunc("00 14 * * *", func() {
		//Lights off
		fmt.Println("Turning lights off at: ", time.Now())
		_, err := i2c.WriteBytes([]byte{0x6})
		if err != nil {
			fmt.Println("error writing to i2c")
		}
	} )
	c.Start()
	fmt.Printf("%+v\n", c.Entries())
    done := make(chan bool)
    <-done
}

func TimeTask() {
    fmt.Println(time.Now())
    fmt.Println("do some job.")
}

// func motor1on() {
// 	fmt.Println("Turning Motor 1 on at: ", time.Now())
// 	_, err := i2c.WriteBytes([]byte{0x1})
// 	if err != nil {
// 		fmt.Println("error writing to i2c")
// 	}
// }
// func motor1off() {
// 	fmt.Println("Turning Motor 1 off at: ", time.Now())
// 	_, err := i2c.WriteBytes([]byte{0x2})
// 	if err != nil {
// 		fmt.Println("error writing to i2c")
// 	}
// }
// func lightson() {
// 	fmt.Println("Turning lights on at: ", time.Now())
// 	_, err := i2c.WriteBytes([]byte{0x5})
// 	if err != nil {
// 		fmt.Println("error writing to i2c")
// 	}
// }
// func lightsoff() {
// 	fmt.Println("Turning lights off at: ", time.Now())
// 	_, err := i2c.WriteBytes([]byte{0x6})
// 	if err != nil {
// 		fmt.Println("error writing to i2c")
// 	}
// }

