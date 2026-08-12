/**
 * d_a_klft.cpp
 * Object - Forbidden Woods - Lift (moving wooden platform)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_klft.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_controller_pad.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/d_path.h"
#include "d/d_s_play.h"
#include "f_op/f_op_actor_mng.h"

static cXyz* wind_vec;
static s16 wy;
static f32* wp;

/* 00000078-00000374       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c* i_ac, fopAc_ac_c* i_pt) {
    klft_class* pActor = static_cast<klft_class*>(i_ac);

    cXyz delta_pos, local_44, local_50;
    cMtx_YrotS(*calc_mtx, -pActor->current.angle.y);
    delta_pos = i_pt->current.pos - pActor->mPos;
    MtxPosition(&delta_pos, &local_44);
    delta_pos = i_pt->old.pos - pActor->mPos;
    MtxPosition(&delta_pos, &local_50);
    if (fopAcM_GetName(i_pt) == fpcNm_PLAYER_e) {
        pActor->field_9EC = 10;
    }
    pActor->field_3BC = -50.0f;
    f32 f4 = std::sqrtf(local_44.x * local_44.x + local_44.z * local_44.z);
    s16 zAngle_target = f4 * ((REG0_F(0) + 30.0f) / pActor->scale.z);
    cLib_addCalcAngleS2(&pActor->mAngleZ, zAngle_target, 10, 0x800);
    cLib_addCalcAngleS2(&pActor->mAngleX, cM_atan2s(local_44.x, local_44.z), 2, 0x2000);
    if ((std::abs(g_mDoCPd_cpadInfo[0].mMainStickPosX) + std::abs(g_mDoCPd_cpadInfo[0].mMainStickPosY) > 0.1f) ||
        (std::abs(pActor->field_3C4) > 0.0001f)) {
        f32 fVar1 = (REG0_F(4) + 100.0f) * std::abs(local_50.z - local_44.z);
        if (fVar1 > (REG0_F(6) + 200.0f)) {
            pActor->field_2E8.x = fVar1;
        }
        fVar1 = (REG0_F(4) + 100.0f) * std::abs(local_44.x - local_50.x);
        if (fVar1 > (REG0_F(6) + 200.0f)) {
            pActor->field_2E8.z = fVar1;
        }
        fVar1 = (REG0_F(8) + 2.0f) * std::abs(local_44.x - local_50.x);
        if (fVar1 > 10.0f && pActor->field_2D0 < fVar1) {
            pActor->field_2DC.x = fVar1;
        }
        fVar1 = (REG0_F(8) + 2.0f) * std::abs(local_50.z - local_44.z);
        if (fVar1 > 10.0f && pActor->field_2D8 < fVar1) {
            pActor->field_2DC.z = fVar1;
        }
    }
}

/* 000003B0-0000046C       .text nodeCallBack_main__FP7J3DNodei */
static BOOL nodeCallBack_main(J3DNode* i_node, int i_calcType) {
    if (i_calcType == 0) {
        int jnt_no = ((J3DJoint*)i_node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        klft_class* pActor = (klft_class*)model->getUserArea();
        if (pActor != NULL && jnt_no == 1) {
            MTXCopy(model->getAnmMtx(jnt_no), *calc_mtx);
            cMtx_XrotM(*calc_mtx, pActor->field_3B0);
            model->setAnmMtx(jnt_no, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 0000046C-00000520       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* i_node, int i_calcType) {
    if (i_calcType == 0) {
        int jnt_no = ((J3DJoint*)i_node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        klft_class* pActor = (klft_class*)model->getUserArea();
        if (pActor != NULL && jnt_no == 1) {
            MTXCopy(model->getAnmMtx(jnt_no), *calc_mtx);
            cMtx_YrotM(*calc_mtx, pActor->mRotY);
            model->setAnmMtx(jnt_no, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000520-000005A0       .text himo_Draw__FP10klft_class */
void himo_Draw(klft_class* i_this) {
    i_this->mLineMat.update(0x14, (GXColor){150, 150, 150, 255}, &i_this->tevStr);
    dComIfGd_set3DlineMat(&i_this->mLineMat);
}

/* 000005A0-00000688       .text daKlft_Draw__FP10klft_class */
static BOOL daKlft_Draw(klft_class* i_this) {
    dKy_getEnvlight().settingTevStruct(TEV_TYPE_BG0, &i_this->current.pos, &i_this->tevStr);
    dKy_getEnvlight().setLightTevColorType(i_this->mModel, &i_this->tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(i_this->mModel);
    dComIfGd_setList();
    himo_Draw(i_this);
    for (int i = 0; i < 2; i++) {
        g_env_light.setLightTevColorType(i_this->mMorf[i]->getModel(), &i_this->tevStr);
        i_this->mMorf[i]->updateDL();
    }
    return TRUE;
}

/* 00000688-00000F24       .text klft_move__FP10klft_class */
void klft_move(klft_class* i_this) {
    fopAc_ac_c* actor = static_cast<fopAc_ac_c*>(i_this);
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    i_this->mMoveCounter++;
    s16 playerAngle;
    f32 moveSpeed;
    if (i_this->field_9EC != 0) {
        playerAngle = player->shape_angle.y;
        moveSpeed = 1.0f;
    } else {
        playerAngle = player->shape_angle.y + 0x8000;
        moveSpeed = 0.5f;
    }
    f32 f30 = 0.01f;
    f32 sinAngle;
    if (i_this->mSph.ChkTgHit() != 0 || i_this->mSph2[0].ChkTgHit() != 0 || i_this->mSph2[1].ChkTgHit() != 0) {
        cXyz sp4C;
        cXyz sp40;
        if (i_this->mSph.ChkTgHit() != 0) {
            cMtx_YrotS(*calc_mtx, playerAngle - i_this->current.angle.y);
            sp4C.z = (0.5f + REG0_F(13)) * moveSpeed;
        } else {
            if (i_this->mSph2[0].ChkTgHit() != 0) {
                cMtx_YrotS(*calc_mtx, -0x8000);
            } else {
                cMtx_YrotS(*calc_mtx, 0);
            }
            sp4C.z = (0.85f + REG0_F(16)) * moveSpeed;
            f30 = 0.1f;
        }
        sp4C.x = 0.0f;
        sp4C.y = 0.0f;
        MtxPosition(&sp4C, &sp40);
        i_this->field_3C8 = sp40.z;
        sp4C.set((500.0f + REG0_F(15)) * moveSpeed, 0.0f, 0.0f);
        MtxPosition(&sp4C, &i_this->field_2E8);
        i_this->field_3B2 = REG0_S(5) + 0x3C;
        cMtx_YrotS(*calc_mtx, playerAngle);
        sp4C.x = 0.0f;
        sp4C.y = 0.0f;
        sp4C.z = (20.0f + REG0_F(16)) * moveSpeed;
        MtxPosition(&sp4C, &i_this->field_2DC);
    }
    if (i_this->field_3B2 == 0x28) {
        mDoAud_seStart(JA_SE_OBJ_KASSHA_LIFT_SWING, &i_this->current.pos, 0,
                       dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    }
    cLib_addCalc2(&i_this->field_3C4, i_this->field_3C8, 1.0f, f30);
    cLib_addCalc0(&i_this->field_3C8, 1.0f, 0.001f + REG0_F(14));
    i_this->field_3C0 += i_this->field_3C4;
    if (i_this->field_3C0 > 80.0f) {
        i_this->field_3C0 = 80.0f;
        i_this->field_3C4 = 0.0f;
    } else if (i_this->field_3C0 < 20.0f) {
        i_this->field_3C0 = 20.0f;
        i_this->field_3C4 = 0.0f;
    }
    i_this->field_3B0 += (s16)(-2500.0f * i_this->field_3C4);
    if (std::abs(i_this->field_3C4) > 0.01f) {
        u32 volume = (u32)(std::abs(i_this->field_3C4) * (500.0f + REG0_F(0)));
        if (volume > 100) {
            volume = 100;
        }
        for (int i = 0; i < 2; i++) {
            mDoAud_seStart(JA_SE_OBJ_KM_WINDMILL, &i_this->mPath2[i], volume,
                           dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        i_this->field_3B4 += std::abs(i_this->field_3C4);
        if (i_this->field_3B4 > 3.0f + REG0_F(1)) {
            i_this->field_3B4 -= 3.0f + REG0_F(1);
            mDoAud_seStart(JA_SE_OBJ_KASSHA_LIFT_MOVE, &i_this->current.pos, volume,
                           dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
    }
    for (int i = 0; i < 2; i++) {
        if (i_this->mCyl[i].ChkTgHit() != 0) {
            def_se_set(actor, i_this->mCyl[i].GetTgHitObj(), 0xB);
        }
    }
    cLib_addCalcAngleS2(&i_this->mAngleZ, 0, 10, 0x200);
    cLib_addCalcAngleS2(&i_this->current.angle.x, 0, 10, 0x200);
    cLib_addCalcAngleS2(&i_this->current.angle.z, 0, 10, 0x200);
    i_this->field_300.x = (s16)(i_this->field_2F4 * cM_ssin(i_this->mMoveCounter * 0x5DC));
    i_this->field_300.z = (s16)(i_this->field_2FC * cM_ssin(i_this->mMoveCounter * 0x514));
    f32 f3;
    if (i_this->field_3B2 != 0) {
        f3 = 10.0f;
    } else if (std::abs(i_this->field_2E8.x) > 100.0f + REG0_F(2)) {
        f3 = 10.0f + REG0_F(4);
    } else {
        f3 = 2.0f + REG0_F(3);
    }
    cLib_addCalc2(&i_this->field_2F4, i_this->field_2E8.x, 1.0f, f3);
    if (i_this->field_3B2 != 0) {
        f3 = 40.0f;
    } else if (std::abs(i_this->field_2E8.z) > 100.0f + REG0_F(2)) {
        f3 = 10.0f + REG0_F(4);
    } else {
        f3 = 2.0f + REG0_F(3);
    }
    cLib_addCalc2(&i_this->field_2FC, i_this->field_2E8.z, 1.0f, f3);
    if (i_this->field_3B2 == 0) {
        i_this->field_2E8.z = 0.0f;
        i_this->field_2E8.x = 0.0f;
    }
    sinAngle = cM_ssin(cM_rad2s(3.1415927f * (0.01f * i_this->field_3C0)));
    i_this->mSwingPos.x = sinAngle * (i_this->field_2D0 * cM_ssin(i_this->mMoveCounter * 0x2EE));
    i_this->mSwingPos.z = sinAngle * (i_this->field_2D8 * cM_ssin(i_this->mMoveCounter * 0x384));
    i_this->mSwingPos.y = sinAngle * ((1.0f + REG0_F(1)) * ((i_this->field_2D0 + i_this->field_2D8) *
                          cM_ssin(i_this->mMoveCounter * 0x5DC)));
    if (i_this->field_3B2 != 0) {
        f3 = 10.0f;
    } else if (std::abs(i_this->field_2DC.x) > 10.0f) {
        f3 = 1.2f;
    } else {
        f3 = 0.25f;
    }
    cLib_addCalc2(&i_this->field_2D0, i_this->field_2DC.x, 1.0f, f3);
    if (i_this->field_3B2 != 0) {
        f3 = 10.0f;
    } else if (std::abs(i_this->field_2DC.z) > 10.0f) {
        f3 = 1.2f;
    } else {
        f3 = 0.25f;
    }
    cLib_addCalc2(&i_this->field_2D8, i_this->field_2DC.z, 1.0f, f3);
    if (i_this->field_3B2 == 0) {
        i_this->field_2DC.x = 0.0f;
        i_this->field_2DC.z = 0.0f;
    }
    i_this->shape_angle = i_this->current.angle + i_this->field_300;
    i_this->home.pos = i_this->mPath0[0] + (i_this->field_394 * i_this->field_3C0) * 0.01f;
    i_this->home.pos.y += (-100.0f + REG0_F(2)) + moveSpeed * (-100.0f + i_this->field_3B8 + REG0_F(0));
    cLib_addCalc2(&i_this->field_3B8, i_this->field_3BC, 0.1f, 25.0f);
    i_this->field_3BC = 0.0f;
    i_this->current.pos = i_this->home.pos + i_this->mSwingPos;
}

/* 00000F24-00001140       .text himo_move__FP10klft_class */
void himo_move(klft_class* i_this) {
    cXyz* linePos = i_this->mLineMat.getPos(0);
    u8* lineSize = i_this->mLineMat.getSize(0);
    cXyz delta1 = i_this->current.pos - i_this->mPath0[0];
    cXyz delta2 = i_this->current.pos - i_this->mPath0[1];
    delta1.y -= 25.0f;
    delta2.y -= 25.0f;
    for (int i = 0; i < 20; i++) {
        f32 t;
        if (i < 10) {
            t = (f32)i / 9.0f;
            *linePos = i_this->mPath0[0] + delta1 * t;
        } else {
            t = (f32)(19 - i) / 9.0f;
            *linePos = i_this->mPath0[1] + delta2 * t;
        }
        linePos->y += (REG0_F(7) + -20.0f) * cM_ssin(cM_rad2s(3.1415927f * t));
        *lineSize = 8;
        linePos++;
        lineSize++;
    }
}

/* 00001140-00001444       .text daKlft_Execute__FP10klft_class */
static BOOL daKlft_Execute(klft_class* i_this) {
    fopAc_ac_c* actor = static_cast<fopAc_ac_c*>(i_this);
    if (i_this->field_3B2 != 0) {
        i_this->field_3B2--;
    }
    if (i_this->field_9EC != 0) {
        i_this->field_9EC--;
    }
    wind_vec = dKyw_get_wind_vec();
    wy = cM_atan2s(wind_vec->x, wind_vec->z);
    wp = dKyw_get_wind_power();
    klft_move(i_this);
    himo_move(i_this);
    MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
    cMtx_YrotM(*calc_mtx, i_this->mAngleX);
    cMtx_XrotM(*calc_mtx, i_this->mAngleZ);
    cMtx_YrotM(*calc_mtx, -i_this->mAngleX);
    cMtx_XrotM(*calc_mtx, i_this->shape_angle.x);
    cMtx_ZrotM(*calc_mtx, i_this->shape_angle.z);
    i_this->mModel->setBaseTRMtx(*calc_mtx);
    PSMTXCopy(*calc_mtx, i_this->mMtx);
    MtxTrans(0.0f, REG0_F(7) - 400.0f, 0.0f, true);
    cXyz sp8;
    sp8.set(0.0f, 0.0f, 0.0f);
    MtxPosition(&sp8, &i_this->mPos);
    i_this->mStts.Move();
    i_this->mSph.SetC(i_this->mPos);
    dComIfG_Ccsp()->Set(&i_this->mSph);
    for (int i = 0; i < 2; i++) {
        cXyz pos = i_this->mPath2[i];
        pos.y += 35.0f + REG0_F(11);
        i_this->mSph2[i].SetC(pos);
        dComIfG_Ccsp()->Set(&i_this->mSph2[i]);
        i_this->mCyl[i].SetC(pos);
        dComIfG_Ccsp()->Set(&i_this->mCyl[i]);
    }
    i_this->pm_bgw->Move();
    i_this->mRotY += (s16)(i_this->field_3C4 * (8000.0f + REG0_F(8)));
    for (int i = 0; i < 2; i++) {
        MtxTrans(i_this->mPath2[i].x, i_this->mPath2[i].y, i_this->mPath2[i].z, false);
        i_this->mMorf[i]->getModel()->setBaseTRMtx(*calc_mtx);
    }
    return TRUE;
}

/* 00001444-0000144C       .text daKlft_IsDelete__FP10klft_class */
static BOOL daKlft_IsDelete(klft_class*) {
    return TRUE;
}

/* 0000144C-00001520       .text daKlft_Delete__FP10klft_class */
static BOOL daKlft_Delete(klft_class* i_this) {
    fopAc_ac_c* actor = static_cast<fopAc_ac_c*>(i_this);
    dComIfG_resDelete(&i_this->mPhs, "Klft");
    if (i_this->heap != NULL) {
        dComIfG_Bgsp()->Release(i_this->pm_bgw);
    }
    if (i_this->mShapeParam != 0) {
        if (i_this->field_3C0 >= 50.0f) {
            dComIfGs_onSwitch(i_this->mShapeParam, fopAcM_GetRoomNo(actor));
        } else {
            dComIfGs_offSwitch(i_this->mShapeParam, fopAcM_GetRoomNo(actor));
        }
    }
    mDoAud_seDeleteObject(&i_this->mPath2[0]);
    mDoAud_seDeleteObject(&i_this->mPath2[1]);
    return TRUE;
}

/* 00001520-000017C4       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_this) {
    klft_class* actor = static_cast<klft_class*>(i_this);
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Klft", 5);
    actor->mModel = mDoExt_J3DModel__create(modelData, 0, 0x110203);
    if (actor->mModel == NULL) {
        return FALSE;
    }
    actor->mModel->setUserArea((u32)i_this);
    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == 1) {
            modelData->getJointNodePointer(i)->setCallBack(nodeCallBack_main);
        }
    }
    actor->pm_bgw = new dBgW();
    JUT_ASSERT(0x343, actor->pm_bgw != 0);
    actor->pm_bgw->Set((cBgD_t*)dComIfG_getObjectRes("Klft", 9), 1, &actor->mMtx);
    actor->pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);
    actor->pm_bgw->SetRideCallback(ride_call_back);
    if (!actor->mLineMat.init(1, 0x14, (ResTIMG*)dComIfG_getObjectRes("Klft", 0xC), 1)) {
        return FALSE;
    }
    for (int i = 0; i < 2; i++) {
        actor->mMorf[i] = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("Klft", 6), NULL, NULL, NULL, 2, 1.0f, 0, -1, 0,
            NULL, 0, 0x110203);
        actor->mMorf[i]->getModel()->setUserArea((u32)i_this);
        J3DModelData* morfModelData = actor->mMorf[i]->getModel()->getModelData();
        for (u16 j = 0; j < morfModelData->getJointNum(); j++) {
            if (j == 3) {
                morfModelData->getJointNodePointer(j)->setCallBack(nodeCallBack);
            }
        }
    }
    return TRUE;
}

/* 000017C4-00001C78       .text daKlft_Create__FP10fopAc_ac_c */
static cPhs_State daKlft_Create(fopAc_ac_c* i_this) {
    static dCcD_SrcSph utiwa_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_WIND,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 250.0f,
        }},
    };
    static dCcD_SrcCyl p_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK6,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
            /* Height */ 60.0f,
        }},
    };

    fopAcM_SetupActor(i_this, klft_class);
    klft_class* actor = static_cast<klft_class*>(i_this);
    cPhs_State phase = dComIfG_resLoad(&actor->mPhs, "Klft");
    if (phase == cPhs_COMPLEATE_e) {
        actor->mParam = fopAcM_GetParam(i_this);
        u8 pathNo = (fopAcM_GetParam(i_this) >> 16) & 0xFF;
        actor->mShapeParam = i_this->current.angle.z;
        i_this->current.angle.z = 0;
        if (actor->mShapeParam == 0xFF) {
            actor->mShapeParam = 0;
        }
        if (actor->mShapeParam != 0) {
            if (dComIfGs_isSwitch(actor->mShapeParam, fopAcM_GetRoomNo(i_this))) {
                actor->field_3C0 = 80.0f;
            } else {
                actor->field_3C0 = 20.0f;
            }
        }
        if (actor->mParam == 0xFF) {
            actor->mParam = 0;
        }
        if (!fopAcM_entrySolidHeap(i_this, CallbackCreateHeap, 0x10000)) {
            return cPhs_ERROR_e;
        }
        if (actor->pm_bgw != NULL && dComIfG_Bgsp()->Regist(actor->pm_bgw, i_this) != 0) {
            return cPhs_ERROR_e;
        }
        if (pathNo == 0xFF) {
            return cPhs_ERROR_e;
        }
        dPath* path = dPath_GetRoomPath(pathNo, fopAcM_GetRoomNo(i_this));
        if (path != NULL) {
            dPnt* point = &path->m_points[0];
            actor->mPath0[0] = point[0].m_position;
            actor->mPath0[1] = point[1].m_position;
            cXyz delta = actor->mPath0[1] - actor->mPath0[0];
            i_this->home.angle.y = cM_atan2s(delta.x, delta.z) + 0x8000;
            i_this->current.angle.y = cM_atan2s(delta.x, delta.z) + 0x8000;
            actor->field_394 = delta;
            actor->mPath2[0] = point[2].m_position;
            actor->mPath2[1] = point[3].m_position;
        } else {
            return cPhs_ERROR_e;
        }
        switch (actor->mParam) {
        case 1:
            i_this->scale.x = 0.9f;
            i_this->scale.z = 0.9f;
            break;
        case 2:
            i_this->scale.x = 0.8f;
            i_this->scale.z = 0.8f;
            break;
        case 3:
            i_this->scale.x = 0.7f;
            i_this->scale.z = 0.7f;
            break;
        default:
            i_this->scale.z = 1.0f;
            i_this->scale.x = 1.0f;
            break;
        }
        i_this->scale.y = 1.0f;
        actor->mModel->setBaseScale(i_this->scale);
        actor->mStts.Init(0xFF, 0xFF, i_this);
        actor->mSph.Set(utiwa_sph_src);
        actor->mSph.SetStts(&actor->mStts);
        for (int i = 0; i < 2; i++) {
            actor->mSph2[i].Set(utiwa_sph_src);
            actor->mSph2[i].SetStts(&actor->mStts);
            actor->mSph2[i].SetR(130.0f + REG0_F(11));
            actor->mCyl[i].Set(p_co_cyl_src);
            actor->mCyl[i].SetStts(&actor->mStts);
        }
        daKlft_Execute(actor);
    }
    return phase;
}

static actor_method_class l_daKlft_Method = {
    (process_method_func)daKlft_Create,
    (process_method_func)daKlft_Delete,
    (process_method_func)daKlft_Execute,
    (process_method_func)daKlft_IsDelete,
    (process_method_func)daKlft_Draw,
};

actor_process_profile_definition g_profile_KLFT = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_KLFT_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(klft_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_KLFT_e,
    /* Actor SubMtd */ &l_daKlft_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
