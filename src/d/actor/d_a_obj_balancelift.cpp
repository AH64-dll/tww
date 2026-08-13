/**
 * d_a_obj_balancelift.cpp
 * Object - Tower of the Gods - Pair of scales
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_balancelift.h"
#include "d/d_a_obj.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_chain.h"
#include "d/d_path.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_particle.h"
#include "d/d_lib.h"
#include "m_Do/m_Do_mtx.h"
#include "JAZelAudio/JAIZelBasic.h"

dChain_packet_c* dChain_packet_create(int, dKy_tevstr_c*, f32);
void PSQUATInverse(const Quaternion* src, Quaternion* inv);

static daBalancelift_HIO_c l_HIO;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 200.0f,
    }},
};

/* 000000EC-00000160       .text __ct__19daBalancelift_HIO_cFv */
daBalancelift_HIO_c::daBalancelift_HIO_c() {
    mChildIdx = -1;
    mFloat0x08 = 45.0f;
    mFloat0x0C = 0.05f;
    mFloat0x10 = 0.005f;
    mFloat0x14 = 0.9f;
    mFloat0x18 = 25.0f;
    mFloat0x1C = 0.65f;
    mFloat0x20 = 0.9f;
    mFloat0x24 = 440.0f;
    mFloat0x28 = 1800.0f;
    mFloat0x2C = 2.0f;
    mFloat0x30 = 2.0f;
    mFloat0x34 = 2.0f;
}

const char daBalancelift_c::M_arcname[] = "Hten1";

/* 0000019C-00000264       .text daObjBlift_ride_actor_check__FP10fopAc_ac_c */
s32 daObjBlift_ride_actor_check(fopAc_ac_c* actor) {
    /* Nonmatching */
    s32 result = 0;
    if (fopAc_IsActor(actor)) {
        if (fopAcM_GetName(actor) == fpcNm_Obj_Try_e) {
            result = 1;
        } else if (fopAcM_GetName(actor) == fpcNm_PLAYER_e) {
            result = 1;
            fpc_ProcID grab_id = ((daPy_py_c*)actor)->getGrabActorID();
            if (grab_id != fpcM_ERROR_PROCESS_ID_e) {
                fopAc_ac_c* grab_actor = fopAcM_SearchByID(grab_id);
                if (grab_actor != NULL) {
                    result = daObjBlift_ride_actor_check(grab_actor) + 1;
                }
            }
        } else if (fopAcM_GetName(actor) == fpcNm_AM2_e || fopAcM_GetName(actor) == fpcNm_NPC_OS_e ||
                   fopAcM_GetName(actor) == fpcNm_NPC_CB1_e) {
            result = 1;
        }
    }
    return result;
}

/* 00000264-0000033C       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
static void ride_call_back(dBgW* pBgW, fopAc_ac_c* actor, fopAc_ac_c* rideActor) {
    daBalancelift_c* lift = (daBalancelift_c*)actor;
    s32 ride_count = daObjBlift_ride_actor_check(rideActor);

    cXyz pos = rideActor->current.pos;
    cXyz diff = pos - lift->mOldPos;
    PSVECScale(&diff, &diff, l_HIO.mFloat0x10);
    PSVECAdd(&lift->mOffset, &diff, &lift->mOffset);

    if (lift->mDir == 0) {
        *lift->mWeightPtr += ride_count;
    } else {
        *lift->mWeightPtr -= ride_count;
    }
}

/* 0000033C-00000510       .text calc_quat__15daBalancelift_cFv */
void daBalancelift_c::calc_quat() {
    /* Nonmatching */
    cXyz pos = current.pos;
    pos.y -= mCurrentY;
    cXyz diff = pos - mOldPos;
    PSVECScale(&diff, &diff, l_HIO.mFloat0x0C);
    PSVECAdd(&mOffset, &diff, &mOffset);
    PSVECScale(&mOffset, &mOffset, l_HIO.mFloat0x14);
    PSVECAdd(&mOldPos, &mOffset, &mOldPos);

    cXyz left = mLeftPos;
    cXyz cur = current.pos;
    PSVECSubtract(&left, &mOldPos, &left);
    PSVECSubtract(&cur, &mOldPos, &cur);

    Quaternion quat1;
    daObj::quat_rotBaseY2(&quat1, cur);
    PSQUATInverse(&quat1, &quat1);

    Quaternion out;
    C_QUATSlerp(&mQuatL, &quat1, &out, 0.1f + REG10_F(23));
    mQuatL = out;

    Quaternion quat2;
    daObj::quat_rotBaseY2(&quat2, left);
    PSQUATInverse(&quat2, &quat2);
    C_QUATSlerp(&mQuatR, &quat2, &out, 0.15f + REG10_F(24));
    mQuatR = out;
}

