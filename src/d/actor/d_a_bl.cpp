/**
 * d_a_bl.cpp
 * Enemy - Bubble
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bl.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_kankyo.h"
#include "d/d_material.h"
#include "d/d_path.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "SSystem/SComponent/c_math.h"
#include "d/d_bg_s.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_camera_mng.h"
#include "d/d_s_play.h"
#include "SSystem/SComponent/c_data_tbl.h"
#include "string.h"

static dCcD_SrcSph body_co_sph_src = {
    // dCcD_SrcGObjInf
    {
        // cCcD_SrcObj
        {
            /* mFlags */ 0,
            // cCcD_SrcObjHitInf
            {
                // cCcD_SrcObjAt
                {
                    /* mType */ 0x200,
                    /* mAtp */ 0x01,
                    /* mBase.mSPrm */ 0x5,
                },
                // cCcD_SrcObjTg
                {
                    /* mType */ 0xFF3DFEFF,
                    /* mBase.mSPrm */ 0x3,
                },
                // cCcD_SrcObjCo
                {
                    /* mBase.mSPrm */ 0x75,
                },
            },
        },
        // dCcD_SrcGObjAt
        {
            /* mSe */ 0x04,
            /* mHitMark */ 0,
            /* mSpl */ 0,
            /* mMtrl */ 0,
            /* mBase */ {0},
        },
        // dCcD_SrcGObjTg
        {
            /* mSe */ 0,
            /* mHitMark */ 0,
            /* mSpl */ 0,
            /* mMtrl */ 0x06,
            /* mBase */ {0},
        },
        // dCcD_SrcGObjCo
        {
            /* mBase */ {0},
        },
    },
    // cCcD_SrcSphAttr
    {
        // cM3dGSphS
        {
            /* mCenter */ {0.0f, 0.0f, 0.0f},
            /* mRadius */ 15.0f,
        },
    },
};

static const u8 fire_j[10] = {0, 1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const f32 fire_sc[10] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

/* 00000078-00000178       .text draw_SUB__FP8bl_class */
void draw_SUB(bl_class* i_this) {
    /* Nonmatching */
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(i_this->scale);
    MtxTrans(i_this->current.pos.x, i_this->current.pos.y + i_this->m314, i_this->current.pos.z, 0);
    mDoMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->shape_angle.x);
    mDoMtx_ZrotM(*calc_mtx, i_this->shape_angle.z);
    MtxTrans(0.0f, -i_this->m314, 0.0f, 1);
    PSMTXCopy(*calc_mtx, model->getBaseTRMtx());
    i_this->mpMorf->calc();
    enemy_fire(&i_this->mEnemyFire);
    g_env_light.settingTevStruct(0, &i_this->current.pos, &i_this->tevStr);
}

/* 00000178-000002F8       .text daBL_Draw__FP8bl_class */
static BOOL daBL_Draw(bl_class* i_this) {
    /* Nonmatching */
    J3DModel* model = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(model, &i_this->tevStr);

    if (i_this->m2D5 != 0xFF && !dComIfGs_isSwitch(i_this->m2D5, dComIfGp_roomControl_getStayNo())) {
        return TRUE;
    }

    dSnap_RegistFig(0xB4, i_this, 1.0f, 1.0f, 1.0f);

    if (i_this->mEnemyIce.mFreezeTimer > 0x14) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, &i_this->mInvisibleModel);
        return TRUE;
    }

    if (i_this->m2D3 == 0) {
        i_this->mpBtk2->entry(model->getModelData());
    } else {
        i_this->mpBtk1->entry(model->getModelData());
    }

    i_this->mpMorf->entryDL();

    if (i_this->health > 0) {
        dComIfGd_setSimpleShadow2(&i_this->current.pos, i_this->mAcch.GetGroundH(), 30.0f, i_this->mAcch.m_gnd, 0,
                                  1.0f, dDlst_shadowControl_c::getSimpleTex());
    }

    if (i_this->m2D3 == 0) {
        i_this->mpBtk2->remove(model->getModelData());
    } else {
        i_this->mpBtk1->remove(model->getModelData());
    }

    return TRUE;
}

/* 000002F8-000003F8       .text smoke_set__FP8bl_class */
void smoke_set(bl_class* i_this) {
    /* Nonmatching */
    if (i_this->mSmokeCB.getEmitter() == NULL) {
        s8 roomNo = i_this->current.roomNo;
        dComIfGp_particle_setToon(0x2027, (const cXyz*)i_this->m6BC, &i_this->shape_angle, NULL, 0xB9,
                                  &i_this->mSmokeCB, roomNo, NULL, NULL, NULL);
    }

    if (i_this->mSmokeCB.getEmitter() != NULL) {
        GXColor color = { 0xB4, 0x80, 0xA0, 0xA0 };
        i_this->mSmokeCB.getEmitter()->setGlobalParticleScale(JGeometry::TVec3<f32>(1.6f, 1.6f, 1.6f));
        i_this->mSmokeCB.getEmitter()->setRate(10.0f);
        i_this->mSmokeCB.getEmitter()->setMaxFrame(1);
        i_this->mSmokeCB.getEmitter()->setAwayFromCenterSpeed(8.0f);
        i_this->mSmokeCB.getEmitter()->becomeImmortalEmitter();
        i_this->mSmokeCB.setColor(color);
    }
}

/* 000003F8-000004AC       .text fire_move_set__FP8bl_class */
void fire_move_set(bl_class* i_this) {
    /* Nonmatching */
    u16 particleId = i_this->m2D0 == 0 ? 0x8124 : 0x8123;

    if (i_this->mFollowCB2.getEmitter() == NULL) {
        g_dComIfG_gameInfo.play.getParticle()->set(0, particleId, &i_this->current.pos, NULL, NULL, 0xFF,
                                                   &i_this->mFollowCB2, i_this->current.roomNo, NULL, NULL, NULL);
        if (i_this->m2D0 == 1) {
            i_this->mSph.SetTgSe(5);
            i_this->mSph.SetTgHitMark(dCcg_TgHitMark_Purple_e);
            i_this->mSph.OnTgShield();
        }
    }
}

/* 000004AC-00000578       .text fire_emitter_clr__FP8bl_class */
void fire_emitter_clr(bl_class* i_this) {
    /* Nonmatching */
    JPABaseEmitter* emitter = i_this->mFollowCB2.getEmitter();
    if (emitter != NULL && i_this->m2F0 == 0) {
        if (i_this->m2D0 == 0) {
            JPAGetXYZRotateMtx(0, (s16)(dComIfGp_getPlayer(0)->shape_angle.y + 0x8000), 0, emitter->mGlobalRotation);
            i_this->mFollowCB2.getEmitter()->setRate(3.0f);
            i_this->mFollowCB2.getEmitter()->setLifeTime(0xA);
            i_this->mFollowCB2.getEmitter()->setDirectionalSpeed(50.0f);
            i_this->m2F0 = 0x15;
        } else {
            i_this->m2F0 = 1;
        }
    }

    i_this->mFollowCB1.remove();
}

/* 00000578-000006E0       .text fire_kaiten_keisan__FP8bl_class */
void fire_kaiten_keisan(bl_class* i_this) {
    /* Nonmatching */
    JPABaseEmitter* emitter = i_this->mFollowCB2.getEmitter();
    if (emitter != NULL) {
        if (i_this->m2D0 == 0) {
            JPASetRMtxTVecfromMtx(i_this->mpMorf->getModel()->getAnmMtx(0), emitter->mGlobalRotation, emitter->mGlobalTranslation);
            JAIZelBasic::zel_basic->seStart(0x7023, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f,
                                            -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x7024, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f,
                                            -1.0f, -1.0f, 0);
            camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
            PSMTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0), *calc_mtx);
            mDoMtx_YrotM(*calc_mtx, (s16)(fopCamM_GetAngleY(camera) - i_this->shape_angle.y));
            JPASetRMtxTVecfromMtx(*calc_mtx, emitter->mGlobalRotation, emitter->mGlobalTranslation);
        }
    }
}

/* 000006E0-00000820       .text shock_damage_check__FP8bl_class */
BOOL shock_damage_check(bl_class* i_this) {
    /* Nonmatching */
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (!(i_this->m2D0 & 0x80) && i_this->m2D3 == 0) {
        return FALSE;
    }

    if (!(player->mResetFlg0 & 0x20000)) {
        return FALSE;
    }

    cXyz swordPos = player->getSwordTopPos();
    cXyz dist;
    dist.x = swordPos.x - i_this->current.pos.x;
    dist.z = swordPos.z - i_this->current.pos.z;
    f32 distSq = dist.x * dist.x + dist.z * dist.z;
    if (distSq > 0.0f) {
        distSq = std::sqrtf(distSq);
    }

    if (distSq < 1000.0f) {
        i_this->m2F0 = 0;
        fire_emitter_clr(i_this);
        return TRUE;
    }

    return FALSE;
}

