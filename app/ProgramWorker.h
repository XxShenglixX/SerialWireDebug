#ifndef ProgramWorker_H
#define ProgramWorker_H

#include "Tlv.h"
#include "CoreDebug.h"
#include "swdStub.h"
#include "Tlv_ErrorCode.h"
#include "CException.h"

/* swdStub instruction */
void loadEraseSectorInstruction(uint32_t *startSector, uint32_t *endSector);
void loadMassEraseInstruction(uint32_t bankSelect);
void loadCopyFromSRAMToFlashInstruction(uint32_t *dataAddress, uint32_t *destAddress, int size);

void writeTargetRegister(Tlv_Session *session, uint32_t *registerAddress, uint32_t *data);
void readTargetRegister(Tlv_Session *session, uint32_t *registerAddress);

void performSoftResetOnTarget(Tlv_Session *session);
void performHardResetOnTarget(Tlv_Session *session);

void selectTask(Tlv_Session *session, Tlv *tlv);
void probeTaskManager(Tlv_Session *session);

void haltTarget(Tlv_Session *session);
void runTarget(Tlv_Session *session);

void singleStepTarget(Tlv_Session *session);
void multipleStepTarget(Tlv_Session *session, int nInstructions);

void setBreakpoint(uint32_t instructionAddress,int matchingMode);
#endif // ProgramWorker_H