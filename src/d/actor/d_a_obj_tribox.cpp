/**
 * d_a_obj_tribox.cpp
 * Object - Hyrule Castle - Pushable triangle blocks
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include <math.h>
#include "d/actor/d_a_obj_tribox.h"
#include "d/d_bg_s.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_particle.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_manager.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/actor/d_a_player_main.h"
#include "f_pc/f_pc_name.h"
#include "f_pc/f_pc_draw_priority.h"
#include "res/Object/MtryB.h"

namespace daObjTribox {
    namespace {
        f32 L_r_in = 41.666668f * std::sqrtf(3.0f);
        f32 L_r_out = 2.0f * L_r_in;

        static const Attr_c l_attr = {
            -0.8f,
            0.82f,
            0.5f,
            5,
            12,
            0.4f,
            65,
            74,
            50,
            0,
        };

        cPhs_State Mthd_Create(void* i_this) {
            return static_cast<Act_c*>(i_this)->_create();
        }

        BOOL Mthd_Delete(void* i_this) {
            return static_cast<Act_c*>(i_this)->_delete();
        }

        BOOL Mthd_Execute(void* i_this) {
            return static_cast<Act_c*>(i_this)->_execute();
        }

        BOOL Mthd_Draw(void* i_this) {
            return static_cast<Act_c*>(i_this)->_draw();
        }

        BOOL Mthd_IsDelete(void* i_this) {
            return true;
        }
    };  // namespace

    const char Act_c::M_arcname[] = "MtryB";

    cXyz Act_c::M_post[3] = {
        cXyz(0.0f, 0.0f, -L_r_out),
        cXyz(-125.0f, 0.0f, L_r_in),
        cXyz(125.0f, 0.0f, L_r_in),
    };
    dBgS_ObjLinChk Act_c::M_lin;

    /* 000000EC-000001A4       .text set_state__Q211daObjTribox5Act_cFv */
    void Act_c::set_state() {
        int type = prm_get_type();
        int swSave = prm_get_swSave();
        bool sw = dComIfGs_isSwitch(swSave, home.roomNo);
        if (type == 0) {
            if (sw) {
                mMode = 1;
            } else {
                mMode = 0;
            }
        } else {
            if (sw) {
                mMode = 3;
            } else {
                mMode = 2;
            }
        }
    }

    /* 000001A4-000001C8       .text solidHeapCB__Q211daObjTribox5Act_cFP10fopAc_ac_c */
    BOOL Act_c::solidHeapCB(fopAc_ac_c* i_actor) {
        return static_cast<Act_c*>(i_actor)->create_heap();
    }

    /* 000001C8-000004B0       .text create_heap__Q211daObjTribox5Act_cFv */
    u8 Act_c::create_heap() {
        J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_MTRYB_BDL_MTRYB_e);
        JUT_ASSERT(0x140, model_data != 0);
        mpModel = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);

        cBgD_t* bgw_data = (cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_MTRYB_DZB_MTRYB_e);
        JUT_ASSERT(0x149, bgw_data != 0);
        if (mpModel) {
            mpBgW = dBgW_NewSet(bgw_data, cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx());
        } else {
            mpBgW = 0;
        }

        J3DModelData* model_ytfbl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_MTRYB_BDL_YTFBL00_e);
        JUT_ASSERT(0x159, model_ytfbl_data != 0);
        mpModel2 = mDoExt_J3DModel__create(model_ytfbl_data, 0x80000, 0x11000022);

        J3DAnmTevRegKey* brk_app_data = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_MTRYB_BRK_YTFBL00_APP_e);
        JUT_ASSERT(0x163, brk_app_data != 0);
        int brkOk = mBrkAnm.init(model_ytfbl_data, brk_app_data, 1, 0, 1.0f, 0, -1, 0);

        J3DAnmTevRegKey* brk_cmn_data = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_MTRYB_BRK_YTFBL00_CMN_e);
        JUT_ASSERT(0x16D, brk_cmn_data != 0);
        int brk2Ok = mBrkAnm2.init(model_ytfbl_data, brk_cmn_data, 1, 2, 1.0f, 0, -1, 0);

        bool success = (mpModel != 0 && mpBgW != 0 && mpModel2 != 0 && brkOk && brk2Ok);
        if (!success) {
            mpBgW = 0;
        }
        return success;
    }

    /* 000004B0-000005C0       .text block_init__Q211daObjTribox5Act_cFv */
    void Act_c::block_init() {
        cullMtx = mpModel->getBaseTRMtx();
        init_mtx();
        fopAcM_setCullSizeSphere(this, 0.0f, 125.0f, 0.0f, 200.0f);
        dComIfG_Bgsp()->Regist(mpBgW, this);
        mpBgW->SetCrrFunc(dBgS_MoveBGProc_TypicalRotY);
        mpBgW->Move();
        mpBgW->SetPushPullCallback(push_pullCB);

        M_correct_flag = false;
        mPP[0].mFlag = 0;
        mPP[0].mX = 0;
        mPP[0].mY = 0;
        mPP[0].mZ = 0;
        mPP[1].mFlag = 0;
        mPP[1].mX = 0;
        mPP[1].mY = 0;
        mPP[1].mZ = 0;
        mPP[2].mFlag = 0;
        mPP[2].mX = 0;
        mPP[2].mY = 0;
        mPP[2].mZ = 0;
        m344 = current.pos;
        m350 = 0;
        m354 = 0;
        m358 = 1;
        m394 = 0;
        mode_block_wait_init();
    }

    /* 000005C0-00000604       .text chk_light__Q211daObjTribox5Act_cCFv */
    u8 Act_c::chk_light() const {
        return dComIfGs_isEventBit(0x3820) ? 2 : 0;
    }

    /* 00000604-0000068C       .text correct_before_init__Q211daObjTribox5Act_cFv */
    void Act_c::correct_before_init() {
        fopAcM_setCullSizeSphere(this, 0.0f, 125.0f, 0.0f, 200.0f);
        if (m38E) {
            m396 = dComIfGp_evmng_getEventIdx("MtryB_sink", 0xFF);
        } else {
            m396 = -1;
        }
        mode_correct_off_init();
    }

    /* 0000068C-00000748       .text correct_after_init__Q211daObjTribox5Act_cFv */
    void Act_c::correct_after_init() {
        current.pos.y = home.pos.y + -245.0f;
        cullMtx = mpModel->getBaseTRMtx();
        init_mtx();
        fopAcM_setCullSizeSphere(this, 0.0f, 125.0f, 0.0f, 200.0f);
        dComIfG_Bgsp()->Regist(mpBgW, this);
        mpBgW->SetCrrFunc(0);
        mpBgW->Move();
        mpBgW->SetPushPullCallback(0);
        m394 = chk_light();
        mode_correct_dummy_init();
    }

    /* 00000748-00000840       .text controll_set__Q211daObjTribox5Act_cFv */
    void Act_c::controll_set() {
        if (base.base.mInitState == 0) {
            if (prm_get_type() == 1) {
                fpcPi_Change(&base.base.mPi, -3, 2, 0xFFFD);
                if (M_c_cont_cnt == 0) {
                    m38E = 1;
                    M_sink_start = 0;
                    M_correct_flag = false;
                    M_correct_cnt = 0;
                } else {
                    m38E = 0;
                }
                M_c_cont_cnt++;
                sound_pos_init();
                return;
            }
            if (M_b_cont_cnt == 0) {
                m38E = 1;
            } else {
                m38E = 0;
            }
            M_b_cont_cnt++;
        }
    }

    /* 00000840-00000904       .text controll_clear__Q211daObjTribox5Act_cFv */
    void Act_c::controll_clear() {
        if (prm_get_type() == 1) {
            M_c_cont_cnt--;
            JUT_ASSERT(0x214, M_c_cont_cnt >= 0);
        } else {
            M_b_cont_cnt--;
            JUT_ASSERT(0x217, M_b_cont_cnt >= 0);
        }
    }

    /* 00000904-00000980       .text create_block_before__Q211daObjTribox5Act_cFv */
    cPhs_State Act_c::create_block_before() {
        cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
        if (phase_state == cPhs_COMPLEATE_e) {
            if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x11C0) != 0) {
                block_init();
            } else {
                phase_state = cPhs_ERROR_e;
            }
        }
        return phase_state;
    }

    /* 00000980-00000988       .text create_block_after__Q211daObjTribox5Act_cFv */
    cPhs_State Act_c::create_block_after() {
        return cPhs_ERROR_e;
    }

    /* 00000988-000009AC       .text create_correct_before__Q211daObjTribox5Act_cFv */
    cPhs_State Act_c::create_correct_before() {
        correct_before_init();
        return cPhs_COMPLEATE_e;
    }

    /* 000009AC-00000A28       .text create_correct_after__Q211daObjTribox5Act_cFv */
    cPhs_State Act_c::create_correct_after() {
        cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
        if (phase_state == cPhs_COMPLEATE_e) {
            if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x4000) != 0) {
                correct_after_init();
            } else {
                phase_state = cPhs_ERROR_e;
            }
        }
        return phase_state;
    }

    /* 00000A28-00000BC4       .text _create__Q211daObjTribox5Act_cFv */
    cPhs_State Act_c::_create() {
        if (!fopAcM_CheckCondition(this, 8)) {
            new (this) Act_c();
            fopAcM_OnCondition(this, 8);
        }
        set_state();
        controll_set();
        static const cPhs_State (Act_c::*create_proc[])() = {
            &Act_c::create_block_before,
            &Act_c::create_block_after,
            &Act_c::create_correct_before,
            &Act_c::create_correct_after,
        };
        return (this->*create_proc[mMode])();
    }

    /* 00000BC4-00000CA4       .text _delete__Q211daObjTribox5Act_cFv */
    bool Act_c::_delete() {
        sound_pos_delete();
        controll_clear();
        eff_smoke_remove();
        eff_sink_smoke_remove();
        if (mMode == 0 || mMode == 3) {
            if (mpBgW) {
                mpBgW->SetPushPullCallback(0);
            }
            if (mpBgW && mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
            dComIfG_resDelete(&mPhs, M_arcname);
        }
        return true;
    }

    /* 00000D68-00000DFC       .text set_mtx__Q211daObjTribox5Act_cFv */
    void Act_c::set_mtx() {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        PSMTXCopy(mDoMtx_stack_c::get(), mpModel->getBaseTRMtx());
        mDoMtx_stack_c::transM(0.0f, 251.0f, 0.0f);
        PSMTXCopy(mDoMtx_stack_c::get(), mpModel2->getBaseTRMtx());
    }

    /* 00000DFC-00000E54       .text init_mtx__Q211daObjTribox5Act_cFv */
    void Act_c::init_mtx() {
        mpModel->setBaseScale(scale);
        mpModel2->setBaseScale(scale);
        set_mtx();
    }

    /* 00000E54-00000F8C       .text push_pullCB__Q211daObjTribox5Act_cFP10fopAc_ac_cP10fopAc_ac_csQ24dBgW13PushPullLabel */
    fopAc_ac_c* Act_c::push_pullCB(fopAc_ac_c* i_actor, fopAc_ac_c* i_actor2, s16 i_angle, dBgW::PushPullLabel i_pp_label) {
        static const s16 face_ang_offset[3] = {0, 0x5555, 0xAAAB};
        dBgW::PushPullLabel pp_label = (dBgW::PushPullLabel)(i_pp_label & 3);
        if (pp_label != 0) {
            const int pp_field = dBgW::PPLABEL_PUSH | dBgW::PPLABEL_PULL;
            JUT_ASSERT(0x2B0, pp_label != pp_field);
            if (pp_label & 1) {
                ((Act_c*)i_actor)->mPP[0].mZ = 0;
            } else {
                ((Act_c*)i_actor)->mPP[0].mZ = 1;
            }
            s16 angle = i_angle - 0x8000;
            s16 angleDiff = angle - ((Act_c*)i_actor)->shape_angle.y;
            if (angleDiff >= -0x2AAA && angleDiff < 0x2AAA) {
                ((Act_c*)i_actor)->mPP[0].mX = 0;
            } else if (angleDiff >= 0x2AAA) {
                ((Act_c*)i_actor)->mPP[0].mX = 1;
            } else {
                ((Act_c*)i_actor)->mPP[0].mX = 2;
            }
            s16 searchAngle = fopAcM_searchActorAngleY((fopAc_ac_c*)i_actor, i_actor2);
            s16 faceAngle = ((Act_c*)i_actor)->shape_angle.y + face_ang_offset[((Act_c*)i_actor)->mPP[0].mX];
            if ((s16)(faceAngle - searchAngle) >= 0) {
                ((Act_c*)i_actor)->mPP[0].mY = 0;
            } else {
                ((Act_c*)i_actor)->mPP[0].mY = 1;
            }
            ((Act_c*)i_actor)->mPP[0].mFlag = 1;
        }
        return (fopAc_ac_c*)i_actor;
    }

    /* 00000F8C-00000FF4       .text line_cross__Q211daObjTribox5Act_cCFPC4cXyzPC4cXyz */
    bool Act_c::line_cross(const cXyz* i_start, const cXyz* i_end) const {
        M_lin.Set((cXyz*)i_start, (cXyz*)i_end, const_cast<Act_c*>(this));
        M_lin.SetActorPid(fopAcM_GetID((void*)this));
        return dComIfG_Bgsp()->LineCross(&M_lin);
    }

    /* 00000FF4-000012A0       .text chk_wall__Q211daObjTribox5Act_cCFi */
    bool Act_c::chk_wall(int num) const {
        JUT_ASSERT(0x30C, (num == 1) || (num == 2));
        int idx = (m358 >= 0) ? (m354 + 1) % 3 : (m354 + 2) % 3;
        mDoMtx_stack_c::YrotS(shape_angle.y);
        cXyz postPos;
        PSMTXMultVecSR(mDoMtx_stack_c::get(), &M_post[idx], &postPos);

        cXyz startPos(current.pos.x, current.pos.y + 5.0f, current.pos.z);
        cXyz dir = postPos * 0.99f;
        cXyz endPos = startPos - dir;
        if (line_cross(&startPos, &endPos)) {
            return true;
        }
        if (num == 2) {
            cXyz startPos2 = startPos;
            s16 rot = (m358 >= 0) ? 0x2AAA : -0x2AAA;
            mDoMtx_stack_c::YrotM(rot);
            cXyz postPos2;
            PSMTXMultVecSR(mDoMtx_stack_c::get(), &M_post[idx], &postPos2);
            cXyz dir2 = postPos2 * 0.49f;
            cXyz endPos2 = startPos2 - dir2;
            if (line_cross(&startPos2, &endPos2)) {
                return true;
            }
            startPos2.y += 30.0f;
            cXyz dir3 = postPos2 * 0.99f;
            cXyz endPos3 = startPos2 - dir3;
            if (line_cross(&startPos2, &endPos3)) {
                return true;
            }
        }
        return false;
    }

    /* 000012A0-000012E8       .text chk_space__Q211daObjTribox5Act_cCFv */
    bool Act_c::chk_space() const {
        if (chk_wall((mPP[2].mZ == 1) ? 2 : 1)) {
            return false;
        } else {
            return true;
        }
    }

    /* 000012E8-00001378       .text eff_flash__Q211daObjTribox5Act_cFv */
    void Act_c::eff_flash() {
        cXyz pos = current.pos;
        pos.y += 251.0f;
        dComIfGp_particle_setP1(0x833A, &pos, &shape_angle, NULL, 0xFF, NULL);
    }

    /* 00001378-00001464       .text eff_smoke_start__Q211daObjTribox5Act_cFv */
    void Act_c::eff_smoke_start() {
        static cXyz scl(0.6f, 0.6f, 0.6f);
        eff_smoke_pos();
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(0x2022, &mSmokePos, &mSmokeAngle, &scl, 0xB9, &mSmokeCB);
        if (emitter) {
            emitter->setRate(1.0f);
            emitter->setDirectionalSpeed(15.0f);
            emitter->setSpread(0.15f);
            emitter->setLifeTime(0x1E);
        }
    }

    /* 00001464-000015C8       .text eff_smoke_pos__Q211daObjTribox5Act_cFv */
    void Act_c::eff_smoke_pos() {
        int idx1, idx2;
        if (m358 >= 0) {
            idx1 = m354 + 1;
            idx2 = m354 + 2;
        } else {
            idx1 = m354 + 2;
            idx2 = m354 + 1;
        }
        idx1 %= 3;
        idx2 %= 3;
        mDoMtx_stack_c::YrotS(shape_angle.y);
        cXyz pos1, pos2;
        PSMTXMultVecSR(mDoMtx_stack_c::get(), &M_post[idx1], &pos1);
        PSMTXMultVecSR(mDoMtx_stack_c::get(), &M_post[idx2], &pos2);
        cXyz dir = pos2 - pos1;
        dir.normalizeZP();
        PSVECScale(&dir, &dir, 10.0f);
        mSmokePos = pos1 + dir + current.pos;
        mSmokeAngle.x = 0;
        mSmokeAngle.y = cLib_targetAngleY(&pos1, &pos2);
        mSmokeAngle.z = 0;
    }

    /* 000015C8-000015F4       .text eff_smoke_end__Q211daObjTribox5Act_cFv */
    void Act_c::eff_smoke_end() {
        mSmokeCB.end();
    }

    /* 000015F4-00001620       .text eff_smoke_remove__Q211daObjTribox5Act_cFv */
    void Act_c::eff_smoke_remove() {
        mSmokeCB.remove();
    }

    /* 00001620-0000162C       .text eff_sink_smoke_init__Q211daObjTribox5Act_cFv */
    void Act_c::eff_sink_smoke_init() {
        m3F8 = 0;
    }

    /* 0000162C-00001740       .text eff_sink_smoke_start__Q211daObjTribox5Act_cFv */
    void Act_c::eff_sink_smoke_start() {
        if (m3F8 == 0) {
            m3F8 = 1;
            dPa_smokeEcallBack* cbs[3] = {&mSinkSmokeCB, &mSinkSmokeCB2, &mSinkSmokeCB3};
            for (int i = 0; i < 3; i++) {
                SVec a;
                a.x = shape_angle.x;
                a.y = shape_angle.y + i * 0x5555;
                a.z = shape_angle.z;
                dComIfGp_particle_set(0xA320, &current.pos, (const csXyz*)&a, NULL, 0xA0, cbs[i]);
            }
        }
    }

    /* 00001740-000017B8       .text eff_sink_smoke_end__Q211daObjTribox5Act_cFv */
    void Act_c::eff_sink_smoke_end() {
        if (m3F8 != 0) {
            m3F8 = 0;
            mSinkSmokeCB.end();
            mSinkSmokeCB2.end();
            mSinkSmokeCB3.end();
        }
    }

    /* 000017B8-0000181C       .text eff_sink_smoke_remove__Q211daObjTribox5Act_cFv */
    void Act_c::eff_sink_smoke_remove() {
        mSinkSmokeCB.remove();
        mSinkSmokeCB2.remove();
        mSinkSmokeCB3.remove();
    }

    /* 0000181C-00001828       .text vib_sink_init__Q211daObjTribox5Act_cFv */
    void Act_c::vib_sink_init() {
        m3F9 = 0;
    }

    /* 00001828-000018FC       .text vib_sink_start__Q211daObjTribox5Act_cFv */
    void Act_c::vib_sink_start() {
        if (m3F9 == 0) {
            m3F9 = 1;
            dComIfGp_getVibration().StartShock(2, 1, cXyz(0.0f, 1.0f, 0.0f));
            dComIfGp_getVibration().StartShock(1, 6, cXyz(0.0f, 1.0f, 0.0f));
            dComIfGp_getVibration().StartQuake(3, 0xF, cXyz(0.0f, 1.0f, 0.0f));
        }
    }

    /* 000018FC-0000197C       .text vib_sink_end__Q211daObjTribox5Act_cFv */
    void Act_c::vib_sink_end() {
        if (m3F9 != 0) {
            m3F9 = 0;
            dComIfGp_getVibration().StopQuake(-1);
            dComIfGp_getVibration().StartShock(3, 0xF, cXyz(0.0f, 1.0f, 0.0f));
        }
    }

    /* 0000197C-00001A08       .text search_block__Q211daObjTribox5Act_cFPvPv */
    fopAc_ac_c* Act_c::search_block(void* i_actor, void* i_self) {
        fopAc_ac_c* actor = (fopAc_ac_c*)i_actor;
        fopAc_ac_c* self = (fopAc_ac_c*)i_self;
        if (fopAcM_IsActor(actor) && fopAcM_GetName(actor) == fpcNm_Obj_Tribox_e &&
            ((Act_c*)actor)->prm_get_type() == 0 &&
            fopAcM_searchActorDistance2(self, actor) < 225.0f)
        {
            return actor;
        }
        return NULL;
    }

    /* 00001A08-00001A90       .text sound_pos_init__Q211daObjTribox5Act_cFv */
    void Act_c::sound_pos_init() {
        if (m38E) {
            M_sound_pos = home.pos * 0.33333334f;
        } else {
            cXyz pos = home.pos * 0.33333334f;
            PSVECAdd(&M_sound_pos, &pos, &M_sound_pos);
        }
    }

    /* 00001A90-00001AC4       .text sound_pos_delete__Q211daObjTribox5Act_cFv */
    void Act_c::sound_pos_delete() {
        mDoAud_seDeleteObject(&M_sound_pos);
    }

    /* 00001AC4-00001D0C       .text sound_get_mapinfo__Q211daObjTribox5Act_cFRC4cXyz */
    int Act_c::sound_get_mapinfo(const cXyz& i_pos) {
        dBgS_ObjGndChk gndChk;
        gndChk.SetObj();
        cXyz pos(i_pos.x, i_pos.y + 50.0f, i_pos.z);
        gndChk.SetPos(&pos);
        int mtrlSndId = 0xD;
        if (dComIfG_Bgsp()->GroundCross(&gndChk)) {
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(gndChk);
        }
        return mtrlSndId;
    }

    /* 000021CC-00002268       .text sound_sink_down_block__Q211daObjTribox5Act_cFv */
    void Act_c::sound_sink_down_block() {
        if (m38E) {
            mDoAud_seStart(0x6222, &M_sound_pos, sound_get_mapinfo(M_sound_pos), dComIfGp_getReverb(current.roomNo));
        }
    }

    /* 00002268-00002304       .text sound_sink_stop_block__Q211daObjTribox5Act_cFv */
    void Act_c::sound_sink_stop_block() {
        if (m38E) {
            mDoAud_seStart(0x6A2C, &M_sound_pos, sound_get_mapinfo(M_sound_pos), dComIfGp_getReverb(current.roomNo));
        }
    }

    /* 00002304-000023A0       .text sound_flash_shine__Q211daObjTribox5Act_cFv */
    void Act_c::sound_flash_shine() {
        if (m38E) {
            mDoAud_seStart(0x6A24, &M_sound_pos, sound_get_mapinfo(M_sound_pos), dComIfGp_getReverb(current.roomNo));
        }
    }

    /* 000023A0-0000243C       .text sound_flash_light__Q211daObjTribox5Act_cFv */
    void Act_c::sound_flash_light() {
        if (m38E) {
            mDoAud_seStart(0x6223, &M_sound_pos, sound_get_mapinfo(M_sound_pos), dComIfGp_getReverb(current.roomNo));
        }
    }

    /* 0000243C-00002458       .text mode_block_wait_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_block_wait_init() {
        fopAcM_OnStatus(this, 0x80);
        m340 = 0;
        m308 = 0;
    }

    /* 00002458-000025C0       .text mode_block_wait__Q211daObjTribox5Act_cFv */
    void Act_c::mode_block_wait() {
        if (M_correct_flag) {
            m340 = 0;
            mode_block_sink_init();
            return;
        }
        if (mPP[0].mFlag && mPP[0].mX == mPP[1].mX && mPP[0].mY == mPP[1].mY && mPP[0].mZ == mPP[1].mZ) {
            m340++;
        } else {
            m340 = 0;
        }
        if (m340 >= 4) {
            if ((mPP[0].mY == 0 && mPP[0].mZ == 1) || (mPP[0].mY == 1 && mPP[0].mZ == 0)) {
                m358 = 1;
            } else {
                m358 = -1;
            }
            if (mPP[0].mY == 0) {
                m354 = (mPP[0].mX + 2) % 3;
            } else {
                m354 = (mPP[0].mX + 1) % 3;
            }
            mPP[2] = mPP[0];
            if (chk_space()) {
                mode_block_walk_init();
            }
        }
    }

    /* 000025C0-0000262C       .text mode_block_walk_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_block_walk_init() {
        fopAcM_OffStatus(this, 0x80);
        m308 = 1;
        m30C = 0x14;
        m344 = current.pos;
        eff_smoke_start();
        dComIfGp_event_onEventFlag(0x800);
    }

    /* 0000262C-00002B34       .text mode_block_walk__Q211daObjTribox5Act_cFv */
    void Act_c::mode_block_walk() {
        m30C--;
        bool finished = (m30C <= 0);
        f32 cosVal = cosf(0.15707963f * m30C);
        f32 angleY = (9.5873802e-05f * home.angle.z) + (1.0471976f * m350);
        f32 dir = m358;
        f32 rot = 1.0471976f * (dir * (0.5f * (1.0f + cosVal)));
        PSMTXRotRad(mDoMtx_stack_c::get(), 0x59, angleY);
        cXyz postPos;
        PSMTXMultVecSR(mDoMtx_stack_c::get(), &M_post[m354], &postPos);
        mDoMtx_stack_c::rYrotM(rot);
        cXyz postPos2;
        PSMTXMultVecSR(mDoMtx_stack_c::get(), &M_post[m354], &postPos2);
        cXyz newPos = m344 + postPos2;
        cXyz diff = newPos - m344;
        current.pos = diff;
        shape_angle.y = (s16)(0.5f + (10430.378f * (angleY + rot)));

        if (finished) {
            eff_smoke_end();
        } else {
            eff_smoke_pos();
        }
        if (finished) {
            dComIfGp_event_offEventFlag(0x800);
            m350 = (m350 + m358) % 6;
            if (chk_wall(1)) {
                int mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(M_lin);
                mDoAud_seStart(0x2823, &eyePos, mtrlSndId, dComIfGp_getReverb(current.roomNo));
            }
            mode_block_wait_init();
            return;
        }
        dBgS_ObjGndChk gndChk;
        gndChk.SetObj();
        cXyz pos2(current.pos.x, current.pos.y + 50.0f, current.pos.z);
        gndChk.SetPos(&pos2);
        int mtrlSndId = 0;
        if (dComIfG_Bgsp()->GroundCross(&gndChk)) {
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(gndChk);
        }
        mDoAud_seStart(0x2022, &eyePos, mtrlSndId, dComIfGp_getReverb(current.roomNo));
    }

    /* 00002B34-00002B90       .text mode_block_sink_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_block_sink_init() {
        fopAcM_OffStatus(this, 0x80);
        m308 = 2;
        m390 = 0.0f;
        m30C = 0;
        eff_sink_smoke_init();
        vib_sink_init();
    }

    /* 00002B90-00002CE4       .text mode_block_sink__Q211daObjTribox5Act_cFv */
    void Act_c::mode_block_sink() {
        if (M_sink_start) {
            eff_sink_smoke_start();
            vib_sink_start();
            f32 sinkY = home.pos.y + -245.0f;
            m390 += l_attr.m00;
            s16 frame = m30C;
            if ((frame >= l_attr.m0C) && (frame < l_attr.m0E)) {
                m390 *= l_attr.m08;
            } else if ((frame >= l_attr.m14) && (frame < l_attr.m16)) {
                m390 *= l_attr.m10;
            } else {
                m390 *= l_attr.m04;
            }
            current.pos.y += m390;
            if (current.pos.y < sinkY) {
                current.pos.y = sinkY;
                eff_sink_smoke_end();
                vib_sink_end();
                sound_sink_stop_block();
                mode_block_lower_init();
                return;
            }
            sound_sink_down_block();
            m30C++;
            return;
        }
        m390 = 0.0f;
        m30C = 0;
    }

    /* 00002CE4-00002D14       .text mode_block_lower_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_block_lower_init() {
        fopAcM_OffStatus(this, 0x80);
        m308 = 3;
        m30C = l_attr.m18;
        m3FA = 0x5E;
    }

    /* 00002D14-00002DA8       .text mode_block_lower__Q211daObjTribox5Act_cFv */
    void Act_c::mode_block_lower() {
        if (m30C > 0) {
            m30C--;
            if (m30C == 0) {
                eff_flash();
                m394 = 1;
            }
        }
        if (m30C == 0) {
            if (m3FA > 0) {
                m3FA--;
                if (m3FA == 0) {
                    sound_flash_shine();
                }
            }
        } else {
            m3FA = 0x5E;
        }
    }

    /* 00002DA8-00002DC0       .text mode_correct_off_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_off_init() {
        fopAcM_OffStatus(this, 0x80);
        m308 = 4;
    }

    /* 00002DC0-00002E1C       .text mode_correct_off__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_off() {
        if (fopAcM_Search((fopAcIt_JudgeFunc)&Act_c::search_block, this)) {
            M_correct_cnt++;
            mode_correct_on_init();
        }
    }

    /* 00002E1C-00002E34       .text mode_correct_on_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_on_init() {
        fopAcM_OffStatus(this, 0x80);
        m308 = 5;
    }

    /* 00002E34-00002EEC       .text mode_correct_on__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_on() {
        if (fopAcM_Search((fopAcIt_JudgeFunc)&Act_c::search_block, this)) {
            if (m38E && M_correct_cnt >= 3) {
                M_correct_flag = true;
            }
            if (M_correct_flag) {
                if (m38E) {
                    mode_correct_demoreq_init();
                    return;
                }
                mode_correct_end_init();
            }
        } else {
            M_correct_cnt--;
            mode_correct_off_init();
        }
    }

    /* 00002EEC-00002F0C       .text mode_correct_demoreq_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_demoreq_init() {
        fopAcM_OffStatus(this, 0x80);
        m308 = 6;
        m30C = 0xA;
    }

    /* 00002F0C-00002FB4       .text mode_correct_demoreq__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_demoreq() {
        bool waiting = true;
        if (dComIfGp_evmng_existence(m396)) {
            if (eventInfo.checkCommandDemoAccrpt()) {
                m395 = 1;
            } else {
                fopAcM_orderOtherEventId(this, m396, 0xFF, 0xFFFF, 0, 1);
                eventInfo.onCondition(2);
                waiting = false;
            }
        }
        if (waiting) {
            mode_correct_demorun_init();
        }
    }

    /* 00002FB4-00003028       .text mode_correct_demorun_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_demorun_init() {
        fopAcM_OffStatus(this, 0x80);
        m308 = 7;
        m30C = 0x32;
        mDoAud_seStart(0x806);
    }

    /* 00003028-00003104       .text mode_correct_demorun__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_demorun() {
        if (m30C > 0) {
            m30C--;
            if (m30C == 0) {
                int swSave = prm_get_swSave();
                dComIfGs_onSwitch(swSave, home.roomNo);
                M_sink_start = 1;
            }
        } else {
            bool done = true;
            if (m395) {
                if (dComIfGp_evmng_endCheck(m396)) {
                    dComIfGp_event_reset();
                    m395 = 0;
                } else {
                    done = false;
                }
            }
            if (done) {
                mode_correct_end_init();
            }
        }
    }

    /* 00003104-0000311C       .text mode_correct_end_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_end_init() {
        fopAcM_OnStatus(this, 0x80);
        m308 = 8;
    }

    /* 0000311C-00003120       .text mode_correct_end__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_end() {}

    /* 00003120-00003138       .text mode_correct_dummy_init__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_dummy_init() {
        fopAcM_OffStatus(this, 0x80);
        m308 = 9;
    }

    /* 00003138-0000313C       .text mode_correct_dummy__Q211daObjTribox5Act_cFv */
    void Act_c::mode_correct_dummy() {}

    /* 0000313C-00003288       .text mode_proc_call__Q211daObjTribox5Act_cFv */
    void Act_c::mode_proc_call() {
        static const void (Act_c::*mode_proc[])() = {
            &Act_c::mode_block_wait,
            &Act_c::mode_block_walk,
            &Act_c::mode_block_sink,
            &Act_c::mode_block_lower,
            &Act_c::mode_correct_off,
            &Act_c::mode_correct_on,
            &Act_c::mode_correct_demoreq,
            &Act_c::mode_correct_demorun,
            &Act_c::mode_correct_end,
            &Act_c::mode_correct_dummy,
        };
        (this->*mode_proc[m308])();
    }

    /* 00003288-00003304       .text execute_block__Q211daObjTribox5Act_cFv */
    void Act_c::execute_block() {
        mode_proc_call();
        mPP[1] = mPP[0];
        mPP[0].mFlag = 0;
        eyePos = current.pos;
        set_mtx();
        mpBgW->Move();
    }

    /* 00003304-00003324       .text execute_correct__Q211daObjTribox5Act_cFv */
    void Act_c::execute_correct() {
        mode_proc_call();
    }

    /* 00003324-000033D8       .text _execute__Q211daObjTribox5Act_cFv */
    bool Act_c::_execute() {
        if (prm_get_type() == 0) {
            execute_block();
        } else {
            execute_correct();
        }
        if (mpModel2) {
            if (m394 == 1) {
                if (mBrkAnm.play()) {
                    m394 = 2;
                }
            } else if (m394 == 2) {
                mBrkAnm2.play();
            }
            if (m394 == 1 || m394 == 2) {
                sound_flash_light();
            }
        }
        return true;
    }

    /* 000033D8-00003538       .text _draw__Q211daObjTribox5Act_cFv */
    bool Act_c::_draw() {
        if (mMode == 0 || mMode == 3) {
            g_env_light.settingTevStruct(0, &current.pos, &tevStr);
            g_env_light.setLightTevColorType(mpModel, &tevStr);
            if (m394) {
                g_env_light.setLightTevColorType(mpModel2, &tevStr);
                if (m394 == 1) {
                    J3DModelData* modelData = mpModel2->getModelData();
                    mBrkAnm.entry(modelData, mBrkAnm.getFrame());
                } else {
                    J3DModelData* modelData2 = mpModel2->getModelData();
                    mBrkAnm2.entry(modelData2, mBrkAnm2.getFrame());
                }
            }
            if (m394) {
                dComIfGd_setListP1();
                mDoExt_modelUpdateDL(mpModel2);
                dComIfGd_setList();
            }
            dComIfGd_setListBG();
            mDoExt_modelUpdateDL(mpModel);
            dComIfGd_setList();
        }
        return true;
    }
};  // namespace daObjTribox

namespace daObjTribox {
    namespace {
        static actor_method_class Mthd_Table = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    };  // namespace
};  // namespace daObjTribox

actor_process_profile_definition g_profile_Obj_Tribox = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Tribox_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTribox::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Tribox_e,
    /* Actor SubMtd */ &daObjTribox::Mthd_Table,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
