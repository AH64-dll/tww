#ifndef D_A_OBJ_HSEHI1_H
#define D_A_OBJ_HSEHI1_H

#include "f_op/f_op_actor.h"

class JPABaseEmitter;
class cBgW;

class daObj_hsh_c : public fopAc_ac_c {
public:
    ~daObj_hsh_c();
    
    void isEventAccept() {}
    void isOffDraw() {}
    void isTactCancel() {}
    void isTactCorrect() {}
    void offEventAccept() {}
    void offTactCancel() {}
    void offTactCorrect() {}
    void onEventAccept() {}
    void onTactCancel() {}
    void onTactCorrect() {}

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
    void createHeap();
    cPhs_State create();
    void init();
    void action(void*);
    void setAction(int (daObj_hsh_c::*)(void*), void*);
    void waitAction(void*);
    void talkAction(void*);
    void offAction(void*);
    void deleteAction(void*);
    void eventOrder();
    void checkOrder();
    void checkCommandTalk();
    void chkAttention(cXyz, short);
    void eventProc();
    void eventEnd();
    void initialDefault(int);
    void actionDefault(int);
    void initialLinkDispEvent(int);
    void initialMsgSetEvent(int);
    void actionMsgSetEvent(int);
    void actionMessageEvent(int);
    void actionTactEvent(int);
    void initialJudgeEvent(int);
    void initialAppearEvent(int);
    void actionAppearEvent(int);
    void initialDeleteEvent(int);
    void actionDeleteEvent(int);
    void talk_init();
    void talk(int);
    void getMsg();
    void next_msgStatus(unsigned long*);
    BOOL execute();
    BOOL draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ u8 field_0x29C[0x4A0 - 0x29C];
    /* 0x4A0 */ JPABaseEmitter* m4A0;
    /* 0x4A4 */ Mtx m4A4;
    /* 0x4D4 */ cBgW* m4D4;
    /* 0x4D8 */ u8 field_0x4D8[0x504 - 0x4D8];
    /* 0x504 */ u32 m504;
    /* 0x515 */ u8 m515;
    /* 0x530 */ s16 m530;
};

class daObj_hsh_HIO_c {
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
};

#endif /* D_A_OBJ_HSEHI1_H */
