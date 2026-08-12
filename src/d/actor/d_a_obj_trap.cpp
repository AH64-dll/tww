/**
 * d_a_obj_trap.cpp
 * Enemy - Blade Trap (normal)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_trap.h"
#include "res/Object/Trap.h"
#include "d/d_a_obj.h"
#include "d/actor/d_a_obj_movebox.h"
#include "d/d_bg_s.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "f_op/f_op_actor_mng.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "math.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_math.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

static dCcD_SrcCyl l_daObjTrap_cyl_data = {
    // dCcD_SrcGObjInf
    {
        // cCcD_SrcObj
        {
            /* Flags             */ 0,
            // cCcD_SrcObjHitInf
            {
                // cCcD_SrcObjAt
                {
                    /* Type */ AT_TYPE_SPIKE,
                    /* Atp  */ 0x01,
                    /* SPrm */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
                },
                // cCcD_SrcObjTg
                {
                    /* Type */ 0,
                    /* SPrm */ 0,
                },
                // cCcD_SrcObjCo
                {
                    /* SPrm */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e |
                               cCcD_CoSPrm_VsGrpAll_e,
                },
            },
        },
        // dCcD_SrcGObjAt
        {
            /* Se      */ dCcG_SE_NONE,
            /* HitMark */ dCcG_AtHitMark_None_e,
            /* Spl     */ dCcG_At_Spl_UNK1,
            /* Mtrl    */ 0,
            /* SPrm    */ 0,
        },
        // dCcD_SrcGObjTg
        {
            /* Se      */ dCcG_SE_NONE,
            /* HitMark */ dCcG_TgHitMark_None_e,
            /* Spl     */ dCcG_Tg_Spl_UNK0,
            /* Mtrl    */ 0,
            /* SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        },
        // dCcD_SrcGObjCo
        {
            /* SPrm */ 0,
        },
    },
    // cCcD_SrcCylAttr
    {{
        /* Center */ {0.0f, -40.0f, 0.0f},
        /* Radius */ 155.0f,
        /* Height */ 100.0f,
    }},
};

const f32 daObjTrap_c::M_speed_table[] = {50.0f, 80.0f, 100.0f};
const s16 daObjTrap_c::M_wait_f_table[] = {30, 10, 0};
const char daObjTrap_c::M_arcname[] = "Trap";

/* 000000EC-0000010C       .text solidHeapCB__11daObjTrap_cFP10fopAc_ac_c */
int daObjTrap_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjTrap_c*)i_this)->create_heap();
}

/* 0000010C-000002A4       .text create_heap__11daObjTrap_cFv */
int daObjTrap_c::create_heap() {
    int ret = 0;

    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_TRAP_BDL_HTORA1_e);
    JUT_ASSERT(0x163, mdl_data != NULL);
    if (mdl_data) {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000222);
        if (mpModel) {
            J3DAnmTextureSRTKey* btk_data = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_TRAP_BTK_HTORA1_e);
            JUT_ASSERT(0x16c, btk_data != NULL);
            if (btk_data) {
                if (mBtk.init(mdl_data, btk_data, TRUE, 0)) {
                    cBgD_t* bgd = (cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_TRAP_DZB_HTORA1_e);
                    mpBgW = dBgW_NewSet(bgd, cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx());
                    if (mpBgW) {
                        ret = 1;
                    }
                }
            }
        }
    }
    return ret;
}

