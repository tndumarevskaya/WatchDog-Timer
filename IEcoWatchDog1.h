/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoWatchDog1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoWatchDog1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOWATCHDOG1_H__
#define __I_ECOWATCHDOG1_H__

#include "IEcoBase1.h"

/* IEcoWatchDog1 IID = {E42A4F19-797C-41CB-82EC-0263DDD2C0F4} */
#ifndef __IID_IEcoWatchDog1
static const UGUID IID_IEcoWatchDog1 = {0x01, 0x10, 0xE4, 0x2A, 0x4F, 0x19, 0x79, 0x7C, 0x41, 0xCB, 0x82, 0xEC, 0x02, 0x63, 0xDD, 0xD2, 0xC0, 0xF4};
#endif /* __IID_IEcoWatchDog1 */

typedef struct IEcoWatchDog1VTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoWatchDog1* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoWatchDog1* me);
    uint32_t (*Release)(/* in */ struct IEcoWatchDog1* me);

    /* IEcoWatchDog1 */
    int16_t (*Enable)(/* in */ struct IEcoWatchDog1* me, /* in */ uint32_t msec);
    int16_t (*set_Mode)(/* in */ struct IEcoWatchDog1* me, /* in */ uint32_t mode);
    int16_t (*Reset)(/* in */ struct IEcoWatchDog1* me);
    int16_t (*Disable)(/* in */ struct IEcoWatchDog1* me);
    int16_t (*set_Handler)(/* in */ struct IEcoWatchDog1* me, /* in */ void* funcHandler);

} IEcoWatchDog1VTbl, *IEcoWatchDog1VTblPtr;

interface IEcoWatchDog1 {
    struct IEcoWatchDog1VTbl *pVTbl;
} IEcoWatchDog1;


#endif /* __I_ECOWATCHDOG1_H__ */
