#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "model.h"
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <string.h>

// read node
UA_StatusCode readCurrentAccelX(UA_Server *server,
                                  const UA_NodeId *sessionId, void *sessionContext,
                                  const UA_NodeId *nodeId, void *nodeContext,
                                  UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                                  UA_DataValue *dataValue)
{
    // if a node does not send data, a corruption error will occur
    UA_Float accelXValue = sensorReadingAccelX(); //call to get data
    UA_Variant_setScalarCopy(&dataValue->value, &accelXValue, &UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

// node setup and call the read node
void addCurrentAccelXDataSourceVariable(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "AccelX");
    attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "accelX");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Accel value for X");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentAccelX; // read data
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        timeDataSource, NULL, NULL);
}

/* Pressure */
UA_StatusCode readCurrentAccelY(UA_Server *server,
                                  const UA_NodeId *sessionId, void *sessionContext,
                                  const UA_NodeId *nodeId, void *nodeContext,
                                  UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                                  UA_DataValue *dataValue)
{
    // if a node does not send data, a corruption error will occur
    UA_Float accelYValue = sensorReadingAccelY();
    UA_Variant_setScalarCopy(&dataValue->value, &accelYValue, &UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

void addCurrentAccelYDataSourceVariable(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "AccelY");
    attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "accelY");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Accel value for Y");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentAccelY; // read data
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        timeDataSource, NULL, NULL);
}

/* Pressure */
UA_StatusCode readCurrentAccelZ(UA_Server *server,
                                  const UA_NodeId *sessionId, void *sessionContext,
                                  const UA_NodeId *nodeId, void *nodeContext,
                                  UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                                  UA_DataValue *dataValue)
{
    // if a node does not send data, a corruption error will occur
    UA_Float accelZValue = sensorReadingAccelZ();
    UA_Variant_setScalarCopy(&dataValue->value, &accelZValue, &UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD; 
}

void addCurrentAccelZDataSourceVariable(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "AccelZ");
    attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "accelZ");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Accel value for Z");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentAccelZ; // read data
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        timeDataSource, NULL, NULL);
}
