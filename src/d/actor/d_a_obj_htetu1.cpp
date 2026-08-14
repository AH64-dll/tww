/**
 * d_a_obj_htetu1.cpp
 * Object - Tower of the Gods - Large yellow gate (blocks room containing Small Key)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_htetu1.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_bg_s.h"
#include "d/d_bg_s_func.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_audio.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "f_op/f_op_actor_mng.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "SSystem/SComponent/c_lib.h"

namespace {
u16 l_daObjHtetu1_splash_id_table[2] = {0x82BA, 0x82BB};
}  // namespace

const char daObjHtetu1_c::M_arcname[] = "Htetu1";

/* 00000078-00000178       .text create_s__19daObjHtetu1Splash_cFUsP4cXyzP5csXyzP12dKy_tevstr_c */
void daObjHtetu1Splash_c::create_s(u16 param, cXyz* pos, csXyz* angle, dKy_tevstr_c* tevStr) {
    mPos = *pos;
    mAngle = *angle;
    mpEmitter = dComIfGp_particle_set(param, &mPos, &mAngle, NULL, 0xFF, this, -1, NULL, NULL, NULL);
    if (mpEmitter != NULL) {
        mpEmitter->setGlobalPrmColor(tevStr->mColorC0.r, tevStr->mColorC0.g, tevStr->mColorC0.b);
    }
    if (mpEmitter != NULL) {
        mpEmitter->stopCreateParticle();
        mStop = 0;
    }
    mStop = 0;
    mTimer = -2;
}

/* 00000178-00000198       .text solidHeapCB__13daObjHtetu1_cFP10fopAc_ac_c */
u8 daObjHtetu1_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjHtetu1_c*)i_this)->create_heap();
}

/* 00000198-00000298       .text create_heap__13daObjHtetu1_cFv */
int daObjHtetu1_c::create_heap() {
    int ret = TRUE;
    J3DModelData* mdl_data =
        (J3DModelData*)dComIfG_getObjectRes(M_arcname, 4);
    if (mdl_data == NULL) {
        JUT_ASSERT(0x119, mdl_data != 0);
        ret = FALSE;
    } else {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        Mtx* mtx = &mpModel->getBaseTRMtx();
        mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(M_arcname, 7), 1, mtx);
        if (mpBgW == NULL) {
            ret = FALSE;
        }
    }
    return ret;
}

/* 00000298-00000460       .text _create__13daObjHtetu1_cFv */
cPhs_State daObjHtetu1_c::_create() {
    fopAcM_SetupActor(this, daObjHtetu1_c);

    cPhs_State phs = dComIfG_resLoad(&mPhs, M_arcname);
    if (phs == cPhs_COMPLEATE_e) {
        phs = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, (heapCallbackFunc)solidHeapCB, 0xAE0)) {
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            mSwSave = fopAcM_GetParam(this) & 0xFF;
            mWaterLevel = current.pos.y - 2300.0f;
            if (check_sw()) {
                current.pos.y = mWaterLevel;
                mMode = 2;
            }
            mQuakeTimer = -1;
            init_mtx();
            g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &tevStr);
            for (int i = 0; i < 2; i++) {
                mSplash[i].create_s(l_daObjHtetu1_splash_id_table[i], &current.pos, &current.angle, &tevStr);
            }
            fopAcM_setCullSizeBox(this, -950.0f, -1000.0f, -100.0f, 950.0f, 1300.0f, 100.0f);
            dComIfG_Bgsp()->Regist(mpBgW, this);
            mEvtIdx = dComIfGp_evmng_getEventIdx("htetu1_open", 0xFF);
            phs = cPhs_COMPLEATE_e;
        }
    }
    return phs;
}

/* 00000508-00000610       .text _delete__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_delete() {
    if (mQuakeTimer > 0) {
        dComIfGp_getVibration().StopQuake(-1);
        mQuakeTimer = -1;
    }
    for (int i = 0; i < 2; i++) {
        mSplash[i].delete_s();
    }
    if (heap != NULL && mpBgW != NULL && mpBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW);
        mpBgW = NULL;
    }
    dComIfG_resDelete(&mPhs, M_arcname);
    return TRUE;
}

/* 00000610-00000648       .text check_sw__13daObjHtetu1_cFv */
inline BOOL daObjHtetu1_c::check_sw() {
    return dComIfGs_isSwitch(mSwSave, home.roomNo);
}

/* 00000648-000006E4       .text init_mtx__13daObjHtetu1_cFv */
void daObjHtetu1_c::init_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 000006E4-000007F8       .text unlock__13daObjHtetu1_cFv */
void daObjHtetu1_c::unlock() {
    cXyz dir = cXyz::BaseY;
    mPos -= mDir;
    f32 spd = (s16)(mSpeed * cM_ssin(mAngle * 0x859));
    dir *= fabs(spd);
    mPos += dir;
    mDir = dir;
    cLib_addCalc(&mSpeed, 0.0f, 0.13f, 50.0f, 1.0f);
}

