#ifndef D_A_OBJ_HSEHI1_H
#define D_A_OBJ_HSEHI1_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "m_Do/m_Do_ext.h"

class JPABaseEmitter;
class dBgW;

class daObj_hsh_c : public fopAc_ac_c {
public:
    typedef int (daObj_hsh_c::*ActionFunc)(void*);

public:
    ~daObj_hsh_c();

    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    void particle_set(unsigned short);
    void particle_set(JPABaseEmitter**, unsigned short);
    void emitterDelete(JPABaseEmitter**);
    void setAttention(bool);
    void onOffDraw();
    void offOffDraw();
    void drawStop();
    void drawStart();
    void setBaseMtx();
    BOOL createHeap();
    cPhs_State create();
    BOOL init();
    void action(void*);
    BOOL setAction(ActionFunc, void*);
    BOOL waitAction(void*);
    BOOL talkAction(void*);
    BOOL offAction(void*);
    BOOL deleteAction(void*);
    void eventOrder();
    void checkOrder();
    BOOL checkCommandTalk();
    BOOL chkAttention(cXyz, short);
    BOOL eventProc();
    void eventEnd();
    void initialDefault(int);
    BOOL actionDefault(int);
    void initialLinkDispEvent(int);
    void initialMsgSetEvent(int);
    BOOL actionMsgSetEvent(int);
    BOOL actionMessageEvent(int);
    BOOL actionTactEvent(int);
    void initialJudgeEvent(int);
    void initialAppearEvent(int);
    BOOL actionAppearEvent(int);
    void initialDeleteEvent(int);
    BOOL actionDeleteEvent(int);
    BOOL talk_init();
    BOOL talk(int);
    u32 getMsg();
    u32 next_msgStatus(u32*);
    BOOL execute();
    BOOL draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgS_ObjAcch mAcch;
    /* 0x460 */ dBgS_AcchCir mAcchCir;
    /* 0x4A0 */ JPABaseEmitter* m4A0;
    /* 0x4A4 */ Mtx m4A4;
    /* 0x4D4 */ dBgW* m4D4;
    /* 0x4D8 */ u8 field_0x4D8[0x4E4 - 0x4D8];
    /* 0x4E4 */ cBgS_PolyInfo mPolyInfo;
    /* 0x4F4 */ ActionFunc mCurrActionFunc;
    /* 0x500 */ u32 m500;
    /* 0x504 */ u32 m504;
    /* 0x508 */ u32 m508;
    /* 0x50C */ u32 m50C;
    /* 0x510 */ u32 m510;
    /* 0x514 */ s8 m514;
    /* 0x515 */ s8 m515;
    /* 0x516 */ u8 field_0x516;
    /* 0x517 */ s8 mActionStatus;
    /* 0x518 */ u8 m518;
    /* 0x519 */ u8 m519;
    /* 0x51C */ s16 m51C;
    /* 0x51E */ s16 m51E;
    /* 0x520 */ s16 m520;
    /* 0x522 */ s16 m522;
    /* 0x524 */ u32 field_0x524;
    /* 0x528 */ f32 m528;
    /* 0x52C */ u32 field_0x52C;
    /* 0x530 */ s16 m530[2];
};

class daObj_hsh_HIO_c : public JORReflexible {
public:
    daObj_hsh_HIO_c();
    virtual ~daObj_hsh_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ s16 m14;
    /* 0x16 */ u8 m16;
    /* 0x18 */ daObj_hsh_c* mpActor;
};

#endif /* D_A_OBJ_HSEHI1_H */
