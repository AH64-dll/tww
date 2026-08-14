#ifndef D_A_OBJ_BUOYFLAG_H
#define D_A_OBJ_BUOYFLAG_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_mtx.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"

namespace daObjBuoyflag {
    class Act_c;

    enum Type_e {
        Type_UNK0_e = 0,
        Type_UNK1_e = 1,
        Type_UNK2_e = 2,
    };
    enum Texture_e {
        Texture_00_e = 0x0,
        Texture_01_e = 0x1,
    };

    struct AttrType_c {
        /* 0x00 */ f32 mScale;
        /* 0x04 */ u8 m04;
        /* 0x05 */ u8 m05;
        /* 0x06 */ u8 m06;
        /* 0x07 */ u8 m07;
    }; // size = 0x8

    class DrawVtx_c {
    public:
        /* 0x000 */ cXyz mPos[35];
        /* 0x1A4 */ cXyz mNrm[35];
        /* 0x348 */ cXyz mNrm2[35];
    }; // size = 0x4EC

    class Packet_c : public J3DPacket {
    public:
        Packet_c() { hasi_nrm_init(); }
        virtual ~Packet_c() { /* Nonmatching */ /* __dt__ 95.12: retail guards mPos[35] __destroy_arr with addic./beq */ }

        void hasi_nrm_init();
        void draw_hata(Act_c*);
        void draw_hasi(Act_c*);
        virtual void draw();
        void init(Act_c*);
        void calc_wind_base(Act_c*);
        void calc_pos_spring_near(const cXyz*, const cXyz*, f32, f32);
        void calc_pos(Act_c*);
        void calc_nrm();
        void calc(Act_c*);
        void update(Act_c*);

        void calc_pos_gravity(int, int);
        void calc_pos_spd(int, int);
        void calc_pos_spring(int, int);
        void calc_pos_wave(int, int);

        static cXyz M_hasi_nrm[11];
        static bool M_hasi_nrm_flag;

        /* 0x10 */ DrawVtx_c mDrawVtx[2];
        /* 0x9E8 */ cXyz mPos[35];
        /* 0xB8C */ s32 mB8C;
        /* 0xB90 */ Mtx mB90;
        /* 0xBC0 */ Mtx mBC0;
        /* 0xBF0 */ Mtx mBF0;
        /* 0xC20 */ Mtx mC20;
        /* 0xC50 */ cXyz mC50;
        /* 0xC5C */ cXyz mC5C;
        /* 0xC68 */ s16 mC68[12];
        /* 0xC80 */ cXyz mC80;
    }; // size = 0xC8C

    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_TYPE_W = 2,
            PRM_TYPE_S = 0,

            PRM_TEXTURE_W = 1,
            PRM_TEXTURE_S = 8,

            PRM_FLAG_W = 1,
            PRM_FLAG_S = 31,
        };

        static fpc_ProcID make_norm(fpc_ProcID parentPId, cXyz* pos, int roomNo, csXyz* angle) {
            u32 params = prm_make(Type_UNK0_e, Texture_00_e, false);
            return fopAcM_createChild(fpcNm_Obj_Buoyflag_e, parentPId, params, pos, roomNo, angle);
        }
        static u32 prm_make(Type_e type, Texture_e texture, bool arg2) {
            s32 b = arg2 ? 1 : 0;
            return (type << PRM_TYPE_S) | (texture << PRM_TEXTURE_S) | (b << PRM_FLAG_S);
        }

        void setup(MtxP mtx) { cMtx_copy(mtx, m1090); }
        inline cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        void jump_to_sea(float, float, short) {}
        static fpc_ProcID make_barrel2_mine(fpc_ProcID parent, cXyz* pos, int room, csXyz* angle, Texture_e texture, bool arg5) {
            u32 params = prm_make(Type_UNK2_e, texture, arg5);
            return fopAcM_createChild(fpcNm_Obj_Buoyflag_e, parent, params, pos, room, angle);
        }
        static fpc_ProcID make_barrel2_norm(fpc_ProcID parent, cXyz* pos, int room, csXyz* angle, Texture_e texture) {
            u32 params = prm_make(Type_UNK1_e, texture, false);
            return fopAcM_createChild(fpcNm_Obj_Buoyflag_e, parent, params, pos, room, angle);
        }
        inline const AttrType_c* attr_type() const;
        inline Texture_e prm_get_texture() const;
        void prm_get_noCull() const {}
        s32 prm_get_type() const {
            return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S);
        }

        void mtx_init();
        int mode_afl();
        int mode_jumpToSea();

        static const dCcD_SrcCyl M_cyl_src;
        static const AttrType_c M_attr_type[4];

        
        /* 0x290 */ request_of_phase_process_class mPhase;
        /* 0x298 */ dCcD_Stts mStts;
        /* 0x2D4 */ dCcD_Cyl mCyl;
        /* 0x404 */ Packet_c mPacket;
        /* 0x1090 */ Mtx m1090;
        /* 0x10C0 */ Mtx m10C0;
        /* 0x10F0 */ Mtx m10F0;
        /* 0x1120 */ s32 m1120;
        /* 0x1124 */ s32 m1124;
        /* 0x1128 */ bool m1128;
        /* 0x112A */ s16 m112A;
        /* 0x112C */ f32 m112C;
        /* 0x1130 */ cXyz m1130;
    }; // size = 0x113C

    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };

};

#endif /* D_A_OBJ_BUOYFLAG_H */
