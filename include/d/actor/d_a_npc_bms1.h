#ifndef D_A_NPC_BMS1_H
#define D_A_NPC_BMS1_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"
#include "d/d_shop.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Bms1_c : public fopAc_ac_c {
public:
    typedef BOOL (daNpc_Bms1_c::*ActionFunc)(void*);

    s8 getBackboneJntNum() { return mJntCtrl.getBackboneJntNum(); }
    s16 getBackbone_x() { return mJntCtrl.getBackbone_x(); }
    s16 getBackbone_y() { return mJntCtrl.getBackbone_y(); }
    s8 getHeadJntNum() { return mJntCtrl.getHeadJntNum(); }
    s16 getHead_x() { return mJntCtrl.getHead_x(); }
    s16 getHead_y() { return mJntCtrl.getHead_y(); }
    s8 getHairLJntNum() { return m_hairL_jnt_num; }
    s8 getHairRJntNum() { return m_hairR_jnt_num; }
    void incAttnSetCount() {}
    void setAction(ActionFunc i_funcP, void* i_actParam) {
        if (mCurrActionFunc != i_funcP) {
            if (mCurrActionFunc) {
                mActionStatus = -1;
                (this->*mCurrActionFunc)(NULL);
            }
            mCurrActionFunc = i_funcP;
            mActionStatus = 0;
            (this->*mCurrActionFunc)(i_actParam);
        }
    }
    void setAttentionBasePos(cXyz i_attnBasePos) { mAttnBasePos = i_attnBasePos; }
    void setEyePos(cXyz i_eyePos) { eyePos = i_eyePos; }

    void set_mtx();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8, f32);
    void setTexAnm(s8);
    void setAnmFromMsgTag();
    BOOL chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void talkInit();
    u16 normal_talk();
    u16 shop_talk();
    u16 talk();
    BOOL CreateInit();
    void setAttention(bool);
    BOOL checkPlayerLanding();
    void lookBack();
    bool wait01();
    bool talk01();
    BOOL getdemo_action(void*);
    BOOL wait_action(void*);
    BOOL event_action(void*);
    BOOL evn_talk_init(int);
    BOOL evn_continue_talk_init(int);
    BOOL evn_talk();
    BOOL evn_viblation_init(int);
    BOOL evn_head_swing_init(int);
    BOOL privateCut();
    BOOL demo_move();
    void demo_end_init();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

    static char m_arcname[];

