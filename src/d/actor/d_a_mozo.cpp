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
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
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

    fopAcM_setCullSizeBox(this, -1000.0f, -1000.0f, -1000.0f, 1000.0f, 1000.0f, 1000.0f);
    fopAcM_SetMtx(this, mAnimMorf->getModel()->getBaseTRMtx());

    // TODO: Insert missing code here

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
    /* Nonmatching */
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
