#ifndef D_A_NPC_KG2_H
#define D_A_NPC_KG2_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daNpc_Kg2_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Kg2_c::*ActionFunc)(void*);

    cXyz& getAttentionBasePos() { return m714; }
    cXyz& getEyePos() { return m708; }
    void setAction(ActionFunc i_action, void* i_param) {
        if (mAction != i_action) {
            if (mAction) {
                m763 = -1;
                (this->*mAction)(i_param);
            }
            mAction = i_action;
            m763 = 0;
            (this->*mAction)(i_param);
        }
    }
    static void setCanonGameResult(u8 result) { canon_game_result = result; }

    void set_mtx();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8, f32);
    void subAnm();
    s32 chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    u32 getMsg();
    u16 next_msgStatus(u32*);
    void anmAtr(u16);
    void setAttention();
    void lookBack();
    BOOL CreateHeap();
    BOOL CreateInit();
    void wait01();
    void talk01();
    int evn_setAnm_init(int);
    int evn_setAnm();
    int evn_jnt_lock_init(int);
    int evn_talk_init(int);
    int evn_talk();
    int evn_createItem_init(int);
    int privateCut();
    BOOL processMove();
    int wait_action(void*);
    int event_wait_action(void*);
    cPhs_State _create();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();

    static void init() {
        canon_game_result = 0;
    }

    static const char M_arcname[];
    static s8 canon_game_result;
    static daNpc_Kg2_c* l_kg2_pointer;

public:
    /* 0x6C4 */ s8 m6C4;
    /* 0x6C8 */ request_of_phase_process_class mPhs;
    /* 0x6D0 */ u32 m6D0;
    /* 0x6D4 */ J3DModel* m6D4;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ J3DAnmTexPattern* m_eye_tex_pattern;
    /* 0x6F0 */ mDoExt_btpAnm m6F0;
    /* 0x704 */ u8 m704;
    /* 0x705 */ u8 field_0x705[0x706 - 0x705];
    /* 0x706 */ s16 m706;
    /* 0x708 */ cXyz m708;
    /* 0x714 */ cXyz m714;
    /* 0x720 */ s16 m720;
    /* 0x722 */ u8 field_0x722[0x724 - 0x722];
    /* 0x724 */ s16 m724;
    /* 0x726 */ s16 m726;
    /* 0x728 */ s16 m728;
    /* 0x72A */ u8 field_0x72a[0x72c - 0x72a];
    /* 0x72C */ u8 m72C;
    /* 0x72D */ u8 m72D;
    /* 0x72E */ u8 field_0x72e[0x734 - 0x72e];
    /* 0x734 */ u8 m734;
    /* 0x735 */ u8 m735;
    /* 0x736 */ u8 m736;
    /* 0x737 */ u8 m737;
    /* 0x738 */ u8 m738;
    /* 0x739 */ u8 m739;
    /* 0x73A */ u8 field_0x73a[0x73c - 0x73a];
    /* 0x73C */ ActionFunc mAction;
    /* 0x748 */ s8 m748;
    /* 0x749 */ s8 m749;
    /* 0x74A */ u8 field_0x74a[0x74c - 0x74a];
    /* 0x74C */ u32 m74C;
    /* 0x750 */ u8 m750;
    /* 0x751 */ u8 field_0x751[0x754 - 0x751];
    /* 0x754 */ u32 m754;
    /* 0x758 */ s16 m758[4];
    /* 0x760 */ u8 m760;
    /* 0x761 */ u8 field_0x761[0x763 - 0x761];
    /* 0x763 */ s8 m763;
}; // Size: 0x764

STATIC_ASSERT(sizeof(daNpc_Kg2_c) == 0x764);

class daNpc_Kg2_HIO_c : public JORReflexible {
public:
    daNpc_Kg2_HIO_c();
    virtual ~daNpc_Kg2_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ dNpc_HIO_c mHio;
    /* 0x30 */ u8 field_0x30;
};

#endif /* D_A_NPC_KG2_H */
