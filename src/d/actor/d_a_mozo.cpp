/**
 * d_a_mozo.cpp
 * Enemy - Moblin Statue / モ石像 (Mo Sekizou)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "JAZelAudio/JAIZelBasic.h"
#include "d/actor/d_a_mozo.h"
#include "res/Object/Mozo.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_lib.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "d/actor/d_a_beam.h"
#include "d/actor/d_a_player.h"

static dCcD_SrcCps cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_FIRE,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK8,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 50.0f,
    }},
};


static daMozo_HIO_c l_HIO;
u8 daMozo_c::m_event_flag;

/* 000000EC-000001D0       .text __ct__12daMozo_HIO_cFv */
daMozo_HIO_c::daMozo_HIO_c() {
    
    m3C = 0.0f;
    m40 = -300.0f;
    m44 = 600.0f;
    mNo = -1;
    m08 = -1;
    mpBeamChild = &mBeamChild;
    mpFireChild = &mFireChild;
    mpBeamChild->m04 = 1000.0f;
    mpBeamChild->m08 = 1200.0f;
    mpBeamChild->m0C = 0x2000;
    mpBeamChild->m0E = 0x2800;
    mpBeamChild->m10 = 0;
    mpFireChild->m04 = 1000.0f;
    mpFireChild->m08 = 1200.0f;
    mpFireChild->m0C = 0x2000;
    mpFireChild->m0E = 0x2800;
    mpFireChild->m10 = 0;
}

/* 000002D0-00000568       .text daMozo_nodeCallBackBeam__FP8daMozo_cP8J3DModelP7J3DNodei */
static BOOL daMozo_nodeCallBackBeam(daMozo_c* i_this, J3DModel* model, J3DNode* node, int calcTiming) {
    /* Nonmatching */
    s32 jntNo = ((J3DJoint*)node)->getJntNo();

    if (calcTiming == 0) {
        static cXyz a_beam_start(60.0f, -20.0f, 0.0f);
        static cXyz a_beam_end(1250.0f, -250.0f, 0.0f);
        static cXyz a_beamL_start(60.0f, -20.0f, 12.5f);
        static cXyz a_beamR_start(60.0f, -20.0f, -12.5f);

        PSMTXCopy(model->getAnmMtx(jntNo), mDoMtx_stack_c::now);
        PSMTXMultVec(mDoMtx_stack_c::now, &a_beam_start, &i_this->m30C);
        PSMTXMultVec(mDoMtx_stack_c::now, &a_beam_end, &i_this->m318);

        Mtx sp14;
        PSMTXCopy(mDoMtx_stack_c::now, sp14);
        cXyz sp8(sp14[0][3], sp14[1][3], sp14[2][3]);
        sp14[0][3] = 0.0f;
        sp14[1][3] = 0.0f;
        sp14[2][3] = 0.0f;
        mDoMtx_stack_c::transS(sp8);
        mDoMtx_stack_c::quatM(&i_this->mQuatRotation);
        mDoMtx_stack_c::concat(sp14);

        PSMTXMultVec(mDoMtx_stack_c::now, &a_beam_start, &i_this->m2DC);
        PSMTXMultVec(mDoMtx_stack_c::now, &a_beam_end, &i_this->m2E8);
        PSMTXMultVec(mDoMtx_stack_c::now, &a_beamL_start, &i_this->m2F4);
        PSMTXMultVec(mDoMtx_stack_c::now, &a_beamR_start, &i_this->m300);

        PSMTXCopy(mDoMtx_stack_c::now, model->getAnmMtx(jntNo));
        PSMTXCopy(mDoMtx_stack_c::now, J3DSys::mCurrentMtx);
    }

    return TRUE;
}

