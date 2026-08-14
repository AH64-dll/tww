/**
 * d_a_obj_YLzou.cpp
 * Object - Hyrule Castle - Link statue (moving stairs)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_YLzou.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_particle.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "JAZelAudio/JAZelAudio_SE.h"
#include "SSystem/SComponent/c_math.h"
#include "d/d_vibration.h"

namespace {
const char l_arcname[] = "YLzou";
const char l_move_ylzou_demo_name[] = "move_YLzou";
const char l_go_up_stairs_demo_name[] = "go_up_stairs";
const char l_go_up_stairs_demo2_name[] = "go_up_stairs2";
const char* l_demo_name[] = {
    NULL,
    l_move_ylzou_demo_name,
    l_go_up_stairs_demo_name,
    l_go_up_stairs_demo2_name,
};

int bdl_table[] = { 4, 5 };
int dzb_table[] = { 8, 9 };
u32 solidHeapSize_table[] = { 0x5840, 0x49E0 };
int next_act_idx[] = { -1, 6, 11, 12 };
}  // namespace

/* 000000EC-000002B8       .text set_start_type__12daObjYLzou_cFv */
void daObjYLzou_c::set_start_type() {
    s32 type = 0;
    s32 mType = 0;
    s32 demoIdx = 0;
    bool onBit = false;

    if (!dComIfGs_isEventBit(0x2D04)) {
        if (mParam != 0xFF && !dComIfGs_isSwitch(mParam, fopAcM_GetHomeRoomNo(this))) {
            type = 0;
            demoIdx = 1;
        } else {
            type = 6;
            onBit = true;
        }
    } else if (!dComIfGs_isEventBit(0x3A04)) {
        type = 6;
        onBit = true;
    } else if (!dComIfGs_isEventBit(0x3804)) {
        if (dComIfGs_isEventBit(0x3820) == 1) {
            type = 7;
            demoIdx = 2;
        } else {
            type = 11;
        }
    } else if (!dComIfGs_isEventBit(0x2D02)) {
        type = 6;
        onBit = true;
    } else if (dComIfGs_getTriforceNum() < 8) {
        if (dComIfGs_isEventBit(0x3820) == 1) {
            type = 7;
            demoIdx = 2;
        } else {
            type = 11;
        }
    } else {
        mType = 1;
        if (!dComIfGs_isEventBit(0x2C01)) {
            type = 12;
        } else if (!dComIfGs_isEventBit(0x3980)) {
            type = 13;
            demoIdx = 3;
        } else {
            type = 12;
        }
    }

    mAction = type;
    this->mType = mType;
    mDemoIdx = demoIdx;
    if (!onBit) {
        dComIfGs_offEventBit(0x3820);
    } else {
        dComIfGs_onEventBit(0x3820);
    }
}

/* 000002B8-00000374       .text set_mtx__12daObjYLzou_cFv */
void daObjYLzou_c::set_mtx() {
    f32 sinA = cM_ssin(mAngle);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + mVibStrength * sinA, current.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
    cMtx_copy(mDoMtx_stack_c::get(), mBaseMtx);
}

/* 00000374-000003B0       .text init_mtx__12daObjYLzou_cFv */
void daObjYLzou_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 000003B0-000003D4       .text solidHeapCB__12daObjYLzou_cFP10fopAc_ac_c */
BOOL daObjYLzou_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjYLzou_c*)i_this)->create_heap();
}

/* 000003D4-000004F4       .text create_heap__12daObjYLzou_cFv */
bool daObjYLzou_c::create_heap() {
    bool ret = true;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, bdl_table[mType]);
    if (modelData == NULL) {
        JUT_ASSERT(0x198, 0);
        ret = false;
    } else {
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        Mtx* pBaseMtx = &mpModel->getBaseTRMtx();
        cBgD_t* pDzb = (cBgD_t*)dComIfG_getObjectRes(l_arcname, dzb_table[mType]);
        mpBgW = dBgW_NewSet(pDzb, 1, pBaseMtx);
        if (mpModel == NULL || mpBgW == NULL) {
            ret = false;
        }
    }
    return ret;
}

/* 000004F4-00000668       .text eff_set_slip_smoke_pos__12daObjYLzou_cFv */
void daObjYLzou_c::eff_set_slip_smoke_pos() {
    static cXyz base_pos[ARRAY_SIZE(mSmokeCbs)] = {
        cXyz(-240.0f, 0.0f, -240.0f),
        cXyz(240.0f, 0.0f, -240.0f)
    };

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + -1550.0f, current.pos.z + -1200.0f);
    mDoMtx_stack_c::YrotM(current.angle.y);
    for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); i++) {
        mDoMtx_stack_c::push();
        mDoMtx_stack_c::transM(base_pos[i]);
        mDoMtx_stack_c::multVecZero(&mSmokeCbs[i].mPos);
        mSmokeCbs[i].mAngle.set(0, current.angle.y, 0);
        mDoMtx_stack_c::pop();
    }
}

