/*
 * Test_Function.cpp
 *
 *  Created on: 2020/03/08
 *      Author:
 */

#include "Test_Function.h"
#include "FailSafeFunc.h"
#include "StubAPIFunc.h"

#define DEBUG_AD_VMC

void TestFunc_CANFailInfo()
{
#ifdef DEBUG_AD_TC
	/* AD_TC */
	/* Fail Judgment */
	for(int i=0; i < 1; i++)
	{
		g_GetCANRecv = 0;
		f_CANFailInfo_set(AD_TC);
	}
	for(int i=0; i < 3; i++)
	{
		g_GetCANRecv = 1;
		f_CANFailInfo_set(AD_TC);
	}

	/* Fail Fall */
	for(int i=0; i < 1; i++)
	{
		g_GetCANRecv = 0;
		f_CANFailInfo_set(AD_TC);
	}
#endif

#ifdef DEBUG_AD_VMC
	/* AD_VMC */
	/* CoverageCase2 */
	for(int i=0; i < 1; i++)
	{
		g_GetCANRecv = 0;
		f_CANFailInfo_set(AD_VMC);
	}

	/* CoverageCase1 */
	for(int i=0; i < 3; i++)
	{
		g_GetCANRecv = 1;
		f_CANFailInfo_set(AD_VMC);
	}

	/* CoverageCase3 */
	for(int i=0; i < 1; i++)
	{
		g_GetCANRecv = 0;
		f_CANFailInfo_set(AD_VMC);
	}

	/* ParamCase1 / ParamCase1 */
	for(int i=0; i < 1; i++)
	{
		g_GetCANRecv = 0;
		f_CANFailInfo_set(AD_VMC);
	}
	for(int i=0; i < 1; i++)
	{
		g_GetCANRecv = 1;
		f_CANFailInfo_set(AD_VMC);
	}

#endif

}

void TestFunc_CANRecv()
{
	f_CANFailInfo_set(AD_VMC);
}