public:
    /* 0x290 */ dNpc_HeadAnm_c mHeadAnm;
    /* 0x2B4 */ cXyz m2B4;
    /* 0x2C0 */ cXyz m2C0;
    /* 0x2CC */ f32 m2CC;
    /* 0x2D0 */ f32 m2D0;
    /* 0x2D4 */ cXyz m2D4;
    /* 0x2E0 */ cXyz m2E0;
    /* 0x2EC */ cXyz m2EC;
    /* 0x2F8 */ cXyz m2F8;
    /* 0x304 */ Quaternion m304;
    /* 0x314 */ Quaternion m314;
    /* 0x324 */ request_of_phase_process_class mPhs;
    /* 0x32C */ mDoExt_McaMorf* mpMorf;
    /* 0x330 */ u32 mShadowID;
    /* 0x334 */ J3DAnmTexPattern* mpBtpRes;
    /* 0x338 */ mDoExt_btpAnm mBtpAnm;
    /* 0x34C */ u8 mBtpFrame;
    /* 0x34D */ u8 m34D;
    /* 0x34E */ s16 m34E;
    /* 0x350 */ J3DModel* mpModel;
    /* 0x354 */ J3DModel* mpModel2;
    /* 0x358 */ J3DModel* mpModel3;
    /* 0x35C */ J3DModel* mpModel4;
    /* 0x360 */ J3DModel* mpModel5;
    /* 0x364 */ dBgS_ObjAcch mAcch;
    /* 0x528 */ dBgS_AcchCir mAcchCir;
    /* 0x568 */ dCcD_Stts mStts;
    /* 0x5A4 */ dCcD_Cyl mCyl;
    /* 0x6D4 */ s8 m_head_jnt_num;
    /* 0x6D5 */ s8 m_backbone_jnt_num;
    /* 0x6D6 */ s8 m_hairL_jnt_num;
    /* 0x6D7 */ s8 m_hairR_jnt_num;
    /* 0x6D8 */ s8 m_leg_jnt_num;
    /* 0x6D9 */ u8 m6D9[0x6DC - 0x6D9];
    /* 0x6DC */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x710 */ dNpc_EventCut_c mEventCut;
    /* 0x77C */ u8 m77C[0x7A4 - 0x77C];
    /* 0x7A4 */ u8 m7A4;
    /* 0x7A5 */ u8 m7A5[0x7B4 - 0x7A5];
    /* 0x7B4 */ cXyz mAttnBasePos;
    /* 0x7C0 */ s16 m7C0;
    /* 0x7C2 */ s16 m7C2;
    /* 0x7C4 */ s16 m7C4;
    /* 0x7C6 */ s16 m7C6;
    /* 0x7C8 */ u8 m7C8[0x7CA - 0x7C8];
    /* 0x7CA */ u8 mMorfIsStop;
    /* 0x7CB */ u8 m7CB;
    /* 0x7CC */ u8 m7CC;
    /* 0x7CD */ u8 m7CD;
    /* 0x7CE */ u8 m7CE;
    /* 0x7CF */ u8 m7CF;
    /* 0x7D0 */ f32 mMorfPrevFrame;
    /* 0x7D4 */ f32 m7D4;
    /* 0x7D8 */ u32 mMsgNo;
    /* 0x7DC */ u32 mMsgNo2;
    /* 0x7E0 */ u32 m7E0;
    /* 0x7E4 */ u32 mLastMsgNo;
    /* 0x7E8 */ u8 m7E8;
    /* 0x7E9 */ u8 m7E9;
    /* 0x7EA */ u8 m7EA[0x7EC - 0x7EA];
    /* 0x7EC */ ActionFunc mCurrActionFunc;
    /* 0x7F8 */ ShopCam_action_c mShopCam;
    /* 0x850 */ ShopItems_c mShopItems;
    /* 0x894 */ ShopCursor_c* mpShopCursor;
    /* 0x898 */ s8 mBtpIdx;
    /* 0x899 */ s8 m899;
    /* 0x89A */ u8 m89A;
    /* 0x89B */ s8 m89B;
    /* 0x89C */ s8 m89C;
    /* 0x89D */ u8 m89D;
    /* 0x89E */ s8 mShopIdx;
    /* 0x89F */ u8 m89F[0x8A0 - 0x89F];
    /* 0x8A0 */ s8 mActionStatus;
    /* 0x8A1 */ u8 m8A1[0x8A2 - 0x8A1];
    /* 0x8A2 */ u8 m8A2;
    /* 0x8A3 */ u8 m8A3[0x8A5 - 0x8A3];
    /* 0x8A5 */ u8 m8A5;
    /* 0x8A6 */ u8 m8A6[0x8A8 - 0x8A6];
};  // Size: 0x8A8

class daNpc_Bms1_childHIO_c : public JORReflexible {
public:
    daNpc_Bms1_childHIO_c();
    virtual ~daNpc_Bms1_childHIO_c() {}

public:
    /* 0x000 */ // this.__vt
    /* 0x004 */ dNpc_HIO_c mNpc;
    /* 0x02C */ f32 m2C;
    /* 0x030 */ f32 m30;
    /* 0x034 */ f32 m34;
    /* 0x038 */ f32 m38;
    /* 0x03C */ f32 m3C;
    /* 0x040 */ f32 m40;
    /* 0x044 */ f32 m44;
    /* 0x048 */ f32 m48;
    /* 0x04C */ f32 m4C;
};  // Size: 0x50

class daNpc_Bms1_HIO_c : public JORReflexible {
public:
    daNpc_Bms1_HIO_c();
    virtual ~daNpc_Bms1_HIO_c() {}

public:
    /* 0x000 */ // this.__vt
    /* 0x004 */ s8 mNo;
    /* 0x008 */ int m8;
    /* 0x00C */ daNpc_Bms1_childHIO_c mChild[1];
};  // Size: 0x5C

#endif /* D_A_NPC_BMS1_H */
