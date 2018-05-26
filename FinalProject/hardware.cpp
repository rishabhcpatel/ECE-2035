// This header has all the (extern) declarations of the globals.
// "extern" means "this is instantiated somewhere, but here's what the name
// means.
#include "globals.h"

#include "hardware.h"

// We need to actually instantiate all of the globals (i.e. declare them once
// without the extern keyword). That's what this file does!

// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p9,p10,p11);             // LCD Screen (tx, rx, reset)
//SDFileSystem sd(p5, p6, p7, p8, "sd");  // SD Card(mosi, miso, sck, cs)
Serial pc(USBTX,USBRX);                 // USB Console (tx, rx)
MMA8452 acc(p28, p27, 100000);        // Accelerometer (sda, sdc, rate)
DigitalIn button1(p22);                 // Pushbuttons (pin)
DigitalIn button2(p23);
DigitalIn button3(p24);
Speaker mySpeaker(p21);
//AnalogOut DACout(p18);                  // Speaker (pin)
//PwmOut speaker(p26);
//wave_player waver(&DACout);

// Some hardware also needs to have functions called before it will set up
// properly. Do that here.
int hardware_init()
{
    // Crank up the speed
    uLCD.baudrate(3000000);
    pc.baud(115200);
        
    //Initialize pushbuttons
    button1.mode(PullUp); //action button
    button2.mode(PullUp); //omnipotent button
    button3.mode(PullUp); //menu button      
    
    return ERROR_NONE;
}

GameInputs read_inputs() 
{
    GameInputs in;
    
    double *xAccel = &in.ax;
    double *yAccel = &in.ay;
    double *zAccel = &in.az;
    
    acc.readXGravity(xAccel);
    acc.readYGravity(yAccel);
    acc.readZGravity(zAccel);
    
    in.ax = *xAccel;
    in.ay = *yAccel;
    in.az = *zAccel;
    
    in.b1 = button1;
    in.b2 = button2;
    in.b3 = button3;
    
    return in;
}
