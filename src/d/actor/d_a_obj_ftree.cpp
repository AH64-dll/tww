/**
 * d_a_obj_ftree.cpp
 * Object - Forest Trees
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ftree.h"
#include "d/actor/d_a_player.h"
#include "res/Object/Vmr.h"
#include "d/d_a_obj.h"

namespace daObjFtree {
u32 message_table[] = {0, 0x149F, 0x14A0, 0x14A1, 0, 0, 0, 0, 0, 0, 0x149F, 0x14A0, 0x14A1};

static const u32 L_attr[] = {
    0x42740000, 0x42C00000, 0x41C80000, 0x42500000, 0x43040000, 0x446D8000, 0x42900000, 0x42140000,
    0xC2140000, 0x00140000, 0x3E4CCCCD, 0x3E4CCCCD, 0x3CA3D70A, 0x42480000, 0x41A00000, 0x008C0000,
    0x43020000, 0x3FE00000, 0x41F00000, 0x23280000, 0x44570000, 0xC0066666, 0x002F0000, 0x001E0000,
};

static const dCcD_SrcCyl M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0xFF1DFEFF,
        /* SrcObjTg  SPrm    */ 0xF,
        /* SrcObjCo  SPrm    */ 0x79,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0x3,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};

static const dCcD_SrcCyl M_cyl_srcW = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0x100,
        /* SrcObjTg  SPrm    */ 0xF,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};
}


