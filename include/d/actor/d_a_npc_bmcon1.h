#ifndef D_A_NPC_BMCON1_H
#define D_A_NPC_BMCON1_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class J3DModel;

struct sBmconAnmDat {
    /* 0x00 */ u8 mAnmNo;
    /* 0x01 */ u8 mMorf;
    /* 0x02 */ s8 mCount;
};

struct NpcDatStruct {
    /* 0x00 */ s16 mMax_head_x;
    /* 0x02 */ s16 mMax_head_y;
    /* 0x04 */ s16 mMax_backbone_x;
    /* 0x06 */ s16 mMax_backbone_y;
    /* 0x08 */ s16 mMin_head_x;
    /* 0x0A */ s16 mMin_head_y;
    /* 0x0C */ s16 mMin_backbone_x;
    /* 0x0E */ s16 mMin_backbone_y;
    /* 0x10 */ s16 mMax_turn_step;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ s16 field_0x2C;
    /* 0x2E */ s16 field_0x2E;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ s8 field_0x4A;
    /* 0x4B */ s8 field_0x4B;
}; // Size: 0x4c

class daNpcBmcon_c : public fopNpc_npc_c {
public:
    enum Prm_e {
        PRM_NPC_NO_W = 0x0,
        PRM_NPC_NO_S = 0x0,

        PRM_RAIL_ID_W = 0x8,
        PRM_RAIL_ID_S = 0x10,
    };

    typedef s32 (daNpcBmcon_c::*InitFunc_t)();
    typedef void (daNpcBmcon_c::*MoveFunc_t)();

    u8 getNpcNo() { return mNpcNo; }
    request_of_phase_process_class* getPhaseP() { return &mPhs; }
    s8 get_nec_jnt_num() { return m_nec_jnt_num; }
    s8 get_arm_L_jnt_num() { return m_arm_L_jnt_num; }
    s8 get_arm_R_jnt_num() { return m_arm_R_jnt_num; }
    void setResFlag(u8 flag) { mResFlag = flag; }

    daNpcBmcon_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    u8 executeCommon();
    void executeSetMode(u8);
    s32 executeWaitInit();
    void executeWait();
    s32 executeTalkInit();
    void executeTalk();
    s32 executeWalkInit();
    void executeWalk();
    s32 executeTurnInit();
    void executeTurn();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    bool eventMesSet();
    void eventGetItemInit();
    u16 talk2(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void chkMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    u8 getPrmNpcNo();
    u8 getPrmRailID();
    void setMtx();
    void chkAttention();
    void lookBack();
    void playAnm();
    void setAnm(u8, int, f32);
    bool setAnmTbl(sBmconAnmDat*);
    s16 XyCheckCB(int);
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    cXyz calcFlyDist();
    s16 getFlyDistMax();
    void setFlyDistMax(s16);
    s16 getFlyDistNow();
    void setFlyDistNow(s16);
    BOOL chkEndEvent();
    BOOL isClear();
    void nodeArmControl(J3DNode*, J3DModel*);

    static const char m_arcname[];

public:
    /* 0x6C4 */ Mtx mLeftArmMtx;
    /* 0x6F4 */ Mtx mRightArmMtx;

private:
    /* 0x724 */ request_of_phase_process_class mPhs;
    /* 0x72C */ request_of_phase_process_class mPhase;
    /* 0x734 */ mDoExt_McaMorf* mpArmMorf;
    /* 0x738 */ J3DModel* mpHeadModel;
    /* 0x73C */ u32 field_0x73C;
    /* 0x740 */ mDoExt_btpAnm mBtpAnm;
    /* 0x754 */ u32 mShadowID;
    /* 0x758 */ dNpc_PathRun_c mPathRun;
    /* 0x760 */ u8 field_0x760[0x76C - 0x760];
    /* 0x76C */ cXyz mLookAtPos;
    /* 0x778 */ sBmconAnmDat* mpAnmDat;
    /* 0x77C */ u32* mpMsgTbl;
    /* 0x780 */ f32 m780;
    /* 0x784 */ f32 m784;
    /* 0x788 */ f32 mAttnDist;
    /* 0x78C */ u32 mItemNo;
    /* 0x790 */ bool m790;
    /* 0x791 */ u8 field_0x791;
    /* 0x792 */ s16 mEventIdx1;
    /* 0x794 */ s16 mEventIdx2;
    /* 0x796 */ s16 m796;
    /* 0x798 */ s16 m798;
    /* 0x79A */ s16 mAttnAngle;
    /* 0x79C */ s16 m79C;
    /* 0x79E */ u16 mMsgStatus;
    /* 0x7A0 */ s16 m7A0;
    /* 0x7A2 */ s16 mFlyDistNow;
    /* 0x7A4 */ s16 m7A4;
    /* 0x7A6 */ s16 m7A6;
    /* 0x7A8 */ s16 m7A8;
    /* 0x7AA */ s16 m7AA;
    /* 0x7AC */ u8 m7AC;
    /* 0x7AD */ u8 m7AD;
    /* 0x7AE */ u8 m7AE;
    /* 0x7AF */ u8 field_0x7AF;
    /* 0x7B0 */ s8 m_nec_jnt_num;
    /* 0x7B1 */ s8 m_arm_L_jnt_num;
    /* 0x7B2 */ s8 m_arm_R_jnt_num;
    /* 0x7B3 */ s8 m_armL1_jnt_num;
    /* 0x7B4 */ s8 m_armR1_jnt_num;
    /* 0x7B5 */ u8 mMode;
    /* 0x7B6 */ u8 mResFlag;
    /* 0x7B7 */ u8 mNpcNo;
    /* 0x7B8 */ u8 mMsgFlags;
    /* 0x7B9 */ u8 mBckNo;
    /* 0x7BA */ u8 mAnmFlag;
    /* 0x7BB */ s8 mAnmTimer;
    /* 0x7BC */ s8 mActIdx;
    /* 0x7BD */ u8 field_0x7BD;
    /* 0x7BE */ s8 m7BE;
    /* 0x7BF */ u8 m7BF;
    /* 0x7C0 */ u8 m7C0;
    /* 0x7C1 */ u8 m7C1;
    /* 0x7C2 */ u8 m7C2;
    /* 0x7C3 */ u8 m7C3;
    /* 0x7C4 */ u8 mFlyState;
    /* 0x7C5 */ u8 mSndFlags;
    /* 0x7C6 */ u8 field_0x7C6[2];
};  // Size: 0x7C8

#endif /* D_A_NPC_BMCON1_H */
