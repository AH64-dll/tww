#ifndef D_A_NPC_YW1_H
#define D_A_NPC_YW1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;
class J3DModel;

class daNpc_Yw1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Yw1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };

    void _nodeCB_Hair(J3DNode*, J3DModel*);
    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void init_YW1_0();
    void init_YW1_1();
    void init_YW1_2();
    void init_YW1_3();
    void createInit();
    void play_animation();
    void upLift();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    void init_texPttrnAnm(signed char, bool);
    void play_texPttrnAnm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    u16 next_msgStatus(u32*);
    u32 getMsg_YW1_0();
    u32 getMsg_YW1_1();
    u32 getMsg_YW1_2();
    u32 getMsg_YW1_3();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_parts_notMov();
    void searchByID(fpc_ProcID, int*);
    void partner_search_sub(void* (*)(void*, void*));
    void partner_search();
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    void decideType(int);
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Yw1_c::*)(void*), void*);
    void setStt(signed char);
    void chngTsuboAnm();
    void chk_areaIN(float, float, short, cXyz);
    void set_pthPoint(unsigned char);
    void setHairAngle();
    void chk_brkTsubo();
    void chk_bm1Odoroki();
    void wait_1();
    void wait_2();
    void wait_3();
    void walk_1();
    void turn_1();
    void talk_1();
    void wait_action1(void*);
    void wait_action2(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void bodyCreateHeap();
    void headCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hair1_jnt_num;
    /* 0x6CF */ s8 m_hair2_jnt_num;
    /* 0x6D0 */ s8 m_hair3_jnt_num;
    /* 0x6D1 */ u8 field_0x6d1[0x6D4 - 0x6D1];
    /* 0x6D4 */ u32 mShadowID;
    /* 0x6D8 */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x6DC */ mDoExt_btpAnm mHeadBtpAnm;
    /* 0x6F0 */ u8 mBlinkFrame;
    /* 0x6F2 */ s16 mBlinkTimer;
    /* 0x6F4 */ ProcFunc mCurrProcFunc;
    /* 0x700 */ u32 m700;
    /* 0x704 */ u32 m704;
    /* 0x708 */ u32 m708;
    /* 0x70C */ u32 m70C;
    /* 0x710 */ u8 field_0x710[0x711 - 0x710];
    /* 0x711 */ u8 m711;
    /* 0x712 */ u8 m712;
    /* 0x713 */ u8 field_0x713[0x720 - 0x713];
    /* 0x720 */ s16 m720;
    /* 0x722 */ s16 m722;
    /* 0x724 */ s16 m724;
    /* 0x726 */ s16 m726;
    /* 0x728 */ s16 m728;
    /* 0x72A */ s16 m72A;
    /* 0x72C */ cXyz m72C;
    /* 0x738 */ cXyz m738;
    /* 0x744 */ f32 m744;
    /* 0x748 */ f32 m748;
    /* 0x74C */ f32 m74C;
    /* 0x750 */ f32 m750;
    /* 0x754 */ u8 field_0x754[0x758 - 0x754];
    /* 0x758 */ s16 m758;
    /* 0x75A */ s16 m75A;
    /* 0x75C */ s16 m75C;
    /* 0x75E */ u8 field_0x75e[0x760 - 0x75E];
    /* 0x760 */ u32 m760;
    /* 0x764 */ u8 field_0x764[0x766 - 0x764];
    /* 0x766 */ s16 m766;
    /* 0x768 */ u8 field_0x768[0x76C - 0x768];
    /* 0x76C */ s16 m76C;
    /* 0x76E */ s16 m76E;
    /* 0x770 */ u8 m770;
    /* 0x771 */ u8 m771;
    /* 0x772 */ u8 m772;
    /* 0x773 */ u8 m773;
    /* 0x774 */ u8 m774;
    /* 0x775 */ u8 m775;
    /* 0x776 */ u8 m776;
    /* 0x777 */ u8 m777;
    /* 0x778 */ u8 m778;
    /* 0x779 */ u8 m779;
    /* 0x77A */ u8 m77A;
    /* 0x77B */ u8 m77B;
    /* 0x77C */ u8 m77C;
    /* 0x77D */ u8 m77D;
    /* 0x77E */ u8 m77E;
    /* 0x77F */ u8 field_0x77f[0x780 - 0x77F];
    /* 0x780 */ s16 m780;
    /* 0x782 */ s16 m782;
    /* 0x784 */ s16 m784;
    /* 0x786 */ s16 m786;
    /* 0x788 */ u8 field_0x788[0x794 - 0x788];
    /* 0x794 */ f32 m794;
    /* 0x798 */ f32 m798;
    /* 0x79C */ f32 m79C;
    /* 0x7A0 */ s16 m7A0;
    /* 0x7A2 */ s16 m7A2;
    /* 0x7A4 */ s16 m7A4;
    /* 0x7A6 */ s16 m7A6;
    /* 0x7A8 */ s16 m7A8;
    /* 0x7AA */ s16 m7AA;
    /* 0x7AC */ s16 m7AC;
    /* 0x7AE */ s16 m7AE;
    /* 0x7B0 */ s16 m7B0;
    /* 0x7B2 */ s16 m7B2;
    /* 0x7B4 */ s16 m7B4;
    /* 0x7B6 */ s16 m7B6;
    /* 0x7B8 */ s16 m7B8;
    /* 0x7BA */ s16 m7BA;
    /* 0x7BC */ u8 m7BC;
    /* 0x7BD */ u8 mAnmAtr;
    /* 0x7BE */ u8 mAnmTag;
    /* 0x7BF */ u8 m7BF;
    /* 0x7C0 */ u8 mAnmNum;
    /* 0x7C1 */ s8 mStatus;
    /* 0x7C2 */ s8 mStt;
    /* 0x7C3 */ u8 m7C3;
    /* 0x7C4 */ u8 m7C4;
    /* 0x7C5 */ u8 m7C5;
    /* 0x7C6 */ u8 m7C6;
    /* 0x7C7 */ u8 m7C7;
    /* 0x7C8 */ u8 m7C8;
};  // Size: 0x7CC

class daNpc_Yw1_childHIO_c : public mDoHIO_entry_c {
public:
    daNpc_Yw1_childHIO_c();
    virtual ~daNpc_Yw1_childHIO_c() {}

public:
    /* Place member variables here */
};

class daNpc_Yw1_HIO_c {
public:
    daNpc_Yw1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_YW1_H */
