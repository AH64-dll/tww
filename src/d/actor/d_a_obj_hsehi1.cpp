/**
 * d_a_obj_hsehi1.cpp
 * Object - Tower of the Gods - Command Melody monument & blue monument next to Companion Statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hsehi1.h"
#include "m_Do/m_Do_mtx.h"
#include "d/actor/d_a_player_main.h"

/* 000000EC-00000130       .text __ct__15daObj_hsh_HIO_cFv */
daObj_hsh_HIO_c::daObj_hsh_HIO_c() {
    static const struct init_data_t {
        f32 m0;
        f32 m4;
        f32 m8;
        s16 mC;
        u8 mE;
    } init_data = {250.0f, 0.0f, 0.0f, 0x4000, 0};

    mNo = -1;
    m08 = init_data.m0;
    m0C = init_data.m4;
    m10 = init_data.m8;
    m14 = init_data.mC;
    m16 = init_data.mE;
}

static daObj_hsh_HIO_c l_HIO;
static s32 l_hio_counter;
static u32 l_msgId;
static msg_class* l_msg;

static void (daObj_hsh_c::*event_init_tbl[8])(int) = {
    &daObj_hsh_c::initialDefault,
    &daObj_hsh_c::initialLinkDispEvent,
    &daObj_hsh_c::initialMsgSetEvent,
    &daObj_hsh_c::initialDefault,
    &daObj_hsh_c::initialDefault,
    &daObj_hsh_c::initialJudgeEvent,
    &daObj_hsh_c::initialAppearEvent,
    &daObj_hsh_c::initialDeleteEvent,
};

static BOOL (daObj_hsh_c::*event_action_tbl[8])(int) = {
    &daObj_hsh_c::actionDefault,
    &daObj_hsh_c::actionDefault,
    &daObj_hsh_c::actionMsgSetEvent,
    &daObj_hsh_c::actionMessageEvent,
    &daObj_hsh_c::actionTactEvent,
    &daObj_hsh_c::actionDefault,
    &daObj_hsh_c::actionAppearEvent,
    &daObj_hsh_c::actionDeleteEvent,
};

