/**
 * d_a_obj_hcbh.cpp
 * Object - Tower of the Gods - Pillar with Companion Statue's face on it.
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hcbh.h"
#include "d/d_com_inf_game.h"
#include "d/d_stage.h"
#include "d/d_kankyo.h"
#include "d/d_bg_s.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "f_op/f_op_actor_mng.h"

namespace {
const char l_arcname[] = "Hcbh";

static const dCcD_SrcCyl l_cyl_src = {
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0x04010028,
        /* SrcObjTg  SPrm    */ 0x09,
        /* SrcObjCo  SPrm    */ 0x39,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 6,
        /* SrcGObjCo SPrm    */ 0,
    },
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 70.0f,
        /* Height */ 556.0f,
    }},
};

static const dCcD_SrcSph l_sph_src = {
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0x800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ 0x0F,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0x79,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 1,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 35.0f,
    }},
};

static const Vec l_co_sph_offset[6] = {
    {0.0f, 157.0f, 0.0f},
    {0.0f, 227.0f, 0.0f},
    {0.0f, 297.0f, 0.0f},
    {0.0f, 367.0f, 0.0f},
    {0.0f, 437.0f, 0.0f},
    {0.0f, 507.0f, 0.0f},
};

static int bdl_table[4] = {4, 5, 6, 7};

static s16 set_anglY[4] = {-0x8000, -0x4000, 0x4000, 0x0000};
}  // namespace

/* 00000078-000000D8       .text chk_appear__11daObjHcbh_cFv */
BOOL daObjHcbh_c::chk_appear() {
    s32 swSave = param_get_swSave();
    BOOL result = TRUE;
    if (swSave != 0xFF) {
        result = dComIfGs_isSwitch(swSave, home.roomNo) ? FALSE : TRUE;
    }
    return result;
}

/* 000000D8-0000029C       .text set_mtx__11daObjHcbh_cFv */
void daObjHcbh_c::set_mtx() {
    /* Nonmatching */
    f32 f31 = 50.0f * cM_ssin(mD34);
    mDoMtx_stack_c::transS(current.pos.x, mD2C, current.pos.z);
    mDoMtx_stack_c::YrotM(mDA0);
    mDoMtx_stack_c::transM(0.0f, f31, 0.0f);
    mDoMtx_stack_c::XrotM(mD34);
    mDoMtx_stack_c::transM(0.0f, -f31, 0.0f);
    mDoMtx_stack_c::YrotM(-mDA0);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    J3DModel* mdl = mpModel;
    MtxP now = mDoMtx_stack_c::get();
    PSMTXCopy(now, mdl->getBaseTRMtx());

    for (int i = 0; i < 4; i++) {
        mDoMtx_stack_c::transS(mD38[i].x, mD38[i].y, mD38[i].z);
        mDoMtx_stack_c::YrotM(mD80[i]);
        mDoMtx_stack_c::XrotM(mD78[i]);
        mDoMtx_stack_c::YrotM(-mD80[i]);
        mDoMtx_stack_c::XYZrotM(shape_angle.x, shape_angle.y, shape_angle.z);
        MtxP now2 = mDoMtx_stack_c::get();
        J3DModel* mdl2 = mpModel2[i];
        PSMTXCopy(now2, mdl2->getBaseTRMtx());
    }
}

/* 0000029C-0000030C       .text init_mtx__11daObjHcbh_cFv */
void daObjHcbh_c::init_mtx() {
    mpModel->setBaseScale(scale);
    for (int i = 0; i < 4; i++) {
        mpModel2[i]->setBaseScale(scale);
    }
    set_mtx();
}

/* 0000030C-00000330       .text solidHeapCB__11daObjHcbh_cFP10fopAc_ac_c */
u8 daObjHcbh_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjHcbh_c*)i_this)->create_heap();
}

/* 00000330-00000500       .text create_heap__11daObjHcbh_cFv */
int daObjHcbh_c::create_heap() {
    /* Nonmatching */
    int ret = TRUE;
    J3DModelData* modelData =
        (J3DModelData*)dComIfG_getObjectRes(l_arcname, 8);
    if (modelData == NULL) {
        JUT_ASSERT(0x1F3, 0);
        ret = FALSE;
    } else {
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        for (int i = 0; i < 4; i++) {
            modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, bdl_table[i]);
            if (modelData == NULL) {
                ret = FALSE;
                break;
            }
            mpModel2[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        }
        Mtx* mtx = &mpModel->getBaseTRMtx();
        mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, 0xC), 1, mtx);
        mtx = &mpModel2[0]->getBaseTRMtx();
        mpBgW2 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, 0xB), 1, mtx);
        if (mpModel != NULL && mpModel2[0] != NULL && mpModel2[1] != NULL && mpModel2[2] != NULL &&
            mpModel2[3] != NULL && mpBgW != NULL && mpBgW2 != NULL)
        {
        } else {
            ret = FALSE;
        }
    }
    return ret;
}

