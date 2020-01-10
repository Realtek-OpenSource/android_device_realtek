#ifndef SP_CONST_DEF_H
#define SP_CONST_DEF_H

/*-----------------------------
Main control
------------------------------*/
#define SP_USE_ION_MEMORY 1
#define SP_WORKAROUND 1
#define SP_FIXED_BUG 1
#define SP_DATA_STRUCTURE_SIZE_SYNC_WITH_VO 0
#define SP_LITTLE_ENDIAN 1
#define SP_LITTLE_ENDIAN_SPECIAL 0
#define SP_CHECK_BUG 1
#define SP_CONFIG_RESOLUTION_BY_RPC 1
#define SP_FLUSH_NEW 1 // When RVSD recieve Flush command, it will record the BS_ring-wp at that moment. Then it will update BS_ring-rp with the recorded-wp later.
#define SP_FIXED_BUG_43980 1
#define SP_FIXED_BUG_44226 1
#define SP_FIXED_BUG_44312 1
#define SP_FIXED_BUG_44226 1
#define SP_FIXED_BUG_44221 1
#define SP_FIXED_BUG_OF_DVB 1
#define SP_AVOID_HANG_IN_RPC 1
#define RPC_SUPPORT_MULTI_CALLER
#define FIXED_COVERITY
#define SP_DUMMY_DECODER

/*-----------------------------
DBG info
------------------------------*/
#define SP_DBG_VO 0
#define SP_DBG_BS_RING 0
#define SP_TRACE_ENABLE 0
#define SP_ENABLE_DBG 0
#define SP_CHECK_PHY_ADDR_RANGE 0
#define SP_CHECK_VIRT_ADDR_RANGE 0
#define SP_CHECK_VTM 0
#define SP_DVB_PRINT_DATA_EN 0
#define SP_DISABLE_SEND_OBJ_TO_VO 0
#define SP_DISABLE_SPU 0    // it may NOT work ??
#define SP_DUMP_BS 0    // NOT display pictures

///////////////////

#define MAX_TAG_NUM         32
#define VP_PACKET_DWORD_SIZE 16
#define RPC_BUF_SIZE 256

#define SP_SUCCESS                 1
#define SP_FAIL                    0

#endif  // #ifndef SP_CONST_DEF_H