/* 00000078-000000DC       .text search_heart_part__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::search_heart_part() {
    if (mSpawnedHeartPieceProcessId != fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* heart_piece;
        if (fopAcM_SearchByID(mSpawnedHeartPieceProcessId, &heart_piece) == 0) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2E20);
            mSpawnedHeartPieceProcessId = fpcM_ERROR_PROCESS_ID_e;
        }
    }
}

/* 000000DC-000001F0       .text launch_heart_part__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::launch_heart_part() {
    csXyz angle = shape_angle;
    cXyz scale(1.0f, 1.0f, 1.0f);
    cXyz pos = current.pos;
    angle.y += 0x2328;
    pos.y += 860.0f;

    fopAc_ac_c* heart_piece = (fopAc_ac_c*)fopAcM_fastCreateItem(&pos, 7, current.roomNo, &angle, &scale, 1.75f, 30.0f, -2.1f);
    if (heart_piece != NULL) {
        mSpawnedHeartPieceProcessId = fopAcM_GetID(heart_piece);
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_9B07, param_get_tree_idx());
        heart_piece->actor_status = fopAcStts_UNK4000_e | fopAcStts_UNK40_e;
        m648 = 1;
        return TRUE;
    }
    return FALSE;
}

/* 000001F0-00000394       .text place_heart_part__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::place_heart_part() {
    /* Nonmatching */
    if (m356 == -1) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0102) == TRUE) {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E20)) {
                if (dComIfGs_getEventReg(dSv_event_flag_c::UNK_9B07) == param_get_tree_idx()) {
                    cXyz offset(0.0f, 1.0f, 310.0f);
                    s16 rot = (s16)(shape_angle.y + 0x2328);
                    mDoMtx_stack_c::transS(current.pos);
                    mDoMtx_stack_c::YrotM(rot);
                    Mtx mtx;
                    cMtx_copy(mDoMtx_stack_c::get(), mtx);
                    cXyz pos;
                    PSMTXMultVec(mtx, &offset, &pos);
                    cXyz scale(1.0f, 1.0f, 1.0f);
                    csXyz angle(0, 0, 0);
                    fopAc_ac_c* heart_piece = (fopAc_ac_c*)fopAcM_fastCreateItem(&pos, 7, current.roomNo, &angle, &scale, 0.0f, 0.0f, -2.1f);
                    if (heart_piece != NULL) {
                        mSpawnedHeartPieceProcessId = fopAcM_GetID(heart_piece);
                        dComIfGs_setEventReg(dSv_event_flag_c::UNK_9B07, param_get_tree_idx());
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

/* 00000394-00000454       .text Ftree_get_water_pos__10daObjFtreeFP4cXyzP4cXyz */
void daObjFtree::Ftree_get_water_pos(cXyz* o_pos, cXyz* i_pos) {
    cXyz local_pos(0.0f, 0.0f, 50.0f);
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    s16 angle = cM_atan2s(i_pos->x - player->current.pos.x, i_pos->z - player->current.pos.z);
    mDoMtx_stack_c::transS(player->current.pos);
    mDoMtx_stack_c::YrotM(angle);
    Mtx mtx;
    cMtx_copy(mDoMtx_stack_c::get(), mtx);
    PSMTXMultVec(mtx, &local_pos, o_pos);
}

/* 00000454-000004B8       .text estimate_water__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::estimate_water() {
    cXyz water_pos;
    Ftree_get_water_pos(&water_pos, &current.pos);
    f32 dist_sq = PSVECSquareDistance(&water_pos, &current.pos);
    return dist_sq <= (m4C8 + 20.0f) * (m4C8 + 20.0f);
}

/* 000004B8-000004DC       .text Ftree_checkXyEventCallBack__10daObjFtreeFPvi */
s16 daObjFtree::Ftree_checkXyEventCallBack(void* i_this, int i_idx) {
    return g_dComIfG_gameInfo.play.mSelectItem[i_idx] == 0x59 ? 1 : 0;
}

/* 000004DC-000004FC       .text Ftree_XyEventCallBack__10daObjFtreeFPvi */
s16 daObjFtree::Ftree_XyEventCallBack(void* i_this, int i_idx) {
    return ((daObjFtree::Act_c*)i_this)->XyEventCallBack(i_idx);
}

/* 000004FC-000005E4       .text XyEventCallBack__Q210daObjFtree5Act_cFi */
s16 daObjFtree::Act_c::XyEventCallBack(int i_idx) {
    if (g_dComIfG_gameInfo.play.mSelectItem[i_idx] == 0x59) {
        if (!is_brought()) {
            if (estimate_water()) {
                if (!iam_last()) {
                    if (XyEvent_set(mEventCam1Idx)) {
                        m652 = 0x8c;
                        return mEventCam1Idx;
                    }
                } else {
                    if (XyEvent_set(mEventCam2Idx)) {
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0102);
                        m652 = 0x8c;
                        return mEventCam2Idx;
                    }
                }
            }
        }
    }
    if (XyEvent_set(mEventCam0Idx)) {
        return mEventCam0Idx;
    }
    return -1;
}

/* 000005E4-000005F8       .text XyEvent_init__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::XyEvent_init() {
    m356 = -1;
    m358 = 0;
}

/* 000005F8-0000062C       .text XyEvent_set__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::XyEvent_set(s16 i_event) {
    if (m358 == 0) {
        if (i_event != -1) {
            m356 = i_event;
            m358 = 1;
            return TRUE;
        }
    }
    return FALSE;
}

/* 0000062C-00000764       .text XyEvent_exe__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::XyEvent_exe() {
    switch (m358) {
    case 1:
        if (eventInfo.checkCommandTalk()) {
            m358 = 2;
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            cXyz offset(0.0f, 1.0f, 108.0f);
            s16 rot = (s16)(shape_angle.y + 0x2328);
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(rot);
            Mtx mtx;
            cMtx_copy(mDoMtx_stack_c::get(), mtx);
            cXyz result;
            PSMTXMultVec(mtx, &offset, &result);
            player->setPlayerPosAndAngle(&result, (s16)(rot + 0x8000));
        }
        break;
    case 2:
        if (dComIfGp_getPEvtManager()->endCheck(m356)) {
            dComIfGp_event_reset();
            XyEvent_init();
        }
        break;
    }
}

namespace daObjFtree {
static const u8 ret_tree_no[] = {0x0F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x0F, 0x06, 0x07};
}

/* 00000764-000007A8       .text param_get_tree_idx__Q210daObjFtree5Act_cCFv */
s32 daObjFtree::Act_c::param_get_tree_idx() const {
    static const u8 ret_num = 0xA;
    s32 tree_no = daObj::PrmAbstract(this, 4, 0);
    if (tree_no < ret_num) {
        return ret_tree_no[tree_no];
    }
    return 0xF;
}

/* 000007A8-000008D8       .text SetJointAnimation__Q210daObjFtree5Act_cFiffi */
BOOL daObjFtree::Act_c::SetJointAnimation(int i_anm, float i_f1, float i_f2, int i_arg) {
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, i_anm);
    s32 v = cLib_maxLimit(i_arg, 0);
    if (anm != NULL) {
    /* Nonmatching */
        if (v == 0) {
            mpMorf->setAnm(anm, 0, i_f2, i_f1, 0.0f, -1.0f, NULL);
        } else {
            mpMorf->setAnm(anm, 0, i_f2, i_f1, 0.0f, (float)i_arg + (float)anm->getFrameMax(), NULL);
        }
        return TRUE;
    }
    return FALSE;
}

/* 000008D8-00000910       .text PlayStopJointAnimation__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::PlayStopJointAnimation() {
    return mpMorf->play(NULL, 0, 0) ? TRUE : FALSE;
}

/* 00000910-0000093C       .text PlayStopColorAnimation__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::PlayStopColorAnimation() {
    return mBrkAnm.play() ? TRUE : FALSE;
}

/* 0000093C-00000A1C       .text set_first_stat__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_first_stat() {
    if (dComIfGs_isSymbol(2) != 0) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0102) != 0) {
            process_init(3, 0);
            m63C = 1.0f;
        } else if (is_brought() == 0) {
            process_init(1, 0);
            m63C = 0.2f;
        } else {
            process_init(2, 0);
            m63C = 0.2f;
        }
    } else {
        process_init(0, 0);
    }
}

/* 00000A1C-00000C1C       .text set_collision__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_collision() {
    if (m2A6 == 1 || m2A7 == 1) {
        if (m508.ChkTgHit()) {
            if (m2A6 == 1) {
                daObj::HitSeStart(&current.pos, current.roomNo, &m508, 8);
            } else {
                daObj::HitSeStart(&current.pos, current.roomNo, &m508, 7);
                daObj::HitEff_kikuzu(this, &m508);
            }
            dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
            m508.ClrTgHit();
        } else if (m2A6 == 1) {
            cXyz pos = current.pos;
            pos.y -= 50.0f;
            m398.SetR(61.0f);
            m398.SetH(96.0f);
            m398.SetC(pos);
            dComIfG_Ccsp()->Set(&m398);
            m4C8 = 61.0f;
            m508.SetR(61.0f);
            m508.SetH(96.0f);
            m508.SetC(current.pos);
            dComIfG_Ccsp()->Set(&m508);
        } else if (m2A7 == 1) {
            m4C8 = 132.0f * m63C;
            m508.SetR(m4C8);
            m508.SetH(950.0f * m63C);
            m508.SetC(current.pos);
            dComIfG_Ccsp()->Set(&m508);
        }
    }
}

/* 00000C1C-00000D50       .text talk_ct__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::talk_ct() {
    m6A4 = -1;
    m6A8 = NULL;
    cXyz pos = current.pos;
    cXyz pos2 = current.pos;
    if (mMode >= 0 && mMode < 0xD) {
        switch (message_table[mMode]) {
        case 0x149F:
            pos2.y += 80.0f;
            pos.y += 105.0f;
            attention_info.flags = 0x800000A;
            break;
        case 0x14A0:
            pos2.y += 90.0f;
            pos.y += 195.0f;
            attention_info.flags = 0x800000A;
            break;
        case 0x14A1:
            pos2.y += 250.0f;
            pos.y += 200.0f;
            attention_info.flags = 0x8000008;
            break;
        }
    }
    attention_info.position = pos;
    eyePos = pos2;
}

/* 00000D50-00000F14       .text talk_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::talk_main() {
    /* Nonmatching */
    if (m356 == -1 && eventInfo.mCommand == dEvtCmd_INTALK_e) {
        if (m6A4 == fpcM_ERROR_PROCESS_ID_e) {
            m6A4 = fopMsgM_messageSet(message_table[mMode], this);
            m6A8 = NULL;
            return;
        }
        if (m6A8 == NULL) {
            m6A8 = fopMsgM_SearchByID(m6A4);
            return;
        }
        switch (m6A8->mStatus) {
        case fopMsgStts_MSG_DISPLAYED_e:
            m6A8->mStatus = fopMsgStts_MSG_ENDS_e;
            return;
        case fopMsgStts_BOX_CLOSED_e:
            m6A8->mStatus = fopMsgStts_MSG_DESTROYED_e;
            g_dComIfG_gameInfo.play.mEvtCtrl.mEventFlag |= 8;
            talk_ct();
            return;
        }
        return;
    }
    if (mMode >= 0 && mMode < 0xD && message_table[mMode] != 0) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        if (PSVECSquareDistance(&current.pos, &player->current.pos) <=
            (m4C8 + 130.0f) * (m4C8 + 130.0f)) {
            talk_ct();
            if (player != NULL) {
                cXyz diff = current.pos - player->current.pos;
                s16 diffAngle = cM_atan2s(diff.x, diff.z) - player->shape_angle.y;
                if (diffAngle <= 0) {
                    diffAngle = -diffAngle;
                }
                if (diffAngle <= 0x4000) {
                    eventInfo.mCondition |= 1;
                }
            }
            eventInfo.mCondition |= 0x20;
        }
    }
}

