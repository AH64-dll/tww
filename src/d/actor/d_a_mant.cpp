/**
 * d_a_mant.cpp
 * Object - Phantom Ganon's cape/Darknut cape
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mant.h"
#include "d/d_com_inf_game.h"
#include "d/d_cc_d.h"
#include "d/d_cc_uty.h"
#include "d/d_kankyo.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_audio.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_bg_s.h"
#include "d/d_bg_s.h"
#include "d/d_bg_s_gnd_chk.h"
#include "dolphin/gf/GFGeometry.h"
#include "dolphin/gf/GFTev.h"
#include "dolphin/gf/GFTransform.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/J3DGraphBase/J3DShape.h"
#include "JSystem/JMath/JMATrigonometric.h"
#include <math.h>

/* Unreferenced static data at the start of the original .data:
   @2100/@2080 (weak_data.h fake_data_2100/2080), @1811 (attnFnTbl),
   sqrtf localstatics -- all emitted via dolzel.pch (DECOMPCTX). */

#include "assets/l_pg_mantle1TEX.h"
#include "assets/l_pg_mantle1_palettePAL.h"
#include "assets/l_tn_boro_b1TEX.h"
#include "assets/l_tn_boro_b1_palettePAL.h"
#include "assets/l_tn_boro_k1TEX.h"
#include "assets/l_tn_boro_k1_palettePAL.h"
#include "assets/l_tn_boro1TEX.h"
#include "assets/l_tn_boro1_palettePAL.h"
#include "assets/l_tn_mantle1TEX.h"
#include "assets/l_tn_mantle1_palettePAL.h"
const u16 l_tn_boro1TEX__width = 128;
const u16 l_tn_boro1TEX__height = 128;
const u16 l_pg_mantle1TEX__width = 128;
const u16 l_pg_mantle1TEX__height = 128;

#include "assets/l_pos__d_a_mant.h"
#include "assets/l_texCoord__d_a_mant.h"
#include "assets/l_DL__d_a_mant.h"
#include "assets/l_matDL__d_a_mant.h"
l_matDL__d_a_mant(l_tn_boro1TEX);
#include "assets/l_matDL2__d_a_mant.h"
l_matDL2__d_a_mant(l_tn_boro1TEX);
#include "assets/l_matDL_LIGHTOFF__d_a_mant.h"
l_matDL_LIGHTOFF__d_a_mant(l_pg_mantle1TEX);

static void* tex_d[] = {
    l_tn_mantle1TEX,
    l_tn_boro1TEX,
    l_tn_boro_b1TEX,
    NULL,
    l_tn_boro_k1TEX,
    NULL,
    l_pg_mantle1TEX,
};

static void* pal_d[] = {
    l_tn_mantle1_palettePAL,
    l_tn_boro1_palettePAL,
    l_tn_boro_b1_palettePAL,
    NULL,
    l_tn_boro_k1_palettePAL,
    NULL,
    l_pg_mantle1_palettePAL,
};

/* .bss:0x0  weak_bss_3569 (cXyz, via dolzel.pch) */
/* .bss:0xC  16x weak_bss_936_to_1036 u8s 4-aligned (via dolzel.pch) */
static cXyz* l_v_pos;
static s32 l_v_count;
static s32 l_mesh_cc_ct;
/* .bss:0x58 DestructorChain regmem for l_non_pos (compiler-emitted) */
static cXyz l_non_pos(-20000.0f, -200000.0f, -100000.0f);