/* 000007F8-0000098C       .text get_water_h__13daObjHtetu1_cFv */
f32 daObjHtetu1_c::get_water_h() {
    dBgS_WtrChk waterChk;
    cXyz chkPos = home.pos;
    f32 ret = current.pos.y;

    mDoMtx_stack_c::YrotS(current.angle.y);
    cXyz offVec = cXyz::BaseZ;
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &offVec);
    offVec *= 400.0f;
    chkPos += offVec;
    if (dBgS_SplGrpChk_In_ObjGnd(chkPos, &waterChk, 1.0f) != false) {
        ret = waterChk.GetHeight();
    }
    return ret;
}

/* 00000AB0-00000BCC       .text splash_manager__13daObjHtetu1_cFv */
void daObjHtetu1_c::splash_manager() {
    f32 waterH = get_water_h();
    for (int i = 0; i < 2; i++) {
        mSplash[i].set_pos_y(waterH);
        s16 timer = mSplash[i].get_timer();
        if (timer == 0) {
            if (mSplash[i].chk_stop()) {
                mSplash[i].stop_particle();
            }
        } else {
            if (timer > 0 || timer == -1) {
                if (1400.0f + current.pos.y <= waterH) {
                    if (mSplash[i].chk_stop()) {
                        mSplash[i].stop_particle();
                    }
                } else if (!mSplash[i].chk_stop()) {
                    mSplash[i].play_particle();
                }
            }
            if (timer > 0) {
                mSplash[i].sub_timer();
            }
        }
    }
}

/* 00000BCC-0000101C       .text _execute__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_execute() {
    switch (mMode) {
    case 0:
        if (check_sw()) {
            if (eventInfo.mCommand != dEvtCmd_INDEMO_e) {
                fopAcM_orderOtherEventId(this, mEvtIdx, 0xFF, 0xFFFF, 0, 1);
                eventInfo.onCondition(dEvtCnd_UNK2_e);
            } else {
                mSpeed = 50.0f;
                mAngle = 0x46;
                mDir = cXyz::BaseY * 50.0f;
                mDoAud_seStart(JA_SE_READ_RIDDLE_1);
                mStatus = 1;
                mMode = 1;
                dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                for (int i = 0; i < 2; i++) {
                    mSplash[i].timer_play_particle(0x1E);
                }
            }
        }
        break;
    case 1:
        if (dComIfGp_evmng_endCheck(mEvtIdx)) {
            dComIfGp_event_reset();
            mMode = 2;
        }
        break;
    }

    mPos = current.pos;

    switch (mStatus) {
    case 1:
        unlock();
        if (mAngle != 0) {
            mAngle--;
            fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_KOUSHI_MOVE, 0);
        } else {
            dComIfGp_getVibration().StartQuake(6, 3, cXyz(0.0f, 1.0f, 0.0f));
            mStatus = 2;
            mQuakeTimer = 200;
            for (int i = 0; i < 2; i++) {
                mSplash[i].timer_play_particle(-1);
            }
        }
        break;
    case 2:
        mPos.y -= 5.0f;
        fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_KOUSHI_MOVE, 0);
        if (mPos.y <= mWaterLevel) {
            for (int i = 0; i < 2; i++) {
                mSplash[i].delete_s();
            }
            mPos.y = mWaterLevel;
            mStatus = 0;
        }
        break;
    }

    current.pos = mPos;
    init_mtx();
    splash_manager();

    if (mQuakeTimer == 0) {
        dComIfGp_getVibration().StopQuake(-1);
        mQuakeTimer = -1;
    } else if (mQuakeTimer > 0) {
        mQuakeTimer--;
    }

    if (heap != NULL && mpBgW != NULL && mpBgW->ChkUsed()) {
        mpBgW->Move();
    }
    return TRUE;
}

/* 0000101C-0000107C       .text _draw__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

namespace {
/* 0000107C-0000109C       .text Mthd_Create__28@unnamed@d_a_obj_htetu1_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_create();
}

/* 0000109C-000010C0       .text Mthd_Delete__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_delete();
}

/* 000010C0-000010E4       .text Mthd_Execute__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_execute();
}

/* 000010E4-00001108       .text Mthd_Draw__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_draw();
}

/* 00001108-00001110       .text Mthd_IsDelete__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Htetu1_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Htetu1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Htetu1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHtetu1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Htetu1_e,
    /* Actor SubMtd */ &Htetu1_Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