/* 00000568-00000728       .text daMozo_nodeCallBackFire__FP8daMozo_cP8J3DModelP7J3DNodei */
static BOOL daMozo_nodeCallBackFire(daMozo_c* i_this, J3DModel* model, J3DNode* node, int calcTiming) {
    /* Nonmatching */
    s32 jntNo = ((J3DJoint*)node)->getJntNo();

    if (calcTiming == 0) {
        static cXyz a_fire_start(0.0f, 0.0f, 0.0f);
        static cXyz a_fire_end(5000.0f, 0.0f, 0.0f);

        PSMTXCopy(model->getAnmMtx(jntNo), mDoMtx_stack_c::now);
        PSMTXMultVec(mDoMtx_stack_c::now, &a_fire_start, &i_this->m30C);
        PSMTXMultVec(mDoMtx_stack_c::now, &a_fire_end, &i_this->m318);

        Mtx sp14;
        PSMTXCopy(mDoMtx_stack_c::now, sp14);
        cXyz sp8(sp14[0][3], sp14[1][3], sp14[2][3]);
        sp14[0][3] = 0.0f;
        sp14[1][3] = 0.0f;
        sp14[2][3] = 0.0f;
        mDoMtx_stack_c::transS(sp8);
        mDoMtx_stack_c::quatM(&i_this->mQuatRotation);
        mDoMtx_stack_c::concat(sp14);

        PSMTXMultVec(mDoMtx_stack_c::now, &a_fire_start, &i_this->m330);
        PSMTXMultVec(mDoMtx_stack_c::now, &a_fire_end, &i_this->m33C);

        PSMTXCopy(mDoMtx_stack_c::now, model->getAnmMtx(jntNo));
        PSMTXCopy(mDoMtx_stack_c::now, J3DSys::mCurrentMtx);
    }

    return TRUE;
}

/* 00000728-0000078C       .text daMozo_nodeCallBack__FP7J3DNodei */
static BOOL daMozo_nodeCallBack(J3DNode* node, int calcTiming) {
    
    J3DJoint* joint = (J3DJoint*)node;
    s32 jntNo = joint->getJntNo();
    J3DModel* model = j3dSys.getModel();
    daMozo_c* i_this = (daMozo_c*)model->getUserArea();

    switch (i_this->field_0x376) {
    case 0: return daMozo_nodeCallBackBeam(i_this, model, node, calcTiming);
    case 1: return daMozo_nodeCallBackFire(i_this, model, node, calcTiming);
    }

    return TRUE;
}

/* 0000078C-000007AC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daMozo_c*>(i_this)->CreateHeap();
}

/* 000007AC-00000A24       .text CreateHeap__8daMozo_cFv */
BOOL daMozo_c::CreateHeap() {
    J3DModelData* mdlData = (J3DModelData*)dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BDL_MOZ_e);
    
    mDoExt_McaMorf* newMorf =  new mDoExt_McaMorf(
        mdlData,
        0,
        0,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BCK_MOZ_e)),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        0,
        0,
        0,
        0x11020203
    );
    
    mAnimMorf = newMorf;

    m_brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BRK_MOZ_e);
    JUT_ASSERT(0x16A, m_brk != NULL);

    m_btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BTK_MOZ_e);
    JUT_ASSERT(0x16D, m_btk != NULL);

    int brkInitResult = mBrkAnm.init(mdlData, m_brk, true, J3DFrameCtrl::EMode_NONE);
    int btkInitResult = mBtkAnm.init(mdlData, m_btk, true, J3DFrameCtrl::EMode_NONE);

    return mdlData != 0 && mAnimMorf != 0 && mAnimMorf->getModel() != 0 && brkInitResult != 0 && btkInitResult != 0;
}

