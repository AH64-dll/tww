/**
 * d_a_npc_uk.cpp
 * NPC - Jin, Jan, & Jun-Roberto
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_uk.h"
#include "m_Do/m_Do_ext.h"
#include "res/Object/Uk.h"
#include "d/actor/d_a_player_main.h"
#include "m_Do/m_Do_lib.h"
#include "d/d_snap.h"
#include "d/d_particle.h"

static fpc_ProcID l_msgId;
static msg_class* l_msg;

/* 000000EC-000000F8       .text getType__10daNpc_Uk_cFv */
u8 daNpc_Uk_c::getType() {
    return fopAcM_GetParam(this) & 0xFF;
}

/* 000000F8-00000104       .text getPath__10daNpc_Uk_cFv */
u8 daNpc_Uk_c::getPath() {
    return fopAcM_GetParam(this) >> 8 & 0xFF;
}

/* 00000104-00000110       .text getShapeType__10daNpc_Uk_cFv */
int daNpc_Uk_c::getShapeType() {
    return (fopAcM_GetParam(this) >> 16) & 0xF;
}

/* 00000110-0000015C       .text getCaughtFlag__10daNpc_Uk_cFv */
u16 daNpc_Uk_c::getCaughtFlag() {
    switch (getShapeType()) {
    case 1:
        return 0x8;
    case 2:
        return 0x4;
    default:
        return 0x10;
    }
}

/* 0000015C-000001A8       .text getFoundFlag__10daNpc_Uk_cFv */
u16 daNpc_Uk_c::getFoundFlag() {
    switch (getShapeType()) {
    case 1:
        return 0x180;
    case 2:
        return 0x140;
    default:
        return 1;
    }
}

/* 000001A8-000001F4       .text getFirstTalk__10daNpc_Uk_cFv */
u32 daNpc_Uk_c::getFirstTalk() {
    switch (getShapeType()) {
    case 0:
        return 0x1202;
    case 1:
        return 0x1204;
    default:
        return 0x1201;
    }
}

/* 000001F4-0000026C       .text chkGameStart__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::chkGameStart() {
    if (dComIfGs_isTmpBit(0x40) && !dComIfGs_isTmpBit(getCaughtFlag())) {
        return TRUE;
    }
    return FALSE;
}

/* 0000026C-00000420       .text chkPositioning__10daNpc_Uk_cFfffss */
BOOL daNpc_Uk_c::chkPositioning(f32 param_0, f32 param_1, f32 param_2, s16 param_3, s16 param_4) {
    cXyz dist;
    fopAc_ac_c* pLink = daPy_getPlayerLinkActorClass();

    dist = pLink->current.pos - current.pos;
    f32 xzDist = dist.absXZ();
    if (xzDist > param_0) {
        return FALSE;
    }

    if (dist.y < param_1 || dist.y > param_2) {
        return FALSE;
    }

    s16 angle = cLib_targetAngleY(&current.pos, &pLink->current.pos) - current.angle.y;
    if (param_3 > param_4) {
        if (angle < param_3 && angle > param_4) {
            return TRUE;
        }
    } else {
        if (angle < param_3 || angle > param_4) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 0000045C-000008B0       .text nextVisitMode__10daNpc_Uk_cFv */
u8 daNpc_Uk_c::nextVisitMode() {
    fopAc_ac_c* pActor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &mLookActorId);
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    u8 lookMode = 0;

    if (pActor == NULL) {
        mVisitMode = VISIT_START;
    } else {
        lookMode = ((daNpc_Uk_c*)pActor)->mAnmIdx;
    }

    if (mVisitMode == VISIT_WAIT_3) {
        if (mWaitTimer != 0) {
            mWaitTimer--;
            return VISIT_WAIT_3;
        }
    }

    if (mVisitMode == VISIT_START) {
        pActor = fopAcM_searchFromName("Mk", 0xFF, 1);
        if (pActor == NULL) {
            return VISIT_START;
        }
        mLookActorId = pActor->base.base.mBsPcId;
        lookMode = ((daNpc_Uk_c*)pActor)->mAnmIdx;
    }

    if (lookMode == 2 || lookMode == 8 || lookMode == 9) {
        cXyz dist = pActor->current.pos - current.pos;
        switch (mVisitMode) {
        case VISIT_REACHED_LINK:
            if (dist.absXZ() > 6400.0f) {
                return VISIT_RUN_LINK;
            }
            return VISIT_WALK_AROUND_LINK;
        case VISIT_RUN_LINK:
            if (dist.absXZ() > 22500.0f) {
                return VISIT_NOTICE_LINK;
            }
            return VISIT_REACHED_LINK;
        default:
            if (dist.absXZ() < 160000.0f) {
                return VISIT_RUN_LINK;
            }
            return VISIT_WALK_PATH;
        }
    } else if (mVisitMode == VISIT_WAIT_2) {
        if (mWaitTimer != 0) {
            mWaitTimer--;
            return VISIT_WAIT_2;
        }
        cXyz dist = pLink->current.pos - current.pos;
        if (dist.absXZ() < 22500.0f) {
            return VISIT_LEFT_PATH;
        }
        if (lookMode == 4 || lookMode == 5) {
            return VISIT_REACHED_LINK;
        }
        s16 angle = fopAcM_searchActorAngleY(pLink, this) - current.angle.y;
        if (angle < 0) {
            angle = -angle;
        }
        if (angle < 0x3800) {
            return VISIT_WALK_PATH;
        }
        return VISIT_WAIT_2;
    } else if (mVisitMode == VISIT_WALK_AROUND_LINK) {
        if (mVisitMode == 8) {
            if (mWaitTimer != 0) {
                mWaitTimer--;
                return VISIT_WAIT;
            }
            return VISIT_WAIT_2;
        }
        return VISIT_WAIT;
    } else if (mVisitMode == VISIT_LEFT_PATH) {
        return VISIT_WAIT_3;
    } else {
        cXyz dist = pLink->current.pos - current.pos;
        if (mVisitMode >= 5 && mVisitMode < 8) {
            if (dist.absXZ() > 32400.0f) {
                return VISIT_REACHED_LINK;
            }
            if (mVisitMode == VISIT_LEFT_PATH) {
                if (mRunAroundLinkTimer != 0) {
                    mRunAroundLinkTimer--;
                } else {
                    return VISIT_WALK_AROUND_LINK;
                }
            }
            return mVisitMode;
        }
        if (dist.absXZ() < 22500.0f) {
            return VISIT_LEFT_PATH;
        }
        return VISIT_WALK_PATH;
    }
}

/* 000008B0-00000930       .text approachRun__10daNpc_Uk_cFP10fopAc_ac_c */
BOOL daNpc_Uk_c::approachRun(fopAc_ac_c* i_pTarget) {
    s16 angle;
    dNpc_calc_DisXZ_AngY(current.pos, i_pTarget->current.pos, NULL, &angle);
    cLib_addCalcAngleS2(&current.angle.y, angle, 8, 0x800);
    return TRUE;
}

/* 00000930-00000964       .text aroundWalk__10daNpc_Uk_cFP10fopAc_ac_c */
BOOL daNpc_Uk_c::aroundWalk(fopAc_ac_c* i_pTarget) {
    mUkStatic.aroundWalk(this, i_pTarget, mRunAroundLinkTimer);
    return TRUE;
}

/* 00000964-00000AD4       .text surrender__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::surrender() {
    fopAc_ac_c* pActor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &mLookActorId);
    if (pActor != NULL && pActor->speedF > 1.0f) {
        cXyz dist = pActor->current.pos - current.pos;
        cXyz distXZ(dist.x, 0.0f, dist.z);
        if (PSVECSquareMag(&distXZ) <= 7225.0f) {
            s16 angle = fopAcM_searchActorAngleY(pActor, this) - pActor->shape_angle.y;
            if (angle <= 0x2AAA && angle >= -0x2AAA) {
                s16 dir = (s16)(pActor->shape_angle.y + ((angle < 0) ? -0x4000 : 0x4000));
                speed.x += 0.5f * cM_ssin(dir);
                speed.z += 0.5f * cM_scos(dir);
                setFlag(0x8);
            }
        }
    }
    return TRUE;
}

/* 00000AD4-00000D88       .text runawayInit__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::runawayInit() {
    switch (mUkStatic.m0) {
    case 1:
    case 2:
    case 5:
        if (mAnmIdx == 5) {
            switch (getShapeType()) {
            case 1:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_C_FOUND, 0);
                break;
            case 2:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_D_FOUND, 0);
                break;
            default:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_B_FOUND, 0);
                break;
            }
        }
        speedF = 0.0f;
        setAnm(4, 0);
        break;
    case 3:
        speedF = 0.0f;
        setAnm(5, 0);
        break;
    case 4:
        speed.y = 25.0f;
        gravity = -3.3f;
        speedF = 8.0f;
        setFlag(0x200);
        setAnm(8, 0);
        mState = STATE_JUMP;
        current.angle.y = field_0x6E8;
        switch (getShapeType()) {
        case 1:
            fopAcM_seStart(this, JA_SE_CV_TR_KO_C_CAUGHT, 0);
            break;
        case 2:
            fopAcM_seStart(this, JA_SE_CV_TR_KO_D_CAUGHT, 0);
            break;
        default:
            fopAcM_seStart(this, JA_SE_CV_TR_KO_B_CAUGHT, 0);
            break;
        }
        break;
    }
    return TRUE;
}

/* 00000D88-00000F48       .text nodeCallBack_Uk__FP7J3DNodei */
static BOOL nodeCallBack_Uk(J3DNode* node, int calcTiming) {
    cXyz temp;
    cXyz temp2;
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Uk_c* i_this = (daNpc_Uk_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        int jntNo = joint->getJntNo();

        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == i_this->getHeadJntNum()) {
                temp.setall(0.0f);
                mDoMtx_XrotM(*calc_mtx, (s16)i_this->getHead_y());
                mDoMtx_ZrotM(*calc_mtx, (s16)-i_this->getHead_x());
                MtxPosition(&temp, &temp2);
                i_this->setAttentionBasePos(temp2);
                temp.set(20.0f, -20.0f, 0.0f);
                MtxPosition(&temp, &temp2);
                i_this->setEyePos(temp2);
                i_this->incAttnSetCount();
            } else if (jntNo == i_this->getBackboneJntNum()) {
                mDoMtx_XrotM(*calc_mtx, i_this->getBackbone_y());
                mDoMtx_ZrotM(*calc_mtx, i_this->getBackbone_x());
            }
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, *calc_mtx);
        }
    }
    return TRUE;
}

