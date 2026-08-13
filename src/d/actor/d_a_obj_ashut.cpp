/**
 * d_a_obj_ashut.cpp
 * Object - Metal bars (Pirate Ship rope minigame)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ashut.h"
#include "res/Object/Ashut.h"

namespace daObjAshut {
    namespace {
        struct L_attr_t {
            /* 0x00 */ f32 mUpper;
            /* 0x04 */ f32 mFall;
            /* 0x08 */ f32 mFallRate;
            /* 0x0C */ u8 mTimer;
            /* 0x10 */ f32 mBounce;
            /* 0x14 */ f32 mBounceMax;
            /* 0x18 */ f32 mRise;
            /* 0x1C */ f32 mRiseRate1;
            /* 0x20 */ f32 mRiseRate2;
            /* 0x24 */ u8 mTimer2;
            /* 0x25 */ u8 mTimer2Max;
            /* 0x26 */ u8 mTimer3;
            /* 0x28 */ f32 mDamp;
            /* 0x2C */ f32 mDampMin;
        };
        static const L_attr_t L_attr = {
            250.0f, -2.5f, 0.05f, 5, -0.5f, 7.0f, 0.8f, 0.1f, 0.4f, 14, 4, 5, -0.6f, -4.0f,
        };
    } // namespace

    Mtx Act_c::M_tmp_mtx;
    const char Act_c::M_arcname[] = "Ashut";

    /* 00000078-0000012C       .text CreateHeap__Q210daObjAshut5Act_cFv */
    BOOL Act_c::CreateHeap() {
        J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_ASHUT_BDL_ASHUT_e);
        JUT_ASSERT(0xF9, mdl_data != 0);
        mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000022);
        return mpModel != NULL;
    }

    /* 0000012C-00000224       .text Create__Q210daObjAshut5Act_cFv */
    BOOL Act_c::Create() {
        mpBgW->SetPriority((cBgW::PRIORITY)1);
        fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
        init_mtx();
        fopAcM_setCullSizeBox(this, -80.0f, -5.0f, -30.0f, 80.0f, 250.0f, 30.0f);
        mIsDemo = 0;
        mEvtIdx = dComIfGp_evmng_getEventIdx(NULL, prm_get_evId());
        mDemoNext = 5;
        if (is_switch()) {
            mode_upper_init();
        } else {
            mode_lower_init();
        }
        return TRUE;
    }

    /* 00000224-00000388       .text Mthd_Create__Q210daObjAshut5Act_cFv */
    cPhs_State Act_c::Mthd_Create() {
        fopAcM_ct(this, daObjAshut::Act_c);
        cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
        if (phase_state == cPhs_COMPLEATE_e) {
            phase_state = MoveBGCreate(M_arcname, dRes_INDEX_ASHUT_DZB_ASHUT_e, NULL, 0x760);
            JUT_ASSERT(0x138, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
            if (is_switch()) {
                if (mpBgW->ChkUsed()) {
                    dComIfG_Bgsp()->Release(mpBgW);
                }
            }
        }
        return phase_state;
    }

    /* 00000388-00000390       .text Delete__Q210daObjAshut5Act_cFv */
    BOOL Act_c::Delete() {
        return TRUE;
    }

    /* 00000390-000003DC       .text Mthd_Delete__Q210daObjAshut5Act_cFv */
    BOOL Act_c::Mthd_Delete() {
        BOOL result = MoveBGDelete();
        dComIfG_resDelete(&mPhs, M_arcname);
        return result;
    }

    /* 000003DC-0000046C       .text set_mtx__Q210daObjAshut5Act_cFv */
    void Act_c::set_mtx() {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        PSMTXCopy(mDoMtx_stack_c::get(), M_tmp_mtx);
        mDoMtx_stack_c::get()[1][3] += mOffset;
        PSMTXCopy(mDoMtx_stack_c::get(), mpModel->getBaseTRMtx());
    }

    /* 0000046C-000004A8       .text init_mtx__Q210daObjAshut5Act_cFv */
    void Act_c::init_mtx() {
        mpModel->setBaseScale(scale);
        set_mtx();
    }

    /* 000004A8-000005A4       .text chk_safe_area__Q210daObjAshut5Act_cCFv */
    /* Nonmatching */
    u8 Act_c::chk_safe_area() const {
        u8 result;
        s16 angle = -shape_angle.y;
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        cXyz sp20 = player->current.pos - current.pos;
        mDoMtx_stack_c::YrotS(angle);
        cXyz sp14;
        mDoMtx_stack_c::multVecSR(&sp20, &sp14);
        result = FALSE;
        if (std::fabsf(sp14.y) < 100.0f && std::fabsf(sp14.z) < 55.0f) {
            result = TRUE;
        }
        if (result) {
            if (std::fabsf(sp14.x) < 105.0f) {
                result = TRUE;
            }
        }
        return result;
    }

    /* 000005A4-000005BC       .text mode_upper_init__Q210daObjAshut5Act_cFv */
    void Act_c::mode_upper_init() {
        mMode = Mode_UPPER;
        mOffset = L_attr.mUpper;
    }

    /* 000005BC-0000066C       .text mode_upper__Q210daObjAshut5Act_cFv */
    void Act_c::mode_upper() {
        if (!is_switch()) {
            if (!chk_safe_area()) {
                if (!mpBgW->ChkUsed()) {
                    dComIfG_Bgsp()->Regist(mpBgW, this);
                }
                mode_demoreq_init(Mode_U_L);
            }
        }
    }

    /* 0000066C-00000700       .text mode_u_l_init__Q210daObjAshut5Act_cFv */
    void Act_c::mode_u_l_init() {
        mMode = Mode_U_L;
        mSpeed = 0.0f;
        mTimer = L_attr.mTimer;
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_P_SHIP_SHTR_CL, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
    }

    /* 00000700-000007C0       .text mode_u_l__Q210daObjAshut5Act_cFv */
    void Act_c::mode_u_l() {
        mSpeed += L_attr.mFall;
        mSpeed *= 1.0f - L_attr.mFallRate;
        mOffset += mSpeed;
        if (mOffset <= 0.0f) {
            if (mTimer == 0) {
                mode_lower_init();
            } else {
                mTimer--;
                mOffset *= L_attr.mBounce;
                mSpeed *= L_attr.mBounce;
                if (mSpeed > L_attr.mBounceMax) {
                    mSpeed = L_attr.mBounceMax;
                }
            }
        }
    }

    /* 000007C0-000007D8       .text mode_lower_init__Q210daObjAshut5Act_cFv */
    void Act_c::mode_lower_init() {
        mMode = Mode_LOWER;
        mOffset = 0.0f;
    }

    /* 000007D8-00000838       .text mode_lower__Q210daObjAshut5Act_cFv */
    void Act_c::mode_lower() {
        if (is_switch()) {
            mode_demoreq_init(Mode_L_U);
        }
    }

    /* 00000838-000008D4       .text mode_l_u_init__Q210daObjAshut5Act_cFv */
    void Act_c::mode_l_u_init() {
        mMode = Mode_L_U;
        mSpeed = 0.0f;
        mTimer = L_attr.mTimer3;
        mTimer2 = L_attr.mTimer2;
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_P_SHIP_SHTR_OP, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
    }

    /* 000008D4-00000A50       .text mode_l_u__Q210daObjAshut5Act_cFv */
    /* Nonmatching */
    void Act_c::mode_l_u() {
        if (mTimer2 > 0) {
            mTimer2--;
        }
        mSpeed += L_attr.mRise;
        if (mTimer2 > 0 && mTimer2 < L_attr.mTimer2Max) {
            mSpeed *= 1.0f - L_attr.mRiseRate2;
        } else {
            mSpeed *= 1.0f - L_attr.mRiseRate1;
        }
        mOffset += mSpeed;
        if (mOffset > 150.0f) {
            if (mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
        }
        if (mOffset >= L_attr.mUpper) {
            if (mTimer == 0) {
                mode_upper_init();
            } else {
                mTimer--;
                f32 damp = L_attr.mDamp;
                mOffset = L_attr.mUpper + (mOffset - L_attr.mUpper) * damp;
                mSpeed *= damp;
                if (mSpeed < L_attr.mDampMin) {
                    mSpeed = L_attr.mDampMin;
                }
            }
        }
    }

    /* 00000A50-00000B0C       .text mode_demoreq_init__Q210daObjAshut5Act_cFQ310daObjAshut5Act_c6Mode_e */
    void Act_c::mode_demoreq_init(Mode_e i_demo_next) {
        JUT_ASSERT(0x222, (i_demo_next == Mode_U_L) || (i_demo_next == Mode_L_U));
        if (mIsDemo) {
            if (i_demo_next == Mode_U_L) {
                mode_u_l_init();
            } else {
                mode_l_u_init();
            }
        } else {
            mMode = Mode_DEMOREQ;
            mDemoNext = i_demo_next;
        }
    }

    /* 00000B0C-00000BE4       .text mode_demoreq__Q210daObjAshut5Act_cFv */
    void Act_c::mode_demoreq() {
        u8 done = FALSE;
        if (dComIfGp_evmng_existence(mEvtIdx)) {
            if (eventInfo.checkCommandDemoAccrpt()) {
                done = TRUE;
                mIsDemo = 1;
            } else {
                fopAcM_orderOtherEventId(this, mEvtIdx, prm_get_evId(), 0xFFFF, 0, 1);
                eventInfo.onCondition(dEvtCnd_UNK2_e);
            }
        } else {
            done = TRUE;
        }
        if (done) {
            if (mDemoNext == Mode_U_L) {
                mode_u_l_init();
            } else {
                mode_l_u_init();
            }
        }
    }

    /* 00000BE4-00000D0C       .text Execute__Q210daObjAshut5Act_cFPPA3_A4_f */
    /* Nonmatching */
    BOOL Act_c::Execute(Mtx** i_mtx) {
        typedef void (Act_c::*modeProc)();
        static modeProc mode_proc[] = {
            &Act_c::mode_upper,
            &Act_c::mode_u_l,
            &Act_c::mode_lower,
            &Act_c::mode_l_u,
            &Act_c::mode_demoreq,
        };
        (this->*mode_proc[mMode])();
        eyePos.set(current.pos.x, current.pos.y + mOffset, current.pos.z);
        set_mtx();
        *i_mtx = &M_tmp_mtx;
        return TRUE;
    }

    /* 00000D0C-00000D6C       .text Draw__Q210daObjAshut5Act_cFv */
    BOOL Act_c::Draw() {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModel, &tevStr);
        mDoExt_modelUpdateDL(mpModel);
        return TRUE;
    }
}; // namespace daObjAshut

