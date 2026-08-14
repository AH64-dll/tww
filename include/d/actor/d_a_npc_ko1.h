#ifndef D_A_NPC_KO1_H
#define D_A_NPC_KO1_H

#include "d/d_npc.h"
#include "d/d_particle.h"

class J3DNode;

class daNpc_Ko1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Ko1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };

    void nodeHedControl(J3DNode*, J3DModel*);
    void nodeBlnControl(J3DNode*, J3DModel*);
    void nodeKo1Control(J3DNode*, J3DModel*);
    BOOL init_HNA_0();
    BOOL init_HNA_1();
    BOOL init_HNA_2();
    BOOL init_HNA_3();
    BOOL init_HNA_4();
    BOOL init_BOU_0();
    BOOL init_BOU_1();
    BOOL init_BOU_2();
    BOOL init_BOU_3();
    BOOL createInit();
    void setMtx(bool);
    int anmNum_toResID(int);
    int headAnmNum_toResID(int);
    int balloon_anmNum_toResID(int);
    int btpNum_toResID(int);
    void setBtp(bool, int);
    void iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(s8);
    void setAnm_anm(anm_prm_c*);
    void set_balloonAnm_anm(anm_prm_c*);
    void set_balloonAnm_NUM(int);
    void setAnm_NUM(int, int);
    void setAnm();
    void setPlaySpd(float);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    BOOL chk_talk();
    BOOL chk_manzai_1();
    BOOL chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(u32*);
    u32 getMsg_HNA_0();
    u32 getMsg_HNA_1();
    u32 getMsg_HNA_2();
    u32 getMsg_HNA_3();
    u32 getMsg_BOU_0();
    u32 getMsg_BOU_1();
    u8 bitCount(u8);
    u32 getMsg_BOU_2();
    u32 getMsg();
    BOOL chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(unsigned int);
    void* partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    BOOL check_landOn();
    void ko_setPthPos();
    void set_tgtPos(cXyz);
    BOOL ko_movPass();
    BOOL ko_clcMovSpd();
    BOOL ko_clcSwmSpd();
    void ko_nMove();
    BOOL chk_routeAngle(cXyz&, s16*);
    BOOL routeWallCheck(cXyz&, cXyz&, s16*);
    BOOL chk_ForwardGroundY(s16);
    BOOL chk_wallJump(s16);
    BOOL routeCheck(f32, s16*);
    BOOL chk_start_swim();
    fopAc_ac_c* get_crsActorID();
    BOOL chk_areaIn(f32, cXyz);
    void setPrtcl_Hamon(f32, f32);
    void setPrtcl_HanaPachi();
    BOOL charDecide(int);
    void event_actionInit(int);
    void event_action();
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
    void clrSpd();
    void setStt(s8);
    BOOL wait_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL wait_4();
    BOOL wait_5(s8);
    BOOL wait_6();
    BOOL wait_7();
    BOOL wait_9();
    BOOL wait_a();
    BOOL walk_1();
    BOOL walk_2(s8, s8);
    BOOL walk_3();
    BOOL swim_1();
    BOOL swim_2();
    BOOL attk_1();
    BOOL attk_2(s8, s8);
    BOOL attk_3();
    BOOL down_1(s8);
    BOOL talk_1();
    BOOL talk_2();
    BOOL manzai();
    BOOL neru_1();
    BOOL neru_2();
    BOOL hana_action1(void*);
    BOOL hana_action2(void*);
    BOOL hana_action3(void*);
    BOOL hana_action4(void*);
    BOOL hana_action5(void*);
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    BOOL wait_action3(void*);
    BOOL wait_action4(void*);
    BOOL demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_hed_Anm();
    void create_bln_Anm();
    void create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 mJntNo1;
    /* 0x6CD */ s8 mJntNo2;
    /* 0x6CE */ s8 m6CE;
    /* 0x6CF */ s8 mHedJntNo;
    /* 0x6D0 */ s8 mBlnJntNo;
    /* 0x6D1 */ s8 m6D1;
    /* 0x6D4 */ Mtx mMtx;
    /* 0x704 */ mDoExt_McaMorf* mpBlnMorf;
    /* 0x708 */ mDoExt_McaMorf* mpItmMorf;
    /* 0x70C */ u32 m70C;
    /* 0x710 */ mDoExt_McaMorf* mpHedMorf;
    /* 0x714 */ J3DAnmTexPattern* mpBtpAnm;
    /* 0x718 */ mDoExt_btpAnm mBtpAnm;
    /* 0x72C */ u8 mBtpFrame;
    /* 0x72E */ s16 mBtpTimer;
    /* 0x730 */ ProcFunc mProcFunc;
    /* 0x73C */ dNpc_PathRun_c mPath;
    /* 0x744 */ u32 m744;
    /* 0x748 */ dNpc_EventCut_c mEventCut;
    /* 0x7B4 */ fpc_ProcID m7B4[2];
    /* 0x7BC */ u8 mPartnerCnt;
    /* 0x7C0 */ fpc_ProcID m7C0;
    /* 0x7C4 */ cXyz m7C4;
    /* 0x7D0 */ s16 m7D0;
    /* 0x7D2 */ s16 m7D2;
    /* 0x7D4 */ s16 m7D4;
    /* 0x7D6 */ s16 m7D6;
    /* 0x7D8 */ s16 m7D8;
    /* 0x7DA */ s16 m7DA;
    /* 0x7DC */ cXyz m7DC;
    /* 0x7E8 */ cXyz m7E8;
    /* 0x7F4 */ cXyz m7F4;
    /* 0x800 */ u8 field_0x800[0xC];
    /* 0x80C */ cXyz m80C;
    /* 0x818 */ cXyz m818;
    /* 0x824 */ f32 m824;
    /* 0x828 */ f32 m828;
    /* 0x82C */ f32 m82C;
    /* 0x830 */ f32 m830;
    /* 0x834 */ f32 m834;
    /* 0x838 */ f32 m838;
    /* 0x83C */ f32 m83C;
    /* 0x840 */ u8 field_0x840[8];
    /* 0x848 */ u32 m848;
    /* 0x84C */ u8 field_0x84c[2];
    /* 0x84E */ s16 m84E;
    /* 0x850 */ s16 m850;
    /* 0x852 */ s16 m852;
    /* 0x854 */ s16 m854;
    /* 0x856 */ s16 m856;
    /* 0x858 */ s16 m858;
    /* 0x85A */ s16 m85A;
    /* 0x85C */ u8 field_0x85c[2];
    /* 0x85E */ u8 m85E;
    /* 0x85F */ u8 m85F;
    /* 0x860 */ u8 m860;
    /* 0x861 */ u8 m861;
    /* 0x862 */ u8 m862;
    /* 0x863 */ u8 m863;
    /* 0x864 */ u8 m864;
    /* 0x865 */ u8 m865;
    /* 0x866 */ u8 m866;
    /* 0x867 */ u8 m867;
    /* 0x868 */ u8 m868;
    /* 0x869 */ u8 m869;
    /* 0x86A */ u8 m86A;
    /* 0x86B */ u8 m86B;
    /* 0x86C */ u8 m86C;
    /* 0x86D */ u8 m86D;
    /* 0x86E */ u8 m86E;
    /* 0x86F */ u8 m86F;
    /* 0x870 */ u32 m870;
    /* 0x874 */ u8 m874;
    /* 0x875 */ u8 m875;
    /* 0x876 */ u8 m876;
    /* 0x877 */ u8 m877;
    /* 0x878 */ dPa_rippleEcallBack mRipple;
    /* 0x88C */ u32 m88C;
    /* 0x890 */ u32 m890;
    /* 0x894 */ u32 m894;
    /* 0x898 */ u8 m898;
    /* 0x899 */ u8 m899;
    /* 0x89A */ u8 m89A;
    /* 0x89B */ u8 m89B;
    /* 0x89C */ u8 m89C;
    /* 0x89D */ u8 m89D;
    /* 0x89E */ u8 m89E;
    /* 0x89F */ u8 m89F;
    /* 0x8A0 */ u8 m8A0;
    /* 0x8A1 */ u8 m8A1;
    /* 0x8A2 */ u8 m8A2;
    /* 0x8A3 */ u8 m8A3;
    /* 0x8A4 */ u8 m8A4;
    /* 0x8A5 */ u8 m8A5;
    /* 0x8A6 */ u8 mCharNo;
    /* 0x8A7 */ u8 mStaffNo;
    /* 0x8A8 */ u8 m8A8;
    /* 0x8A9 */ u8 m8A9;
};  // Size: 0x8AC

class daNpc_Ko1_childHIO_c : public mDoHIO_entry_c {
public:
    daNpc_Ko1_childHIO_c();

public:
    /* 0x04 */ u8 mPrm[0x58];
    /* 0x5C */ s32 mIdx;
};  // Size: 0x60

class daNpc_Ko1_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_Ko1_HIO_c();
    virtual ~daNpc_Ko1_HIO_c() {}

    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ daNpc_Ko1_childHIO_c mChild[2];
};  // Size: 0xCC

#endif /* D_A_NPC_KO1_H */