static const int l_bck_ix_tbl[] = {
    dRes_INDEX_UK_BCK_UK_WAIT_e,
    dRes_INDEX_UK_BCK_UK_TALK01_e,
    dRes_INDEX_UK_BCK_UK_TALK02_e,
    dRes_INDEX_UK_BCK_UK_WALK_e,
    dRes_INDEX_UK_BCK_UK_RUN_e,
    dRes_INDEX_UK_BCK_UK_KEIKAI_e,
    dRes_INDEX_UK_BCK_UK_JIDA01_e,
    dRes_INDEX_UK_BCK_UK_JIDA02_e,
    dRes_INDEX_UK_BCK_UK_DA_e,
    dRes_INDEX_UK_BCK_UK_JUMP_e,
    dRes_INDEX_UK_BCK_UK_LAND_e,
};

static const int l_btp_ix_tbl[] = {
    dRes_INDEX_UK_BTP_UK_MABA_C_e,
};

/* 00000F48-00001070       .text initTexPatternAnm__10daNpc_Uk_cFb */
BOOL daNpc_Uk_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();

    if (getShapeType() != 1) {
        return TRUE;
    }

    m_maba_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Uk", l_btp_ix_tbl[mTexPatternIdx]);
    JUT_ASSERT(679, m_maba_tex_pattern != NULL);

    if (!mBtpAnm.init(modelData, m_maba_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }

    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return TRUE;
}

/* 00001070-00001108       .text playTexPatternAnm__10daNpc_Uk_cFv */
void daNpc_Uk_c::playTexPatternAnm() {
    if (getShapeType() == 1 && cLib_calcTimer(&mBlinkTimer) == 0) {
        if (mBlinkFrame >= m_maba_tex_pattern->getFrameMax()) {
            mBlinkFrame -= m_maba_tex_pattern->getFrameMax();
            mBlinkTimer = cM_rndF(100.0f) + 30.0f;
        } else {
            mBlinkFrame++;
        }
    }
}

/* 00001108-000011C0       .text setAnm__10daNpc_Uk_cFScUc */
void daNpc_Uk_c::setAnm(s8 newAnmIdx, u8 i_flag) {
    f32 morf = 8.0f;

    if (newAnmIdx == 4 && mAnmIdx == 0xa) {
        morf = 0.0f;
    }

    if (i_flag & 1) {
        morf = 0.0f;
        mAnmIdx = 0xb;
    }

    if (newAnmIdx != mAnmIdx && newAnmIdx != -1) {
        mAnmIdx = newAnmIdx;
        mAnmTimer = 0.0f;
        dNpc_setAnm(mpMorf, J3DFrameCtrl::EMode_NULL, morf, 1.0f, l_bck_ix_tbl[mAnmIdx], -1, "Uk");
    }
}

/* 000011C0-00001274       .text chkAttentionLocal__10daNpc_Uk_cFv */
bool daNpc_Uk_c::chkAttentionLocal() {
    dAttention_c& attention = dComIfGp_getAttention();

    if (chkFlag(0x1)) {
        return true;
    }

    if (mAttentionTimer != 0) {
        mAttentionTimer--;
        return true;
    }

    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }

    return this == attention.ActionTarget(0);
}

/* 00001274-00001310       .text chkAttention__10daNpc_Uk_cFv */
void daNpc_Uk_c::chkAttention() {
    bool temp = chkFlag(0x4);

    if (chkAttentionLocal()) {
        setFlag(0x4);
    } else {
        clrFlag(0x4);
    }

    if (temp != chkFlag(0x4) && temp == true) {
        m_jnt.setTrn();
    }
}

