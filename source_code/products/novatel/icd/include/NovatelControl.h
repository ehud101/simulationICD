#ifndef NOVATEL_CONTROL
#define NOVATEL_CONTROL

/*
* NovatelControl.h
* Manage communication between DGPS sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include "IICD.h"
#include "NovatelData.h"

template <class T>
class Message;
class NovatelConfig;
class ICommunication;

class NovatelControl : public IICD<NovatelData> {
private:
    // connection protocol to use 
    ICommunication* m_comm = nullptr;
    // configuration parser
    NovatelConfig* m_novatelConf = nullptr;

    Message<NovatelData>* GetMsgByType(NovatelMsgType msgType) const;
   
protected: 
    virtual void InitCommunication() override;

public:
    NovatelControl(const std::string& confFilePath);

    virtual ~NovatelControl();

    /**
     * Set data on Dgps
     * @param data - NovatelData object
     */ 
    virtual void SendData(const NovatelData& data) override;

    /**
     * This function is implemented with empty return
     */ 
    virtual NovatelData ReceiveData() override;
};

#endif // NOVATEL_CONTROL