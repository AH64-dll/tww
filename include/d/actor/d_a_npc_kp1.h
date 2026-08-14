#ifndef D_A_NPC_KP1_H
#define D_A_NPC_KP1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daNpc_Kp1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Kp1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 bckNum;
        /* 0x01 */ s8 btpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    };  // Size: 0x10

    bool createInit();
    void setMtx();
    int anmResID(int, int*, int*);
    int BtpNum2ResID(int, int*);
    void setAnm_tex(s8);
    bool init_btp(bool, int);
    bool initTexPatternAnm(bool);
    void playTexPatternAnm();
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    void setStt(s8);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    bool chkAttention();
    void setAttention();
    bool chk_talk();
    bool decideType(int);
    void event_actionInit(int);
    BOOL event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    bool set_action(ProcFunc, void*);
    BOOL wait01();
    BOOL talk01();
    BOOL wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_head_jnt_num;
    /* 0x6CD */ s8 m_backbone_jnt_num;
    /* 0x6CE */ s8 m_handL_jnt_num;
    /* 0x6CF */ u8 field_0x6cf;
    /* 0x6D0 */ J3DModel* mpModel;
    /* 0x6D4 */ J3DModel* mpHandLModel;
    /* 0x6D8 */ u8 mShadowIdx;
    /* 0x6D9 */ u8 field_0x6d9[3];
    /* 0x6DC */ u32 mShadowId;
    /* 0x6E0 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6E4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F8 */ u8 mBtpFrame;
    /* 0x6F9 */ u8 field_0x6f9;
    /* 0x6FA */ s16 mBtpTimer;
    /* 0x6FC */ ProcFunc mCurrProcFunc;
    /* 0x708 */ dNpc_EventCut_c mEvtCut;
    /* 0x774 */ s16 mSaveAngleX;
    /* 0x776 */ s16 mSaveAngleY;
    /* 0x778 */ s16 mSaveAngleZ;
    /* 0x77C */ cXyz mSavePos;
    /* 0x788 */ cXyz mAttPos;
    /* 0x794 */ cXyz mEyePos;
    /* 0x7A0 */ cXyz mLookTarget;
    /* 0x7AC */ f32 mMorfFrame;
    /* 0x7B0 */ u8 field_0x7b0[8];
    /* 0x7B8 */ s16 mLookAngle;
    /* 0x7BA */ s16 mLookStartAngle;
    /* 0x7BC */ s8 mPlayEnd;
    /* 0x7BD */ s8 mAnmTimer;
    /* 0x7BE */ u8 mMsgNo;
    /* 0x7BF */ u8 mTalkFlag;
    /* 0x7C0 */ u8 mEventFlag;
    /* 0x7C1 */ u8 mPresentFlag;
    /* 0x7C2 */ u8 mCancelFlag;
    /* 0x7C3 */ u8 mInitFlag;
    /* 0x7C4 */ s32 mAttnFlag;
    /* 0x7C8 */ s32 mTalkResult;
    /* 0x7CC */ u8 mAttention;
    /* 0x7CD */ u8 mTalkEnd;
    /* 0x7CE */ bool mLookBackFlag;
    /* 0x7CF */ u8 mDemoFlag;
    /* 0x7D0 */ u8 mTalkClear;
    /* 0x7D1 */ s8 mActIdx;
    /* 0x7D2 */ s8 mEventAction;
    /* 0x7D3 */ u8 mAnmAtr;
    /* 0x7D4 */ u8 mAnmTag;
    /* 0x7D5 */ s8 mBtpNum;
    /* 0x7D6 */ s8 mBckNum;
    /* 0x7D7 */ s8 mStatus;
    /* 0x7D8 */ s8 mType;
    /* 0x7D9 */ s8 mPrevType;
    /* 0x7DA */ s8 mLookMode;
    /* 0x7DB */ s8 mSpecificType;
    /* 0x7DC */ s8 mSubType;
    /* 0x7DD */ s8 mWaitFlag;
    /* 0x7DE */ s8 mAnmAtrStep;
    /* 0x7DF */ u8 field_0x7df;
};  // Size: 0x7E0

class daNpc_Kp1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 mMaxHeadX;
        /* 0x02 */ s16 mMaxHeadY;
        /* 0x04 */ s16 mMinHeadX;
        /* 0x06 */ s16 mMinHeadY;
        /* 0x08 */ s16 mMaxBackboneX;
        /* 0x0A */ s16 mMaxBackboneY;
        /* 0x0C */ s16 mMinBackboneX;
        /* 0x0E */ s16 mMinBackboneY;
        /* 0x10 */ s16 mMaxTurnStep;
        /* 0x12 */ s16 mCalcAngleTarget;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ u32 field_0x18;
    };  // Size: 0x1C

    daNpc_Kp1_HIO_c();
    virtual ~daNpc_Kp1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x5[3];
    /* 0x08 */ s32 field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};  // Size: 0x28

#endif /* D_A_NPC_KP1_H */