/* 00001310-00001378       .text setAnmStatus__10daNpc_Uk_cFv */
void daNpc_Uk_c::setAnmStatus() {
    switch (mState) {
    case STATE_WARNING_B:
    case STATE_WARNING_C:
    case STATE_WARNING_D:
        setAnm(5, 0);
        break;
    case STATE_JITANDA01:
    case STATE_JITANDA02:
        break;
    default:
        setAnm(0, 0);
        break;
    }
}

/* 00001378-000013BC       .text eventOrder__10daNpc_Uk_cFv */
void daNpc_Uk_c::eventOrder() {
    if (ChkOrder(3)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (ChkOrder(2)) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 000013BC-00001420       .text checkOrder__10daNpc_Uk_cFv */
void daNpc_Uk_c::checkOrder() {
    if (eventInfo.mCommand != dEvtCmd_INDEMO_e && eventInfo.mCommand == dEvtCmd_INTALK_e && ChkOrder(3)) {
        setFlag(0x1);
        talkInit();
    }
    ClrOrder(0xFF);
}

/* 00001420-00001464       .text next_msgStatus__10daNpc_Uk_cFPUl */
u16 daNpc_Uk_c::next_msgStatus(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;

    switch (*pMsgNo) {
    case 0x26BF:
    case 0x26C1:
    case 0x26C4:
    case 0x26C6:
    case 0x26C7:
    case 0x26C8:
    case 0x26C9:
    case 0x26CA:
    case 0x26CB:
    case 0x26CC:
    case 0x26CD:
    case 0x26CE:
    case 0x26CF:
    case 0x26D0:
    case 0x26D1:
    case 0x26D2:
    case 0x26D3:
    case 0x26D4:
    case 0x26D5:
    case 0x26D6:
    case 0x26D7:
    case 0x26D8:
        *pMsgNo += 1;
        break;
    default:
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msgStatus;
}

/* 00001464-000015E0       .text getMsg__10daNpc_Uk_cFv */
u32 daNpc_Uk_c::getMsg() {
    u32 msgNo = 0;
    clrFlag(0x8);
    switch (mType) {
    case TYPE_NORMAL:
        if (mState == STATE_DEMO01 || mState == STATE_DEMO02) {
            msgNo = mMsgNo;
        } else if (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0040)) {
            msgNo = getShapeType() + 0x26B6;
        } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1340)) {
            msgNo = getShapeType() + 0x26AE;
        } else if (dComIfGs_isEventBit(getFirstTalk())) {
            msgNo = getShapeType() + 0x26BA;
        } else {
            msgNo = getShapeType() * 2 + 0x26BF;
            dComIfGs_onEventBit(getFirstTalk());
        }
        break;
    case TYPE_MINIGAME:
        if (dComIfGs_isTmpBit(getCaughtFlag())) {
            msgNo = getShapeType() + 0x26B6;
        } else {
            msgNo = getShapeType() + 0x26B2;
            dComIfGs_onTmpBit(getCaughtFlag());
        }
        break;
    }
    return msgNo;
}

/* 000015E0-00001660       .text setCollision__10daNpc_Uk_cFv */
void daNpc_Uk_c::setCollision() {
    cXyz centerPos(current.pos);
    f32 cylCollisionRadius = 40.0f;
    f32 height = 80.0f;
    mCyl.SetC(centerPos);
    mCyl.SetR(cylCollisionRadius);
    mCyl.SetH(height);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 00001660-00001730       .text msgAnm__10daNpc_Uk_cFUc */
void daNpc_Uk_c::msgAnm(u8 i_msgAnmIdx) {
    if (mMsgAnmIdx == i_msgAnmIdx) {
        return;
    }

    mMsgAnmIdx = i_msgAnmIdx;

    switch (mMsgAnmIdx) {
    case 0:
        setAnm(0, 0);
        break;
    case 1:
        setAnm(1, 0);
        break;
    case 2:
        setAnm(2, 0);
        break;
    case 3:
        setAnm(3, 0);
        break;
    case 4:
        setAnm(4, 0);
        break;
    case 5:
        setAnm(6, 0);
        break;
    case 6:
        setAnm(5, 0);
        break;
    case 7:
        setAnm(8, 0);
        break;
    }
}

/* 00001730-00001744       .text talkInit__10daNpc_Uk_cFv */
void daNpc_Uk_c::talkInit() {
    mTalkState = TALK_INIT;
    mMsgAnmIdx = 0xFF;
}

/* 00001744-000018F0       .text talk__10daNpc_Uk_cFv */
u16 daNpc_Uk_c::talk() {
    u16 msgStatus = 0xFF;
    if (mTalkState == TALK_INIT) {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        mCurrMsgNo = getMsg();
        mTalkState = TALK_MSG_CREATE;
    } else if (mTalkState != TALK_FINISHED) {
        if (l_msgId == fpcM_ERROR_PROCESS_ID_e) {
            l_msgId = fopMsgM_messageSet(mCurrMsgNo, this);
        } else {
            if (!chkFlag(0x400)) {
                msgAnm(dComIfGp_getMesgAnimeAttrInfo());
            }
            switch (mTalkState) {
            case TALK_MSG_CREATE:
                l_msg = fopMsgM_SearchByID(l_msgId);
                if (l_msg != NULL) {
                    mTalkState = TALK_ACTIVE;
                    if (chkFlag(0x80)) {
                        dComIfGp_event_setTalkPartner(this);
                        clrFlag(0x80);
                    }
                }
                break;
            case TALK_ACTIVE:
                msgStatus = l_msg->mStatus;
                if (msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
                    l_msg->mStatus = next_msgStatus(&mCurrMsgNo);
                    if (l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                        fopMsgM_messageSet(mCurrMsgNo);
                    }
                } else if (msgStatus == fopMsgStts_BOX_CLOSED_e) {
                    l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                    mTalkState = TALK_FINISHED;
                }
                break;
            }
        }
    }
    return msgStatus;
}

/* 000018F0-00001DE4       .text init__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::init() {
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -30.0f;

    J3DModel* pModel = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    mStts.Init(0x64, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    fopAcM_SetStatusMap(this, 0x27);
    fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);

    switch (mType) {
    case TYPE_NONE:
        setAction(&daNpc_Uk_c::wait_action, NULL);
        break;
    case TYPE_NORMAL:
        if (chkGameStart()) {
            setAction(&daNpc_Uk_c::hind_action, NULL);
            setFlag(0x10);
            fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
        } else {
            setAction(&daNpc_Uk_c::visit_action, NULL);
        }
        break;
    case TYPE_MINIGAME:
        mStts.SetWeight(0xFE);
        mPathRun.setInf(getPath(), current.roomNo, true);
        if (mPathRun.getPath() == NULL) {
            return FALSE;
        }
        if (chkGameStart()) {
            setAction(&daNpc_Uk_c::seek_action, NULL);
        } else {
            setAction(&daNpc_Uk_c::hind_action, NULL);
            setFlag(0x10);
            fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
        }
        fopAcM_OnStatus(this, fopAcStts_UNK40_e);
        break;
    }

    mAttnBasePos.set(current.pos);
    mEyePos.set(current.pos);

    if (mDoLib_clipper::getFar() > 1.0f) {
        fopAcM_setCullSizeFar(this, 5000.0f / mDoLib_clipper::getFar());
    }

    mMtrlSndId = 0;
    mReverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
    return TRUE;
}

/* 00001DE4-00001E38       .text setAttention__10daNpc_Uk_cFb */
void daNpc_Uk_c::setAttention(bool param_1) {
    if (!param_1 && mAttnSetCount >= 2) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    attention_info.position.set(mAttnBasePos.x, mAttnBasePos.y + 45.0f, mAttnBasePos.z);
}

/* 00001E38-00001F5C       .text getLookBackMode__10daNpc_Uk_cFv */
u8 daNpc_Uk_c::getLookBackMode() {
    fopAc_ac_c* pActor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &mLookActorId);
    if (pActor != NULL && mState == STATE_VISIT) {
        if (mVisitMode == VISIT_WAIT || mVisitMode == VISIT_NOTICE_LINK) {
            return 3;
        }
        if (((daNpc_Uk_c*)pActor)->mAnmIdx == 8 || ((daNpc_Uk_c*)pActor)->mAnmIdx == 9) {
            return 2;
        }
    }

    if (chkFlag(0x40)) {
        if (fopAcM_getTalkEventPartner(daPy_getPlayerLinkActorClass()) != this) {
            return 4;
        }
        return 2;
    }

    if (chkFlag(0x20)) {
        return 0;
    }

    if (chkFlag(0x4)) {
        return 1;
    }

    if (mState == STATE_VISIT && (mVisitMode == VISIT_WALK_AROUND_LINK || mVisitMode == VISIT_LEFT_PATH)) {
        return 1;
    }
    return 2;
}