/* 000006A4-000007AC       .text eff_smoke_slip_start__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_start() {
    static cXyz scl(2.0f, 2.0f, 2.0f);

    eff_set_slip_smoke_pos();
    for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); i++) {
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(
            dPa_name::ID_AK_JT_ELEMENTSMOKE00, &mSmokeCbs[i].mPos, &mSmokeCbs[i].mAngle, &scl,
            0xB9, &mSmokeCbs[i], fopAcM_GetRoomNo(this)
        );
        if (emitter) {
            emitter->setRate(2.0f);
            emitter->setDirectionalSpeed(15.0f);
            emitter->setSpread(0.15f);
            emitter->setLifeTime(30);
        }
    }
}

/* 000007AC-0000080C       .text eff_smoke_slip_end__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_end() {
    for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); i++) {
        mSmokeCbs[i].remove();
    }
}

/* 0000080C-0000086C       .text eff_smoke_slip_remove__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_remove() {
    for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); i++) {
        mSmokeCbs[i].remove();
    }
}

/* 0000086C-000008D0       .text eff_smoke_proc__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_proc() {
    if (mSmokeState != mSmokeNext) {
        if (mSmokeNext == 1) {
            eff_smoke_slip_start();
        } else {
            eff_smoke_slip_end();
        }
        mSmokeState = mSmokeNext;
    } else if (mSmokeState == 1) {
        eff_set_slip_smoke_pos();
    }
}

/* 000008D0-000009A4       .text vib_proc__12daObjYLzou_cFv */
void daObjYLzou_c::vib_proc() {
    if (mVibState != mVibNext) {
        mVibState = mVibNext;
    }

    switch (mVibState) {
    case 1:
        mAngle += 0x4000;
        mVibStrength += 0.05f;
        if (mVibStrength > 0.8f) {
            mVibStrength = 0.8f;
        }
        break;
    case 2:
        mAngle += 0x4000;
        mVibStrength -= 0.05f;
        if (mVibStrength < 0.4f) {
            mVibStrength = 0.4f;
        }
        break;
    default:
        mAngle += 0x4000;
        mVibStrength -= 0.1f;
        if (mVibStrength < 0.0f) {
            mVibStrength = 0.0f;
        }
        break;
    }
}

/* 000009A4-00000AE0       .text _create__12daObjYLzou_cFv */
cPhs_State daObjYLzou_c::_create() {
    fopAcM_SetupActor(this, daObjYLzou_c);

    if (fopAcM_IsFirstCreating(this)) {
        mParam = param_get_swSave();
        set_start_type();
    }

    cPhs_State phs = (cPhs_State)dComIfG_resLoad(&mPhs, l_arcname);
    if (phs == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, (heapCallbackFunc)solidHeapCB, solidHeapSize_table[mType])) {
            if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
                phs = cPhs_ERROR_e;
            } else {
                fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
                setup_action(mAction);
                init_mtx();
            }
        } else {
            phs = cPhs_ERROR_e;
        }
    }
    return phs;
}

/* 00000AE0-00000B7C       .text _delete__12daObjYLzou_cFv */
bool daObjYLzou_c::_delete() {
    dComIfG_resDelete(&mPhs, l_arcname);
    eff_smoke_slip_remove();
    if (heap != NULL && mpBgW != NULL) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }
        mpBgW = NULL;
    }
    return true;
}