/* 00000130-000002A4       .text __dt__11daObj_hsh_cFv */
daObj_hsh_c::~daObj_hsh_c() {
    if (argument == 0) {
        dComIfG_resDelete(&mPhase, "Hsehi1");
    } else {
        dComIfG_resDelete(&mPhase, "Hsehi2");
    }
    if (m4D4 != NULL) {
        dComIfG_Bgsp()->Release(m4D4);
    }
    emitterDelete(&m4A0);
    if (l_HIO.mNo >= 0) {
        mDoHIO_root.deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
}

/* 000002A4-000002C4       .text daObj_hsh_XyCheckCB__FPvi */
static s16 daObj_hsh_XyCheckCB(void* i_this, int i_itemBtn) {
    return ((daObj_hsh_c*)i_this)->XyCheckCB(i_itemBtn);
}

/* 000002C4-000002E8       .text XyCheckCB__11daObj_hsh_cFi */
s16 daObj_hsh_c::XyCheckCB(int i_itemBtn) {
    return dComIfGp_getSelectItem(i_itemBtn) == dItemNo_WIND_WAKER_e ? TRUE : FALSE;
}

/* 000002E8-00000308       .text daObj_hsh_XyEventCB__FPvi */
static s16 daObj_hsh_XyEventCB(void* i_this, int i_itemBtn) {
    return ((daObj_hsh_c*)i_this)->XyEventCB(i_itemBtn);
}

/* Nonmatching */
/* 00000308-00000390       .text XyEventCB__11daObj_hsh_cFi */
s16 daObj_hsh_c::XyEventCB(int) {
    mDoAud_seStart(JA_SE_PRE_TAKT, &eyePos, 0, dComIfGp_getReverb(current.roomNo));
    m504 |= 1;
    m515 = 0;
    return m530[0];
}

/* 00000390-000003F4       .text particle_set__11daObj_hsh_cFUs */
void daObj_hsh_c::particle_set(unsigned short i_particleID) {
    dComIfGp_particle_set(i_particleID, &current.pos, &current.angle);
}

/* 000003F4-00000488       .text particle_set__11daObj_hsh_cFPP14JPABaseEmitterUs */
void daObj_hsh_c::particle_set(JPABaseEmitter** pEmitter, unsigned short i_particleID) {
    if (*pEmitter == NULL) {
        *pEmitter = dComIfGp_particle_set(i_particleID, &current.pos, &current.angle);
        if (*pEmitter != NULL) {
            (*pEmitter)->mFlags |= 0x40;
        }    }
}

/* 00000488-000004C4       .text emitterDelete__11daObj_hsh_cFPP14JPABaseEmitter */
void daObj_hsh_c::emitterDelete(JPABaseEmitter** pEmitter) {
    if (*pEmitter != NULL) {
        (*pEmitter)->mFlags &= ~0x40;
        (*pEmitter)->becomeInvalidEmitter();
        *pEmitter = NULL;
    }
}

/* 000004C4-00000568       .text setAttention__11daObj_hsh_cFb */
void daObj_hsh_c::setAttention(bool i_param) {
    if(!i_param) {
        return;
    }
    f32 eye_y;
    f32 attn_y;
    if(argument == 0) {
        eye_y = current.pos.y + 90.0f + l_HIO.m10;
        attn_y = current.pos.y + 180.0f + l_HIO.m0C;
    } else {
        eye_y = current.pos.y + 80.0f + l_HIO.m10;
        attn_y = current.pos.y + 120.0f + l_HIO.m0C;
    }
    eyePos.set(current.pos.x, eye_y, current.pos.z);
    attention_info.position.set(current.pos.x, attn_y, current.pos.z);
}

/* 00000568-000005AC       .text onOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::onOffDraw() {
    m504 |= 8;
    if(m4D4 != NULL) {
        dComIfG_Bgsp()->Release(m4D4);
    }
}

/* 000005AC-000005F4       .text offOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::offOffDraw() {
    m504 &= ~8;
    if(m4D4 != NULL) {
        dComIfG_Bgsp()->Regist(m4D4, this);
    }
}

/* 000005F4-0000062C       .text drawStop__11daObj_hsh_cFv */
void daObj_hsh_c::drawStop() {
    onOffDraw();
    emitterDelete(&m4A0);
}

/* 0000062C-0000064C       .text drawStart__11daObj_hsh_cFv */
void daObj_hsh_c::drawStart() {
    offOffDraw();
}

/* 0000064C-000006C8       .text setBaseMtx__11daObj_hsh_cFv */
void daObj_hsh_c::setBaseMtx() {
    J3DModel* model = mpModel;
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    PSMTXCopy(mDoMtx_stack_c::get(), m4A4);
}

/* 000006C8-00000910       .text createHeap__11daObj_hsh_cFv */
BOOL daObj_hsh_c::createHeap() {
    if (argument == 0) {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hsehi1", 4);
        JUT_ASSERT(0x1F9, modelData != 0);
        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL) {
            return 0;
        }
        m4D4 = new dBgW();
        if (m4D4 != NULL) {
            if (m4D4->Set((cBgD_t*)dComIfG_getObjectRes("Hsehi1", 7), cBgW::MOVE_BG_e, &m4A4) == false) {
                goto fail;
            }
            return 0;
        }
        return 0;
    } else {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hsehi2", 4);
        JUT_ASSERT(0x20F, modelData != 0);
        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL) {
            return 0;
        }
        m4D4 = new dBgW();
        if (m4D4 != NULL) {
            if (m4D4->Set((cBgD_t*)dComIfG_getObjectRes("Hsehi2", 7), cBgW::MOVE_BG_e, &m4A4) == false) {
                goto fail;
            }
            return 0;
        }
        return 0;
    }
fail:
    return 1;
}