/* 00000F14-00000FC4       .text get_tev_material0_color__Q210daObjFtree5Act_cFP12J3DModelDataUlPsPsPs */
void daObjFtree::Act_c::get_tev_material0_color(J3DModelData* modelData, unsigned long i_idx, short* o_r, short* o_g, short* o_b) {
    J3DMaterial* mat = modelData->getJointNodePointer(0)->getMesh();
    if (mat != NULL) {
        *o_r = mat->mTevBlock->getTevColor(i_idx)->mColor.r;
        *o_g = mat->mTevBlock->getTevColor(i_idx)->mColor.g;
        *o_b = mat->mTevBlock->getTevColor(i_idx)->mColor.b;
    }
}

/* 00000FC4-00001070       .text set_tev_color__Q210daObjFtree5Act_cFP12J3DModelDataUlsss */
void daObjFtree::Act_c::set_tev_color(J3DModelData* modelData, unsigned long i_idx, short i_r, short i_g, short i_b) {
    J3DMaterial* mat = modelData->getJointNodePointer(0)->getMesh();
    while (mat != NULL) {
        mat->mTevBlock->getTevColor(i_idx)->mColor.r = i_r;
        mat->mTevBlock->getTevColor(i_idx)->mColor.g = i_g;
        mat->mTevBlock->getTevColor(i_idx)->mColor.b = i_b;
        mat = mat->mNext;
    }
}

/* 00001070-000010F0       .text is_broughtID__10daObjFtreeFi */
BOOL daObjFtree::is_broughtID(int i_id) {
    u8 ret = TRUE;
    dSv_event_c* event = &g_dComIfG_gameInfo.save.getEvent();
    u8 reg = event->getEventReg(dSv_event_flag_c::UNK_9EFF);
    if (((reg >> (i_id & 7)) & 1) == 0 && event->isEventBit(dSv_event_flag_c::UNK_0102) == 0) {
        ret = FALSE;
    }
    return ret;
}

/* 000010F0-00001138       .text is_brought__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::is_brought() {
    s32 tree_no = daObj::PrmAbstract(this, 4, 0);
    if (tree_no < 0xA) {
        tree_no = ret_tree_no[tree_no];
    } else {
        tree_no = 0xF;
    }
    return is_broughtID(tree_no);
}

/* 00001138-000011FC       .text set_broughtID__Q210daObjFtree5Act_cFi */
void daObjFtree::Act_c::set_broughtID(int i_id) {
    u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_9EFF);
    int bit = 1 << (i_id & 7);
    reg |= bit;
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_9EFF, reg);
    reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_9AFF);
    reg |= bit;
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_9AFF, reg);

    _ftree_seach_info_ info;
    get_ftree_info(&info);
    if (info.mBroughtCount == info.mCount) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0102);
    }
}

