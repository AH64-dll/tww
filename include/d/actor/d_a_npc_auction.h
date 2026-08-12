#ifndef D_A_NPC_AUCTION_H
#define D_A_NPC_AUCTION_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

struct sAnmDat {
    /* 0x00 */ u8 mAnmNo;
    /* 0x01 */ u8 mMorf;
    /* 0x02 */ u8 mCount;
};  // Size: 0x3

class daNpc_Auction2_HIO_c : public dNpc_HIO_c {
public:
    daNpc_Auction2_HIO_c() {}
    daNpc_Auction2_HIO_c(f32 i_m04, s16 i_max_head_x, s16 i_max_backbone_x, s16 i_max_head_y,
                         s16 i_max_backbone_y, s16 i_min_head_x, s16 i_min_backbone_x,
                         s16 i_min_head_y, s16 i_min_backbone_y, s16 i_max_turn_step,
                         s16 i_max_head_turn_vel, f32 i_attn_y_offset, s16 i_max_attn_angle_y,
                         u8 i_22, f32 i_max_attn_dist_xz, f32 i_28, f32 i_2C, f32 i_30) {
        m04 = i_m04;
        mMaxHeadX = i_max_head_x;
        mMaxBackboneX = i_max_backbone_x;
        mMaxHeadY = i_max_head_y;
        mMaxBackboneY = i_max_backbone_y;
        mMinHeadX = i_min_head_x;
        mMinBackboneX = i_min_backbone_x;
        mMinHeadY = i_min_head_y;
        mMinBackboneY = i_min_backbone_y;
        mMaxTurnStep = i_max_turn_step;
        mMaxHeadTurnVel = i_max_head_turn_vel;
        mAttnYOffset = i_attn_y_offset;
        mMaxAttnAngleY = i_max_attn_angle_y;
        m22 = i_22;
        mMaxAttnDistXZ = i_max_attn_dist_xz;
        m28 = i_28;
        m2C = i_2C;
        m30 = i_30;
    }
    virtual ~daNpc_Auction2_HIO_c() {}

    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
};  // Size: 0x34

class daNpcAuction_c : public fopNpc_npc_c {
public:
    typedef void (daNpcAuction_c::*ActionFunc)();

    daNpcAuction_c();

    static const char m_arcname[4];

    request_of_phase_process_class* getPhaseP() { return &mPhs; }
    f32 getPiconOfsY() { return mPiconOfsY; }
    void setAction(ActionFunc i_action) { mAction = i_action; }
    void setBmtNo(int i_bmt_no) { mBmtNo = i_bmt_no; }
    void setBtpNo(int i_btp_no) { mBtpNo = i_btp_no; }
    void setMdlNo(unsigned char i_mdl_no) { mBtpNo = i_mdl_no; }
    void setNpcNo(unsigned char i_npc_no) { mNpcNo = i_npc_no; }

    void createHeap();
    void createInit();
    void wait_action_init();
    void wait_action();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMainInit();
    void eventMain();
    void eventMesSetInit(int);
    void eventMesSet();
    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setAnmFromMsgTag();
    u8 getPrmNpcNo();
    void setMtx();
    void lookBack();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnm2(unsigned char, int, float);
    void setAnmTbl(sAnmDat*);
    BOOL isExecute();
    int getRand(int);
    void clrEmitter();

public:
    /* 0x6C4 */ ActionFunc mAction;
    /* 0x6D0 */ request_of_phase_process_class mPhsArcname;
    /* 0x6D8 */ request_of_phase_process_class mPhs;
    /* 0x6E0 */ J3DModel* mHeadModel;
    /* 0x6E4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6E8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6FC */ u32 mShadowID;
    /* 0x700 */ JPABaseEmitter* mEmitter;
    /* 0x704 */ u8 m704[0x71C - 0x704];
    /* 0x71C */ sAnmDat* mpAnmDat;
    /* 0x720 */ f32 m720;
    /* 0x724 */ f32 mPiconOfsY;
    /* 0x728 */ u32 m728;
    /* 0x72C */ s32 mBtpNo;
    /* 0x730 */ s32 mBmtNo;
    /* 0x734 */ s16 m734;
    /* 0x736 */ s16 mAngleY;
    /* 0x738 */ s16 mEventIdx;
    /* 0x73A */ s16 mSoundTimer;
    /* 0x73C */ u8 m73C;
    /* 0x73D */ u8 m73D;
    /* 0x73E */ u8 m73E;
    /* 0x73F */ u8 m73F;
    /* 0x740 */ u8 mNpcNo;
    /* 0x741 */ u8 mDataNo;
    /* 0x742 */ u8 m742;
    /* 0x743 */ u8 m743;
    /* 0x744 */ u8 m744;
    /* 0x745 */ u8 m745;
    /* 0x746 */ u8 mAnmNo;
    /* 0x747 */ u8 m747;
    /* 0x748 */ u8 m748;
    /* 0x749 */ u8 m749;
    /* 0x74A */ u8 mActIdx;
    /* 0x74B */ u8 m74B;
};  // Size: 0x74C

#endif /* D_A_NPC_AUCTION_H */