/* 00000510-00000670       .text set_mtx__15daBalancelift_cFv */
void daBalancelift_c::set_mtx() {
    /* Nonmatching */
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::quatM(&mQuatL);
    mDoMtx_stack_c::transM(0.0f, -mCurrentY, 0.0f);

    cXyz vec(0.0f, 300.0f, 0.0f);
    PSMTXMultVec(mDoMtx_stack_c::get(), &vec, &mLeftPos);
    PSMTXMultVec(mDoMtx_stack_c::get(), &mRightPos, &mChainPos);

    cXyz zero(0.0f, 0.0f, 0.0f);
    PSMTXMultVec(mDoMtx_stack_c::get(), &zero, &mPos);

    mDoMtx_stack_c::quatM(&mQuatR);
    mDoMtx_stack_c::scaleM(l_HIO.mFloat0x2C, l_HIO.mFloat0x30, l_HIO.mFloat0x34);
    J3DModel* mdl = M_mdl;
    PSMTXCopy(mDoMtx_stack_c::get(), mdl->getBaseTRMtx());
    PSMTXCopy(mDoMtx_stack_c::get(), mBgMtx);

    cXyz* pt = m_chain->mPt;
    pt[0] = mPos;
    pt[1] = mChainPos;
    pt[2] = current.pos;
}

/* 00000670-00000984       .text calc_weight__15daBalancelift_cFv */
void daBalancelift_c::calc_weight() {
    /* Nonmatching */
    f32 target_height;
    if (mDir == 0) {
        if (*mWeightPtr == 0) {
            target_height = l_HIO.mFloat0x28 - 0.5f * l_HIO.mFloat0x24;
        } else if (*mWeightPtr > 0) {
            target_height = l_HIO.mFloat0x28;
        } else {
            target_height = l_HIO.mFloat0x28 - l_HIO.mFloat0x24;
        }
        *mWeightPtr2 |= 1;
    } else {
        if (*mWeightPtr == 0) {
            target_height = l_HIO.mFloat0x28 - 0.5f * l_HIO.mFloat0x24;
        } else if (*mWeightPtr > 0) {
            target_height = l_HIO.mFloat0x28 - l_HIO.mFloat0x24;
        } else {
            target_height = l_HIO.mFloat0x28;
        }
        *mWeightPtr2 |= 2;
    }

    if (*mWeightPtr2 == 3) {
        *mWeightPtr = 0;
        *mWeightPtr2 = 0;
    }

    cXyz vec(mRightPos.x, 0.0f, mRightPos.z);
    f32 mag = PSVECSquareMag(&vec);
    f32 diff = target_height * target_height - mag;
    diff = std::sqrtf(diff);

    mVelocity += 0.005f * (diff - mCurrentY);
    mVelocity *= 0.92f;
    mCurrentY += mVelocity;

    cXyz diff2 = mSpringPos - mRightPos;
    PSVECScale(&diff2, &diff2, l_HIO.mFloat0x20);
    PSVECAdd(&mTarget, &diff2, &mTarget);
    PSVECScale(&mTarget, &mTarget, l_HIO.mFloat0x1C);
    PSVECAdd(&mRightPos, &mTarget, &mRightPos);

    if (std::fabsf((f32)(mVelocity > 1.0f)) != 0.0f) {
        JAIZelBasic::zel_basic->seStart(0x3024, &current.pos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
    }
}

/* 00000984-000009A4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daBalancelift_c*)i_this)->CreateHeap();
}

/* 000009A4-00000BA0       .text CreateHeap__15daBalancelift_cFv */
BOOL daBalancelift_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, 4);
    JUT_ASSERT(419, modelData != 0);

    M_mdl = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    JUT_ASSERT(421, M_mdl != 0);

    m_chain = dChain_packet_create(3, &tevStr, 2.0f);
    JUT_ASSERT(423, m_chain != 0);

    pm_bgw = new dBgW();
    pm_bgw->Set((cBgD_t*)dComIfG_getObjectRes(M_arcname, 7), cBgW::MOVE_BG_e, &mBgMtx);
    pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);
    JUT_ASSERT(432, pm_bgw != 0);

    return M_mdl != 0 && m_chain != 0 && pm_bgw != 0;
}