/* 00001F5C-0000218C       .text lookBack__10daNpc_Uk_cFv */
void daNpc_Uk_c::lookBack() {
    cXyz temp2;
    cXyz temp(0.0f, 0.0f, 0.0f);
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    bool headOnlyFollow = false;
    fopAc_ac_c* pActor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &mLookActorId);

    switch (getLookBackMode()) {
    case 0:
        m_jnt.setTrn();
        temp2 = dNpc_playerEyePos(-20.0f);
        dstPos = &temp2;
        break;
    case 1:
        headOnlyFollow = true;
        temp2 = dNpc_playerEyePos(-20.0f);
        dstPos = &temp2;
        break;
    case 2:
        desiredYRot = current.angle.y;
        headOnlyFollow = true;
        break;
    case 3:
        m_jnt.setTrn();
        temp2.set(pActor->current.pos.x, pActor->eyePos.y, pActor->current.pos.z);
        dstPos = &temp2;
        break;
    case 4: {
        daPy_lk_c* pLink = (daPy_lk_c*)fopAcM_getTalkEventPartner(daPy_getPlayerLinkActorClass());
        if (pLink == NULL) {
            pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
        }
        m_jnt.setTrn();
        temp2 = pLink->eyePos;
        dstPos = &temp2;
        temp.set(current.pos);
        temp.y = eyePos.y;
        break;
    }
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&mMaxHeadTurnVelocity, 0x5DC, 4, 0x800);
    } else {
        mMaxHeadTurnVelocity = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPos, temp, desiredYRot, mMaxHeadTurnVelocity, headOnlyFollow);
}

/* 0000218C-00002254       .text getStaffName__10daNpc_Uk_cFv */
char* daNpc_Uk_c::getStaffName() {
    if (mType == TYPE_MINIGAME) {
        switch (getShapeType()) {
        case 1:
            return "UkC2";
        case 2:
            return "UkD2";
        case 0:
            return "UkB2";
        }
    } else {
        switch (getShapeType()) {
        case 2:
            return "UkD";
        case 1:
            return "UkC";
        }
    }
    return "UkB";
}

/* 00002254-000022C4       .text checkDemoStart__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::checkDemoStart() {
    mStaffIdx = dComIfGp_evmng_getMyStaffId(getStaffName(), NULL, 0);
    if (mStaffIdx != -1) {
        mEventAction = getNowEventAction();
        return TRUE;
    }
    return FALSE;
}

/* 000022C4-0000230C       .text getNowEventAction__10daNpc_Uk_cFv */
s32 daNpc_Uk_c::getNowEventAction() {
    static char* action_table[] = {
        "WAIT",
        "TALK",
        "TALK2",
        "HOME",
        "RUN",
        "RUN3",
        "HIND",
        "DISP",
        "SPEAK",
        "LOOK_P",
        "WARNING",
        "JUMP",
        "JUMP2",
        "TURN",
        "WARP",
    };
    return dComIfGp_evmng_getMyActIdx(mStaffIdx, action_table, ARRAY_SIZE(action_table), FALSE, 0);
}

/* 0000230C-00002494       .text visitInit__10daNpc_Uk_cFUc */
void daNpc_Uk_c::visitInit(u8 i_nextVisitMode) {
    switch (i_nextVisitMode) {
    case VISIT_WALK_PATH:
        setAnm(4, 0);
        break;
    case VISIT_RUN_LINK:
        setAnm(4, 0);
        if (mVisitMode == VISIT_WAIT_2) {
            mTimerToReachLink = 0x2D;
        } else {
            mTimerToReachLink = 0;
        }
        break;
    case VISIT_WALK_AROUND_LINK:
        setAnm(3, 0);
        break;
    case VISIT_REACHED_LINK:
        setAnm(4, 0);
        if (mVisitMode == VISIT_WALK_PATH || mVisitMode == VISIT_WAIT || mVisitMode == VISIT_WAIT_2) {
            mRunAroundLinkTimer = 0x2D;
        } else {
            mRunAroundLinkTimer = mTimerToReachLink;
        }
        break;
    case VISIT_NOTICE_LINK:
        setAnm(0, 0);
        mWaitTimer = 5;
        speedF = 0.0f;
        break;
    case VISIT_LEFT_PATH:
        setAnm(0, 0);
        mWaitTimer = 0xF;
        speedF = 0.0f;
        break;
    case VISIT_WAIT:
        setAnm(0, 0);
        mWaitTimer = 0x1E;
        speedF = 0.0f;
        break;
    case VISIT_WAIT_2:
        setAnm(0, 0);
        speedF = 0.0f;
        break;
    default:
        speedF = 0.0f;
        break;
    }
    mVisitMode = i_nextVisitMode;
}

/* 00002494-000025A4       .text visitProc__10daNpc_Uk_cFv */
void daNpc_Uk_c::visitProc() {
    fopAc_ac_c* pActor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &mLookActorId);
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();

    switch (mVisitMode) {
    case VISIT_WALK_PATH:
        approachRun(pActor);
        break;
    case VISIT_RUN_LINK:
        approachRun(pLink);
        break;
    case VISIT_REACHED_LINK:
        if (mTimerToReachLink < 0x2D) {
            mTimerToReachLink++;
        }
        approachRun(pLink);
        break;
    case VISIT_WALK_AROUND_LINK:
    case VISIT_LEFT_PATH:
        aroundWalk(pLink);
        break;
    case VISIT_NOTICE_LINK:
    case VISIT_WAIT:
    case VISIT_WAIT_2:
    case VISIT_WAIT_3:
        surrender();
        break;
    }

    if (mVisitMode >= VISIT_WAIT && mVisitMode < VISIT_WAIT_3 + 1) {
        setFlag(0x20);
    }
}

