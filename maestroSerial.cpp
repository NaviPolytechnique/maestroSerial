//
//  maestroSerial.cpp
//  
//
//  Created by Charles Roques-Carmes on 11/08/2015.
//
//

#include "maestroSerial.h"
#include "Serial.h"
#include <cstdio>
#include <string.h>
#include <exception>
#include <math.h>

#include <stdio.h>
#include "serial_exception.hpp"
#include <iostream>

using namespace std;

static double v_max=4.92;//max speed in rd/s


int maestroSerialgoHome(Serial* maestro){
    
    unsigned char command[1]={0xA2};
    if(maestro->write_bytes(command,1)==-1){
        throw serial_exception::serial_exception(1,"Failed to write on port",0);
    }
    return 1;
}


int maestroSerialgetPos(Serial* maestro, int channel){
    
    unsigned char command[2] = {0x90, static_cast<unsigned char>(channel)}; //Buffer of the "position" bytes. Source : Pololu documentation
    
    if(maestro->write_bytes(command, sizeof(command))==-1){
        throw serial_exception::serial_exception(1,"Failed to write on port",0);
    }
    
    unsigned char res[sizeof(command)];
    if(maestro->read_bytes(res, sizeof(res))==-1){//Warning : Serial::ready_bytes does not return the number of successfuly written bytes, only 1 or -1
        throw serial_exception::serial_exception(1,"Failed to read port",0);
    }
    
    return (*res)+256*(*(res+1));
    
}

double maestroSerialgetPosSI(Serial* maestro, int channel){
    
    return (6000-maestroSerialgetPos(maestro, channel))*v_max/2000;
    
}


int maestroSerialsetPos(Serial* maestro, int channel, int target){

    unsigned char command[4] = {0x84, static_cast<unsigned char>(channel),static_cast<unsigned char>(target & 0x7F), static_cast<unsigned char>(target >> 7 & 0x7F)};//Byte of Pololu SetPos, channel, target low byte, target high byte.
    
    int ret = maestro->write_bytes(command,sizeof(command));
    if(ret==-1){
        throw serial_exception::serial_exception(1,"Failed to write on port",0);
    }
    return ret;
}

int maestroSerialsetPosSI(Serial* maestro, int channel, double targetSI){

    return maestroSerialsetPos(maestro, channel, (int)(6000-targetSI*2000/v_max));
    
}


int maestroSerialsetSpeed(Serial* maestro, int channel, int target){
    
    unsigned char command[4] = {0x87, static_cast<unsigned char>(channel),static_cast<unsigned char>(target & 0x7F), static_cast<unsigned char>(target >> 7 & 0x7F)};//Byte of Pololu SetSpeed, channel, target low byte, target high byte.
    
    if(maestro->write_bytes(command,sizeof(command))==-1){
        throw serial_exception::serial_exception(1,"Failed to write on port",0);
        return -1;
    }
    
    return 1;
}

int maestroSerialsetSpeedSI(Serial* maestro, int channel, double targetSI){
    
    int target = targetSI*80/v_max/4;//with the Pololu 6pin, the minimum speed does not correspond to the data we have : speed 1 corresponds to v_max/20 rd.s^-2 approximately
    //int target =targetSI*80/v_max;
    std::cout<<target<<std::endl;
    return maestroSerialsetSpeed(maestro, channel, target);
}


int maestroSerialsetAcc(Serial* maestro, int channel, int target){
    
    unsigned char command[4] = {0x89, static_cast<unsigned char>(channel),static_cast<unsigned char>(target & 0x7F), static_cast<unsigned char>(target >> 7 & 0x7F)};//Byte of Pololu SetAcc, channel, target low byte, target high byte.
    
    if(maestro->write_bytes(command,sizeof(command))==-1){
        throw serial_exception::serial_exception(1,"Failed to write on port",0);
        return -1;
    }
    
    return 1;
}

int maestroSmoothTarget(Serial* maestro, int channel, double targetSI, double tau){
    
    maestroSerialsetSpeed(maestro, channel, 1);
    maestroSerialsetPosSI(maestro, channel, targetSI);
    for(double t=0; t<tau;t=t+0.001){
        double speed =2*targetSI/tau*exp(-((t-tau/2)*(t-tau/2)/((tau*tau))));
        if(speed>1){
            maestroSerialsetSpeed(maestro, channel, speed);
        }
        else maestroSerialsetSpeed(maestro, channel, 1);

    }
    
    return 1;
}


