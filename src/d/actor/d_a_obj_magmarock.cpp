/**
 * d_a_obj_magmarock.cpp
 * Object - Dragon Roost Cavern - Lava slab
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_magmarock.h"
#include "res/Object/Kyjim.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_lib.h"
#include "d/d_magma.h"
#include "d/d_particle.h"
#include "d/d_particle_name.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "SSystem/SComponent/c_lib.h"
#include "dolphin/mtx/quat.h"

const char daObjMagmarock::Act_c::M_arcname[] = "Kyjim";
GXColor daObjMagmarock::Act_c::default_color = {0xFF, 0xFF, 0xFF, 0xFF};

/* 00000078-00000128       .text set_mtx__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::set_mtx() {
    /* Nonmatching */
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    Quaternion quat;
    PSQUATMultiply(&mQuat1, &mQuat3, &quat);
    mDoMtx_stack_c::quatM(&quat);
    MTXCopy(mDoMtx_stack_c::get(), mpModel->getBaseTRMtx());
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000128-00000258       .text demo_move__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::demo_move() {
    /* Nonmatching */
    if (dComIfGs_isEventBit(0x380)) {
        return;
    }
    if (m29F == 0) {
        if (m45A == 0) {
            if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
                m45A++;
            } else {
                fopAcM_orderOtherEvent2(this, "magma_cam", dEvtFlag_NOPARTNER_e, 0xFFFF);
                eventInfo.mCondition |= dEvtCnd_UNK2_e;
            }
        } else if (m45A == 1) {
            dEvent_manager_c& evtmgr = g_dComIfG_gameInfo.play.getEvtManager();
            s32 staff = evtmgr.getMyStaffId("Magrock", NULL, 0);
            if (evtmgr.endCheckOld("magma_cam")) {
                g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
                m45A++;
                dComIfGs_onEventBit(0x380);
            } else {
                evtmgr.cutEnd(staff);
            }
        }
    }
}

/* 00000258-00000410       .text ControlEffect__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::ControlEffect() {
    /* Nonmatching */
    if (m45C != 0) {
        if (m45E != 0) {
            if (mpEffectA == NULL) {
                mpEffectA = dComIfGp_particle_set(dPa_name::ID_AK_SN_MAGMAISLAND00, &current.pos, NULL,
                                                  NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
            } else {
                mpEffectA->setGlobalTranslation(current.pos.x, current.pos.y, current.pos.z);
            }
        } else {
            if (mpEffectA != NULL) {
                JPABaseEmitter* emtr = mpEffectA;
                emtr->mMaxFrame = -1;
                emtr->setStatus(JPAEmtrStts_StopEmit);
                mpEffectA = NULL;
            }
            if (mpEffectB == NULL) {
                dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
                mpEffectB = dComIfGp_particle_setToon(dPa_name::ID_AK_SN_MAGMAISLAND01, &current.pos, NULL,
                                                      NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
            } else {
                mpEffectB->setGlobalTranslation(current.pos.x, current.pos.y, current.pos.z);
            }
        }
    } else {
        if (mpEffectB != NULL) {
            JPABaseEmitter* emtr = mpEffectB;
            emtr->mMaxFrame = -1;
            emtr->setStatus(JPAEmtrStts_StopEmit);
            mpEffectB = NULL;
        }
    }
}

/* 0000044C-00000560       .text play_anim__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::play_anim() {
    /* Nonmatching */
    if (mAnmIdx > 0x177 && mBrkFrame > 0.0f) {
        mBrkFrame -= 1.0f;
    } else if (mAnmIdx >= 0xF && mAnmIdx <= 0x3C) {
    } else if (mBrkFrame < (f32)M_brk->getFrameMax()) {
        mBrkFrame += 1.0f;
    }

    if (mAnmIdx < 0x3C) {
        if (mBckFrame < (f32)M_bck->getFrameMax()) {
            mBckFrame += 1.0f;
        }
    } else if (mAnmIdx > 0x177 && mBckFrame > 0.0f) {
        mBckFrame -= 1.0f;
    }
}

