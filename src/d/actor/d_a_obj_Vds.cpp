/**
 * d_a_obj_Vds.cpp
 * Object - Earth Temple - Face statue (lights up when eyes are hit with Mirror Shield)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Vds.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/actor/d_a_obj_swlight.h"

namespace daObjVds {
namespace {
/* 00000000-00000028       .rodata L_attr__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@ */
struct Attr_c {
    /* 0x00 */ Vec mPos;
    /* 0x0C */ GXColorS10 mColor;
    /* 0x14 */ f32 mPower;
    /* 0x18 */ f32 mFluctuation;
    /* 0x1C */ s32 mIdx;
    /* 0x20 */ s32 mUnk20;
    /* 0x24 */ s32 mUnk24;
};  // Size: 0x28

static const Attr_c L_attr = {
    {222.5f, 598.73f, 178.9f},
    {0x400, 0x400, 0x400, 0},
    2200.0f,
    0.0f,
    0,
    0,
    0,
};
} // namespace
} // namespace daObjVds

/* 00000078-00000134       .text SetLoopJointAnimation__Q28daObjVds5Act_cFP18J3DAnmTransformKeyP18J3DAnmTransformKeyff */
s32 daObjVds::Act_c::SetLoopJointAnimation(J3DAnmTransformKey* i_anm0, J3DAnmTransformKey* i_anm1, f32 i_f1, f32 i_f2) {
    M_anm0->setAnm(i_anm0, 2, i_f2, i_f1, 0.0f, -1.0f, NULL);
    M_anm1->setAnm(i_anm1, 2, i_f2, i_f1, 0.0f, -1.0f, NULL);
    m318 = 1;
    return 1;
}

/* 00000134-00000188       .text PlayLoopJointAnimation__Q28daObjVds5Act_cFv */
s32 daObjVds::Act_c::PlayLoopJointAnimation() {
    M_anm0->play(NULL, 0, 0);
    M_anm1->play(NULL, 0, 0);
    return 1;
}

/* 00000188-000001E8       .text set_first_process__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_first_process() {
    static s32 angle_data[1] = {0};
    int swBit = daObj::PrmAbstract(this, 8, 0);
    process_init(dComIfGs_isSwitch(swBit, home.roomNo) ? 1 : 0);
}

/* 000001E8-00000214       .text ds_search_switchCB__8daObjVdsFPvPv */
void* daObjVds::ds_search_switchCB(void* i_actor, void* i_this) {
    return static_cast<Act_c*>(i_this)->search_switchCB(static_cast<fopAc_ac_c*>(i_actor));
}

/* 00000214-000002B0       .text search_switchCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
void* daObjVds::Act_c::search_switchCB(fopAc_ac_c* i_actor) {
    if (fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == 0x20) {
        for (int i = 0; i < 2; i++) {
            if (mTargetIds[i] == -1) {
                mTargetIds[i] = fopAcM_GetID(i_actor);
                break;
            }
        }
    }
    return NULL;
}

static const f32 l_eyeData[4] = {-222.5f, 598.73f, 178.9f, 222.5f};

/* 000002EC-000003C8       .text process_off_init__Q28daObjVds5Act_cFv */
s32 daObjVds::Act_c::process_off_init() {
    J3DModelData* modelData0 = M_anm0->getModel()->getModelData();
    if (mBrk0.init(modelData0, M_brk_data0, 1, 0, 1.0f, 0, -1, 1, 0) != 0) {
        mBrk0.setPlaySpeed(0.0f);
        J3DModelData* modelData1 = M_anm1->getModel()->getModelData();
        if (mBrk1.init(modelData1, M_brk_data1, 1, 0, 1.0f, 0, -1, 1, 0) != 0) {
            mBrk1.setPlaySpeed(0.0f);
            return 1;
        }
    }
    return 0;
}

/* 000003C8-00000474       .text process_off_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_off_main() {
    for (int i = 0; i < 2; i++) {
        fopAc_ac_c* actor = fopAcM_SearchByID(mTargetIds[i]);
        mPowers[i] = static_cast<daObjSwlight::Act_c*>(actor)->mF30;
    }
    if (fopAcM_isSwitch(this, daObj::PrmAbstract(this, 8, 0))) {
        process_init(1);
    }
}

/* 00000474-000004F0       .text process_on_init__Q28daObjVds5Act_cFv */
s32 daObjVds::Act_c::process_on_init() {
    if (SetLoopJointAnimation(M_bck_data0, M_bck_data1, 1.0f, 0.0f) != 0) {
        for (int i = 0; i < 2; i++) {
            mPowers[i] = 1.0f;
        }
        return 1;
    }
    return 0;
}

/* 000004F0-000004F4       .text process_on_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_on_main() {}

/* 000004F4-000005C0       .text process_init__Q28daObjVds5Act_cFi */
s32 daObjVds::Act_c::process_init(int i_proc) {
    /* Nonmatching */
    static s32 (Act_c::*init_table[])() = {
        &Act_c::process_off_init,
        &Act_c::process_on_init,
    };
    if (i_proc >= 0 && i_proc < 2) {
        if ((this->*init_table[i_proc])()) {
            mProcIdx = i_proc;
            return 1;
        }
    }
    return 0;
}

