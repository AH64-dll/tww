/**
 * d_a_obj_msdan_sub2.cpp
 * Object - Tower of the Gods - MsdanSub2 (spark from Msdan2)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_msdan_sub2.h"
#include "d/d_com_inf_game.h"
#include "f_pc/f_pc_name.h"
#include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_name.h"
#include "SSystem/SComponent/c_math.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "m_Do/m_Do_mtx.h"

namespace daObjMsdanSub2 {
const char Act_c::M_arcname[] = "Msdan";
Mtx Act_c::M_tmp_mtx;

/* 00000078-0000012C       .text CreateHeap__Q214daObjMsdanSub25Act_cFv */
BOOL Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, 4);
    JUT_ASSERT(0x57, model_data != 0);

    mpModel = mDoExt_J3DModel__create(model_data, 0, 0x11020203);
    return mpModel != NULL;
}

/* 0000012C-000002E4       .text Create__Q214daObjMsdanSub25Act_cFv */
BOOL Act_c::Create() {
    cullMtx = mpModel->getBaseTRMtx();
    fopAcM_setCullSizeBox(this, -1500.0f, -1000.0f, -1500.0f, 1500.0f, 1000.0f, 1500.0f);

    s32 swSave = prm_get_swSave();
    if (dComIfGs_isSwitch(swSave, home.roomNo)) {
        if (!(prm_get_swSave2() & 1)) {
            current.pos.x = home.pos.x + 600.0f * cM_scos(current.angle.y);
            current.pos.z = home.pos.z + 600.0f * cM_ssin(current.angle.y);
        } else {
            current.pos.x = home.pos.x - 600.0f * cM_scos(current.angle.y);
            current.pos.z = home.pos.z - 600.0f * cM_ssin(current.angle.y);
        }
        mCounter = 0x10;
    } else {
        mCounter = 0;
        mOffset = 0.0f;
        mTimer = 0.0f;
    }

    init_mtx();
    mpBgW->Move();
    return TRUE;
}

/* 000002E4-00000454       .text Mthd_Create__Q214daObjMsdanSub25Act_cFv */
cPhs_State Act_c::Mthd_Create() {
    fopAcM_ct(this, Act_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, 7, dBgS_MoveBGProc_Trans, 0x9A0);
        JUT_ASSERT(0x91, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));

        s32 swSave = prm_get_swSave();
        if (dComIfGs_isSwitch(swSave, home.roomNo)) {
            if (mpBgW != NULL && mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
        }
    }
    return phase_state;
}

/* 00000454-0000045C       .text Delete__Q214daObjMsdanSub25Act_cFv */
BOOL Act_c::Delete() {
    return TRUE;
}

/* 0000045C-000004A8       .text Mthd_Delete__Q214daObjMsdanSub25Act_cFv */
BOOL Act_c::Mthd_Delete() {
    BOOL ret = MoveBGDelete();
    dComIfG_resDelete(&mPhs, M_arcname);
    return ret;
}

/* 000004A8-00000528       .text set_mtx__Q214daObjMsdanSub25Act_cFv */
void Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    J3DModel* mdl = mpModel;
    MtxP now = mDoMtx_stack_c::get();
    PSMTXCopy(now, mdl->getBaseTRMtx());
    PSMTXCopy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000528-00000598       .text init_mtx__Q214daObjMsdanSub25Act_cFv */
void Act_c::init_mtx() {
    PSVECScale(&scale, &scale, 1.01f);
    mpModel->setBaseScale(scale);
    MtxP tmpMtx = M_tmp_mtx;
    PSMTXCopy(tmpMtx, mBgMtx);
    set_mtx();
}

/* 00000598-0000090C       .text Execute__Q214daObjMsdanSub25Act_cFPPA3_A4_f */
BOOL Act_c::Execute(Mtx** i_mtx) {
    if (dComIfGs_isSwitch(prm_get_swSave(), home.roomNo)) {
        if (mTimer < 0.0f) {
            mTimer = 0.0f;
        }
        if (mCounter < 0x10) {
            if (mTimer == 0.0f) {
                mDoAud_seStart(JA_SE_OBJ_SW_STAIR2_ON_1, &current.pos, 0,
                               dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            }
            mTimer += 10.0f;
            mOffset += mTimer;
            if (mCounter == prm_get_swSave2()) {
                if (mCounter & 1) {
                    current.pos.x = home.pos.x - mOffset * cM_scos(current.angle.y);
                    current.pos.z = home.pos.z - mOffset * cM_ssin(current.angle.y);
                } else {
                    current.pos.x = home.pos.x + mOffset * cM_scos(current.angle.y);
                    current.pos.z = home.pos.z + mOffset * cM_ssin(current.angle.y);
                }
            }
            if (mOffset >= 600.0f) {
                if (mCounter == prm_get_swSave2()) {
                    if (mCounter & 1) {
                        current.pos.x = home.pos.x - mOffset * cM_scos(current.angle.y);
                        current.pos.z = home.pos.z - mOffset * cM_ssin(current.angle.y);
                    } else {
                        current.pos.x = home.pos.x + mOffset * cM_scos(current.angle.y);
                        current.pos.z = home.pos.z + mOffset * cM_ssin(current.angle.y);
                    }
                    dComIfGp_getVibration().StartShock(1, 1, cXyz(0.0f, 1.0f, 0.0f));
                }
                mCounter++;
                mTimer = 0.0f;
                mOffset = 0.0f;
            }
        }
    }
    set_mtx();
    *i_mtx = &M_tmp_mtx;
    return TRUE;
}

/* 0000090C-000009AC       .text Draw__Q214daObjMsdanSub25Act_cFv */
BOOL Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaListBG, 0);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpXluListBG, 1);
    mDoExt_modelUpdateDL(mpModel);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaList, 0);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpXluList, 1);
    return TRUE;
}

namespace {
/* 000009AC-000009CC       .text Mthd_Create__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjMsdanSub2::Act_c*)i_this)->Mthd_Create();
}

/* 000009CC-000009EC       .text Mthd_Delete__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjMsdanSub2::Act_c*)i_this)->Mthd_Delete();
}

/* 000009EC-00000A0C       .text Mthd_Execute__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjMsdanSub2::Act_c*)i_this)->MoveBGExecute();
}

/* 00000A0C-00000A38       .text Mthd_Draw__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjMsdanSub2::Act_c*)i_this)->Draw();
}

/* 00000A38-00000A64       .text Mthd_IsDelete__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjMsdanSub2::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_MsdanSub2 = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjMsdanSub2

actor_process_profile_definition g_profile_Obj_MsdanSub2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_MsdanSub2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMsdanSub2::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_MsdanSub2_e,
    /* Actor SubMtd */ &daObjMsdanSub2::Mthd_MsdanSub2,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
