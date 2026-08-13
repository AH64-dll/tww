#ifndef D_A_NPC_BJ1_H
#define D_A_NPC_BJ1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Bj1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Bj1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };

    void nodeBj1Control(J3DNode*, J3DModel*);
    void nodePrpControl(J3DNode*, J3DModel*);
    bool init_BJ4_0();
    bool init_BJ6_0();
    bool init_BJ7_0();
    bool init_BJX_0();
    bool init_BJX_1();
    BOOL createInit();
    void setMtx_anmProc();
    void setMtx(bool);
    int anmNum_toResID(int);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int);
    bool setAnm();
    BOOL setAnm_prp(s8);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_drct(f32);
    bool chk_partsNotMove();
    void lookBack();
    bool getMaskInf(u8*);
    bool chkReg(u16);
    void setReg(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_BJ1_0();
    u32 getMsg_BJ2_0();
    u32 getMsg_BJ3_0();
    u32 getMsg_BJ4_0();
    u32 getMsg_BJ5_0();
    u32 getMsg_BJ6_0();
    u32 getMsg_BJ7_0();
    u32 getMsg_BJ8_0();
    u32 getMsg_BJ9_0();
    u32 getMsg_Corog();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(fpc_ProcID);
    bool partner_srch_sub(fpcLyIt_JudgeFunc);
    void partner_srch();
    void setCollision_SP_();
    void set_pthPoint(u8);
    void bj_clcFlySpd();
    void bj_movPass(bool);
    void bj_flyMove();
    void bj_clcMovSpd();
    void bj_nMove();
    void setPrtcl_drugPot_1();
    void setPrtcl_drugPot_2();
    void delPrtcl_drugPot();
    void setPrtcl_danceLR();
    void flwPrtcl_danceLR();
    void delPrtcl_danceLR();
    void setPrtcl_peraProOpen();
    void createSeed();
    void deleteSeed();
    bool charDecide(int);
    void eInit_setLocFlag(int*);
    void eInit_setShapeAngleY(int*, s16);
    void eInit_setEvTimer(int*);
    void eInit_calcRelativPos(cXyz*, int*);
    f32 eInit_prmFloat(f32*, f32);
    void eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*);
    void eInit_PLYER_MOV_1_();
    void eInit_MOV_(f32*, f32*, f32*, int*);
    void eInit_JMP_(f32*, f32*);
    void eInit_CHG_PTH_(int*, int*);
    void eInit_END_MOV_();
    void eInit_SET_TNE_();
    void eInit_DEL_TNE_();
    void eInit_SET_ANM_(int*, f32*);
    void event_actionInit(int);
    bool eMove_ATTENTION_();
    bool eMove_MOV_();
    BOOL eMove_JMP_();
    bool eMove_SET_TNE_();
    bool eMove_PTH_MOV_();
    void event_action();
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
    void setStt(s8);
    BOOL wait_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL wait_4();
    void flyMov();
    void fall01();
    BOOL talk_1();
    BOOL walk_1();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    BOOL wait_action3(void*);
    BOOL wait_action4(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_prp_Anm();
    void create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_armL2_jnt_num;
    /* 0x6CF */ s8 m_armR2_jnt_num;
    /* 0x6D0 */ J3DModel* mpMdl;
    /* 0x6D4 */ J3DModel* mpItmMdl;
    /* 0x6D8 */ J3DModel* mpArmMdl;
    /* 0x6DC */ s8 m_itm_jnt_num;
    /* 0x6DD */ u8 field_0x6DD[0x6E0 - 0x6DD];
    /* 0x6E0 */ u32 field_0x6E0;
    /* 0x6E4 */ mDoExt_McaMorf* mpPrpMorf;
    /* 0x6E8 */ s8 m_prp_jnt_num_1;
    /* 0x6E9 */ s8 m_prp_jnt_num_2;
    /* 0x6EA */ u8 field_0x6EA[0x6F0 - 0x6EA];
    /* 0x6F0 */ s16 mPrpAngleY;
    /* 0x6F2 */ s16 field_0x6F2;
    /* 0x6F4 */ u8 field_0x6F4[0x6F8 - 0x6F4];
    /* 0x6F8 */ ProcFunc mCurrProcFunc;
    /* 0x704 */ Mtx mPrpMtx;
    /* 0x734 */ dNpc_PathRun_c mPathRun;
    /* 0x73C */ dNpc_EventCut_c mEventCut;
    /* 0x7A8 */ fpc_ProcID mPartnerProcID;
    /* 0x7AC */ cXyz mInitPosSave;
    /* 0x7B8 */ csXyz mInitAngleSave;
    /* 0x7C0 */ cXyz mTransformedEyePos;
    /* 0x7CC */ cXyz mHomePos;
    /* 0x7D8 */ cXyz mPathPoint;
    /* 0x7E4 */ cXyz mScaleBack;
    /* 0x7F0 */ cXyz mScaleHead;
    /* 0x7FC */ cXyz mScaleArm;
    /* 0x808 */ f32 mPrevMorfFrame;
    /* 0x80C */ f32 m80C;
    /* 0x810 */ f32 m810;
    /* 0x814 */ f32 m814;
    /* 0x818 */ f32 m818;
    /* 0x81C */ f32 m81C;
    /* 0x820 */ s16 m820;
    /* 0x822 */ s16 m822;
    /* 0x824 */ s16 mActorAngleY;
    /* 0x826 */ s16 mEventIdTable[3];
    /* 0x82C */ s16 m82C;
    /* 0x82E */ s16 m82E;
    /* 0x830 */ s16 m830;
    /* 0x832 */ s16 mEvTimer;
    /* 0x834 */ s16 m834;
    /* 0x836 */ s16 m836;
    /* 0x838 */ s16 m838;
    /* 0x83A */ s16 m83A;
    /* 0x83C */ s8 m83C;
    /* 0x83D */ u8 m83D;
    /* 0x83E */ u8 m83E;
    /* 0x83F */ u8 mPathNo;
    /* 0x840 */ s8 m840;
    /* 0x841 */ s8 m841;
    /* 0x842 */ u8 m842;
    /* 0x843 */ u8 m843;
    /* 0x844 */ u8 m844;
    /* 0x845 */ u8 m845;
    /* 0x846 */ bool m846;
    /* 0x847 */ s8 m847;
    /* 0x848 */ u8 m848;
    /* 0x849 */ s8 m849;
    /* 0x84A */ s8 m84A;
    /* 0x84B */ u8 m84B;
    /* 0x84C */ u8 m84C;
    /* 0x84D */ u8 m84D;
    /* 0x84E */ u8 m84E;
    /* 0x84F */ u8 m84F;
    /* 0x850 */ s32 m850;
    /* 0x854 */ s8 m854;
    /* 0x855 */ s8 m855;
    /* 0x856 */ bool m856;
    /* 0x857 */ u8 mMesgAnimeTagInfo;
    /* 0x858 */ s8 m858;
    /* 0x859 */ s8 m859;
    /* 0x85A */ s16 m85A;
    /* 0x85C */ s16 m85C;
    /* 0x85E */ u8 m85E;
    /* 0x85F */ u8 m85F;
    /* 0x860 */ f32 mFlySpd;
    /* 0x864 */ f32 m864;
    /* 0x868 */ f32 m868;
    /* 0x86C */ f32 m86C;
    /* 0x870 */ f32 m870;
    /* 0x874 */ f32 m874;
    /* 0x878 */ s32 m878;
    /* 0x87C */ s32 m87C;
    /* 0x880 */ s32 m880;
    /* 0x884 */ s32 m884;
    /* 0x888 */ s32 m888;
    /* 0x88C */ s32 m88C;
    /* 0x890 */ s32 m890;
    /* 0x894 */ s16 m894;
    /* 0x896 */ u8 field_0x896[0x8A8 - 0x896];
    /* 0x8A8 */ s8 m8A8;
    /* 0x8A9 */ s8 m8A9;
    /* 0x8AA */ s8 m8AA;
    /* 0x8AB */ u8 m8AB;
    /* 0x8AC */ u8 m8AC;
    /* 0x8AD */ u8 m8AD;
    /* 0x8AE */ u8 m8AE;
    /* 0x8AF */ s8 m8AF;
    /* 0x8B0 */ u8 mStatus;
    /* 0x8B1 */ s8 mPrevStatus;
    /* 0x8B2 */ s8 m8B2;
    /* 0x8B3 */ s8 m8B3;
    /* 0x8B4 */ s8 mType;
    /* 0x8B5 */ s8 mSpecificType;
    /* 0x8B6 */ s8 mActionIndex;
    /* 0x8B7 */ s8 m8B7;
};  // Size: 0x8B8