/* 00000BA0-00000F34       .text CreateInit__15daBalancelift_cFv */
cPhs_State daBalancelift_c::CreateInit() {
    /* Nonmatching */
    u8 pathIdx = fopAcM_GetParam(this) >> 16;
    if (pathIdx != 0xFF) {
        mPath = dPath_GetRoomPath(pathIdx, current.roomNo);
        if (mPath != NULL && mPath->m_num > 0) {
            current.pos = mPath->m_points[0].m_position;
            home.pos = current.pos;

            if (mPath->m_num > 1) {
                cXyz child_pos = mPath->m_points[1].m_position;
                fpc_ProcID child_id = fopAcM_createChild(fpcNm_Balancelift_e, fopAcM_GetID(this), -1,
                                                         &child_pos, tevStr.mRoomNo,
                                                         NULL, NULL, -1);
                parentActorID = child_id;
            }
        }

        mLeftWeight = 0;
        mDir = 0;
        mWeightPtr = &mLeftWeight;
        mRightWeight = 0;
        mWeightPtr2 = &mRightWeight;
        mCurrentY = l_HIO.mFloat0x28 - 0.5f * l_HIO.mFloat0x24;
    } else {
        mLeftWeight = 0;
        mRightWeight = 0;

        fpc_ProcID parent_id = parentActorID;
        if (parent_id != fpcM_ERROR_PROCESS_ID_e) {
            fopAc_ac_c* parent_actor = fopAcM_SearchByID(parent_id);
            if (parent_actor != NULL) {
                mDir = 1;
                mWeightPtr = &((daBalancelift_c*)parent_actor)->mLeftWeight;
                mWeightPtr2 = &((daBalancelift_c*)parent_actor)->mRightWeight;
            } else {
                mDir = 0;
                mWeightPtr = &mLeftWeight;
                mWeightPtr2 = &mRightWeight;
            }
        } else {
            mDir = 0;
            mWeightPtr = &mLeftWeight;
            mWeightPtr2 = &mRightWeight;
        }
        mCurrentY = l_HIO.mFloat0x28 - 0.5f * l_HIO.mFloat0x24;
    }

    mVelocity = 0.0f;
    dComIfG_Bgsp()->Regist(pm_bgw, this);

    mOldPos = current.pos;
    mOldPos.y -= mCurrentY;
    mOffset = cXyz::Zero;
    mTarget = cXyz::Zero;
    mRightPos = cXyz::Zero;
    mSpringPos = cXyz::Zero;
    mQuatL = ZeroQuat;
    mQuatR = ZeroQuat;
    scale.set(2.0f, 2.0f, 2.0f);

    set_mtx();
    pm_bgw->SetRideCallback(ride_call_back);

    mStts.Init(0xC0, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.OnTgShield();
    mCyl.OnTgNoConHit();

    if (l_HIO.mChildIdx < 0) {
        l_HIO.mChildIdx = mDoHIO_createChild("\223V\224\211\203\212\203t\203g", &l_HIO);
    }

    return cPhs_COMPLEATE_e;
}

/* 00000F34-000010E0       .text daBalanceliftCreate__FPv */
static cPhs_State daBalanceliftCreate(void* i_this) {
    /* Nonmatching */
    daBalancelift_c* a_this = (daBalancelift_c*)i_this;
    fopAcM_ct(a_this, daBalancelift_c);

    cPhs_State phase_state = dComIfG_resLoad(&a_this->mPhase, daBalancelift_c::M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(a_this, CheckCreateHeap, 0xE40)) {
            phase_state = a_this->CreateInit();
            fopAcM_SetMtx(a_this, a_this->M_mdl->getBaseTRMtx());
            fopAcM_setCullSizeBox(a_this, -150.0f, -150.0f, -150.0f, 150.0f, 1000.0f, 150.0f);
            PSMTXCopy(a_this->M_mdl->getBaseTRMtx(), a_this->mBgMtx);
        } else {
            phase_state = cPhs_ERROR_e;
        }
    }

    return phase_state;
}

/* 0000129C-00001318       .text daBalanceliftDelete__FPv */
static BOOL daBalanceliftDelete(void* i_this) {
    daBalancelift_c* a_this = (daBalancelift_c*)i_this;
    dComIfG_Bgsp()->Release(a_this->pm_bgw);
    dComIfG_resDelete(&a_this->mPhase, daBalancelift_c::M_arcname);

    if (l_HIO.mChildIdx >= 0) {
        mDoHIO_deleteChild(l_HIO.mChildIdx);
        l_HIO.mChildIdx = -1;
    }

    return TRUE;
}