/* 00000A24-00000AAC       .text set_mtx__8daMozo_cFv */
void daMozo_c::set_mtx() {
    J3DModel* mdl = mAnimMorf->getModel();
    mdl->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
        
    mdl->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000AAC-00000C38       .text anime_proc__8daMozo_cFv */
void daMozo_c::anime_proc() {
    
    mAnimMorf->play(NULL, 0, 0);
    mBrkAnm.play();
    mBtkAnm.play();

    if (mAnimMorf->getFrame() < 24.0f) {
        fopAcM_seStart(this, 0x6179, 0);
    }

    if (mAnimMorf->checkFrame(35.0f)) {
        if (mAnimMorf->getPlaySpeed() > 0.0f) {
            fopAcM_seStart(this, 0x697A, 0);
        } else {
            mDoAud_seStopActor(&eyePos, 0x697A);
            fopAcM_seStart(this, 0x697B, 0);
        }
    }
}

/* 00000C38-00000C90       .text wait_proc_init__8daMozo_cFv */
void daMozo_c::wait_proc_init() {
    /* Nonmatching */
    setAnm(0, 0.0f);
    setProcess(&daMozo_c::wait_proc);
}

/* 00000C90-00000D58       .text wait_proc__8daMozo_cFv */
void daMozo_c::wait_proc() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (checkRange(0) && !player->checkPlayerFly()) {
        switch (field_0x376) {
        case 0:
            search_beam_proc_init();
            break;
        case 1:
            search_fire_proc_init();
            break;
        case 2:
            search_beam_proc_init();
            break;
        }
        if (m_event_flag == 0) {
            field_0x377 = 1;
        }
    }
}

/* 00000D58-00000DE0       .text search_beam_proc_init__8daMozo_cFv */
void daMozo_c::search_beam_proc_init() {
    /* Nonmatching */
    setAnm(1, 0.0f);
    setProcess(&daMozo_c::search_beam_proc);

    mBrkAnm.setFrame(0.0f);
    mBtkAnm.setFrame(0.0f);
    mBrkAnm.setPlaySpeed(1.0f);
    mBtkAnm.setPlaySpeed(1.0f);
}

/* 00000DE0-00001230       .text search_beam_proc__8daMozo_cFv */
void daMozo_c::search_beam_proc() {
    /* Nonmatching */
    daPy_py_c* player = daPy_getPlayerActorClass();

    if (mAnimMorf->getFrame() > 30.0f) {
        cXyz sp48 = player->current.pos - m30C;
        cXyz sp3C = m318 - m30C;
        Quaternion sp60;
        daObj::quat_rotVec(&sp60, sp3C, sp48);
        C_QUATSlerp(&mQuatRotation, &sp60, &mQuatRotation, 0.2f);
    }

    anime_proc();

    if (mAnimMorf->getFrame() > mAnimMorf->getEndFrame() - 1.0f) {
        daBeam_c* beam1 = (daBeam_c*)getBeamActor(mBeam1ID);
        daBeam_c* beam2 = (daBeam_c*)getBeamActor(mBeam2ID);

        if (beam1 != NULL && beam2 != NULL) {
            cXyz sp30 = m2E8 - m2DC;
            csXyz sp1C = csXyz::Zero;
            sp1C.y = cM_atan2s(sp30.x, sp30.z);

            Vec sp24;
            sp24.x = sp30.x;
            sp24.y = 0.0f;
            sp24.z = sp30.z;
            f32 dist = std::sqrtf(PSVECSquareMag(&sp24));
            sp1C.x = cM_atan2s(-sp30.y, dist);

            if (beam1->m690 == NULL) {
                beam1->m690 = dComIfGp_particle_set(dPa_name::ID_AK_SN_LASERROOT00, &beam1->current.pos);
            }
            if (beam1->m5F4 == 0) {
                beam1->m5A8 = 0.0f;
                if (beam1->m588 < 5.0f) {
                    beam1->m588 += 1.0f;
                } else {
                    beam1->m5A8 = 0.0f;
                    beam1->m588 = 5.0f;
                    beam1->m5F4 = 1;
                }
            } else {
                beam1->m5A8 = 0.0f;
                beam1->m588 = 5.0f;
            }

            beam1->current.pos = m2F4;
            beam1->current.angle = sp1C;
            beam1->m694 = 15.0f;

            if (beam2->m690 == NULL) {
                beam2->m690 = dComIfGp_particle_set(dPa_name::ID_AK_SN_LASERROOT00, &beam2->current.pos);
            }
            if (beam2->m5F4 == 0) {
                beam2->m5A8 = 0.0f;
                if (beam2->m588 < 5.0f) {
                    beam2->m588 += 1.0f;
                } else {
                    beam2->m5A8 = 0.0f;
                    beam2->m588 = 5.0f;
                    beam2->m5F4 = 1;
                }
            } else {
                beam2->m5A8 = 0.0f;
                beam2->m588 = 5.0f;
            }

            beam2->current.pos = m300;
            beam2->current.angle = sp1C;
            beam2->m694 = 15.0f;
        }
    }

    if (checkRange(1) == 0) {
        towait_proc_init();
    }
}

