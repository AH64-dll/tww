/**
 * d_a_obj_tntrap.cpp
 * Object - TnT Trap
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_tntrap.h"
#include "d/actor/d_a_ship.h"
#include "d/d_event_manager.h"
#include "d/d_particle.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"
#include "SSystem/SComponent/c_math.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_mtx.h"

static const char l_arcname[] = "TnTrap";

static const dCcD_SrcTri l_tri_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0x800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ 5,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0xB,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGTriS
    {{
        /* a */ {0.0f, 0.0f, 0.0f},
        /* b */ {0.0f, 0.0f, 0.0f},
        /* c */ {0.0f, 0.0f, 0.0f},
    }},
};

static const Vec l_tri_vtx[6] = {
    {300.0f, -70.0f, 0.0f},
    {-300.0f, -70.0f, 0.0f},
    {-300.0f, 55.0f, 0.0f},
    {300.0f, 55.0f, 0.0f},
    {300.0f, 180.0f, 0.0f},
    {-300.0f, 180.0f, 0.0f},
};

static const Vec l_offset_ball[2] = {
    {-300.0f, 90.0f, 0.0f},
    {300.0f, 90.0f, 0.0f},
};

static const Vec l_offset_thunder[3] = {
    {0.0f, 25.0f, 0.0f},
    {0.0f, 85.0f, 0.0f},
    {0.0f, 145.0f, 0.0f},
};

static s32 table_idx[12] = {0, 1, 2, 0, 2, 3, 3, 2, 5, 3, 5, 4};

/* 00000078-000002AC       .text chk_appear__13daObjTnTrap_cFv */
    /* Nonmatching */
BOOL daObjTnTrap_c::chk_appear() {
    mSwSave = param_get_swSave();
    mSwSave2 = param_get_swSave2();
    mArg0 = param_get_arg0();
    mMapType = param_get_mapType();

    BOOL ret = FALSE;
    switch (mMapType) {
        case 0:
            if (dComIfGs_isEventBit(0x3A04)) {
                if (mSwSave != 0xFF) {
                    if (dComIfGs_isSwitch(mSwSave, current.roomNo)) {
                        if (dComIfGs_getTriforceNum() == 8) {
                            if (mArg0 == 0) {
                                if (dComIfGs_isEventBit(0x2C01)) {
                                    if (mSwSave2 != 0xFF) {
                                        if (!dComIfGs_isSwitch(mSwSave2, current.roomNo)) {
                                            mAppear = 2;
                                            ret = TRUE;
                                        }
                                    }
                                } else {
                                    mAppear = 1;
                                    ret = TRUE;
                                }
                            }
                        }
                    } else {
                        mAppear = 0;
                        ret = TRUE;
                    }
                } else {
                    mAppear = 0;
                    ret = TRUE;
                }
            }
            break;
        case 1:
            if (mSwSave != 0xFF && !dComIfGs_isSwitch(mSwSave, current.roomNo)) {
                mAppear = 3;
                ret = TRUE;
            }
            break;
        case 2:
            if (mSwSave != 0xFF) {
                if (!dComIfGs_isSwitch(mSwSave, current.roomNo)) {
                    mAppear = 5;
                    ret = TRUE;
                }
            } else {
                mAppear = 5;
                ret = TRUE;
            }
            break;
        default:
            JUT_ASSERT(0x17C, 0);
            break;
    }
    return ret;
}

