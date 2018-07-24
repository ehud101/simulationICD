/*
* InternalGPSMessage.cpp
* Tiltan internal GPS message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "InternalGPSMessage.h"
#include "TiltanData.h"
#include "Helper.h" // Utilities::StrcpyCrossPlatform
#include <cstring> // memset, memcpy

void InternalGPSMessage::FillMessage(const TiltanData& data) {
	Tiltan_Internal_GPS msg;
	FillHeader(msg.Header);
	msg.Time_From_Startup = data.GetSimTime() * TIME_MULTIPLY;
	msg.UTC_Time = data.GetUtcTime() * TIME_MULTIPLY;
	msg.GPS_FOM = data.GetIntGpsGpsFom();
	msg.Num_Of_Satelites_In_Nav_Sol = data.GetIntGpsNumOfSatelites();

	// these fields are not parsed by the other side
	msg.GPS_Week = 0;
	memset(&msg.Data_Validity_Bitfield, 0, sizeof(msg.Data_Validity_Bitfield));
	msg.GPS_UTM_Northing = 0;
	msg.GPS_UTM_Easting = 0;
	msg.GPS_Altitude = 0;
	msg.North_Velocity = 0;
	msg.East_Velocity = 0;
	msg.Down_Velocity = 0;
	memset(&msg.GPS_Status.dummy, 0, sizeof(msg.GPS_Status.dummy));
	memset(&msg.GPS_Navigation_Mode.dummy, 0, sizeof(msg.GPS_Navigation_Mode.dummy));
	memset(&msg.RESIDUAL, 0, sizeof(msg.RESIDUAL));
	memset(&msg.GPS_Error_Bits.dummy, 0, sizeof(msg.GPS_Error_Bits.dummy));
	memset(&msg.Signals_SNRs, 0, sizeof(msg.Signals_SNRs));
	msg.GPS_EHE = 0;
	msg.GPS_EVE = 0;
	msg.GPS_HDOP = 0;
	msg.GPS_VDOP = 0;
	msg.GPS_TDOP = 0;
	msg.GPS_Zone = 0;
	msg.Zone_Type =  ZONETYPE_NORMAL;
	msg.Datum = 0;
	msg.Geoid = GEOID_EGM96;
	msg.Reserved_A2DLevel = 0;
	msg.Reserved_RFImmun = 0;
	memset(&msg.Spare, 0, sizeof(msg.Spare));

	memcpy(m_buffer, &msg, sizeof(msg));
}

void InternalGPSMessage::FillHeader(/* out */ TILTAN_HEADER& header) const {
	header.Unit_Code = 0x3c;
	Utilities::StrcpyCrossPlatform((char*)header.Operation_Code, "\x82\x3c", 2);
	header.Length = sizeof(Tiltan_Internal_GPS) - sizeof(TILTAN_HEADER);
}

int InternalGPSMessage::GetMessageSize() const {
	return sizeof(Tiltan_Internal_GPS);
}

TiltanMsgType InternalGPSMessage::GetMsgType() const {
	return TILTAN_INTERNAL_GPS_MSG;
}