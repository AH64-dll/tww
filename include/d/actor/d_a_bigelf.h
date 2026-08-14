#ifndef D_A_BIGELF_H
#define D_A_BIGELF_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

class daBigelf_c : public fopAc_ac_c {
public:
    typedef BOOL (daBigelf_c::*ActionFunc)(void*);

    bool chkFlag(unsigned short flag) { return (mStateBits & flag) == flag; }
    void clrFlag(unsigned short flag) { mStateBits &= ~flag; }
    void setFlag(unsigned short flag) { mStateBits |= flag; }
    s8 getBackboneJntNum() { return mJntCtrl.getBackboneJntNum(); }
    s8 getHeadJntNum() { return mJntCtrl.getHeadJntNum(); }
    s16 getHead_x() { return mJntCtrl.getHead_x(); }
    void incAttnSetCount() {}
    void setAction(ActionFunc i_actionFunc, void* i_param) {
        if (mCurrentStateFunc != i_actionFunc) {
            if (mCurrentStateFunc != NULL) {
                m3F6 = -1;
                (this->*mCurrentStateFunc)(i_param);
            }
            mCurrentStateFunc = i_actionFunc;
            m3F6 = 0;
            (this->*mCurrentStateFunc)(i_param);
        }
    }
    void setAttentionBasePos(cXyz i_pos) { mAttentionBasePos = i_pos; }
    void setEyePos(cXyz i_pos) { mEyePos = i_pos; }

    void oct_delete();
    s32 nodeCallBack(J3DNode*);
    void lightInit(cXyz*);
    void lightEnd();
    void lightProc();
    void darkInit();
    void darkEnd();
    void darkProc();
    void demoInitFlDelete();
    BOOL demoProcFlDelete();
    void demoInitFlLink();
    BOOL demoProcFlLink();
    void demoInitFlDmAf();
    BOOL demoProcFlDmAf();
    void demoInitFlDmMd();
    BOOL demoProcFlDmMd();
    void demoInitFlDmBf();
    BOOL demoProcFlDmBf();
    void demoInitFlDemo();
    BOOL demoProcFlDemo();
    void demoInitExit();
    BOOL demoProcExit();
    void demoInitTalk();
    BOOL demoProcTalk();
    void demoInitAppear();
    BOOL demoProcAppear();
    void demoInitFa1();
    BOOL demoProcFa1();
    void demoInitWait();
    BOOL demoProcWait();
    void demoInitCom();
    void demoProcCom();
    int getNowEventAction();
    void demoProc();
    u8 getType();
    u8 getSwbit();
    u8 getSwbit2();
    u16 getEventFlag();
    void makeFa1S();
    void makeFa1();
    void setAnm(signed char);
    void setAnmStatus();
    s32 next_msgStatus(unsigned long*);
    u32 getMsg();
    void msgPushButton();
    void msgAnm(unsigned char);
    void talkInit();
    u16 talk();
    BOOL init();
    void setAttention(BOOL);
    void lookBack();
    BOOL hunt();
    BOOL oct_search();
    BOOL oct();
    BOOL ready0();
    BOOL event0();
    BOOL dead();
    BOOL wait_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x290 */ request_of_phase_process_class mPhaseProcReq;
    /* 0x298 */ mDoExt_McaMorf* mpBckAnimator;
    /* 0x29C */ mDoExt_brkAnm mBrkAnimator;
    /* 0x2B4 */ mDoExt_btkAnm mBtkAnimator;
    /* 0x2C8 */ J3DModel* mpFlowerModel;
    /* 0x2CC */ mDoExt_brkAnm mFlowerBrkAnimator;
    /* 0x2E4 */ s8 mHandRBJointIndex;
    /* 0x2E5 */ u8 m2E5[0x2E8 - 0x2E5];
    /* 0x2E8 */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x31C */ cXyz mEyePos;
    /* 0x328 */ cXyz mAttentionBasePos;
    /* 0x334 */ u8 m334[0x336 - 0x334];
    /* 0x336 */ s8 m336;
    /* 0x337 */ u8 m337;
    /* 0x338 */ f32 m338;
    /* 0x33C */ u32 m33C;
    /* 0x340 */ u16 mStateBits;
    /* 0x342 */ u8 m342[0x344 - 0x342];
    /* 0x344 */ s8 m344;
    /* 0x345 */ u8 m345[0x346 - 0x345];
    /* 0x346 */ u8 mGivenItem;
    /* 0x347 */ u8 m347[0x348 - 0x347];
    /* 0x348 */ u32 mCurrentMessageId;
    /* 0x34C */ u32 m34C;
    /* 0x350 */ s16 m350;
    /* 0x352 */ bool mIsLightShining;
    /* 0x353 */ u8 m353[0x354 - 0x353];
    /* 0x354 */ LIGHT_INFLUENCE mLightInfluence;
    /* 0x374 */ cXyz mLightInfluencePos;
    /* 0x380 */ GXColorS10 mLightInfluenceColor;
    /* 0x388 */ f32 mLightInfluencePower;
    /* 0x38C */ f32 mLightInfluenceFluctuation;
    /* 0x390 */ u8 m390[0x39C - 0x390];
    /* 0x39C */ s8 mDark;
    /* 0x39D */ u8 m39D[0x3A0 - 0x39D];
    /* 0x3A0 */ f32 m3A0;
    /* 0x3A4 */ f32 m3A4;
    /* 0x3A8 */ f32 m3A8;
    /* 0x3AC */ s16 m3AC;
    /* 0x3AE */ u8 m3AE[0x3B0 - 0x3AE];
    /* 0x3B0 */ ActionFunc mCurrentStateFunc;
    /* 0x3BC */ s8 m3BC;
    /* 0x3BD */ s8 m3BD;
    /* 0x3BE */ u8 m3BE[0x3C0 - 0x3BE];
    /* 0x3C0 */ s16 m3C0;
    /* 0x3C2 */ u8 m3C2[0x3C4 - 0x3C2];
    /* 0x3C4 */ int mStaffId;
    /* 0x3C8 */ s16 m3C8;
    /* 0x3CA */ s16 m3CA;
    /* 0x3CC */ JPABaseEmitter* m3CC;
    /* 0x3D0 */ cXyz m3D0;
    /* 0x3DC */ u8 m3DC;
    /* 0x3DD */ u8 m3DD[0x3E0 - 0x3DD];
    /* 0x3E0 */ JPABaseEmitter* m3E0;
    /* 0x3E4 */ JPABaseEmitter* m3E4;
    /* 0x3E8 */ f32 mHeightOffset;
    /* 0x3EC */ f32 m3EC;
    /* 0x3F0 */ f32 m3F0;
    /* 0x3F4 */ s8 m3F4;
    /* 0x3F5 */ s8 m3F5;
    /* 0x3F6 */ s8 m3F6;
    /* 0x3F7 */ s8 m3F7;
    /* 0x3F8 */ u32 m3F8;
};

#endif /* D_A_BIGELF_H */
