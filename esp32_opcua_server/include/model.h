#ifndef MODEL_H
#define MODEL_H

#include "open62541.h"
#include "sensors.h"

#ifdef __cplusplus
extern "C"
{
#endif
    UA_StatusCode
    readCurrentAccelX(UA_Server *server,
                      const UA_NodeId *sessionId, void *sessionContext,
                      const UA_NodeId *nodeId, void *nodeContext,
                      UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                      UA_DataValue *dataValue);
    UA_StatusCode
    readCurrentAccelY(UA_Server *server,
                      const UA_NodeId *sessionId, void *sessionContext,
                      const UA_NodeId *nodeId, void *nodeContext,
                      UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                      UA_DataValue *dataValue);
    UA_StatusCode
    readCurrentAccelZ(UA_Server *server,
                      const UA_NodeId *sessionId, void *sessionContext,
                      const UA_NodeId *nodeId, void *nodeContext,
                      UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                      UA_DataValue *dataValue);

    void addCurrentAccelXDataSourceVariable(UA_Server *server);
    void addCurrentAccelYDataSourceVariable(UA_Server *server);
    void addCurrentAccelZDataSourceVariable(UA_Server *server);
#ifdef __cplusplus
}
#endif

#endif /* MODEL_H */