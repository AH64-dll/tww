#ifndef D_A_NPC_PF1_H
#define D_A_NPC_PF1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Pf1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Pf1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    BOOL init_PF1_0();
    BOOL createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool setBtp(signed char, bool);
    bool init_texPttrnAnm(signed char, bool);
    void play_btp_anm();
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
    u32 getMsg_PF1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    BOOL chk_talk();
    BOOL chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    void lookBack();
    BOOL chkAttention();
    void setAttention(bool);
    BOOL decideType(int);
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Pf1_c::*)(void*), void*);
    void setStt(signed char);
    void createTama(float);
    BOOL chk_areaIN(float, cXyz);
    BOOL endEvent_check();
    BOOL startEvent_check();
    void set_pthPoint(unsigned char);
    BOOL chk_attn();
    void setBikon(cXyz);
    void delBikon();
    BOOL wait_1();
    BOOL regret();
    BOOL attk_1();
    BOOL walk_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL talk_1();
    BOOL wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ char m_arcname[6];
    /* 0x6D4 */ u32 mShadowID;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u8 mBtpFrame;
    /* 0x6ED */ u8 field_0x6ED;
    /* 0x6EE */ s16 m6EE;
    /* 0x6F0 */ ProcFunc mProcFunc;
    /* 0x6FC */ u8 field_0x6FC[0x700 - 0x6FC];
    /* 0x700 */ fpc_ProcID mTargetProcID;
    /* 0x704 */ dNpc_PathRun_c mPathRun;
    /* 0x70C */ cXyz mHomePos;
    /* 0x718 */ s16 m718;
    /* 0x71A */ s16 m71A;
    /* 0x71C */ s16 m71C;
    /* 0x71E */ csXyz mAngle;
    /* 0x724 */ u8 field_0x724[0x72C - 0x724];
    /* 0x72C */ cXyz mEyePos;
    /* 0x738 */ cXyz mLookTargetPos;
    /* 0x744 */ u8 field_0x744[0x750 - 0x744];
    /* 0x750 */ cXyz mHeadPos;
    /* 0x75C */ u8 field_0x75C[0x768 - 0x75C];
    /* 0x768 */ cXyz mObjAcchNormal;
    /* 0x774 */ f32 mPrevMorfFrame;
    /* 0x778 */ u8 field_0x778[0x77C - 0x778];
    /* 0x77C */ s16 m77C;
    /* 0x77E */ s16 m77E;
    /* 0x780 */ s16 m780;
    /* 0x782 */ u8 field_0x782[0x784 - 0x782];
    /* 0x784 */ s32 mActionResult;
    /* 0x788 */ s16 mEventIdTable[1];
    /* 0x78A */ s16 m78A;
    /* 0x78C */ u8 field_0x78C[0x796 - 0x78C];
    /* 0x796 */ s16 m796;
    /* 0x798 */ s16 m798;
    /* 0x79A */ u8 field_0x79A[0x79E - 0x79A];
    /* 0x79E */ s16 m79E;
    /* 0x7A0 */ s8 m7A0;
    /* 0x7A1 */ u8 m7A1;
    /* 0x7A2 */ u8 m7A2;
    /* 0x7A3 */ u8 m7A3;
    /* 0x7A4 */ u8 m7A4;
    /* 0x7A5 */ u8 m7A5;
    /* 0x7A6 */ u8 m7A6;
    /* 0x7A7 */ u8 mCreatePhase;
    /* 0x7A8 */ u8 m7A8;
    /* 0x7A9 */ u8 m7A9;
    /* 0x7AA */ u8 mAnmAtr;
    /* 0x7AB */ u8 mAnmTag;
    /* 0x7AC */ u8 m7AC;
    /* 0x7AD */ u8 mActNo;
    /* 0x7AE */ u8 m7AE;
    /* 0x7AF */ u8 mHeadOnlyFollow;
    /* 0x7B0 */ u8 m7B0;
    /* 0x7B1 */ u8 m7B1;
    /* 0x7B2 */ u8 m7B2;
    /* 0x7B3 */ u8 m7B3;
    /* 0x7B4 */ u8 m7B4;
    /* 0x7B5 */ u8 m7B5;
    /* 0x7B6 */ u8 m7B6;
    /* 0x7B7 */ u8 m7B7;
    /* 0x7B8 */ s8 mStt;
    /* 0x7B9 */ u8 m7B9;
    /* 0x7BA */ u8 m7BA;
    /* 0x7BB */ s8 mType;
    /* 0x7BC */ s8 m7BC;
    /* 0x7BD */ u8 m7BD;
    /* 0x7BE */ u8 m7BE;
};  // Size: 0x7C0

#endif /* D_A_NPC_PF1_H */