/* 000011FC-00001260       .text set_brought__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_brought() {
    s32 tree_no = daObj::PrmAbstract(this, 4, 0);
    if (tree_no < 0xA) {
        tree_no = ret_tree_no[tree_no];
    } else {
        tree_no = 0xF;
    }
    set_broughtID(tree_no);
    m638 = 1;
}

/* 00001260-000012D0       .text unset_broughtID__Q210daObjFtree5Act_cFi */
void daObjFtree::Act_c::unset_broughtID(int i_id) {
    dSv_event_c* event = &g_dComIfG_gameInfo.save.getEvent();
    u8 reg = event->getEventReg(dSv_event_flag_c::UNK_9EFF);
    int bit = 1 << (i_id & 7);
    reg &= ~bit;
    event->setEventReg(dSv_event_flag_c::UNK_9EFF, reg);
}

/* 000012D0-00001334       .text unset_brought__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::unset_brought() {
    s32 tree_no = daObj::PrmAbstract(this, 4, 0);
    if (tree_no < 0xA) {
        tree_no = ret_tree_no[tree_no];
    } else {
        tree_no = 0xF;
    }
    unset_broughtID(tree_no);
    m638 = 0;
}

/* 00001334-000013A0       .text get_ftree_info__Q210daObjFtree5Act_cFPQ210daObjFtree18_ftree_seach_info_ */
void daObjFtree::Act_c::get_ftree_info(daObjFtree::_ftree_seach_info_* info) {
    info->mCount = 8;
    info->mBroughtCount = 0;
    for (u32 i = 0; i < 8; i++) {
        if (is_broughtID(i)) {
            info->mBroughtCount++;
        }
    }
}

/* 000013A0-00001400       .text iam_last__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::iam_last() {
    _ftree_seach_info_ info;
    get_ftree_info(&info);
    if (is_brought() == 0 && info.mBroughtCount >= info.mCount - 1) {
        return TRUE;
    }
    return FALSE;
}

/* 00001400-00001414       .text action_none_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_none_init(s16) {
    m2A6 = 0;
    m2A7 = 0;
    return 1;
}

/* 00001414-00001418       .text action_none_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_none_main() {}

/* 00001418-000014E8       .text action_waitS_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_waitS_init(s16) {
    m2A6 = 1;
    m2A7 = 0;
    unset_brought();

    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e));
    if (brk != NULL) {
        if (mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, 0, 1.0f, 0, -1, 1, FALSE) != 0) {
            return SetJointAnimation(6, 1.0f, 0.0f, 0);
        }
    }
    return 0;
}

/* 000014E8-00001608       .text action_waitS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitS_main() {
    if (m652 == 1) {
        s32 ret;
        if (m356 == mEventCam2Idx) {
            ret = process_init(4, 0);
        } else {
            ret = process_init(8, 0);
        }
        if (ret != 0) {
            m652 = 0;
            return;
        }
    }
    s32 hit = m508.ChkCoHit();
    if (m67C == 0 && hit == 1 && process_init(10, 1)) {
        hit = 0;
    } else if ((s32)cM_rndF(100.0f) == 0 && mMode == 1) {
        process_init(10, 1.0f + 4.0f * cM_rndF(1.0f));
    }
    m67C = hit;
}

/* 00001608-0000173C       .text action_waitM_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_waitM_init(s16) {
    set_brought();
    m2A6 = 1;
    m2A7 = 0;

    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e));
    if (brk != NULL) {
        if (mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, 0, -1.0f, 0, -1, 1, FALSE) != 0) {
            if (SetJointAnimation(5, -1.0f, 0.0f, 0) != 0) {
                mpMorf->setFrame(mpMorf->getEndFrame() - 1.0f);
                return 1;
            }
        }
    }
    return 0;
}

/* 0000173C-00001878       .text action_waitM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitM_main() {
    if (dComIfGs_getFwaterTimer() == 0) {
        _ftree_seach_info_ info;
        get_ftree_info(&info);
        if (info.mCount != info.mBroughtCount) {
            process_init(9, 0);
            return;
        }
    }
    if (mMode == 2) {
        s32 hit = m508.ChkCoHit();
        if (dKy_rain_check() != 0) {
            process_init(0xB, -1);
        } else if (m67C == 0 && hit == 1 && process_init(0xB, 0x78)) {
            hit = 0;
        } else if ((s32)cM_rndF(90.0f) == 0) {
            process_init(0xB, 30.0f + 90.0f * cM_rndF(1.0f));
        }
        m67C = hit;
    }
}

/* 00001878-000018AC       .text action_waitL_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_waitL_init(s16) {
    m2A7 = 1;
    m2A6 = 0;
    set_brought();
    return 1;
}

/* 000018AC-000019BC       .text action_waitL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitL_main() {
    if (mMode == 3) {
        if (dKy_rain_check() != 0) {
            process_init(0xC, -1);
            return;
        }
        if ((s32)cM_rndF(30.0f) == 0) {
            process_init(0xC, 100.0f + 80.0f * cM_rndF(1.0f));
            return;
        }
        if (m356 != -1) {
            process_init(0xC, -1);
            return;
        }
    } else if (mMode == 0xC) {
        if (dKy_rain_check() == 0 && m69A == -1 && m356 == -1) {
            process_init(3, 0);
        }
    }
}

/* 000019BC-00001A4C       .text action_pikupikuS_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_pikupikuS_init(s16 i_cnt) {
    /* Nonmatching */
    s32 cnt = i_cnt > 0 ? i_cnt : 1;
    m2A6 = 1;
    m2A7 = 0;
    m688 = cnt;
    m68C = 0;
    return SetJointAnimation(6, 0.7f + 0.50000006f * cM_rndF(1.0f), 10.0f, 0);
}

