#ifndef D_A_NPC_KK1_H
#define D_A_NPC_KK1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Kk1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Kk1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 bckNum;
        /* 0x01 */ s8 btpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    };  // Size: 0x10

    u8 getSWbit() { return m7B5; }

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_KK1_0();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool setBtp(s8, bool);
    bool init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void play_eff_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg_KK1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    void partner_search_sub(void* (*)(void*, void*));
    void partner_search();
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void cut_init_RUN_START(int);
    void cut_move_RUN_START();
    void cut_init_RUN(int);
    void cut_move_RUN();
    void cut_init_CATCH_START(int);
    void cut_move_CATCH_START();
    void cut_init_CATCH_END(int);
    void cut_move_CATCH_END();
    void cut_init_TRN(int);
    void cut_move_TRN();
    void cut_init_BYE_START(int);
    void cut_move_BYE_START();
    void cut_init_BYE(int);
    void cut_move_BYE();
    void cut_init_BYE_CONTINUE(int);
    void cut_move_BYE_CONTINUE();
    void cut_init_BYE_END(int);
    void cut_move_BYE_END();
    void cut_init_PLYER_TRN(int);
    void cut_move_PLYER_TRN();
    void cut_init_OTOBOKE(int);
    void cut_move_OTOBOKE();
    void cut_init_PLYER_MOV(int);
    void cut_move_PLYER_MOV();
    void cut_init_RUNAWAY_START(int);
    void cut_move_RUNAWAY_START();
    void cut_init_RUNAWAY_END(int);
    void cut_move_RUNAWAY_END();
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    bool checkCommandTalk();
    bool set_action(ProcFunc, void*);
    void setStt(signed char);
    void createTama(float);
    void chk_areaIN(float, cXyz);
    bool startEvent_check();
    bool chkHitPlayer();
    void set_pthPoint(unsigned char);
    BOOL event_move(bool);
    void kyoroPos(int);
    void kyorokyoro();
    BOOL chk_attn();
    void setBikon(cXyz);
    void delBikon();
    void setAse();
    void flwAse();
    void delAse();
    BOOL wait_1();
    BOOL walk_1();
    BOOL wait_2();
    void init_CMT_WAI();
    void move_CMT_WAI();
    void init_CMT_TRN();
    void move_CMT_TRN();
    void init_CMT_PCK();
    void move_CMT_PCK();
    BOOL cmmt_1();
    BOOL wait_3();
    BOOL wait_4();
    BOOL talk_1();
    BOOL wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL effcCreateHeap();
    BOOL CreateHeap();

private:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ char mArcName[3];
    /* 0x6D1 */ u8 m6D1[0x6D4 - 0x6D1];
    /* 0x6D4 */ u32 mShadowId;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u8 mBtpFrame;
    /* 0x6ED */ u8 field_0x6ED;
    /* 0x6EE */ s16 mTimer1;
    /* 0x6F0 */ ProcFunc mCurrProcFunc;
    /* 0x6FC */ fpc_ProcID mProcId1;
    /* 0x700 */ fpc_ProcID mProcId2;
    /* 0x704 */ dNpc_PathRun_c mPathRun;
    /* 0x70C */ cXyz field_0x70C;
    /* 0x718 */ csXyz field_0x718;
    /* 0x71E */ csXyz mAngle;
    /* 0x724 */ u8 m724[0x72C - 0x724];
    /* 0x72C */ cXyz mTransformedEyePos;
    /* 0x738 */ cXyz mPlayerEyePos;
    /* 0x744 */ u8 m744[0x750 - 0x744];
    /* 0x750 */ cXyz field_0x750;
    /* 0x75C */ u8 m75C[0x768 - 0x75C];
    /* 0x768 */ f32 mPrevMorfFrame;
    /* 0x76C */ u8 m76C[0x770 - 0x76C];
    /* 0x770 */ s16 mActorAngleY;
    /* 0x772 */ s16 mJointHeadY;
    /* 0x774 */ s16 mJointBackboneY;
    /* 0x776 */ s16 field_0x776;
    /* 0x778 */ BOOL mbSetEyePos;
    /* 0x77C */ s16 mEventIDTbl[8];
    /* 0x78C */ u8 m78C[0x792 - 0x78C];
    /* 0x792 */ s16 field_0x792;
    /* 0x794 */ u8 field_0x794;
    /* 0x795 */ u8 field_0x795;
    /* 0x796 */ u8 mItemNo;
    /* 0x797 */ bool field_0x797;
    /* 0x798 */ bool field_0x798;
    /* 0x799 */ u8 field_0x799;
    /* 0x79A */ u8 field_0x79A;
    /* 0x79B */ bool mbResLoadIsComplete;
    /* 0x79C */ u8 field_0x79C;
    /* 0x79D */ u8 field_0x79D;
    /* 0x79E */ u8 field_0x79E;
    /* 0x79F */ bool field_0x79F;
    /* 0x7A0 */ bool mHasAttention;
    /* 0x7A1 */ bool field_0x7A1;
    /* 0x7A2 */ s16 field_0x7A2;
    /* 0x7A4 */ u8 field_0x7A4;
    /* 0x7A5 */ s8 mActIdx;
    /* 0x7A6 */ u8 field_0x7A6;
    /* 0x7A7 */ u8 mMesgAnimeTag;
    /* 0x7A8 */ u8 field_0x7A8;
    /* 0x7A9 */ u8 field_0x7A9;
    /* 0x7AA */ s8 field_0x7AA;
    /* 0x7AB */ s8 mStatus;
    /* 0x7AC */ s8 field_0x7AC;
    /* 0x7AD */ s8 mLookBackState;
    /* 0x7AE */ s8 mType;
    /* 0x7AF */ s8 mSpecificType;
    /* 0x7B0 */ s8 field_0x7B0;
    /* 0x7B1 */ s8 field_0x7B1;
    /* 0x7B2 */ u8 mbMorfAnimStopped;
    /* 0x7B3 */ u8 field_0x7B3;
    /* 0x7B4 */ u8 field_0x7B4;
    /* 0x7B5 */ u8 m7B5;
    /* 0x7B6 */ u8 m7B6[0x7B8 - 0x7B6];
    /* 0x7B8 */ u8 m7B8;
    /* 0x7B9 */ u8 m7B9[0x7BE - 0x7B9];
    /* 0x7BE */ u8 m7BE;
    /* 0x7BF */ u8 m7BF[0x7C4 - 0x7BF];
    /* 0x7C4 */ u8 m7C4;
    /* 0x7C5 */ u8 m7C5[0x7C8 - 0x7C5];
    /* 0x7C8 */ mDoExt_bpkAnm mBpkAnm;
    /* 0x7DC */ mDoExt_btkAnm mBtkAnm;
    /* 0x7F0 */ mDoExt_bckAnm mBckAnm;
    /* 0x800 */ s16 m800;
    /* 0x802 */ s16 m802;
    /* 0x804 */ s16 m804;
    /* 0x806 */ u8 m806[0x808 - 0x806];
    /* 0x808 */ J3DModel* mpModelEff;
    /* 0x80C */ u8 m80C[0x817 - 0x80C];
    /* 0x817 */ u8 mAnmAtr;
    /* 0x818 */ u8 m818;
    /* 0x819 */ s8 mBtpNum;
    /* 0x81A */ s8 mBckNum;
    /* 0x81B */ u8 m81B;
    /* 0x81C */ s8 mAnmIdx;
    /* 0x81D */ u8 m81D;
    /* 0x81E */ u8 m81E;
    /* 0x81F */ s8 m81F;
    /* 0x820 */ s8 m820;
    /* 0x821 */ u8 m821;
    /* 0x822 */ s8 m822;
    /* 0x823 */ u8 m823;
};  // Size: 0x824

class daNpc_Kk1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x18 */ s16 m18;
        /* 0x1A */ s16 m1A;
        /* 0x1C */ s16 m1C;
        /* 0x1E */ s16 m1E;
        /* 0x20 */ s16 m20;
        /* 0x22 */ s16 m22;
        /* 0x24 */ s16 m24;
        /* 0x26 */ s16 m26;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
        /* 0x30 */ f32 m30;
        /* 0x34 */ f32 m34;
        /* 0x38 */ f32 m38;
        /* 0x3C */ f32 m3C;
        /* 0x40 */ f32 m40;
        /* 0x44 */ f32 m44;
        /* 0x48 */ f32 m48;
        /* 0x4C */ f32 m4C;
        /* 0x50 */ f32 m50;
    };  // Size: 0x54

    daNpc_Kk1_HIO_c();
    virtual ~daNpc_Kk1_HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05[0x08 - 0x05];
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};  // Size: 0x60

#endif /* D_A_NPC_KK1_H */
