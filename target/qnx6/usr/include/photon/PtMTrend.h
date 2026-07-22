/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */



/*
 *	PtMTrend.h
 *		Header file for the PtMTrend widget class.
 *

 */
#ifndef __PT_MTREND_H_INCLUDED
#define __PT_MTREND_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtGraphic public
 */

extern PtWidgetClassRef_t *PtMTrend;

#define Pt_MTREND_ID		75

/* Resources */
#define Pt_ARG_MTREND_FLAGS			Pt_RESOURCE( Pt_MTREND_ID, 0 )
#define	Pt_ARG_MTREND_N_SAMPLES		Pt_RESOURCE( Pt_MTREND_ID, 1 )
#define	Pt_ARG_MTREND_N_GRAPHS		Pt_RESOURCE( Pt_MTREND_ID, 2 )
#define	Pt_ARG_MTREND_GRAPH_ATTR	Pt_RESOURCE( Pt_MTREND_ID, 3 )
#define	Pt_ARG_MTREND_GRAPH_STATE	Pt_RESOURCE( Pt_MTREND_ID, 4 )
#define	Pt_ARG_MTREND_GRAPH_DATA	Pt_RESOURCE( Pt_MTREND_ID, 5 )
#define	Pt_ARG_MTREND_TRACE_WIDTH	Pt_RESOURCE( Pt_MTREND_ID, 6 )
#define	Pt_ARG_MTREND_TRACE_COLOR	Pt_RESOURCE( Pt_MTREND_ID, 7 )
#define	Pt_ARG_MTREND_TRACE_DRAW_F	Pt_RESOURCE( Pt_MTREND_ID, 8 )
#define	Pt_ARG_MTREND_GRID_X		Pt_RESOURCE( Pt_MTREND_ID, 9 )
#define	Pt_ARG_MTREND_GRID_Y		Pt_RESOURCE( Pt_MTREND_ID, 10 )
#define	Pt_ARG_MTREND_GRID_COLOR	Pt_RESOURCE( Pt_MTREND_ID, 11 )
#define	Pt_ARG_MTREND_GRID_DRAW_F	Pt_RESOURCE( Pt_MTREND_ID, 12 )
#define	Pt_ARG_MTREND_ADVANCE_BY_N_SAMPLES	Pt_RESOURCE( Pt_MTREND_ID, 13 )

/* PtMTrendState values */
#define	Pt_MTREND_STATE_SHOWN	0
#define	Pt_MTREND_STATE_HIDDEN	1

/* PtMTrendDataMode values */
#define	Pt_MTREND_ADD	0		/* Add new data */
#define	Pt_MTREND_PUT	1		/* Replace data */

typedef struct pt_mtrend_data {
	int			mode;			/* see PtMTrendDataMode */
	unsigned	n_samples;
	unsigned	last_sample;
	const int	*data;
} PtMTrendData_t;

/* PtMTrend direction values */
#define	Pt_MTREND_HORZ_L2R			0
#define	Pt_MTREND_HORZ_R2L			1
#define	Pt_MTREND_VERT_T2B			2
#define	Pt_MTREND_VERT_B2T			3
#define	Pt_MTREND_DIRECTION_MASK	0x00000007

/* PtMTrend Grid values, if none is set - no grid */
#define	Pt_MTREND_GRID_NONE			0x00000000
#define Pt_MTREND_GRID_ABOVE		0x00000010
#define	Pt_MTREND_GRID_BELOW		0x00000020
#define	Pt_MTREND_GRID_MASK			0x00000070

/* PtMTrend Mode flag */
#define	Pt_MTREND_TRACE				0x00000100

/* PtMTrend blit flag (used in the default trend mode only) */
#define	Pt_MTREND_BLIT				0x00002000

#define	Pt_MTREND_ALWAYS_SCROLL		0x00004000

#define	Pt_MTREND_NO_SAMPLE_DATA	INT_MIN

struct pt_mtrend_graph_info;

struct pt_mtrend_attr {
	int			state;				/* see PtMTrendStates: SHOWN/HIDDEN */
	PgColor_t	color;				/* Line color */
	int			line_thickness;		/* Line thickness in pixels */
	int			join_type;			/* Line join type, see PgSetStrokeJoin() */
	int			min, max;			/* Minimum and maximum of samples */
	void		(*draw_f)( PtWidget_t *widget, PhTile_t *damage, struct pt_mtrend_graph_info *attr );
	int			zero[4];
};

struct pt_mtrend_graph_info {
	struct pt_mtrend_attr attr;
	int				n_samples;	/* Total number of available samples in the data buffer */
	int				last_value;	/* Contains last valid value */
	int				*data;
	int				zero[4];
};

/* Widget structure */
typedef struct Pt_mtrend_widget {
	PtBasicWidget_t		basic;
	
	int					mtrend_flags;

	unsigned			advance_by_n_samples;	
	unsigned			total_samples;		/* Total number of samples */
	unsigned			max_samples;		/* Maximum number of available samples */
	unsigned			max_width;			/* Maximum line width of all the graphs */
	unsigned			insert_sample;
	
	long long			npp;				/* Number of samples per pixel 
	                                         * multiplied by 1000000 */
	
	unsigned			n_graphs;			/* Total number of graphs */
	struct pt_mtrend_graph_info *graphs;
	
	struct {
		int				setup_width;
		PgColor_t		color;
		void			(*draw_f)( PtWidget_t *widget, PhTile_t *damage );
		/* calculated runtime values */
		unsigned		offset;
		PhPoint_t		pos;
		PhDim_t			dim;
		int				zero[4];
	} trace;
	
	struct {
		unsigned		x_grid_lines;
		unsigned		y_grid_lines;
		PgColor_t		color;
		void			(*draw_f)( PtWidget_t *widget, PhTile_t *damage );
		int				zero[4];
	} grid;	
	
	int					blit_error;
	int					zero[4];
	
} PtMTrendWidget_t;

typedef struct pt_mtrend_attr PtMTrendAttr_t;

/* Widget union */
typedef union Pt_mtrend_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtMTrendWidget_t			mtrend;
} PtMTrendUnion_t;

extern void PtMTrendAddData( PtWidget_t *trend, 
	unsigned graph_no, const int *newdata, unsigned nsamples 
	);
	
extern void PtMTrendChangeData( PtWidget_t *widget,
	unsigned graph_no, int const *newdata, unsigned last_sample, unsigned nsamples
	);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtMTrend.h $ $Rev: 219996 $" )
#endif
