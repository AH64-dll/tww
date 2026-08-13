#ifndef D_A_NPC_SARACE_H
#define D_A_NPC_SARACE_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Sarace_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Sarace_c::*ProcFunc)(void*);

    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8, f32);
    BOOL chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    BOOL CreateInit();
    void setAttention();
    void lookBack();
    void wait01();
    void talk01();
    BOOL dummy_action(void*);
    BOOL wait_action(void*);
    BOOL event_endCheck_action(void*);
    void set_mtx();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

    virtual u16 next_msgStatus(u32*);
    virtual u32 getMsg();
    virtual void anmAtr(u16);

    cXyz* getEyePos() { return &m6FC; }
    cXyz* getAttentionBasePos() { return &m708; }

    inline BOOL setAction(ProcFunc i_newProcFunc, void* i_argsP) {
        if (mAction != i_newProcFunc) {
            if (mAction) {
                m746 = -1;
                (this->*mAction)(i_argsP);
            }
            mAction = i_newProcFunc;
            m746 = 0;
            (this->*mAction)(i_argsP);
        }
        return TRUE;
    }

    static s32 ship_race_rupee;
    static s32 ship_race_result;

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ mDoExt_McaMorf* mpMorf2;
    /* 0x6D0 */ u32 mShadowId;
    /* 0x6D4 */ u32 m6D4;
    /* 0x6D8 */ u32 mBarrelAId;
    /* 0x6DC */ u32 mBarrelBId;
    /* 0x6E0 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6E4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F8 */ u8 mBtpFrame;
    /* 0x6F9 */ u8 m6F9;
    /* 0x6FA */ s16 mTimer;
    /* 0x6FC */ cXyz m6FC;
    /* 0x708 */ cXyz m708;
    /* 0x714 */ s16 m714;
    /* 0x716 */ u8 m716[2];
    /* 0x718 */ s16 m718;
    /* 0x71A */ s16 m71A;
    /* 0x71C */ s16 m71C;
    /* 0x71E */ u8 m71E[6];
    /* 0x724 */ u32 mMsgNo;
    /* 0x728 */ u8 m728;
    /* 0x729 */ u8 m729;
    /* 0x72A */ u8 m72A[6];
    /* 0x730 */ u8 m730;
    /* 0x731 */ u8 m731[3];
    /* 0x734 */ ProcFunc mAction;
    /* 0x740 */ s8 m740;
    /* 0x741 */ s8 m741;
    /* 0x742 */ s8 m742;
    /* 0x743 */ s8 m743;
    /* 0x744 */ u8 m744[2];
    /* 0x746 */ s8 m746;
    /* 0x747 */ u8 m747;
};  // Size: 0x748

class daNpc_Sarace_HIO_c : public JORReflexible {
public:
    daNpc_Sarace_HIO_c();
    virtual ~daNpc_Sarace_HIO_c() {}
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ dNpc_HIO_c mNpc;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
};  // Size: 0x38

#endif /* D_A_NPC_SARACE_H */
