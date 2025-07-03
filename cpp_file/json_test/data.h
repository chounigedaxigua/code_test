#ifndef REMOTE_ENGINE_H
#define REMOTE_ENGINE_H
// #include "sal_def_inc.h"
// #include "openssl_def.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define OFF_MODE              0x00
#define PRE_START_MODE        0x01
#define RES_START_MODE        0x02
#define PRE_OFF_MODE          0x03
#define RES_IG_RUN_MODE       0x04
#define RES_IG_RUN_WAIT_MODE  0x05
#define PRE_IG_RUN_MODE       0x06
#define ACC_MODE              0x07
#define IG_STOP_MODE          0x08
#define IG_RUN_MODE           0x09
#define START_MODE            0x0A
#define IS_RESUME_MODE        0x0B
#define DI_RESUME_MODE        0x0C

#define DOOR_STATUS_LOCK 0x00
#define DOOR_STATUS_UNLOCK 0x01
typedef int sal_int32_t;
typedef char sal_char_t;
typedef bool sal_bool_t;
// Table 4.44-1 List of inputs and outputs
typedef struct _vehicles_start_duration_t
{
    sal_int32_t value;//[1 - 60]

    sal_char_t *unit; //单位 min

}vehicles_start_duration_t;
typedef struct _ac_settings_t
{
    sal_char_t *acTempVal;
    sal_char_t *acDefFSetting;
    sal_char_t *acDefRSetting;
    sal_char_t *strHeaterSetting;
    sal_char_t *seatHeaterDrSetting;
    sal_char_t *seatHeaterAsSetting;
}ac_settings_t;

typedef struct _vehicle_control
{
    vehicles_start_duration_t vehicleStartDuration;
    ac_settings_t acSetting;
}vehicle_control_t;


typedef struct _remote_engine_order
{
    char *command;
    vehicle_control_t vehicleControl;
    
}remote_engine_order_t;
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _cabin_temperature
{
    sal_int32_t value;
    sal_char_t *unit;
}cabin_temperature_t;

typedef struct _control_capability
{
    sal_bool_t acDefF;
    sal_bool_t acDefR;
    sal_bool_t strHeater;
    sal_bool_t seatHeaterDr;
    sal_bool_t seatHeaterAs;

}control_capability_t;
typedef struct _vehicle_start_event
{
    sal_int32_t rStartCounter;
    sal_char_t *eventTime;
}vehicle_start_event_t ;
typedef struct _ac_status
{
    sal_char_t *acTempVal;
    sal_char_t *acDefFSetting;
    sal_char_t *acDefRSetting;
    sal_char_t *strHeaterSetting;
    sal_char_t *seatHeaterDrSetting;
    sal_char_t *seatHeaterAsSetting;
}ac_status_t;

typedef struct _vehicle_control_reply
{
    cabin_temperature_t cabinTemperature;
    sal_char_t *vehicleStartStatus;
    control_capability_t controlCapability;
    vehicle_start_event_t vehicleStartEvent;
    ac_status_t acStatus;
}vehicle_control_replay_t;
typedef struct _remote_engine_reply
{
    sal_char_t *ignition;
    sal_int32_t resultCode;
    vehicle_control_replay_t vehicleControl;
}remote_engine_reply_t;

#endif