/* 00000560-0000058C       .text appear_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::appear_proc_init() {
    mProcTimer = 30;
    mProcFunc = &Act_c::appear_proc;
}

/* 0000058C-000005EC       .text appear_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::appear_proc() {
    if (mProcTimer == 10) {
        dComIfG_Bgsp()->Regist(mpBgW, this);
    }
    if (mProcTimer == 0) {
        wait_proc_init();
    }
}

/* 000005EC-00000618       .text wait_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::wait_proc_init() {
    mProcTimer = 0x12C;
    mProcFunc = &Act_c::wait_proc;
}

/* 00000618-00000644       .text wait_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::wait_proc() {
    if (mProcTimer == 0) {
        quake_proc_init();
    }
}

/* 00000644-000006E0       .text stay_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::stay_proc_init() {
    u8 param = fopAcM_GetParam(this);
    if (param == 0xFF) {
        param = 0;
    }
    mBrkFrame = 30.0f;
    mBckFrame = 30.0f;
    mProcTimer = param * 15 + 30;
    mAnmIdx = 0x14A;
    dComIfG_Bgsp()->Regist(mpBgW, this);
    mProcFunc = &Act_c::stay_proc;
}

/* 000006E0-00000720       .text stay_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::stay_proc() {
    if (m29E != 0) {
        if (mProcTimer-- == 0) {
            quake_proc_init();
        }
    }
}

/* 00000720-000007B8       .text quake_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::quake_proc_init() {
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(0x380F, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    mProcTimer = 0x2D;
    mProcFunc = &Act_c::quake_proc;
}

/* 000007B8-0000084C       .text quake_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::quake_proc() {
    mAngle += mAngleAdd;
    cLib_addCalcAngleS2(&mAngleAdd, 0x1000, 2, 0x100);
    cLib_addCalc2(&mQuakeAngle, 750.0f + REG10_F(10), 0.25f, 50.0f);
    if (mProcTimer == 0) {
        vanish_proc_init();
    }
}

/* 0000084C-00000878       .text vanish_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::vanish_proc_init() {
    mProcTimer = 0x5A;
    mProcFunc = &Act_c::vanish_proc;
}

/* 00000878-000008F8       .text vanish_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::vanish_proc() {
    mAngle += mAngleAdd;
    cLib_addCalcAngleS2(&mAngleAdd, 0, 4, 0x40);
    if (mProcTimer == 0x50) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    if (mProcTimer < 0) {
        fopAcM_delete(this);
    }
}

/* 000008F8-00000AEC       .text ride_call_back__14daObjMagmarockFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjMagmarock::ride_call_back(dBgW*, fopAc_ac_c* i_ac, fopAc_ac_c* i_pt) {
    /* Nonmatching */
    Act_c* i_this = (Act_c*)i_ac;

    cXyz sp30 = i_pt->current.pos - i_ac->current.pos;
    cXyz sp24(0.0f, 1.0f, 0.0f);
    sp30 = sp30.outprod(sp24);

    f32 dist = sp30.abs2();
    f32 invDist;
    if (dist > 0.0f) {
        invDist = std::sqrtf(dist);
    } else {
        invDist = dist;
    }

    if (sp30.normalizeRS()) {
        cLib_addCalcAngleS2(&i_this->mRideAngle,
                            (s16)(-invDist * (2.0f + 4.0f * (0.001f * (i_this->current.pos.y - i_this->home.pos.y)))),
                            8, 0x200);
        i_this->m29C = 1;
        i_this->m29E = 1;
        f32 s = cM_ssin(i_this->mRideAngle);
        i_this->mQuat2.x = sp30.x * s;
        i_this->mQuat2.y = sp30.y * s;
        i_this->mQuat2.z = sp30.z * s;
        i_this->mQuat2.w = cM_scos(i_this->mRideAngle);
    }
}

/* 00000AEC-00000B0C       .text CheckCreateHeap__14daObjMagmarockFP10fopAc_ac_c */
BOOL daObjMagmarock::CheckCreateHeap(fopAc_ac_c* i_actor) {
    return ((Act_c*)i_actor)->CreateHeap();
}

/* 00000B0C-00000DA0       .text CreateHeap__Q214daObjMagmarock5Act_cFv */
BOOL daObjMagmarock::Act_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_KYJIM_BDL_KYJIM_00_e);
    JUT_ASSERT(333, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    M_brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_KYJIM_BRK_KYJIM_00_e);
    M_bck = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_KYJIM_BCK_KYJIM_00_e);
    JUT_ASSERT(341, M_brk != 0);
    JUT_ASSERT(342, M_bck != 0);
    s32 brkInit = mBrkAnm.init(modelData, M_brk, 0, 2, 1.0f, 0, -1, false, 0);
    s32 bckInit = mBckAnm.init(modelData, M_bck, 0, 2, 1.0f, 0, -1, false);

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale);
    MTXCopy(mDoMtx_stack_c::get(), mMtx);

    mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_KYJIM_DZB_KYJIM_00_e), 1, &mMtx);
    mpBgW->SetCrrFunc(dBgS_MoveBGProc_Typical);

    if (mpBgW == NULL) {
        return FALSE;
    }
    BOOL ret = FALSE;
    if (mpModel != NULL && brkInit != 0 && bckInit != 0) {
        ret = TRUE;
    }
    return ret;
}