/* 00001A4C-00001AF4       .text action_pikupikuS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuS_main() {
    if (PlayStopJointAnimation()) {
        if (m68C < m688) {
            SetJointAnimation(6, 0.7f + 0.3f * cM_rndF(1.0f), 10.0f, 0);
        } else {
            process_init(1, 0);
        }
        m68C++;
    }
    action_waitS_main();
}

/* 00001AF4-00001B4C       .text action_pikupikuM_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_pikupikuM_init(s16 i_cnt) {
    set_brought();
    m690 = i_cnt;
    m692 = 0;
    m694 = 0;
    m2A6 = 1;
    m2A7 = 0;
    return 1;
}

/* 00001B4C-00001C44       .text action_pikupikuM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuM_main() {
    /* Nonmatching */
    s16 cnt = m692;
    s16 max = m690;
    if (cnt < max || max == -1) {
        f32 sin = jmaSinTable[(u16)m694 >> jmaSinShift];
        m696 = (s16)(100.0f * sin);
        sin = jmaSinTable[(u16)m694 >> jmaSinShift];
        m698 = (s16)(300.0f * sin);
        m694 += 0xFA0;
    } else if (cnt >= max) {
        process_init(2, 0);
    }
    m692++;
    action_waitM_main();
}

/* 00001C44-00001C9C       .text action_pikupikuL_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_pikupikuL_init(s16 i_cnt) {
    set_brought();
    m69A = i_cnt;
    m69C = 0;
    m69E = 0;
    m2A6 = 0;
    m2A7 = 1;
    return 1;
}

/* 00001C9C-00001D94       .text action_pikupikuL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuL_main() {
    /* Nonmatching */
    s16 cnt = m69C;
    s16 max = m69A;
    if (cnt < max || max == -1) {
        f32 sin = jmaSinTable[(u16)m69E >> jmaSinShift];
        m6A0 = (s16)(30.0f * sin);
        sin = jmaSinTable[(u16)m69E >> jmaSinShift];
        m6A2 = (s16)(36.0f * sin);
        m69E += 0xBB8;
    } else if (cnt >= max) {
        process_init(3, 0);
    }
    m69C++;
    action_waitL_main();
}

/* 00001D94-00001EAC       .text action_changeSL_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeSL_init(s16) {
    m2A6 = 1;
    m2A7 = 0;

    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e));
    if (brk != NULL) {
        if (mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, 0, 1.0f, 0, -1, 1, FALSE) != 0
            && SetJointAnimation(5, 1.0f, 10.0f, 0) != 0) {
            set_brought();
            JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_DK_TREE_RECOVER, &current.pos, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            return 1;
        }
    }
    return 0;
}

/* 00001EAC-00001F0C       .text action_changeSL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSL_main() {
    BOOL joint = PlayStopJointAnimation();
    BOOL color = PlayStopColorAnimation();
    if (joint == 1 && color == 1) {
        process_init(5, 0);
    }
}

/* 00001F0C-00001FB4       .text action_changeSL2_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeSL2_init(s16) {
    m2A6 = 1;
    m2A7 = 0;
    m2A4 = 1;
    m640 = 0.0f;
    m684 = 0x1E;
    m63C = 0.2f;
    get_tev_material0_color(mpMorf->getModel()->getModelData(), 2, &m65C, &m65E, &m660);
    m66C = m65C;
    m66E = m65E;
    m670 = m660;
    m672 = m662;
    m69E = 0;
    return 1;
}

/* 00001FB4-00002300       .text action_changeSL2_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSL2_main() {
    /* Nonmatching */
    if (m2A6 != 0) {
        cLib_addCalc(&m640, 1.0f, 0.2f, 1.0f, 0.007f);
        m66C = (s16)((f32)m65C + (255.0f - (f32)m65C) * m640);
        m66E = (s16)((f32)m65E + (255.0f - (f32)m65E) * m640);
        m670 = (s16)((f32)m660 + (255.0f - (f32)m660) * m640);
        if (m640 == 1.0f) {
            if (m684 > 0) {
                m684--;
            }
            if (m684 == 0) {
                m2A6 = 0;
                m2A7 = 1;
            }
        }
    }
    if (m2A7 != 0) {
        f32 ratio;
        if (m63C <= 0.2f) {
            ratio = 0.0f;
        } else {
            ratio = 1.0f;
            if (m63C >= ratio) {
            } else {
                ratio = (m63C - 0.2f) / 0.8f;
            }
        }
        cLib_addCalc(&m63C, 1.0f, 0.02f, 1.0f, 0.005f);
        m674.r = (s16)(255.0f + ((f32)m664.r - 255.0f) * ratio);
        m674.g = (s16)(255.0f + ((f32)m664.g - 255.0f) * ratio);
        m674.b = (s16)(255.0f + ((f32)m664.b - 255.0f) * ratio);
        if (m63C == 1.0f) {
            if (process_init(3, 0) != 0) {
                m650 = 0x2f;
            }
        }
        m6A0 = (s16)(30.0f * jmaSinTable[(u16)m69E >> jmaSinShift]);
        m6A2 = (s16)(36.0f * jmaSinTable[(u16)m69E >> jmaSinShift]);
        m69E += 0xBB8;
    }
}

