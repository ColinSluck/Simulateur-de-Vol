#include "cusb_6xxx.h"
#include "NIDAQmx.h"
#include <QElapsedTimer>

CUsb_6xxx::CUsb_6xxx()
{
    m_taskHandle = nullptr;
    m_taskHandle2 = nullptr;
    m_nomTache = QString::fromUtf8("Simulation");
    m_nomCarte = QString::fromUtf8("Dev6/ao0");
    m_numVoie = QString::fromUtf8("ao0");
    m_tension = 0;
}
CUsb_6xxx::~CUsb_6xxx()
{
}
void CUsb_6xxx::configuration(QString nomTachex,QString nomCartex,QString nomVoiex)
{
    m_nomTache =nomTachex;
    m_nomCarte = nomCartex;
    m_numVoie = nomVoiex;
    m_nomCarte = m_nomCarte + "/" + m_numVoie;
    m_tension = 0;
    m_taskHandle = nullptr;
    m_error = DAQmxCreateTask(m_nomTache.toStdString().c_str(),&m_taskHandle);
    printError(m_error);
    m_error = DAQmxCreateAOVoltageChan(m_taskHandle,"Dev6/ao0","Simulation",-9,9,DAQmx_Val_Volts,"");
    printError(m_error);

}
void CUsb_6xxx::configuration_2(QString nomTachex,QString nomCartex,QString nomVoiex)
{
    m_nomTache =nomTachex;
    m_nomCarte = nomCartex;
    m_numVoie = nomVoiex;
    m_nomCarte = m_nomCarte + "/" + m_numVoie;
    m_taskHandle2 = nullptr;
    m_error = DAQmxCreateTask(m_nomTache.toStdString().c_str(),&m_taskHandle2);
    printError(m_error);
    m_error = DAQmxCreateAOVoltageChan(m_taskHandle2,"Dev6/ao1","Simulation2",-9.0,9,DAQmx_Val_Volts,"");
    printError(m_error);

}
void CUsb_6xxx::startAcquisition()
{
    DAQmxStartTask(m_taskHandle);
}
void CUsb_6xxx::setAO0(double p_tension)
{
     m_error = DAQmxWriteAnalogScalarF64(m_taskHandle,1,10,p_tension,NULL);
     printError(m_error);
}
void CUsb_6xxx::setAO1(double p_tension)
{
    m_error = DAQmxWriteAnalogScalarF64(m_taskHandle2,1,10,p_tension,NULL);
    printError(m_error);

}
void CUsb_6xxx::stopAcquisition()
{
    DAQmxStopTask(m_taskHandle);
}
void CUsb_6xxx::clearAcquisition()
{
    DAQmxClearTask(m_taskHandle);
}

void CUsb_6xxx::printError(int32 p_error)
{
    if(p_error != 0)
    {
        printf("CUsb_6xxx Error : %ld\n",p_error);
    }
}
