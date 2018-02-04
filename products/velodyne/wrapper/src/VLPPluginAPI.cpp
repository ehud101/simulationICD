
#include "VLPPluginAPI.h"

VLPWrapper* CreateVLPObject(const char* ip, const char* port, int resolution,
    int returnMode, int dataSource, int sensorFrequency, int velType) {
    return new VLPWrapper(ip, port, resolution, returnMode, dataSource, sensorFrequency, velType);
}

void DeleteVLPObject(VLPWrapper* pVlp) {delete pVlp;}

void RunVLP(VLPWrapper* pVlp) { pVlp->Run();}

void SetAzimuth(VLPWrapper* pVlp, double azimuth){ pVlp->SetAzimuth(azimuth); }

void SetVLPTimeStamp(VLPWrapper* pVlp, int timeStamp) { pVlp->SetTimeStamp(timeStamp); }

void SetChannel(VLPWrapper* pVlp, double distance, short reflectivity) { pVlp->SetChannel(distance, reflectivity); }

void SendVLPData(VLPWrapper* pVlp) { pVlp->SetData(); }