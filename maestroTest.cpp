//
//  maestroTest.cpp
//  
//
//  Created by Charles Roques-Carmes on 11/08/2015.
//
//

#include <stdio.h>
#include "maestroSerial.h"
#include "serial_exception.hpp"
#include "Serial.h"
#include <exception>
#include <iostream>


using namespace std;

int main(int argc, char *argv[]){
    
    // General setup : baud rate constant for the moment. Should not be changed.
    int baud_rate = 9600;
    
    
    // Test values : Pololu maestro 6 pin + Servo continuous rotation connected to channel 5
    const char* maestro_port_name = "/dev/tty.usbmodem00114861";
    
    int channel = 5;
    
    try{
        
        Serial maestro(maestro_port_name,baud_rate);

/*        maestroSerialsetPosSI(&maestro,channel,0);
        maestroSerialsetSpeed(&maestro, channel, 1);
        std::cout<<maestroSerialsetAcc(&maestro, channel, 1)<<std::endl;
        maestroSerialsetPosSI(&maestro, channel, 0);
        maestroSerialsetAcc(&maestro, channel, 1);*/
        
        maestroSerialsetSpeed(&maestro, channel,1);
        maestroSerialsetPosSI(&maestro, channel, 0);
        while(maestroSerialgetPosSI(&maestro, channel)<4.92){
            usleep(100000);
            std::cout<<maestroSerialgetPosSI(&maestro, channel)<<std::endl;
        }
        sleep(2);
        maestroSerialsetSpeed(&maestro, channel,10);
        while(maestroSerialgetPosSI(&maestro, channel)<4.92){
            usleep(100000);
            std::cout<<maestroSerialgetPosSI(&maestro, channel)<<std::endl;
        }
        sleep(2);
        maestroSerialsetSpeed(&maestro, channel,1);
        while(maestroSerialgetPosSI(&maestro, channel)<4.92){
            usleep(100000);
            std::cout<<maestroSerialgetPosSI(&maestro, channel)<<std::endl;
        }
        sleep(2);

//        maestroSmoothTarget(&maestro, channel, 0, 20);// ne marche pas encore

        while(maestroSerialgetPosSI(&maestro, channel)<4.92){
            usleep(100000);
            std::cout<<maestroSerialgetPosSI(&maestro, channel)<<std::endl;
        }

    }
    catch (exception const& e){
        cout << "ERR : " << maestro_port_name << " : " << e.what() << " ! " << endl;
    }

    
    return 0;

}