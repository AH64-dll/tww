/**
 * d_a_obj_hsehi1.cpp
 * Object - Tower of the Gods - Command Melody monument & blue monument next to Companion Statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hsehi1.h"
#include "m_Do/m_Do_mtx.h"

/* 000000EC-00000130       .text __ct__15daObj_hsh_HIO_cFv */
daObj_hsh_HIO_c::daObj_hsh_HIO_c() {
    static const struct init_data_t {
        f32 m0;
        f32 m4;
        f32 m8;
        s16 mC;
        u8 mE;
    } init_data = {250.0f, 0.0f, 0.0f, 0x4000, 0};

    mNo = -1;
    m08 = init_data.m0;
    m0C = init_data.m4;
    m10 = init_data.m8;
    m14 = init_data.mC;
    m16 = init_data.mE;
}

static daObj_hsh_HIO_c l_HIO;

/* 00000130-000002A4       .text __dt__11daObj_hsh_cFv */
daObj_hsh_c::~daObj_hsh_c() {
    /* Nonmatching */
}

/* 000002A4-000002C4       .text daObj_hsh_XyCheckCB__FPvi */
static s16 daObj_hsh_XyCheckCB(void* i_this, int i_itemBtn) {
    return ((daObj_hsh_c*)i_this)->XyCheckCB(i_itemBtn);
}

/* 000002C4-000002E8       .text XyCheckCB__11daObj_hsh_cFi */
s16 daObj_hsh_c::XyCheckCB(int i_itemBtn) {
    return dComIfGp_getSelectItem(i_itemBtn) == dItemNo_WIND_WAKER_e ? TRUE : FALSE;
}

/* 000002E8-00000308       .text daObj_hsh_XyEventCB__FPvi */
static s16 daObj_hsh_XyEventCB(void* i_this, int i_itemBtn) {
    return ((daObj_hsh_c*)i_this)->XyEventCB(i_itemBtn);
}

/* 00000308-00000390       .text XyEventCB__11daObj_hsh_cFi */
s16 daObj_hsh_c::XyEventCB(int) {
    mDoAud_seStart(JA_SE_PRE_TAKT, &eyePos, 0, dComIfGp_getReverb(current.roomNo));
    m504 |= 1;
    m515 = 0;
    return m530;
}

/* 00000390-000003F4       .text particle_set__11daObj_hsh_cFUs */
void daObj_hsh_c::particle_set(unsigned short i_particleID) {
    dComIfGp_particle_set(i_particleID, &current.pos, &current.angle);
}

/* 000003F4-00000488       .text particle_set__11daObj_hsh_cFPP14JPABaseEmitterUs */
void daObj_hsh_c::particle_set(JPABaseEmitter** pEmitter, unsigned short i_particleID) {
    if (*pEmitter == NULL) {
        *pEmitter = dComIfGp_particle_set(i_particleID, &current.pos, &current.angle);
        if (*pEmitter != NULL) {
            (*pEmitter)->mFlags |= 0x40;
        }    }
}

/* 00000488-000004C4       .text emitterDelete__11daObj_hsh_cFPP14JPABaseEmitter */
void daObj_hsh_c::emitterDelete(JPABaseEmitter** pEmitter) {
    if (*pEmitter != NULL) {
        (*pEmitter)->mFlags &= ~0x40;
        (*pEmitter)->becomeInvalidEmitter();
        *pEmitter = NULL;
    }
}

/* 000004C4-00000568       .text setAttention__11daObj_hsh_cFb */
void daObj_hsh_c::setAttention(bool i_param) {
    if(!i_param) {
        return;
    }
    f32 eye_y;
    f32 attn_y;
    if(argument == 0) {
        eye_y = current.pos.y + 90.0f + l_HIO.m10;
        attn_y = current.pos.y + 180.0f + l_HIO.m0C;
    } else {
        eye_y = current.pos.y + 80.0f + l_HIO.m10;
        attn_y = current.pos.y + 120.0f + l_HIO.m0C;
    }
    eyePos.set(current.pos.x, eye_y, current.pos.z);
    attention_info.position.set(current.pos.x, attn_y, current.pos.z);
}