/* 00001318-0000133C       .text daBalanceliftExecute__FPv */
static BOOL daBalanceliftExecute(void* i_this) {
    return ((daBalancelift_c*)i_this)->_execute();
}

/* 0000133C-000016F0       .text _execute__15daBalancelift_cFv */
bool daBalancelift_c::_execute() {
    /* Nonmatching */
    calc_weight();
    calc_quat();
    set_mtx();
    pm_bgw->Move();
    mStts.Move();

    if (mCyl.ChkTgHit()) {
        fopAc_ac_c* hit_actor = mCyl.GetTgHitAc();
        cCcD_Obj* hit_obj = mCyl.GetTgHitObj();

        if (hit_actor != NULL && fopAc_IsActor(hit_actor) && fopAcM_GetProfName(hit_actor) == fpcNm_BOMB_e) {
            cXyz pan_pos = mPos;
            pan_pos.y -= 50.0f;
            cXyz dir = pan_pos - hit_actor->current.pos;
            if (dir.normalizeRS() == 0) {
                dir = cXyz(0.0f, 0.0f, 1.0f);
            }

            cXyz push = dir * -20.0f;
            PSVECAdd(&mOffset, &push, &mOffset);
            mVelocity += 440.0f * -dir.y;
        } else if (hit_obj != NULL) {
            cXyz dir = *mCyl.GetTgRVecP();
            if (dir.normalizeRS() == 0) {
                dir = cXyz(0.0f, 0.0f, 1.0f);
            }

            if (hit_obj->GetObjAt().GetType() & AT_TYPE_WIND) {
                cXyz push = dir * -12.0f;
                PSVECAdd(&mOffset, &push, &mOffset);
                mVelocity += 440.0f * -dir.y;
            } else if (hit_obj->GetObjAt().GetType() & AT_TYPE_SWORD) {
                cXyz push = dir * -8.0f;
                PSVECAdd(&mOffset, &push, &mOffset);
                mVelocity += 440.0f * -dir.y;

                cXyz* hit_pos = mCyl.GetTgHitPosP();
                if (hit_pos != NULL) {
                    cXyz dist = *hit_pos - mPos;
                    f32 dist_mag = PSVECSquareMag(&dist);
                    f32 d = dist_mag > 0.0f ? std::sqrtf(dist_mag) : dist_mag;

                    cXyz push2 = dir * l_HIO.mFloat0x18;
                    PSVECAdd(&mTarget, &push2, &mTarget);
                    mSpringPos.y = d;
                    mRightPos.y = d;

                    g_dComIfG_gameInfo.play.getParticle()->set(0, 0xC, hit_pos, NULL, NULL, 0xFF, NULL, -1,
                                                                NULL, NULL, NULL);
                }

                JAIZelBasic::zel_basic->seStart(0x6817, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            }
        }
    }

    mCyl.SetC(mPos);
    g_dComIfG_gameInfo.play.mCcS.Set(&mCyl);
    return false;
}

/* 000016F0-00001774       .text daBalanceliftDraw__FPv */
static BOOL daBalanceliftDraw(void* i_this) {
    /* Nonmatching */
    daBalancelift_c* a_this = (daBalancelift_c*)i_this;
    dKy_tevstr_c* tev = &a_this->tevStr;
    g_env_light.settingTevStruct(0, &a_this->current.pos, tev);
    g_env_light.setLightTevColorType(a_this->M_mdl, tev);
    mDoExt_modelUpdateDL(a_this->M_mdl);
    j3dSys.getDrawBuffer(0)->entryImm(a_this->m_chain, 0);
    return TRUE;
}

/* 00001774-0000177C       .text daBalanceliftIsDelete__FPv */
static BOOL daBalanceliftIsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daBalanceliftMethodTable = {
    (process_method_func)daBalanceliftCreate,
    (process_method_func)daBalanceliftDelete,
    (process_method_func)daBalanceliftExecute,
    (process_method_func)daBalanceliftIsDelete,
    (process_method_func)daBalanceliftDraw,
};

actor_process_profile_definition g_profile_Balancelift = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Balancelift_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBalancelift_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Balancelift_e,
    /* Actor SubMtd */ &daBalanceliftMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