/* 000002A4-00000510       .text _create__11daObjTrap_cFv */
cPhs_State daObjTrap_c::_create() {
    fopAcM_ct(this, daObjTrap_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        ret = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            mParam = fopAcM_GetParam(this) & 0xFF;
            if (mParam != 0xFF) {
                mpPath = dPath_GetRoomPath(mParam, current.roomNo);
                if (mpPath && mpPath->m_points) {
                    mSpeedIdx = (fopAcM_GetParam(this) >> 20) & 0xF;
                    if (mSpeedIdx == 0xF) {
                        mSpeedIdx = 0;
                    }
                    mSpeed = M_speed_table[mSpeedIdx];
                    mWait = M_wait_f_table[mSpeedIdx];
                    current.pos.x = mpPath->m_points[0].m_position.x;
                    current.pos.z = mpPath->m_points[0].m_position.z;
                    set_move_info();
                    mDist = (mPathPosA - mPathPosB).absXZ();
                    mCurPos = current.pos;
                    init_mtx();
                    mStts.Init(0, 0xFF, this);
                    mCyl.SetStts(&mStts);
                    mCyl.Set(l_daObjTrap_cyl_data);
                    set_co_pos();
                    dComIfG_Bgsp()->Regist(mpBgW, this);
                    get_ground();
                    ret = cPhs_COMPLEATE_e;
                } else {
                    mParam = 0xFF;
                    ret = cPhs_ERROR_e;
                }
            }
        }
    }
    return ret;
}

/* 00000DF0-00000E84       .text _delete__11daObjTrap_cFv */
bool daObjTrap_c::_delete() {
    if (heap && mpBgW) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }
        mpBgW = NULL;
    }
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 00000E84-00000F20       .text init_mtx__11daObjTrap_cFv */
void daObjTrap_c::init_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 00000F20-00000F70       .text set_co_pos__11daObjTrap_cFv */
void daObjTrap_c::set_co_pos() {
    cXyz pos = current.pos;
    pos.y -= 40.0f;
    mCyl.SetC(pos);
}

/* 00000F70-00000FF4       .text get_ground__11daObjTrap_cFv */
void daObjTrap_c::get_ground() {
    cXyz pos(current.pos.x, current.pos.y + 50.0f, current.pos.z);
    mGndChk.SetPos(&pos);
    mGndChk.SetActorPid(fopAcM_GetID(this));
    mGroundY = dComIfG_Bgsp()->GroundCross(&mGndChk);
}

/* 00000FF4-0000112C       .text circle_search__11daObjTrap_cFv */
bool daObjTrap_c::circle_search() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz diff = player->current.pos - current.pos;
    f32 dist = PSVECSquareMag((Vec*)&cXyz(diff.x, 0.0f, diff.z));
    dist = std::sqrtf(dist);
    return dist <= 400.0f && mDirValid == 1 && mDir.x * diff.x + mDir.z * diff.z >= 0.0f;
}

/* 0000112C-0000122C       .text set_move_info__11daObjTrap_cFv */
void daObjTrap_c::set_move_info() {
    dPnt* pnt = &mpPath->m_points[mPathIdx];
    mPathPosB.set(pnt->m_position.x, current.pos.y, pnt->m_position.z);
    dPnt* pnt2 = &mpPath->m_points[(mPathIdx + 1) & 1];
    mPathPosA.set(pnt2->m_position.x, current.pos.y, pnt2->m_position.z);
    mDir = mPathPosA - mPathPosB;
    mDirValid = mDir.normalizeRS();
    mSpeedVec = cXyz::Zero;
    mTargetPos = mDir * 100.0f;
}

/* 0000122C-000013E4       .text check_arrival__11daObjTrap_cFv */
bool daObjTrap_c::check_arrival() {
    cXyz d1 = mCurPos - mPathPosB;
    cXyz d2 = mPathPosA - mPathPosB;
    f32 mag1 = PSVECSquareMag((Vec*)&cXyz(d1.x, 0.0f, d1.z));
    mag1 = std::sqrtf(mag1);
    f32 mag2 = PSVECSquareMag((Vec*)&cXyz(d2.x, 0.0f, d2.z));
    mag2 = std::sqrtf(mag2);
    return mag1 >= mag2;
}