/* 00002300-00002344       .text action_changeLS_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeLS_init(s16) {
    m2A6 = 0;
    m2A7 = 1;
    m640 = 1.0f;
    m63C = 1.0f;
    unset_brought();
    return 1;
}

/* 00002344-000025DC       .text action_changeLS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeLS_main() {
    if (m2A7 != 0) {
        f32 ratio = (m63C <= 0.2f) ? 0.0f : ((m63C >= 1.0f) ? 1.0f : (m63C - 0.2f) / 0.8f);
        cLib_addCalc(&m63C, 0.2f, 0.02f, 1.0f, 0.005f);
        m674.r = (s16)(255.0f + ((f32)m664.r - 255.0f) * ratio);
        m674.g = (s16)(255.0f + ((f32)m664.g - 255.0f) * ratio);
        m674.b = (s16)(255.0f + ((f32)m664.b - 255.0f) * ratio);
        if (m63C == 0.2f) {
            m2A6 = 1;
            m2A7 = 0;
        }
    }
    if (m2A6 != 0) {
        cLib_addCalc(&m640, 0.0f, 0.2f, 1.0f, 0.007f);
        m66C = (s16)((f32)m65C + (255.0f - (f32)m65C) * m640);
        m66E = (s16)((f32)m65E + (255.0f - (f32)m65E) * m640);
        m670 = (s16)((f32)m660 + (255.0f - (f32)m660) * m640);
        if (m640 == 0.0f) {
            process_init(7, 0);
        }
    }
}

/* 000025DC-000026AC       .text action_changeLS2_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeLS2_init(s16) {
    m2A6 = 1;
    m2A7 = 0;

    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e));
    if (brk != NULL) {
        if (mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, 0, -1.0f, 0, -1, 1, FALSE) != 0) {
            return SetJointAnimation(5, -0.7f, 10.0f, -0x14);
        }
    }
    return 0;
}

/* 000026AC-0000270C       .text action_changeLS2_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeLS2_main() {
    BOOL joint = PlayStopJointAnimation();
    BOOL color = PlayStopColorAnimation();
    if (joint == 1 && color == 1) {
        process_init(1, 0);
    }
}

/* 0000270C-00002794       .text action_changeSM_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeSM_init(s16) {
    set_brought();
    if (action_changeSL_init(0) == 1) {
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_DK_TREE_RECOVER, &current.pos, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
        return 1;
    }
    return 0;
}

/* 00002794-000027F4       .text action_changeSM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSM_main() {
    BOOL joint = PlayStopJointAnimation();
    BOOL color = PlayStopColorAnimation();
    if (joint == 1 && color == 1) {
        process_init(2, 0);
    }
}

/* 000027F4-00002840       .text action_changeMS_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeMS_init(s16) {
    if (action_changeLS2_init(0)) {
        unset_brought();
        return 1;
    }
    return 0;
}

/* 00002840-00002860       .text action_changeMS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeMS_main() {
    action_changeLS2_main();
}

/* 00002860-00002A4C       .text process_init__Q210daObjFtree5Act_cFis */
s32 daObjFtree::Act_c::process_init(int i_state, s16 i_arg) {
    static ProcInitFunc init_table[] = {
        &Act_c::action_none_init,
        &Act_c::action_waitS_init,
        &Act_c::action_waitM_init,
        &Act_c::action_waitL_init,
        &Act_c::action_changeSL_init,
        &Act_c::action_changeSL2_init,
        &Act_c::action_changeLS_init,
        &Act_c::action_changeLS2_init,
        &Act_c::action_changeSM_init,
        &Act_c::action_changeMS_init,
        &Act_c::action_pikupikuS_init,
        &Act_c::action_pikupikuM_init,
        &Act_c::action_pikupikuL_init,
    };
    if (i_state >= 0 && i_state < 0xD) {
    /* Nonmatching */
        if ((this->*init_table[i_state])(i_arg)) {
            m696 = 0;
            m698 = 0;
            m6A0 = 0;
            m6A2 = 0;
            mMode = i_state;
            return TRUE;
        }
    }
    return FALSE;
}

/* 00002A4C-00002BF0       .text process_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::process_main() {
    static ProcMainFunc main_table[] = {
        &Act_c::action_none_main,
        &Act_c::action_waitS_main,
        &Act_c::action_waitM_main,
        &Act_c::action_waitL_main,
        &Act_c::action_changeSL_main,
        &Act_c::action_changeSL2_main,
        &Act_c::action_changeLS_main,
        &Act_c::action_changeLS2_main,
        &Act_c::action_changeSM_main,
        &Act_c::action_changeMS_main,
        &Act_c::action_pikupikuS_main,
        &Act_c::action_pikupikuM_main,
        &Act_c::action_pikupikuL_main,
    };
    if (mMode >= 0 && mMode < 0xD) {
    /* Nonmatching */
        (this->*main_table[mMode])();
    }
}

/* 00002BF0-00002C14       .text solidHeapCB__Q210daObjFtree5Act_cFP10fopAc_ac_c */
BOOL daObjFtree::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 00002C14-00002D94       .text NodeCallBack_Effect__Q210daObjFtree5Act_cFP7J3DNodei */
BOOL daObjFtree::Act_c::NodeCallBack_Effect(J3DNode* i_node, int i_param) {
    if (m2A4 == 1 && i_param == 0) {
        J3DJoint* joint = (J3DJoint*)i_node;
        Mtx mtx;
        cXyz pos(0.0f, 0.0f, 0.0f);
        cXyz out;
        J3DModel* model = j3dSys.getModel();
        mDoMtx_stack_c::copy(model->getAnmMtx(joint->getJntNo()));
        PSMTXCopy(mDoMtx_stack_c::now, mtx);
        PSMTXMultVec(mtx, &pos, &out);

        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_DK_TREE_GROW_UP, &current.pos, 0, 0, 1.0f, 1.0f,
                                        -1.0f, -1.0f, 0);
        JPABaseEmitter* emitter1 = dComIfGp_particle_set(dPa_name::ID_AK_SN_HANASAKAFLASH00, &out);
        JPABaseEmitter* emitter2 = dComIfGp_particle_set(dPa_name::ID_AK_SN_HANASAKAFLASH01, &out);
        if (emitter1 != NULL && emitter2 != NULL) {
            m2A4 = 0;
        }
    }
    return TRUE;
}