/* 000025A4-00002628       .text wait01__10daNpc_Uk_cFv */
bool daNpc_Uk_c::wait01() {
    if (chkFlag(0x1)) {
        mPrevState = mState;
        mState = STATE_TALK01;
        setAnmStatus();
    } else {
        SetOrder(0x1);
    }
    return mpMorf->isMorf();
}

/* 00002628-000026CC       .text talk01__10daNpc_Uk_cFv */
bool daNpc_Uk_c::talk01() {
    if (talk() == fopMsgStts_BOX_CLOSED_e) {
        mState = mPrevState;
        setAnmStatus();
        dComIfGp_event_reset();
        clrFlag(0x1);
        mAttentionTimer = 5;
    }
    setFlag(0x20);
    return mpMorf->isMorf();
}

/* 000026CC-0000280C       .text talk02__10daNpc_Uk_cFv */
bool daNpc_Uk_c::talk02() {
    if (talk() == fopMsgStts_BOX_CLOSED_e) {
        if (!mUkStatic.chkGameSet()) {
            mState = mPrevState;
            setAnmStatus();
            dComIfGp_event_reset();
        } else {
            mEventIdx = dComIfGp_evmng_getEventIdx("MK_GAMESET", 0xFF);
            fopAcM_orderChangeEventId(this, mEventIdx, 0, 0xFFFF);
            mDoAud_seStart(JA_SE_END_WHISTLE);
            mState = STATE_DEMO02;
            mPrevState = STATE_RUNAWAY;
        }
        clrFlag(0x1);
        mAttentionTimer = 5;
    }
    setFlag(0x20);
    return mpMorf->isMorf();
}

/* 0000280C-00002968       .text visitTalkInit__10daNpc_Uk_cFv */
u8 daNpc_Uk_c::visitTalkInit() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1F80) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1E02)) {
        mEventIdx = eventInfo.mEventId;
        fopAc_ac_c* pActor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &mLookActorId);
        dComIfGp_event_setTalkPartner(pActor);
        mState = STATE_DEMO02;
        demo02();
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1E04);
        return STATE_DEMO02;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1208) && !dComIfGs_checkGetItem(dItemNo_PICTO_BOX_e) && !dComIfGs_checkGetItem(dItemNo_DELUXE_PICTO_BOX_e)) {
        mEventIdx = eventInfo.mEventId;
        fopAc_ac_c* pActor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &mLookActorId);
        dComIfGp_event_setTalkPartner(pActor);
        mState = STATE_DEMO02;
        demo02();
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1602);
        return STATE_DEMO02;
    }
    return 1;
}

/* 00002968-00002A44       .text visitSetEvent__10daNpc_Uk_cFv */
void daNpc_Uk_c::visitSetEvent() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1F80) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1E02)) {
        eventInfo.setEventName("MK_TALK3");
        return;
    }

    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1208) && !dComIfGs_checkGetItem(dItemNo_PICTO_BOX_e) && !dComIfGs_checkGetItem(dItemNo_DELUXE_PICTO_BOX_e)) {
        eventInfo.setEventName("MK_TALK2");
        return;
    }
    eventInfo.setEventName("MK_TALK");
}

/* 00002A44-00002C80       .text visit01__10daNpc_Uk_cFv */
bool daNpc_Uk_c::visit01() {
    f32 temp;
    fopAc_ac_c* pActor;
    if (chkFlag(0x1)) {
        mPrevState = mState;
        mState = visitTalkInit();
        setAnmStatus();
        speedF = 0.0f;
        mVisitMode = VISIT_TALK;
    } else if (checkDemoStart()) {
        mPrevState = mState;
        mState = STATE_DEMO01;
        setAnmStatus();
        speedF = 0.0f;
        mVisitMode = VISIT_TALK;
        demo01();
    } else {
        u8 nextMode = nextVisitMode();
        if (nextMode != mVisitMode) {
            visitInit(nextMode);
        }
        visitProc();
        if (mAnmIdx == 3) {
            if (mVisitMode == VISIT_WALK_AROUND_LINK) {
                temp = 2.5f;
            } else {
                temp = m690;
            }
        } else if (mAnmIdx == 4) {
            temp = m694;
            if (mVisitMode == VISIT_LEFT_PATH) {
                temp -= 2.5f;
            }
        }

        if (speedF > temp) {
            cLib_chaseF(&speedF, temp, 2.8f);
        } else {
            cLib_chaseF(&speedF, temp, 1.1f);
        }
        SetOrder(0x1);

        if (mVisitMode == VISIT_WALK_AROUND_LINK || mVisitMode == VISIT_LEFT_PATH) {
            daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
            s16 angle = fopAcM_searchActorAngleY(pLink, this) - pLink->shape_angle.y;
            if (angle < 0) {
                angle = -angle;
            }
            if (angle > 0x1800) {
                mOrderFlags &= ~0x01;
            }
        }

        pActor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &mLookActorId);
        if (pActor != NULL) {
            if (((daNpc_Uk_c*)pActor)->mAnmIdx == 8 || ((daNpc_Uk_c*)pActor)->mAnmIdx == 9) {
                mOrderFlags &= ~0x01;
            }
        }

        if (ChkOrder(0x1)) {
            visitSetEvent();
        }
    }
    return true;
}

/* 00002C80-00002D20       .text warningB__10daNpc_Uk_cFv */
bool daNpc_Uk_c::warningB() {
    if (chkPositioning(300.0f, -10.0f, 80.0f, 0x3A98, -0x3A98)) {
        mState = STATE_FOUND;
        mEventIdx = dComIfGp_evmng_getEventIdx("UkB_FOUND", 0xFF);
        fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
    }
    return false;
}

/* 00002D20-00002DC0       .text warningC__10daNpc_Uk_cFv */
bool daNpc_Uk_c::warningC() {
    if (chkPositioning(180.0f, -10.0f, 80.0f, 0x3A98, -0x1388)) {
        mState = STATE_FOUND;
        mEventIdx = dComIfGp_evmng_getEventIdx("UkC_FOUND", 0xFF);
        fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
    }
    return false;
}

/* 00002DC0-00002ED8       .text warningD__10daNpc_Uk_cFv */
bool daNpc_Uk_c::warningD() {
    if (chkPositioning(150.0f, -10.0f, 80.0f, 0x4650, 0)) {
        mState = STATE_FOUND;
        mEventIdx = dComIfGp_evmng_getEventIdx("UkD_FOUND", 0xFF);
        fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
    }
    if (chkPositioning(150.0f, -10.0f, 80.0f, 0, -0x4650)) {
        mState = STATE_FOUND;
        mEventIdx = dComIfGp_evmng_getEventIdx("UkD_FOUND2", 0xFF);
        fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
    }
    return false;
}

/* 00002ED8-00002F74       .text found__10daNpc_Uk_cFv */
bool daNpc_Uk_c::found() {
    if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        mPrevState = STATE_RUNAWAY;
        mState = STATE_DEMO02;
        mUkStatic.init(0x50, 0x12C);
        dComIfGs_onTmpBit(getFoundFlag());
        return demo02();
    }
    fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
    return false;
}