/* 000013E4-000018E4       .text check_wall__11daObjTrap_cFv */
cXyz daObjTrap_c::check_wall() {
    static dBgS_ObjLinChk l_wall_work;
    static const s16 angleY[] = {0x0000, 0x4000, 0xC000};
    static const f32 transA[] = {0.0f, 145.0f, 145.0f};

    cXyz spB8 = mDir * 150.0f;
    cXyz spAC;
    cXyz spA0;
    cXyz sp94;
    cXyz sp88;
    cXyz sp7C = cXyz::BaseY * 75.0f;
    cXyz ret = cXyz::Zero;

    for (int i = 0; i < 3; i++) {
        mDoMtx_stack_c::YrotS(angleY[i]);
        mDoMtx_stack_c::multVec(&mDir, &sp88);
        sp88 *= transA[i];
        sp88 += sp7C;
        spAC = current.pos + sp88;
        spA0 = spAC + mSpeedVec;
        spA0 += spB8;
        l_wall_work.Set(&spAC, &spA0, this);
        l_wall_work.SetActorPid(fopAcM_GetID(this));
        if (dComIfG_Bgsp()->LineCross(&l_wall_work)) {
            sp94 = l_wall_work.GetCross();
            PSVECSubtract(&sp94, &spAC, &sp94);
            if (ret == cXyz::Zero) {
                goto update_ret;
            }
            {
                f32 retDist = PSVECSquareMag((Vec*)&cXyz(ret.x, 0.0f, ret.z));
                retDist = std::sqrtf(retDist);
                f32 sp94Dist = PSVECSquareMag((Vec*)&cXyz(sp94.x, 0.0f, sp94.z));
                sp94Dist = std::sqrtf(sp94Dist);
                if (retDist > sp94Dist) {
                    goto update_ret;
                }
            }
            goto done_update;
        update_ret:
            ret = sp94 + current.pos - spB8;
        done_update:
            ;
        }
    }
    return ret;
}

/* 00001C88-00001D7C       .text check_block_target_pos__11daObjTrap_cFP4cXyz */
BOOL daObjTrap_c::check_block_target_pos(cXyz* i_targetPos) {
    cXyz diff = *i_targetPos - current.pos;
    f32 dot = mDir.x * diff.x + mDir.z * diff.z;
    BOOL ret = FALSE;
    if (dot >= 0.0f && dot < 150.0f + mDist) {
        mDoMtx_stack_c::YrotS(0x4000);
        cXyz rot;
        mDoMtx_stack_c::multVec(&mDir, &rot);
        f32 dot2 = rot.x * diff.x + rot.z * diff.z;
        if (std::fabsf(dot2) < 225.0f) {
            ret = TRUE;
        }
    }
    return ret;
}