/* 00000568-000005AC       .text onOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::onOffDraw() {
    m504 |= 8;
    if(m4D4 != NULL) {
        dComIfG_Bgsp()->Release(m4D4);
    }
}

/* 000005AC-000005F4       .text offOffDraw__11daObj_hsh_cFv */
void daObj_hsh_c::offOffDraw() {
    m504 &= ~8;
    if(m4D4 != NULL) {
        dComIfG_Bgsp()->Regist(m4D4, this);
    }
}

/* 000005F4-0000062C       .text drawStop__11daObj_hsh_cFv */
void daObj_hsh_c::drawStop() {
    onOffDraw();
    emitterDelete(&m4A0);
}

/* 0000062C-0000064C       .text drawStart__11daObj_hsh_cFv */
void daObj_hsh_c::drawStart() {
    offOffDraw();
}

/* 0000064C-000006C8       .text setBaseMtx__11daObj_hsh_cFv */
void daObj_hsh_c::setBaseMtx() {
    J3DModel* model = mpModel;
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    PSMTXCopy(mDoMtx_stack_c::get(), m4A4);
}

/* 000006C8-00000910       .text createHeap__11daObj_hsh_cFv */
void daObj_hsh_c::createHeap() {
    /* Nonmatching */
}

/* 00000910-00000930       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000930-00000B44       .text create__11daObj_hsh_cFv */
cPhs_State daObj_hsh_c::create() {
    /* Nonmatching */
}

/* 00000C84-00000E60       .text init__11daObj_hsh_cFv */
void daObj_hsh_c::init() {
    /* Nonmatching */
}

/* 00000E60-00000EF4       .text action__11daObj_hsh_cFPv */
void daObj_hsh_c::action(void*) {
    /* Nonmatching */
}

/* 00000EF4-00000FBC       .text setAction__11daObj_hsh_cFM11daObj_hsh_cFPCvPvPv_iPv */
void daObj_hsh_c::setAction(int (daObj_hsh_c::*)(void*), void*) {
    /* Nonmatching */
}

/* 00000FBC-000010E8       .text waitAction__11daObj_hsh_cFPv */
void daObj_hsh_c::waitAction(void*) {
    /* Nonmatching */
}

/* 000010E8-00001214       .text talkAction__11daObj_hsh_cFPv */
void daObj_hsh_c::talkAction(void*) {
    /* Nonmatching */
}

/* 00001214-00001230       .text offAction__11daObj_hsh_cFPv */
void daObj_hsh_c::offAction(void*) {
    /* Nonmatching */
}

/* 00001230-00001278       .text deleteAction__11daObj_hsh_cFPv */
void daObj_hsh_c::deleteAction(void*) {
    /* Nonmatching */
}

/* 00001278-0000135C       .text eventOrder__11daObj_hsh_cFv */
void daObj_hsh_c::eventOrder() {
    /* Nonmatching */
}

/* 0000135C-0000140C       .text checkOrder__11daObj_hsh_cFv */
void daObj_hsh_c::checkOrder() {
    /* Nonmatching */
}

/* 0000140C-00001478       .text checkCommandTalk__11daObj_hsh_cFv */
void daObj_hsh_c::checkCommandTalk() {
    /* Nonmatching */
}

/* 00001478-000015E0       .text chkAttention__11daObj_hsh_cF4cXyzs */
void daObj_hsh_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 000015E0-00001784       .text eventProc__11daObj_hsh_cFv */
void daObj_hsh_c::eventProc() {
    /* Nonmatching */
}

/* 00001784-000017B0       .text eventEnd__11daObj_hsh_cFv */
void daObj_hsh_c::eventEnd() {
    /* Nonmatching */
}

/* 000017B0-000017B4       .text initialDefault__11daObj_hsh_cFi */
void daObj_hsh_c::initialDefault(int) {
    /* Nonmatching */
}

/* 000017B4-000017BC       .text actionDefault__11daObj_hsh_cFi */
void daObj_hsh_c::actionDefault(int) {
    /* Nonmatching */
}

/* 000017BC-00001938       .text initialLinkDispEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialLinkDispEvent(int) {
    /* Nonmatching */
}

