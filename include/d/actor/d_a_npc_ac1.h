#ifndef D_A_NPC_AC1_H
#define D_A_NPC_AC1_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class daNpc_Ac1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        /* 0x00 */ s8 anmNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
        /* 0x10 */ BOOL hasArms;
    };

    typedef BOOL (daNpc_Ac1_c::*ActionFunc)(void*);

    void nodeWngControl(J3DNode*, J3DModel*);
    void nodeArmControl(J3DNode*, J3DModel*);
    void nodeAc1Control(J3DNode*, J3DModel*);
    u8 init_AC1_0();
    bool createInit();
    void setMtx(bool);
    int anmNum_toResID(int);
    int wingAnmNum_toResID(int);
    int btpNum_toResID(int);
    bool setBtp(bool, int);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(s8);
    BOOL setAnm_anm(anm_prm_c*);
    bool setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(u32*);
    s32 getBitMask();
    u32 getMsg_AC1_0();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    bool charDecide(int);
    void event_actionInit(int);
    BOOL event_action();
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    BOOL set_action(ActionFunc, void*);
    void setStt(s8);
    BOOL wait_1();
    BOOL talk_1();
    BOOL wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    J3DModelData* create_wng_Anm();
    J3DModelData* create_arm_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

private:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_arm_L_jnt_num;
    /* 0x6CF */ s8 m_arm_R_jnt_num;
    /* 0x6D0 */ s8 m_hnd_R_jnt_num;
    /* 0x6D1 */ u8 pad6D1[0x6D4 - 0x6D1];
    /* 0x6D4 */ J3DModel* mpItemModel;
    /* 0x6D8 */ u32 mShadowID;
    /* 0x6DC */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnim;
    /* 0x6F4 */ u8 mBlinkFrame;
    /* 0x6F5 */ u8 pad6F5[0x6F6 - 0x6F5];
    /* 0x6F6 */ s16 mBlinkTimer;
    /* 0x6F8 */ u8 pad6F8[0x6FC - 0x6F8];
    /* 0x6FC */ mDoExt_McaMorf* mpWingMorf;
    /* 0x700 */ s8 m_wngL1_jnt_num;
    /* 0x701 */ s8 m_wngR1_jnt_num;
    /* 0x702 */ u8 pad702[0x708 - 0x702];
    /* 0x708 */ mDoExt_McaMorf* mpArmMorf;
    /* 0x70C */ s8 m_armL1_jnt_num;
    /* 0x70D */ s8 m_armR1_jnt_num;
    /* 0x70E */ u8 pad70E[0x710 - 0x70E];
    /* 0x710 */ ActionFunc mCurrActionFunc;
    /* 0x71C */ Mtx mLeftArmMtx;
    /* 0x74C */ Mtx mRightArmMtx;
    /* 0x77C */ dNpc_PathRun_c mPathRun;
    /* 0x784 */ dNpc_EventCut_c mEventCut;
    /* 0x7F0 */ u8 pad7F0[0x7F4 - 0x7F0];
    /* 0x7F4 */ cXyz mInitPos;
    /* 0x800 */ csXyz mInitAngle;
    /* 0x806 */ u8 pad806[0x808 - 0x806];
    /* 0x808 */ cXyz mEyePos;
    /* 0x814 */ cXyz m814;
    /* 0x820 */ u8 pad820[0x82C - 0x820];
    /* 0x82C */ f32 mFrame;
    /* 0x830 */ u8 pad830[0x844 - 0x830];
    /* 0x844 */ s16 m844;
    /* 0x846 */ s16 m846;
    /* 0x848 */ s16 m848;
    /* 0x84A */ u8 pad84A[0x84C - 0x84A];
    /* 0x84C */ s16 m84C;
    /* 0x84E */ u8 pad84E[0x852 - 0x84E];
    /* 0x852 */ s16 m852;
    /* 0x854 */ s16 m854;
    /* 0x856 */ s16 m856;
    /* 0x858 */ s8 mbMorfAnimStopped;
    /* 0x859 */ s8 m859;
    /* 0x85A */ u8 pad85A[0x85B - 0x85A];
    /* 0x85B */ u8 m85B;
    /* 0x85C */ u8 pad85C[0x85D - 0x85C];
    /* 0x85D */ u8 m85D;
    /* 0x85E */ u8 mbHasArms;
    /* 0x85F */ u8 m85F;
    /* 0x860 */ u8 m860;
    /* 0x861 */ u8 m861;
    /* 0x862 */ u8 pad862[0x863 - 0x862];
    /* 0x863 */ u8 m863;
    /* 0x864 */ u8 m864;
    /* 0x865 */ u8 pad865[0x868 - 0x865];
    /* 0x868 */ u8 m868;
    /* 0x869 */ u8 m869;
    /* 0x86A */ u8 m86A;
    /* 0x86B */ u8 mbInDemo;
    /* 0x86C */ u8 m86C;
    /* 0x86D */ u8 m86D;
    /* 0x86E */ u8 mAnmAtr;
    /* 0x86F */ u8 mAnmTag;
    /* 0x870 */ u8 mBtpNum;
    /* 0x871 */ u8 mAnmNum;
    /* 0x872 */ u8 pad872[0x874 - 0x872];
    /* 0x874 */ u8 m874;
    /* 0x875 */ u8 mStatus;
    /* 0x876 */ u8 mPrevStatus;
    /* 0x877 */ u8 mLookBackState;
    /* 0x878 */ u8 m878;
    /* 0x879 */ u8 m879;
    /* 0x87A */ u8 mActionIndex;
    /* 0x87B */ u8 m87B;
};  // Size: 0x87C

class daNpc_Ac1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x12 */ s16 mMaxHeadTurnVel;
        /* 0x14 */ f32 mAttnYOffset;
        /* 0x18 */ s16 m18;
        /* 0x1A */ s16 mMaxAttnAngleY;
        /* 0x1C */ s16 m1C;
        /* 0x1E */ s16 m1E;
        /* 0x20 */ f32 mMaxAttnDistXZ;
        /* 0x24 */ f32 m24;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
    };  // Size: 0x30

    daNpc_Ac1_HIO_c();
    virtual ~daNpc_Ac1_HIO_c() {};
    void genMessage(JORMContext* ctx) {};

public:
    /* 0x04 */ s8 m4;
    /* 0x08 */ s32 m8;
    /* 0x0C */ hio_prm_c hio_prm;
};  // Size: 0x3C

#endif /* D_A_NPC_AC1_H */
