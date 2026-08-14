#ifndef D_A_OBJ_SEARCH_H
#define D_A_OBJ_SEARCH_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_w.h"
#include "d/d_kankyo.h"
#include "d/d_particle.h"
#include "d/d_lib.h"

class J3DNode;
class dPath;

namespace daObj_Search {
    class Act_c;

    struct Attr_c {
        /* 0x00 */ u8 m00;
        /* 0x01 */ u8 m01;
        /* 0x02 */ s16 m02;
        /* 0x04 */ f32 m04;
        /* 0x08 */ s16 m08;
        /* 0x0A */ s16 m0A;
        /* 0x0C */ f32 m0C;
        /* 0x10 */ f32 m10;
        /* 0x14 */ f32 m14;
        /* 0x18 */ f32 m18;
        /* 0x1C */ f32 m1C;
        /* 0x20 */ f32 m20;
        /* 0x24 */ s32 m24;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
        /* 0x30 */ f32 m30;
        /* 0x34 */ f32 m34;
        /* 0x38 */ u8 m38;
        /* 0x39 */ u8 m39;
        /* 0x3A */ u8 m3A;
        /* 0x3B */ u8 m3B;
        /* 0x3C */ s16 m3C;
        /* 0x3E */ s16 m3E;
        /* 0x40 */ f32 m40;
        /* 0x44 */ u8 m44;
        /* 0x45 */ u8 m45;
        /* 0x46 */ u8 m46;
        /* 0x47 */ u8 m47;
        /* 0x48 */ u32 m48;
        /* 0x4C */ f32 m4C;
        /* 0x50 */ s16 m50;
        /* 0x52 */ s16 m52;
        /* 0x54 */ f32 m54;
        /* 0x58 */ f32 m58;
        /* 0x5C */ s16 m5C;
        /* 0x5E */ s16 m5E;
    };  // Size: 0x60

    STATIC_ASSERT(sizeof(Attr_c) == 0x60);

    class Bgc_c : public dBgS_LinChk {
    public:
        Bgc_c();
        void wall_pos(const Act_c* i_actor, cXyz* o_pos, cXyz* o_normal, bool* o_hit, float* o_dist);

        /* 0x6C */ cXyz mPos;
    };  // Size: 0x78

    class Act_c : public fopAc_ac_c {
    public:
        enum Proc_e {
            PROC_INIT_e = 0,
            PROC_EXEC_e = 1,
        };

        enum Mode_e {
            MODE_SEARCH_RND_e = 0,
            MODE_SEARCH_PATH_e,
            MODE_STOP_e,
            MODE_TO_SEARCH_e,
            MODE_TO_STOP_e,
            MODE_FIND_e,
            MODE_FIND_2ND_e,
            MODE_SEARCH_BDK_e,
        };

        static bool getFindFlag() { return m_find_flag == true; }
        static void setFindFlag(bool flag) { m_find_flag = flag; }

        static bool m_find_flag;
        static const char m_arc_name[7];
        static const Attr_c m_attr;

        Act_c();
        Bgc_c* getBgc() { return &mBgc; }

        void isSecond() {}
        void modeProcInit(int) {}
        void setBkControl(bool control) { mBkControl = control; }
        void setChildId(fpc_ProcID id) { mChildId = id; }

        BOOL _createHeap();
        bool searchCreateHeap();
        bool beamCreateHeap(int);
        void _nodeControl(J3DNode*, J3DModel*);
        void modeSearchRndInit();
        void modeSearchRnd();
        void modeSearchPathInit();
        void modeSearchPath();
        void modeStopInit();
        void modeStop();
        void modeToSearchInit();
        void modeToSearch();
        void modeToStopInit();
        void modeToStop();
        void modeFindInit();
        void modeFind();
        void modeFind2ndInit();
        void modeFind2nd();
        void modeSearchBdkInit();
        void modeSearchBdk();
        void modeProc(Proc_e, int);
        const Attr_c* attr() const;
        void SetArgData();
        void CreateInit();
        cPhs_State _create();
        void smoke_set(float, int);
        bool _execute();
        void check_bk_control();
        void set_mtx_base();
        void set_mtx_light_A();
        void set_mtx_light_B();
        void set_moveBG_mtx_base();
        void set_moveBG_mtx_light_A();
        void set_moveBG_mtx_light_B();
        void bg_check();
        bool player_check();
        void set_path_info();
        bool is_path_info();
        bool _draw();
        bool _delete();
        BOOL _isdelete();