/* 00000DA0-000013B4       .text CreateInit__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::CreateInit() {
    /* Nonmatching */
    scale.set(1.0f, 1.0f, 1.0f);
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -200.0f, -30.0f, -200.0f, 200.0f, 15.0f, 200.0f);
    PSMTXCopy(mpModel->getBaseTRMtx(), mMtx);

    mQuakeAngle = 0.0f;
    mRideAngle = 0;
    m29A = 0;
    field_0x450 = 0;
    mProcTimer = 0x1E;
    mAnmIdx = 0;
    mBrkFrame = 0.0f;
    mAngle = 0;
    mAngleAdd = 0;
    m45A = 0;
    m29E = 0;
    speed.set(0.0f, 0.0f, 0.0f);
    home.pos = current.pos;
    home.pos.y += 15.0f;
    gravity = -2.5f;

    mQuat3 = ZeroQuat;
    mQuat2 = mQuat3;
    mQuat1 = mQuat2;

    set_mtx();
    mpBgW->SetRideCallback(ride_call_back);
    m29F = fopAcM_GetParam(this) >> 24;

    if (m29F != 0) {
        stay_proc_init();
        return;
    }

    appear_proc_init();
    if (mpLavaSmoke == NULL) {
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::getInterface()->seStart(0x380E, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
        dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));

        mTevStr = tevStr;

        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mTevStr);
        mTevStr.mColorC0.r = (u8)(mTevStr.mColorC0.r + (s32)(0.12f * (255 - mTevStr.mColorC0.r)));
        mTevStr.mColorC0.g = (u8)(mTevStr.mColorC0.g + (s32)(0.12f * (255 - mTevStr.mColorC0.g)));
        mTevStr.mColorC0.b = (u8)(mTevStr.mColorC0.b + (s32)(0.12f * (255 - mTevStr.mColorC0.b)));
        mTevStr.mColorK0.r = (u8)(mTevStr.mColorK0.r + (s32)(0.12f * (255 - mTevStr.mColorK0.r)));
        mTevStr.mColorK0.g = (u8)(mTevStr.mColorK0.g + (s32)(0.12f * (255 - mTevStr.mColorK0.g)));
        mTevStr.mColorK0.b = (u8)(mTevStr.mColorK0.b + (s32)(0.12f * (255 - mTevStr.mColorK0.b)));

        mpLavaSmoke = dComIfGp_particle_setToon(
            dPa_name::ID_AK_SN_YOGANYUGE00, &current.pos, NULL, NULL, (s32)(153.0f + 102.0f * REG10_F(25)),
            NULL, -1, NULL, NULL, NULL);
        mpLavaBubble = dComIfGp_particle_setToon(
            dPa_name::ID_AK_SN_YOGANYUGE01, &current.pos, NULL, NULL, (s32)(153.0f + 102.0f * REG10_F(26)),
            NULL, -1, NULL, NULL, NULL);

        if (mpLavaSmoke != NULL) {
            mpLavaSmoke->setGlobalPrmColor(default_color.r, default_color.g, default_color.b);
            mpLavaSmoke->setGlobalEnvColor(default_color.r, default_color.g, default_color.b);
        }
        if (mpLavaBubble != NULL) {
            mpLavaBubble->setGlobalPrmColor(default_color.r, default_color.g, default_color.b);
            mpLavaBubble->setGlobalEnvColor(default_color.r, default_color.g, default_color.b);
        }
    }
}

/* 000013B4-00001560       .text LiftUpRequest__Q214daObjMagmarock5Act_cFR4cXyz */
bool daObjMagmarock::Act_c::LiftUpRequest(cXyz& i_pos) {
    /* Nonmatching */
    mLiftPos = i_pos;
    void (Act_c::*waitProc)() = &Act_c::wait_proc;
    int isWait = mProcFunc == waitProc;
    if (isWait) {
        void (Act_c::*appearProc)() = &Act_c::appear_proc;
        int isAppear = mProcFunc == appearProc;
        if (!isAppear) {
            cXyz sp2C = current.pos - mLiftPos;
            sp2C.y = 0.0f;
            if (!sp2C.normalizeRS()) {
                sp2C.set(0.0f, 0.0f, 1.0f);
            }
            PSVECScale(&sp2C, &sp2C, 10.0f);
            PSVECAdd(&current.pos, &sp2C, &current.pos);
        }
        return FALSE;
    }
    cLib_addCalcPos2(&current.pos, i_pos, 0.05f, 5.0f);
    cLib_addCalc2(&mQuakeAngle, 750.0f, 0.5f, 40.0f);
    cLib_addCalcAngleS2(&mAngleAdd, 0x1200, 4, 0x100);
    mAngle += mAngleAdd;
    cLib_addCalc2(&current.pos.y, i_pos.y, 0.25f, 150.0f);
    m45C = 1;
    return TRUE;
}

