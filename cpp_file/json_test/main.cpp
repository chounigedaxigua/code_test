#include "data.h"
#include "json/json.h"
remote_engine_reply_t *remote_engine_reply = {0};
void struct_data_init(remote_engine_reply_t *remote_engine_reply)
{
    remote_engine_reply->ignition = "igOn";
    remote_engine_reply->resultCode = 0x12;

    remote_engine_reply->vehicleControl.acStatus.acDefFSetting = "F_ac";
    remote_engine_reply->vehicleControl.acStatus.acDefRSetting = "R_ac";

    remote_engine_reply->vehicleControl.acStatus.acTempVal = "0x20";
    remote_engine_reply->vehicleControl.acStatus.seatHeaterAsSetting = "on";
    remote_engine_reply->vehicleControl.acStatus.seatHeaterDrSetting = "off";
    remote_engine_reply->vehicleControl.acStatus.strHeaterSetting = "on";

    remote_engine_reply->vehicleControl.cabinTemperature.value = 23;
    remote_engine_reply->vehicleControl.cabinTemperature.unit = "c";

    remote_engine_reply->vehicleControl.controlCapability.acDefF = true;
    remote_engine_reply->vehicleControl.controlCapability.acDefR = false;
    remote_engine_reply->vehicleControl.controlCapability.seatHeaterAs = true;
    remote_engine_reply->vehicleControl.controlCapability.seatHeaterDr = false;
    remote_engine_reply->vehicleControl.controlCapability.strHeater = true;

    remote_engine_reply->vehicleControl.vehicleStartEvent.eventTime = "0x20";
    remote_engine_reply->vehicleControl.vehicleStartEvent.rStartCounter = 10086;

    remote_engine_reply->vehicleControl.vehicleStartStatus = "yoxi";
}

int haha(char *str)
{
    if(0 == strcpy(str,"on"))
        return 1;
    if(0 == strcpy(str,"off"))
        return 2;
    return 0;
}
int main()
{  
    struct json_tokener *root;
    // struct_data_init(remote_engine_reply);
    char *ptr;
    char arr[10];
    

    // root = json_object_new_object("root");

}