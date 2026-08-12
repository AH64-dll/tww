#ifndef D_A_NPC_UK_H
#define D_A_NPC_UK_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"

class daNpc_Uk_c : public fopAc_ac_c {
public:

    enum TalkStates {
        TALK_FINISHED = -1,
        TALK_INIT = 0,
        TALK_MSG_CREATE = 1,
        TALK_ACTIVE = 2
    };

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING = 1,
        ACTION_ENDING = -1,
    };

    enum Types {
        TYPE_NONE = 0,
        TYPE_NORMAL = 1,
        TYPE_MINIGAME = 2,
    };

    typedef BOOL (daNpc_Uk_c::*ActionFunc)(void*);

    BOOL ChkOrder(u8 flag) { return mOrderFlags & flag; }
    void ClrOrder(u8 flag) { mOrderFlags &= ~flag; }
    void SetOrder(u8 flag) { mOrderFlags |= flag; }

    bool chkFlag(u16 flag) { return (mFlags & flag) == flag; }
    void clrFlag(u16 flag) { mFlags &= ~flag; }
    s8 getBackboneJntNum() { return m_jnt.getBackboneJntNum(); }
    s8 getHeadJntNum() { return m_jnt.getHeadJntNum(); }
    s16 getBackbone_x() { return m_jnt.getBackbone_x(); }
    s16 getBackbone_y() { return m_jnt.getBackbone_y(); }
    s16 getHead_x() { return m_jnt.getHead_x(); }
    s16 getHead_y() { return m_jnt.getHead_y(); }

    void incAttnSetCount() {
        if (mAttnSetCount != 0xff) {
            mAttnSetCount++;
        }
    }

    BOOL setAction(ActionFunc actionFunc, void* arg) {
        if (mCurrActionFunc != actionFunc) {
            if (mCurrActionFunc != NULL) {
                mActionStatus = ACTION_ENDING;
                (this->*mCurrActionFunc)(arg);
            }
            mCurrActionFunc = actionFunc;
            mActionStatus = ACTION_STARTING;
            (this->*mCurrActionFunc)(arg);
        }
        return TRUE;
    }

    void setAttentionBasePos(cXyz i_attnBasePos) { mAttnBasePos = i_attnBasePos; }
    void setEyePos(cXyz i_eyePos) { mEyePos = i_eyePos; }
    void setFlag(u16 flag) { mFlags |= flag; }

    u8 getType();
    u8 getPath();
    u8 getShapeType();
    u16 getCaughtFlag();
    u16 getFoundFlag();
    u32 getFirstTalk();
    BOOL chkGameStart();
    BOOL chkPositioning(f32, f32, f32, s16, s16);
    u8 nextVisitMode();
    BOOL approachRun(fopAc_ac_c*);
    BOOL aroundWalk(fopAc_ac_c*);
    BOOL surrender();
    BOOL runawayInit();
    static BOOL nodeCallBack_Uk(J3DNode*, int);
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8, u8);
    bool chkAttentionLocal();
    void chkAttention();
    void setAnmStatus();
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void msgAnm(u8);
    void talkInit();
    u16 talk();
    BOOL init();
    void setAttention(bool);
    u8 getLookBackMode();
    void lookBack();
    u32 getStaffName();
    BOOL checkDemoStart();
    s32 getNowEventAction();
    void visitInit(u8);
    void visitProc();
    bool wait01();
    bool talk01();
    bool talk02();
    u8 visitTalkInit();
    void visitSetEvent();
    bool visit01();
    bool warningB();
    bool warningC();
    bool warningD();
    bool found();
    bool runaway();
    bool jump();
    bool jitanda01();
    bool jitanda02();
    bool demo01();
    bool demo02();
    void demoInitCom();
    bool demoProc();
    BOOL wait_action(void*);
    BOOL seek_action(void*);
    BOOL hind_action(void*);
    BOOL visit_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ u32 mShadowId;
    /* 0x2A4 */ J3DAnmTexPattern* mBtpRes;
    /* 0x2A8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2BC */ u8 mBlinkFrame;
    /* 0x2BD */ u8 field_0x2BD;
    /* 0x2BE */ s16 mBlinkTimer;
    /* 0x2C0 */ dBgS_ObjAcch mObjAcch;
    /* 0x484 */ dBgS_AcchCir mAcchCir;
    /* 0x4DC */ dCcD_Stts mStts;
    /* 0x4FC */ dCcD_Cyl mCyl;
    /* 0x62C */ dNpc_JntCtrl_c m_jnt;
    /* 0x660 */ cXyz mEyePos;
    /* 0x66C */ cXyz mAttnBasePos;
    /* 0x678 */ s16 mMaxHeadTurnVelocity;
    /* 0x67A */ s8 mAnmEnded;
    /* 0x67B */ u8 mAttnSetCount;
    /* 0x67C */ f32 mAnmTimer;
    /* 0x680 */ u32 mCurrMsgNo;
    /* 0x684 */ u16 mFlags;
    /* 0x686 */ u8 mAttentionTimer;
    /* 0x687 */ u8 mMsgSelectNum;
    /* 0x688 */ dNpc_PathRun_c mPathRun;
    /* 0x690 */ f32 m690;
    /* 0x694 */ f32 m694;
    /* 0x698 */ dNpc_PathRun_c mPathRun2;
    /* 0x6A0 */ ActionFunc mCurrActionFunc;
    /* 0x6A4 */ s8 mTexPatternIdx;
    /* 0x6A5 */ s8 mAnmIdx;
    /* 0x6A6 */ u8 field_0x6A6;
    /* 0x6A7 */ u8 field_0x6A7;
    /* 0x6A8 */ int mStaffIdx;
    /* 0x6AC */ s32 mEventAction;
    /* 0x6B0 */ u8 mOrderFlags;
    /* 0x6B1 */ s8 mState;
    /* 0x6B2 */ s8 mPrevState;
    /* 0x6B3 */ s8 mType;
    /* 0x6B4 */ s8 mActionStatus;
    /* 0x6B5 */ s8 mTalkState;
    /* 0x6B6 */ u8 mMsgAnmIdx;
    /* 0x6B7 */ u8 field_0x6B7;
    /* 0x6B8 */ u32 mMtrlSndId;
    /* 0x6BC */ s8 mReverb;
    /* 0x6BD */ u8 field_0x6BD[0x6C0 - 0x6BD];
    /* 0x6C0 */ cXyz field_0x6C0;
    /* 0x6CC */ cXyz field_0x6CC;
    /* 0x6D8 */ s16 field_0x6D8;
    /* 0x6DA */ s16 mEventIdx;
    /* 0x6DC */ char* mpName;
    /* 0x6E0 */ s16 field_0x6E0;
    /* 0x6E2 */ u8 field_0x6E2[0x6E4 - 0x6E2];
    /* 0x6E4 */ u32 mMsgNo;
};  // Size: 0x700

#endif /* D_A_NPC_UK_H */
