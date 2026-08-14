#ifndef D_A_FALLROCK_TAG_H
#define D_A_FALLROCK_TAG_H

#include "c/c_dylink.h"
#include "f_op/f_op_actor.h"

class daFallRockTag_c : public fopAc_ac_c {
public:
    struct m_data_t {
        /* 0x00 */ f32 mField_0x00; // 250.0
        /* 0x04 */ f32 mField_0x04; // 0.3
        /* 0x08 */ f32 mField_0x08; // 0.8
        /* 0x0C */ f32 mField_0x0C; // -70.0
        /* 0x10 */ f32 mField_0x10; // -7.0
        /* 0x14 */ s16 mField_0x14; // 90
        /* 0x16 */ s16 mField_0x16; // 90
        /* 0x18 */ s16 mField_0x18; // 3
        /* 0x1A */ s16 mField_0x1A; // 0
    };

    static f32 m_div_num;
    static m_data_t m_data;

    ~daFallRockTag_c() { cDyl_Unlink(fpcNm_FallRock_e); }

    inline m_data_t* getData();
    void createRock(cXyz*, cXyz*, csXyz*, int, unsigned long);

public:
    /* 0x290 */ u8 m290[0x298 - 0x290];
    /* 0x298 */ s32 mTimer;
    /* 0x29C */ u8 m29C[0x29E - 0x29C];
    /* 0x29E */ u8 mSchbitFlag;
    /* 0x29F */ u8 m29F;
};  // Size: 0x2A0

#endif /* D_A_FALLROCK_TAG_H */