/* 00001230-000012C0       .text search_fire_proc_init__8daMozo_cFv */
void daMozo_c::search_fire_proc_init() {
    /* Nonmatching */
    setAnm(1, 0.0f);
    setProcess(&daMozo_c::search_fire_proc);

    mBrkAnm.setFrame(0.0f);
    mBtkAnm.setFrame(0.0f);
    mBrkAnm.setPlaySpeed(1.0f);
    mBtkAnm.setPlaySpeed(1.0f);

    m370 = 0;
}

/* 000012C0-000017F4       .text search_fire_proc__8daMozo_cFv */
void daMozo_c::search_fire_proc() {
    if (mAnimMorf->getFrame() > 30.0f || mAnmIdx == 4 || mAnmIdx == 3) {
        mDoMtx_stack_c::YrotS(current.angle.y);
        cXyz sp64;
        PSMTXMultVec(mDoMtx_stack_c::now, (Vec*)&l_HIO.m3C, &sp64);
        PSVECAdd(&sp64, &current.pos, &sp64);
        PSVECSubtract(&sp64, &m30C, &sp64);
        cXyz sp58 = m318 - m30C;
        Quaternion sp48;
        daObj::quat_rotVec(&sp48, sp58, sp64);
        C_QUATSlerp(&mQuatRotation, &sp48, &mQuatRotation, 0.2f);
    }

    anime_proc();

    if (mAnmIdx == 1 || mAnmIdx == 3) {
        if (mAnimMorf->getFrame() > mAnimMorf->getEndFrame() - 50.0f) {
            if (mPtcl0 == NULL) {
                mPtcl0 = dComIfGp_particle_set(dPa_name::ID_AK_SN_MOZFIRE00, &current.pos);
            }
            if (mPtcl1 == NULL) {
                mPtcl1 = dComIfGp_particle_setToon(dPa_name::ID_AK_SN_MOZFIRE01, &current.pos);
            }
            PSMTXCopy(mAnimMorf->getModel()->getAnmMtx(MOZ_JNT_ATAMA_J_e), mDoMtx_stack_c::now);
            mDoMtx_stack_c::XYZrotM(0x640, 0x4000, 0);
            mDoMtx_stack_c::transM(0.0f, 50.0f, 52.0f);
            if (mPtcl0 != NULL) {
                mPtcl0->setGlobalRTMatrix(mDoMtx_stack_c::now);
            }
            if (mPtcl1 != NULL) {
                mPtcl1->setGlobalRTMatrix(mDoMtx_stack_c::now);
            }
            cXyz sp3C = m33C - m330;
            if (sp3C.normalizeRS() == 0) {
                sp3C = cXyz::Zero;
            }
            cXyz sp30 = sp3C;
            f32 temp_f3 = 45.0f * m370;
            f32 temp_f0 = 3.0f * m370;
            f32 var_f1 = temp_f3 > 600.0f ? 600.0f : temp_f3;
            f32 var_f31 = temp_f0 > 80.0f ? 80.0f : temp_f0;
            PSVECScale(&sp30, &sp30, var_f1);
            PSVECAdd(&sp30, &m330, &sp30);
            mCps.SetStartEnd(m330, sp30);
            mCps.SetR(var_f31);
            mCps.SetAtVec(sp3C);
            dComIfG_Ccsp()->Set(&mCps);
            mSoundPos = sp30;
            JAIZelBasic::zel_basic->seStart(0x7033, &mSoundPos, 0, 0, 1.0f, 1.0f, -1.0f,
                                            -1.0f, 0);
            if (m370++ > 0x3C) {
                setAnm(4, 0.0f);
                if (mPtcl0 != NULL) {
                    mPtcl0->setRate(0.0f);
                    mPtcl0->becomeInvalidEmitter();
                    mPtcl0 = NULL;
                }
                if (mPtcl1 != NULL) {
                    mPtcl1->setRate(0.0f);
                    mPtcl1->becomeInvalidEmitter();
                    mPtcl1 = NULL;
                }
                towait_proc_init();
                return;
            }
        }
    } else if (mAnmIdx == 4) {
        if (mAnimMorf->getFrame() < 30.0f) {
            setAnm(3, 8.0f);
            m370 = 0;
        }
    }
}