/* 00002F74-00003148       .text runaway__10daNpc_Uk_cFv */
bool daNpc_Uk_c::runaway() {
    u8 temp = mUkStatic.runAwayProc(this, &mPathRun, &mCyl, &field_0x6E8);
    if (temp != mUkStatic.m0) {
        if ((temp == 1 && mUkStatic.m0 == 2) || (temp == 2 && mUkStatic.m0 == 1)) {
            if (cM_rndF(1.0f) < 0.5f) {
                switch (getShapeType()) {
                case 1:
                    fopAcM_seStart(this, JA_SE_CV_TR_KO_C_TURN, 0);
                    break;
                case 2:
                    fopAcM_seStart(this, JA_SE_CV_TR_KO_D_TURN, 0);
                    break;
                default:
                    fopAcM_seStart(this, JA_SE_CV_TR_KO_B_TURN, 0);
                    break;
                }
            }
        }
        mUkStatic.m0 = temp;
        runawayInit();
    }

    if (temp == 3) {
        setFlag(0x20);
    }
    if (mAnmIdx == 4) {
        cLib_chaseF(&speedF, mUkStatic.getSpeedF(15.0f, 18.0f), 2.8f);
    }
    return true;
}

/* 00003148-000031E8       .text jump__10daNpc_Uk_cFv */
bool daNpc_Uk_c::jump() {
    if (!chkFlag(0x200)) {
        setAnm(0, 0);
        gravity = -30.0f;
        speedF = 0.0f;
        if (mpMorf->isMorf()) {
            mState = STATE_JITANDA01;
            setAnm(6, 0);
            SetOrder(0x2);
        }
    }
    return true;
}

/* 000031E8-00003228       .text jitanda01__10daNpc_Uk_cFv */
bool daNpc_Uk_c::jitanda01() {
    if (chkFlag(0x1)) {
        setFlag(0x400);
        mPrevState = STATE_JITANDA02;
        mState = STATE_TALK01;
    } else {
        SetOrder(0x2);
    }
    return true;
}

/* 00003228-000032AC       .text jitanda02__10daNpc_Uk_cFv */
bool daNpc_Uk_c::jitanda02() {
    if (chkFlag(0x1)) {
        mPrevState = mState;
        mState = STATE_TALK01;
    }
    if (checkDemoStart()) {
        mPrevState = mState;
        mState = STATE_DEMO01;
        demo01();
    } else {
        SetOrder(0x1);
    }
    return true;
}

/* 000032AC-00003300       .text demo01__10daNpc_Uk_cFv */
bool daNpc_Uk_c::demo01() {
    if (!checkDemoStart()) {
        mState = mPrevState;
        setAnmStatus();
        return true;
    }
    return demoProc();
}

/* 00003300-000033D4       .text demo02__10daNpc_Uk_cFv */
bool daNpc_Uk_c::demo02() {
    if (dComIfGp_evmng_endCheck(mEventIdx)) {
        mState = mPrevState;
        setAnmStatus();
        dComIfGp_event_reset();
        clrFlag(0x1);
        mAttentionTimer = 5;
        return true;
    }

    if (!checkDemoStart()) {
        JUT_ASSERT(1921, NULL);
    }

    return demoProc();
}

/* 000033D4-00003648       .text demoInitCom__10daNpc_Uk_cFv */
void daNpc_Uk_c::demoInitCom() {
    int* a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "SOUND");
    if (a_intP != NULL) {
        switch (*a_intP) {
        case 1:
            switch (getShapeType()) {
            case 1:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_C_RUN_AWAY, 0);
                break;
            case 2:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_D_RUN_AWAY, 0);
                break;
            default:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_B_RUN_AWAY, 0);
                break;
            }
            break;
        case 2:
            switch (getShapeType()) {
            case 1:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_C_FOUND, 0);
                break;
            case 2:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_D_FOUND, 0);
                break;
            default:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_B_FOUND, 0);
                break;
            }
            break;
        }
    }
}

/* 00003648-000040E0       .text demoProc__10daNpc_Uk_cFv */
bool daNpc_Uk_c::demoProc() {
    BOOL temp = FALSE;
    cXyz* a_xyz;
    int* a_intP;
    if (dComIfGp_evmng_getIsAddvance(mStaffIdx)) {
        demoInitCom();
        switch (mEventAction) {
        case 0:
        case 1:
        case 9:
            speedF = 0.0f;
            setAnm(0, 0);
            break;
        case 2:
            speedF = 0.0f;
            setAnm(2, 0);
            break;
        case 3:
            speedF = 0.0f;
            old.pos = home.pos;
            current.pos = home.pos;
            current.angle.y = home.angle.y;
            break;
        case 4:
        case 5: {
            if (mAnmIdx == 4) {
                speedF = m694;
            } else {
                setAnm(4, 0);
            }

            a_xyz = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos");
            JUT_ASSERT(2015, a_xyz);
            field_0x6CC = current.pos;
            field_0x6D8 = *a_xyz;
            int* pTimer = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Timer");

            if (pTimer != NULL) {
                field_0x6E4 = *pTimer;
            } else {
                field_0x6E4 = -1;
            }
            break;
        }
        case 6:
            speedF = 0.0f;
            setFlag(0x10);
            fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
            mPrevState = STATE_5;
            break;
        case 7:
            setAction(&daNpc_Uk_c::visit_action, NULL);
            mPrevState = mState;
            mState = STATE_DEMO01;
            clrFlag(0x10);
            fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
            break;
        case 8:
            speedF = 0.0f;
            talkInit();
            setFlag(0x80);

            a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "MsgNo");
            JUT_ASSERT(2054, a_intP);

            mMsgNo = *a_intP;
            switch (getShapeType()) {
            case 1:
                setAnm(1, 0);
                break;
            case 2:
                setAnm(2, 0);
                break;
            default:
                setAnm(0, 0);
                break;
            }
            temp = TRUE;
            break;
        case 10:
            speedF = 0.0f;
            setFlag(0x2);
            setAnm(5, 1);
            break;
        case 11:
        case 12:
            setFlag(0x2);
            gravity = -3.3f;
            speed.y = 30.0f;
            speedF = 10.0f;
            setFlag(0x200);
            setAnm(9, 0);
            switch (getShapeType()) {
            case 1:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_C_RUN_AWAY, 0);
                break;
            case 2:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_D_RUN_AWAY, 0);
                break;
            default:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_B_RUN_AWAY, 0);
                break;
            }
            break;
        case 13:
            a_xyz = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos");
            JUT_ASSERT(2027, a_xyz);
            field_0x6CC = current.pos;
            field_0x6D8 = *a_xyz;
            field_0x6E8 = cLib_targetAngleY(&field_0x6CC, &field_0x6D8);
            setAnm(0, 0);
            break;
        case 14:
            speedF = 0.0f;
            a_xyz = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos");
            JUT_ASSERT(2095, a_xyz);

            current.pos = *a_xyz;
            old.pos = *a_xyz;

            a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Angle");
            JUT_ASSERT(2101, a_intP);

            current.angle.y = *a_intP;
            shape_angle.y = *a_intP;
            temp = TRUE;
            break;
        }
    }
    switch (mEventAction) {
    case 4:
    case 5: {
        f32 temp2;
        s16 temp3;
        dNpc_calc_DisXZ_AngY(current.pos, field_0x6D8, &temp2, &temp3);
        if (temp2 < m694 || mUkStatic.chkPointPass(&field_0x6CC, &field_0x6D8, &current.pos) != 0) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            if (mEventAction == 5) {
                current.pos.x = field_0x6D8.x;
                current.pos.z = field_0x6D8.z;
                speedF = 0.0f;
            }
        } else {
            cLib_addCalcAngleS(&current.angle.y, temp3, 4, 0x2000, 0x400);
            cLib_chaseF(&speedF, m694, 1.1f);
            if (field_0x6E4 > 0) {
                field_0x6E4--;
            }
            if (field_0x6E4 == 0) {
                dComIfGp_evmng_cutEnd(mStaffIdx);
            }
        }
        return true;
    }
    case 8: {
        u16 temp4 = talk();
        if (temp4 == fopMsgStts_BOX_CLOSED_e || temp4 == 0xFE) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        }
        setFlag(0x20);
        break;
    }
    case 9:
        setFlag(0x40);
        dComIfGp_evmng_cutEnd(mStaffIdx);
        break;
    case 1:
    case 2:
        setFlag(0x20);
        dComIfGp_evmng_cutEnd(mStaffIdx);
        break;
    case 10:
        if (chkFlag(0x2)) {
            if (mAnmEnded != 0) {
                dComIfGp_evmng_cutEnd(mStaffIdx);
                clrFlag(0x2);
            }
        } else {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        }
        break;
    case 11:
    case 12:
        if (!chkFlag(0x200)) {
            setAnm(10, 0);
            gravity = -30.0f;
            speedF = 0.0f;
            if (chkFlag(0x2)) {
                clrFlag(0x2);
                dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                if (mEventAction == 12) {
                    static cXyz scale = cXyz(0.6f, 0.6f, 0.6f);
                    dComIfGp_particle_set(0x23, &current.pos, &current.angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
                }
            }
        }
        return true;
    case 13:
        if (cLib_addCalcAngleS(&current.angle.y, field_0x6E8, 1, 0x800, 0x800) == 0) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        }
        break;
    default:
        break;
    }

    if (temp) {
        return true;
    }
    return mpMorf->isMorf();
}