/* 00000910-00000930       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c* i_this) {
    return ((daObj_hsh_c*)i_this)->createHeap();
}

/* 00000930-00000B44       .text create__11daObj_hsh_cFv */
cPhs_State daObj_hsh_c::create() {
    static u32 a_heap_size_tbl = 0x4000;

    cPhs_State phase_state = cPhs_COMPLEATE_e;

    fopAcM_ct(this, daObj_hsh_c);

    if (argument == 0) {
        if (dComIfGs_isEventBit(0x2510)) {
            return cPhs_ERROR_e;
        }
    }

    if (argument == 0) {
        phase_state = dComIfG_resLoad(&mPhase, "Hsehi1");
    } else {
        phase_state = dComIfG_resLoad(&mPhase, "Hsehi2");
    }
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, checkCreateHeap, a_heap_size_tbl)) {
            m4D4 = NULL;
            return cPhs_ERROR_e;
        }
        cullMtx = mpModel->getBaseTRMtx();

        if (l_HIO.mNo < 0) {
            if (argument == 0) {
                l_HIO.mNo = mDoHIO_createChild("タクト石版", &l_HIO);
            } else {
                l_HIO.mNo = mDoHIO_createChild("メッセージ石碑", &l_HIO);
            }
            l_HIO.mpActor = this;
        }

        if (!init()) {
            phase_state = cPhs_ERROR_e;
        }
    }

    return phase_state;
}

/* 00000C84-00000E60       .text init__11daObj_hsh_cFv */
/* Nonmatching */
BOOL daObj_hsh_c::init() {
    m50C = fopAcM_GetParam(this) & 0xFF;
    m510 = (fopAcM_GetParam(this) >> 8) & 0xFFFF;
    m518 = 0;
    m514 = -1;
    m515 = -1;

    mAcchCir.SetWall(30.0f, 30.0f);

    mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);

    setBaseMtx();

    dComIfG_Bgsp()->Regist(m4D4, this);
    m4D4->Move();

    if (argument == 0) {
        if (dComIfGs_isEventBit(0x2B10)) {
            setAction(&waitAction, NULL);
        } else {
            onOffDraw();
            setAction(&waitAction, NULL);
        }
    } else {
        setAction(&waitAction, NULL);
    }

    static const char* event_name_tbl[2] = { "hsehi1_tact", "hsehi1_talk" };
    for (int i = 0; i < 2; i++) {
        m530[i] = dComIfGp_evmng_getEventIdx(event_name_tbl[i], 0xFF);
    }

    eventInfo.setXyCheckCB(daObj_hsh_XyCheckCB);
    eventInfo.setXyEventCB(daObj_hsh_XyEventCB);

    return 1;
}

/* 00000E60-00000EF4       .text action__11daObj_hsh_cFPv */
/* Nonmatching */
void daObj_hsh_c::action(void* i_param) {
    if (mCurrActionFunc == NULL) {
        speedF = 0.0f;
        setAction(&waitAction, NULL);
    }
    (this->*mCurrActionFunc)(i_param);
}

/* 00000EF4-00000FBC       .text setAction__11daObj_hsh_cFM11daObj_hsh_cFPCvPvPv_iPv */
/* Nonmatching */
BOOL daObj_hsh_c::setAction(ActionFunc i_actionFunc, void* i_param) {
    if (mCurrActionFunc != i_actionFunc) {
        if (mCurrActionFunc != NULL) {
            mActionStatus = -1;
            (this->*mCurrActionFunc)(i_param);
        }
        mCurrActionFunc = i_actionFunc;
        mActionStatus = 0;
        m51C = 0;
        m51E = 0;
        m520 = 0;
        m522 = 0;
        m528 = 0.0f;
        (this->*mCurrActionFunc)(i_param);
    }
    return 1;
}