/* 000000EC-000003EC       .text draw__15daMant_packet_cFv */
void daMant_packet_c::draw() {
static GXVtxDescList l_vtxDescList[] = {
    {GX_VA_POS, GX_INDEX8},
    {GX_VA_NRM, GX_INDEX8},
    {GX_VA_TEX0, GX_INDEX8},
    {GX_VA_NULL, GX_NONE},
};

static GXVtxAttrFmtList l_vtxAttrFmtList[] = {
    {GX_VA_POS, GX_POS_XYZ, GX_F32, 0},
    {GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0},
    {GX_VA_TEX0, GX_TEX_ST, GX_F32, 0},
    {GX_VA_NULL, GX_CLR_RGBA, GX_F32, 0},
};

    GXTlutObj tlutObj;
    GXTexObj texObj;
    void* tex = tex_d[mTexNo];
    void* pal = pal_d[mTexNo];

    j3dSys.reinitGX();
    GXSetNumIndStages(0);
    dKy_GxFog_tevstr_set(mTevstr);
    dKy_setLight_mine(mTevstr);
    GFSetVtxDescv(l_vtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_vtxAttrFmtList);
    GFSetArray(GX_VA_POS, &mPosArr[mType * (0x3CC / 0xC)], sizeof(cXyz));
    GFSetArray(GX_VA_NRM, &mNrmArr[mType * (0x3CC / 0xC)], sizeof(cXyz));
    GFSetArray(GX_VA_TEX0, l_texCoord, sizeof(cXy));

    GXInitTlutObj(&tlutObj, pal, GX_TL_RGB5A3, 0x100);
    GXInitTexObjCI(&texObj, tex, 0x80, 0x80, GX_TF_C4, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTlut(&tlutObj, GX_TLUT0);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    GXColor tevColor = {0xFF, 0xFF, 0xFF, 0xFF};
    if (mFlag == 1) {
        GXColorS10 tevColorS10 = {0xFF, 0xFF, 0xFF, 0xFF};
        GFSetTevColorS10(GX_TEVREG0, tevColorS10);
        GFSetTevColor(GX_TEVREG1, tevColor);
        GXCallDisplayList(l_matDL_LIGHTOFF, 0x80);
        GFLoadPosMtxImm(mMtx, 0);
        Mtx mtx;
        mDoMtx_inverseTranspose(mMtx, mtx);
        GFLoadNrmMtxImm(mtx, 0);
        GXCallDisplayList(l_DL, 0x1E0);
    } else {
        GXColorS10 tevColorS10 = {55, 55, 55, 0xFF};
        GFSetTevColorS10(GX_TEVREG0, tevColorS10);
        GFSetTevColor(GX_TEVREG1, tevColor);
        GXCallDisplayList(l_matDL, 0xA0);
        GFLoadPosMtxImm(mMtx, 0);
        Mtx mtx;
        mDoMtx_inverseTranspose(mMtx, mtx);
        GFLoadNrmMtxImm(mtx, 0);
        GXCallDisplayList(l_DL, 0x1E0);

        tevColorS10.r = 30;
        tevColorS10.g = 30;
        tevColorS10.b = 30;
        tevColor.r = 0;
        tevColor.g = 0;
        tevColor.b = 0;
        GFSetTevColorS10(GX_TEVREG0, tevColorS10);
        GFSetTevColor(GX_TEVREG1, tevColor);
        GXCallDisplayList(l_matDL2, 0x40);
        GFLoadPosMtxImm(mMtx2, 0);
        mDoMtx_inverseTranspose(mMtx2, mtx);
        GFLoadNrmMtxImm(mtx, 0);
        GXCallDisplayList(l_DL, 0x1E0);
    }
    mType ^= 1;
    J3DShape::resetVcdVatCache();
}

/* 000003EC-000004E8       .text daMant_Draw__FP10mant_class */
static BOOL daMant_Draw(mant_class* i_this) {
    if (i_this->scale.y <= 0.01f) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_BG0_FULL, &i_this->current.pos, &i_this->tevStr);
    MtxTrans(0.0f, 0.0f, 0.0f, 0);
    cMtx_concat(j3dSys.getViewMtx(), *calc_mtx, i_this->mPacket.getMtx());
    if (i_this->m1244 != mant_class::Type_PHANTOM_GANON_e) {
        MtxTrans(0.0f, -3.0f, 0.0f, 0);
        cMtx_concat(j3dSys.getViewMtx(), *calc_mtx, i_this->mPacket.getMtx2());
    }
    i_this->mPacket.mTevstr = &i_this->tevStr;
    j3dSys.getDrawBuffer(0)->entryImm(&i_this->mPacket, 0);
    return TRUE;
}

