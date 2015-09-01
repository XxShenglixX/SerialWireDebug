#ifndef ProgramWorker_H
#define ProgramWorker_H

#include "Tlv.h"
#include "CoreDebug.h"
#include "swdStub.h"

/* swdStub instruction */
void loadEraseSectorInstruction(uint32_t *startSector, uint32_t *endSector);
void loadMassEraseInstruction(uint32_t bankSelect);
void loadCopyFromSRAMToFlashInstruction(uint32_t *dataAddress, uint32_t *destAddress, int size);

Tlv_Session *tlvCreateWorkerSession(void);

void writeTargetRegister(Tlv_Session *session, uint32_t *registerAddress, uint32_t *data);
void readTargetRegister(Tlv_Session *session, uint32_t *registerAddress);

void performSoftResetOnTarget(Tlv_Session *session);
void performHardResetOnTarget(Tlv_Session *session);

void selectInstruction(Tlv_Session *session, Tlv *tlv);
void programWorker(Tlv_Session *session);

#endif // ProgramWorker_H