/* 00001560-0000167C       .text BeforeLiftRequest__Q214daObjMagmarock5Act_cFR4cXyz */
bool daObjMagmarock::Act_c::BeforeLiftRequest(cXyz& i_pos) {
    /* Nonmatching */
    mLiftPos = i_pos;
    if (mLiftPos.y < home.pos.y + 25.0f) {
        mLiftPos.y = home.pos.y + 25.0f;
    }

    void (Act_c::*waitProc)() = &Act_c::wait_proc;
    int isWait = mProcFunc == waitProc;
    if (isWait) {
        return FALSE;
    }
    cLib_addCalcPos2(&current.pos, mLiftPos, 0.05f, 5.0f);
    cLib_addCalc2(&mQuakeAngle, 500.0f, 0.25f, 20.0f);
    cLib_addCalcAngleS2(&mAngleAdd, 0xA00, 8, 0x100);
    mAngle += mAngleAdd;
    cLib_addCalc2(&current.pos.y, mLiftPos.y, 0.25f, 150.0f);
    m45C = 1;
    m45E = 1;
    return TRUE;
}

/* 0000167C-000017DC       .text calc_ground_quat__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::calc_ground_quat() {
    f32 yPos;
    if (dComIfGp_getMagma() != NULL) {
        yPos = dComIfGp_getMagma()->checkYpos(current.pos);
    } else {
        yPos = current.pos.y - 10.0f;
    }
    if (yPos > -99999992.0f) {
        home.pos.y = 15.0f + (10.0f + yPos);
    }
    home.pos.x = current.pos.x;
    home.pos.z = current.pos.z;

    mCorner[0].set(0.0f, 0.0f, 120.0f);
    mCorner[1].set(103.9f, 0.0f, -60.0f);
    mCorner[2].set(-103.9f, 0.0f, -60.0f);

    for (s32 i = 0; i < 3; i++) {
        PSVECAdd(&mCorner[i], &home.pos, &mCorner[i]);
        if (dComIfGp_getMagma() != NULL) {
            yPos = dComIfGp_getMagma()->checkYpos(mCorner[i]);
        } else {
            yPos = current.pos.y - 10.0f;
        }
        if (yPos > -99999992.0f) {
            mCorner[i].y = 15.0f + yPos;
        }
    }

    dLib_calc_QuatFromTriangle(&mQuat3, 0.25f, &mCorner[0], &mCorner[1], &mCorner[2]);
}

/* 000017DC-0000198C       .text Create__Q214daObjMagmarock6MethodFPv */
cPhs_State daObjMagmarock::Method::Create(void* i_this) {
    Act_c* a_this = (Act_c*)i_this;
    fopAcM_ct(a_this, Act_c);

    cPhs_State state = dComIfG_resLoad(&a_this->mPhs, Act_c::M_arcname);
    if (state == cPhs_COMPLEATE_e) {
        if (dComIfGp_getMagma() == NULL) {
            state = cPhs_INIT_e;
        } else {
            if (!fopAcM_entrySolidHeap(a_this, CheckCreateHeap, 0x5D40)) {
                state = cPhs_ERROR_e;
            } else {
                a_this->CreateInit();
            }
        }
    }
    return state;
}

