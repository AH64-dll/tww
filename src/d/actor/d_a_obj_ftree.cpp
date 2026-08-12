/**
 * d_a_obj_ftree.cpp
 * Object - Forest Trees
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ftree.h"
#include "d/actor/d_a_player.h"
#include "d/d_a_obj.h"

namespace daObjFtree {
static u8 ret_tree_no[] = {0x0F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x0F, 0x06, 0x07};
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
void daObjFtree::Act_c::place_heart_part() {
    /* Nonmatching */
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
BOOL daObjFtree::Act_c::SetJointAnimation(int, float, float, int) {
    /* Nonmatching */
}

/* 000008D8-00000910       .text PlayStopJointAnimation__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::PlayStopJointAnimation() {
    /* Nonmatching */
}

/* 00000910-0000093C       .text PlayStopColorAnimation__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::PlayStopColorAnimation() {
    /* Nonmatching */
}

/* 0000093C-00000A1C       .text set_first_stat__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_first_stat() {
    /* Nonmatching */
}

/* 00000A1C-00000C1C       .text set_collision__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_collision() {
    /* Nonmatching */
}

/* 00000C1C-00000D50       .text talk_ct__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::talk_ct() {
    /* Nonmatching */
}

/* 00000D50-00000F14       .text talk_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::talk_main() {
    /* Nonmatching */
}

/* 00000F14-00000FC4       .text get_tev_material0_color__Q210daObjFtree5Act_cFP12J3DModelDataUlPsPsPs */
void daObjFtree::Act_c::get_tev_material0_color(J3DModelData*, unsigned long, short*, short*, short*) {
    /* Nonmatching */
}

/* 00000FC4-00001070       .text set_tev_color__Q210daObjFtree5Act_cFP12J3DModelDataUlsss */
void daObjFtree::Act_c::set_tev_color(J3DModelData*, unsigned long, short, short, short) {
    /* Nonmatching */
}

/* 00001070-000010F0       .text is_broughtID__10daObjFtreeFi */
BOOL daObjFtree::is_broughtID(int) {
    /* Nonmatching */
}

/* 000010F0-00001138       .text is_brought__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::is_brought() {
    /* Nonmatching */
}

/* 00001138-000011FC       .text set_broughtID__Q210daObjFtree5Act_cFi */
void daObjFtree::Act_c::set_broughtID(int) {
    /* Nonmatching */
}

/* 000011FC-00001260       .text set_brought__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_brought() {
    /* Nonmatching */
}

/* 00001260-000012D0       .text unset_broughtID__Q210daObjFtree5Act_cFi */
void daObjFtree::Act_c::unset_broughtID(int) {
    /* Nonmatching */
}

/* 000012D0-00001334       .text unset_brought__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::unset_brought() {
    /* Nonmatching */
}

/* 00001334-000013A0       .text get_ftree_info__Q210daObjFtree5Act_cFPQ210daObjFtree18_ftree_seach_info_ */
void daObjFtree::Act_c::get_ftree_info(daObjFtree::_ftree_seach_info_*) {
    /* Nonmatching */
}

/* 000013A0-00001400       .text iam_last__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::iam_last() {
    /* Nonmatching */
}

/* 00001400-00001414       .text action_none_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_none_init(s16) {
    /* Nonmatching */
}

/* 00001414-00001418       .text action_none_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_none_main() {
    /* Nonmatching */
}

/* 00001418-000014E8       .text action_waitS_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_waitS_init(s16) {
    /* Nonmatching */
}

/* 000014E8-00001608       .text action_waitS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitS_main() {
    /* Nonmatching */
}

/* 00001608-0000173C       .text action_waitM_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_waitM_init(s16) {
    /* Nonmatching */
}

/* 0000173C-00001878       .text action_waitM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitM_main() {
    /* Nonmatching */
}

/* 00001878-000018AC       .text action_waitL_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_waitL_init(s16) {
    /* Nonmatching */
}

/* 000018AC-000019BC       .text action_waitL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitL_main() {
    /* Nonmatching */
}

/* 000019BC-00001A4C       .text action_pikupikuS_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_pikupikuS_init(s16) {
    /* Nonmatching */
}

