#ifndef D_A_NPC_GK1_H
#define D_A_NPC_GK1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Gk1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Gk1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_Neck(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    s32 init_GK1_0();
    u8 createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    s32 setBtp(s8, bool);
    s32 init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_GK1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    BOOL chk_talk();
    BOOL chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void privateCut(int);
    void endEvent();
    s32 isEventEntry();
    void event_proc(int);
    BOOL set_action(int (daNpc_Gk1_c::*)(void*), void*);
    void setStt(s8);
    BOOL chk_attn();
    BOOL wait_1();
    BOOL talk_1();
    BOOL wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    s32 bodyCreateHeap();
    s32 itemCreateHeap();
    s32 hat_CreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_nck_jnt_num;
    /* 0x6D0 */ J3DModel* mpItemModel;
    /* 0x6D4 */ J3DModel* mpHatModel;
    /* 0x6D8 */ char m_arcname[4];
    /* 0x6DC */ u32 mShadowID;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F4 */ u8 mBlinkFrame;
    /* 0x6F6 */ s16 mBlinkTimer;
    /* 0x6F8 */ ProcFunc mProcFunc;
    /* 0x704 */ u8 field_0x704[0x708 - 0x704];
    /* 0x708 */ fpc_ProcID mPartnerProcID;
    /* 0x70C */ u8 field_0x70C[0x714 - 0x70C];
    /* 0x714 */ cXyz mPrevPos;
    /* 0x720 */ csXyz mPrevAngle;
    /* 0x726 */ csXyz mAngle;
    /* 0x72C */ u8 field_0x72C[0x734 - 0x72C];
    /* 0x734 */ cXyz mTargetPos;
    /* 0x740 */ cXyz mEyePos;
    /* 0x74C */ u8 field_0x74C[0x758 - 0x74C];
    /* 0x758 */ cXyz mHeadPos;
    /* 0x764 */ u8 field_0x764[0x770 - 0x764];
    /* 0x770 */ f32 mPrevMorfFrame;
    /* 0x774 */ u8 field_0x774[0x778 - 0x774];
    /* 0x778 */ s16 mLookAtY;
    /* 0x77A */ s16 mLookAtNckX;
    /* 0x77C */ s16 mLookAtBoneX;
    /* 0x77E */ u8 field_0x77E[0x780 - 0x77E];
    /* 0x780 */ s32 mActionResult;
    /* 0x784 */ s16 mEventIdTable[1];
    /* 0x786 */ s16 mEventIdx;
    /* 0x788 */ u8 field_0x788[0x790 - 0x788];
    /* 0x790 */ s16 mEvTimer;
    /* 0x792 */ u8 field_0x792[0x79A - 0x792];
    /* 0x79A */ s16 m79A;
    /* 0x79C */ u8 m79C;
    /* 0x79D */ u8 m79D;
    /* 0x79E */ u8 mTalkStatus;
    /* 0x79F */ u8 mCreatePhase;
    /* 0x7A0 */ u8 m7A0;
    /* 0x7A1 */ u8 m7A1;
    /* 0x7A2 */ u8 m7A2;
    /* 0x7A3 */ u8 m7A3;
    /* 0x7A4 */ u8 m7A4;
    /* 0x7A5 */ u8 m7A5;
    /* 0x7A6 */ bool m7A6;
    /* 0x7A7 */ u8 m7A7;
    /* 0x7A8 */ u8 m7A8;
    /* 0x7A9 */ s8 m7A9;
    /* 0x7AA */ u8 mAnmAtr;
    /* 0x7AB */ u8 mAnmTag;
    /* 0x7AC */ s8 mBtpNum;
    /* 0x7AD */ s8 mActNo;
    /* 0x7AE */ s8 mStatus;
    /* 0x7AF */ s8 mAnmNum;
    /* 0x7B0 */ u8 m7B0;
    /* 0x7B1 */ s8 m7B1;
    /* 0x7B2 */ s8 mTypeInit;
    /* 0x7B3 */ s8 mType;
    /* 0x7B4 */ u8 m7B4;
    /* 0x7B5 */ s8 m7B5;
};  // Size: 0x7B8

#endif /* D_A_NPC_GK1_H */