/* 000004E8-00000FC0       .text joint_control__FP10mant_classP8mant_j_si */
void joint_control(mant_class* i_this, mant_j_s* i_joint, int i_idx) {
static f32 l_d_p[] = {
    0.6f, 0.4f, 0.3f, 0.3f, 0.2f, 0.2f, 0.2f, 0.1f,
};

static f32 l_d_p2[] = {
    5.0f, 2.0f, 1.0f, 0.5f, 0.0f, -0.3f, -0.3f, 0.0f,
};

    dBgS_GndChk gndChk;
    cXyz pos(i_joint->mPos[0].x, i_joint->mPos[0].y + 50.0f, i_joint->mPos[0].z);
    gndChk.SetPos(&pos);
    f32 f30 = 1.5f + dComIfG_Bgsp()->GroundCross(&gndChk);
    if (f30 - i_joint->mPos[0].y > 50.0f) {
        f30 = i_joint->mPos[0].y;
    }

    cXyz local_84(0.0f, 0.0f, 0.0f);
    cXyz local_78(0.0f, 0.0f, 0.0f);
    cXyz local_6C(0.0f, 0.0f, 0.0f);

    mDoMtx_YrotS(*calc_mtx, i_joint->mRot.y);

    cXyz local_B4(0.0f, 0.0f, -5.0f);
    cXyz local_9C;
    MtxPosition(&local_B4, &local_9C);

    cXyz local_54(0.0f, 0.0f, 0.0f);

    s16 angle = i_this->m1C0C + (s16)((i_idx - 4) * 0xBB8);
    mDoMtx_YrotS(*calc_mtx, angle);
    cXyz local_B4_2(0.0f, 0.0f, i_this->m1C00);
    s16 diff = angle - i_joint->mRot.y;
    if (diff < 0) {
        diff = -diff;
    }
    f32 f29;
    if ((u16)diff < 0x4000) {
        local_B4_2.z *= 0.05f;
        f29 = 0.0f;
    } else {
        f29 = 1.0f;
    }
    cXyz local_60;
    MtxPosition(&local_B4_2, &local_60);

    cXyz local_B4_3(0.0f, 0.0f, 0.0f);
    local_B4_3.z = (i_this->m1BF8 + cM_ssin((s16)(i_idx * 0x59D8))) * i_this->scale.y;

    s32 i = 0;
    s32 phase = 0;
    s32 dp_idx = 0;
    s32 base = i_idx * 0x2710;
    dCcS* ccS = dComIfG_Ccsp();

    for (i = 0; i < 9; i++, phase += 0x2710, dp_idx += 4) {
        cXyz* p_pos = &i_joint->mPos[i];
        cXyz* p_speed = &i_joint->mSpeed[i];

        if (i > 0) {
            cXyz local_48 = i_joint->mPos[i] * l_d_p[i - 1];
            cXyz local_90(local_48.x, local_48.y, local_48.z);

            f32 wind = i_this->m1C00;
            if (std::fabsf(wind) > 0.1f) {
                cXyz local_54_2 = local_60;
                local_54_2.y = 0.5f * wind * cM_ssin((s16)((i_this->m1248 << 0xC) + (phase + base)));
                local_54 = local_54_2;
            }

            if (i_this->m1C04 > 0.01f) {
                cXyz local_3C = local_9C * l_d_p2[i - 1];
                cXyz local_30 = local_3C * i_this->m1C04;
                cXyz local_24 = local_30 * f29;
                local_84 = local_24;
            }

            if (i_this->m1244 == mant_class::Type_PHANTOM_GANON_e) {
                local_78.z = 2.0f * cM_ssin((s16)((i_this->m1248 << 0xB) + (phase + base)));
                mDoMtx_YrotS(*calc_mtx, i_joint->mRot.y);
                MtxPosition(&local_78, &local_6C);
            }

            f32 f31 = local_6C.x + (local_84.x + (local_54.x + (local_90.x + (p_speed->x + (p_pos->x - i_joint->mPos[i - 1].x)))));
            f32 f27 = local_6C.z + (local_84.z + (local_54.z + (local_90.z + (p_speed->z + (p_pos->z - i_joint->mPos[i - 1].z)))));
            f32 f1 = local_54.y + (i_this->m1C08 + (p_pos->y + p_speed->y));
            if (f1 < f30) {
                f1 = f30;
            }
            f32 f28 = f1 - i_joint->mPos[i - 1].y;

            s16 x_angle = -cM_atan2s(f28, f27);
            f32 dist = f28 * f28 + f27 * f27;
            if (dist > 0.0f) {
                dist = std::sqrtf(dist);
            }
            s16 y_angle = cM_atan2s(f31, dist);
            mDoMtx_XrotS(*calc_mtx, x_angle);
            mDoMtx_YrotM(*calc_mtx, y_angle);
            cXyz local_A8;
            MtxPosition(&local_B4, &local_A8);

            *p_speed = *p_pos;
            p_pos->x += local_A8.x;
            p_pos->y += local_A8.y;
            p_pos->z += local_A8.z;
            p_speed->x = i_this->m1BFC * (p_pos->x - p_speed->x);
            p_speed->y = i_this->m1BFC * (p_pos->y - p_speed->y);
            p_speed->z = i_this->m1BFC * (p_pos->z - p_speed->z);
        }

        *l_v_pos = *p_pos;
        l_v_pos++;
        l_v_count++;

        if (i_this->m1244 == mant_class::Type_DARKNUT_e && !(i & 1) && !(i_idx & 1) && i != 0 && i != 8 && i_idx != 0 && i_idx != 8) {
            dCcD_Sph* sph = &i_this->mMeshSph[l_mesh_cc_ct];
            if (i_this->m2834 != 0) {
                sph->SetR(30.0f);
                sph->SetC(*p_pos);
            } else {
                sph->SetR(-200.0f);
                sph->SetC(l_non_pos);
            }
            ccS->Set(sph);

            if (i_this->m2836 == 0 && i_this->m2838 == 0 && sph->ChkTgHit()) {
                i_this->m2836 = 0xA;
                CcAtInfo atInfo;
                atInfo.mpObj = sph->GetTgHitObj();
                at_power_check(&atInfo);
                fopAc_ac_c* player = dComIfGp_getPlayer(0);
                s32 res = 0;
                if (atInfo.mResultingAttackType == 1 || atInfo.mResultingAttackType == 2) {
                    if (atInfo.mResultingAttackType == 2) {
                        if (i_this->mPacket.mTexNo == 0) {
                            i_this->mPacket.mTexNo = 2;
                            i_this->m2834 = 0;
                            res = 1;
                        }
                    } else if (i_this->mPacket.mTexNo == 0) {
                        i_this->mPacket.mTexNo = 4;
                        i_this->m2834 = 0;
                        res = 1;
                    }
                }
                if (res != 0) {
                    csXyz angle = i_this->current.angle;
                    angle.x += 0x8000;
                    dComIfGp_particle_set(0x81B6, p_pos, &angle, NULL, 0xFF, NULL, i_this->current.roomNo,
                                          &i_this->tevStr.mColorK0, &i_this->tevStr.mColorK0, NULL);
                    mDoAud_seStart(0x58ED, &i_this->current.pos, 0, dComIfGp_getReverb(i_this->current.roomNo));
                }
                i_this->m1C0E = 2;
                i_this->m1C0C = player->shape_angle.y;
                i_this->m1C00 = 10.0f;
                if (atInfo.mResultingAttackType == 5) {
                    i_this->m2838 = 0x1A;
                    i_this->m1C0E = 6;
                    return;
                }
            }
            l_mesh_cc_ct++;
            if (i == 4 && i_idx == 4) {
                i_this->mWindSph.SetR(200.0f);
                i_this->mWindSph.SetC(*p_pos);
                ccS->Set(&i_this->mWindSph);
            }
        }
    }
}

