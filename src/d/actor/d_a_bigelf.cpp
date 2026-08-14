/**
 * d_a_bigelf.cpp
 * NPC - Great Fairy
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bigelf.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_npc_fa1.h"
#include "d/d_com_inf_game.h"
#include "d/d_event_manager.h"
#include "d/d_msg.h"
#include "d/d_particle.h"
#include "f_pc/f_pc_name.h"
#include "m_Do/m_Do_audio.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "JAZelAudio/JAZelAudio_SE.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_lib.h"
#include "d/d_s_play.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_iter.h"

/* l_bck_ix_tbl: bck resource indices per anm state */
static const int l_bck_ix_tbl[] = {8, 6, 7, 6};

/* pa_name_flower / pa_name_flower2: particle names per flower type */
static const u16 pa_name_flower[] = {0x834F, 0x8351, 0x8353, 0x8355};
static const u16 pa_name_flower2[] = {0x8350, 0x8352, 0x8354, 0x8356};

/* p_name0 / p_name1: appear particle names per flower type */
static u16 p_name0[] = {0x8347, 0x8349, 0x834B, 0x834D};
static u16 p_name1[] = {0x8348, 0x834A, 0x834C, 0x834E};

static u32 l_msgId;
static msg_class* l_msg;

static BOOL CheckCreateHeap(fopAc_ac_c* a_this);
static BOOL nodeCallBack_Bigelf(J3DNode*, int);

/* 00000078-0000016C       .text oct_delete__10daBigelf_cFv */
void daBigelf_c::oct_delete() {
    /* Nonmatching */
    fopAc_ac_c* octActor = fopAcM_SearchByID(m3F8);
    daShip_c* ship = dComIfGp_getShipActor();
    if (!chkFlag(0x40)) {
        return;
    }

    if (m3AC > 0) {
        m3AC--;
        return;
    }

    if (octActor != NULL) {
        if (ship != NULL) {
            cXyz pos(0.0f, 0.0f, 1570.0f);
            cXyz curPos;
            fpoAcM_absolutePos(octActor, &pos, &curPos);
            curPos.y = ship->current.pos.y;
            ship->initStartPos(&curPos, cLib_targetAngleY(&current.pos, &curPos) + 0x4000);
        }
        fopAcM_delete(octActor);
    }
    clrFlag(0x40);
}

/* 0000016C-00000338       .text nodeCallBack__10daBigelf_cFP7J3DNode */
s32 daBigelf_c::nodeCallBack(J3DNode* i_joint) {
    /* Nonmatching */
    J3DModel* model = j3dSys.getModel();
    u16 jntNo = ((J3DJoint*)i_joint)->getJntNo();
    u32 jointOff = jntNo * 0x30;
    cXyz pos;
    cXyz outPos;

    PSMTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
    if (jntNo == getHeadJntNum()) {
        s16 target = 0;
        if (m3BC == 0) {
            target = m_jnt.getHead_x();
        }
        cLib_addCalcAngleS(&m350, target, 8, 0x400, 0x100);
        mDoMtx_ZrotM(*calc_mtx, -m350);
        pos.set(0.0f, 0.0f, 0.0f);
        MtxPosition(&pos, &outPos);
        setAttentionBasePos(outPos);
        pos.set(20.0f, -20.0f, 0.0f);
        MtxPosition(&pos, &outPos);
        setEyePos(outPos);
        if (m337 != 0xFF) {
            m337++;
        }
    } else if (jntNo != getBackboneJntNum() && jntNo == m_fl_jnt) {
        pos.set(0.0f, 0.0f, 0.0f);
        MtxPosition(&pos, &m3D0);
    }

    PSMTXCopy(*calc_mtx, j3dSys.mCurrentMtx);
    PSMTXCopy(*calc_mtx, model->getAnmMtx(jntNo));
    return 1;
}

/* 00000338-00000384       .text nodeCallBack_Bigelf__FP7J3DNodei */
static BOOL nodeCallBack_Bigelf(J3DNode* i_joint, int i_flag) {
    if (i_flag == 0) {
        J3DModel* model = j3dSys.getModel();
        daBigelf_c* i_this = (daBigelf_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->nodeCallBack(i_joint);
        }
    }
    return 1;
}

/* 00000384-00000438       .text lightInit__10daBigelf_cFP4cXyz */
void daBigelf_c::lightInit(cXyz* i_pos) {
    /* Nonmatching */
    mLightInfluencePos = *i_pos;
    mLightInfluence.mPos = *i_pos;
    if (!mIsLightShining) {
        mIsLightShining = true;
        mLightInfluence.mColor.r = 0xFF;
        mLightInfluence.mColor.g = 0xFF;
        mLightInfluence.mColor.b = 0xFF;
        mLightInfluence.mPower = 0.0f;
        mLightInfluence.mFluctuation = 0.0f;
        mLightInfluencePos = *i_pos;
        mLightInfluenceColor.r = 0xFF;
        mLightInfluenceColor.g = 0xFF;
        mLightInfluenceColor.b = 0xFF;
        mLightInfluencePower = 0.0f;
        mLightInfluenceFluctuation = 0.0f;
        dKy_plight_priority_set(&mLightInfluence);
    }
}

/* 00000438-00000470       .text lightEnd__10daBigelf_cFv */
void daBigelf_c::lightEnd() {
    if (mIsLightShining) {
        mIsLightShining = false;
        dKy_plight_cut(&mLightInfluence);
    }
}

/* 00000470-0000047C       .text lightProc__10daBigelf_cFv */
void daBigelf_c::lightProc() {
    if (mIsLightShining) {
        return;
    }
}

/* 0000047C-00000488       .text darkInit__10daBigelf_cFv */
void daBigelf_c::darkInit() {
    mDark = 1;
}