/* 00000FBC-000010E8       .text waitAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::waitAction(void*) {
    if (mActionStatus == 0) {
        mActionStatus++;
    } else if (mActionStatus != -1) {
        m518 = chkAttention(current.pos, shape_angle.y);

        if (argument == 0) {
            if (m518) {
                cLib_onBit<u32>(attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
                if (m514 == -1) {
                    m514 = 5;
                }
            } else {
                cLib_offBit<u32>(attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
            }
        } else {
            if (m518) {
                cLib_onBit<u32>(attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
                if (m514 == -1) {
                    m514 = 3;
                }
            } else {
                cLib_offBit<u32>(attention_info.flags, fopAc_Attn_TALKFLAG_CHECK_e | fopAc_Attn_ACTION_SPEAK_e);
            }
        }

        setAttention(1);
    }
    return 1;
}

/* 000010E8-00001214       .text talkAction__11daObj_hsh_cFPv */
/* Nonmatching */
BOOL daObj_hsh_c::talkAction(void*) {
    if (mActionStatus == 0) {
        l_msgId = -1;
        m508 = getMsg();
        mActionStatus++;
        if (argument == 0) {
            ((daPy_py_c*)dComIfGp_getLinkPlayer())->onNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
        }
    } else if (mActionStatus != -1) {
        if (mActionStatus == 1) {
            if (talk_init()) {
                mActionStatus++;
            }
        } else {
            if (talk(0)) {
                setAction(&waitAction, NULL);
                g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
                if (argument == 0) {
                    ((daPy_py_c*)dComIfGp_getLinkPlayer())->offNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
                }
            }
        }

        setAttention(1);
    }
    return 1;
}

/* 00001214-00001230       .text offAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::offAction(void*) {
    if (mActionStatus == 0) {
        mActionStatus++;
    }
    return 1;
}

/* 00001230-00001278       .text deleteAction__11daObj_hsh_cFPv */
BOOL daObj_hsh_c::deleteAction(void*) {
    if (mActionStatus == 0) {
        mActionStatus++;
    } else if (mActionStatus != -1) {
        fopAcM_delete(this);
    }
    return 1;
}

/* 00001278-0000135C       .text eventOrder__11daObj_hsh_cFv */
/* Nonmatching */
void daObj_hsh_c::eventOrder() {
    if (!(m504 & 1)) {
        if (m514 == 4 || m514 == 3) {
            eventInfo.onCondition(0x1);
            if (m514 == 4) {
                fopAcM_orderSpeakEvent(this);
            }
        } else if (m514 == 5) {
            eventInfo.onCondition(0x20);
            eventInfo.onCondition(0x1);
            if (argument == 0) {
                eventInfo.setEventName("Hsh");
            }
        } else if (m514 != -1 && m514 < 2) {
            m515 = m514;
            fopAcM_orderOtherEventId(this, m530[m515], 0xFF, 0xFFFF, 0, 1);
        }
    }
}

/* 0000135C-0000140C       .text checkOrder__11daObj_hsh_cFv */
/* Nonmatching */
void daObj_hsh_c::checkOrder() {
    if (eventInfo.checkCommandTalk()) {
        if (m514 == 4 || m514 == 3 || m514 == 5) {
            m514 = -1;
            u8 present = (dComIfGp_event_getTalkXYBtn() == dTalkBtn_X_e ||
                          dComIfGp_event_getTalkXYBtn() == dTalkBtn_Y_e ||
                          dComIfGp_event_getTalkXYBtn() == dTalkBtn_Z_e);
            if (present) {
            } else {
                setAction(&talkAction, NULL);
            }
        }
    }
}

