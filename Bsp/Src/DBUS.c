#include "DBUS.h"

void DBUS_Resolved(uint8_t* Data, DBUS_Typedef *DBUS)
{
	DBUS_UNION_Typdef DBUS_UNION={0};
	memcpy(DBUS_UNION.GetData,Data,19);
	
	DBUS->Remote.CH0_int16=DBUS_UNION.DataNeaten.CH0-1024;
	DBUS->Remote.CH1_int16=DBUS_UNION.DataNeaten.CH1-1024;
	DBUS->Remote.CH2_int16=DBUS_UNION.DataNeaten.CH2-1024;
	DBUS->Remote.CH3_int16=DBUS_UNION.DataNeaten.CH3-1024;
	DBUS->Remote.S1_u8=DBUS_UNION.DataNeaten.S1;
	DBUS->Remote.S2_u8=DBUS_UNION.DataNeaten.S2;
	
	
}

