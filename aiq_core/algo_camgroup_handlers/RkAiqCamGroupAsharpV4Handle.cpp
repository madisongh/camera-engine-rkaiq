/*
 * Copyright (c) 2019-2021 Rockchip Eletronics Co., Ltd.
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
 */

#include "RkAiqCamGroupHandleInt.h"
#include "asharp4/rk_aiq_uapi_camgroup_asharp_int_v4.h"

namespace RkCam {

XCamReturn RkAiqCamGroupAsharpV4HandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        LOGD_ASHARP("%s:%d\n", __FUNCTION__, __LINE__);
        mCurAtt   = mNewAtt;
        rk_aiq_uapi_camgroup_asharpV4_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal(mCurAtt.sync.sync_mode);
        updateAtt = false;
    }

    if (updateStrength) {
        LOGD_ASHARP("%s:%d\n", __FUNCTION__, __LINE__);
        mCurStrength = mNewStrength;
        rk_aiq_uapi_camgroup_asharpV4_SetStrength(mAlgoCtx, mCurStrength.percent);
        sendSignal(mCurStrength.sync.sync_mode);
        updateStrength = false;
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqCamGroupAsharpV4HandleInt::setAttrib(rk_aiq_sharp_attrib_v4_t* att) {
    ENTER_ANALYZER_FUNCTION();
    LOGD_ASHARP("%s:%d\n", __FUNCTION__, __LINE__);

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();

    // check if there is different between att & mCurAtt(sync)/mNewAtt(async)
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore
    bool isChanged = false;
    if (att->sync.sync_mode == RK_AIQ_UAPI_MODE_ASYNC && \
        memcmp(&mNewAtt, att, sizeof(*att)))
        isChanged = true;
    else if (att->sync.sync_mode != RK_AIQ_UAPI_MODE_ASYNC && \
             memcmp(&mCurAtt, att, sizeof(*att)))
        isChanged = true;

    // if something changed
    if (isChanged) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal(att->sync.sync_mode);
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqCamGroupAsharpV4HandleInt::getAttrib(rk_aiq_sharp_attrib_v4_t* att) {
    ENTER_ANALYZER_FUNCTION();
    LOGD_ASHARP("%s:%d\n", __FUNCTION__, __LINE__);

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if(att->sync.sync_mode == RK_AIQ_UAPI_MODE_SYNC) {
        mCfgMutex.lock();
        rk_aiq_uapi_camgroup_asharpV4_GetAttrib(mAlgoCtx, att);
        att->sync.done = true;
        mCfgMutex.unlock();
    } else {
        if(updateAtt) {
            memcpy(att, &mNewAtt, sizeof(mNewAtt));
            att->sync.done = false;
        } else {
            rk_aiq_uapi_camgroup_asharpV4_GetAttrib(mAlgoCtx, att);
            att->sync.done = true;
        }
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

#if 1

XCamReturn RkAiqCamGroupAsharpV4HandleInt::setStrength(rk_aiq_sharp_strength_v4_t *pStrength) {
    ENTER_ANALYZER_FUNCTION();
    LOGD_ASHARP("%s:%d\n", __FUNCTION__, __LINE__);

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mCfgMutex.lock();

    bool isChanged = false;
    if (pStrength->sync.sync_mode == RK_AIQ_UAPI_MODE_ASYNC && \
        memcmp(&mNewStrength, pStrength, sizeof(*pStrength)))
        isChanged = true;
    else if (pStrength->sync.sync_mode != RK_AIQ_UAPI_MODE_ASYNC && \
             memcmp(&mCurStrength, pStrength, sizeof(*pStrength)))
        isChanged = true;

    if (isChanged) {
        mNewStrength   = *pStrength;
        updateStrength = true;
        waitSignal(pStrength->sync.sync_mode);
    }

    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqCamGroupAsharpV4HandleInt::getStrength(rk_aiq_sharp_strength_v4_t *pStrength) {
    ENTER_ANALYZER_FUNCTION();
    LOGD_ASHARP("%s:%d\n", __FUNCTION__, __LINE__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if(pStrength->sync.sync_mode == RK_AIQ_UAPI_MODE_SYNC) {
        mCfgMutex.lock();
        rk_aiq_uapi_camgroup_asharpV4_GetStrength(mAlgoCtx, &pStrength->percent );
        pStrength->sync.done = true;
        mCfgMutex.unlock();
    } else {
        if(updateStrength) {
            pStrength->percent = mNewStrength.percent;
            pStrength->sync.done = false;
        } else {
            rk_aiq_uapi_camgroup_asharpV4_GetStrength(mAlgoCtx, &pStrength->percent);
            pStrength->sync.done = true;
        }
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
#endif


};  // namespace RkCam