/* 000002AC-00000344       .text set_mtx__13daObjTnTrap_cFv */
void daObjTnTrap_c::set_mtx() {
    mDoMtx_stack_c::transS(home.pos.x, home.pos.y, home.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mDoMtx_stack_c::transM(0.0f, -9000.0f, -94.0f);
    mDoMtx_stack_c::scaleM(scale.x, 100.0f, scale.z);
    PSMTXCopy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000344-00000368       .text solidHeapCB__13daObjTnTrap_cFP10fopAc_ac_c */
BOOL daObjTnTrap_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->create_heap();
}

/* 00000368-000003E4       .text create_heap__13daObjTnTrap_cFv */
bool daObjTnTrap_c::create_heap() {
    bool ret = true;
    cBgD_t* bgd = (cBgD_t*)dComIfG_getObjectRes(l_arcname, 3);
    mpBgW = dBgW_NewSet(bgd, 1, &mMtx);
    if (mpBgW == NULL) {
        ret = false;
    }
    return ret;
}

/* 000003E4-000005F8       .text particle_set__13daObjTnTrap_cFif */
    /* Nonmatching */
void daObjTnTrap_c::particle_set(int i_idx, f32 i_offsetY) {
    if (mPrtSetFlg[i_idx] == 1) {
        if (mOffsetY[i_idx] != i_offsetY) {
            particle_delete(i_idx);
        } else {
            return;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (mBallPrt[i_idx][i] == NULL) {
            cXyz pos;
            pos.x = l_offset_ball[i].x;
            pos.y = i_offsetY + l_offset_ball[i].y;
            pos.z = l_offset_ball[i].z;
            mBallPrt[i_idx][i] = dComIfGp_particle_set(dPa_name::ID_AK_SN_TNTRAPBALL00, &home.pos,
                                                       &shape_angle, NULL, 0xFF, NULL, -1, NULL,
                                                       NULL, NULL);
            mBallPrt[i_idx][i]->setEmitterTranslation(pos);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (mThunderPrt[i_idx][i] == NULL) {
            cXyz pos;
            pos.x = l_offset_thunder[i].x;
            pos.y = i_offsetY + l_offset_thunder[i].y;
            pos.z = l_offset_thunder[i].z;
            mThunderPrt[i_idx][i] = dComIfGp_particle_set(dPa_name::ID_AK_SN_TNTRAPTHUNDER00,
                                                          &home.pos, &shape_angle, NULL, 0xFF,
                                                          NULL, -1, NULL, NULL, NULL);
            mThunderPrt[i_idx][i]->setEmitterTranslation(pos);
        }
    }

    mOffsetY[i_idx] = i_offsetY;
    mPrtSetFlg[i_idx] = 1;
}

/* 000005F8-000006A4       .text particle_delete__13daObjTnTrap_cFi */
    /* Nonmatching */
void daObjTnTrap_c::particle_delete(int i_idx) {
    if (mPrtSetFlg[i_idx] == 1) {
        for (int i = 0; i < 2; i++) {
            if (mBallPrt[i_idx][i] != NULL) {
                mBallPrt[i_idx][i]->becomeInvalidEmitter();
                mBallPrt[i_idx][i] = NULL;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (mThunderPrt[i_idx][i] != NULL) {
                mThunderPrt[i_idx][i]->becomeInvalidEmitter();
                mThunderPrt[i_idx][i] = NULL;
            }
        }
    }
    mPrtSetFlg[i_idx] = 0;
}

/* 000006A4-0000072C       .text set_se__13daObjTnTrap_cFv */
    /* Nonmatching */
void daObjTnTrap_c::set_se() {
    if (mAction >= 1 && mAction < 5) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_TN_TRAP, 0);
    }
}

/* 0000072C-000008A0       .text set_tri__13daObjTnTrap_cFi */
    /* Nonmatching */
void daObjTnTrap_c::set_tri(int i_idx) {
    mDoMtx_stack_c::transS(home.pos.x, home.pos.y + mOffsetY[i_idx], home.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, shape_angle.y, shape_angle.z);

    dCcD_Tri* tri = &mTri[i_idx * 4];
    for (int i = 0; i < 4; i++) {
        Vec vtx[3];
        const s32* tbl = &table_idx[i * 3];
        for (int j = 0; j < 3; j++) {
            vtx[j] = l_tri_vtx[tbl[j]];
            mDoMtx_stack_c::multVec(&vtx[j], &vtx[j]);
        }
        tri[i].setPos(&vtx[0], &vtx[1], &vtx[2]);
    }
}

/* 000008A0-00000A10       .text chk_event_flg__13daObjTnTrap_cFv */
    /* Nonmatching */
BOOL daObjTnTrap_c::chk_event_flg() {
    BOOL ret = TRUE;
    switch (mAppear) {
        case 0:
            if (mSwSave != 0xFF && dComIfGs_isSwitch(mSwSave, current.roomNo)) {
                s32 act = 4;
                if (mArg0 == 0) {
                    act = 2;
                    dComIfGs_onEventBit(0x3B40);
                }
                setup_action(act);
            }
            break;
        case 1:
            if (mAction == 1) {
                setup_action(2);
            }
            break;
        case 3:
            if (mSwSave != 0xFF && dComIfGs_isSwitch(mSwSave, current.roomNo)) {
                daShip_c* ship = dComIfGp_getShipActor();
                if (ship != NULL) {
                    ship->offFantomGanonBattle();
                    fopAcM_delete(this);
                    ret = FALSE;
                }
            }
            break;
        case 5:
            if (mSwSave != 0xFF && dComIfGs_isSwitch(mSwSave, current.roomNo)) {
                fopAcM_delete(this);
                ret = FALSE;
            }
            break;
    }
    return ret;
}

/* 00000A10-00000A98       .text set_em_set_offsetY__13daObjTnTrap_cFv */
    /* Nonmatching */
void daObjTnTrap_c::set_em_set_offsetY() {
    if (mAppear == 5) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        if (player != NULL) {
            mOffsetY[0] = 180.0f * (s32)((player->current.pos.y - home.pos.y) / 180.0f);
        }
    } else {
        mOffsetY[0] = 0.0f;
    }
}

/* 00000A98-00000C78       .text _create__13daObjTnTrap_cFv */
    /* Nonmatching */
cPhs_State daObjTnTrap_c::_create() {
    cPhs_State phase = cPhs_ERROR_e;
    fopAcM_ct(this, daObjTnTrap_c);

    if (fopAcM_IsFirstCreating(this)) {
        mAppearFlg = chk_appear();
    }
    if (mAppearFlg == 1) {
        phase = dComIfG_resLoad(&mPhs, l_arcname);
    }
    if (phase == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x2E0)) {
            if (mAppear != 3) {
                if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
                    phase = cPhs_ERROR_e;
                    return phase;
                }
            }
            set_em_set_offsetY();
            set_mtx();
            mStts.Init(0xFF, 0xFF, this);
            for (int g = 0; g < 2; g++) {
                for (int i = 0; i < 4; i++) {
                    mTri[g * 4 + i].Set(l_tri_src);
                    mTri[g * 4 + i].SetStts(&mStts);
                }
                set_tri(g);
            }
            setup_action(mAppear == 3 ? 6 : 0);
        } else {
            phase = cPhs_ERROR_e;
        }
    }
    return phase;
}