/* 000017F4-00001874       .text towait_proc_init__8daMozo_cFv */
void daMozo_c::towait_proc_init() {
    /* Nonmatching */
    setAnm(2, 0.0f);
    mAnimMorf->setPlaySpeed(-0.5f);
    setProcess(&daMozo_c::towait_proc);

    mBrkAnm.setPlaySpeed(-1.0f);
    mBtkAnm.setPlaySpeed(-1.0f);
}

/* 00001874-00001B3C       .text towait_proc__8daMozo_cFv */
void daMozo_c::towait_proc() {
    /* Nonmatching */
    daBeam_c* beam1 = (daBeam_c*)getBeamActor(mBeam1ID);
    daBeam_c* beam2 = (daBeam_c*)getBeamActor(mBeam2ID);

    mDoMtx_quatSlerp(&mQuatRotation, &ZeroQuat, &mQuatRotation, 0.05f);
    anime_proc();

    if (field_0x376 == 0) {
        if (beam1 != NULL && beam2 != NULL) {
            int beam1Done;
            int beam2Done;

            if (beam1->m690 != NULL) {
                beam1->beamOff();
            }
            if (beam1->m5F4 == 1) {
                if (beam1->m588 < 5.0f) {
                    beam1->m588 += 1.0f;
                }
                if (beam1->m5A8 < 4.0f) {
                    beam1->m5A8 += 1.0f;
                    beam1Done = 0;
                } else {
                    beam1->m5A8 = 0.0f;
                    beam1->m588 = 0.0f;
                    beam1->m5F4 = 0;
                    beam1Done = 1;
                }
            } else {
                beam1->m588 = 0.0f;
                beam1->m5A8 = 0.0f;
                beam1Done = 1;
            }

            if (beam2->m690 != NULL) {
                beam2->beamOff();
            }
            if (beam2->m5F4 == 1) {
                if (beam2->m588 < 5.0f) {
                    beam2->m588 += 1.0f;
                }
                if (beam2->m5A8 < 4.0f) {
                    beam2->m5A8 += 1.0f;
                    beam2Done = 0;
                } else {
                    beam2->m5A8 = 0.0f;
                    beam2->m588 = 0.0f;
                    beam2->m5F4 = 0;
                    beam2Done = 1;
                }
            } else {
                beam2->m588 = 0.0f;
                beam2->m5A8 = 0.0f;
                beam2Done = 1;
            }

            if (beam1Done != 0 && beam2Done != 0 && mQuatRotation.w > 0.99f &&
                mAnimMorf->getFrame() < 25.0f && mBrkAnm.getFrame() < 1.0f &&
                mBtkAnm.getFrame() < 1.0f) {
                wait_proc_init();
            }
        }
    } else if (field_0x376 == 1) {
        if (mQuatRotation.w > 0.99f && mAnimMorf->getFrame() < 25.0f &&
            mBrkAnm.getFrame() < 1.0f && mBtkAnm.getFrame() < 1.0f) {
            wait_proc_init();
        }
    }
}

/* 00001B3C-00001D8C       .text checkRange__8daMozo_cFi */
BOOL daMozo_c::checkRange(int i_param) {
    
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (i_param == 0 && player->checkGrabWear()) {
        return 0;
    }

    cXyz diff = player->current.pos - current.pos;
    f32 dist = diff.absXZ();
    if (diff.y > -280.0f) {
        return 0;
    }

    f32 range;
    s16 angle;
    if (i_param == 0) {
        daMozo_childHIO_c* child = (&l_HIO.mpBeamChild)[field_0x376];
        range = child->m04;
        angle = child->m0C;
    } else {
        daMozo_childHIO_c* child = (&l_HIO.mpBeamChild)[field_0x376];
        range = child->m08;
        angle = child->m0E;
    }

    cXyz dir(cM_ssin(current.angle.y), 0.0f, cM_scos(current.angle.y));
    f32 dot = diff.inprod(dir);
    if (cLib_distanceAngleS(fopAcM_searchPlayerAngleY(this), current.angle.y) < angle && dist < range &&
        dot > 200.0f) {
        return 1;
    }
    return 0;
}

