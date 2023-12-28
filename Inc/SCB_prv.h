/*
 * SCB_prv.h
 *
 *  Created on: Dec 2, 2023
 *      Author: AlsharQawy
 */

#ifndef SCB_PRV_H_
#define SCB_PRV_H_

#define   VECTKEY           0x5FAU
#define   VECTKEY_ACCESS    16U
#define   VECTKEY_MASK      0xFFFFU

#define   PRIGROUP_ACCESS   8U
#define   PRIGROUP_MASK     0b111U

#define   DIV_0_TRP_BIT_ACCESS       4U
#define   UNALIGN_TRP_BIT_ACCESS     3U

#define   SCB_PRIORITY_ACCESS        4U

#define   USGFAULTENA_BIT_ACCESS        18U
#define   BUSFAULTENA_BIT_ACCESS        17U
#define   MEMFAULTENA_BIT_ACCESS        16U
#define   SYSTICKACT_BIT_ACCESS         11U


#endif /* SCB_PRV_H_ */