namespace daObjAshut {
    namespace {
        /* 00000D6C-00000D8C       .text Mthd_Create__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
        cPhs_State Mthd_Create(void* i_this) {
            return ((Act_c*)i_this)->Mthd_Create();
        }

        /* 00000D8C-00000DAC       .text Mthd_Delete__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
        BOOL Mthd_Delete(void* i_this) {
            return ((Act_c*)i_this)->Mthd_Delete();
        }

        /* 00000DAC-00000DCC       .text Mthd_Execute__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
        BOOL Mthd_Execute(void* i_this) {
            return ((Act_c*)i_this)->MoveBGExecute();
        }

        /* 00000DCC-00000DF8       .text Mthd_Draw__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
        BOOL Mthd_Draw(void* i_this) {
            return ((Act_c*)i_this)->MoveBGDraw();
        }

        /* 00000DF8-00000E24       .text Mthd_IsDelete__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
        BOOL Mthd_IsDelete(void* i_this) {
            return ((Act_c*)i_this)->MoveBGIsDelete();
        }

        static actor_method_class Mthd_Table = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    }; // namespace
}; // namespace daObjAshut

actor_process_profile_definition g_profile_Obj_Ashut = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Ashut_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAshut::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Ashut_e,
    /* Actor SubMtd */ &daObjAshut::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