/* 00002D94-00002DDC       .text Ftree_NodeCallBack_Effect__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_Effect(J3DNode* i_node, int i_param) {
    if (!i_param) {
        J3DModel* model = j3dSys.getModel();
        return ((daObjFtree::Act_c*)model->getUserArea())->NodeCallBack_Effect(i_node, i_param);
    }
    return TRUE;
}

/* 00002DDC-00002E9C       .text Ftree_NodeCallBack_M__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_M(J3DNode* i_node, int i_param) {
    if (i_param == 0) {
        u32 jnt_no = ((J3DJoint*)i_node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        Act_c* area = (Act_c*)model->getUserArea();
        if (area != NULL) {
            csXyz rot(area->m294, area->m296, 0);
            mDoMtx_stack_c::copy(model->getAnmMtx(jnt_no));
            mDoMtx_stack_c::ZXYrotM(rot.x, rot.y, rot.z);
            PSMTXCopy(mDoMtx_stack_c::now, model->getAnmMtx(jnt_no));
            PSMTXCopy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00002E9C-00002F5C       .text Ftree_NodeCallBack_L__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_L(J3DNode* i_node, int i_param) {
    if (i_param == 0) {
        u32 jnt_no = ((J3DJoint*)i_node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        Act_c* area = (Act_c*)model->getUserArea();
        if (area != NULL) {
            csXyz rot(0, area->m298, area->m29A);
            mDoMtx_stack_c::copy(model->getAnmMtx(jnt_no));
            mDoMtx_stack_c::ZXYrotM(rot.x, rot.y, rot.z);
            PSMTXCopy(mDoMtx_stack_c::now, model->getAnmMtx(jnt_no));
            PSMTXCopy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00002F5C-00003354       .text create_heap__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::create_heap() {
    J3DAnmTransform* tmp_bck_data = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BCK_VMRTY_e);
    JUT_ASSERT(0x836, tmp_bck_data != 0);

    J3DModelData* mdl_dataS = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BDL_VMRTY_e);
    JUT_ASSERT(0x83C, mdl_dataS != 0);
    if (mdl_dataS == NULL) {
        return false;
    }

    mpMorf = new mDoExt_McaMorf(
        mdl_dataS, NULL, NULL,
        tmp_bck_data,
        J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1,
        NULL,
        0,
        0x11020203
    );
    if (mpMorf == NULL) {
        return false;
    }
    mpMorf->getModel()->setUserArea((u32)this);

    mdl_dataS->getJointNodePointer(2)->setCallBack(Ftree_NodeCallBack_Effect);
    mdl_dataS->getJointNodePointer(3)->setCallBack(Ftree_NodeCallBack_M);
    mdl_dataS->getJointNodePointer(4)->setCallBack(Ftree_NodeCallBack_M);
    mdl_dataS->getJointNodePointer(5)->setCallBack(Ftree_NodeCallBack_M);

    J3DModelData* mdl_dataL = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BDL_VMRTO_e);
    JUT_ASSERT(0x85B, mdl_dataL != 0);
    if (mdl_dataL == NULL) {
        return false;
    }
    mpModel = mDoExt_J3DModel__create(mdl_dataL, 0, 0x11020203);
    if (mpModel == NULL) {
        return false;
    }
    mpModel->setUserArea((u32)this);
    mdl_dataL->getJointNodePointer(1)->setCallBack(Ftree_NodeCallBack_L);

    J3DAnmTevRegKey* brk_data = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e);
    JUT_ASSERT(0x86B, brk_data != 0);
    if (brk_data == NULL) {
        return false;
    }
    int brkOk = mBrkAnm.init(mdl_dataS, brk_data, 1, 0, 1.0f, 0, -1, 0);

    get_tev_material0_color(mpMorf->getModel()->getModelData(), 2, &m654.r, &m654.g, &m654.b);
    m66C = m654.r;
    m66E = m654.g;
    m670 = m654.b;
    m672 = m654.a;

    get_tev_material0_color(mpModel->getModelData(), 2, &m664.r, &m664.g, &m664.b);
    m674.r = m664.r;
    m674.g = m664.g;
    m674.b = m664.b;
    m674.a = m664.a;

    return mdl_dataS != 0 && mpMorf != 0 && mpMorf->getModel() != 0 && mdl_dataL != 0 && brk_data != 0 && brkOk != 0;
}

/* 00003354-000035F4       .text _create__Q210daObjFtree5Act_cFv */
cPhs_State daObjFtree::Act_c::_create() {
    fopAcM_SetupActor(this, daObjFtree::Act_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            s32 tree_no = daObj::PrmAbstract(this, 4, 0);
            m644 = tree_no < 10 ? ret_tree_no[tree_no] : 0xF;
            m648 = 0;
            mSpawnedHeartPieceProcessId = fpcM_ERROR_PROCESS_ID_e;
            set_first_stat();
            talk_ct();

            cXyz pos(current.pos.x, current.pos.y + 100.0f, current.pos.z);
            mGndChk.SetPos(&pos);
            mGndChk.SetActorPid(fopAcM_GetID(this));
            m34C = dComIfG_Bgsp()->GroundCross(&mGndChk);
            set_mtx();
            cullMtx = mpMorf->getModel()->getBaseTRMtx();
            fopAcM_setCullSizeBox(this, -300.0f, 0.0f, -300.0f, 300.0f, 1000.0f, 300.0f);

            m35C.Init(0xFF, 0xFF, this);
            m398.Set(M_cyl_srcW);
            m398.SetStts(&m35C);
            m398.SetTgVec((cXyz&)cXyz::Zero);
            m398.OnTgNoHitMark();

            m4CC.Init(0xFF, 0xFF, this);
            m508.Set(M_cyl_src);
            m508.SetStts(&m4CC);
            m508.SetTgVec((cXyz&)cXyz::Zero);
            m508.OnTgNoHitMark();

            XyEvent_init();
            eventInfo.setXyCheckCB(Ftree_checkXyEventCallBack);
            eventInfo.setXyEventCB(Ftree_XyEventCallBack);

            mEventCam0Idx = dComIfGp_evmng_getEventIdx("morinoki_camera0", 0xFF);
            mEventCam1Idx = dComIfGp_evmng_getEventIdx("morinoki_camera1", 0xFF);
            mEventCam2Idx = dComIfGp_evmng_getEventIdx("morinoki_camera2", 0xFF);
        } else {
            phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 00003FB8-00004004       .text _delete__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_delete() {
    if (m638 != 0) {
        set_brought();
    }
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 00004004-00004144       .text set_mtx__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_mtx() {
    /* Nonmatching */
    mpMorf->getModel()->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    PSMTXCopy(mDoMtx_stack_c::now, mpMorf->getModel()->getBaseTRMtx());
    PSMTXCopy(mDoMtx_stack_c::now, m2A8);

    cXyz sp(scale.x * m63C, scale.y * m63C, scale.z * m63C);
    mpModel->setBaseScale(sp);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    PSMTXCopy(mDoMtx_stack_c::now, mpModel->getBaseTRMtx());
    PSMTXCopy(mDoMtx_stack_c::now, m2A8);

    mpModel->calc();
}

/* 00004144-000042C4       .text _execute__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_execute() {
    if (mMode == 0) {
        return true;
    }

    search_heart_part();
    talk_main();
    set_mtx();
    process_main();
    set_collision();
    fopAcM_rollPlayerCrash(this, m4C8, 7);

    s16 spd = mMode == 0xB ? 1 : 0x1E;
    cLib_addCalcAngleS2(&m294, m696, spd, 0x1000);
    cLib_addCalcAngleS2(&m296, m698, spd, 0x1000);

    s16 spd2 = (mMode == 0xC || mMode == 0x5) ? 1 : 0xA;
    cLib_addCalcAngleS2(&m298, m6A0, spd2, 0x1000);
    cLib_addCalcAngleS2(&m29A, m6A2, spd2, 0x1000);

    XyEvent_exe();
    if (m648 == 0) {
        m648 = place_heart_part();
    }
    if (m650 == 1) {
        if (launch_heart_part() != 0) {
            m650 = 0;
        }
    }
    if (m652 > 1) {
        m652--;
    }
    if (m650 > 1) {
        m650--;
    }
    return true;
}

/* 000042C4-0000455C       .text _draw__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_draw() {
    if (mMode == 0) {
        return true;
    }

    if (m2A6 == 1) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
        dComIfGd_setListBG();

        if (mMode == 5 || mMode == 6) {
            mBrkAnm.remove(mpMorf->getModel()->getModelData());
            set_tev_color(mpMorf->getModel()->getModelData(), 2, m66C, m66E, m670);
        } else {
            J3DModelData* md = mpMorf->getModel()->getModelData();
            f32 fr = mBrkAnm.getFrame();
            mBrkAnm.entry(md, fr);
        }
        mpMorf->updateDL();
        dComIfGd_setList();

        cXyz pos(current.pos.x, current.pos.y, current.pos.z);
        dComIfGd_setSimpleShadow2(&pos, m34C, 75.0f, mGndChk, shape_angle.y, 1.0f,
                                  &dDlst_shadowControl_c::mSimpleTexObj);
    }

    if (m2A7 == 1) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModel, &tevStr);
        dComIfGd_setListBG();

        set_tev_color(mpModel->getModelData(), 2, m674.r, m674.g, m674.b);
        mDoExt_modelUpdateDL(mpModel);
        dComIfGd_setList();

        f32 ratio = (m63C <= 0.2f) ? 0.0f : ((m63C >= 1.0f) ? 1.0f : (m63C - 0.2f) / 0.8f);
        cXyz pos(current.pos.x, current.pos.y, current.pos.z);
        dComIfGd_setSimpleShadow2(&pos, m34C, 75.0f * (1.0f + 2.5f * ratio), mGndChk,
                                  shape_angle.y, 1.0f, &dDlst_shadowControl_c::mSimpleTexObj);
    }
    return true;
}

namespace daObjFtree {
namespace {
char Act_c::M_arcname[] = "Vmr";

/* 0000455C-0000457C       .text Mthd_Create__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_create();
}

/* 0000457C-000045A0       .text Mthd_Delete__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_delete();
}

/* 000045A0-000045C4       .text Mthd_Execute__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_execute();
}

/* 000045C4-000045E8       .text Mthd_Draw__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_draw();
}

/* 000045E8-000045F0       .text Mthd_IsDelete__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjFtree

actor_process_profile_definition g_profile_Obj_Ftree = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Ftree_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjFtree::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Ftree_e,
    /* Actor SubMtd */ &daObjFtree::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