/* 0000137C-000015F0       .text mant_v_calc__FP10mant_class */
void mant_v_calc(mant_class* i_this) {
    csXyz angle(0, 0, 0);
    cXyz offset;
    cXyz mtx_pos;
    cXyz diff = i_this->m1BE0 - i_this->m1BEC;
    angle.y = cM_atan2s(diff.x, diff.z) + 0x4000;

    mant_j_s* joint = i_this->mJoint;
    offset.x = 0.0f;

    for (s32 i = 0; i < 9; i++, joint++) {
        i_this->mJoint[i].mPos[0].x = i_this->m1BEC.x + (diff.x / 8.0f) * (f32)i;
        i_this->mJoint[i].mPos[0].y = i_this->m1BEC.y + (diff.y / 8.0f) * (f32)i;
        i_this->mJoint[i].mPos[0].z = i_this->m1BEC.z + (diff.z / 8.0f) * (f32)i;

        mDoMtx_YrotS(*calc_mtx, angle.y);

        s16 sin_angle = cM_rad2s(0.3926991f * (f32)i);
        f32 sin_val = jmaSinTable[(u16)sin_angle >> jmaSinShift];

        offset.y = -10.0f * sin_val;
        offset.z = -20.0f * sin_val;

        MtxPosition(&offset, &mtx_pos);
        i_this->mJoint[i].mPos[0] += mtx_pos;

        i_this->mJoint[i].mRot = angle;
        i_this->mJoint[i].mRot.y += (s16)((i - 4) * 0xBB8);

        joint_control(i_this, joint, i);
    }
}