/* 00001D8C-00001F70       .text setAnm__8daMozo_cFif */
void daMozo_c::setAnm(int i_idx, float i_morf) {
    /* Nonmatching */
    mAnmIdx = i_idx;
    J3DAnmTransform* res;
    f32 speed, start, end;
    switch (i_idx) {
    case 0:
        res = (J3DAnmTransform*)dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BCK_MOZ_e);
        start = 0.0f;
        end = -1.0f;
        speed = start;
        break;
    case 1:
        res = (J3DAnmTransform*)dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BCK_MOZ_e);
        start = 0.0f;
        end = -1.0f;
        speed = 1.0f;
        break;
    case 2:
        res = (J3DAnmTransform*)dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BCK_MOZ_e);
        start = 24.0f;
        end = 36.0f;
        speed = -0.25f;
        break;
    case 3:
        res = (J3DAnmTransform*)dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BCK_MOZ_e);
        start = 25.0f;
        end = -1.0f;
        speed = 1.0f;
        break;
    case 4:
        res = (J3DAnmTransform*)dComIfG_getObjectRes("Mozo", dRes_INDEX_MOZO_BCK_MOZ_e);
        start = 32.0f;
        end = 36.0f;
        speed = -0.25f;
        break;
    default:
        return;
    }
    mAnimMorf->setAnm(res, 0, i_morf, speed, start, end, NULL);
}

/* 00001F70-00002228       .text CreateInit__8daMozo_cFv */
cPhs_State daMozo_c::CreateInit() {
    /* Nonmatching */
    J3DModelData* mdlData = mAnimMorf->getModel()->getModelData();

    u8 temp = fopAcM_GetParam(this) & 0xFF;
    if (temp == 0xFF) {
        temp = 0;
    }
    field_0x376 = cLib_minMaxLimit<u8>(temp, 0, 2);

    mAnimMorf->getModel()->setUserArea((u32)this);
    for (u16 i = 0; i < mdlData->getJointNum(); i++) {
        if (i == MOZ_JNT_ATAMA_J_e) {
            mdlData->getJointNodePointer(i)->setCallBack(daMozo_nodeCallBack);
        }
    }

    mQuatRotation = ZeroQuat;

    cull.box.min.x = -1000.0f;
    cull.box.min.y = -1000.0f;
    cull.box.min.z = -1000.0f;
    cull.box.max.x = 1000.0f;
    cull.box.max.y = 1000.0f;
    cull.box.max.z = 1000.0f;
    fopAcM_SetMtx(this, mAnimMorf->getModel()->getBaseTRMtx());

    m2F4 = current.pos;
    m300 = current.pos;

    if (field_0x376 == 0) {
        cXyz scale(1.5f, 1.5f, 20.0f);
        mBeam1ID = fopAcM_createChild(fpcNm_Beam_e, fopAcM_GetID(this), 0, &m2F4,
                                      tevStr.mRoomNo, NULL, &scale, -1, NULL);
        mBeam2ID = fopAcM_createChild(fpcNm_Beam_e, fopAcM_GetID(this), 0x30000000, &m300,
                                      tevStr.mRoomNo, NULL, &scale, -1, NULL);
    } else {
        mStts.Init(0xFF, 0xFF, this);
        mCps.Set(cps_src);
        mCps.SetStts(&mStts);
        mCps.SetStartEnd(current.pos, current.pos);
        mCps.SetR(25.0f);
    }

    set_mtx();
    mAnimMorf->calc();
    wait_proc_init();

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("モ石像", &l_HIO); // "Mo Statue" (mo sekizou)
    }

    return cPhs_COMPLEATE_e;
}