/* 00001938-000019C0       .text initialMsgSetEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialMsgSetEvent(int) {
    /* Nonmatching */
}

/* 000019C0-000019E0       .text actionMsgSetEvent__11daObj_hsh_cFi */
void daObj_hsh_c::actionMsgSetEvent(int) {
    /* Nonmatching */
}

/* 000019E0-00001A40       .text actionMessageEvent__11daObj_hsh_cFi */
void daObj_hsh_c::actionMessageEvent(int) {
    /* Nonmatching */
}

/* 00001A40-00001ADC       .text actionTactEvent__11daObj_hsh_cFi */
void daObj_hsh_c::actionTactEvent(int) {
    /* Nonmatching */
}

/* 00001ADC-00001B3C       .text initialJudgeEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialJudgeEvent(int) {
    /* Nonmatching */
}

/* 00001B3C-00001C1C       .text initialAppearEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialAppearEvent(int) {
    /* Nonmatching */
}

/* 00001C1C-00001C74       .text actionAppearEvent__11daObj_hsh_cFi */
void daObj_hsh_c::actionAppearEvent(int) {
    /* Nonmatching */
}

/* 00001C74-00001D3C       .text initialDeleteEvent__11daObj_hsh_cFi */
void daObj_hsh_c::initialDeleteEvent(int) {
    /* Nonmatching */
}

/* 00001D3C-00001D88       .text actionDeleteEvent__11daObj_hsh_cFi */
void daObj_hsh_c::actionDeleteEvent(int) {
    /* Nonmatching */
}

/* 00001D88-00001DF4       .text talk_init__11daObj_hsh_cFv */
void daObj_hsh_c::talk_init() {
    /* Nonmatching */
}

/* 00001DF4-00001F1C       .text talk__11daObj_hsh_cFi */
void daObj_hsh_c::talk(int) {
    /* Nonmatching */
}

/* 00001F1C-00001F38       .text getMsg__11daObj_hsh_cFv */
void daObj_hsh_c::getMsg() {
    /* Nonmatching */
}

/* 00001F38-00001F78       .text next_msgStatus__11daObj_hsh_cFPUl */
void daObj_hsh_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001F78-00002098       .text execute__11daObj_hsh_cFv */
BOOL daObj_hsh_c::execute() {
    /* Nonmatching */
}

/* 00002098-00002158       .text draw__11daObj_hsh_cFv */
BOOL daObj_hsh_c::draw() {
    /* Nonmatching */
}

/* 00002158-00002178       .text daObj_hsh_Draw__FP11daObj_hsh_c */
static BOOL daObj_hsh_Draw(daObj_hsh_c* i_this) {
    return ((daObj_hsh_c*)i_this)->draw();
}

/* 00002178-00002198       .text daObj_hsh_Execute__FP11daObj_hsh_c */
static BOOL daObj_hsh_Execute(daObj_hsh_c* i_this) {
    return ((daObj_hsh_c*)i_this)->execute();
}

/* 00002198-000021A0       .text daObj_hsh_IsDelete__FP11daObj_hsh_c */
static BOOL daObj_hsh_IsDelete(daObj_hsh_c*) {
    return TRUE;
}

/* 000021A0-000021C8       .text daObj_hsh_Delete__FP11daObj_hsh_c */
static BOOL daObj_hsh_Delete(daObj_hsh_c* i_this) {
    ((daObj_hsh_c*)i_this)->~daObj_hsh_c();
    return TRUE;
}

/* 000021C8-000021E8       .text daObj_hsh_Create__FP10fopAc_ac_c */
static cPhs_State daObj_hsh_Create(fopAc_ac_c* i_this) {
    return ((daObj_hsh_c*)i_this)->create();
}

static actor_method_class l_daObj_hsh_Method = {
    (process_method_func)daObj_hsh_Create,
    (process_method_func)daObj_hsh_Delete,
    (process_method_func)daObj_hsh_Execute,
    (process_method_func)daObj_hsh_IsDelete,
    (process_method_func)daObj_hsh_Draw,
};

actor_process_profile_definition g_profile_Obj_HSH = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_HSH_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_hsh_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_HSH_e,
    /* Actor SubMtd */ &l_daObj_hsh_Method,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