/* 00000B7C-00000BD8       .text move_ylzou_demo_start_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_start_wait_act_proc() {
    if (mParam != 0xFF && fopAcM_isSwitch(this, mParam) == 1) {
        setup_action(1);
    }
}

/* 00000BD8-00000C70       .text demo_regist_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_regist_wait_act_proc() {
    if (mEventId != -1) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            setup_action(mAction + 1);
        } else {
            fopAcM_orderOtherEventId(this, mEventId);
        }
    } else {
        mEventId = dComIfGp_evmng_getEventIdx(l_demo_name[mDemoIdx], 0xFF);
    }
}

/* 00000C70-00000D18       .text demo_vib_start_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_vib_start_wait_act_proc() {
    if (dComIfGp_evmng_existence(mEventId)) {
        int staffId = dComIfGp_evmng_getMyStaffId("YLzou");
        if (staffId != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffId), "Vibrate") == 0) {
                setup_action(mAction + 1);
            }
        }
    }
}

/* 00000D18-00000E08       .text demo_vib_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_vib_act_proc() {
    if (dComIfGp_evmng_existence(mEventId)) {
        int staffId = dComIfGp_evmng_getMyStaffId("YLzou");
        if (staffId != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffId), "Move") == 0) {
                setup_action(mAction + 1);
            }
        }
    }
    JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_H_STATUE_VIB, &current.pos, 0,
                                    dComIfGp_getReverb(fopAcM_GetRoomNo(this)), 1.0f, 1.0f, -1.0f,
                                    -1.0f, 0);
}

/* 00000E08-00000F0C       .text move_ylzou_demo_move_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_move_act_proc() {
    if (current.pos.z < home.pos.z + -680.0f) {
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_H_STATUE_STOP, &current.pos, 0,
                                        dComIfGp_getReverb(fopAcM_GetRoomNo(this)), 1.0f, 1.0f,
                                        -1.0f, -1.0f, 0);
        setup_action(5);
    } else {
        speedF += 0.1f;
        if (speedF > 6.0f) {
            speedF = 6.0f;
        }
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_H_STATUE_MOVE, &current.pos, 0,
                                        dComIfGp_getReverb(fopAcM_GetRoomNo(this)), 1.0f, 1.0f,
                                        -1.0f, -1.0f, 0);
    }
}

/* 00000F0C-00001008       .text go_up_stairs_demo_move_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_act_proc() {
    if (current.pos.z > home.pos.z) {
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_H_STATUE_STOP, &current.pos, 0,
                                        dComIfGp_getReverb(fopAcM_GetRoomNo(this)), 1.0f, 1.0f,
                                        -1.0f, -1.0f, 0);
        setup_action(0xA);
    } else {
        speedF += 0.1f;
        if (speedF > 6.0f) {
            speedF = 6.0f;
        }
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_H_STATUE_MOVE, &current.pos, 0,
                                        dComIfGp_getReverb(fopAcM_GetRoomNo(this)), 1.0f, 1.0f,
                                        -1.0f, -1.0f, 0);
    }
}

/* 00001008-000010A8       .text demo_end_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_end_wait_act_proc() {
    if (dComIfGp_evmng_endCheck(mEventId)) {
        dComIfGp_event_reset();
        if (mAction == 0xE) {
            dComIfGs_onEventBit(0x3980);
        }
        fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
        setup_action(next_act_idx[mDemoIdx]);
    }
}

/* 000010A8-000010AC       .text wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::wait_act_proc() {}

/* 000010AC-000010D8       .text move_ylzou_demo_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_start_wait_act_init_proc() {
    mEventId = -1;
    home.pos.set(0.0f, 0.0f, 0.0f);
    current.pos.set(0.0f, 0.0f, 0.0f);
}

/* 000010D8-00001174       .text demo_regist_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_regist_wait_act_init_proc() {
    if (mDemoIdx != 1) {
        dComIfGp_evmng_cancelStartDemo();
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
    }
    mEventId = dComIfGp_evmng_getEventIdx(l_demo_name[mDemoIdx], 0xFF);
    fopAcM_orderOtherEventId(this, mEventId);
}

/* 00001174-000011A4       .text move_ylzou_demo_vib_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_vib_start_wait_act_init_proc() {
    dComIfGs_onEventBit(0x3820);
}

/* 000011A4-0000120C       .text move_ylzou_demo_vib_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_vib_act_init_proc() {
    dComIfGp_getVibration().StartQuake(6, 1, cXyz(0.0f, 1.0f, 0.0f));
    mVibNext = 1;
}

/* 0000120C-00001228       .text move_ylzou_demo_move_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_move_act_init_proc() {
    mSmokeNext = 1;
    mVibNext = 2;
    current.angle.y = -0x8000;
}

/* 00001228-000012C8       .text demo_end_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_end_wait_act_init_proc() {
    speedF = 0.0f;
    mSmokeNext = 0;
    if (mDemoIdx != 3) {
        dComIfGp_getVibration().StopQuake(-1);
        dComIfGp_getVibration().StartShock(8, 1, cXyz(0.0f, 1.0f, 0.0f));
    }
    mVibNext = 0;
}

/* 000012C8-000012F4       .text open_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::open_wait_act_init_proc() {
    home.pos.set(0.0f, 0.0f, -680.0f);
    current.pos.set(0.0f, 0.0f, -680.0f);
}

/* 000012F4-00001318       .text close_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::close_wait_act_init_proc() {
    home.pos.set(0.0f, 0.0f, 0.0f);
    current.pos.set(0.0f, 0.0f, 0.0f);
}

/* 00001318-000013A4       .text go_up_stairs_demo_move_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_start_wait_act_init_proc() {
    current.angle.y = 0;
    home.pos.set(0.0f, 0.0f, 0.0f);
    current.pos.set(0.0f, 0.0f, -680.0f);
    dComIfGp_getVibration().StartQuake(6, 1, cXyz(0.0f, 1.0f, 0.0f));
    mVibNext = 1;
}

/* 000013A4-000013B8       .text go_up_stairs_demo_move_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_act_init_proc() {
    mSmokeNext = 1;
    mVibNext = 2;
}

/* 000013B8-00001740       .text setup_action__12daObjYLzou_cFi */
void daObjYLzou_c::setup_action(int i_action) {
    static void (daObjYLzou_c::*act_init_proc[15])() = {
        &daObjYLzou_c::move_ylzou_demo_start_wait_act_init_proc,
        &daObjYLzou_c::demo_regist_wait_act_init_proc,
        &daObjYLzou_c::move_ylzou_demo_vib_start_wait_act_init_proc,
        &daObjYLzou_c::move_ylzou_demo_vib_act_init_proc,
        &daObjYLzou_c::move_ylzou_demo_move_act_init_proc,
        &daObjYLzou_c::demo_end_wait_act_init_proc,
        &daObjYLzou_c::open_wait_act_init_proc,
        &daObjYLzou_c::demo_regist_wait_act_init_proc,
        &daObjYLzou_c::go_up_stairs_demo_move_start_wait_act_init_proc,
        &daObjYLzou_c::go_up_stairs_demo_move_act_init_proc,
        &daObjYLzou_c::demo_end_wait_act_init_proc,
        &daObjYLzou_c::close_wait_act_init_proc,
        &daObjYLzou_c::close_wait_act_init_proc,
        &daObjYLzou_c::demo_regist_wait_act_init_proc,
        &daObjYLzou_c::demo_end_wait_act_init_proc,
    };
    static void (daObjYLzou_c::*act_proc[15])() = {
        &daObjYLzou_c::move_ylzou_demo_start_wait_act_proc,
        &daObjYLzou_c::demo_regist_wait_act_proc,
        &daObjYLzou_c::demo_vib_start_wait_act_proc,
        &daObjYLzou_c::demo_vib_act_proc,
        &daObjYLzou_c::move_ylzou_demo_move_act_proc,
        &daObjYLzou_c::demo_end_wait_act_proc,
        &daObjYLzou_c::wait_act_proc,
        &daObjYLzou_c::demo_regist_wait_act_proc,
        &daObjYLzou_c::demo_vib_act_proc,
        &daObjYLzou_c::go_up_stairs_demo_move_act_proc,
        &daObjYLzou_c::demo_end_wait_act_proc,
        &daObjYLzou_c::wait_act_proc,
        &daObjYLzou_c::wait_act_proc,
        &daObjYLzou_c::demo_regist_wait_act_proc,
        &daObjYLzou_c::demo_end_wait_act_proc,
    };
    (this->*act_init_proc[i_action])();
    mActionFn = act_proc[i_action];
    mAction = i_action;
}