/* 00000488-000004D0       .text darkEnd__10daBigelf_cFv */
void daBigelf_c::darkEnd() {

    mDark = 0;
    dKy_set_actcol_ratio(1.0f);
    dKy_set_bgcol_ratio(1.0f);
    dKy_set_vrboxcol_ratio(1.0f);
}

/* 000004D0-00000574       .text darkProc__10daBigelf_cFv */
void daBigelf_c::darkProc() {
    if (mDark != 0) {
        cLib_addCalc2(&m3A0, m3A4, 0.1f, 1.0f);
        dKy_set_actcol_ratio(0.3f + m3A0 * 0.7f);
        f32 f31 = 0.6f + m3A0 * 0.4f;
        dKy_set_bgcol_ratio(f31);
        dKy_set_vrboxcol_ratio(f31);
    }
}

/* 00000574-00000588       .text demoInitFlDelete__10daBigelf_cFv */
void daBigelf_c::demoInitFlDelete() {
    m3C0 = 0;
    m3DC = 0xFF;
}

/* 00000588-00000708       .text demoProcFlDelete__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDelete() {
    /* Nonmatching */
    m3C0++;
    if (m3C0 == 0x1B) {
        fopAc_ac_c* player = dComIfGp_getLinkPlayer();
        dComIfGp_particle_set(pa_name_flower2[(s8)m3F5], &player->current.pos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        m3A4 = 1.0f;
    }
    if (m3C0 >= 0x1B) {
        if (m3E4 != 0) {
            if (m3DC > 0xA) {
                m3DC -= 0xA;
                ((JPABaseEmitter*)m3E4)->mGlobalPrmColor.a = m3DC;
            } else {
                m3DC = 0;
                ((JPABaseEmitter*)m3E4)->mGlobalPrmColor.a = 0;
                ((JPABaseEmitter*)m3E4)->setMaxFrame(-1);
                ((JPABaseEmitter*)m3E4)->setStatus(1);
                m3E4 = 0;
            }
        } else {
            lightEnd();
            dComIfGp_evmng_cutEnd(mStaffId);
            if (chkFlag(0x1)) {
                clrFlag(0x1);
                if (getType() == 6) {
                    g_dComIfG_gameInfo.play.setItemMaxMagicCount(0x20);
                    g_dComIfG_gameInfo.play.setItemMagicCount(0x20);
                }
            }
        }
    }
    return 1;
}

/* 00000708-000007E4       .text demoInitFlLink__10daBigelf_cFv */
void daBigelf_c::demoInitFlLink() {
    fopAc_ac_c* player = dComIfGp_getLinkPlayer();
    cXyz pos(0.0f, 300.0f, 400.0f);
    cXyz curPos;
    fpoAcM_absolutePos(player, &pos, &curPos);
    m3E4 = dComIfGp_particle_set(pa_name_flower[(s8)m3F5], &curPos, &shape_angle, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
    lightInit(&curPos);
    mLightInfluence.mPower = 1000.0f;
    demoInitWait();
}

/* 000007E4-00000808       .text demoProcFlLink__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlLink() {
    demoProcWait();
    return 1;
}

/* 00000808-000008F0       .text demoInitFlDmAf__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmAf() {
    cXyz pos = m3D0;
    pos.y += 20.0f;
    m3E0 = dComIfGp_particle_set(pa_name_flower[(s8)m3F5], &pos, &shape_angle, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
    JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_DY_HANAFUBUKI, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 000008F0-000009C0       .text demoProcFlDmAf__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDmAf() {
    /* Nonmatching */
    if (m336 != 0 || !chkFlag(0x1)) {
        dComIfGp_evmng_cutEnd(mStaffId);
        clrFlag(0x1);
        if (m3E0 != 0) {
            ((JPABaseEmitter*)m3E0)->setMaxFrame(-1);
            ((JPABaseEmitter*)m3E0)->setStatus(1);
            m3E0 = 0;
        }
        return 1;
    }
    f32 frame = mpBckAnimator->getFrame();
    if (frame >= 116.0f && frame <= 173.0f) {
        setFlag(0x8);
    }
    return 1;
}

