#ifndef D_A_NPC_DE1_H
#define D_A_NPC_DE1_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/d_bg_w_deform.h"
#include "d/d_particle.h"

class daNpc_De1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_De1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ u8 field_0x01[3];
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };  // Size: 0x10

    BOOL createInit();
    void setMtx();
    void anmResID(int, int*, int*);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int);
    BOOL setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    void setStt(s8);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chkAttention();
    void setAttention();
    fopAc_ac_c* searchByID(fpc_ProcID);
    void setDemoStartCenter();
    bool partner_srch();
    void ccCreate();
    void cc_set();
    void set_pa_happa();
    void del_pa_happa();
    void followPa_happa();
    bool decideType(int);
    void event_actionInit(int);
    bool event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    BOOL set_action(ProcFunc, void*);
    BOOL wait01();
    BOOL wait02();
    BOOL wait03();
    BOOL wait04();
    BOOL wait05();
    BOOL talk01();
    BOOL talk02();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    bool demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_branchL_jnt_num;
    /* 0x6CD */ s8 m_head_jnt_num;
    /* 0x6CE */ u8 field_0x6CE[2];
    /* 0x6D0 */ dBgWDeform* mpDeform;
    /* 0x6D4 */ ProcFunc mCurrProcFunc;
    /* 0x6E0 */ dNpc_EventCut_c mEventCut;
    /* 0x74C */ csXyz mInitialAngle;
    /* 0x754 */ cXyz mInitialPos;
    /* 0x760 */ cXyz mTransformedEyePos;
    /* 0x76C */ cXyz m76C;
    /* 0x778 */ cXyz m778;
    /* 0x784 */ cXyz mDemoStartCenter;
    /* 0x790 */ f32 mPrevMorfFrame;
    /* 0x794 */ u32 field_0x794;
    /* 0x798 */ s16 mTimer0;
    /* 0x79A */ s16 mTimer1;
    /* 0x79C */ s16 field_0x79C;
    /* 0x79E */ s16 mTimer2;
    /* 0x7A0 */ u8 field_0x7A0[4];
    /* 0x7A4 */ u8 mbMorfAnimStopped;
    /* 0x7A5 */ u8 m7A5;
    /* 0x7A6 */ u8 m7A6;
    /* 0x7A7 */ u8 m7A7;
    /* 0x7A8 */ u8 mbRanExecute;
    /* 0x7A9 */ u8 field_0x7A9[3];
    /* 0x7AC */ u32 m7AC;
    /* 0x7B0 */ u8 field_0x7B0[4];
    /* 0x7B4 */ u8 mbAttention;
    /* 0x7B5 */ u8 m7B5;
    /* 0x7B6 */ u8 m7B6;
    /* 0x7B7 */ u8 mbInDemo;
    /* 0x7B8 */ u8 m7B8;
    /* 0x7B9 */ u8 field_0x7B9[3];
    /* 0x7BC */ dPa_followEcallBack mEcallBack;
    /* 0x7D0 */ cXyz mParticlePos;
    /* 0x7DC */ u32 m_cc_ID[10];
    /* 0x804 */ s8 m_c0_jnt_num[10];
    /* 0x80E */ u8 m80E;
    /* 0x80F */ u8 m80F;
    /* 0x810 */ u32 mPartnerProcID;
    /* 0x814 */ s8 mActIdx;
    /* 0x815 */ s8 mActNo;
    /* 0x816 */ u8 mAnmAtr;
    /* 0x817 */ u8 mAnmTag;
    /* 0x818 */ s8 mAnmNum;
    /* 0x819 */ s8 mOrder;
    /* 0x81A */ s8 mStatus;
    /* 0x81B */ s8 mPrevStatus;
    /* 0x81C */ s8 mType;
    /* 0x81D */ s8 mSpecificType;
    /* 0x81E */ s8 mStep;
    /* 0x81F */ u8 mTagInitCounter;
};  // Size: 0x820

#endif /* D_A_NPC_DE1_H */