/* 00001740-000017D4       .text _execute__12daObjYLzou_cFv */
bool daObjYLzou_c::_execute() {
    fopAcM_posMoveF(this, NULL);
    set_mtx();
    if (mpBgW != NULL && mpBgW->ChkUsed()) {
        mpBgW->Move();
    }
    (this->*mActionFn)();
    eff_smoke_proc();
    vib_proc();
    return true;
}

/* 000017D4-00001834       .text _draw__12daObjYLzou_cFv */
bool daObjYLzou_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

/* 00001834-00001854       .text daObjYLzou_Create__FP10fopAc_ac_c */
static cPhs_State daObjYLzou_Create(fopAc_ac_c* i_this) {
    return ((daObjYLzou_c*)i_this)->_create();
}

/* 00001854-00001878       .text daObjYLzou_Delete__FP12daObjYLzou_c */
static BOOL daObjYLzou_Delete(daObjYLzou_c* i_this) {
    return ((daObjYLzou_c*)i_this)->_delete();
}

/* 00001878-0000189C       .text daObjYLzou_Execute__FP12daObjYLzou_c */
static BOOL daObjYLzou_Execute(daObjYLzou_c* i_this) {
    return ((daObjYLzou_c*)i_this)->_execute();
}

/* 0000189C-000018C0       .text daObjYLzou_Draw__FP12daObjYLzou_c */
static BOOL daObjYLzou_Draw(daObjYLzou_c* i_this) {
    return ((daObjYLzou_c*)i_this)->_draw();
}

/* 000018C0-000018C8       .text daObjYLzou_IsDelete__FP12daObjYLzou_c */
static BOOL daObjYLzou_IsDelete(daObjYLzou_c*) {
    return TRUE;
}

static actor_method_class l_daObjYLzou_Method = {
    (process_method_func)daObjYLzou_Create,
    (process_method_func)daObjYLzou_Delete,
    (process_method_func)daObjYLzou_Execute,
    (process_method_func)daObjYLzou_IsDelete,
    (process_method_func)daObjYLzou_Draw,
};

actor_process_profile_definition g_profile_Obj_YLzou = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_YLzou_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjYLzou_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0058,
    /* Sub Method   */ &l_daObjYLzou_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