/* 000005C0-0000065C       .text process_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_main() {
    /* Nonmatching */
    static void (Act_c::*main_table[])() = {
        &Act_c::process_off_main,
        &Act_c::process_on_main,
    };
    if (mProcIdx >= 0 && mProcIdx < 2) {
        (this->*main_table[mProcIdx])();
    }
}

/* 0000065C-000007EC       .text process_common__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_common() {
    switch (mProcState) {
        case 0:
            for (int i = 0; i < 2; i++) {
                mTargetIds[i] = -1;
            }
            fopAcIt_Judge(ds_search_switchCB, this);
            if (mTargetIds[0] != -1 && mTargetIds[1] != -1) {
                fopAc_ac_c* actor0 = fopAcM_SearchByID(mTargetIds[0]);
                fopAc_ac_c* actor1 = fopAcM_SearchByID(mTargetIds[1]);
                if (actor0 != NULL && actor1 != NULL) {
                    s16 diff = actor0->shape_angle.y - shape_angle.y;
                    if (diff >= 0) {
                        s32 tmp = mTargetIds[0];
                        mTargetIds[0] = mTargetIds[1];
                        mTargetIds[1] = tmp;
                    }
                    mProcState = 1;
                }
            }
            break;
        case 1:
            fopAc_ac_c* actor0 = fopAcM_SearchByID(mTargetIds[0]);
            fopAc_ac_c* actor1 = fopAcM_SearchByID(mTargetIds[1]);
            if (actor0 != NULL && actor1 != NULL) {
                create_point_light(0, &actor0->current.pos);
                create_point_light(1, &actor1->current.pos);
                mProcState = 2;
            }
            break;
        case 2:
            execute_point_light();
            break;
    }
}

/* 000007EC-0000087C       .text create_point_light__Q28daObjVds5Act_cFiP4cXyz */
void daObjVds::Act_c::create_point_light(int i_idx, cXyz* i_pos) {
    int idx = i_idx & 1;
    mLights[idx].mPos = *i_pos;
    mBurnPos[idx] = *i_pos;
    mLights[idx].mColor.r = 0x400;
    mLights[idx].mColor.g = 0x400;
    mLights[idx].mColor.b = 0x400;
    mLights[idx].mPower = 0.0f;
    mLights[idx].mFluctuation = 0.0f;
    dKy_plight_set(&mLights[idx]);
}

/* 0000087C-00000900       .text execute_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::execute_point_light() {
    /* Nonmatching */
    for (int i = 0; i < 2; i++) {
        mLights[i].mPower = 2200.0f * mPowers[i];
        cXyz pos(mBurnPos[i]);
        mLights[i].mPos = pos;
        mLights[i].mColor.r = 0x400;
        mLights[i].mColor.g = 0x400;
        mLights[i].mColor.b = 0x400;
    }
}