/* 00001D7C-000023D4       .text check_block__11daObjTrap_cF4cXyz */
cXyz daObjTrap_c::check_block(cXyz i_blockPos) {
    static dBgS_ObjLinChk l_block_work;
    static s16 angleY[] = {0x4000, 0xC000};

    cXyz sp100 = mDir * 150.0f;
    cXyz spF4;
    cXyz spE8;
    cXyz spDC;
    cXyz spD0;
    cXyz ret = i_blockPos;
    cXyz sp58;
    cXyz spAC = cXyz::BaseY * 75.0f;

    for (int i = 0; i < 2; i++) {
        mDoMtx_stack_c::YrotS(angleY[i]);
        mDoMtx_stack_c::multVec(&mDir, &spD0);
        spD0 *= 153.0f;
        spD0 += spAC;
        spF4 = current.pos + spD0;
        spE8 = spF4 + mSpeedVec;
        spE8 += sp100;
        l_block_work.Set(&spF4, &spE8, this);
        l_block_work.SetActorPid(fopAcM_GetID(this));
        if (dComIfG_Bgsp()->LineCross(&l_block_work)) {
            fopAc_ac_c* hitActor = dComIfG_Bgsp()->GetActorPointer(l_block_work);
            if (hitActor && fopAc_IsActor(hitActor) && fopAcM_GetName(hitActor) == fpcNm_Obj_Movebox_e) {
                bool isBlocked;
                daObjMovebox::Act_c* movebox = (daObjMovebox::Act_c*)hitActor;
                cXyz sp58;
                if (movebox->mMode == 1) {
                    mDoMtx_stack_c::push();
                    mDoMtx_stack_c::YrotS(movebox->home.angle.y);
                    mDoMtx_stack_c::transM((f32)movebox->m628, 0.0f, (f32)movebox->m62C);
                    cXyz sp28(mDoMtx_stack_c::get()[0][3], mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);
                    mDoMtx_stack_c::YrotS((s16)(movebox->home.angle.y + daObjMovebox::Act_c::M_dir_base[movebox->m634]));
                    cXyz sp34;
                    mDoMtx_stack_c::multVecSR(&cXyz::BaseZ, &sp34);
                    mDoMtx_stack_c::pop();
                    sp58 = ((sp28 + sp34) * 75.0f) + movebox->home.pos;
                    isBlocked = true;
                } else {
                    isBlocked = false;
                }
                if (isBlocked) {
                    if (check_block_target_pos(&sp58)) {
                        spDC = l_block_work.GetCross();
                        PSVECSubtract(&spDC, &spF4, &spDC);
                        if (ret == cXyz::Zero) {
                            goto update_ret;
                        }
                        {
                            f32 retDist = PSVECSquareMag((Vec*)&cXyz(ret.x, 0.0f, ret.z));
                            retDist = std::sqrtf(retDist);
                            f32 spDC2Dist = PSVECSquareMag((Vec*)&cXyz(spDC.x, 0.0f, spDC.z));
                            spDC2Dist = std::sqrtf(spDC2Dist);
                            if (retDist > spDC2Dist) {
                                goto update_ret;
                            }
                        }
                        goto done_update;
                    update_ret:
                        ret = spDC + current.pos - sp100;
                    done_update:
                        ;
                    }
                }
            }
        }
    }
    return ret;
}

/* 000023D4-0000250C       .text set_vib_mode__11daObjTrap_cFv */
void daObjTrap_c::set_vib_mode() {
    mAngleY = shape_angle.x;
    mVibTimer = 6;
    mVibF = 35.0f;
    mBoundTimer = 0x10;
    mVibPos = cXyz::Zero;
    mVibMode = 2;

    cXyz pos = mDir * 150.0f;
    PSVECAdd(&pos, &current.pos, &pos);
    cXyz dir = mDir * -1.0f;
    pos.y += 50.0f;
    daObj::HitEff_hibana(&pos, &dir);

    if (mVibTimer) {
        vibrate();
        mVibTimer--;
    }
    if (mBoundTimer) {
        bound();
        mBoundTimer--;
    }
}

/* 0000250C-0000255C       .text vibrate__11daObjTrap_cFv */
void daObjTrap_c::vibrate() {
    f32 fVar = jmaSinTable[(u16)(mVibTimer * 0x5555) >> jmaSinShift];
    shape_angle.x = (s16)(288.0f * fVar);
}

/* 0000255C-00002678       .text bound__11daObjTrap_cFv */
void daObjTrap_c::bound() {
    cXyz sp14 = mDir * -1.0f;
    PSVECSubtract(&mCurPos, &mVibPos, &mCurPos);
    f32 vibF = mVibF;
    f32 f = std::fabsf((f32)(s16)(vibF * cM_ssin((mBoundTimer & 3) << 14)));
    PSVECScale(&sp14, &sp14, f);
    PSVECAdd(&mCurPos, &sp14, &mCurPos);
    mVibPos = sp14;
    cLib_addCalc(&mVibF, 0.0f, 0.17f, 35.0f, 1.0f);
}

/* 00002678-0000270C       .text set_shine__11daObjTrap_cFv */
void daObjTrap_c::set_shine() {
    mShineFlag = 1;
    if (PSVECDotProduct(&cXyz::BaseX, &mDir) >= 0.0f) {
        mBtk.setFrame(35.0f);
        mBtk.setPlaySpeed(1.0f);
    } else {
        mBtk.setFrame(46.0f);
        mBtk.setPlaySpeed(-1.0f);
    }
}