class daNpc_Bj1_childHIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 field_0x00;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ s16 field_0x04;
        /* 0x06 */ s16 field_0x06;
        /* 0x08 */ s16 field_0x08;
        /* 0x0A */ s16 field_0x0A;
        /* 0x0C */ s16 field_0x0C;
        /* 0x0E */ s16 field_0x0E;
        /* 0x10 */ s16 field_0x10;
        /* 0x12 */ s16 field_0x12;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1C;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ f32 field_0x2C;
        /* 0x30 */ f32 field_0x30;
        /* 0x34 */ f32 field_0x34;
        /* 0x38 */ f32 field_0x38;
        /* 0x3C */ f32 field_0x3C;
        /* 0x40 */ f32 field_0x40;
        /* 0x44 */ f32 field_0x44;
        /* 0x48 */ f32 field_0x48;
        /* 0x4C */ f32 field_0x4C;
        /* 0x50 */ f32 field_0x50;
        /* 0x54 */ f32 field_0x54;
        /* 0x58 */ f32 field_0x58;
        /* 0x5C */ f32 field_0x5C;
        /* 0x60 */ f32 field_0x60;
    };  // Size: 0x64

    daNpc_Bj1_childHIO_c();

public:
    /* 0x04 */ hio_prm_c mPrm;
    /* 0x68 */ s32 mNo;
};  // Size: 0x6C

class daNpc_Bj1_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_Bj1_HIO_c();
    virtual ~daNpc_Bj1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ daNpc_Bj1_childHIO_c mChild[9];
};  // Size: 0x3D8

#endif /* D_A_NPC_BJ1_H */
