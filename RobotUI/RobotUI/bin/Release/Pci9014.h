#ifndef __PCI9014_H__
#define __PCI9014_H__

#define PCI9014_API __declspec(dllimport)

typedef signed int             I32;
typedef unsigned int           U32;

#ifdef __cplusplus
extern "C" {
#endif
//open/close
PCI9014_API I32 WINAPI p9014_initial(I32* pCard_count, I32* pBoard_id);
PCI9014_API I32 WINAPI p9014_close();

//pulse input/output configuration
PCI9014_API I32 WINAPI p9014_set_pls_outmode(I32 axis, I32 pls_outmode);
PCI9014_API I32 WINAPI p9014_set_pls_iptmode(I32 axis, I32 pls_iptmode);

//parameter setting
PCI9014_API I32 WINAPI p9014_set_t_profile(I32 axis, double start_vel, double max_vel, double acc, double dec);
PCI9014_API I32 WINAPI p9014_set_s_profile(I32 axis, double start_vel, double max_vel, double acc, double dec, double jerk_percent);

//single axis driving functions
//dist_mode:  0  incremental coordinate; 1 - absolute coordinate
//vel_mode:   0  low speed mode without acc/dec;
//			  1 high speed mode without acc/dec;
//			  2 high speed mode with acc/dec
PCI9014_API I32 WINAPI p9014_pmove(I32 axis, I32 dist, I32 dist_mode = 0, I32 vel_mode = 2);
PCI9014_API I32 WINAPI p9014_vmove(I32 axis, I32 plus_dir, I32 vel_mode = 2);
PCI9014_API I32 WINAPI p9014_stop(I32 axis, int EmgStop);

//home return
//mode:		0	- low speed, ORG only;
//			2   - low speed,  ORG + EZ;
PCI9014_API I32 WINAPI p9014_home_config(I32 axis, I32 mode, I32 org_level, I32 ez_level);
PCI9014_API I32 WINAPI p9014_home_move(I32 axis, I32 PlusDir);

//position counter control
PCI9014_API I32 WINAPI p9014_set_pos(I32 axis, I32 cntr_no, I32 pos);
PCI9014_API I32 WINAPI p9014_get_pos(I32 axis, I32 cntr_no, I32* pPos);

//I/O control
PCI9014_API I32 WINAPI p9014_set_do(I32 card_no, U32 data);
PCI9014_API I32 WINAPI p9014_set_do_bit(I32 card_no, U32 bit_no, U32 data);
PCI9014_API I32 WINAPI p9014_get_do(I32 card_no, U32* pData);
PCI9014_API I32 WINAPI p9014_get_di(I32 card_no, U32* pData);
PCI9014_API I32 WINAPI p9014_get_di_bit(I32 card_no, U32 bit_no, U32* pData);

//mechanical switch status
PCI9014_API I32 WINAPI p9014_get_io_status(I32 axis, U32* pStatus);

//motion status
PCI9014_API I32 WINAPI p9014_get_motion_status(I32 axis, U32* pStatus);
PCI9014_API I32 WINAPI p9014_get_current_speed(I32 axis, double* pSpeed);

//version
PCI9014_API I32 WINAPI p9014_get_version(I32 card_no, U32* pApi_ver, U32* pDriver_ver, U32 *pLogic_ver);

//2011-6-17 added
//set End Limit Input active level
PCI9014_API I32 WINAPI p9014_set_el_level(I32 axis, I32 active_level);

//2012-3-11
PCI9014_API I32 WINAPI p9014_set_error_stop_mode(I32 axis, I32 stop_mode);
PCI9014_API I32 WINAPI p9014_set_alarm(I32 axis, I32 enable, I32 active_level);

//2013-7-25
PCI9014_API I32  WINAPI p9014_comp_enable(I32 card_no, I32 enable, I32 active_level, I32 ref_source, I32 length);
PCI9014_API I32  WINAPI p9014_comp_get_fifoStatus(I32 card_no, U32* stat);
PCI9014_API I32  WINAPI p9014_comp_add_ref(I32 card_no, I32 PosRef);
PCI9014_API I32  WINAPI p9014_comp_get_curRef(I32 card_no, I32 *PosRef);
PCI9014_API I32  WINAPI p9014_comp_clr_fifo(I32 card_no);
PCI9014_API I32  WINAPI p9014_comp_get_matchCount(I32 card_no, U32 * Count);
PCI9014_API I32  WINAPI p9014_comp_clr_matchCount(I32 card_no);

PCI9014_API I32 WINAPI p9014_get_revision(I32 card_no, U32 *pLogic_revision);
#ifdef __cplusplus
}
#endif

#endif