/* 00000F8C-00001050       .text _delete__13daObjTnTrap_cFv */
bool daObjTnTrap_c::_delete() {
    if (mAppearFlg == 1) {
        dComIfG_resDelete(&mPhs, l_arcname);
        if (heap != NULL && mpBgW != NULL) {
            if (mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
            mpBgW = NULL;
        }
        for (int i = 0; i < 2; i++) {
            particle_delete(i);
        }
    }
    return true;
}

/* 00001050-00001150       .text trap_off_wait_act_proc__13daObjTnTrap_cFv */
    /* Nonmatching */
BOOL daObjTnTrap_c::trap_off_wait_act_proc() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    if (player != NULL) {
        cXyz diff = player->current.pos - home.pos;
        f32 dist = diff.absXZ();
        if (dist < 500.0f) {
            setup_action(1);
        }
    }
    return chk_event_flg();
}

/* 00001150-00001384       .text trap_on_wait_act_proc__13daObjTnTrap_cFv */
    /* Nonmatching */
BOOL daObjTnTrap_c::trap_on_wait_act_proc() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    if (player != NULL) {
        cXyz diff = player->current.pos - home.pos;
        f32 dist = diff.absXZ();
        if (dist > 500.0f) {
            setup_action(0);
        } else if (mAppear == 5) {
            f32 offset[2];
            for (int i = 0; i < 2; i++) {
                offset[i] = player->current.pos.y - (home.pos.y + mOffsetY[i] + 90.0f);
                if (std::fabsf(offset[i]) > 150.0f) {
                    particle_delete(i);
                }
            }
            for (int i = 0; i < 2; i++) {
                if (std::fabsf(offset[i]) > 80.0f) {
                    f32 target;
                    if (offset[i] > 0.0f) {
                        target = 180.0f + mOffsetY[i];
                    } else {
                        target = mOffsetY[i] - 180.0f;
                    }
                    if (std::fabsf(player->current.pos.y - (home.pos.y + target + 90.0f)) <= 150.0f) {
                        particle_set(i ^ 1, target);
                    }
                }
            }
        }
    }
    return chk_event_flg();
}

