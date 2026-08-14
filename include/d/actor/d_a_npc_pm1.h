#ifndef D_A_NPC_PM1_H
#define D_A_NPC_PM1_H

#include "d/d_lib.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Pm1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Pm1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        // Borrowed from d_lib.h, fields seem to match
        /* 0x00 */ s8 bckNum;
        /* 0x01 */ s8 btpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    };

    void createInit();
    void setMtx();
    void anmResID(int, int*, int*);
    void BtpNum2ResID(int, int*);
    void setAnm_tex(signed char);
    void init_btp(bool, int);
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void setStt(signed char);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    void chkAttention();
    void setAttention();
    void decideType(int);
    void event_actionInit(int);
    void event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    void set_action(ProcFunc, void*);
    void wait01();
    void talk01();
    void wait_action1(void*);
    void demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ char mArcName[3];
    /* 0x6D1 */ u8 m6D1[0x6D4 - 0x6D1];
    /* 0x6D4 */ u32 mShadowId;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u8 m6EC[0x780 - 0x6EC];
    /* 0x780 */ cXyz mTransformedEyePos;
    /* 0x78C */ cXyz field_0x78C;
    /* 0x798 */ u8 m798[0x7A8 - 0x798];
    /* 0x7A8 */ u8 m7A8;
    /* 0x7A9 */ u8 m7A9;
    /* 0x7AA */ u8 m7AA;
    /* 0x7AB */ u8 m7AB;
    /* 0x7AC */ u8 m7AC;
    /* 0x7AD */ u8 m7AD;
    /* 0x7AE */ u8 m7AE;
    /* 0x7AF */ u8 m7AF;
    /* 0x7B0 */ u8 m7B0;
    /* 0x7B1 */ u8 m7B1;
    /* 0x7B2 */ u8 m7B2;
    /* 0x7B3 */ u8 m7B3;
    /* 0x7B4 */ u8 m7B4;
    /* 0x7B5 */ u8 m7B5;
    /* 0x7B6 */ u8 m7B6;
    /* 0x7B7 */ u8 m7B7;
    /* 0x7B8 */ u8 m7B8;
    /* 0x7B9 */ u8 m7B9;
    /* 0x7BA */ u8 m7BA;
    /* 0x7BB */ u8 m7BB;
    /* 0x7BC */ u8 m7BC;
    /* 0x7BD */ u8 m7BD;
    /* 0x7BE */ u8 m7BE;
    /* 0x7BF */ u8 m7BF;
    /* 0x7C0 */ u8 m7C0;
    /* 0x7C1 */ u8 m7C1;
    /* 0x7C2 */ u8 m7C2;
    /* 0x7C3 */ u8 m7C3;
    /* 0x7C4 */ u8 m7C4;
    /* 0x7C5 */ u8 m7C5;
    /* 0x7C6 */ u8 m7C6;
    /* 0x7C7 */ u8 m7C7;
    /* 0x7C8 */ u8 m7C8;
    /* 0x7C9 */ u8 m7C9;
    /* 0x7CA */ u8 m7CA;
    /* 0x7CB */ u8 m7CB;
    /* 0x7CC */ u8 m7CC;
    /* 0x7CD */ u8 m7CD;
    /* 0x7CE */ u8 m7CE;
    /* 0x7CF */ u8 m7CF;
    /* 0x7D0 */ u8 m7D0;
    /* 0x7D1 */ u8 m7D1;
    /* 0x7D2 */ u8 m7D2;
    /* 0x7D3 */ u8 m7D3;
    /* 0x7D4 */ u8 m7D4;
    /* 0x7D5 */ u8 m7D5;
    /* 0x7D6 */ u8 m7D6;
};

#endif /* D_A_NPC_PM1_H */