/* 00000500-000005E8       .text setup_break_condition__11daObjHcbh_cFP10fopAc_ac_c */
void daObjHcbh_c::setup_break_condition(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    if (i_actor != NULL) {
        mDA0 = cM_atan2s(mCyl.GetC().x - i_actor->current.pos.x, mCyl.GetC().z - i_actor->current.pos.z);
        f32 f1 = 15.0f;
        for (int i = 0; i < 4; i++) {
            mD80[i] = set_anglY[i];
            mD78[i] = 0;
            f32 f0 = fabs(cM_ssin((s16)((set_anglY[i] - mDA0) >> 1)));
            mD90[i] = (int)(f1 * f0);
        }
    }
}

/* 000005E8-00000724       .text checkCollision__11daObjHcbh_cFv */
void daObjHcbh_c::checkCollision() {
    if (mCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj != NULL) {
            switch (hitObj->GetAtType()) {
            case 0x20:
                mDA4 = 3;
                setup_break_condition(mCyl.GetTgHitAc());
                break;
            case 0x10000:
                mDA4 = 2;
                setup_break_condition(mCyl.GetTgHitAc());
                break;
            case 0x8: {
                fopAc_ac_c* hitActor = mCyl.GetTgHitAc();
                if (hitActor != NULL && fopAcM_GetProfName(hitActor) == 0xC0) {
                    mDA4 = 1;
                    setup_break_condition(mCyl.GetTgHitAc());
                }
                break;
            }
            case 0x4000000:
                mDA4 = 1;
                setup_break_condition(mCyl.GetTgHitAc());
                break;
            }
        }
        mCyl.ClrTgHit();
    }
}

/* 00000724-0000077C       .text co_hitCallback__11daObjHcbh_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjHcbh_c::co_hitCallback(fopAc_ac_c* i_this, dCcD_GObjInf*, fopAc_ac_c* i_actor, dCcD_GObjInf*) {
    if (fopAc_IsActor(i_actor) && fopAcM_GetProfName(i_actor) == 0xCB) {
        ((daObjHcbh_c*)i_this)->mDA4 = 4;
    }
}

/* 0000077C-000008F8       .text particle_set__11daObjHcbh_cFv */
void daObjHcbh_c::particle_set() {
    /* Nonmatching */
    csXyz angle(0, mDA0, 0);
    dComIfG_inf_c* gameInfo = &g_dComIfG_gameInfo;
    gameInfo->play.getParticle()->set(0, 0x82DD, &current.pos, NULL, NULL, 0xFF, NULL, -1,
                                      &tevStr.mColorK0, NULL, NULL);
    gameInfo->play.getParticle()->set(0, 0x82DE, &current.pos, &angle, NULL, 0xFF, NULL, -1,
                                      &tevStr.mColorK0, NULL, NULL);
    if (mDA4 != 3) {
        gameInfo->play.getParticle()->set(0, 0x82DF, &current.pos, &angle, NULL, 0xFF, NULL, -1,
                                          &tevStr.mColorK0, NULL, NULL);
    }
    mSmokeCB.end();
    gameInfo->play.getParticle()->set(2, 0xA2E0, &current.pos, &angle, NULL, 0xA0, &mSmokeCB, -1,
                                      &tevStr.mColorK0, NULL, NULL);
}

/* 000008F8-000009E4       .text make_item__11daObjHcbh_cFv */
void daObjHcbh_c::make_item() {
    s32 itemNo = param_get_itemNo();
    s32 itemSaveBitNo = param_get_itemSaveBitNo();
    cXyz pos = current.pos;
    csXyz angle(0, 0, 0);
    pos.y -= 30.0f;
    fopAcM_createItemFromTable(&pos, itemNo, itemSaveBitNo, home.roomNo, 0, &angle, 1, NULL);
    s32 swSave = param_get_swSave();
    if (swSave != 0xFF) {
        dComIfGs_onSwitch(swSave, home.roomNo);
    }
}

