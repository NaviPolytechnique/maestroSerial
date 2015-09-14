//
//  maestroSerial.h
//  
//
//  Created by Charles Roques-Carmes on 11/08/2015.
//
//

#ifndef ____maestroSerial__
#define ____maestroSerial__

#include <stdio.h>
#include "serial_exception.hpp"
#include "Serial.h"
#include <exception>

#include <iostream>


/** ------------------------------------------------------------------------------------------------
 * \brief Sends all servos and outputs to their home positions, just as if an error had occurred.
 * Returns 1 if successful, -1 in the other case.
 **/

int maestroSerialgoHome(Serial* maestro);

//-------------------------------------------------------------------------------------------------//

/** ------------------------------------------------------------------------------------------------
 * \brief Reads the position of the servo on channel of the Serial maestro
 * \param Serial instance of the maestro port
 * \param Channel of the servo
 * Returns the position of the servo or -1 if unsucessful. Interval to be determined.
 **/

int maestroSerialgetPos(Serial* maestro, int channel);

//-------------------------------------------------------------------------------------------------//


/** ------------------------------------------------------------------------------------------------
 * \brief Reads the position of the servo on channel of the Serial maestro and convert it
 * \param Serial instance of the maestro port
 * \param Channel of the servo
 * Returns the position of the servo in rd/s or -1 if unsucessful. Interval to be determined.
 **/

double maestroSerialgetPosSI(Serial* maestro, int channel);

//-------------------------------------------------------------------------------------------------//



/** ------------------------------------------------------------------------------------------------
 * \brief Sets the position of the servo on channel of the Serial maestro
 * \param Serial instance of the maestro port
 * \param Channel of the servo
 * \param Target to be set, between 1000micros (max speed in trigonometric sense) and 2000micros (max speed in clockwork sense). For the moment the unit is 4*microseconds (same target as shown in the MaestroControlCenter : between 4000 and 8000).
 * Return 1 if success
 *       -1 if error during reading/writing the bytes
 **/

int maestroSerialsetPos(Serial* maestro, int channel, int target);

//-------------------------------------------------------------------------------------------------//

/** ------------------------------------------------------------------------------------------------
 * \brief Sets the position of the servo on channel of the Serial maestro
 * \param Serial instance of the maestro port
 * \param Channel of the servo
 * \param Target to be set, between -v_max and +v_max (v_max is the max speed in trigonometric sense, given in rd/s). 
 * Return 1 if success
 *       -1 if error during reading/writing the bytes
 **/

int maestroSerialsetPosSI(Serial* maestro, int channel, double targetSI);

//-------------------------------------------------------------------------------------------------//

/** ------------------------------------------------------------------------------------------------
 * \brief Sets speed limit of the servo on channel of the Serial maestro.
 The speed limit is given in units of (0.25 μs)/(10 ms).
 WARNING : this unit only applies if you use a period of 20ms, which can be changed with Pololu Maestro 12, 18 and 24.
 The minimum value is 1. Value 0 makes immediate changes.
 * \param Serial instance of the maestro port
 * \param Channel of the servo
 * \param Target to be set.
 * Returns 1 if successful, -1 in the other case.
 **/

int maestroSerialsetSpeed(Serial* maestro, int channel, int target);

//-------------------------------------------------------------------------------------------------//

/** ------------------------------------------------------------------------------------------------
 * \brief Sets speed limit of the servo on channel of the Serial maestro.
 The speed limit is given in units of rd/s^2.
 The minimum value is 1. Value 0 makes immediate changes.
 * \param Serial instance of the maestro port
 * \param Channel of the servo
 * \param Target to be set.
 * Returns 1 if successful, -1 in the other case.
 **/

int maestroSerialsetSpeedSI(Serial* maestro, int channel, double targetSI);

//-------------------------------------------------------------------------------------------------//



/**
* \brief Sets acceleration LIMIT of the servo on channel of the Serial maestro.
*The acceleration limit is given in units of (0.25 μs)/(10 ms)/(80 ms).
*The acceleration limit is a value from 0 to 255 in units of (0.25 μs)/(10 ms)/(80 ms)* 
 WARNING : this unit only applies if you use a period of 20ms, which can be changed with Pololu Maestro 12, 18 and 24.
* \param Serial instance of the maestro port
* \param Channel of the servo
* \param Target to be set.
* Returns 1 if successful, -1 in the other case.
**/

int maestroSerialsetAcc(Serial* maestro, int channel, int target);

//-------------------------------------------------------------------------------------------------//

/**
 * \brief Sets the position with a smooth behavior
 * \param Serial instance of the maestro port
 * \param Channel of the servo
 * \param Target to be set in rd/s.
 $ \param time to get to target in s
 * Returns 1 if successful, -1 in the other case.
 **/

int maestroSmoothTarget(Serial* maestro, int channel, double targetSI, double tau);

//-------------------------------------------------------------------------------------------------//





#endif /* defined(____maestroSerial__) */
