#ifndef __PARAMETERS_READER_H__
#define __PARAMETERS_READER_H__

#include "SystemComponent.h"
#include "Output.h"

class ParametersReader : public SystemComponent
{
public:
    ParametersReader();
    virtual ~ParametersReader();
    
    void start();
    void stop();
    void tick();

    int getTargetHumidity();
    void setOutput(Output *output);

private:
    int lastReadTargetHumidity = 0;
    Output *output;
};

#endif