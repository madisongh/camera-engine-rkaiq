/*
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ___RK_AIQ_UAPITYPES_H__
#define ___RK_AIQ_UAPITYPES_H__

#include "adpcc/rk_aiq_types_adpcc_ext.h"
#include "adrc_uapi_head.h"
#include "aec_uapi_head.h"
#include "agamma_uapi_head.h"
#include "amerge_uapi_head.h"
#include "atmo_uapi_head.h"
#include "awb_uapi_head.h"
#include "rk_aiq_user_api_common.h"
#include "adrc_uapi_head.h"
#include "adpcc/rk_aiq_types_adpcc_ext.h"
#include "bayer2dnr_uapi_head_v2.h"
#include "bayertnr_uapi_head_v2.h"
#include "ynr_uapi_head_v3.h"
#include "cnr_uapi_head_v2.h"
#include "sharp_uapi_head_v4.h"
#include "gain_uapi_head_v2.h"
#include "ablc_uapi_head.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __ae_uapi {
    // M4_STRUCT_DESC("expsw_attr", "normal_ui_style")
    uapi_expsw_attr_t expsw_attr;
    // M4_STRUCT_DESC("QueryExpInfo", "normal_ui_style")
    uapi_expinfo_t expinfo;
} ae_uapi_t;

typedef struct __awb_uapi {
    // M4_STRUCT_DESC("mode", "normal_ui_style")
    uapi_wb_mode_t mode;
    // M4_STRUCT_DESC("wbgain", "normal_ui_style")
    uapi_wb_gain_t wbgain;
} awb_uapi_t;

typedef struct __amerge_uapi {
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    mMergeAttrV30_t stManual;
    // M4_STRUCT_DESC("ctldata", "normal_ui_style")
    uapiMergeCurrCtlData_t ctldata;
} amerge_uapi_t;

typedef struct __atmo_uapi {
    // M4_STRUCT_DESC("ctldata", "normal_ui_style")
    uapiTmoCurrCtlData_t ctldata;
} atmo_uapi_t;

typedef struct __adrc_uapi {
    // M4_STRUCT_DESC("stManualV30", "normal_ui_style")
    mdrcAttr_V30_t stManualV30;
    // M4_STRUCT_DESC("info", "normal_ui_style")
    DrcInfo_t info;
} adrc_uapi_t;

typedef struct __agamma_uapi {
    // M4_STRUCT_DESC("stManual", "normal_ui_style")
    Agamma_api_manualV30_t stManual;
} agamma_uapi_t;

typedef struct __aiq_scene {
    // M4_STRING_DESC("main_scene", M4_SIZE(1,1), M4_RANGE(0, 32), "normal", M4_DYNAMIC(0))
    char* main_scene;
    // M4_STRING_DESC("sub_scene", M4_SIZE(1,1), M4_RANGE(0, 32), "day", M4_DYNAMIC(0))
    char* sub_scene;
} aiq_scene_t;

typedef struct __work_mode {
    // M4_ENUM_DESC("mode", "rk_aiq_working_mode_t", "RK_AIQ_WORKING_MODE_NORMAL");
    rk_aiq_working_mode_t mode;
} work_mode_t;

typedef struct __aiq_sysctl_desc {
    // M4_STRUCT_DESC("scene", "normal_ui_style")
    aiq_scene_t scene;
    // M4_STRUCT_DESC("work_mode", "normal_ui_style")
    work_mode_t work_mode;
} RkaiqSysCtl_t;

typedef struct __aiq_measure_info {
    // M4_STRUCT_DESC("ae_hwstats", "normal_ui_style")
    uapi_ae_hwstats_t ae_hwstats;
    // M4_STRUCT_DESC("wb_log", "normal_ui_style")
    uapi_wb_log_t wb_log;
} aiq_measure_info_t;

typedef struct __ablc_uapi_v30 {
    // M4_STRUCT_DESC("bls0", "normal_ui_style")
    AblcSelect_t bls0;
    // M4_STRUCT_DESC("bls1", "normal_ui_style")
    AblcSelect_t bls1;
} ablc_uapi_v30_t;

typedef struct __abayer2dnr_uapi_v30 {
    // M4_STRUCT_DESC("manual", "normal_ui_style")
    RK_Bayer2dnr_Params_V2_Select_t manual;
} abayer2dnr_uapi_v30_t;

typedef struct __abayertnr_uapi_v30 {
    // M4_STRUCT_DESC("manual", "normal_ui_style")
    RK_Bayertnr_Params_V2_Select_t manual;
} abayertnr_uapi_v30_t;

typedef struct __aynr_uapi_v30 {
    // M4_STRUCT_DESC("manual", "normal_ui_style")
    RK_YNR_Params_V3_Select_t manual;
} aynr_uapi_v30_t;

typedef struct __acnr_uapi_v30 {
    // M4_STRUCT_DESC("manual", "normal_ui_style")
    RK_CNR_Params_V2_Select_t manual;
} acnr_uapi_v30_t;

typedef struct __asharp_uapi_v30 {
    // M4_STRUCT_DESC("manual", "normal_ui_style")
    RK_SHARP_Params_V4_Select_t manual;
} asharp_uapi_v30_t;

typedef struct __again_uapi_v30 {
    // M4_STRUCT_DESC("manual", "normal_ui_style")
    RK_GAIN_Select_V2_t manual;
} again_uapi_v30_t;



typedef struct __aiq_uapi_t {
    // M4_STRUCT_DESC("ae_uapi", "normal_ui_style")
    ae_uapi_t ae_uapi;
    // M4_STRUCT_DESC("awb_uapi", "normal_ui_style")
    awb_uapi_t awb_uapi;
    // M4_STRUCT_DESC("amerge_uapi", "normal_ui_style")
    amerge_uapi_t amerge_uapi;
#if defined(ISP_HW_V20)
    // M4_STRUCT_DESC("atmo_uapi", "normal_ui_style")
    atmo_uapi_t atmo_uapi;
#else
    // M4_STRUCT_DESC("adrc_uapi", "normal_ui_style")
    adrc_uapi_t adrc_uapi;
#endif
    // M4_STRUCT_DESC("agamma_uapi", "normal_ui_style")
    agamma_uapi_t agamma_uapi;
    // M4_STRUCT_DESC("SystemCtl", "normal_ui_style")
    RkaiqSysCtl_t system;
    // M4_STRUCT_DESC("measure_info", "normal_ui_style")
    aiq_measure_info_t measure_info;
    // M4_STRUCT_DESC("adpcc_manual", "normal_ui_style")
    Adpcc_Manual_Attr_t adpcc_manual;
#if defined(ISP_HW_V30)
    // M4_STRUCT_DESC("ablc_v30_uapi", "normal_ui_style")
    ablc_uapi_v30_t ablc_v30_uapi;
    // M4_STRUCT_DESC("abayer2dnr_v2_uapi", "normal_ui_style")
    abayer2dnr_uapi_v30_t abayer2dnr_v2_uapi;
    // M4_STRUCT_DESC("abayertnr_v2_uapi", "normal_ui_style")
    abayertnr_uapi_v30_t abayertnr_v2_uapi;
    // M4_STRUCT_DESC("aynr_v3_uapi", "normal_ui_style")
    aynr_uapi_v30_t aynr_v3_uapi;
    // M4_STRUCT_DESC("acnr_v2_uapi", "normal_ui_style")
    acnr_uapi_v30_t acnr_v2_uapi;
    // M4_STRUCT_DESC("asharp_v4_uapi", "normal_ui_style")
    asharp_uapi_v30_t asharp_v4_uapi;
    // M4_STRUCT_DESC("again_v2_uapi", "normal_ui_style")
    again_uapi_v30_t again_v2_uapi;
#endif
} RkaiqUapi_t;

#ifdef __cplusplus
}
#endif

#endif  /*___RK_AIQ_UAPITYPES_H__*/
