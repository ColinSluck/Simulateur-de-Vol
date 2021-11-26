#include "cusb_6xxx.h"
#include "NIDAQmx.h"

CUsb_6xxx::CUsb_6xxx()
{
    m_taskHandle = nullptr;
    m_nomTache = QString::fromUtf8("Simulation");
    m_nomCarte = QString::fromUtf8("Dev6/ao0");
    m_numVoie = QString::fromUtf8("ao0");
    m_connexionCapteur = DAQmx_Val_Cfg_Default;
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
    m_error = DAQmxCreateAOVoltageChan(m_taskHandle,"Dev6/ao0","Simulation",-10.0,10.0,DAQmx_Val_Volts,"");
    m_read = 10;
    m_i = 0;

}
void CUsb_6xxx::configuration_2(QString nomTachex,QString nomCartex,QString nomVoiex)
{
    m_nomTache =nomTachex;
    m_nomCarte = nomCartex;
    m_numVoie = nomVoiex;
    m_nomCarte = m_nomCarte + "/" + m_numVoie;
    m_connexionCapteur = DAQmx_Val_Cfg_Default;
    m_taskHandle = nullptr;
    m_error = DAQmxCreateTask(m_nomTache.toStdString().c_str(),&m_taskHandle);
    m_error = DAQmxCreateAOVoltageChan(m_taskHandle,"Dev6/ao1","Simulation2",-10.0,10.0,DAQmx_Val_Volts,"");
    m_read = 10;
    m_i = 0;

}
void CUsb_6xxx::startAcquisition()
{
    DAQmxStartTask(m_taskHandle);
}
void CUsb_6xxx::setAO0(double p_tension)
{
    m_tension=p_tension;
    DAQmxWriteAnalogScalarF64(m_taskHandle,1,10,m_tension,NULL);

}
void CUsb_6xxx::setAO1(double p_tension)
{
    m_tension=p_tension;
    DAQmxWriteAnalogScalarF64(m_taskHandle,1,10,m_tension,NULL);

}
void CUsb_6xxx::stopAcquisition()
{
    DAQmxStopTask(m_taskHandle);
}
void CUsb_6xxx::clearAcquisition()
{
    DAQmxClearTask(m_taskHandle);
}