/* 000015F0-000017EC       .text mant_n_calc__FP10mant_class */
void mant_n_calc(mant_class* i_this) {
    s16 angle;
    cXyz local_20;
    cXyz cStack_2c;
    cXyz local_44;
    volatile f32 tmp;

    local_20.x = 0.0f;
    local_20.y = 0.0f;
    local_20.z = 1.0f;

    mDoMtx_YrotS(*calc_mtx, 0x4FA0);
    MtxPosition(&local_20, &cStack_2c);

    cXyz* pcVar3 = (cXyz*)((u8*)i_this + 0x310 + i_this->mPacket.mType * 0x3CC);
    cXyz* pDst = (cXyz*)((u8*)i_this + 0xAA8 + i_this->mPacket.mType * 0x3CC);
    for (int i = 0; i < 0x51; i++, pcVar3++, pDst++) {
        if (((((i == 8) || (i == 0x11)) || (i == 0x1a)) || ((i == 0x23 || (i == 0x2c)))) ||
           ((i == 0x35 || ((i == 0x3e || (i == 0x47)))))) {
            pDst->x = pDst[-1].x;
            pDst->y = pDst[-1].y;
            pDst->z = pDst[-1].z;
        } else if (!(i < 0x48)) {
            pDst->x = pDst[-9].x;
            pDst->y = pDst[-9].y;
            pDst->z = pDst[-9].z;
        } else {
            local_44 = pcVar3[10] - pcVar3[0];
            angle = cM_atan2s(local_44.x, local_44.z);
            mDoMtx_YrotS(*calc_mtx, angle);
            {
                f32 dVar5 = local_44.x * local_44.x + local_44.z * local_44.z;
                if (dVar5 > 0.0f) {
                    const double half = 0.5;
                    const double three = 3.0;
                    double guess = __frsqrte(dVar5);
                    guess = half * guess * (three - guess * guess * dVar5);
                    guess = half * guess * (three - guess * guess * dVar5);
                    guess = half * guess * (three - guess * guess * dVar5);
                    tmp = (f32)(dVar5 * guess);
                    dVar5 = tmp;
                }
                mDoMtx_XrotM(*calc_mtx, -cM_atan2s(local_44.y, dVar5));
            }
            MtxPosition(&cStack_2c, pDst);
        }
    }
}

/* 000017EC-000019C0       .text mant_move__FP10mant_class */
void mant_move(mant_class* i_this) {
    l_v_count = 0;
    l_v_pos = (cXyz*)(&((cXyz*)((u8*)i_this + 0x310))[i_this->mPacket.mType * 81]);
    l_mesh_cc_ct = 0;
    mant_v_calc(i_this);
    mant_n_calc(i_this);
    {
        u8* base = (u8*)i_this;
        base += i_this->mPacket.mType * 0x3CC;
        DCStoreRangeNoSync(base + 0x310, 0x3CC);
    }

    if (i_this->m2838 != 0) {
        i_this->m2838--;
        u8* base = (u8*)i_this;
        base += i_this->mPacket.mType * 0x3CC;
        cXyz* pos = (cXyz*)(base + 0x310);
        for (s32 i = 0; i < 0x51; i++) {
            if ((i & 3) == 0) {
                dComIfGp_particle_setSimple(0x8069, pos, 0xFF, g_whiteColor, g_whiteColor, 0);
            }
            pos++;
        }
        if (i_this->m2838 <= 2) {
            fopAcM_delete(i_this);
            return;
        }
    }

    cLib_addCalc2(&i_this->m1BF8, 30.0f, 0.1f, 1.0f);
    cLib_addCalc2(&i_this->m1BFC, 0.7f, 0.1f, 0.05f);
    if (i_this->mWindSph.ChkTgHit()) {
        i_this->m1C0E = 0xA;
        i_this->m1C0C = dComIfGp_getPlayer(0)->shape_angle.y;
    }
    if (i_this->m1C0E != 0) {
        i_this->m1C0E--;
        cLib_addCalc2(&i_this->m1C00, 50.0f, 0.2f, 1.5f);
    } else {
        cLib_addCalc0(&i_this->m1C00, 0.1f, 1.0f);
    }
    if (i_this->m1C0E > 4) {
        cLib_addCalc2(&i_this->m1C04, 1.0f, 1.0f, 1.0f);
    } else {
        cLib_addCalc0(&i_this->m1C04, 0.1f, 0.1f);
    }
}

