#ifndef D_A_NPC_MN_H
#define D_A_NPC_MN_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class J3DNode;

struct sMnAnmDat {
    /* 0x00 */ u8 mAnmNum;
    /* 0x01 */ u8 mBtpNum;
    /* 0x02 */ s8 mAnmCnt;
};

struct sMnDat {
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

class daNpcMn_c : public fopNpc_npc_c {
public:
    static const char m_arcname[];

    typedef s32 (daNpcMn_c::*InitFunc_t)();
    typedef void (daNpcMn_c::*MoveFunc_t)();

    enum Prm_e {
        PRM_RAIL_ID_W = 0x8,
        PRM_RAIL_ID_S = 0x18,

        PRM_SW_BIT_W = 0x8,
        PRM_SW_BIT_S = 0x8,

        PRM_SW_BIT2_W = 0x8,
        PRM_SW_BIT2_S = 0x10,
    };

    void getNpcNo() {}
    request_of_phase_process_class* getPhaseP() { return &mPhs; }
    void getPosFlag() {}
    void setResFlag(unsigned char) {}

    daNpcMn_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    BOOL executeCommon();
    void executeSetMode(unsigned char);
    s32 executeWaitInit();
    void executeWait();
    s32 executeTalkInit();
    void executeTalk();
    s32 executeTalk3Init();
    void executeTalk3();
    s32 executeWalkInit();
    void executeWalk();
    s32 executeTurnInit();
    void executeTurn();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    s32 eventMesSet();
    void eventGetItemInit();
    void eventWaitInit(int);
    s32 eventWait(int);
    void eventSwOnInit(int);
    s32 eventSwOn();
    void eventHatchInit();
    s32 eventHatch();
    void eventBikkuriInit(int);
    s32 eventBikkuri();
    void eventTurnInit();
    s32 eventTurn(int);
    void eventWalkInit();
    s32 eventWalk();
    void eventLookInit();
    s32 eventLook();
    void eventJumpInit(int);
    s32 eventJump();
    u16 talk2(int);
    u8 talk3(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    u32 getMsg3();
    void chkMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    int getPrmNpcNo();
    u8 getPrmRailID();
    u8 getPrmSwitchBit();
    u8 getPrmSwitchBit2();
    void setMtx();
    void chkAttention();
    void lookBack();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    s32 setAnmTbl(sMnAnmDat*);
    s32 XyCheckCB(int);
    int getRand(int);
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    s32 chkEndEvent();
    u8 chkPosNo();
    u8 getPosNo();
    BOOL isChangePos(unsigned char);

public:
    /* 0x6C4 */ u8 field_0x6C4[0x724 - 0x6C4];
    /* 0x724 */ request_of_phase_process_class mPhs;
    /* 0x72C */ request_of_phase_process_class mPhs2;
    /* 0x734 */ J3DModel* m734;
    /* 0x738 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x73C */ mDoExt_btpAnm mBtpAnm;
    /* 0x750 */ u32 mShadowId;
    /* 0x754 */ dNpc_PathRun_c mPathRun;
    /* 0x75C */ u8 field_0x75C[0x768 - 0x75C];
    /* 0x768 */ f32 mLookAtX;
    /* 0x76C */ f32 mLookAtY;
    /* 0x770 */ f32 mLookAtZ;
    /* 0x774 */ sMnAnmDat* mpAnmDat;
    /* 0x778 */ u32* mpMsgTbl;
    /* 0x77C */ f32 m77C;
    /* 0x780 */ f32 m780;
    /* 0x784 */ f32 mAttnDist;
    /* 0x788 */ f32 m788;
    /* 0x78C */ u32 mItemId;
    /* 0x790 */ u32 m790;
    /* 0x794 */ u8 m794;
    /* 0x795 */ u8 field_0x795[0x796 - 0x795];
    /* 0x796 */ s16 mEventIdx;
    /* 0x798 */ s16 mTimer;
    /* 0x79A */ s16 mLookTimer;
    /* 0x79C */ s16 mEvTimer;
    /* 0x79E */ s16 mTurnSpeed;
    /* 0x7A0 */ s16 m7A0;
    /* 0x7A2 */ u16 mMsgStatus;
    /* 0x7A4 */ s16 m7A4;
    /* 0x7A6 */ u8 field_0x7A6[0x7A8 - 0x7A6];
    /* 0x7A8 */ s16 mTexTimer;
    /* 0x7AA */ s16 m7AA;
    /* 0x7AC */ s16 mAngAccel;
    /* 0x7AE */ s16 m7AE;
    /* 0x7B0 */ u8 mMode;
    /* 0x7B1 */ u8 mAttnFlag;
    /* 0x7B2 */ u8 mOrderMode;
    /* 0x7B3 */ u8 mTexPatternNo;
    /* 0x7B4 */ u8 m7B4;
    /* 0x7B5 */ u8 m7B5;
    /* 0x7B6 */ u8 mNpcNo;
    /* 0x7B7 */ u8 mSwFlag;
    /* 0x7B8 */ u8 mAnmNo;
    /* 0x7B9 */ u8 m7B9;
    /* 0x7BA */ u8 mAnmCnt;
    /* 0x7BB */ u8 mCutActIdx;
    /* 0x7BC */ u8 m7BC;
    /* 0x7BD */ u8 mLookMode;
    /* 0x7BE */ u8 m7BE;
    /* 0x7BF */ u8 m7BF;
    /* 0x7C0 */ u8 m7C0;
    /* 0x7C1 */ u8 mPosNo;
    /* 0x7C2 */ u8 m7C2;
    /* 0x7C3 */ u8 m7C3;
    /* 0x7C4 */ u8 m7C4;
    /* 0x7C5 */ u8 m7C5;
};  // Size: 0x7C8

#endif /* D_A_NPC_MN_H */