/* 00000A20-00000E30       .text _create__11daObjHcbh_cFv */
cPhs_State daObjHcbh_c::_create() {
    /* Nonmatching */
    cPhs_State phs = cPhs_ERROR_e;

    fopAcM_SetupActor(this, daObjHcbh_c);

    if (base.base.mInitState == 0) {
        mD2C = current.pos.y;
        mD34 = 0;
        for (int i = 0; i < 4; i++) {
            mD38[i] = current.pos;
            mD78[i] = 0;
            mD80[i] = 0;
        }
        mDC8 = chk_appear();
    }

    if (mDC8 == 1) {
        phs = dComIfG_resLoad(&mPhs, l_arcname);
        if (phs == cPhs_COMPLEATE_e) {
            if (fopAcM_entrySolidHeap(this, (heapCallbackFunc)solidHeapCB, 0x2D00)) {
                if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
                    phs = cPhs_ERROR_e;
                } else if (dComIfG_Bgsp()->Regist(mpBgW2, this)) {
                    phs = cPhs_ERROR_e;
                } else {
                    cullMtx = mpModel->getBaseTRMtx();
                    init_mtx();
                    mCir.SetWall(589.0f, 70.0f);
                    mAcch.Set(&current.pos, &old.pos, this, 1, &mCir, &speed, &current.angle, &shape_angle);
                    mAcch.ClrWaterNone();
                    mAcch.ClrRoofNone();
                    mAcch.m_roof_crr_height = 589.0f;
                    mAcch.CrrPos(*dComIfG_Bgsp());
                    mAcch.m_flags &= ~0x80;
                    mStts.Init(0xFF, 0xFF, this);
                    mCyl.Set(l_cyl_src);
                    mCyl.SetStts(&mStts);
                    mCyl.SetC(current.pos);
                    mCyl.SetCoHitCallback(co_hitCallback);

                    for (int i = 0; i < 6; i++) {
                        mSph[i].Set(l_sph_src);
                        mSph[i].SetStts(&mStts);
                        mSph[i].SetR(70.0f);
                        mSph[i].SetC(cXyz(current.pos.x, current.pos.y + l_co_sph_offset[i].y, current.pos.z));
                    }
                    mSmokeCB.setTevStr(&tevStr);
                    mSmokeCB.setRateOff(0);
                    mSmokeCB.setFollowOff();
                    mProcFunc = &daObjHcbh_c::wait_act_proc;
                    fopAcM_setCullSizeBox(this, -40.0f, 0.0f, -40.0f, 100.0f, 589.0f, 100.0f);
                }
            } else {
                phs = cPhs_ERROR_e;
            }
        }
    }
    return phs;
}

/* 000011F4-000012F4       .text _delete__11daObjHcbh_cFv */
bool daObjHcbh_c::_delete() {
    /* Nonmatching */
    if (mDC8 == 1) {
        dComIfG_resDelete(&mPhs, l_arcname);
        if (heap != NULL) {
            if (mpBgW != NULL && mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
            mpBgW = NULL;
            if (mpBgW2 != NULL && mpBgW2->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW2);
            }
            mpBgW2 = NULL;
        }
        mSmokeCB.remove();
    }
    return TRUE;
}

/* 000012F4-000013BC       .text wait_act_proc__11daObjHcbh_cFv */
void daObjHcbh_c::wait_act_proc() {
    /* Nonmatching */
    checkCollision();
    if (mDA4 == 0) {
        dComIfG_Ccsp()->Set(&mCyl);
    } else {
        particle_set();
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_TN_COLUMN_BREAK, &current.pos, 0,
                                        dComIfGp_getReverb(fopAcM_GetRoomNo(this)), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        mCyl.SetCoHitCallback(NULL);
        mProcFunc = &daObjHcbh_c::fall_act_proc;
    }
}