/* 00002228-000023B0       .text _create__8daMozo_cFv */
cPhs_State daMozo_c::_create() {
    fopAcM_ct(this, daMozo_c);

    cPhs_State result = dComIfG_resLoad(&mPhs, "Mozo");

    if (result == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x1AA0)) {
            result = CreateInit();
            _execute();
        } else {
            return cPhs_ERROR_e;
        }
    }

    return result;
}

/* 000023B0-0000242C       .text _delete__8daMozo_cFv */
bool daMozo_c::_delete() {
    dComIfG_resDelete(&mPhs, "Mozo");
    JAIZelBasic::zel_basic->seDeleteObject((Vec*)&mSoundPos);
    if (l_HIO.mNo >= 0) {
        mDoHIO_root.deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return true;
}

/* 0000242C-00002498       .text getBeamActor__8daMozo_cFUi */
fopAc_ac_c* daMozo_c::getBeamActor(fpc_ProcID apid) {
    fopAc_ac_c* ac = fopAcM_SearchByID(apid);
    if (ac == NULL)
        return NULL;
    if (fopAc_IsActor(ac) && fopAcM_GetProfName(ac) == fpcNm_Beam_e)
        return ac;
    return NULL;
}

/* 00002498-00002588       .text event_move__8daMozo_cFv */
void daMozo_c::event_move() {
    if (m_event_flag != 2) {
        if (eventInfo.getCommand() == dEvtCmd_INDEMO_e) {
            field_0x377 = 0;
            m_event_flag = 1;
        }
        if (m_event_flag == 1) {
            if (dComIfGp_getPEvtManager()->endCheckOld("MOZO_CAM")) {
                dComIfGp_event_onEventFlag(8);
                m_event_flag = 2;
            }
        }
        if (m_event_flag == 0 && field_0x377 == 1) {
            fopAcM_orderOtherEvent2(this, "MOZO_CAM", dEvtFlag_NOPARTNER_e, 0xFFFF);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    }
}

/* 00002588-000025DC       .text _execute__8daMozo_cFv */
bool daMozo_c::_execute() {
    mAnimMorf->calc();

    (this->*mCurrentProc)();
    event_move();
    set_mtx();

    return true;
}

/* 000025DC-0000267C       .text _draw__8daMozo_cFv */
bool daMozo_c::_draw() {
    
    J3DModelData* mdlData = mAnimMorf->getModel()->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mAnimMorf->getModel(), &tevStr);

    mBrkAnm.entry(mdlData);
    mBtkAnm.entry(mdlData);
    mAnimMorf->entryDL();

    return true;
}

/* 0000267C-000026A0       .text daMozo_Draw__FP8daMozo_c */
static BOOL daMozo_Draw(daMozo_c* i_this) {
    return i_this->_draw();
}

/* 000026A0-000026C4       .text daMozo_Execute__FP8daMozo_c */
static BOOL daMozo_Execute(daMozo_c* i_this) {
    return i_this->_execute();
}

/* 000026C4-000026CC       .text daMozo_IsDelete__FP8daMozo_c */
static BOOL daMozo_IsDelete(daMozo_c*) {
    return TRUE;
}

/* 000026CC-000026F0       .text daMozo_Delete__FP8daMozo_c */
static BOOL daMozo_Delete(daMozo_c* i_this) {
    return i_this->_delete();
}

/* 000026F0-00002710       .text daMozo_Create__FP10fopAc_ac_c */
static cPhs_State daMozo_Create(fopAc_ac_c* i_this) {
    return static_cast<daMozo_c*>(i_this)->_create();
}

static actor_method_class l_daMozo_Method = {
    (process_method_func)daMozo_Create,
    (process_method_func)daMozo_Delete,
    (process_method_func)daMozo_Execute,
    (process_method_func)daMozo_IsDelete,
    (process_method_func)daMozo_Draw,
};

actor_process_profile_definition g_profile_MOZO = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_MOZO_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daMozo_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_MOZO_e,
    /* Actor SubMtd */ &l_daMozo_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