/* 000009C0-00000A20       .text demoInitFlDmMd__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmMd() {
    darkInit();
    m3A0 = 1.0f;
    m3A4 = 1.0f;
    clrFlag(0x80);
    setFlag(0x200);
    setFlag(0x400);
}

/* 00000A20-00000CEC       .text demoProcFlDmMd__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDmMd() {
    /* Nonmatching */
    f32 f31 = mpBckAnimator->getFrame();
    if (!chkFlag(0x1)) {
        dComIfGp_evmng_cutEnd(mStaffId);
        return 1;
    }

    if (!(f31 < 16.0f)) {
        if (f31 < 116.0f) {
            m3A4 = 0.01f * (116.0f - f31);
        } else {
            m3A4 = 0.0f;
        }
    }
    if (!chkFlag(0x80)) {
        if (f31 >= 116.0f) {
            setFlag(0x80);
            cXyz pos = m3D0;
            pos.x += 850.0f * cM_ssin(shape_angle.y);
            pos.z += 850.0f * cM_scos(shape_angle.y);
            lightInit(&pos);
            mLightInfluence.mPower = 126.0f;
            JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_DY_FLOWER, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
    }
    if (chkFlag(0x200)) {
        if (f31 >= 126.0f) {
            clrFlag(0x200);
            JAIZelBasic::zel_basic->seStart(JA_SE_CV_DY_BREATH_IN, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
    }
    if (chkFlag(0x400)) {
        if (f31 >= 154.0f) {
            clrFlag(0x400);
            JAIZelBasic::zel_basic->seStart(JA_SE_CV_DY_BREATH_OUT, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
    }
    if (f31 >= 166.0f) {
        dComIfGp_evmng_cutEnd(mStaffId);
        clrFlag(0x1);
    }
    if (f31 >= 116.0f && f31 <= 173.0f) {
        setFlag(0x8);
    }
    return 1;
}

/* 00000CEC-00000CF0       .text demoInitFlDmBf__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmBf() {}

/* 00000CF0-00000D7C       .text demoProcFlDmBf__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDmBf() {
    if (!chkFlag(0x1)) {
        dComIfGp_evmng_cutEnd(mStaffId);
        return 1;
    }
    if (m336 != 0) {
        setAnm(2);
        dComIfGp_evmng_cutEnd(mStaffId);
        clrFlag(0x1);
    }
    return 1;
}

/* 00000D7C-00000D88       .text demoInitFlDemo__10daBigelf_cFv */
void daBigelf_c::demoInitFlDemo() {
    m3DC = 0;
}

/* 00000D88-00000FB8       .text demoProcFlDemo__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDemo() {
    /* Nonmatching */
    if (m336 != 0) {
        if (chkFlag(0x1)) {
            switch (m3BC) {
            case 0:
                setAnm(2);
                break;
            case 1:
                break;
            case 2:
                clrFlag(0x1);
                dComIfGp_evmng_cutEnd(mStaffId);
                break;
            }
        } else {
            dComIfGp_evmng_cutEnd(mStaffId);
        }
    }
    if (m3BC == 2) {
        f32 f2 = mpBckAnimator->getFrame();
        if (f2 >= 116.0f && f2 <= 173.0f) {
            setFlag(0x8);
        }
        switch (m3DC) {
        case 0:
            cXyz pos = m3D0;
            pos.y += 20.0f;
            if (f2 >= 167.0f) {
                m3DC++;
                m3E0 = dComIfGp_particle_set(pa_name_flower[(s8)m3F5], &pos, &shape_angle, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
                JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_DY_HANAFUBUKI, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            }
            break;
        case 1:
            if (!chkFlag(0x1) && m3E0 != 0) {
                m3DC++;
                ((JPABaseEmitter*)m3E0)->setMaxFrame(-1);
                ((JPABaseEmitter*)m3E0)->setStatus(1);
                m3E0 = 0;
            }
            break;
        }
    }
    return 1;
}

/* 00000FB8-0000115C       .text demoInitExit__10daBigelf_cFv */
void daBigelf_c::demoInitExit() {
    /* Nonmatching */
    if (m3CC != 0) {
        ((JPABaseEmitter*)m3CC)->setMaxFrame(-1);
        ((JPABaseEmitter*)m3CC)->setStatus(1);
        m3CC = 0;
    }
    setFlag(0x10);
    m3C0 = 0;
    mHeightOffset = 250.0f;
    m3EC = 1.0f;
    m3F0 = 1.0f;
    cXyz pos(1.0f, 1.0f, 1.0f);
    cXyz curPos = current.pos;
    curPos.y += mHeightOffset;
    dComIfGp_particle_set(0x272, &curPos, NULL, &pos, 0xFF, NULL, -1, NULL, NULL, NULL);
    tevStr.mFogColor.r = 0xFF;
    tevStr.mFogColor.g = 0xFF;
    tevStr.mFogColor.b = 0xFF;
    tevStr.mFogStartZ = 0.0f;
    tevStr.mFogEndZ = 2000.0f;
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_DY_GO_AWAY, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
    JAIZelBasic::zel_basic->seStart(JA_SE_CV_DY_GO_AWAY, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
    darkEnd();
}

/* 0000115C-000012D4       .text demoProcExit__10daBigelf_cFv */
BOOL daBigelf_c::demoProcExit() {
    /* Nonmatching */
    m3C0++;
    cLib_addCalc2(&tevStr.mFogEndZ, 10.0f, 1.0f, 80.0f);
    if (m3C0 < 0x46) {
        cLib_addCalc0(&m3EC, 0.1f, 0.01f);
        cLib_addCalc0(&m3F0, 0.1f, 0.01f);
        return 1;
    }
    if (m3C0 == 0x46) {
        JAIZelBasic::zel_basic->seStart(JA_SE_CM_L_ARROW_PASS_AWAY, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        if (getType() == 6) {
            JAIZelBasic::zel_basic->bgmStop(0x2D, 0);
        }
    }
    cLib_addCalc2(&m3F0, 5.0f, 0.1f, 1.0f);
    cLib_addCalc0(&m3EC, 0.1f, 0.05f);
    if (m3C0 >= 0x5A) {
        dComIfGp_evmng_cutEnd(mStaffId);
        setFlag(0x2);
        clrFlag(0x10);
        if (getType() != 6) {
            makeFa1S();
        }
    }
    return 1;
}

/* 000012D4-000013C0       .text demoInitTalk__10daBigelf_cFv */
void daBigelf_c::demoInitTalk() {

    talkInit();
    int* a_intP = (int*)dComIfGp_getPEvtManager()->getMySubstanceP(mStaffId, "MsgNo", 3);
    JUT_ASSERT(0x325, a_intP);
    mCurrentMessageId = *a_intP;
    if (mCurrentMessageId == 0x2EEA) {
        dComIfGp_setItemLifeCount(dComIfGs_getMaxLife());
        dComIfGp_setItemMagicCount(dComIfGs_getMaxMagic());
    }
}

/* 000013C0-00001418       .text demoProcTalk__10daBigelf_cFv */
BOOL daBigelf_c::demoProcTalk() {
    u16 status = talk();
    if (status == 0x12 || status == 0xFE) {
        dComIfGp_evmng_cutEnd(mStaffId);
    }
    return 1;
}

/* 00001418-0000163C       .text demoInitAppear__10daBigelf_cFv */
void daBigelf_c::demoInitAppear() {
    /* Nonmatching */
    fopAc_ac_c* fa1 = fopAcM_SearchByID(m34C);
    if (fa1 != NULL) {
        g_dComIfG_gameInfo.play.mEvtCtrl.mPtTalk = g_dComIfG_gameInfo.play.mEvtCtrl.getPId(this);
        fopAcM_delete(fa1);
    }
    cXyz pos = current.pos;
    pos.y += 70.0f;
    cXyz shock(0.0f, 1.0f, 0.0f);
    dComIfGp_getVibration().StartShock(5, -0x21, shock);
    dComIfGp_particle_set(p_name0[(s8)m3F5], &pos, NULL, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
    dComIfGp_particle_set(p_name1[(s8)m3F5], &pos, NULL, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
    if (getType() == 6) {
        m3CA = 0xF;
    }
    m3DC = 0xF;
    m3A8 = 0.5f;
    if (getType() == 6) {
        JAIZelBasic::zel_basic->seStart(JA_SE_CM_DY_ENTER_DO, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        JAIZelBasic::zel_basic->bgmStart(0x800053, 0, 0);
    }
    setFlag(0x100);
}

/* 0000163C-000017B4       .text demoProcAppear__10daBigelf_cFv */
BOOL daBigelf_c::demoProcAppear() {
    /* Nonmatching */
    if (m3DC != 0) {
        m3DC--;
        if (m3DC == 0) {
            clrFlag(0x2);
            setAnm(1);
            if (m3CC == 0) {
                m3CC = dComIfGp_particle_set(0x8346, &current.pos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
            }
        }
        return 1;
    }
    if (chkFlag(0x100)) {
        if (mpBckAnimator->getFrame() >= 87.0f) {
            clrFlag(0x100);
            JAIZelBasic::zel_basic->seStart(JA_SE_CV_DY_ENTER, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
    }
    if (m336 != 0) {
        setAnm(0);
        dComIfGp_evmng_cutEnd(mStaffId);
    }
    f32 sx = scale.x;
    scale.y = sx;
    scale.z = sx;
    return 1;
}

/* 000017B4-00001848       .text demoInitFa1__10daBigelf_cFv */
void daBigelf_c::demoInitFa1() {
    /* Nonmatching */
    daNpc_Fa1_c* fa1 = (daNpc_Fa1_c*)fopAcM_SearchByID(m34C);
    if (fa1 != NULL) {
        fa1->init_bigelf_change();
        JAIZelBasic::zel_basic->seStart(JA_SE_CM_DY_ENTER, &eyePos, 0, dComIfGp_getReverb((s8)current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
    }
}

/* 00001848-000018D4       .text demoProcFa1__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFa1() {

    daNpc_Fa1_c* fa1 = (daNpc_Fa1_c*)fopAcM_SearchByID(m34C);
    if (fa1 != NULL) {
        cLib_addCalc2(&fa1->current.pos.y, 70.0f + current.pos.y, 0.2f, 100.0f);
    }
    dComIfGp_evmng_cutEnd(mStaffId);
    return 1;
}

/* 000018D4-00001948       .text demoInitWait__10daBigelf_cFv */
void daBigelf_c::demoInitWait() {

    int* pTimer = (int*)dComIfGp_getPEvtManager()->getMySubstanceP(mStaffId, "Timer", 3);
    if (pTimer != NULL) {
        m3C0 = *pTimer;
    } else {
        m3C0 = 0;
    }
    setAnm(0);
}

/* 00001948-00001998       .text demoProcWait__10daBigelf_cFv */
BOOL daBigelf_c::demoProcWait() {
    if (m3C0 > 0) {
        m3C0--;
    } else {
        dComIfGp_evmng_cutEnd(mStaffId);
    }
    return 0;
}

/* 00001998-00001A74       .text demoInitCom__10daBigelf_cFv */
void daBigelf_c::demoInitCom() {
    /* Nonmatching */
    setFlag(0x1);
    if (dComIfGp_getPEvtManager()->getMySubstanceP(mStaffId, "Ship", 3) != NULL) {
        daShip_c* ship = dComIfGp_getShipActor();
        if (ship != NULL) {
            cXyz pos(0.0f, 0.0f, 800.0f);
            cXyz curPos;
            fpoAcM_absolutePos(this, &pos, &curPos);
            ship->initStartPos(&curPos, cLib_targetAngleY(&current.pos, &curPos) + 0x4000);
        }
        setFlag(0x20);
    }
}

/* 00001A74-00001ACC       .text demoProcCom__10daBigelf_cFv */
void daBigelf_c::demoProcCom() {
    if (getType() != 6) {
        dKy_custom_colset(4, 0, m3A8);
    }
    lightProc();
    darkProc();
}

/* action_table: event action names indexed by getNowEventAction */
static const char* action_table[] = {
    "WAIT", "FA1", "APPEAR", "TALK", "EXIT", "FL_DEMO", "FL_LINK", "FL_DELETE", "FL_DM_BF", "FL_DM_MD",
    "FL_DM_AF",
};

/* 00001ACC-00001B14       .text getNowEventAction__10daBigelf_cFv */
int daBigelf_c::getNowEventAction() {
    /* Nonmatching */
    return dComIfGp_evmng_getMyActIdx(mStaffId, (char**)action_table, 0xB, 0, 1);
}

/* 00001B14-00001CCC       .text demoProc__10daBigelf_cFv */
void daBigelf_c::demoProc() {
    /* Nonmatching */
    int action = getNowEventAction();
    if (dComIfGp_evmng_getIsAddvance(mStaffId)) {
        demoInitCom();
        switch (action) {
        case 0:
            demoInitWait();
            break;
        case 1:
            demoInitFa1();
            break;
        case 2:
            demoInitAppear();
            break;
        case 3:
            demoInitTalk();
            break;
        case 4:
            demoInitExit();
            break;
        case 5:
            demoInitFlDemo();
            break;
        case 6:
            demoInitFlLink();
            break;
        case 7:
            demoInitFlDelete();
            break;
        case 8:
            demoInitFlDmBf();
            break;
        case 9:
            demoInitFlDmMd();
            break;
        case 10:
            demoInitFlDmAf();
            break;
        }
    }
    switch (action) {
    case 0:
        demoProcWait();
        break;
    case 1:
        demoProcFa1();
        break;
    case 2:
        demoProcAppear();
        break;
    case 3:
        demoProcTalk();
        break;
    case 4:
        demoProcExit();
        break;
    case 5:
        demoProcFlDemo();
        break;
    case 6:
        demoProcFlLink();
        break;
    case 7:
        demoProcFlDelete();
        break;
    case 8:
        demoProcFlDmBf();
        break;
    case 9:
        demoProcFlDmMd();
        break;
    case 10:
        demoProcFlDmAf();
        break;
    default:
        dComIfGp_evmng_cutEnd(mStaffId);
        break;
    }
    demoProcCom();
}

/* 00001CCC-00001CD8       .text getType__10daBigelf_cFv */
u8 daBigelf_c::getType() {
    return fopAcM_GetParam(this) & 0xFF;
}

/* 00001CD8-00001CE4       .text getSwbit__10daBigelf_cFv */
u8 daBigelf_c::getSwbit() {
    return (fopAcM_GetParam(this) >> 8) & 0xFF;
}

/* 00001CE4-00001CF0       .text getSwbit2__10daBigelf_cFv */
u8 daBigelf_c::getSwbit2() {
    return (fopAcM_GetParam(this) >> 16) & 0xFF;
}

/* 00001CF0-00001D70       .text getEventFlag__10daBigelf_cFv */
u16 daBigelf_c::getEventFlag() {
    /* Nonmatching */
    switch (getType()) {
    case 0:
        return 0x3020;
    case 1:
        return 0x3010;
    case 2:
        return 0x3008;
    case 3:
        return 0x3004;
    case 4:
        return 0x3002;
    case 5:
        return 0x3001;
    case 6:
        return 0x3180;
    default:
        return 0;
    }
}

/* 00001D70-00001E20       .text makeFa1S__10daBigelf_cFv */
void daBigelf_c::makeFa1S() {
    /* Nonmatching */
    cXyz pos = current.pos;
    csXyz angle;
    angle.x = current.angle.x;
    angle.y = current.angle.y;
    angle.z = current.angle.z;
    pos.y += mHeightOffset;
    for (int i = 0; i < 0xA; i++) {
        fopAcM_create(fpcNm_NPC_FA1_e, 4, &pos, (s8)current.roomNo, &angle, NULL, -1, NULL);
        angle.y += 0x2710;
    }
}

/* 00001E20-00001EB4       .text makeFa1__10daBigelf_cFv */
void daBigelf_c::makeFa1() {
    /* Nonmatching */
    cXyz pos = current.pos;
    csXyz angle;
    angle.x = current.angle.x;
    angle.y = current.angle.y;
    angle.z = current.angle.z;
    pos.y += 100.0f;
    m34C = fopAcM_create(fpcNm_NPC_FA1_e, 6, &pos, (s8)current.roomNo, &angle, NULL, -1, NULL);
}

/* 00001EB4-0000200C       .text setAnm__10daBigelf_cFSc */
void daBigelf_c::setAnm(signed char i_anm) {
    /* Nonmatching */
    f32 f31 = 8.0f;
    int r31 = -1;
    f32 f30 = 1.0f;
    f32 f29 = 0.0f;
    f32 f28 = -1.0f;
    switch (i_anm) {
    case 1:
    case 2:
        f31 = 0.0f;
        break;
    case 3:
        r31 = 3;
        f30 = -1.0f;
        f28 = 100.0f;
        break;
    }
    if (m3BC == 1) {
        f31 = 0.0f;
    }
    if (i_anm != m3BC && i_anm != -1) {
        m3BC = i_anm;
        m338 = 0.0f;
        m336 = 0;
        mpBckAnimator->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("bigelf", l_bck_ix_tbl[m3BC]), r31, f31, f30, f29, f28, NULL);
    }
}

/* 0000200C-00002030       .text setAnmStatus__10daBigelf_cFv */
void daBigelf_c::setAnmStatus() {
    setAnm(0);
}

/* 00002030-000021A4       .text next_msgStatus__10daBigelf_cFPUl */
s32 daBigelf_c::next_msgStatus(u32* pMsgNo) {
    s32 status = 0xF;
    switch (*pMsgNo) {
    case 0x2EE8:
        (*pMsgNo)++;
        switch (getType()) {
        case 0:
        case 1:
            if (dComIfGs_getWalletSize() == 0) {
                mGivenItem = 0xAB;
            } else {
                mGivenItem = 0xAC;
            }
            break;
        case 2:
        case 3:
            if (dComIfGs_getBombMax() <= 0x1E) {
                mGivenItem = 0xAD;
            } else {
                mGivenItem = 0xAE;
            }
            break;
        case 4:
        case 5:
            if (dComIfGs_getArrowMax() <= 0x1E) {
                mGivenItem = 0xAF;
            } else {
                mGivenItem = 0xB0;
            }
            break;
        default:
            mGivenItem = 4;
            break;
        }
        dComIfGp_event_setGtItm(mGivenItem);
        break;
    case 0x2EEB:
    case 0x2EEC:
        (*pMsgNo)++;
        break;
    case 0x2EEF:
    case 0x2EF0:
        (*pMsgNo)++;
        break;
    case 0x2EF1:
        *pMsgNo = 0x2EEE;
        break;
    default:
        status = 0x10;
        break;
    }
    return status;
}

/* 000021A4-000021D4       .text getMsg__10daBigelf_cFv */
u32 daBigelf_c::getMsg() {
    if (mCurrentMessageId == 0x2EEE && g_dComIfG_gameInfo.save.getPlayer().getItem().mItems[12] == 0x27) {
        mCurrentMessageId = 0x2EEF;
    }
    return mCurrentMessageId;
}

/* 000021D4-000021D8       .text msgPushButton__10daBigelf_cFv */
void daBigelf_c::msgPushButton() {}

/* 000021D8-000021DC       .text msgAnm__10daBigelf_cFUc */
void daBigelf_c::msgAnm(unsigned char) {}

/* 000021DC-000021F0       .text talkInit__10daBigelf_cFv */
void daBigelf_c::talkInit() {
    /* Nonmatching */
    m344 = 0xFF;
    m3F7 = 0;
}

/* 000021F0-0000236C       .text talk__10daBigelf_cFv */
u16 daBigelf_c::talk() {
    u16 r31 = 0xFF;
    if (m3F7 == 0) {
        l_msgId = -1;
        m33C = getMsg();
        m3F7 = 1;
    } else if (m3F7 != -1) {
        if (l_msgId == 0xFFFFFFFF) {
            l_msgId = fopMsgM_messageSet(m33C, this);
        } else {
            if (!chkFlag(0x4)) {
                msgAnm(g_dComIfG_gameInfo.play.getBaseAnimeID());
            }
            switch (m3F7) {
            case 1:
                l_msg = fopMsgM_SearchByID(l_msgId);
                if (l_msg != NULL) {
                    m3F7 = 2;
                }
                break;
            case 2:
                r31 = l_msg->mStatus;
                if (r31 == 0xE) {
                    msgPushButton();
                    l_msg->mStatus = next_msgStatus(&m33C);
                    if (l_msg->mStatus == 0xF) {
                        fopMsgM_messageSet(m33C);
                    }
                } else if (r31 == 0x12) {
                    l_msg->mStatus = 0x13;
                    m3F7 = -1;
                }
                break;
            }
        }
    }
    return r31;
}

/* 0000236C-00002534       .text init__10daBigelf_cFv */
BOOL daBigelf_c::init() {
    /* Nonmatching */
    if ((s32)m3F4 == 0) {
        setAction(&daBigelf_c::wait_action, NULL);
    }
    current.pos.y = 30.0f + home.pos.y;
    mAttentionBasePos = current.pos;
    mAttentionBasePos.y += 100.0f;
    mEyePos = mAttentionBasePos;
    eyePos = mEyePos;
    attention_info.position.set(mAttentionBasePos.x, mAttentionBasePos.y + 50.0f, mAttentionBasePos.z);
    m34C = -1;
    if (getType() != 6) {
        if (dComIfGs_isEventBit(getEventFlag())) {
            makeFa1S();
        } else {
            makeFa1();
        }
    }
    setFlag(0x2);
    return 1;
}

/* 00002534-000025A0       .text setAttention__10daBigelf_cFb */
void daBigelf_c::setAttention(bool i_on) {
    if (m3CA > 0) {
        m3CA--;
        return;
    }
    if (i_on || m337 < 2) {
        eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
        attention_info.position.set(mAttentionBasePos.x, mAttentionBasePos.y + 50.0f, mAttentionBasePos.z);
    }
}

/* 000025A0-000025F4       .text lookBack__10daBigelf_cFv */
void daBigelf_c::lookBack() {
    fopAc_ac_c* player = dComIfGp_getLinkPlayer();
    if ((mStateBits & 0x20) != 0x20) {
        current.angle.y = fopAcM_searchActorAngleY(this, player);
        shape_angle.y = current.angle.y;
    }
}

/* 000025F4-000026C0       .text hunt__10daBigelf_cFv */
BOOL daBigelf_c::hunt() {

    fopAc_ac_c* fa1 = fopAcM_SearchByID(m34C);
    fopAc_ac_c* player = dComIfGp_getLinkPlayer();
    if (fa1 == NULL) {
        m3BD = 3;
        return 0;
    }
    if (fopAcM_searchActorDistanceXZ(this, player) < 900.0f) {
        m3BD = 1;
        m3C8 = dComIfGp_evmng_getEventIdx("BIGELF_ARRIVAL", 0xFF);
        fopAcM_orderOtherEventId(this, m3C8, 0xFF, 0xFFFF, 0, 1);
    }
    return 1;
}

/* 000026C0-00002730       .text oct_search__10daBigelf_cFv */
BOOL daBigelf_c::oct_search() {

    fopAc_ac_c* octActor = fopAcM_searchFromName("Daiocta", 0, 0);
    if (octActor != NULL) {
        m3F8 = fpcM_GetID(octActor);
        m3BD = 5;
        m3AC = 0xA;
    }
    return 1;
}

/* 00002730-000028E8       .text oct__10daBigelf_cFv */
BOOL daBigelf_c::oct() {
    /* Nonmatching */
    fopAc_ac_c* octActor = fopAcM_SearchByID(m3F8);
    if (octActor != NULL) {
        current.pos = octActor->current.pos;
        current.pos.y = home.pos.y;
        attention_info.position = current.pos;
        eyePos = current.pos;
        current.angle.y = octActor->shape_angle.y;
        cXyz a(0.0f, 0.0f, 0.0f);
        cXyz b(-820.0f, 0.0f, 1340.0f);
        current.angle.y += cLib_targetAngleY(&a, &b);
        shape_angle.y = current.angle.y;
        setFlag(0x20);
    } else {
        clrFlag(0x20);
    }
    if (dComIfGs_isSwitch(getSwbit(), (s8)current.roomNo)) {
        if (m3AC > 0) {
            m3AC--;
        } else {
            m3BD = 1;
            m3C8 = dComIfGp_evmng_getEventIdx("BIGELF_ARRIVAL2", 0xFF);
            fopAcM_orderChangeEventId(this, dComIfGp_getLinkPlayer(), m3C8, 0, 0xFFFF);
            m3AC = 0x1E;
            setFlag(0x40);
        }
    }
    return 1;
}

/* 000028E8-000029A0       .text ready0__10daBigelf_cFv */
BOOL daBigelf_c::ready0() {

    fopAcM_SearchByID(m34C);
    if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        m3BD = 2;
        mStaffId = dComIfGp_evmng_getMyStaffId("BigElf", NULL, 0);
        m3A8 = 1.0f;
        demoProc();
    } else {
        fopAcM_orderOtherEventId(this, m3C8, 0xFF, 0xFFFF, 0, 1);
    }
    return 1;
}

/* 000029A0-00002A78       .text event0__10daBigelf_cFv */
BOOL daBigelf_c::event0() {
    /* Nonmatching */
    if (dComIfGp_evmng_endCheck(m3C8)) {
        dComIfGs_onEventBit(getEventFlag());
        m3BD = 3;
        g_dComIfG_gameInfo.play.mEvtCtrl.mEventFlag |= 8;
        if (getType() == 6 && getSwbit2() != 0xFF) {
            dComIfGs_onSwitch(getSwbit2(), (s8)current.roomNo);
        }
    } else {
        demoProc();
    }
    return 1;
}

/* 00002A78-00002A80       .text dead__10daBigelf_cFv */
BOOL daBigelf_c::dead() {
    return 1;
}

/* 00002A80-00002C8C       .text wait_action__10daBigelf_cFPv */
BOOL daBigelf_c::wait_action(void*) {
    /* Nonmatching */
    if (m3F6 == 0) {
        if (dComIfGs_isEventBit(getEventFlag())) {
            m3BD = 3;
        } else if (getType() == 6) {
            if (dComIfGs_isSwitch(getSwbit(), (s8)current.roomNo)) {
                if (getSwbit2() != 0xFF) {
                    dComIfGs_onSwitch(getSwbit2(), (s8)current.roomNo);
                }
                m3BD = 3;
            } else {
                m3BD = 4;
            }
        } else {
            m3BD = 0;
        }
        setAnmStatus();
        m3F6++;
    } else if (m3F6 != -1) {
        BOOL proc = 0;
        switch (m3BD) {
        case 0:
            proc = hunt();
            break;
        case 1:
            proc = ready0();
            break;
        case 2:
            proc = event0();
            break;
        case 3:
            proc = dead();
            break;
        case 4:
            proc = oct_search();
            break;
        case 5:
            proc = oct();
            break;
        }
        lookBack();
        setAttention(proc);
        if (chkFlag(0x2)) {
            attention_info.position = current.pos;
            eyePos = current.pos;
            oct_delete();
        }
    }
    return 1;
}

/* 00002C8C-00002DB4       .text _draw__10daBigelf_cFv */
BOOL daBigelf_c::_draw() {
    /* Nonmatching */
    J3DModel* model = mpBckAnimator->getModel();
    J3DModelData* modelData = model->getModelData();
    J3DModelData* flModelData = mpFlowerModel->getModelData();
    if (chkFlag(0x2)) {
        return 0;
    }
    if (!chkFlag(0x10)) {
        g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    }
    g_env_light.setLightTevColorType(model, &tevStr);
    g_env_light.setLightTevColorType(mpFlowerModel, &tevStr);
    mBrkAnimator.entry(modelData, mBrkAnimator.getFrame());
    mBtkAnimator.entry(modelData, mBtkAnimator.getFrame());
    mpBckAnimator->entry();
    if (chkFlag(0x8)) {
        mFlowerBrkAnimator.entry(flModelData, mFlowerBrkAnimator.getFrame());
        PSMTXCopy(model->getAnmMtx(m_fl_jnt), mpFlowerModel->getBaseTRMtx());
        mDoExt_modelUpdateDL(mpFlowerModel);
    }
    return 1;
}

/* 00002DB4-00002F5C       .text _execute__10daBigelf_cFv */
BOOL daBigelf_c::_execute() {

    m_jnt.setParam(0, 0, 0, 0, 0xFA0, 0x2328, -0x7D0, -0xFA0, 0x1000);
    if (!chkFlag(0x10)) {
        m336 = mpBckAnimator->play(&eyePos, 0, 0);
        if (mpBckAnimator->getFrame() < m338 && m3BC != 3) {
            m336 = 1;
        }
        m338 = mpBckAnimator->getFrame();
    }
    clrFlag(0x8);
    (this->*mCurrentStateFunc)(NULL);
    shape_angle.y = current.angle.y;
    tevStr.mRoomNo = (s8)current.roomNo;
    J3DModel* model = mpBckAnimator->getModel();
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseScale(scale);
    if (chkFlag(0x10)) {
        mDoMtx_stack_c::transM(0.0f, mHeightOffset, 0.0f);
        f32 f1 = m3EC;
        mDoMtx_stack_c::scaleM(f1, m3F0, f1);
        mDoMtx_stack_c::transM(0.0f, -mHeightOffset, 0.0f);
    }
    PSMTXCopy(mDoMtx_stack_c::get(), model->getBaseTRMtx());
    mpBckAnimator->calc();
    mBtkAnimator.play();
    return 1;
}

/* 00002F5C-00002FAC       .text _delete__10daBigelf_cFv */
BOOL daBigelf_c::_delete() {

    dComIfG_resDelete(&mPhaseProcReq, "bigelf");
    if (mpBckAnimator != NULL) {
        mpBckAnimator->stopZelAnime();
    }
    return 1;
}

/* 00002FAC-00002FCC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* a_this) {
    return ((daBigelf_c*)a_this)->CreateHeap();
}

/* 00002FCC-00003124       .text _create__10daBigelf_cFv */
cPhs_State daBigelf_c::_create() {
    /* Nonmatching */
    fopAcM_SetupActor(this, daBigelf_c);
    cPhs_State phase = dComIfG_resLoad(&mPhaseProcReq, "bigelf");
    if (phase == cPhs_COMPLEATE_e) {
        if (fpcM_GetName(this) != fpcNm_BIGELF_e) {
            return cPhs_ERROR_e;
        }
        m3F4 = 0;
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0xB7B0)) {
            mpBckAnimator = NULL;
            return cPhs_ERROR_e;
        }
        cullMtx = mpBckAnimator->getModel()->getBaseTRMtx();
        if (!init()) {
            mpBckAnimator = NULL;
            return cPhs_ERROR_e;
        }
    }
    return phase;
}

/* 00003224-00003808       .text CreateHeap__10daBigelf_cFv */
BOOL daBigelf_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("bigelf", 0xB);
    JUT_ASSERT(0x7D4, modelData);
    mpBckAnimator = new mDoExt_McaMorf(
        modelData,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("bigelf", 8),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11000222
    );
    if (mpBckAnimator == NULL || mpBckAnimator->getModel() == NULL) {
        return 0;
    }
    if (!mBrkAnimator.init(modelData, (J3DAnmTevRegKey*)dComIfG_getObjectRes("bigelf", 0xF), 1, 0, 1.0f, 0, -1, 0)) {
        return 0;
    }
    if (!mBtkAnimator.init(modelData, (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("bigelf", 0x13), 1, 2, 1.0f, 0, -1, 0)) {
        return 0;
    }
    J3DSkinDeform* skinDeform = new J3DSkinDeform();
    if (skinDeform == NULL) {
        return 0;
    }
    switch (mpBckAnimator->getModel()->setSkinDeform(skinDeform, 1)) {
    case 4:
        return 0;
    case 0:
        break;
    default:
        JUT_ASSERT(0x811, 0);
        break;
    }
    J3DModel* model = mpBckAnimator->getModel();
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    PSMTXCopy(mDoMtx_stack_c::get(), model->getBaseTRMtx());
    mpBckAnimator->calc();
    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x824, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(0x829, m_jnt.getBackboneJntNum() >= 0);
    m_fl_jnt = modelData->getJointName()->getIndex("handRB");
    JUT_ASSERT(0x82D, m_fl_jnt >= 0);
    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum() || i == m_fl_jnt) {
            mpBckAnimator->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(
                nodeCallBack_Bigelf);
        }
    }
    mpBckAnimator->getModel()->setUserArea((u32)this);
    J3DModelData* flModelData = (J3DModelData*)dComIfG_getObjectRes("bigelf", 0xC);
    JUT_ASSERT(0x842, flModelData);
    mpFlowerModel = mDoExt_J3DModel__create(flModelData, 0x80000, 0x01000000);
    if (mpFlowerModel == NULL) {
        return 0;
    }
    if (!mFlowerBrkAnimator.init(flModelData, (J3DAnmTevRegKey*)dComIfG_getObjectRes("bigelf", 0x10), 1, 0, 1.0f, 0, -1, 0)) {
        return 0;
    }
    m3F5 = 0;
    switch (getType()) {
    case 2:
    case 3:
        mBrkAnimator.getFrameCtrl()->setFrame(1.0f);
        mFlowerBrkAnimator.getFrameCtrl()->setFrame(1.0f);
        m3F5 = 1;
        break;
    case 4:
    case 5:
        mBrkAnimator.getFrameCtrl()->setFrame(2.0f);
        mFlowerBrkAnimator.getFrameCtrl()->setFrame(2.0f);
        m3F5 = 2;
        break;
    case 6:
        mBrkAnimator.getFrameCtrl()->setFrame(3.0f);
        mFlowerBrkAnimator.getFrameCtrl()->setFrame(3.0f);
        m3F5 = 3;
        break;
    }
    return 1;
}

/* 00003808-00003828       .text daBigelf_Create__FP10fopAc_ac_c */
static cPhs_State daBigelf_Create(fopAc_ac_c* i_this) {
    return ((daBigelf_c*)i_this)->_create();
}

/* 00003828-00003848       .text daBigelf_Delete__FP10daBigelf_c */
static BOOL daBigelf_Delete(daBigelf_c* i_this) {
    return ((daBigelf_c*)i_this)->_delete();
}

/* 00003848-00003868       .text daBigelf_Execute__FP10daBigelf_c */
static BOOL daBigelf_Execute(daBigelf_c* i_this) {
    return ((daBigelf_c*)i_this)->_execute();
}

/* 00003868-00003888       .text daBigelf_Draw__FP10daBigelf_c */
static BOOL daBigelf_Draw(daBigelf_c* i_this) {
    return ((daBigelf_c*)i_this)->_draw();
}

/* 00003888-00003890       .text daBigelf_IsDelete__FP10daBigelf_c */
static BOOL daBigelf_IsDelete(daBigelf_c*) {
    return TRUE;
}

static actor_method_class l_daBigelf_Method = {
    (process_method_func)daBigelf_Create,
    (process_method_func)daBigelf_Delete,
    (process_method_func)daBigelf_Execute,
    (process_method_func)daBigelf_IsDelete,
    (process_method_func)daBigelf_Draw,
};

actor_process_profile_definition g_profile_BIGELF = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_BIGELF_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBigelf_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x012B,
    /* Actor SubMtd */ &l_daBigelf_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Unique ID    */ 0,
    /* Delete Delay */ 0x000C,
};