/* 000013BC-000017D8       .text fall_act_proc__11daObjHcbh_cFv */
void daObjHcbh_c::fall_act_proc() {
    /* Nonmatching */
    if (mD34 < 0) {
        mD34 = -0x8000;
        mD36 = 0;
    } else if (mD34 > 0x2000) {
        if (mpBgW != NULL && mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }
        if (mpBgW2 != NULL && mpBgW2->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW2);
        }
        mD36 += (s16)(4.0f + cM_ssin(mD34) * 127.0f);
    }

    if (mD2C < home.pos.y + -10.0f) {
        make_item();
        dComIfGp_getVibration().StartShock(8, -0x11, cXyz(0.0f, 1.0f, 0.0f));
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_TN_COLUMN_SMASH, &current.pos, 0,
                                        dComIfGp_getReverb(fopAcM_GetRoomNo(this)), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        fopAcM_delete(this);
        return;
    }

    mD30 += -0.011f;
    f32 f31 = 50.0f * cM_ssin(mD34);
    mDoMtx_stack_c::transS(current.pos.x, mD2C, current.pos.z);
    mDoMtx_stack_c::YrotM(mDA0);
    mDoMtx_stack_c::transM(0.0f, f31, 0.0f);
    mDoMtx_stack_c::XrotM(mD34);
    mDoMtx_stack_c::transM(0.0f, -f31, 0.0f);
    mDoMtx_stack_c::YrotM(-mDA0);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, shape_angle.y, shape_angle.z);

    for (int i = 0; i < 6; i++) {
        cXyz pos(l_co_sph_offset[i]);
        PSMTXMultVec(mDoMtx_stack_c::get(), &pos, &pos);
        mSph[i].MoveCAt(pos);
        dComIfG_Ccsp()->Set(&mSph[i]);
    }

    for (int i = 0; i < 4; i++) {
        if (mD90[i] > 0) {
            mD90[i]--;
        } else {
            mD68[i] += -0.01f;
            mD38[i].y += mD68[i];
            if (mD38[i].y < home.pos.y + -100.0f) {
                mD38[i].y = home.pos.y + -100.0f;
            }
            mD88[i] += (s16)(4.0f + cM_ssin(mD78[i]) * 512.0f);
            mD78[i] += mD88[i];
            if (mD78[i] > 0x4000) {
                mD78[i] = 0x4000;
            }
        }
    }
}

/* 000017D8-000018D8       .text _execute__11daObjHcbh_cFv */
bool daObjHcbh_c::_execute() {
    set_mtx();
    mStts.Move();
    mAcch.CrrPos(*dComIfG_Bgsp());
    if (mpBgW != NULL && mpBgW->ChkUsed()) {
        mpBgW->Move();
    }
    if (mpBgW2 != NULL && mpBgW2->ChkUsed()) {
        mpBgW2->Move();
    }
    mD2C += mD30;
    mD34 += mD36;
    if (mD34 >= 0x4000) {
        mD34 = 0x4000;
    }
    (this->*mProcFunc)();
    return TRUE;
}

/* 000018D8-0000197C       .text _draw__11daObjHcbh_cFv */
bool daObjHcbh_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    for (int i = 0; i < 4; i++) {
        g_env_light.setLightTevColorType(mpModel2[i], &tevStr);
        mDoExt_modelUpdateDL(mpModel2[i]);
    }
    return TRUE;
}

/* 0000197C-0000199C       .text daObjHcbh_Create__FP10fopAc_ac_c */
static cPhs_State daObjHcbh_Create(fopAc_ac_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_create();
}

/* 0000199C-000019C0       .text daObjHcbh_Delete__FP11daObjHcbh_c */
static BOOL daObjHcbh_Delete(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_delete();
}

/* 000019C0-000019E4       .text daObjHcbh_Execute__FP11daObjHcbh_c */
static BOOL daObjHcbh_Execute(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_execute();
}

/* 000019E4-00001A08       .text daObjHcbh_Draw__FP11daObjHcbh_c */
static BOOL daObjHcbh_Draw(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_draw();
}

/* 00001A08-00001A10       .text daObjHcbh_IsDelete__FP11daObjHcbh_c */
static BOOL daObjHcbh_IsDelete(daObjHcbh_c*) {
    return TRUE;
}

static actor_method_class l_daObjHcbh_Method = {
    (process_method_func)daObjHcbh_Create,
    (process_method_func)daObjHcbh_Delete,
    (process_method_func)daObjHcbh_Execute,
    (process_method_func)daObjHcbh_IsDelete,
    (process_method_func)daObjHcbh_Draw,
};

actor_process_profile_definition g_profile_Obj_Hcbh = {
    /* Layer ID */ fpcLy_CURRENT_e,
    /* List ID  */ 3,
    /* List Prio*/ fpcPi_CURRENT_e,
    /* Proc Name*/ fpcNm_Obj_Hcbh_e,
    /* Proc SubMtd*/ &g_fpcLf_Method.base,
    /* Size     */ sizeof(daObjHcbh_c),
    /* Size Other*/ 0,
    /* Parameters*/ 0,
    /* Leaf SubMtd*/ &g_fopAc_Method.base,
    /* Priority  */ 0x005D,
    /* Actor SubMtd*/ &l_daObjHcbh_Method,
    /* Status    */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group     */ fopAc_ACTOR_e,
    /* Cull Type */ fopAc_CULLBOX_CUSTOM_e,
};