/* 00000820-0000094C       .text anm_init__FP8bl_classifUcfi */
void anm_init(bl_class* i_this, int i_anmIdx, f32 i_morf, u8 i_playMode, f32 i_playSpeed, int i_anmDataIdx) {
    /* Nonmatching */
    i_this->m308 = i_anmIdx;
    if (i_anmDataIdx >= 0) {
        void* anmData = dComIfG_getObjectRes("BL", i_anmDataIdx);
        void* anmData2 = dComIfG_getObjectRes("BL", i_anmIdx);
        i_this->mpMorf->setAnm((J3DAnmTransform*)anmData2, i_playMode, i_morf, i_playSpeed, 0.0f, -1.0f, anmData);
    } else {
        void* anmData = dComIfG_getObjectRes("BL", i_anmIdx);
        i_this->mpMorf->setAnm((J3DAnmTransform*)anmData, i_playMode, i_morf, i_playSpeed, 0.0f, -1.0f, NULL);
    }
}

/* 0000094C-00000BF4       .text skull_atari_check__FP8bl_class */
s32 skull_atari_check(bl_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    i_this->mStts.Move();
    if (i_this->health == 0) {
        return TRUE;
    }

    if (shock_damage_check(i_this)) {
        i_this->m2D2 = 3;
        i_this->m306 = 0x22;
        return TRUE;
    }

    if (!i_this->mSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->m2F4 != 0) {
        return FALSE;
    }

    i_this->current.angle.y = fopAcM_searchActorAngleY(i_this, player) + 0x8000;
    i_this->m2F4 = 8;
    i_this->m2D4 = 0;
    u8 flag = 0;

    switch (hitObj->GetAtType()) {
    case 0x2:
        i_this->m2D4 = 6;
        break;
    case 0x200000:
        flag = 1;
        i_this->m2D4 = 1;
        i_this->m2D2 = 3;
        i_this->m306 = 0x24;
        break;
    case 0x10000:
        i_this->m2D4 = 4;
        if (((daPy_py_c*)player)->mCutType == 0x11) {
            i_this->current.angle.y = player->shape_angle.y - 0x4000;
            i_this->m2D4 = 5;
            i_this->speed.y = 30.0f;
            i_this->speedF = 20.0f;
        }
        break;
    case 0x40:
    case 0x80:
        i_this->m2D4 = 3;
        break;
    case 0x20:
        i_this->speed.y = 30.0f;
        /* fallthrough */
    case 0x200:
        i_this->mEnemyFire.mFireDuration = 0x3E8;
        break;
    case 0x8000:
        flag = 1;
        i_this->m2D4 = 7;
        i_this->m2D2 = 5;
        i_this->m306 = 0x3C;
        break;
    }

    cXyz hitPos = *i_this->mSph.GetTgHitPosP();
    if (flag == 0) {
        JAIZelBasic::zel_basic->seStart(0x692B, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        i_this->health = 0;
        i_this->attention_info.flags = 0;
        i_this->m2D2 = 0xA;
        i_this->m306 = 0x67;
    }
    return TRUE;
}

/* 00000C44-00001768       .text blue_body_atari_check__FP8bl_class */
s32 blue_body_atari_check(bl_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    i_this->mStts.Move();
    if (shock_damage_check(i_this)) {
        i_this->m2D2 = 3;
        i_this->m306 = 0x22;
        return TRUE;
    }

    if (!i_this->mSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->m2F4 != 0) {
        return FALSE;
    }

    i_this->current.angle.y = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0)) + 0x8000;
    u8 flag = 0;
    i_this->m2F4 = 8;
    i_this->m2D4 = 0;

    switch (hitObj->GetAtType()) {
    case 0x8000000:
        if (i_this->m2D3 != 0) {
            i_this->stealItemLeft = i_this->m2EA;
            if (i_this->stealItemLeft > 0) {
                s8 saveHealth = i_this->health;
                i_this->health = 0xA;
                CcAtInfo atInfo;
                atInfo.mpObj = i_this->mSph.GetTgHitObj();
                atInfo.mpActor = NULL;
                cc_at_check(i_this, &atInfo);
                i_this->health = saveHealth;
            }
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
            if (i_this->m2EA > 0) {
                i_this->m2EA--;
            }
            dComIfGp_particle_set(0x27B, &i_this->attention_info.position, NULL, NULL, 0xFF, NULL,
                                  -1, NULL, NULL, NULL);
            flag = 1;
        } else {
            i_this->stealItemLeft = 0;
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        break;
    case 0x2:
        if (i_this->m2D3 == 0) {
            JAIZelBasic::zel_basic->seStart(0x2803, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x2803, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        if (((daPy_py_c*)player)->mCutType == 6 || ((daPy_py_c*)player)->mCutType == 7 || ((daPy_py_c*)player)->mCutType == 8 ||
            ((daPy_py_c*)player)->mCutType == 9 || ((daPy_py_c*)player)->mCutType == 0xA || ((daPy_py_c*)player)->mCutType == 0xC ||
            ((daPy_py_c*)player)->mCutType == 0xE || ((daPy_py_c*)player)->mCutType == 5 || ((daPy_py_c*)player)->mCutType == 0xF ||
            ((daPy_py_c*)player)->mCutType == 0x10 || ((daPy_py_c*)player)->mCutType == 0x15 || ((daPy_py_c*)player)->mCutType == 0x17 ||
            ((daPy_py_c*)player)->mCutType == 0x19 || ((daPy_py_c*)player)->mCutType == 0x1A || ((daPy_py_c*)player)->mCutType == 0x1B ||
            ((daPy_py_c*)player)->mCutType == 0x1E || ((daPy_py_c*)player)->mCutType == 0x1F)
        {
            i_this->m2D4 = 6;
        }
        break;
    case 0x20:
        if (i_this->m2D3 == 0) {
            i_this->m2D4 = 2;
        }
        /* fallthrough */
    case 0x200000:
        flag = 1;
        i_this->m2D4 = 1;
        i_this->m2D2 = 3;
        i_this->m306 = 0x24;
        if (!(i_this->mAcch.m_flags & dBgS_Acch::GROUND_HIT) && i_this->gravity > -2.0f) {
            i_this->m306 = 0x1E;
        }
        break;
    case 0x10000:
        if (i_this->m2D3 == 0) {
            JAIZelBasic::zel_basic->seStart(0x2855, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x2855, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        i_this->m2D4 = 4;
        if (((daPy_py_c*)player)->mCutType == 0x11) {
            i_this->current.angle.y = player->shape_angle.y - 0x4000;
            i_this->m2D4 = 5;
        }
        if (i_this->m2D3 == 0) {
            i_this->health = 0;
        }
        break;
    case 0x80:
    case 0x40:
        flag = 1;
        if (i_this->m2D3 == 0) {
            JAIZelBasic::zel_basic->seStart(0x2833, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x2833, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        i_this->m2D4 = 3;
        break;
    case 0x40000:
    case 0x200:
        if (i_this->m2D3 == 0) {
            i_this->mEnemyFire.mFireDuration = 0x64;
            JAIZelBasic::zel_basic->seStart(0x588B, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
            fopAcM_monsSeStart(i_this, 0x4873, 0);
            i_this->mSph.ClrAtSet();
            i_this->mSph.ClrAtSet();
            i_this->attention_info.flags = 0;
            i_this->m2F0 = 0;
            fire_emitter_clr(i_this);
        }
        break;
    case 0x100000:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 40.0f;
        JAIZelBasic::zel_basic->seStart(0x588B, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        fopAcM_monsSeStart(i_this, 0x4873, 0);
        i_this->current.angle.x = 0;
        i_this->current.angle.z = 0;
        i_this->m2D3 = 0;
        i_this->shape_angle.x = 0;
        i_this->shape_angle.z = 0;
        i_this->gravity = 0.0f;
        i_this->speedF = 0.0f;
        i_this->m2EC = 0;
        i_this->speed.x = 0.0f;
        i_this->speed.y = 0.0f;
        i_this->speed.z = 0.0f;
        i_this->mSph.ClrAtSet();
        i_this->mSph.ClrAtSet();
        i_this->attention_info.flags = 0;
        i_this->m2F0 = 0;
        fire_emitter_clr(i_this);
        break;
    case 0x80000:
        flag = 1;
        if (i_this->m2D3 == 0) {
            i_this->m2D3 = 0;
            i_this->current.angle.x = 0;
            i_this->current.angle.z = 0;
            i_this->shape_angle.x = 0;
            i_this->shape_angle.z = 0;
            i_this->gravity = 0.0f;
            i_this->speedF = 0.0f;
            i_this->m2EC = 0;
            i_this->speed.x = 0.0f;
            i_this->speed.y = 0.0f;
            i_this->speed.z = 0.0f;
            i_this->mSph.ClrAtSet();
            i_this->mSph.ClrAtSet();
            i_this->mEnemyIce.mFreezeDuration = 0xC8;
            enemy_fire_remove(&i_this->mEnemyFire);
            i_this->attention_info.flags = 0;
        } else {
            i_this->m2D4 = 1;
            i_this->m2D2 = 3;
            i_this->m306 = 0x1E;
        }
        break;
    case 0x8000:
        flag = 1;
        if (i_this->m2D3 == 0) {
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        i_this->m2D4 = 7;
        i_this->m2D2 = 5;
        i_this->m306 = 0x3C;
        break;
    default:
        if (i_this->m2D3 == 0) {
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        break;
    }

    cXyz hitPos = *i_this->mSph.GetTgHitPosP();
    if (i_this->m2D3 != 0) {
        if (i_this->m2D4 != 7 && i_this->m2D4 != 1) {
            dComIfGp_particle_set(0xC, &hitPos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
            i_this->m2D2 = 2;
            i_this->m306 = 0x14;
            return TRUE;
        }
    }

    if (flag == 0) {
        CcAtInfo atInfo;
        atInfo.mpObj = i_this->mSph.GetTgHitObj();
        atInfo.mpActor = NULL;
        cc_at_check(i_this, &atInfo);
        if (i_this->m2D4 == 6 || i_this->m2D4 == 5 || i_this->m2D4 == 4 || i_this->health <= 0) {
            dComIfGp_particle_set(0x10, &hitPos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
            cXyz scale(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(0xF, &hitPos, &player->shape_angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
        } else {
            dComIfGp_particle_set(0xD, &hitPos, &player->shape_angle, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        }
        i_this->m2D2 = 4;
        i_this->m306 = 0x28;
    }
    return TRUE;
}

/* 00001768-000022BC       .text red_body_atari_check__FP8bl_class */
s32 red_body_atari_check(bl_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    i_this->mStts.Move();
    if (shock_damage_check(i_this)) {
        i_this->m2D2 = 3;
        i_this->m306 = 0x22;
        return TRUE;
    }

    if (!i_this->mSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->m2F4 != 0) {
        return FALSE;
    }

    i_this->current.angle.y = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0)) + 0x8000;
    u8 flag = 0;
    cXyz hitPos = *i_this->mSph.GetTgHitPosP();
    i_this->m2F4 = 8;
    i_this->m2D4 = 0;

    switch (hitObj->GetAtType()) {
    case 0x8000000:
        if (i_this->m2D3 != 0) {
            i_this->stealItemLeft = i_this->m2EA;
            if (i_this->stealItemLeft > 0) {
                s8 saveHealth = i_this->health;
                i_this->health = 0xA;
                CcAtInfo atInfo;
                atInfo.mpObj = i_this->mSph.GetTgHitObj();
                atInfo.mpActor = NULL;
                cc_at_check(i_this, &atInfo);
                i_this->health = saveHealth;
            }
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
            if (i_this->m2EA > 0) {
                i_this->m2EA--;
            }
            dComIfGp_particle_set(0x27B, &i_this->attention_info.position, NULL, NULL, 0xFF, NULL,
                                  -1, NULL, NULL, NULL);
            flag = 1;
        } else {
            i_this->stealItemLeft = 0;
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        break;
    case 0x2:
        i_this->m2D4 = 8;
        JAIZelBasic::zel_basic->seStart(0x2803, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        if (((daPy_py_c*)player)->mCutType == 6 || ((daPy_py_c*)player)->mCutType == 7 ||
            ((daPy_py_c*)player)->mCutType == 8 || ((daPy_py_c*)player)->mCutType == 9 ||
            ((daPy_py_c*)player)->mCutType == 0xA || ((daPy_py_c*)player)->mCutType == 0xC ||
            ((daPy_py_c*)player)->mCutType == 0xE || ((daPy_py_c*)player)->mCutType == 5 ||
            ((daPy_py_c*)player)->mCutType == 0xF || ((daPy_py_c*)player)->mCutType == 0x10 ||
            ((daPy_py_c*)player)->mCutType == 0x15 || ((daPy_py_c*)player)->mCutType == 0x17 ||
            ((daPy_py_c*)player)->mCutType == 0x19 || ((daPy_py_c*)player)->mCutType == 0x1A ||
            ((daPy_py_c*)player)->mCutType == 0x1B || ((daPy_py_c*)player)->mCutType == 0x1E ||
            ((daPy_py_c*)player)->mCutType == 0x1F)
        {
            i_this->m2D4 = 6;
        }
        break;
    case 0x20:
        if (i_this->m2D3 == 0) {
            i_this->m2D4 = 2;
        }
        /* fallthrough */
    case 0x200000:
        flag = 1;
        i_this->m2D4 = 1;
        i_this->m2D2 = 3;
        i_this->m306 = 0x24;
        if (!(i_this->mAcch.m_flags & dBgS_Acch::GROUND_HIT) && i_this->gravity > -2.0f) {
            i_this->m306 = 0x1E;
        }
        break;
    case 0x10000:
        JAIZelBasic::zel_basic->seStart(0x2855, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        i_this->m2D4 = 4;
        if (((daPy_py_c*)player)->mCutType == 0x11) {
            i_this->current.angle.y = player->shape_angle.y - 0x4000;
            i_this->m2D4 = 5;
        }
        i_this->health = 0;
        break;
    case 0x80:
    case 0x40:
        flag = 1;
        if (i_this->m2D3 == 0) {
            JAIZelBasic::zel_basic->seStart(0x2833, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x2833, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        i_this->m2D4 = 3;
        dComIfGp_particle_set(0xC, &hitPos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        break;
    case 0x40000:
    case 0x4000:
    case 0x200:
        if (i_this->m2D3 == 0 || !(hitObj->GetAtType() & 0x200)) {
            if (i_this->m2D3 == 0 && !(hitObj->GetAtType() & 0x4000)) {
                i_this->mEnemyFire.mFireDuration = 0x64;
            }
            JAIZelBasic::zel_basic->seStart(0x588B, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
            fopAcM_monsSeStart(i_this, 0x4873, 0);
            i_this->mSph.ClrAtSet();
            i_this->mSph.ClrAtSet();
            i_this->attention_info.flags = 0;
            i_this->m2F0 = 0;
            fire_emitter_clr(i_this);
        }
        break;
    case 0x100000:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 40.0f;
        JAIZelBasic::zel_basic->seStart(0x588B, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        fopAcM_monsSeStart(i_this, 0x4873, 0);
        i_this->current.angle.x = 0;
        i_this->current.angle.z = 0;
        i_this->m2D3 = 0;
        i_this->shape_angle.x = 0;
        i_this->shape_angle.z = 0;
        i_this->gravity = 0.0f;
        i_this->speedF = 0.0f;
        i_this->m2EC = 0;
        i_this->speed.x = 0.0f;
        i_this->speed.y = 0.0f;
        i_this->speed.z = 0.0f;
        i_this->mSph.ClrAtSet();
        i_this->mSph.ClrAtSet();
        i_this->attention_info.flags = 0;
        i_this->m2F0 = 0;
        fire_emitter_clr(i_this);
        break;
    case 0x80000:
        flag = 1;
        i_this->m2D3 = 0;
        i_this->current.angle.x = 0;
        i_this->current.angle.z = 0;
        i_this->shape_angle.x = 0;
        i_this->shape_angle.z = 0;
        i_this->gravity = 0.0f;
        i_this->speedF = 0.0f;
        i_this->m2EC = 0;
        i_this->speed.x = 0.0f;
        i_this->speed.y = 0.0f;
        i_this->speed.z = 0.0f;
        i_this->m2F0 = 0;
        fire_emitter_clr(i_this);
        i_this->mSph.ClrAtSet();
        i_this->mSph.ClrAtSet();
        i_this->mEnemyIce.mFreezeDuration = 0xC8;
        enemy_fire_remove(&i_this->mEnemyFire);
        i_this->attention_info.flags = 0;
        break;
    case 0x8000:
        flag = 1;
        if (i_this->m2D3 == 0) {
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        i_this->m2D4 = 7;
        i_this->m2D2 = 5;
        i_this->m306 = 0x3C;
        break;
    default:
        flag = 1;
        if (i_this->m2D3 == 0) {
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x33, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else {
            JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x42, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        dComIfGp_particle_set(0xC, &hitPos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        break;
    }

    if (flag == 0) {
        CcAtInfo atInfo;
        atInfo.mpObj = i_this->mSph.GetTgHitObj();
        atInfo.mpActor = NULL;
        cc_at_check(i_this, &atInfo);
        if (i_this->m2D4 == 6 || i_this->m2D4 == 5 || i_this->m2D4 == 4 || i_this->health <= 0) {
            dComIfGp_particle_set(0x10, &hitPos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
            cXyz scale(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(0xF, &hitPos, &player->shape_angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
        } else {
            dComIfGp_particle_set(0xD, &hitPos, &player->shape_angle, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        }
        if (i_this->m2D3 != 0) {
            anm_init(i_this, 0x17, 1.0f, 0, 1.0f, -1);
            i_this->speedF = 60.0f + REG8_F(10);
            if (i_this->health <= 0) {
                i_this->speedF = 60.0f + REG8_F(11);
                if (i_this->m2D4 == 5) {
                    i_this->current.angle.y = player->shape_angle.y - 0x4000;
                }
            }
            fopAcM_monsSeStart(i_this, 0x4873, 0);
            i_this->m2D2 = 2;
            i_this->m306 = 0x15;
        } else {
            i_this->m2D2 = 4;
            i_this->m306 = 0x28;
        }
    }
    return TRUE;
}

/* 000022BC-00002354       .text bound_sound_set__FP8bl_class */
void bound_sound_set(bl_class* i_this) {
    /* Nonmatching */
    u32 volume = (u32)(3.3f * i_this->speed.y);
    if (volume > 0x64) {
        volume = 0x64;
    }

    JAIZelBasic::zel_basic->seStart(0x588C, &i_this->eyePos, volume, dComIfGp_getReverb(i_this->current.roomNo),
                                    1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 00002354-00002458       .text fuwafuwa_keisan__FP8bl_class */
void fuwafuwa_keisan(bl_class* i_this) {
    /* Nonmatching */
    f32 f3 = 3.0f;

    if (i_this->m2D2 == 1) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        i_this->m304 += 0x3E8;
        i_this->m318 = 80.0f + player->current.pos.y;
        i_this->m318 += 10.0f * jmaSinTable[(u16)i_this->m304 >> jmaSinShift];
        f3 = 6.0f;
    } else {
        i_this->m304 += 0x1F4;
        i_this->m318 = 100.0f + i_this->m320;
        i_this->m318 += 40.0f * jmaSinTable[(u16)i_this->m304 >> jmaSinShift];
    }

    cLib_addCalc2(&i_this->current.pos.y, i_this->m318, 1.0f, f3);
}

/* 00002458-000024E4       .text BG_check__FP8bl_class */
void BG_check(bl_class* i_this) {
    /* Nonmatching */
    if (i_this->m306 != 2) {
        i_this->mAcchCir.SetWall(40.0f, 40.0f);
        i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        i_this->mAcch.m_flags |= dBgS_Acch::LINE_CHECK;

        if (i_this->m2D1 == 0) {
            f32 groundH = i_this->mAcch.GetGroundH();
            if (groundH == -1000000000.0f) {
                i_this->m320 = groundH;
            }
        }
    }
}

/* 000024E4-00002804       .text Line_check__FP8bl_class4cXyz */
s32 Line_check(bl_class* i_this, cXyz param) {
    /* Nonmatching */
    dBgS_LinChk linChk;
    cXyz start = i_this->current.pos;

    start.y += 1.0f;
    param.y += 1.0f;

    linChk.Set(&start, &param, i_this);
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 00002C3C-00002CC4       .text roll_check__FP8bl_class */
BOOL roll_check(bl_class* i_this) {
    cLib_addCalcAngleS2(&i_this->shape_angle.x, 0, 1, 0x1000);
    cLib_addCalcAngleS2(&i_this->shape_angle.z, 0, 1, 0x1000);
    i_this->m2F8[0] = 0;
    i_this->m2F8[1] = 0;

    if (abs(i_this->shape_angle.x) < 0x200 && abs(i_this->shape_angle.z) < 0x200) {
        return TRUE;
    }
    return FALSE;
}

/* 00002CC4-00003054       .text way_check__FP8bl_classs */
s16 way_check(bl_class* i_this, s16 angle) {
    /* Nonmatching */
    dBgS_LinChk linChk;
    cXyz end;
    s16 step = 0x2000;
    s16 curAngle = angle;

    if (cM_rndFX(1.0f) < 0.5f) {
        step = -0x2000;
    }

    for (int i = 0; i < 8; i++) {
        mDoMtx_YrotS(*calc_mtx, curAngle);
        cXyz dir(0.0f, 0.0f, 300.0f);
        MtxPosition(&dir, &end);
        PSVECAdd(&end, &i_this->current.pos, &end);

        linChk.Set(&i_this->current.pos, &end, i_this);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            return curAngle;
        }
        curAngle += step;
    }

    return angle;
}

/* 00003054-000039F0       .text action_dousa__FP8bl_class */
void action_dousa(bl_class* i_this) {
    /* Nonmatching */
    s32 angle = 0;

    switch (i_this->m306) {
    case 0:
        i_this->m304 = 0;
        if (fopAcM_searchActorDistance(i_this, dComIfGp_getPlayer(0)) > 1000.0f) {
            break;
        }
        i_this->actor_status |= 0x20;
        i_this->attention_info.flags = 4;
        anm_init(i_this, 0x15, 1.0f, 0, 1.0f, -1);
        i_this->m306++;
        break;
    case 1:
        i_this->m31C = 1.5f;
        if (i_this->mFollowCB1.getEmitter() == NULL) {
            dComIfGp_particle_set(0x8122, &i_this->current.pos, NULL, NULL, 0xFF, &i_this->mFollowCB1, -1, NULL,
                                  NULL, NULL);
            JAIZelBasic::zel_basic->seStart(0x5888, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
        if (i_this->mFollowCB1.getEmitter() != NULL) {
            if (i_this->m2D0 == 0) {
                i_this->mFollowCB1.getEmitter()->setGlobalEnvColor(0x55, 0x1A, 0x0D);
            } else {
                i_this->mFollowCB1.getEmitter()->setGlobalEnvColor(0x0D, 0x20, 0x41);
            }
        }
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->gravity = 0.0f;
        i_this->speed.y = 0.0f;
        i_this->m306++;
        // fall through
    case 2:
        JPABaseEmitter* emitter = i_this->mFollowCB1.getEmitter();
        if (emitter != NULL) {
            JPASetRMtxTVecfromMtx(i_this->mpMorf->getModel()->getAnmMtx(0), emitter->mGlobalRotation,
                                  emitter->mGlobalTranslation);
        }
        cLib_addCalc2(&i_this->speed.y, 10.0f, 0.8f, 1.0f);
        if (i_this->current.pos.y < 100.0f + i_this->m320) {
            break;
        }
        fire_move_set(i_this);
        i_this->speed.y = 0.0f;
        JAIZelBasic::zel_basic->seStart(0x5889, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        fopAcM_monsSeStart(i_this, 0x4871, 0);
        anm_init(i_this, 0x16, 1.0f, 0, 1.0f, -1);
        i_this->m306++;
        break;
    case 3:
        if (i_this->mpMorf->checkFrame(10.0f)) {
            i_this->mFollowCB1.end();
        }
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->m306 = 5;
        break;
    case 4:
        fire_move_set(i_this);
        i_this->actor_status |= 0x20;
        i_this->m2F2 = 5;
        i_this->m306 = 5;
        // fall through
    case 5:
        i_this->actor_status |= 0x20;
        if (i_this->m308 != 0x11) {
            anm_init(i_this, 0x11, 1.0f, 2, 1.0f, -1);
            i_this->m2D3 = 1;
            i_this->mStts.SetWeight(2);
            i_this->mSph.OnAtSetBit();
            i_this->mSph.OnAtHitBit();
        }
        i_this->attention_info.flags = 4;
        if (i_this->m2E9 != 0xFF && i_this->mPath != NULL) {
            f32 dx = i_this->mPath->m_points[i_this->m2E8].m_position.x - i_this->current.pos.x;
            f32 dz = i_this->mPath->m_points[i_this->m2E8].m_position.z - i_this->current.pos.z;
            angle = cM_atan2s(dx, dz);
            i_this->speedF = i_this->m324;
        } else {
            i_this->m2EC = (s16)(100.0f + cM_rndFX(50.0f));
            angle = cM_rndFX(32767.0f);
            if (i_this->speedF == 0.0f) {
                i_this->speedF = 4.0f + cM_rndF(2.0f);
            }
        }
        i_this->m300 = way_check(i_this, angle);
        i_this->m306++;
        // fall through
    case 6:
        if (i_this->m2E9 != 0xFF && i_this->mPath != NULL) {
            f32 dx = i_this->mPath->m_points[i_this->m2E8].m_position.x - i_this->current.pos.x;
            f32 dz = i_this->mPath->m_points[i_this->m2E8].m_position.z - i_this->current.pos.z;
            angle = cM_atan2s(dx, dz);
            f32 dist = dx * dx + dz * dz;
            if (dist > 0.0f) {
                double guess = __frsqrte(dist);
                guess = 0.5 * guess * (3.0 - guess * guess * dist);
                guess = 0.5 * guess * (3.0 - guess * guess * dist);
                guess = 0.5 * guess * (3.0 - guess * guess * dist);
                dist = (f32)(dist * guess);
            }
            if (dist < 80.0f + REG8_F(3)) {
                i_this->m2E8++;
                if (i_this->m2E8 >= i_this->mPath->m_num) {
                    i_this->m2E8 = 0;
                }
            }
            i_this->m2C4 = i_this->current.pos;
            if (i_this->m2EC == 0) {
                i_this->m300 = way_check(i_this, angle);
                if (i_this->m300 == angle) {
                    break;
                }
                i_this->m2EC = (s16)(10.0f + cM_rndF(10.0f));
            }
        } else {
            f32 dx = i_this->current.pos.x - i_this->m2C4.x;
            f32 dz = i_this->current.pos.z - i_this->m2C4.z;
            f32 dist = dx * dx + dz * dz;
            if (dist > 0.0f) {
                double guess = __frsqrte(dist);
                guess = 0.5 * guess * (3.0 - guess * guess * dist);
                guess = 0.5 * guess * (3.0 - guess * guess * dist);
                guess = 0.5 * guess * (3.0 - guess * guess * dist);
                dist = (f32)(dist * guess);
            }
            if (dist < 250.0f) {
                if (i_this->m2EC == 0) {
                    i_this->m306 = 5;
                }
                break;
            } else {
                i_this->m306 = 7;
            }
        }
        // fall through
    case 7:
        f32 dx = i_this->m2C4.x - i_this->current.pos.x;
        f32 dz = i_this->m2C4.z - i_this->current.pos.z;
        i_this->m300 = cM_atan2s(dx, dz);
        f32 targetDist = 10.0f;
        if (i_this->m2E9 != 0xFF && i_this->mPath != NULL) {
            targetDist = 80.0f;
        }
        f32 dist = dx * dx + dz * dz;
        if (dist > 0.0f) {
            double guess = __frsqrte(dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            dist = (f32)(dist * guess);
        }
        if (dist < targetDist) {
            i_this->m306 = 5;
        }
        break;
    }

    if (i_this->m306 >= 1 && i_this->m306 <= 3) {
        if (i_this->mFollowCB1.getEmitter() != NULL) {
            JPASetRMtxTVecfromMtx(i_this->mpMorf->getModel()->getAnmMtx(0), i_this->mFollowCB1.getEmitter()->mGlobalRotation,
                                  i_this->mFollowCB1.getEmitter()->mGlobalTranslation);
        }
    }

    if (i_this->m2F2 == 0) {
        fire_kaiten_keisan(i_this);
    }

    s16 maxStep = 0x120;
    s16 maxStep2 = 0x400;
    if (i_this->m2E9 != 0xFF && i_this->mPath != NULL) {
        maxStep = 0x1000;
        maxStep2 = 0x1000;
    }
    cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->m300, 1, maxStep);
    cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->shape_angle.y, 1, maxStep2);

    if (i_this->m306 >= 3) {
        i_this->m31C = 1.5f;
        fuwafuwa_keisan(i_this);
    }

    if (i_this->m2D0 == 1) {
        if (blue_body_atari_check(i_this)) {
            return;
        }
    } else if (red_body_atari_check(i_this)) {
        return;
    }

    if (i_this->m306 >= 5) {
        if (i_this->mSph.ChkAtShieldHit()) {
            if (i_this->m2E9 != 0xFF && i_this->mPath != NULL && i_this->m306 == 7) {
                return;
            }
            i_this->current.angle.y = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0)) + 0x8000;
            i_this->speedF = 50.0f;
            i_this->m2D2 = 1;
            i_this->m306 = 0xA;
        } else if (i_this->m2D3 != 0) {
            if (fopAcM_searchActorDistance(i_this, dComIfGp_getPlayer(0)) < 600.0f) {
                if (Line_check(i_this, dComIfGp_getPlayer(0)->current.pos)) {
                    if (i_this->m2E9 == 0xFF || i_this->mPath == NULL || i_this->m306 != 7) {
                        i_this->m2D2 = 1;
                        i_this->m306 = 0xA;
                    }
                }
            }
        }
    }
}

/* 000039F0-00003F68       .text action_kougeki__FP8bl_class */
void action_kougeki(bl_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    switch (i_this->m306) {
    case 0xA:
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        i_this->mSph.OnAtSetBit();
        i_this->mSph.OnAtHitBit();
        i_this->m304 = 0;
        anm_init(i_this, 0x12, 1.0f, 0, 1.0f, -1);
        fopAcM_monsSeStart(i_this, 0x4870, 0);
        i_this->speedF = 0.0f;
        i_this->m306++;
        break;
    case 0xB:
        if (i_this->mpMorf->isStop()) {
            i_this->m306++;
            anm_init(i_this, 0x10, 1.0f, 2, 1.0f, 6);
            i_this->speedF = 10.0f;
            i_this->m302 = (s16)(cM_rndFX(768.0f) * (f32)(fopAcM_GetID(i_this) & 3));
            i_this->m306++;
        }
        break;
    case 0xC:
        if (i_this->m2E9 != 0xFF && i_this->mPath != NULL) {
            f32 distSq = (i_this->current.pos.x - i_this->m2C4.x) * (i_this->current.pos.x - i_this->m2C4.x) +
                         (i_this->current.pos.z - i_this->m2C4.z) * (i_this->current.pos.z - i_this->m2C4.z);
            f32 dist = distSq;
            if (dist > 0.0f) {
                dist = std::sqrtf(distSq);
            }
            if (dist > 700.0f) {
                anm_init(i_this, 0x11, 1.0f, 2, 1.0f, -1);
                i_this->speedF = 4.0f + cM_rndF(2.0f);
                i_this->m2D2 = 0;
                i_this->m306 = 7;
                break;
            }
        } else if (fopAcM_searchActorDistance(i_this, player) > 700.0f) {
            i_this->speedF = 4.0f + cM_rndF(2.0f);
            i_this->m2D2 = 0;
            i_this->m306 = 5;
            break;
        }
        break;
    case 0xD:
        break;
    case 0xE:
        cLib_addCalc0(&i_this->speedF, 0.5f, 1.0f);
        if (std::fabsf(i_this->speedF) < 0.2f) {
            i_this->speedF = 0.0f;
            anm_init(i_this, 0x18, 1.0f, 0, 1.0f, -1);
            fopAcM_monsSeStart(i_this, 0x4870, 0);
            i_this->m306 = 0xF;
        }
        break;
    case 0xF:
        if (i_this->mpMorf->isStop()) {
            i_this->m306 = 0xC;
        }
        break;
    }

    i_this->mpMorf->setPlaySpeed(1.0f);
    if (i_this->m306 == 0xD && fopAcM_searchActorDistance(i_this, player) < 230.0f) {
        i_this->mpMorf->setPlaySpeed(2.0f);
    }

    if (i_this->mSph.ChkAtShieldHit()) {
        if (i_this->m306 != 0xE) {
            i_this->speedF = -20.0f;
            i_this->m2D2 = 1;
            i_this->m306 = 0xE;
        }
    } else if (i_this->mSph.ChkAtHit()) {
        fopAc_ac_c* ac = i_this->mSph.mGObjAt.GetAc();
        if (ac != NULL && ac == player && i_this->m306 != 0xF) {
            anm_init(i_this, 0x14, 1.0f, 0, 1.0f, -1);
            fopAcM_monsSeStart(i_this, 0x4872, 0);
            i_this->speedF = 0.0f;
            i_this->m2F8[0] = 0;
            i_this->m306 = 0xF;
        }
    }

    fire_kaiten_keisan(i_this);
    i_this->m300 = i_this->m302 + fopAcM_searchActorAngleY(i_this, player);
    cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->m300, 1, 0x1000);
    cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 1, 0x400);

    if (i_this->m306 >= 0xC) {
        fuwafuwa_keisan(i_this);
    }

    if (i_this->m2D0 == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}

/* 00003F68-00004204       .text action_sagarimasu__FP8bl_class */
void action_sagarimasu(bl_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    switch (i_this->m306) {
    case 0x14:
        anm_init(i_this, 0x17, 1.0f, 0, 1.0f, -1);
        i_this->speedF = 20.0f + REG8_F(10);
        if (i_this->m2D4 == 4 || i_this->m2D4 == 5) {
            i_this->speedF = 60.0f + REG8_F(11);
            if (i_this->m2D4 == 5) {
                i_this->shape_angle.y = player->shape_angle.y - 0x4000;
            }
        }
        i_this->m306++;
        /* fallthrough */
    case 0x15:
        cLib_addCalc0(&i_this->speedF, 0.8f, 5.0f);
        if (i_this->speedF < 0.1f) {
            i_this->m2D2 = 1;
            i_this->m306 = 0xA;
            if (i_this->m2D3 != 0 && i_this->m2D0 == 0 && i_this->health <= 0) {
                cXyz pos = i_this->current.pos;
                pos.y += 30.0f;
                fopAcM_createDisappear(i_this, &pos, 5, 0, 0xFF);
                i_this->attention_info.flags = 0;
                dComIfGs_onActor(i_this->setID, i_this->home.roomNo);
                fopAcM_delete(i_this);
            }
        }
        break;
    }

    fire_kaiten_keisan(i_this);
    if (i_this->m2D0 == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}

/* 00004128-00004798       .text action_kaze_move__FP8bl_class */
void action_kaze_move(bl_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    switch (i_this->m306 - 0x1E) {
    case 0:
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        i_this->attention_info.flags = 4;
        i_this->mSph.SetTgSe(0);
        i_this->mSph.SetTgHitMark(dCcG_TgHitMark_None_e);
        i_this->mSph.OffTgShield();
        i_this->mSph.ClrAtSet();
        i_this->mSph.ClrAtSet();
        i_this->speedF = 15.0f;
        i_this->m310 = 7.0f;
        i_this->m2F8[0] = (s16)(512.0f + cM_rndF(500.0f));
        if (cM_rnd() < 0.5f) {
            i_this->m2F8[0] = -i_this->m2F8[0];
        }
        if (i_this->m308 != 0x17) {
            anm_init(i_this, 0x17, 1.0f, 0, 1.0f, -1);
        }
        i_this->m2F0 = 0;
        fire_emitter_clr(i_this);
        JAIZelBasic::zel_basic->seStart(0x588B, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        fopAcM_monsSeStart(i_this, 0x4873, 0);
        i_this->m306++;
        break;
    case 1:
        i_this->shape_angle.z += i_this->m2F8[0];
        cLib_addCalc2(&i_this->speed.y, i_this->m310, 0.8f, 2.0f);
        cLib_addCalc0(&i_this->speedF, 0.8f, 3.0f);
        if (i_this->speedF > 0.1f) {
            break;
        }
        i_this->m306++;
        break;
    case 2:
        i_this->m2D3 = 0;
        i_this->speedF = 0.0f;
        i_this->m306++;
        break;
    case 3:
        cLib_addCalc2(&i_this->gravity, -3.0f, 0.8f, 0.1f);
        cLib_addCalcAngleS2(&i_this->shape_angle.x, -0x7FFF, 1, 0x120);
        if (i_this->mAcch.m_flags & dBgS_Acch::GROUND_HIT) {
            i_this->m306++;
        }
        break;
    case 4:
        i_this->speed.y = 15.0f;
        i_this->gravity = -3.0f;
        bound_sound_set(i_this);
        i_this->m306++;
        break;
    case 5:
        cLib_addCalcAngleS2(&i_this->shape_angle.x, 0, 1, 0x400);
        cLib_addCalcAngleS2(&i_this->shape_angle.z, 0, 1, 0x400);
        if (abs(i_this->shape_angle.x) < 0x100 && abs(i_this->shape_angle.z) < 0x100) {
            i_this->shape_angle.x = 0;
            i_this->shape_angle.z = 0;
            if (i_this->m2D0 & 0x80) {
                i_this->m2D2 = 0xA;
                i_this->m306 = 0x64;
            } else {
                i_this->m306 = 0x26;
            }
        }
        break;
    case 6:
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        i_this->speed.y = 15.0f;
        i_this->gravity = -3.0f;
        bound_sound_set(i_this);
        if (!(i_this->m2D0 & 0x80)) {
            i_this->attention_info.flags = 4;
        }
        i_this->mSph.ClrAtSet();
        i_this->mSph.ClrAtSet();
        i_this->speedF = 30.0f;

        mDoMtx_YrotS(*calc_mtx, fopAcM_searchActorAngleY(i_this, player) + 0x8000);
        cXyz dir(0.0f, 0.0f, 5000.0f);
        cXyz out;
        MtxPosition(&dir, &out);
        i_this->m2F8[0] = -(s16)out.x;
        i_this->m2F8[1] = (s16)out.z;
        i_this->mStts.SetWeight(0x50);
        i_this->m306++;
        break;
    case 7:
        i_this->shape_angle.x += i_this->m2F8[0];
        i_this->shape_angle.z += i_this->m2F8[1];
        if (i_this->speedF < 5.0f) {
            if (roll_check(i_this)) {
                if (i_this->m2D0 & 0x80) {
                    i_this->m2D2 = 0xA;
                    i_this->m306 = 0x64;
                } else {
                    i_this->m306 = 0x26;
                }
            }
        } else if (i_this->mAcch.m_flags & dBgS_Acch::GROUND_HIT) {
            i_this->m2F8[2] = 1;
            i_this->speed.y = 10.0f;
            bound_sound_set(i_this);
        }
        if (i_this->m2F8[2] != 0) {
            cLib_addCalc0(&i_this->speedF, 0.8f, 1.0f);
        }
        break;
    case 8:
        i_this->m2EE = (s16)(70.0f + cM_rndF(35.0f));
        i_this->speedF = 0.0f;
        i_this->m306++;
        break;
    case 9:
        if (i_this->m2EE == 0) {
            anm_init(i_this, 0x15, 1.0f, 0, 1.0f, -1);
            i_this->speedF = 0.0f;
            i_this->current.angle.y = i_this->shape_angle.y;
            i_this->m2D2 = 0;
            i_this->m306 = 1;
        }
        break;
    }

    i_this->mFollowCB1.end();
    i_this->m31C = 1.0f;
    if (i_this->m2D0 & 0x80) {
        skull_atari_check(i_this);
    } else if (i_this->m2D0 == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}

/* 00004798-00004B84       .text action_itaiyo_ne_san__FP8bl_class */
void action_itaiyo_ne_san(bl_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    switch (i_this->m306) {
    case 0x28:
        i_this->m31C = 1.0f;
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        i_this->gravity = -3.0f;
        i_this->attention_info.flags = 4;
        i_this->mSph.ClrAtSet();
        i_this->mSph.ClrAtSet();
        if (i_this->m308 != 0x17) {
            anm_init(i_this, 0x17, 1.0f, 0, 1.0f, -1);
        }
        i_this->m2F0 = 0;
        fire_emitter_clr(i_this);
        cXyz dir(0.0f, 0.0f, 0.0f);

        if (i_this->health <= 0) {
            if (i_this->m2D4 == 4) {
                i_this->m2EC = 0;
            } else {
                i_this->m2EC = 0x32;
                i_this->m310 = 30.0f;
                i_this->speed.y = 30.0f;
                i_this->speedF = 20.0f;
                dir.z = 5000.0f;
                if (i_this->m2D4 == 5) {
                    i_this->current.angle.y = player->shape_angle.y - 0x4000;
                }
                bound_sound_set(i_this);
            }
            i_this->attention_info.flags = 0;
            i_this->m306 = 0x2A;
        } else {
            i_this->m306 = 0x29;
            i_this->speed.y = 15.0f;
            i_this->speedF = 10.0f;
            dir.z = 5000.0f;
            bound_sound_set(i_this);
        }

        mDoMtx_YrotS(*calc_mtx, fopAcM_searchActorAngleY(i_this, player) + 0x8000);
        cXyz out;
        MtxPosition(&dir, &out);
        i_this->m2F8[0] = -(s16)out.x;
        i_this->m2F8[1] = (s16)out.z;
        break;
    case 0x29:
        if (i_this->speedF < 0.1f && roll_check(i_this)) {
            i_this->m2D2 = 3;
            i_this->m306 = 0x26;
        }
        cLib_addCalc0(&i_this->speedF, 0.8f, 1.0f);
        if (i_this->m2D0 == 1) {
            blue_body_atari_check(i_this);
        } else {
            red_body_atari_check(i_this);
        }
        break;
    case 0x2A:
        if (i_this->mAcch.m_flags & dBgS_Acch::GROUND_HIT) {
            i_this->m310 *= 0.5f;
            if (i_this->m310 < 10.0f) {
                i_this->m310 = 10.0f;
            }
            i_this->speed.y = i_this->m310;
            bound_sound_set(i_this);
            if (i_this->m2EC == 0) {
                cXyz pos = i_this->current.pos;
                pos.y += 30.0f;
                fopAcM_createDisappear(i_this, &pos, 5, 0, 0xFF);
                if (i_this->m2D4 == 4) {
                    cXyz ppos = i_this->current.pos;
                    ppos.y += 25.0f + REG8_F(2);
                    dComIfGp_particle_set(0x3E8, &ppos, &i_this->current.angle, &i_this->scale, 0xFF, NULL,
                                          i_this->current.roomNo, &i_this->tevStr.mColorK0, &i_this->tevStr.mColorK0);
                    *(cXyz*)i_this->m6BC = ppos;
                    smoke_set(i_this);
                    i_this->mSph.ClrTgSet();
                    i_this->mSph.ClrCoSet();
                    i_this->mSph.ClrTgHit();
                    i_this->scale.x = 0.0f;
                    i_this->scale.y = 0.0f;
                    i_this->scale.z = 0.0f;
                    i_this->m31C = 0.0f;
                    i_this->m2F8[2] = 0xB4;
                    i_this->m2EE = 0xA;
                    i_this->m306++;
                } else {
                    dComIfGs_onActor(i_this->setID, i_this->home.roomNo);
                    fopAcM_delete(i_this);
                }
            }
        }
        break;
    case 0x2B:
        if (i_this->mSmokeCB.getEmitter() != NULL) {
            if (i_this->m2EE == 0) {
                i_this->mSmokeCB.getEmitter()->mGlobalPrmColor.a = i_this->m2F8[2];
                i_this->m2F8[2] -= 4;
                if (i_this->m2F8[2] < 0) {
                    i_this->mSmokeCB.end();
                }
            }
        } else {
            dComIfGs_onActor(i_this->setID, i_this->home.roomNo);
            fopAcM_delete(i_this);
        }
        break;
    }

    i_this->shape_angle.x += i_this->m2F8[0];
    i_this->shape_angle.z += i_this->m2F8[1];
}

/* 00004B84-00004D3C       .text action_hook_atari__FP8bl_class */
void action_hook_atari(bl_class* i_this) {
    /* Nonmatching */
    switch (i_this->m306) {
    case 0x3C:
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        if (i_this->mFollowCB2.getEmitter() != NULL) {
            i_this->m2F0 = 0;
            fire_emitter_clr(i_this);
            anm_init(i_this, 0x17, 1.0f, 0, 1.0f, -1);
            i_this->mSph.ClrAtSet();
            i_this->mSph.ClrAtSet();
            i_this->speedF = 0.0f;

            JAIZelBasic::zel_basic->seStart(0x588B, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
            fopAcM_monsSeStart(i_this, 0x4873, 0);
        }
        i_this->actor_status |= 0x20;
        i_this->mSph.SetTgSe(0);
        i_this->mSph.SetTgHitMark(dCcG_TgHitMark_None_e);
        i_this->mSph.OffTgShield();
        i_this->attention_info.flags = 4;
        i_this->m306++;
        break;
    case 0x3D:
        if (!(i_this->actor_status & 0x100000)) {
            i_this->m2D2 = 3;
            i_this->m306 = 0x20;
        }
        break;
    }

    i_this->mFollowCB1.end();
}

/* 00004D3C-00004DBC       .text action_come_wait__FP8bl_class */
void action_come_wait(bl_class* i_this) {
    /* Nonmatching */
    if (i_this->m306 == 0x46) {
        if (i_this->m2D5 != 0xFF && dComIfGs_isSwitch(i_this->m2D5, dComIfGp_roomControl_getStayNo())) {
            i_this->actor_status |= 0x20;
            i_this->m2D2 = 3;
            i_this->m306 = 0x26;
        }
    }
}

/* 00004DBC-00005104       .text action_normal_skull__FP8bl_class */
void action_normal_skull(bl_class* i_this) {
    /* Nonmatching */
    cXyz pos = i_this->current.pos;

    switch (i_this->m306) {
    case 0x64:
        i_this->m328 = 30.0f + REG8_F(7);
        i_this->gravity = -3.0f;
        if (i_this->actor_status & 0x2000) {
            i_this->gravity = 0.0f;
            i_this->mSph.ClrCoSet();
            i_this->m306++;
        }
        /* fallthrough */
    case 0x65:
        if (!(i_this->actor_status & 0x2000)) {
            i_this->mSph.OnCoSetBit();
            i_this->gravity = -3.0f;
            if (i_this->speedF > 0.0f) {
                i_this->speed.y = 25.0f;
                i_this->speedF = 35.0f;
                i_this->m306 = 0x66;
            } else {
                i_this->speedF = 0.0f;
                i_this->speed.x = 0.0f;
                i_this->speed.y = 0.0f;
                i_this->speed.z = 0.0f;
                i_this->gravity = -3.0f;
                i_this->m306 = 0x64;
            }
        }
        break;
    case 0x66:
        if ((i_this->mAcch.m_flags & dBgS_Acch::GROUND_HIT) ||
            (i_this->mAcch.m_flags & dBgS_Acch::WALL_HIT)) {
            i_this->speed.x = 0.0f;
            i_this->speed.y = 0.0f;
            i_this->speed.z = 0.0f;
            if (i_this->mEnemyFire.mFireDuration == 0) {
                i_this->speedF = 0.0f;
                i_this->health = 0;
                i_this->attention_info.flags = 0;
                i_this->m306 = 0x68;
            }
        }
        break;
    case 0x67:
        bound_sound_set(i_this);
        i_this->m306 = 0x66;
        break;
    case 0x68:
        pos.y += 25.0f + REG8_F(2);
        dComIfGp_particle_set(0x3E8, &pos, &i_this->current.angle, &i_this->scale, 0xFF, NULL,
                              i_this->current.roomNo, &i_this->tevStr.mColorK0, &i_this->tevStr.mColorK0);
        *(cXyz*)i_this->m6BC = pos;
        smoke_set(i_this);

        for (int i = 0; i < (s32)cM_rndF(1.99f); i++) {
            fopAcM_createItem(&i_this->current.pos, 0, -1, -1, 0, NULL, 4, NULL);
        }

        i_this->mSph.ClrTgSet();
        i_this->mSph.ClrCoSet();
        i_this->mSph.ClrTgHit();
        i_this->m31C = 0.0f;
        i_this->scale.x = 0.0f;
        i_this->scale.y = 0.0f;
        i_this->scale.z = 0.0f;
        i_this->m2F8[3] = 0xB4;
        i_this->m2EE = 0xA;
        i_this->m306++;
        break;
    case 0x69:
        if (i_this->mSmokeCB.getEmitter() != NULL) {
            if (i_this->m2EE == 0) {
                i_this->mSmokeCB.getEmitter()->mGlobalPrmColor.a = i_this->m2F8[3];
                i_this->m2F8[3] -= 4;
                if (i_this->m2F8[3] < 0) {
                    i_this->mSmokeCB.end();
                }
            }
        } else {
            fopAcM_delete(i_this);
        }
        break;
    }

    i_this->m314 = 0.3f;
    skull_atari_check(i_this);
}

/* 00005104-00005504       .text daBL_Execute__FP8bl_class */
static BOOL daBL_Execute(bl_class* i_this) {
    /* Nonmatching */
    if (i_this->m2F0 == 1) {
        i_this->mFollowCB2.end();
    }

    if (i_this->m2F6 == 1) {
        i_this->actor_status &= ~0x4000;
    }

    i_this->eyePos = i_this->current.pos;
    i_this->attention_info.position = i_this->current.pos;
    i_this->eyePos.y += 40.0f;
    i_this->attention_info.position.y += 80.0f;

    if (!(i_this->m2D0 & 0x80)) {
        if (i_this->m2D3 == 0) {
            i_this->mpBtk2->play();
        } else {
            i_this->mpBtk1->play();
        }
    }

    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
        i_this->mpMorf->calc();
        if (i_this->m2F0 != 0) {
            i_this->m2F0--;
        }
        return TRUE;
    }

    s16* timers = &i_this->m2F0;
    for (int i = 0; i < 6; i++) {
        if (timers[i] != 0) {
            timers[i]--;
        }
    }

    switch (i_this->m2D2) {
    case 0:
        action_dousa(i_this);
        break;
    case 1:
        action_kougeki(i_this);
        break;
    case 2:
        action_sagarimasu(i_this);
        break;
    case 3:
        action_kaze_move(i_this);
        break;
    case 4:
        action_itaiyo_ne_san(i_this);
        break;
    case 5:
        action_hook_atari(i_this);
        break;
    case 6:
        action_come_wait(i_this);
        break;
    case 7:
        action_normal_skull(i_this);
        break;
    case 0xA:
        action_normal_skull(i_this);
        break;
    }

    if (i_this->m306 != 0) {
        u32 groundHit = (i_this->mAcch.m_flags & dBgS_Acch::GROUND_HIT) ? 1 : 0;
        i_this->mpMorf->play(&i_this->eyePos, groundHit, dComIfGp_getReverb(i_this->current.roomNo));
    }

    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    cXyz dir(0.0f, 0.0f, i_this->speedF);
    cXyz out;
    MtxPosition(&dir, &out);
    i_this->speed.x = out.x;
    i_this->speed.z = out.z;
    i_this->speed.y += i_this->gravity;
    if (i_this->speed.y < -55.0f) {
        i_this->speed.y = -55.0f;
    }
    cLib_addCalc2(&i_this->scale.x, i_this->m31C, 0.3f, 0.3f);
    i_this->scale.z = i_this->scale.x;
    i_this->scale.y = i_this->scale.x;

    cXyz pos = i_this->current.pos;
    pos.y += 20.0f;
    i_this->mSph.SetC(pos);
    i_this->mSph.SetR(i_this->m328);
    dComIfG_Ccsp()->Set(&i_this->mSph);

    if (i_this->mSph.ChkCoSet()) {
        fopAcM_posMove(i_this, i_this->mStts.GetCCMoveP());
    } else {
        fopAcM_posMove(i_this, NULL);
    }

    BG_check(i_this);

    if (i_this->m2D1 != 0 || i_this->gravity != 0.0f) {
        if (i_this->mAcch.GetGroundH() != -1000000000.0f) {
            if (dComIfG_Bgsp()->ChkPolySafe(i_this->mAcch.m_gnd) &&
                dComIfG_Bgsp()->GetGroundCode(i_this->mAcch.m_gnd) == 4)
            {
                if (i_this->current.pos.y < i_this->m320 - 5000.0f) {
                    i_this->speedF = 0.0f;
                    i_this->speed.x = 0.0f;
                    i_this->speed.y = 0.0f;
                    i_this->speed.z = 0.0f;
                    i_this->gravity = 0.0f;
                    dComIfGs_onActor(i_this->setID, i_this->home.roomNo);
                    fopAcM_delete(i_this);
                }
            }
        }
    }

    draw_SUB(i_this);
    return TRUE;
}

/* 00005504-0000550C       .text daBL_IsDelete__FP8bl_class */
static BOOL daBL_IsDelete(bl_class*) {
    return TRUE;
}

/* 0000550C-0000558C       .text daBL_Delete__FP8bl_class */
static BOOL daBL_Delete(bl_class* i_this) {
    i_this->mFollowCB1.remove();
    i_this->mFollowCB2.remove();
    i_this->mSmokeCB.remove();
    enemy_fire_remove(&i_this->mEnemyFire);
    dComIfG_resDelete(&i_this->mPhs, "BL");
    return TRUE;
}

/* 0000558C-0000583C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_this) {
    /* Nonmatching */
    bl_class* i_bl = (bl_class*)i_this;

    i_bl->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BL", 0x1B),
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("BL", 0x15),
        1, 0.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x37441422
    );
    if (i_bl->mpMorf == NULL || i_bl->mpMorf->getModel() == NULL) {
        return FALSE;
    }

    i_bl->mpBtk1 = new mDoExt_btkAnm();
    if (i_bl->mpBtk1 == NULL) {
        return FALSE;
    }
    if (!i_bl->mpBtk1->init(i_bl->mpMorf->getModel()->getModelData(),
                            (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("BL", 0x1F), TRUE, 0, 1.0f, 0, -1, false,
                            FALSE)) {
        return FALSE;
    }
    if (i_bl->mpBtk1 == NULL) {
        return FALSE;
    }

    i_bl->mpBtk2 = new mDoExt_btkAnm();
    if (i_bl->mpBtk2 == NULL) {
        return FALSE;
    }
    if (!i_bl->mpBtk2->init(i_bl->mpMorf->getModel()->getModelData(),
                            (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("BL", 0x1E), TRUE, 0, 1.0f, 0, -1, false,
                            FALSE)) {
        return FALSE;
    }
    if (i_bl->mpBtk2 == NULL) {
        return FALSE;
    }

    i_bl->mpMorf->getModel()->setUserArea((u32)i_this);
    return i_bl->mInvisibleModel.create(i_bl->mpMorf->getModel());
}

/* 00005884-00005D88       .text daBL_Create__FP10fopAc_ac_c */
static cPhs_State daBL_Create(fopAc_ac_c* i_this) {
    /* Nonmatching */
    fopAcM_ct(i_this, bl_class);

    cPhs_State ret = dComIfG_resLoad(&((bl_class*)i_this)->mPhs, "BL");
    if (ret == cPhs_COMPLEATE_e) {
        bl_class* i_bl = (bl_class*)i_this;
        i_bl->m2D0 = fopAcM_GetParam(i_this);
        i_bl->m2D1 = fopAcM_GetParam(i_this) >> 24;
        i_bl->m2E9 = (fopAcM_GetParam(i_this) >> 8) & 0xFF;
        i_bl->m2D5 = (fopAcM_GetParam(i_this) >> 16) & 0xFF;
        i_bl->m324 = (f32)i_this->current.angle.z;
        i_this->current.angle.z = 0;
        i_this->shape_angle.z = 0;

        if (i_bl->m2D0 == 0xFF) {
            i_bl->m2D0 = 0;
        }
        if (i_bl->m2D1 == 0xFF) {
            i_bl->m2D1 = 0;
        }

        if (REG8_S(8) != 0) {
            i_bl->m2D1 = 1;
        }
        if (REG8_S(9) != 0) {
            i_bl->m2D0 = REG8_S(9) - 1;
        }

        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x14E0)) {
            return cPhs_ERROR_e;
        }

        if (i_bl->m2D0 & 0x2) {
            i_bl->m2D0 ^= 0x2;
            if (i_bl->m2E9 != 0xFF) {
                i_bl->mPath = dPath_GetRoomPath(i_bl->m2E9, i_this->current.roomNo);
                if (i_bl->m324 < 4.0f) {
                    i_bl->m324 = 4.0f + cM_rndF(2.0f);
                }
            }
            if (REG8_S(9) != 0) {
                i_bl->m2E9 = 0;
                i_bl->mPath = dPath_GetRoomPath(0, i_this->current.roomNo);
            }
        }

        i_this->cullMtx = i_bl->mpMorf->getModel()->getBaseTRMtx();
        i_this->attention_info.flags = 0;

        i_bl->mAcch.Set(&i_this->current.pos, &i_this->old.pos, i_this, 1, &i_bl->mAcchCir, &i_this->speed, NULL, NULL);
        i_bl->mStts.Init(0x50, 0x1, i_this);
        i_this->max_health = 2;
        i_this->health = 2;

        i_bl->mEnemyIce.mpActor = i_this;
        i_bl->mEnemyIce.mCyl.mCenter.x = 1.0f;
        i_bl->mEnemyIce.mCyl.mCenter.y = 1.0f;

        i_bl->mEnemyFire.mpMcaMorf = i_bl->mpMorf;
        i_bl->mEnemyFire.mpActor = i_this;

        for (int i = 0; i < 10; i++) {
            i_bl->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_bl->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }

        i_bl->m328 = 1.0f;
        i_bl->m300 = i_this->shape_angle.y;

        i_bl->mSph.Set(body_co_sph_src);
        i_bl->mSph.SetStts(&i_bl->mStts);
        i_bl->mSph.ClrAtSet();
        i_bl->mSph.ClrAtSet();

        i_this->attention_info.distances[2] = 0x29;

        cDT_NamePTbl* nameTbl = (cDT_NamePTbl*)((u8*)&g_dComIfG_gameInfo + 0x50AC);
        i_this->itemTableIdx = nameTbl->GetIndex("bable_r", 0);
        i_this->gbaName = 0xE;

        if (i_bl->m2D0 == 1) {
            i_bl->mSph.SetAtSpl((dCcG_At_Spl)3);
            i_bl->mSph.GetObjAt().SetType(0x800);
            i_this->itemTableIdx = nameTbl->GetIndex("bable", 0);
            i_this->gbaName = 0xF;
        }

        i_this->gravity = -3.0f;
        i_this->speed.y += i_this->gravity;
        if (i_this->speed.y < -55.0f) {
            i_this->speed.y = -55.0f;
        }

        i_bl->m31C = 1.0f;
        i_bl->m314 = 24.0f;
        i_bl->m2C4 = i_this->current.pos;

        fopAcM_posMove(i_this, i_bl->mStts.GetCCMoveP());
        BG_check(i_bl);
        i_bl->m320 = i_this->current.pos.y;
        if (i_bl->m2D1 == 0) {
            i_bl->m320 = i_bl->mAcch.GetGroundH();
        }

        i_bl->m2D2 = 0;
        if (!(i_bl->mAcch.ChkGroundHit())) {
            i_this->speed.set(0.0f, 0.0f, 0.0f);
            i_this->gravity = 0.0f;
            i_this->speed.y = 1.0f + i_bl->m320;
            i_bl->m306 = 4;
        } else {
            i_bl->m306 = 0;
        }

        if (i_bl->m2D5 != 0xFF && !dComIfGs_isSwitch(i_bl->m2D5, dComIfGp_roomControl_getStayNo())) {
            i_this->actor_status &= ~0x100;
            i_bl->m2D2 = 6;
            i_bl->m306 = 0x46;
        }

        if (i_bl->m2D0 & 0x80) {
            i_this->max_health = 1;
            i_this->health = 1;
            i_bl->m2D3 = 1;
            i_bl->mSph.OnCoSetBit();
            i_this->current.angle.y = (s16)cM_rndFX(32767.0f);
            i_this->shape_angle.y = i_this->current.angle.y;
            i_this->actor_status |= 0x4000;
            i_bl->m2F6 = 4;
            i_this->actor_status &= ~0x100;
            i_this->attention_info.flags |= 0x10;
            i_bl->m2D2 = 0xA;
            i_bl->m306 = 0x64;
        } else {
            i_this->stealItemLeft = 1;
            i_bl->m2EA = i_this->stealItemLeft;
        }

        draw_SUB(i_bl);
    }
    return ret;
}

static actor_method_class l_daBL_Method = {
    (process_method_func)daBL_Create,
    (process_method_func)daBL_Delete,
    (process_method_func)daBL_Execute,
    (process_method_func)daBL_IsDelete,
    (process_method_func)daBL_Draw,
};

actor_process_profile_definition g_profile_BL = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_BL_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bl_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_BL_e,
    /* Actor SubMtd */ &l_daBL_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