/* 00001A4C-00001AF4       .text action_pikupikuS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuS_main() {
    /* Nonmatching */
}

/* 00001AF4-00001B4C       .text action_pikupikuM_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_pikupikuM_init(s16) {
    /* Nonmatching */
}

/* 00001B4C-00001C44       .text action_pikupikuM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuM_main() {
    /* Nonmatching */
}

/* 00001C44-00001C9C       .text action_pikupikuL_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_pikupikuL_init(s16) {
    /* Nonmatching */
}

/* 00001C9C-00001D94       .text action_pikupikuL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuL_main() {
    /* Nonmatching */
}

/* 00001D94-00001EAC       .text action_changeSL_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeSL_init(s16) {
    /* Nonmatching */
}

/* 00001EAC-00001F0C       .text action_changeSL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSL_main() {
    /* Nonmatching */
}

/* 00001F0C-00001FB4       .text action_changeSL2_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeSL2_init(s16) {
    /* Nonmatching */
}

/* 00001FB4-00002300       .text action_changeSL2_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSL2_main() {
    /* Nonmatching */
}

/* 00002300-00002344       .text action_changeLS_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeLS_init(s16) {
    /* Nonmatching */
}

/* 00002344-000025DC       .text action_changeLS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeLS_main() {
    /* Nonmatching */
}

/* 000025DC-000026AC       .text action_changeLS2_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeLS2_init(s16) {
    /* Nonmatching */
}

/* 000026AC-0000270C       .text action_changeLS2_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeLS2_main() {
    /* Nonmatching */
}

/* 0000270C-00002794       .text action_changeSM_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeSM_init(s16) {
    /* Nonmatching */
}

/* 00002794-000027F4       .text action_changeSM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSM_main() {
    /* Nonmatching */
}

/* 000027F4-00002840       .text action_changeMS_init__Q210daObjFtree5Act_cFs */
s32 daObjFtree::Act_c::action_changeMS_init(s16) {
    /* Nonmatching */
}

/* 00002840-00002860       .text action_changeMS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeMS_main() {
    /* Nonmatching */
}

/* 00002860-00002A4C       .text process_init__Q210daObjFtree5Act_cFis */
s32 daObjFtree::Act_c::process_init(int, s16) {
    /* Nonmatching */
}

/* 00002A4C-00002BF0       .text process_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::process_main() {
    /* Nonmatching */
}

/* 00002BF0-00002C14       .text solidHeapCB__Q210daObjFtree5Act_cFP10fopAc_ac_c */
BOOL daObjFtree::Act_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002C14-00002D94       .text NodeCallBack_Effect__Q210daObjFtree5Act_cFP7J3DNodei */
BOOL daObjFtree::Act_c::NodeCallBack_Effect(J3DNode*, int) {
    /* Nonmatching */
}

/* 00002D94-00002DDC       .text Ftree_NodeCallBack_Effect__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_Effect(J3DNode*, int) {
    /* Nonmatching */
}

/* 00002DDC-00002E9C       .text Ftree_NodeCallBack_M__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_M(J3DNode*, int) {
    /* Nonmatching */
}

/* 00002E9C-00002F5C       .text Ftree_NodeCallBack_L__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_L(J3DNode*, int) {
    /* Nonmatching */
}

/* 00002F5C-00003354       .text create_heap__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::create_heap() {
    /* Nonmatching */
}

/* 00003354-000035F4       .text _create__Q210daObjFtree5Act_cFv */
cPhs_State daObjFtree::Act_c::_create() {
    /* Nonmatching */
}

/* 00003FB8-00004004       .text _delete__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_delete() {
    /* Nonmatching */
}

/* 00004004-00004144       .text set_mtx__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00004144-000042C4       .text _execute__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_execute() {
    /* Nonmatching */
}

/* 000042C4-0000455C       .text _draw__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjFtree {
namespace {
/* 0000455C-0000457C       .text Mthd_Create__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_create();
}

/* 0000457C-000045A0       .text Mthd_Delete__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_delete();
}

/* 000045A0-000045C4       .text Mthd_Execute__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_Execute(void*) {
    /* Nonmatching */
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