/* 00001A90-00001B14       .text Delete__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Delete(void* i_this) {
    Act_c* a_this = (Act_c*)i_this;
    dComIfG_resDelete(&a_this->mPhs, Act_c::M_arcname);

    if (a_this->heap != NULL) {
        if (a_this->mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(a_this->mpBgW);
        }
    }
    return TRUE;
}

/* 00001B14-00001B38       .text Execute__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Execute(void* i_this) {
    return ((Act_c*)i_this)->_execute();
}

/* 00001B38-00001EC0       .text _execute__Q214daObjMagmarock5Act_cFv */
inline bool daObjMagmarock::Act_c::_execute() {
    /* Nonmatching */
    calc_ground_quat();

    if (m45C == 0) {
        void (Act_c::*quakeProc)() = &Act_c::quake_proc;
        int isQuake = mProcFunc == quakeProc;
        if (isQuake) {
        } else {
            void (Act_c::*vanishProc)() = &Act_c::vanish_proc;
            int isVanish = mProcFunc == vanishProc;
            if (isVanish) {
            } else {
                cLib_addCalc2(&mQuakeAngle, 0.0f, 0.2f, 20.0f);
                cLib_addCalcAngleS2(&mAngleAdd, 0, 4, 0x100);
            }
        }
        current.pos.y += speed.y;
        speed.y += gravity;
    } else {
        speed.y = 0.0f;
    }

    if (current.pos.y < home.pos.y + 100.0f) {
        if (old.pos.y >= home.pos.y + 100.0f) {
            dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
        }
        if (current.pos.y < home.pos.y) {
            f32 clampY = home.pos.y - 30.0f;
            if (current.pos.y < clampY) {
                current.pos.y = clampY;
            }
            speed.y -= (0.4f + REG10_F(26)) * (current.pos.y - home.pos.y);
        }
        speed.y *= 0.65f - REG10_F(25);
    }

    if (m45C == 0) {
        void (Act_c::*stayProc)() = &Act_c::stay_proc;
        int isStay = mProcFunc == stayProc;
        if (!isStay) {
            mProcTimer--;
            mAnmIdx++;
        }
    }

    set_mtx();
    demo_move();
    ControlEffect();
    m45C = 0;
    m45E = 0;
    (this->*mProcFunc)();
    play_anim();

    shape_angle.x = mQuakeAngle * cM_scos(mAngle);
    shape_angle.z = mQuakeAngle * cM_ssin(mAngle);
    if (m29C == 0) {
        mQuat2 = ZeroQuat;
    }
    Quaternion quat;
    C_QUATSlerp(&mQuat1, &mQuat2, &quat, 0.25f);
    mQuat1 = quat;
    m29C = 0;

    if (mpBgW->ChkUsed()) {
        mpBgW->mIgnorePlaneType |= 4;
        mpBgW->Move();
    }
    return FALSE;
}

/* 00001EC0-00002128       .text Draw__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Draw(void* i_this) {
    /* Nonmatching */
    Act_c* a_this = (Act_c*)i_this;
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &a_this->current.pos, &a_this->tevStr);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &a_this->current.pos, &a_this->mTevStr);

    a_this->mTevStr.mColorC0.r = (u8)(a_this->mTevStr.mColorC0.r + (s32)(0.12f * (255 - a_this->mTevStr.mColorC0.r)));
    a_this->mTevStr.mColorC0.g = (u8)(a_this->mTevStr.mColorC0.g + (s32)(0.12f * (255 - a_this->mTevStr.mColorC0.g)));
    a_this->mTevStr.mColorC0.b = (u8)(a_this->mTevStr.mColorC0.b + (s32)(0.12f * (255 - a_this->mTevStr.mColorC0.b)));
    a_this->mTevStr.mColorK0.r = (u8)(a_this->mTevStr.mColorK0.r + (s32)(0.12f * (255 - a_this->mTevStr.mColorK0.r)));
    a_this->mTevStr.mColorK0.g = (u8)(a_this->mTevStr.mColorK0.g + (s32)(0.12f * (255 - a_this->mTevStr.mColorK0.g)));
    a_this->mTevStr.mColorK0.b = (u8)(a_this->mTevStr.mColorK0.b + (s32)(0.12f * (255 - a_this->mTevStr.mColorK0.b)));

    g_env_light.setLightTevColorType(a_this->mpModel, &a_this->tevStr);
    a_this->mBrkAnm.entry(a_this->mpModel->getModelData(), (s16)a_this->mBrkFrame);
    a_this->mBckAnm.entry(a_this->mpModel->getModelData(), (s16)a_this->mBckFrame);
    mDoExt_modelUpdateDL(a_this->mpModel);
    return TRUE;
}

/* 00002128-00002130       .text IsDelete__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::IsDelete(void*) {
    return TRUE;
}

actor_method_class daObjMagmarock::Method::Table = {
    (process_method_func)daObjMagmarock::Method::Create,
    (process_method_func)daObjMagmarock::Method::Delete,
    (process_method_func)daObjMagmarock::Method::Execute,
    (process_method_func)daObjMagmarock::Method::IsDelete,
    (process_method_func)daObjMagmarock::Method::Draw,
};

actor_process_profile_definition g_profile_Obj_Magmarock = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Magmarock_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMagmarock::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Magmarock_e,
    /* Actor SubMtd */ &daObjMagmarock::Method::Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
