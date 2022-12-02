/***************************************************************************//**
* \file cybsp_dsram.c
*
* Description:
* Provides initialization code for handling deepsleep ram.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
#include <stdlib.h>
#include "cy_syspm.h"
#include "cy_sysclk.h"
#include "cybsp.h"
#if defined(CY_USING_HAL)
#include "cyhal_hwmgr.h"
#include "cyhal_syspm.h"
#endif
#include "cybsp_smif_init.h"
#if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
#include "cyabs_rtos_dsram.h"
#endif
#include "system_cat1b.h"
#include "cybsp_dsram.h"

#if defined(__cplusplus)
extern "C" {
#endif



//--------------------------------------------------------------------------------------------------
// cybsp_syspm_do_warmboot
//--------------------------------------------------------------------------------------------------
__WEAK void cybsp_syspm_do_warmboot(void)
{
    #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
    cyabs_rtos_exit_dsram();
    #endif
}


CY_SECTION_RAMFUNC_BEGIN
//--------------------------------------------------------------------------------------------------
// cybsp_warmboot_handler
//--------------------------------------------------------------------------------------------------
void cybsp_warmboot_handler(void)
{
    SystemInit_Warmboot_CAT1B_CM33();

    #if FLASH_BOOT
    cybsp_smif_init();
    #endif

    init_cycfg_all();

    cybsp_syspm_do_warmboot();
}


CY_SECTION_RAMFUNC_END

/* Currently only GCC_ARM compiler is supported for DS-RAM Warmboot Re-entry*/
#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
extern unsigned int __StackTop;
cy_stc_syspm_warmboot_entrypoint_t syspmBspDeepSleepEntryPoint =
    { (uint32_t*)(&__StackTop), (uint32_t*)cybsp_warmboot_handler };
#endif

//--------------------------------------------------------------------------------------------------
// cybsp_deepsleep_ram_callback
//--------------------------------------------------------------------------------------------------
cy_en_syspm_status_t cybsp_deepsleep_ram_callback(cy_stc_syspm_callback_params_t* callbackParams,
                                                  cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_FAIL;

    CY_UNUSED_PARAMETER(callbackParams);

    switch (mode)
    {
        case CY_SYSPM_CHECK_READY:
        case CY_SYSPM_CHECK_FAIL:
        case CY_SYSPM_BEFORE_TRANSITION:
        {
            retVal = CY_SYSPM_SUCCESS;
            break;
        }

        case CY_SYSPM_AFTER_TRANSITION:
        {
            /* Currently only GCC_ARM compiler is supported for DS-RAM Warmboot Re-entry*/
            #if defined(__GNUC__) && !defined(__ARMCC_VERSION)
            Cy_Syslib_SetWarmBootEntryPoint((uint32_t*)&syspmBspDeepSleepEntryPoint, true);
            #endif

            retVal = CY_SYSPM_SUCCESS;
            break;
        }

        default:
            break;
    }

    return retVal;
}


//--------------------------------------------------------------------------------------------------
// cybsp_register_syspm_dsram_callback
//--------------------------------------------------------------------------------------------------
cy_rslt_t cybsp_register_syspm_dsram_callback(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    static cy_stc_syspm_callback_params_t cybsp_sysclk_pm_callback_param = { NULL, NULL };
    static cy_stc_syspm_callback_t        cybsp_sysclk_pm_callback       =
    {
        .callback       = &cybsp_deepsleep_ram_callback,
        .type           = CY_SYSPM_DEEPSLEEP_RAM,
        .callbackParams = &cybsp_sysclk_pm_callback_param,
        .order          = 0u
    };

    if (!Cy_SysPm_RegisterCallback(&cybsp_sysclk_pm_callback))
    {
        result = CYBSP_RSLT_ERR_SYSCLK_PM_CALLBACK;
    }
    return result;
}


//--------------------------------------------------------------------------------------------------
// cybsp_syspm_dsram_init
//--------------------------------------------------------------------------------------------------
cy_rslt_t cybsp_syspm_dsram_init(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    result = cybsp_register_syspm_dsram_callback();
    /* Currently only GCC_ARM compiler is supported for DS-RAM Warmboot Re-entry*/
    #if defined(__GNUC__) && !defined(__ARMCC_VERSION)
    Cy_Syslib_SetWarmBootEntryPoint((uint32_t*)&syspmBspDeepSleepEntryPoint, true);
    #endif

    return result;
}


#if defined(__cplusplus)
}
#endif