/* 0000270C-00002758       .text shine_move__11daObjTrap_cFv */
void daObjTrap_c::shine_move() {
    if (mShineFlag == 1) {
        if (mBtk.play()) {
            mShineFlag = 0;
        }
    }
}

/* 00002758-00002CB0       .text _execute__11daObjTrap_cFv */
bool daObjTrap_c::_execute() {
    mCurPos = current.pos;

    switch (mVibMode) {
    case 0: {
        int chase = cLib_chasePosXZ(&mCurPos, mPathPosA, mSpeed);
        mSpeedVec = mCurPos - current.pos;
        cXyz wall = check_wall();
        cXyz block = check_block(wall);
        if (block != cXyz::Zero) {
            mCurPos = block;
            set_vib_mode();
            set_shine();
            JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_WDUN_TRAP_STOP, &current.pos, 0,
                                                 dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else if (chase == 1) {
            set_vib_mode();
            set_shine();
            JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_WDUN_TRAP_STOP, &current.pos, 0,
                                                 dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else if (circle_search()) {
            mVibMode = 1;
        } else {
            JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_WDUN_TRAP_MOVE, &current.pos, 0,
                                                 dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        break;
    }
    case 1: {
        cLib_addCalcPosXZ(&mSpeedVec, mTargetPos, 0.06f, 100.0f, 1.0f);
        PSVECAdd(&mCurPos, &mSpeedVec, &mCurPos);
        cXyz wall = check_wall();
        cXyz block = check_block(wall);
        if (block != cXyz::Zero) {
            mCurPos = block;
            set_vib_mode();
            set_shine();
            JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_WDUN_TRAP_STOP, &current.pos, 0,
                                                 dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else if (check_arrival()) {
            mCurPos = mPathPosA;
            set_vib_mode();
            set_shine();
            JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_WDUN_TRAP_STOP, &current.pos, 0,
                                                 dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_WDUN_TRAP_MOVE, &current.pos, 0,
                                                 dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        break;
    }
    case 2:
        if (mVibTimer) {
            vibrate();
            mVibTimer--;
        }
        if (mBoundTimer) {
            bound();
            mBoundTimer--;
        }
        if (mVibTimer == 0) {
            shape_angle.y = mAngleY;
            if (mBoundTimer == 0) {
                mWaitTimer = mWait;
                mVibMode = 3;
            }
        }
        break;
    case 3:
        if (mWaitTimer > 0) {
            mWaitTimer--;
        }
        if (mWaitTimer == 0) {
            mPathIdx = (mPathIdx + 1) & 1;
            set_move_info();
            mVibMode = 0;
        }
        break;
    }

    current.pos = mCurPos;
    shine_move();
    get_ground();
    init_mtx();
    set_co_pos();
    dComIfG_Ccsp()->Set(&mCyl);

    if (heap && mpBgW && mpBgW->ChkUsed()) {
        mpBgW->Move();
    }
    return true;
}

/* 00002CB0-00002D54       .text _draw__11daObjTrap_cFv */
bool daObjTrap_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mBtk.entry(mpModel->getModelData(), mBtk.getFrame());
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setSimpleShadow2(&current.pos, mGroundY, 150.0f, mGndChk, 0, 1.0f,
                              &dDlst_shadowControl_c::mSimpleTexObj);
    return true;
}

namespace {
/* 00002D54-00002D74       .text Mthd_Create__26@unnamed@d_a_obj_trap_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjTrap_c*)i_this)->_create();
}

/* 00002D74-00002D98       .text Mthd_Delete__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjTrap_c*)i_this)->_delete();
}

/* 00002D98-00002DBC       .text Mthd_Execute__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjTrap_c*)i_this)->_execute();
}

/* 00002DBC-00002DE0       .text Mthd_Draw__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjTrap_c*)i_this)->_draw();
}

/* 00002DE0-00002DE8       .text Mthd_IsDelete__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Trap_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Trap = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Trap_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTrap_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Trap_e,
    /* Actor SubMtd */ &Trap_Mthd_Table,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