/* 0000140C-00001478       .text checkCommandTalk__11daObj_hsh_cFv */
/* Nonmatching */
BOOL daObj_hsh_c::checkCommandTalk() {
    if (eventInfo.checkCommandTalk()) {
        u8 present = (dComIfGp_event_getTalkXYBtn() == dTalkBtn_X_e ||
                      dComIfGp_event_getTalkXYBtn() == dTalkBtn_Y_e ||
                      dComIfGp_event_getTalkXYBtn() == dTalkBtn_Z_e);
        if (present) {
            if (m514 == 5) {
                m514 = -1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

/* 00001478-000015E0       .text chkAttention__11daObj_hsh_cF4cXyzs */
/* Nonmatching */
BOOL daObj_hsh_c::chkAttention(cXyz i_pos, short i_angle) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 hio_range = l_HIO.m08;
    s32 hio_angle = l_HIO.m14;

    cXyz diff;
    diff.x = player->current.pos.x - i_pos.x;
    diff.z = player->current.pos.z - i_pos.z;
    f32 dist = std::sqrtf(diff.x * diff.x + diff.z * diff.z);

    s16 angle = cM_atan2s(diff.x, diff.z);

    diff.y = player->current.pos.y - i_pos.y;
    if (m518) {
        hio_range += 40.0f;
        hio_angle += 0x71C;
    }

    s16 angleDiff = angle - i_angle;
    BOOL ret = 0;
    if (hio_angle > abs(angleDiff) && hio_range > dist) {
        ret = 1;
    }
    return ret;
}

/* 000015E0-00001784       .text eventProc__11daObj_hsh_cFv */
/* Nonmatching */
BOOL daObj_hsh_c::eventProc() {
    if (eventInfo.getCommand() == dEvtCmd_INDEMO_e) {
        if (m514 != -1) {
            m504 |= 1;
            m514 = -1;
        }
    }

    dEvent_manager_c* evmgr = dComIfGp_getPEvtManager();
    int staffId = evmgr->getMyStaffId("Hsh", NULL, 0);

    static const char* cut_name_tbl[8] = { "WAIT", "Disp", "MsgSet", "Talk", "Tact", "Judge", "Appear", "Delete" };

    if (g_dComIfG_gameInfo.play.getEvent()->runCheck() && !checkCommandTalk() && staffId != -1) {
        int actIdx = evmgr->getMyActIdx(staffId, cut_name_tbl, 8, 1, 0);
        if (actIdx == -1) {
            evmgr->cutEnd(staffId);
        } else {
            if (evmgr->getIsAddvance(staffId)) {
                (this->*event_init_tbl[actIdx])(staffId);
            }
            if ((this->*event_action_tbl[actIdx])(staffId)) {
                evmgr->cutEnd(staffId);
            }
        }
    }

    if (m504 & 1) {
        if (evmgr->endCheck(m530[m515])) {
            eventEnd();
        }
        return 1;
    }

    if (staffId != -1) {
        return 1;
    }
    return 0;
}

/* 00001784-000017B0       .text eventEnd__11daObj_hsh_cFv */
void daObj_hsh_c::eventEnd() {
    g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
    m504 &= ~1;
    m515 = -1;
}

/* 000017B0-000017B4       .text initialDefault__11daObj_hsh_cFi */
void daObj_hsh_c::initialDefault(int) {
}

/* 000017B4-000017BC       .text actionDefault__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionDefault(int) {
    return 1;
}

/* 000017BC-00001938       .text initialLinkDispEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialLinkDispEvent(int i_staffId) {
    dEvent_manager_c* evmgr = dComIfGp_getPEvtManager();
    char buf[0x10];
    char* substance = (char*)evmgr->getMySubstanceP(i_staffId, "target", 4);

    BOOL isLink = 0;
    if (substance != NULL) {
        strcpy(buf, substance);
        if (strcmp(buf, "@PLAYER") == 0) {
            isLink = 1;
        }
    }

    substance = (char*)evmgr->getMySubstanceP(i_staffId, "disp", 4);
    if (isLink == 1) {
        if (substance != NULL) {
            strcpy(buf, substance);
            daPy_py_c* link = (daPy_py_c*)dComIfGp_getLinkPlayer();
            if (strcmp(buf, "on") == 0) {
                link->offNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
            }
            if (strcmp(buf, "off") == 0) {
                link->onNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
            }
        }
    } else {
        if (substance != NULL) {
            strcpy(buf, substance);
            if (strcmp(buf, "on") == 0) {
                drawStart();
            }
            if (strcmp(buf, "off") == 0) {
                drawStop();
            }
        }
    }
}

/* 00001938-000019C0       .text initialMsgSetEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialMsgSetEvent(int i_staffId) {
    l_msgId = -1;
    m508 = 0;

    dEvent_manager_c* evmgr = dComIfGp_getPEvtManager();
    int* substance = (int*)evmgr->getMySubstanceP(i_staffId, "MsgNo", 3);
    if (substance != NULL) {
        m508 = *substance;
        if (m508 == 0x5B3) {
            dComIfGp_setMelodyNum(2);
        }
    }
}

/* 000019C0-000019E0       .text actionMsgSetEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionMsgSetEvent(int i_staffId) {
    return talk_init();
}

/* 000019E0-00001A40       .text actionMessageEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionMessageEvent(int i_staffId) {
    dEvent_manager_c* evmgr = dComIfGp_getPEvtManager();
    int* substance = (int*)evmgr->getMySubstanceP(i_staffId, "prm0", 3);

    int prm0 = 0;
    if (substance != NULL) {
        prm0 = *substance;
    }
    talk(prm0);
}

/* 00001A40-00001ADC       .text actionTactEvent__11daObj_hsh_cFi */
/* Nonmatching */
BOOL daObj_hsh_c::actionTactEvent(int i_staffId) {
    dEvent_manager_c* evmgr = dComIfGp_getPEvtManager();
    int* substance = (int*)evmgr->getMySubstanceP(i_staffId, "prm0", 3);

    int prm0 = 0;
    if (substance != NULL) {
        prm0 = *substance;
    }

    if (daPy_getPlayerActorClass()->getTactMusic() == prm0) {
        m504 |= 4;
    }
    talk(1);
}

/* 00001ADC-00001B3C       .text initialJudgeEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialJudgeEvent(int) {
    if (m504 & 4) {
        m504 &= ~4;
    } else if (m504 & 2) {
        drawStart();
        m504 &= ~2;
        eventEnd();
    }
}

/* 00001B3C-00001C1C       .text initialAppearEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialAppearEvent(int i_staffId) {
    dComIfGs_onEventBit(0x2B10);
    particle_set(0x8270);
    particle_set(&m4A0, 0x8271);

    mDoAud_seStart(JA_SE_OBJ_ST_TAKT_GR_ON, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
    m519 = 30;
    setAction(&waitAction, NULL);
}

/* 00001C1C-00001C74       .text actionAppearEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionAppearEvent(int) {
    if (cLib_calcTimer<u8>(&m519) == 0) {
        offOffDraw();
        emitterDelete(&m4A0);
        return 1;
    }
    return 0;
}

/* 00001C74-00001D3C       .text initialDeleteEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialDeleteEvent(int i_staffId) {
    particle_set(0x8270);
    particle_set(&m4A0, 0x8271);

    mDoAud_seStart(JA_SE_OBJ_ST_TAKT_GR_ON, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
    m519 = 60;
    setAction(&deleteAction, NULL);
}

/* 00001D3C-00001D88       .text actionDeleteEvent__11daObj_hsh_cFi */
BOOL daObj_hsh_c::actionDeleteEvent(int) {
    if (cLib_calcTimer<u8>(&m519) == 0) {
        drawStop();
        return 1;
    }
    return 0;
}

/* 00001D88-00001DF4       .text talk_init__11daObj_hsh_cFv */
BOOL daObj_hsh_c::talk_init() {
    if (l_msgId == 0xFFFFFFFF) {
        l_msgId = fopMsgM_messageSet(m508, this);
    } else {
        l_msg = fopMsgM_SearchByID(l_msgId);
        if (l_msg != NULL) {
            return 1;
        }
    }
    return 0;
}

/* 00001DF4-00001F1C       .text talk__11daObj_hsh_cFi */
/* Nonmatching */
BOOL daObj_hsh_c::talk(int i_param) {
    if (l_msg->mStatus == 0xE) {
        if (i_param == 1) {
            if (dComIfGp_checkMesgCancelButton()) {
                l_msg->mStatus = 0x10;
                fopMsgM_messageSendOn();
                m504 |= 2;
            } else if (m504 & 4) {
                l_msg->mStatus = 0x10;
                fopMsgM_messageSendOn();
                if (m508 == 0x5B3) {
                    dComIfGs_onSwitch(m50C, current.roomNo);
                }
            }
        } else {
            l_msg->mStatus = next_msgStatus(&m508);
            if (l_msg->mStatus == 0xF) {
                fopMsgM_messageSet(m508);
            }
        }
    } else if (l_msg->mStatus == 0x15) {
        if (i_param == 2) {
            return 1;
        }
    } else if (l_msg->mStatus == 0x6) {
    } else if (l_msg->mStatus == 0x12) {
        l_msg->mStatus = 0x13;
        return 1;
    }
    return 0;
}

/* 00001F1C-00001F38       .text getMsg__11daObj_hsh_cFv */
u32 daObj_hsh_c::getMsg() {
    if (argument == 0) {
        return 0x1901;
    }
    return m510;
}

/* 00001F38-00001F78       .text next_msgStatus__11daObj_hsh_cFPUl */
u32 daObj_hsh_c::next_msgStatus(u32* pMsg) {
    u32 status = 0xF;
    if (*pMsg == 0 || *pMsg == 0xEF3 || *pMsg == m510) {
        status = 0x10;
    } else if (*pMsg == 0x1901) {
        status = 0x10;
    }
    return status;
}

/* 00001F78-00002098       .text execute__11daObj_hsh_cFv */
BOOL daObj_hsh_c::execute() {
    if (argument == 0) {
        if (dComIfGs_isEventBit(0x2B10)) {
            actor_status = (actor_status & ~0x3F) | 0x24;
        } else {
            actor_status &= ~0x20;
        }
    }

    mAcch.CrrPos(*dComIfG_Bgsp());

    if (mAcch.GetGroundH() != -1000000000.0f) {
        u8 roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
        current.roomNo = roomNo;
        tevStr.mRoomNo = roomNo;
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
        mPolyInfo = mAcch.m_gnd;
    }

    if (!eventProc()) {
        checkOrder();
        action(NULL);
    }

    eventOrder();
    setBaseMtx();
    return 1;
}

/* 00002098-00002158       .text draw__11daObj_hsh_cFv */
BOOL daObj_hsh_c::draw() {
    if (m504 & 8) {
        return 1;
    }

    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdate(mpModel);

    cXyz pos(current.pos.x, current.pos.y, current.pos.z);
    m500 = dComIfGd_setRealShadow2(m500, 1, mpModel, &pos, 800.0f, mAcch.GetGroundH(), &tevStr);
    return 1;
}

/* 00002158-00002178       .text daObj_hsh_Draw__FP11daObj_hsh_c */
static BOOL daObj_hsh_Draw(daObj_hsh_c* i_this) {
    return ((daObj_hsh_c*)i_this)->draw();
}

/* 00002178-00002198       .text daObj_hsh_Execute__FP11daObj_hsh_c */
static BOOL daObj_hsh_Execute(daObj_hsh_c* i_this) {
    return ((daObj_hsh_c*)i_this)->execute();
}

/* 00002198-000021A0       .text daObj_hsh_IsDelete__FP11daObj_hsh_c */
static BOOL daObj_hsh_IsDelete(daObj_hsh_c*) {
    return TRUE;
}

/* 000021A0-000021C8       .text daObj_hsh_Delete__FP11daObj_hsh_c */
static BOOL daObj_hsh_Delete(daObj_hsh_c* i_this) {
    ((daObj_hsh_c*)i_this)->~daObj_hsh_c();
    return TRUE;
}

/* 000021C8-000021E8       .text daObj_hsh_Create__FP10fopAc_ac_c */
static cPhs_State daObj_hsh_Create(fopAc_ac_c* i_this) {
    return ((daObj_hsh_c*)i_this)->create();
}

static actor_method_class l_daObj_hsh_Method = {
    (process_method_func)daObj_hsh_Create,
    (process_method_func)daObj_hsh_Delete,
    (process_method_func)daObj_hsh_Execute,
    (process_method_func)daObj_hsh_IsDelete,
    (process_method_func)daObj_hsh_Draw,
};

actor_process_profile_definition g_profile_Obj_HSH = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_HSH_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_hsh_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_HSH_e,
    /* Actor SubMtd */ &l_daObj_hsh_Method,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