/* 00000900-00000954       .text delete_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::delete_point_light() {
    for (int i = 0; i < 2; i++) {
        dKy_plight_cut(&mLights[i]);
    }
}

/* 00000954-00000968       .text Event_init__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_init() {
    mEvtIdx = -1;
    mEvtState = 0;
}

/* 00000968-00000A28       .text Event_exe__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_exe() {
    switch (mEvtState) {
        case 1:
            if (eventInfo.checkCommandDemoAccrpt()) {
                mEvtState = 2;
            } else {
                fopAcM_orderOtherEventId(this, mEvtIdx, 0xFF, 0xFFFF, 0, 1);
                eventInfo.onCondition(dEvtCnd_UNK2_e);
            }
            break;
        case 2:
            if (dComIfGp_evmng_endCheck(mEvtIdx)) {
                dComIfGp_event_onEventFlag(8);
                Event_init();
            }
            break;
    }
}

/* 00000A28-00000A4C       .text solidHeapCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
BOOL daObjVds::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return static_cast<Act_c*>(i_this)->create_heap();
}

const char daObjVds::Act_c::M_arcname[] = "Vds";

/* 00000A4C-00001020       .text create_heap__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::create_heap() {
    J3DModelData* mdl_data0 = (J3DModelData*)dComIfG_getObjectRes(M_arcname, 0xA);
    JUT_ASSERT(0x350, mdl_data0 != 0);
    M_bck_data0 = (J3DAnmTransformKey*)dComIfG_getObjectRes(M_arcname, 6);
    JUT_ASSERT(0x354, M_bck_data0 != 0);
    if (mdl_data0 != NULL && M_bck_data0 != NULL) {
        M_anm0 = new mDoExt_McaMorf(
            mdl_data0, NULL, NULL,
            M_bck_data0,
            0, 1.0f, 0, -1, 1,
            NULL,
            0x00000000,
            0x11020203
        );
    }
    JUT_ASSERT(0x361, M_anm0 != 0);
    J3DModelData* mdl_data1 = (J3DModelData*)dComIfG_getObjectRes(M_arcname, 0xB);
    JUT_ASSERT(0x365, mdl_data1 != 0);
    M_bck_data1 = (J3DAnmTransformKey*)dComIfG_getObjectRes(M_arcname, 7);
    JUT_ASSERT(0x369, M_bck_data1 != 0);
    if (mdl_data1 != NULL && M_bck_data1 != NULL) {
        M_anm1 = new mDoExt_McaMorf(
            mdl_data1, NULL, NULL,
            M_bck_data1,
            0, 1.0f, 0, -1, 1,
            NULL,
            0x00000000,
            0x11020203
        );
    }
    JUT_ASSERT(0x376, M_anm1 != 0);
    M_brk_data0 = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, 0xE);
    JUT_ASSERT(0x37B, M_brk_data0 != 0);
    s32 brk0ok = mBrk0.init(mdl_data0, M_brk_data0, 1, 0, 1.0f, 0, -1, 0, 0);
    M_brk_data1 = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, 0xF);
    JUT_ASSERT(0x388, M_brk_data1 != 0);
    s32 brk1ok = mBrk1.init(mdl_data1, M_brk_data1, 1, 0, 1.0f, 0, -1, 0, 0);
    set_mtx();
    cBgD_t* bgw_data = (cBgD_t*)dComIfG_getObjectRes(M_arcname, 0x12);
    JUT_ASSERT(0x39E, bgw_data != 0);
    if (bgw_data != NULL) {
        mBgW = new dBgW();
        if (mBgW != NULL) {
            mBgW->Set(bgw_data, 1, &mMtx);
        }
    }
    return M_bck_data0 != NULL && M_anm0 != NULL && M_anm0->getModel() != NULL &&
           M_bck_data1 != NULL && M_anm1 != NULL && M_anm1->getModel() != NULL &&
           mBgW != NULL && M_brk_data0 != NULL && M_brk_data1 != NULL &&
           brk0ok != 0 && brk1ok != 0;
}

/* 00001020-000011EC       .text _create__Q28daObjVds5Act_cFv */
cPhs_State daObjVds::Act_c::_create() {
    if (!fopAcM_CheckCondition(this, 8)) {
        new (this) Act_c();
        fopAcM_OnCondition(this, 8);
    }
    cPhs_State phs = dComIfG_resLoad(&mPhs, M_arcname);
    if (phs == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0) != 0) {
            set_first_process();
            fopAcM_SetMtx(this, M_anm0->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -2000.0f, -2000.0f, -2000.0f, 2000.0f, 2000.0f, 2000.0f);
            dComIfG_Bgsp()->Regist(mBgW, this);
            mBgW->SetCrrFunc(NULL);
            Event_init();
            mEvtIdx2 = dComIfGp_evmng_getEventIdx("Vds", 0xFF);
            for (int i = 0; i < 2; i++) {
                mTargetIds[i] = -1;
            }
        } else {
            phs = cPhs_ERROR_e;
        }
    }
    return phs;
}

/* 000012D4-00001368       .text _delete__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_delete() {
    if (heap != NULL && mBgW != NULL && mBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mBgW);
    }
    delete_point_light();
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 00001368-00001420       .text set_mtx__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_mtx() {
    M_anm0->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    M_anm0->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    M_anm1->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00001420-000014EC       .text _execute__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_execute() {
    Event_exe();
    PlayLoopJointAnimation();
    mBrk0.setFrame(mPowers[0] * (f32)(M_brk_data0->getFrameMax() - 1));
    mBrk1.setFrame(mPowers[1] * (f32)(M_brk_data1->getFrameMax() - 1));
    process_common();
    process_main();
    set_mtx();
    if (mBgW != NULL) {
        mBgW->Move();
    }
    return true;
}

static const u8 l_unusedColor[4] = {0xFF, 0x00, 0x00, 0x80};

/* 000014EC-000015A8       .text _draw__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(M_anm0->getModel(), &tevStr);
    g_env_light.setLightTevColorType(M_anm1->getModel(), &tevStr);
    J3DModelData* modelData0 = M_anm0->getModel()->getModelData();
    mBrk0.entry(modelData0, mBrk0.getFrame());
    J3DModelData* modelData1 = M_anm1->getModel()->getModelData();
    mBrk1.entry(modelData1, mBrk1.getFrame());
    M_anm0->updateDL();
    M_anm1->updateDL();
    return true;
}

namespace daObjVds {
namespace {
/* 000015A8-000015C8       .text Mthd_Create__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_create();
}

/* 000015C8-000015EC       .text Mthd_Delete__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_delete();
}

/* 000015EC-00001610       .text Mthd_Execute__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_execute();
}

/* 00001610-00001634       .text Mthd_Draw__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_draw();
}

/* 00001634-0000163C       .text Mthd_IsDelete__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
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
}; // namespace daObjVds

actor_process_profile_definition g_profile_Obj_Vds = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Vds_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVds::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Vds_e,
    /* Actor SubMtd */ &daObjVds::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