/* 000040E0-000041B0       .text wait_action__10daNpc_Uk_cFPv */
BOOL daNpc_Uk_c::wait_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mState = STATE_WAIT;
        setAnmStatus();
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        chkAttention();
        clrFlag(0x200 | 0x20);

        bool temp;
        switch (mState) {
        case STATE_WAIT:
            temp = wait01();
            break;
        case STATE_TALK01:
            temp = talk01();
            break;
        default:
            temp = false;
            break;
        }
        lookBack();
        setAttention(temp);
    }
    return TRUE;
}

/* 000041B0-0000440C       .text seek_action__10daNpc_Uk_cFPv */
BOOL daNpc_Uk_c::seek_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        if (dComIfGs_isTmpBit(getFoundFlag())) {
            mState = STATE_RUNAWAY;
            mUkStatic.init(0x50, 0x12C);
            mUkStatic.setRndPathPos(this, &mPathRun);
        } else {
            mState = (States)(getShapeType() + 6);
        }
        setAnmStatus();
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        chkAttention();
        clrFlag(0x200 | 0x20);

        bool temp;
        switch (mState) {
        case 1: // same numeric state as STATE_TALK01; dispatched to talk02 here
            temp = talk02();
            break;
        case STATE_DEMO01:
            temp = demo01();
            break;
        case STATE_DEMO02:
            temp = demo02();
            break;
        case STATE_5:
            temp = false;
            setAction(&daNpc_Uk_c::hind_action, NULL);
            break;
        case STATE_WARNING_B:
            temp = warningB();
            break;
        case STATE_WARNING_C:
            temp = warningC();
            break;
        case STATE_WARNING_D:
            temp = warningD();
            break;
        case STATE_FOUND:
            temp = found();
            break;
        case STATE_RUNAWAY:
            temp = runaway();
            break;
        case STATE_JUMP:
            temp = jump();
            break;
        case STATE_JITANDA01:
            temp = jitanda01();
            break;
        case STATE_JITANDA02:
            temp = jitanda02();
            break;
        default:
            temp = false;
            break;
        }
        lookBack();
        if (chkFlag(0x40)) {
            temp = true;
        }
        setAttention(temp);
    }
    return TRUE;
}

/* 0000440C-0000457C       .text hind_action__10daNpc_Uk_cFPv */
BOOL daNpc_Uk_c::hind_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        clrFlag(0x200 | 0x20);
        if (mType == TYPE_MINIGAME && chkGameStart()) {
            setAction(&daNpc_Uk_c::seek_action, NULL);
            clrFlag(0x10);
            fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
        }
        if ((mType == TYPE_NORMAL || mType == TYPE_MINIGAME) && checkDemoStart()) {
            bool temp = demoProc();
            lookBack();
            setAttention(temp);
        }
    }
    return TRUE;
}

/* 0000457C-00004774       .text visit_action__10daNpc_Uk_cFPv */
BOOL daNpc_Uk_c::visit_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        if (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0040)) {
            mState = STATE_JITANDA02;
            setAnm(6, 0);
            mStts.SetWeight(0xFE);
        } else {
            mState = STATE_VISIT;
            setAnmStatus();
            mStts.SetWeight(0x64);
        }
        mActionStatus++;
        mVisitMode = VISIT_START;
    } else if (mActionStatus != ACTION_ENDING) {
        bool temp;
        chkAttention();
        clrFlag(0x200 | 0x20);
        switch (mState) {
        case STATE_TALK01:
            temp = talk01();
            break;
        case STATE_VISIT:
            temp = visit01();
            break;
        case STATE_DEMO01:
            temp = demo01();
            break;
        case STATE_DEMO02:
            temp = demo02();
            break;
        case STATE_5:
            temp = false;
            setAction(&daNpc_Uk_c::hind_action, NULL);
            break;
        case STATE_JITANDA02:
            temp = jitanda02();
            break;
        default:
            temp = false;
            break;
        }
        lookBack();
        setAttention(temp);
    }
    return TRUE;
}