/* 00001384-00001448       .text demo_regist_wait_act_proc__13daObjTnTrap_cFv */
BOOL daObjTnTrap_c::demo_regist_wait_act_proc() {
    if (mEvtIdx != -1) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            setup_action(3);
        } else {
            fopAcM_orderOtherEventId(this, mEvtIdx, 0xFF, 0xFFFF, 0, 1);
        }
    } else {
        if (mAppear == 2) {
            mEvtIdx = dComIfGp_evmng_getEventIdx("break_tntrap2");
        } else {
            mEvtIdx = dComIfGp_evmng_getEventIdx("break_tntrap");
        }
    }
    return TRUE;
}

/* 00001448-000014F0       .text demo_wait_act_proc__13daObjTnTrap_cFv */
BOOL daObjTnTrap_c::demo_wait_act_proc() {
    if (dComIfGp_evmng_existence(mEvtIdx)) {
        int staffId = dComIfGp_evmng_getMyStaffId("TnTrap");
        if (staffId != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffId), "Delete") == 0) {
                setup_action(5);
            }
        }
    }
    return TRUE;
}

/* 000014F0-000015B4       .text demo_wait2_act_proc__13daObjTnTrap_cFv */
BOOL daObjTnTrap_c::demo_wait2_act_proc() {
    BOOL ret = TRUE;
    s16 evtIdx = dComIfGp_evmng_getEventIdx("break_tntrap");
    if (dComIfGp_evmng_existence(evtIdx)) {
        int staffId = dComIfGp_evmng_getMyStaffId("TnTrap");
        if (staffId != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffId), "Delete2") == 0) {
                fopAcM_delete(this);
                ret = FALSE;
            }
        }
    }
    return ret;
}

/* 000015B4-000016A8       .text demo_end_wait_act_proc__13daObjTnTrap_cFv */
    /* Nonmatching */
BOOL daObjTnTrap_c::demo_end_wait_act_proc() {
    BOOL ret = TRUE;
    if (dComIfGp_evmng_endCheck(mEvtIdx)) {
        g_dComIfG_gameInfo.play.getEvent()->mEventFlag |= 0x8;
        switch (mAppear) {
            case 0:
                mDoAud_seStart(JA_SE_READ_RIDDLE_1);
                break;
            case 2:
                if (mSwSave2 != 0xFF) {
                    dComIfGs_onSwitch(mSwSave2, home.roomNo);
                }
                break;
        }
        fopAcM_delete(this);
        ret = FALSE;
    }
    return ret;
}

/* 000016A8-00001740       .text hide_wait_act_proc__13daObjTnTrap_cFv */
    /* Nonmatching */
BOOL daObjTnTrap_c::hide_wait_act_proc() {
    if (mSwSave2 != 0xFF && dComIfGs_isSwitch(mSwSave2, current.roomNo)) {
        daShip_c* ship = dComIfGp_getShipActor();
        if (ship != NULL) {
            ship->onFantomGanonBattle();
            if (!dComIfG_Bgsp()->Regist(mpBgW, this)) {
                setup_action(0);
            }
        }
    }
    return FALSE;
}

/* 00001740-00001744       .text dummy_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::dummy_proc() {}

/* 00001744-00001790       .text trap_off_wait_act_init_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::trap_off_wait_act_init_proc() {
    for (int i = 0; i < 2; i++) {
        particle_delete(i);
    }
}

/* 00001790-000017CC       .text trap_on_wait_act_init_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::trap_on_wait_act_init_proc() {
    set_em_set_offsetY();
    particle_set(0, mOffsetY[0]);
}

/* 000017CC-00001860       .text demo_regist_wait_act_init_proc__13daObjTnTrap_cFv */
    /* Nonmatching */
void daObjTnTrap_c::demo_regist_wait_act_init_proc() {
    mOffsetY[0] = 0.0f;
    particle_set(0, mOffsetY[0]);
    if (mAppear == 2) {
        mEvtIdx = dComIfGp_evmng_getEventIdx("break_tntrap2");
    } else {
        mEvtIdx = dComIfGp_evmng_getEventIdx("break_tntrap");
    }
}

/* 00001860-00001890       .text demo_wait2_act_init_proc__13daObjTnTrap_cFv */
    /* Nonmatching */