/* 000019C0-00001A3C       .text daMant_Execute__FP10mant_class */
static BOOL daMant_Execute(mant_class* i_this) {
    i_this->m1248++;
    if (i_this->m2836 != 0) {
        i_this->m2836--;
    }
    mant_move(i_this);
    MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, 0);
    PSMTXCopy(*calc_mtx, i_this->mBaseMtx);
    return TRUE;
}

/* 00001A3C-00001A44       .text daMant_IsDelete__FP10mant_class */
static BOOL daMant_IsDelete(mant_class*) {
    return TRUE;
}

/* 00001A44-00001A4C       .text daMant_Delete__FP10mant_class */
static BOOL daMant_Delete(mant_class*) {
    return TRUE;
}

/* 00001A4C-00001D18       .text daMant_Create__FP10fopAc_ac_c */
static cPhs_State daMant_Create(fopAc_ac_c* pActor) {
    static dCcD_SrcSph wind_cc_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WIND,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 200.0f,
    }},
};
    static dCcD_SrcSph mesh_cc_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
    }},
};

    mant_class* i_this = static_cast<mant_class*>(pActor);
    fopAcM_ct(i_this, mant_class);

    i_this->m1244 = fopAcM_GetParam(i_this) & 0xFF;
    i_this->cull.box.min.x = -2000.0f;
    i_this->cull.box.min.y = -2000.0f;
    i_this->cull.box.min.z = -2000.0f;
    i_this->cull.box.max.x = 2000.0f;
    i_this->cull.box.max.y = 2000.0f;
    i_this->cull.box.max.z = 2000.0f;
    i_this->cullMtx = i_this->mBaseMtx;
    i_this->mPacket.mFlag = i_this->m1244;
    if (i_this->m1244 == mant_class::Type_PHANTOM_GANON_e) {
        i_this->m1BF8 = 40.0f;
        i_this->m1BFC = 0.8f;
        i_this->m1C08 = -5.0f;
        i_this->mPacket.mTexNo = 6;
    } else {
        i_this->m1BF8 = 30.0f;
        i_this->m1BFC = 0.7f;
        i_this->m1C08 = -10.0f;
        i_this->mStts.Init(0xC8, 0xFF, i_this);
        i_this->mWindSph.Set(wind_cc_sph_src);
        i_this->mWindSph.SetStts(&i_this->mStts);
        for (s32 i = 0; i < 9; i++) {
            i_this->mMeshSph[i].Set(mesh_cc_sph_src);
            i_this->mMeshSph[i].SetStts(&i_this->mStts);
        }
        i_this->m2834 = 0xA;
    }
    i_this->scale.x = 1.0f;
    i_this->scale.y = 1.0f;
    i_this->scale.z = 1.0f;
    for (s32 i = 0; i < 10; i++) {
        daMant_Execute(i_this);
    }
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daMant_Method = {
    (process_method_func)daMant_Create,
    (process_method_func)daMant_Delete,
    (process_method_func)daMant_Execute,
    (process_method_func)daMant_IsDelete,
    (process_method_func)daMant_Draw,
};

actor_process_profile_definition g_profile_MANT = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_MANT_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(mant_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_MANT_e,
    /* Actor SubMtd */ &l_daMant_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