/* 00004774-00004A20       .text _draw__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData = pModel->getModelData();
    J3DModelData* pHeadModelData = mpModel->getModelData();
    if (chkFlag(0x10)) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    if (getShapeType() != 0) {
        static int table_bmt[] = {
            -1,
            dRes_INDEX_UK_BMT_UK_C_e,
            dRes_INDEX_UK_BMT_UK_D_e,
        };
        J3DMaterialTable& matTable = pModelData->getMaterialTable();
        J3DTexture* matTex = matTable.getTexture();
        JUTNameTab* matTexName = matTable.getTextureName();
        pModelData->setMaterialTable(
            (J3DMaterialTable*)dComIfG_getObjectRes("Uk", table_bmt[getShapeType()]),
            J3DMatCopyFlag_Texture
        );
        matTable.setTexture(matTex);
        matTable.setTextureName(matTexName);
    }

    if (getShapeType() == 1) {
        mBtpAnm.entry(pHeadModelData, mBlinkFrame);
    }

    mpMorf->entryDL();
    PSMTXCopy(pModel->getAnmMtx(m_jnt.getBackboneJntNum()), mpModel->getBaseTRMtx());
    mDoExt_modelUpdateDL(mpModel);

    if (getShapeType() == 1) {
        mBtpAnm.remove(pHeadModelData);
    }

    cXyz shadowPos(current.pos.x, current.pos.y + 50.0f, current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, pModel, &shadowPos, 300.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr,
        0, 1.0f, &dDlst_shadowControl_c::mSimpleTexObj
    );
    if (mShadowId != 0) {
        dComIfGd_setShadow(
            mShadowId, 1, mpModel, &shadowPos, 300.0f, 20.0f,
            current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr,
            0, 1.0f, &dDlst_shadowControl_c::mSimpleTexObj
        );
    }

    dSnap_RegistFig(DSNAP_TYPE_NPC_MK, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00004A20-00004CE4       .text _execute__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::_execute() {
    m_jnt.setParam(
        /* mMaxBackboneX */ 0,
        /* mMaxBackboneY */ 7300,
        /* mMinBackboneX */ 0,
        /* mMinBackboneY */ -7300,
        /* mMaxHeadX */ 8000,
        /* mMaxHeadY */ 9000,
        /* mMinHeadX */ -2000,
        /* mMinHeadY */ -9000,
        /* mMaxTurnStep */ 1000
    );

    playTexPatternAnm();

    mAnmEnded = mpMorf->play(&eyePos, mMtrlSndId, mReverb);
    if (mpMorf->getFrame() < mAnmTimer) {
        mAnmEnded = 1;
    }

    mAnmTimer = mpMorf->getFrame();
    if (mAnmEnded != 0) {
        switch (mAnmIdx) {
        case 6:
            if (cM_rnd() < 0.4f) {
                setAnm(7, 0);
            }
            break;
        case 7:
            setAnm(6, 0);
            break;
        }
    }
    checkOrder();
    (this->*mCurrActionFunc)(NULL);
    eventOrder();

    if (!chkFlag(0x100)) {
        shape_angle.y = current.angle.y;
    }
    clrFlag(0x100);
    mMtrlSndId = 0;

    if (!chkFlag(0x10)) {
        if (chkFlag(0x8)) {
            fopAcM_posMove(this, mStts.GetCCMoveP());
        } else {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        mObjAcch.CrrPos(*dComIfG_Bgsp());

        if (mObjAcch.ChkGroundHit()) {
            clrFlag(0x200);
            mMtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
        } else {
            setFlag(0x200);
        }

        tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    } else {
        setFlag(0x200);
    }
    clrFlag(0x8);

    J3DModel* pModel = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    if (chkFlag(0x10)) {
        mCyl.OffCoSetBit();
    } else {
        mCyl.OnCoSetBit();
        setCollision();
    }
    return TRUE;
}

/* 00004CE4-00004D34       .text _delete__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::_delete() {
    dComIfG_resDelete(&mPhs, "Uk");
    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00004D34-00004D54       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Uk_c*)i_this)->CreateHeap();
}

/* 00004D54-00005028       .text _create__10daNpc_Uk_cFv */
cPhs_State daNpc_Uk_c::_create() {
    fopAcM_ct_Retail(this, daNpc_Uk_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Uk");
    if (state == cPhs_COMPLEATE_e) {
        if (fopAcM_GetName(this) != fpcNm_NPC_UK_e) {
            return cPhs_ERROR_e;
        }

        switch (getType()) {
        case TYPE_NORMAL:
            mType = TYPE_NORMAL;
            switch (getShapeType()) {
            case 0:
                m690 = 2.5f;
                m694 = 10.0f;
                break;
            case 1:
                m690 = 2.6f;
                m694 = 8.5f;
                break;
            case 2:
                m690 = 2.0f;
                m694 = 7.0f;
                break;
            }
            break;
        case TYPE_MINIGAME:
            mType = TYPE_MINIGAME;
            argument = getShapeType() + 5;
            m694 = 14.0f;
            break;
        default:
            mType = TYPE_NONE;
            break;
        }

        if (!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0xB7B0)) {
            mpMorf = NULL;
            return cPhs_ERROR_e;
        }

        tevStr.mRoomNo = current.roomNo;
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -35.0f, -10.0f, -35.0f, 35.0f, 100.0f, 35.0f);

        if (!init()) {
            mpMorf = NULL;
            return cPhs_ERROR_e;
        }
    }
    return state;
}

/* 000053D8-00005728       .text CreateHeap__10daNpc_Uk_cFv */
BOOL daNpc_Uk_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Uk", dRes_INDEX_UK_BDL_UK_e);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Uk", dRes_INDEX_UK_BCK_UK_WAIT_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x15021222
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(2772, m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(2775, m_jnt.getBackboneJntNum() >= 0);

    static int head_bdl_table[] = {
        dRes_INDEX_UK_BDL_UKHEAD_B_e,
        dRes_INDEX_UK_BDL_UKHEAD_C_e,
        dRes_INDEX_UK_BDL_UKHEAD_D_e,
    };
    mpModel = mDoExt_J3DModel__create(
        (J3DModelData*)dComIfG_getObjectRes("Uk", head_bdl_table[getShapeType()]),
        0x80000,
        0x11020022
    );
    JUT_ASSERT(2790, mpModel != NULL);
    if (mpModel == NULL) {
        return FALSE;
    }

    mTexPatternIdx = 0;
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }

    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == getHeadJntNum() || i == getBackboneJntNum()) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Uk);
        }
    }

    mpMorf->getModel()->setUserArea((u32)(this));

    mAcchCir.SetWall(60.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    mObjAcch.SetGroundCheckOffset(100.0f);
    fopAcM_SetMaxFallSpeed(this, -90.0f);
    mVisitMode = 0;
    return TRUE;
}

/* 00005728-00005748       .text daNpc_Uk_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Uk_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Uk_c*)i_this)->_create();
}

/* 00005748-00005768       .text daNpc_Uk_Delete__FP10daNpc_Uk_c */
static BOOL daNpc_Uk_Delete(daNpc_Uk_c* i_this) {
    return ((daNpc_Uk_c*)i_this)->_delete();
}

/* 00005768-00005788       .text daNpc_Uk_Execute__FP10daNpc_Uk_c */
static BOOL daNpc_Uk_Execute(daNpc_Uk_c* i_this) {
    return ((daNpc_Uk_c*)i_this)->_execute();
}

/* 00005788-000057A8       .text daNpc_Uk_Draw__FP10daNpc_Uk_c */
static BOOL daNpc_Uk_Draw(daNpc_Uk_c* i_this) {
    return ((daNpc_Uk_c*)i_this)->_draw();
}

/* 000057A8-000057B0       .text daNpc_Uk_IsDelete__FP10daNpc_Uk_c */
static BOOL daNpc_Uk_IsDelete(daNpc_Uk_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Uk_Method = {
    (process_method_func)daNpc_Uk_Create,
    (process_method_func)daNpc_Uk_Delete,
    (process_method_func)daNpc_Uk_Execute,
    (process_method_func)daNpc_Uk_IsDelete,
    (process_method_func)daNpc_Uk_Draw,
};

actor_process_profile_definition g_profile_NPC_UK = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_UK_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Uk_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_UK_e,
    /* Actor SubMtd */ &l_daNpc_Uk_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
