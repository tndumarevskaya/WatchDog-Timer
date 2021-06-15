/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoWatchDog1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoWatchDog1
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

#ifndef __ID_ECOWATCHDOG1_H__
#define __ID_ECOWATCHDOG1_H__

#include "IEcoBase1.h"
#include "IEcoWatchDog1.h"

/* EcoWatchDog1 CID = {897EFA2C-9A4D-4D55-B74E-20422EE64D92} */
#ifndef __CID_EcoWatchDog1
static const UGUID CID_EcoWatchDog1 = {0x01, 0x10, 0x89, 0x7E, 0xFA, 0x2C, 0x9A, 0x4D, 0x4D, 0x55, 0xB7, 0x4E, 0x20, 0x42, 0x2E, 0xE6, 0x4D, 0x92};
#endif /* __CID_EcoWatchDog1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_897EFA2C9A4D4D55B74E20422EE64D92;
#endif

#endif /* __ID_ECOWATCHDOG1_H__ */