void daObjTnTrap_c::demo_wait2_act_init_proc() {
    mOffsetY[0] = 0.0f;
    particle_set(0, mOffsetY[0]);
}

/* 00001890-000018DC       .text demo_end_wait_act_init_proc__13daObjTnTrap_cFv */
void daObjTnTrap_c::demo_end_wait_act_init_proc() {
    for (int i = 0; i < 2; i++) {
        particle_delete(i);
    }
}

/* 000018DC-00001AE4       .text setup_action__13daObjTnTrap_cFi */
    /* Nonmatching */
void daObjTnTrap_c::setup_action(int i_action) {
    static BOOL (daObjTnTrap_c::*act_proc[7])() = {
        &daObjTnTrap_c::trap_off_wait_act_proc,
        &daObjTnTrap_c::trap_on_wait_act_proc,
        &daObjTnTrap_c::demo_regist_wait_act_proc,
        &daObjTnTrap_c::demo_wait_act_proc,
        &daObjTnTrap_c::demo_wait2_act_proc,
        &daObjTnTrap_c::demo_end_wait_act_proc,
        &daObjTnTrap_c::hide_wait_act_proc,
    };
    static void (daObjTnTrap_c::*act_init_proc[7])() = {
        &daObjTnTrap_c::trap_off_wait_act_init_proc,
        &daObjTnTrap_c::trap_on_wait_act_init_proc,
        &daObjTnTrap_c::demo_regist_wait_act_init_proc,
        &daObjTnTrap_c::dummy_proc,
        &daObjTnTrap_c::demo_wait2_act_init_proc,
        &daObjTnTrap_c::demo_end_wait_act_init_proc,
        &daObjTnTrap_c::dummy_proc,
    };
    (this->*act_init_proc[i_action])();
    mProcFunc = act_proc[i_action];
    mAction = i_action;
}

/* 00001AE4-00001BE8       .text _execute__13daObjTnTrap_cFv */
    /* Nonmatching */
bool daObjTnTrap_c::_execute() {
    if (mpBgW != NULL && mpBgW->ChkUsed()) {
        mpBgW->Move();
    }
    for (int i = 0; i < 2; i++) {
        set_tri(i);
    }
    mStts.Move();
    u8 procResult = (this->*mProcFunc)();
    if (procResult == 1) {
        for (int g = 0; g < 2; g++) {
            for (int i = 0; i < 4; i++) {
                dComIfG_Ccsp()->Set(&mTri[g * 4 + i]);
            }
        }
        set_se();
    }
    return true;
}

/* 00001BE8-00001BF0       .text _draw__13daObjTnTrap_cFv */
bool daObjTnTrap_c::_draw() {
    return true;
}

/* 00001BF0-00001C10       .text daObjTnTrap_Create__FP10fopAc_ac_c */
static cPhs_State daObjTnTrap_Create(fopAc_ac_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->_create();
}

/* 00001C10-00001C34       .text daObjTnTrap_Delete__FP13daObjTnTrap_c */
static BOOL daObjTnTrap_Delete(daObjTnTrap_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->_delete();
}

/* 00001C34-00001C58       .text daObjTnTrap_Execute__FP13daObjTnTrap_c */
static BOOL daObjTnTrap_Execute(daObjTnTrap_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->_execute();
}

/* 00001C58-00001C7C       .text daObjTnTrap_Draw__FP13daObjTnTrap_c */
static BOOL daObjTnTrap_Draw(daObjTnTrap_c* i_this) {
    return ((daObjTnTrap_c*)i_this)->_draw();
}

/* 00001C7C-00001C84       .text daObjTnTrap_IsDelete__FP13daObjTnTrap_c */
static BOOL daObjTnTrap_IsDelete(daObjTnTrap_c*) {
    return TRUE;
}

static actor_method_class l_daObjTnTrap_Method = {
    (process_method_func)daObjTnTrap_Create,
    (process_method_func)daObjTnTrap_Delete,
    (process_method_func)daObjTnTrap_Execute,
    (process_method_func)daObjTnTrap_IsDelete,
    (process_method_func)daObjTnTrap_Draw,
};

actor_process_profile_definition g_profile_Obj_TnTrap = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_TnTrap_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTnTrap_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_TnTrap_e,
    /* Actor SubMtd */ &l_daObjTnTrap_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