    public:
        /* 0x290 */ s32 mMode;
        /* 0x294 */ Bgc_c mBgc;
        /* 0x30C */ dCcD_Cps mCps[2];
        /* 0x57C */ dCcD_Stts mStts[2];
        /* 0x5F4 */ J3DModel* mModel;
        /* 0x5F8 */ J3DModel* mBeamModel[2];
        /* 0x600 */ cXyz m600;
        /* 0x60C */ cXyz m60C[2];
        /* 0x624 */ cXyz m624[2];
        /* 0x63C */ cXyz m63C[2];
        /* 0x654 */ f32 m654;
        /* 0x658 */ f32 m658;
        /* 0x65C */ f32 m65C;
        /* 0x660 */ f32 m660;
        /* 0x664 */ u8 mBkControl;
        /* 0x665 */ u8 m665[0x668 - 0x665];
        /* 0x668 */ dBgW* mBgWBeam[2];
        /* 0x670 */ dBgW* mBgW;
        /* 0x674 */ Mtx mBgMtxBeam[2];
        /* 0x6D4 */ Mtx mBgMtx;
        /* 0x704 */ u8 m704[0x706 - 0x704];
        /* 0x706 */ csXyz mAngle[2];
        /* 0x712 */ u8 m712[0x71C - 0x712];
        /* 0x71C */ Mtx m71C;
        /* 0x74C */ Mtx m74C;
        /* 0x77C */ u8 m77C;
        /* 0x77D */ u8 m77D;
        /* 0x77E */ s16 m77E;
        /* 0x780 */ LIGHT_INFLUENCE mLight;
        /* 0x7A0 */ u32 m7A0;
        /* 0x7A4 */ u32 m7A4;
        /* 0x7A8 */ s16 m7A8;
        /* 0x7AA */ s16 m7AA;
        /* 0x7AC */ s16 m7AC;
        /* 0x7AE */ s16 m7AE;
        /* 0x7B0 */ s16 m7B0;
        /* 0x7B2 */ s16 m7B2;
        /* 0x7B4 */ s16 m7B4;
        /* 0x7B6 */ u8 m7B6;
        /* 0x7B7 */ u8 m7B7;
        /* 0x7B8 */ u8 m7B8;
        /* 0x7B9 */ u8 m7B9[0x7E0 - 0x7B9];
        /* 0x7E0 */ s16 m7E0;
        /* 0x7E2 */ u8 m7E2;
        /* 0x7E3 */ u8 m7E3[0x7F4 - 0x7E3];
        /* 0x7F4 */ cXyz m7F4;
        /* 0x800 */ csXyz m800;
        /* 0x808 */ dPa_smokeEcallBack mSmokeE;
        /* 0x828 */ int mTimer;
        /* 0x82C */ u8 m82C[4];
        /* 0x830 */ u32 m830;
        /* 0x834 */ u8 m834;
        /* 0x835 */ u8 m835;
        /* 0x836 */ u8 m836;
        /* 0x837 */ u8 m837;
        /* 0x838 */ cXyz m838;
        /* 0x844 */ s8 m844;
        /* 0x845 */ u8 m845[0x848 - 0x845];
        /* 0x848 */ dPath* mPath;
        /* 0x84C */ fpc_ProcID mChildId;
        /* 0x850 */ u32 m850;
        /* 0x854 */ request_of_phase_process_class mPhs;
        /* 0x85C */ s32 m85C;
        /* 0x860 */ u8 m860;
        /* 0x861 */ u8 m861[0x864 - 0x861];
        /* 0x864 */ dBgS_ObjLinChk mObjLinChk;
        /* 0x8D0 */ u8 m8D0;
        /* 0x8D1 */ u8 m8D1[0x8D4 - 0x8D1];
        /* 0x8D4 */ cXyz m8D4;
        /* 0x8E0 */ s16 m8E0;
        /* 0x8E2 */ u8 m8E2[0x8E4 - 0x8E2];
        /* 0x8E4 */ f32 m8E4;
        /* 0x8E8 */ u8 m8E8[0x8EC - 0x8E8];
        /* 0x8EC */ s16 m8EC;
        /* 0x8EE */ u8 m8EE;
        /* 0x8EF */ u8 m8EF[0x900 - 0x8EF];
        /* 0x900 */ u32 m900;
        /* 0x904 */ u32 m904;
    };  // Size: 0x908

    STATIC_ASSERT(sizeof(Act_c) == 0x908);

    namespace Mthd {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_SEARCH_H */
