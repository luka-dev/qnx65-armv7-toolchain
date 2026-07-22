/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
/* $XConsortium: keysymdef.h,v 1.14 91/02/14 15:26:22 rws Exp $ */

/***********************************************************
Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#define Pk_BASIC_LATIN
#define Pk_VoidSymbol				0xFFFFFF	/* void symbol */
#define	Pk_InvalidSymbol			~0
#define Pk_OEM_KeyCap				0x80000000

#define	Pk_KF_Key_Down				0x00000001
#define	Pk_KF_Key_Repeat			0x00000002
#define Pk_KF_Scan_Valid			0x00000020
#define Pk_KF_Sym_Valid				0x00000040
#define Pk_KF_Cap_Valid				0x00000080
#define	Pk_KF_Sym_Valid_Ex			0x00000100
#define Pk_KF_Compose				0x40000000
#define Pk_KF_Mapping_Changed		0x20000000 

#define Pk_KM_Shift					0x00000001
#define Pk_KM_Ctrl					0x00000002
#define Pk_KM_Alt					0x00000004
#define Pk_KM_AltGr					0x00000008
#define Pk_KM_Shl3					0x00000010
#define Pk_KM_Mod6					0x00000020
#define Pk_KM_Mod7					0x00000040
#define Pk_KM_Mod8					0x00000080

#define Pk_KM_Shift_Lock			0x00000100
#define Pk_KM_Ctrl_Lock				0x00000200
#define Pk_KM_Alt_Lock				0x00000400
#define Pk_KM_AltGr_Lock			0x00000800
#define Pk_KM_Shl3_Lock				0x00001000
#define Pk_KM_Mod6_Lock				0x00002000
#define Pk_KM_Mod7_Lock				0x00004000
#define Pk_KM_Mod8_Lock				0x00008000

#define Pk_KM_Caps_Lock				0x00010000
#define Pk_KM_Num_Lock				0x00020000
#define Pk_KM_Scroll_Lock			0x00040000

#define Pk_KM_User1					0x80000000
#define Pk_KM_User2					0x40000000
#define Pk_KM_User3					0x20000000
#define Pk_KM_User4					0x10000000

/* the following defines will use the key_flags feild from PhKeyEvent_t */
#define	PkIsKeyDown( f )		((f & Pk_KF_Key_Down) != 0)
#define	PkIsFirstDown( f )		((f & (Pk_KF_Key_Down | Pk_KF_Key_Repeat)) == Pk_KF_Key_Down)

/*	typedef struct {
		char *		Ano;
		long		Val;
	} __DefAno_t;
    Pk_KeyDefAno */

#define Pk_BackSpace		0xF008	/* back space, back char */
#define Pk_Tab				0xF009
#define Pk_Linefeed			0xF00A	/* Linefeed, LF */
#define Pk_Clear			0xF00B
#define Pk_Return			0xF00D	/* Return, enter */
#define Pk_Pause			0xF013	/* Pause, hold */
#define Pk_Scroll_Lock		0xF014
#define Pk_Escape			0xF01B
#define Pk_Delete			0xF0FF	/* Delete, rubout */

#define	_Pk_Photon_Shutdown		'PhDn'


/* International & multi-key character composition */

#define Pk_Multi_key		0xF020  /* Multi-key character compose */

/* Japanese keyboard support */

#define Pk_Kanji		0xF021	/* Kanji, Kanji convert */
#define Pk_Muhenkan		0xF022  /* Cancel Conversion */
#define Pk_Henkan_Mode		0xF023  /* Start/Stop Conversion */
#define Pk_Henkan		0xF023  /* Alias for Henkan_Mode */
#define Pk_Romaji		0xF024  /* to Romaji */
#define Pk_Hiragana		0xF025  /* to Hiragana */
#define Pk_Katakana		0xF026  /* to Katakana */
#define Pk_Hiragana_Katakana	0xF027  /* Hiragana/Katakana toggle */
#define Pk_Zenkaku		0xF028  /* to Zenkaku */
#define Pk_Hankaku		0xF029  /* to Hankaku */
#define Pk_Zenkaku_Hankaku	0xF02A  /* Zenkaku/Hankaku toggle */
#define Pk_Touroku		0xF02B  /* Add to Dictionary */
#define Pk_Massyo		0xF02C  /* Delete from Dictionary */
#define Pk_Kana_Lock		0xF02D  /* Kana Lock */
#define Pk_Kana_Shift		0xF02E  /* Kana Shift */
#define Pk_Eisu_Shift		0xF02F  /* Alphanumeric Shift */
#define Pk_Eisu_toggle		0xF030  /* Alphanumeric toggle */

/* Cursor control & motion */

#define Pk_Home			0xF050
#define Pk_Left			0xF051	/* Move left, left arrow */
#define Pk_Up			0xF052	/* Move up, up arrow */
#define Pk_Right		0xF053	/* Move right, right arrow */
#define Pk_Down			0xF054	/* Move down, down arrow */
#define Pk_Prior		0xF055	/* Prior, previous */
#define Pk_Pg_Up		0xF055	/* Prior, previous */
#define Pk_Next			0xF056	/* Next */
#define Pk_Pg_Down		0xF056	/* Next */
#define Pk_End			0xF057	/* EOL */
#define Pk_Begin		0xF058	/* BOL */


/* Misc Functions */

#define Pk_Select		0xF060	/* Select, mark */
#define Pk_Print		0xF061
#define Pk_Execute		0xF062	/* Execute, run, do */
#define Pk_Insert		0xF063	/* Insert, insert here */
#define Pk_Undo			0xF065	/* Undo, oops */
#define Pk_Redo			0xF066	/* redo, again */
#define Pk_Menu			0xF067
#define Pk_Find			0xF068	/* Find, search */
#define Pk_Cancel		0xF069	/* Cancel, stop, abort, exit */
#define Pk_Help			0xF06A	/* Help, ? */
#define Pk_Break		0xF06B
#define Pk_Mode_switch		0xF07E	/* Character set switch */
#define Pk_script_switch        0xF07E  /* Alias for mode_switch */
#define Pk_Num_Lock		0xF07F

/* Keypad Functions, keypad numbers cleverly chosen to map to ascii */

#define Pk_KP_Space		0xF080	/* space */
#define Pk_KP_Tab		0xF089
#define Pk_KP_Enter		0xF08D	/* enter */
#define Pk_KP_F1		0xF091	/* PF1, KP_A, ... */
#define Pk_KP_F2		0xF092
#define Pk_KP_F3		0xF093
#define Pk_KP_F4		0xF094
#define Pk_KP_Equal		0xF0BD	/* equals */
#define Pk_KP_Multiply		0xF0AA
#define Pk_KP_Add		0xF0AB
#define Pk_KP_Separator		0xF0AC	/* separator, often comma */
#define Pk_KP_Subtract		0xF0AD
#define Pk_KP_Decimal		0xF0AE
#define Pk_KP_Divide		0xF0AF

#define Pk_KP_0			0xF0B0
#define Pk_KP_1			0xF0B1
#define Pk_KP_2			0xF0B2
#define Pk_KP_3			0xF0B3
#define Pk_KP_4			0xF0B4
#define Pk_KP_5			0xF0B5
#define Pk_KP_6			0xF0B6
#define Pk_KP_7			0xF0B7
#define Pk_KP_8			0xF0B8
#define Pk_KP_9			0xF0B9



/*
 * Auxilliary Functions; note the duplicate definitions for left and right
 * function keys;  Sun keyboards and a few other manufactures have such
 * function key groups on the left and/or right sides of the keyboard.
 * We've not found a keyboard with more than 35 function keys total.
 */

#define Pk_F1			0xF0BE
#define Pk_F2			0xF0BF
#define Pk_F3			0xF0C0
#define Pk_F4			0xF0C1
#define Pk_F5			0xF0C2
#define Pk_F6			0xF0C3
#define Pk_F7			0xF0C4
#define Pk_F8			0xF0C5
#define Pk_F9			0xF0C6
#define Pk_F10			0xF0C7
#define Pk_F11			0xF0C8
#define Pk_L1			0xF0C8
#define Pk_F12			0xF0C9
#define Pk_L2			0xF0C9
#define Pk_F13			0xF0CA
#define Pk_L3			0xF0CA
#define Pk_F14			0xF0CB
#define Pk_L4			0xF0CB
#define Pk_F15			0xF0CC
#define Pk_L5			0xF0CC
#define Pk_F16			0xF0CD
#define Pk_L6			0xF0CD
#define Pk_F17			0xF0CE
#define Pk_L7			0xF0CE
#define Pk_F18			0xF0CF
#define Pk_L8			0xF0CF
#define Pk_F19			0xF0D0
#define Pk_L9			0xF0D0
#define Pk_F20			0xF0D1
#define Pk_L10			0xF0D1
#define Pk_F21			0xF0D2
#define Pk_R1			0xF0D2
#define Pk_F22			0xF0D3
#define Pk_R2			0xF0D3
#define Pk_F23			0xF0D4
#define Pk_R3			0xF0D4
#define Pk_F24			0xF0D5
#define Pk_R4			0xF0D5
#define Pk_F25			0xF0D6
#define Pk_R5			0xF0D6
#define Pk_F26			0xF0D7
#define Pk_R6			0xF0D7
#define Pk_F27			0xF0D8
#define Pk_R7			0xF0D8
#define Pk_F28			0xF0D9
#define Pk_R8			0xF0D9
#define Pk_F29			0xF0DA
#define Pk_R9			0xF0DA
#define Pk_F30			0xF0DB
#define Pk_R10			0xF0DB
#define Pk_F31			0xF0DC
#define Pk_R11			0xF0DC
#define Pk_F32			0xF0DD
#define Pk_R12			0xF0DD
#define Pk_F33			0xF0DE
#define Pk_R13			0xF0DE
#define Pk_F34			0xF0DF
#define Pk_R14			0xF0DF
#define Pk_F35			0xF0E0
#define Pk_R15			0xF0E0

/* Modifiers */

#define Pk_Shift_L		0xF0E1	/* Left shift */
#define Pk_Shift_R		0xF0E2	/* Right shift */
#define Pk_Control_L		0xF0E3	/* Left control */
#define Pk_Control_R		0xF0E4	/* Right control */
#define Pk_Caps_Lock		0xF0E5	/* Caps lock */
#define Pk_Shift_Lock		0xF0E6	/* Shift lock */

#define Pk_Meta_L		0xF0E7	/* Left meta */
#define Pk_Meta_R		0xF0E8	/* Right meta */
#define Pk_Alt_L		0xF0E9	/* Left alt */
#define Pk_Alt_R		0xF0EA	/* Right alt */
#define Pk_Super_L		0xF0EB	/* Left super */
#define Pk_Super_R		0xF0EC	/* Right super */
#define Pk_Hyper_L		0xF0ED	/* Left hyper */
#define Pk_Hyper_R		0xF0EE	/* Right hyper */

/*
 *  Basic Latin
 */
#ifdef Pk_BASIC_LATIN
#define Pk_space               0x020
#define Pk_exclam              0x021
#define Pk_quotedbl            0x022
#define Pk_numbersign          0x023
#define Pk_dollar              0x024
#define Pk_percent             0x025
#define Pk_ampersand           0x026
#define Pk_apostrophe          0x027
#define Pk_quoteright          0x027	/* deprecated */
#define Pk_parenleft           0x028
#define Pk_parenright          0x029
#define Pk_asterisk            0x02a
#define Pk_plus                0x02b
#define Pk_comma               0x02c
#define Pk_minus               0x02d
#define Pk_period              0x02e
#define Pk_slash               0x02f
#define Pk_0                   0x030
#define Pk_1                   0x031
#define Pk_2                   0x032
#define Pk_3                   0x033
#define Pk_4                   0x034
#define Pk_5                   0x035
#define Pk_6                   0x036
#define Pk_7                   0x037
#define Pk_8                   0x038
#define Pk_9                   0x039
#define Pk_colon               0x03a
#define Pk_semicolon           0x03b
#define Pk_less                0x03c
#define Pk_equal               0x03d
#define Pk_greater             0x03e
#define Pk_question            0x03f
#define Pk_at                  0x040
#define Pk_A                   0x041
#define Pk_B                   0x042
#define Pk_C                   0x043
#define Pk_D                   0x044
#define Pk_E                   0x045
#define Pk_F                   0x046
#define Pk_G                   0x047
#define Pk_H                   0x048
#define Pk_I                   0x049
#define Pk_J                   0x04a
#define Pk_K                   0x04b
#define Pk_L                   0x04c
#define Pk_M                   0x04d
#define Pk_N                   0x04e
#define Pk_O                   0x04f
#define Pk_P                   0x050
#define Pk_Q                   0x051
#define Pk_R                   0x052
#define Pk_S                   0x053
#define Pk_T                   0x054
#define Pk_U                   0x055
#define Pk_V                   0x056
#define Pk_W                   0x057
#define Pk_X                   0x058
#define Pk_Y                   0x059
#define Pk_Z                   0x05a
#define Pk_bracketleft         0x05b
#define Pk_backslash           0x05c
#define Pk_bracketright        0x05d
#define Pk_asciicircum         0x05e
#define Pk_carrot		       0x05e
#define Pk_underscore          0x05f
#define Pk_grave               0x060
#define Pk_quoteleft           0x060	/* deprecated */
#define Pk_a                   0x061
#define Pk_b                   0x062
#define Pk_c                   0x063
#define Pk_d                   0x064
#define Pk_e                   0x065
#define Pk_f                   0x066
#define Pk_g                   0x067
#define Pk_h                   0x068
#define Pk_i                   0x069
#define Pk_j                   0x06a
#define Pk_k                   0x06b
#define Pk_l                   0x06c
#define Pk_m                   0x06d
#define Pk_n                   0x06e
#define Pk_o                   0x06f
#define Pk_p                   0x070
#define Pk_q                   0x071
#define Pk_r                   0x072
#define Pk_s                   0x073
#define Pk_t                   0x074
#define Pk_u                   0x075
#define Pk_v                   0x076
#define Pk_w                   0x077
#define Pk_x                   0x078
#define Pk_y                   0x079
#define Pk_z                   0x07a
#define Pk_braceleft           0x07b
#define Pk_bar                 0x07c
#define Pk_braceright          0x07d
#define Pk_asciitilde          0x07e
#endif /* Pk_BASIC_LATIN */

/*
 *  Latin-1 Supplement
 */
#ifdef Pk_LATIN1
#define Pk_nobreakspace        0x0a0
#define Pk_exclamdown          0x0a1
#define Pk_cent        	       0x0a2
#define Pk_sterling            0x0a3
#define Pk_currency            0x0a4
#define Pk_yen                 0x0a5
#define Pk_brokenbar           0x0a6
#define Pk_section             0x0a7
#define Pk_diaeresis           0x0a8
#define Pk_copyright           0x0a9
#define Pk_ordfeminine         0x0aa
#define Pk_guillemotleft       0x0ab	/* left angle quotation mark */
#define Pk_notsign             0x0ac
#define Pk_hyphen              0x0ad
#define Pk_registered          0x0ae
#define Pk_macron              0x0af
#define Pk_degree              0x0b0
#define Pk_plusminus           0x0b1
#define Pk_twosuperior         0x0b2
#define Pk_threesuperior       0x0b3
#define Pk_acute               0x0b4
#define Pk_mu                  0x0b5
#define Pk_paragraph           0x0b6
#define Pk_periodcentered      0x0b7
#define Pk_cedilla             0x0b8
#define Pk_onesuperior         0x0b9
#define Pk_masculine           0x0ba
#define Pk_guillemotright      0x0bb	/* right angle quotation mark */
#define Pk_onequarter          0x0bc
#define Pk_onehalf             0x0bd
#define Pk_threequarters       0x0be
#define Pk_questiondown        0x0bf
#define Pk_Agrave              0x0c0
#define Pk_Aacute              0x0c1
#define Pk_Acircumflex         0x0c2
#define Pk_Atilde              0x0c3
#define Pk_Adiaeresis          0x0c4
#define Pk_Aring               0x0c5
#define Pk_AE                  0x0c6
#define Pk_Ccedilla            0x0c7
#define Pk_Egrave              0x0c8
#define Pk_Eacute              0x0c9
#define Pk_Ecircumflex         0x0ca
#define Pk_Ediaeresis          0x0cb
#define Pk_Igrave              0x0cc
#define Pk_Iacute              0x0cd
#define Pk_Icircumflex         0x0ce
#define Pk_Idiaeresis          0x0cf
#define Pk_ETH                 0x0d0
#define Pk_Eth                 0x0d0	/* deprecated */
#define Pk_Ntilde              0x0d1
#define Pk_Ograve              0x0d2
#define Pk_Oacute              0x0d3
#define Pk_Ocircumflex         0x0d4
#define Pk_Otilde              0x0d5
#define Pk_Odiaeresis          0x0d6
#define Pk_multiply            0x0d7
#define Pk_Ooblique            0x0d8
#define Pk_Ugrave              0x0d9
#define Pk_Uacute              0x0da
#define Pk_Ucircumflex         0x0db
#define Pk_Udiaeresis          0x0dc
#define Pk_Yacute              0x0dd
#define Pk_THORN               0x0de
#define Pk_Thorn               0x0de	/* deprecated */
#define Pk_ssharp              0x0df
#define Pk_agrave              0x0e0
#define Pk_aacute              0x0e1
#define Pk_acircumflex         0x0e2
#define Pk_atilde              0x0e3
#define Pk_adiaeresis          0x0e4
#define Pk_aring               0x0e5
#define Pk_ae                  0x0e6
#define Pk_ccedilla            0x0e7
#define Pk_egrave              0x0e8
#define Pk_eacute              0x0e9
#define Pk_ecircumflex         0x0ea
#define Pk_ediaeresis          0x0eb
#define Pk_igrave              0x0ec
#define Pk_iacute              0x0ed
#define Pk_icircumflex         0x0ee
#define Pk_idiaeresis          0x0ef
#define Pk_eth                 0x0f0
#define Pk_ntilde              0x0f1
#define Pk_ograve              0x0f2
#define Pk_oacute              0x0f3
#define Pk_ocircumflex         0x0f4
#define Pk_otilde              0x0f5
#define Pk_odiaeresis          0x0f6
#define Pk_division            0x0f7
#define Pk_oslash              0x0f8
#define Pk_ugrave              0x0f9
#define Pk_uacute              0x0fa
#define Pk_ucircumflex         0x0fb
#define Pk_udiaeresis          0x0fc
#define Pk_yacute              0x0fd
#define Pk_thorn               0x0fe
#define Pk_ydiaeresis          0x0ff
#endif /* Pk_LATIN1 */

/*
 *	Latin Extended-A
 */
#ifdef Pk_LATIN_EXTENDED_A
#define Pk_Amacron                        0x0100
#define Pk_amacron                        0x0101
#define Pk_Abreve                         0x0102
#define Pk_abreve                         0x0103
#define Pk_Aogonek                        0x0104
#define Pk_aogonek                        0x0105
#define Pk_Cacute                         0x0106
#define Pk_cacute                         0x0107
#define Pk_Ccircumflex                    0x0108
#define Pk_ccircumflex                    0x0109
#define Pk_Cabovedot                      0x010A
#define Pk_cabovedot                      0x010B
#define Pk_Ccaron                         0x010C
#define Pk_ccaron                         0x010D
#define Pk_Dcaron                         0x010E
#define Pk_dcaron                         0x010F
#define Pk_Dstroke                        0x0110
#define Pk_dstroke                        0x0111
#define Pk_Emacron                        0x0112
#define Pk_emacron                        0x0113
#define Pk_Ebreve                         0x0114
#define Pk_ebreve                         0x0115
#define Pk_Eabovedot                      0x0116
#define Pk_eabovedot                      0x0117
#define Pk_Eogonek                        0x0118
#define Pk_eogonek                        0x0119
#define Pk_Ecaron                         0x011A
#define Pk_ecaron                         0x011B
#define Pk_Gcircumflex                    0x011C
#define Pk_gcircumflex                    0x011D
#define Pk_Gbreve                         0x011E
#define Pk_gbreve                         0x011F
#define Pk_Gabovedot                      0x0120
#define Pk_gabovedot                      0x0121
#define Pk_Gcedilla                       0x0122
#define Pk_gcedilla                       0x0123
#define Pk_Hcircumflex                    0x0124
#define Pk_hcircumflex                    0x0125
#define Pk_Hstroke                        0x0126
#define Pk_hstroke                        0x0127
#define Pk_Itilde                         0x0128
#define Pk_itilde                         0x0129
#define Pk_Imacron                        0x012A
#define Pk_imacron                        0x012B
#define Pk_Ibreve                         0x012C
#define Pk_ibreve                         0x012D
#define Pk_Iogonek                        0x012E
#define Pk_iogonek                        0x012F
#define Pk_Iabovedot                      0x0130
#define Pk_idotless                       0x0131
#define Pk_IJ                             0x0132
#define Pk_ij                             0x0133
#define Pk_Jcircumflex                    0x0134
#define Pk_jcircumflex                    0x0135
#define Pk_Kcedilla                       0x0136
#define Pk_kcedilla                       0x0137
#define Pk_kra                            0x0138   /* Greenlandic */
#define Pk_Lacute                         0x0139
#define Pk_lacute                         0x013A
#define Pk_Lcedilla                       0x013B
#define Pk_lcedilla                       0x013C
#define Pk_Lcaron                         0x013D
#define Pk_lcaron                         0x013E
#define Pk_Lmiddledot                     0x013F
#define Pk_lmiddledot                     0x0140
#define Pk_Lstroke                        0x0141
#define Pk_lstroke                        0x0142
#define Pk_Nacute                         0x0143
#define Pk_nacute                         0x0144
#define Pk_Ncedilla                       0x0145
#define Pk_ncedilla                       0x0146
#define Pk_Ncaron                         0x0147
#define Pk_ncaron                         0x0148
#define Pk_napostrophe                    0x0149
#define Pk_ENG                            0x014A   /* Sami */
#define Pk_eng                            0x014B   /* Sami */
#define Pk_Omacron                        0x014C
#define Pk_omacron                        0x014D
#define Pk_Obreve                         0x014E
#define Pk_obreve                         0x014F
#define Pk_Odoubleacute                   0x0150
#define Pk_odoubleacute                   0x0151
#define Pk_OE                             0x0152
#define Pk_oe                             0x0153
#define Pk_Racute                         0x0154
#define Pk_racute                         0x0155
#define Pk_Rcedilla                       0x0156
#define Pk_rcedilla                       0x0157
#define Pk_Rcaron                         0x0158
#define Pk_rcaron                         0x0159
#define Pk_Sacute                         0x015A
#define Pk_sacute                         0x015B
#define Pk_Scircumflex                    0x015C
#define Pk_scircumflex                    0x015D
#define Pk_Scedilla                       0x015E
#define Pk_scedilla                       0x015F
#define Pk_Scaron                         0x0160
#define Pk_scaron                         0x0161
#define Pk_Tcedilla                       0x0162
#define Pk_tcedilla                       0x0163
#define Pk_Tcaron                         0x0164
#define Pk_tcaron                         0x0165
#define Pk_Tstroke                        0x0166
#define Pk_tstroke                        0x0167
#define Pk_Utilde                         0x0168
#define Pk_utilde                         0x0169
#define Pk_Umacron                        0x016A
#define Pk_umacron                        0x016B
#define Pk_Ubreve                         0x016C
#define Pk_ubreve                         0x016D
#define Pk_Uringabove                     0x016E
#define Pk_uringabove                     0x016F
#define Pk_Udoubleacute                   0x0170
#define Pk_udoubleacute                   0x0171
#define Pk_Uogonek                        0x0172
#define Pk_uogonek                        0x0173
#define Pk_Wcircumflex                    0x0174
#define Pk_wcircumflex                    0x0175
#define Pk_Ycircumflex                    0x0176
#define Pk_ycircumflex                    0x0177
#define Pk_Ydiaeresis                     0x0178
#define Pk_Zacute                         0x0179
#define Pk_zacute                         0x017A
#define Pk_Zabovedot                      0x017B
#define Pk_zabovedot                      0x017C
#define Pk_Zcaron                         0x017D
#define Pk_zcaron                         0x017E
#define Pk_slong                          0x017F
#endif /* Pk_LATIN_EXTENDED_A */

/*
 *	Latin Extended-B
 */
#ifdef Pk_LATIN_EXTENDED_B
#define Pk_bstroke                        0x0180
#define Pk_Bhook                          0x0181
#define Pk_Btopbar                        0x0182
#define Pk_btopbar                        0x0183
#define Pk_ToneSix                        0x0184
#define Pk_tonesix                        0x0185
#define Pk_Oopen                          0x0186
#define Pk_Chook                          0x0187
#define Pk_chook                          0x0188
#define Pk_Dafrican                       0x0189
#define Pk_Dhook                          0x018A
#define Pk_Dtopbar                        0x018B
#define Pk_dtopbar                        0x018C
#define Pk_turneddelta                    0x018D
#define Pk_ereversed                      0x018E
#define Pk_SCHWA                          0x018F
#define Pk_Eopen                          0x0190
#define Pk_Fhook                          0x0191
#define Pk_fhook                          0x0192
#define Pk_Ghook                          0x0193
#define Pk_GAMMA                          0x0194
#define Pk_hv                             0x0195
#define Pk_IOTA                           0x0196
#define Pk_Istroke                        0x0197
#define Pk_Khook                          0x0198
#define Pk_khook                          0x0199
#define Pk_lbar                           0x019A
#define Pk_lambdastroke                   0x019B
#define Pk_Mturned                        0x019C
#define Pk_Nlefthook                      0x019D
#define Pk_nlongrightleg                  0x019E
#define Pk_Omiddletilde                   0x019F
#define Pk_Ohorn                          0x01A0
#define Pk_ohorn                          0x01A1
#define Pk_OI                             0x01A2
#define Pk_oi                             0x01A3
#define Pk_Phook                          0x01A4
#define Pk_phook                          0x01A5
#define Pk_yr                             0x01A6
#define Pk_ToneTwo                        0x01A7
#define Pk_tonetwo                        0x01A8
#define Pk_ESH                            0x01A9
#define Pk_eshreversedloop                0x01AA
#define Pk_tpalatalhook                   0x01AB
#define Pk_Thook                          0x01AC
#define Pk_thook                          0x01AD
#define Pk_Tretroflexhook                 0x01AE
#define Pk_Uhorn                          0x01AF
#define Pk_uhorn                          0x01B0
#define Pk_UPSILON                        0x01B1
#define Pk_Vhook                          0x01B2
#define Pk_Yhook                          0x01B3
#define Pk_yhook                          0x01B4
#define Pk_Zstroke                        0x01B5
#define Pk_zstroke                        0x01B6
#define Pk_EZH                            0x01B7
#define Pk_EZHreversed                    0x01B8
#define Pk_ezhreversed                    0x01B9
#define Pk_ezhtail                        0x01BA
#define Pk_2stroke                        0x01BB
#define Pk_ToneFive                       0x01BC
#define Pk_tonefive                       0x01BD
#define Pk_glottalstopinvertedstroke      0x01BE
#define Pk_wynn                           0x01BF
#define Pk_dentalclick                    0x01C0
#define Pk_lateralclick                   0x01C1
#define Pk_alveolarclick                  0x01C2
#define Pk_retroflexclick                 0x01C3
#define Pk_DZcaron                        0x01C4
#define Pk_Dzcaron                        0x01C5
#define Pk_dzcaron                        0x01C6
#define Pk_LJ                             0x01C7
#define Pk_Lj                             0x01C8
#define Pk_lj                             0x01C9
#define Pk_NJ                             0x01CA
#define Pk_Nj                             0x01CB
#define Pk_nj                             0x01CC
#define Pk_Acaron                         0x01CD
#define Pk_acaron                         0x01CE
#define Pk_Icaron                         0x01CF
#define Pk_icaron                         0x01D0
#define Pk_Ocaron                         0x01D1
#define Pk_ocaron                         0x01D2
#define Pk_Ucaron                         0x01D3
#define Pk_ucaron                         0x01D4
#define Pk_Udiaeresismacron               0x01D5
#define Pk_udiaeresismacron               0x01D6
#define Pk_Udiaeresisacute                0x01D7
#define Pk_udiaeresisacute                0x01D8
#define Pk_Udiaeresiscaron                0x01D9
#define Pk_udiaeresiscaron                0x01DA
#define Pk_Udiaeresisgrave                0x01DB
#define Pk_udiaeresisgrave                0x01DC
#define Pk_eturned                        0x01DD
#define Pk_Adiaeresismacron               0x01DE
#define Pk_adiaeresismacron               0x01DF
#define Pk_Aabovedotmacron                0x01E0
#define Pk_aabovedotmacron                0x01E1
#define Pk_AEmacron                       0x01E2
#define Pk_aemacron                       0x01E3
#define Pk_Gstroke                        0x01E4
#define Pk_gstroke                        0x01E5
#define Pk_Gcaron                         0x01E6
#define Pk_gcaron                         0x01E7
#define Pk_Kcaron                         0x01E8
#define Pk_kcaron                         0x01E9
#define Pk_Oogonek                        0x01EA
#define Pk_oogonek                        0x01EB
#define Pk_Oogonekmacron                  0x01EC
#define Pk_oogonekmacron                  0x01ED
#define Pk_EZHcaron                       0x01EE
#define Pk_ezhcaron                       0x01EF
#define Pk_jcaron                         0x01F0
#define Pk_DZ                             0x01F1
#define Pk_Dz                             0x01F2
#define Pk_dz                             0x01F3
#define Pk_Gacute                         0x01F4
#define Pk_gacute                         0x01F5

#define Pk_Aaboveringacute                0x01FA
#define Pk_aaboveringacute                0x01FB
#define Pk_AEacute                        0x01FC
#define Pk_aeacute                        0x01FD
#define Pk_Ostrokeacute                   0x01FE
#define Pk_ostrokeacute                   0x01FF

#define Pk_Adoublegrave                   0x0200
#define Pk_adoublegrave                   0x0201
#define Pk_Ainvertedbreve                 0x0202
#define Pk_ainvertedbreve                 0x0203
#define Pk_Edoublegrave                   0x0204
#define Pk_edoublegrave                   0x0205
#define Pk_Einvertedbreve                 0x0206
#define Pk_einvertedbreve                 0x0207
#define Pk_Idoublegrave                   0x0208
#define Pk_idoublegrave                   0x0209
#define Pk_Iinvertedbreve                 0x020A
#define Pk_iinvertedbreve                 0x020B
#define Pk_Odoublegrave                   0x020C
#define Pk_odoublegrave                   0x020D
#define Pk_Oinvertedbreve                 0x020E
#define Pk_oinvertedbreve                 0x020F
#define Pk_Rdoublegrave                   0x0210
#define Pk_rdoublegrave                   0x0211
#define Pk_Rinvertedbreve                 0x0212
#define Pk_rinvertedbreve                 0x0213
#define Pk_Udoublegrave                   0x0214
#define Pk_udoublegrave                   0x0215
#define Pk_Uinvertedbreve                 0x0216
#define Pk_uinvertedbreve                 0x0217
#endif /* Pk_LATIN_EXTENDED_B */

#ifdef Pk_COMBINING_DIACRITICAL_MARKS
#define Pk_combining_grave                0x0300	/* Varia */
#define Pk_combining_acute                0x0301	/* Oxia */
#define Pk_combining_circumflex           0x0302
#define Pk_combining_tilde                0x0303
#define Pk_combining_macron               0x0304
#define Pk_combining_overline             0x0305
#define Pk_combining_breve                0x0306	/* Vrachy */
#define Pk_combining_abovedot             0x0307
#define Pk_combining_diaeresis            0x0308	/* Dialytika */
#define Pk_combining_abovehook            0x0309
#define Pk_combining_abovering            0x030A
#define Pk_combining_doubleacute          0x030B
#define Pk_combining_caron                0x030C	/* Hacek */
#define Pk_combining_aboveverticalline    0x030D	/* Tonos */
#define Pk_combining_abovedoubleverticalline 0x030E
#define Pk_combining_doublegrave          0x030F
#define Pk_combining_candrabindu          0x0310
#define Pk_combining_invertedbreve        0x0311
#define Pk_combining_aboveturnedcomma     0x0312
#define Pk_combining_abovecomma           0x0313	/* Psili */
#define Pk_combining_abovereversedcomma   0x0314	/* Dasia */
#define Pk_combining_aboverightcomma      0x0315
#define Pk_combining_belowgrave           0x0316
#define Pk_combining_belowacute           0x0317
#define Pk_combining_belowlefttack        0x0318
#define Pk_combining_belowrighttack       0x0319
#define Pk_combining_aboveleftangle       0x031A
#define Pk_combining_horn                 0x031B
#define Pk_combining_belowlefthalfring    0x031C
#define Pk_combining_belowuptack          0x031D
#define Pk_combining_belowdowntack        0x031E
#define Pk_combining_belowplus            0x031F
#define Pk_combining_belowminus           0x0320
#define Pk_combining_belowpalatalizedhook 0x0321
#define Pk_combining_belowretroflexhook   0x0322
#define Pk_combining_belowdot             0x0323
#define Pk_combining_belowdiaeresis       0x0324
#define Pk_combining_belowring            0x0325
#define Pk_combining_belowcomma           0x0326
#define Pk_combining_cedilla              0x0327
#define Pk_combining_ogonek               0x0328
#define Pk_combining_belowverticalline    0x0329
#define Pk_combining_belowbridge          0x032A
#define Pk_combining_belowdoublearch      0x032B
#define Pk_combining_belowcaron           0x032C
#define Pk_combining_belowcircumflex      0x032D
#define Pk_combining_belowbreve           0x032E
#define Pk_combining_belowinvertedbreve   0x032F
#define Pk_combining_belowtilde           0x0330
#define Pk_combining_belowmacron          0x0331
#define Pk_combining_lowline              0x0332
#define Pk_combining_doublelowline        0x0333
#define Pk_combining_overlaytilde         0x0334
#define Pk_combining_overlayshortstroke   0x0335
#define Pk_combining_overlaylongstroke    0x0336
#define Pk_combining_overlaysolidusshort  0x0337
#define Pk_combining_slashshort           0x0337	/* deprecated */
#define Pk_combining_overlaysoliduslong   0x0338
#define Pk_combining_slashlong            0x0338	/* deprecated */
#define Pk_combining_belowrighthalfring   0x0339
#define Pk_combining_belowinvertedbridge  0x033A
#define Pk_combining_belowsquare          0x033B
#define Pk_combining_belowseagull         0x033C
#define Pk_combining_abovex               0x033D
#define Pk_combining_verticaltilde        0x033E
#define Pk_combining_doubleoverline       0x033F
#define Pk_combining_gravetonemark        0x0340	/* Vietnamese */
#define Pk_combining_acutetonemark        0x0341	/* Vietnamese */
#define Pk_combining_perispomeni          0x0342	/* Greek */
#define Pk_combining_koronis              0x0343	/* Greek */
#define Pk_combining_dialytikatonos       0x0344	/* Greek */
#define Pk_combining_ypogegrammeni        0x0345	/* Greek */
#define Pk_combining_doubletilde          0x0360
#define Pk_combining_doubleinvertedbreve  0x0361
#endif /* Pk_COMBINING_DIACRITICAL_MARKS */

/*
 * Greek
 */

#ifdef Pk_GREEK
#define Pk_Greek_numeralsign              0x0374
#define Pk_Greek_lowernumeralsign         0x0375
#define Pk_Greek_ypogegrammeni            0x037A
#define Pk_Greek_questionmark             0x037E
#define Pk_Greek_tonos                    0x0384
#define Pk_Greek_accent                   0x0384	/* deprecated */
#define Pk_Greek_tonosdialytika           0x0385
#define Pk_Greek_accentdieresis           0x0385	/* deprecated */
#define Pk_Greek_ALPHAtonos               0x0386
#define Pk_Greek_ALPHAaccent              0x0386	/* deprecated */
#define Pk_Greek_ano_teleia               0x0387
#define Pk_Greek_EPSILONtonos             0x0388
#define Pk_Greek_EPSILONaccent            0x0388	/* deprecated */
#define Pk_Greek_ETAtonos                 0x0389
#define Pk_Greek_ETAaccent                0x0389	/* deprecated */
#define Pk_Greek_IOTAtonos                0x038A
#define Pk_Greek_IOTAaccent               0x038A	/* deprecated */
#define Pk_Greek_OMICRONtonos             0x038C
#define Pk_Greek_OMICRONaccent            0x038C	/* deprecated */
#define Pk_Greek_UPSILONtonos             0x038E
#define Pk_Greek_UPSILONaccent            0x038E	/* deprecated */
#define Pk_Greek_OMEGAtonos               0x038F
#define Pk_Greek_OMEGAaccent              0x038F	/* deprecated */
#define Pk_Greek_iotatonosdialytika       0x0390
#define Pk_Greek_iotaaccentdieresis       0x0390	/* deprecated */
#define Pk_Greek_ALPHA                    0x0391
#define Pk_Greek_BETA                     0x0392
#define Pk_Greek_GAMMA                    0x0393
#define Pk_Greek_DELTA                    0x0394
#define Pk_Greek_EPSILON                  0x0395
#define Pk_Greek_ZETA                     0x0396
#define Pk_Greek_ETA                      0x0397
#define Pk_Greek_THETA                    0x0398
#define Pk_Greek_IOTA                     0x0399
#define Pk_Greek_KAPPA                    0x039A
#define Pk_Greek_LAMDA                    0x039B
#define Pk_Greek_LAMBDA                   0x039B	/* deprecated */
#define Pk_Greek_MU                       0x039C
#define Pk_Greek_NU                       0x039D
#define Pk_Greek_XI                       0x039E
#define Pk_Greek_OMICRON                  0x039F
#define Pk_Greek_PI                       0x03A0
#define Pk_Greek_RHO                      0x03A1
#define Pk_Greek_SIGMA                    0x03A3
#define Pk_Greek_TAU                      0x03A4
#define Pk_Greek_UPSILON                  0x03A5
#define Pk_Greek_PHI                      0x03A6
#define Pk_Greek_CHI                      0x03A7
#define Pk_Greek_PSI                      0x03A8
#define Pk_Greek_OMEGA                    0x03A9
#define Pk_Greek_IOTAdiaeresis            0x03AA
#define Pk_Greek_UPSILONdialytika         0x03AB
#define Pk_Greek_UPSILONdieresis          0x03AB	/* deprecated */
#define Pk_Greek_alphatonos               0x03AC
#define Pk_Greek_alphaaccent              0x03AC	/* deprecated */
#define Pk_Greek_epsilontonos             0x03AD
#define Pk_Greek_epsilonaccent            0x03AD	/* deprecated */
#define Pk_Greek_etatonos                 0x03AE
#define Pk_Greek_etaaccent                0x03AE	/* deprecated */
#define Pk_Greek_iotatonos                0x03AF
#define Pk_Greek_iotaaccent               0x03AF	/* deprecated */
#define Pk_Greek_upsilontonosdialytika    0x03B0
#define Pk_Greek_upsilonaccentdieresis    0x03B0	/* deprecated */
#define Pk_Greek_alpha                    0x03B1
#define Pk_Greek_beta                     0x03B2
#define Pk_Greek_gamma                    0x03B3
#define Pk_Greek_delta                    0x03B4
#define Pk_Greek_epsilon                  0x03B5
#define Pk_Greek_zeta                     0x03B6
#define Pk_Greek_eta                      0x03B7
#define Pk_Greek_theta                    0x03B8
#define Pk_Greek_iota                     0x03B9
#define Pk_Greek_kappa                    0x03BA
#define Pk_Greek_lamda                    0x03BB
#define Pk_Greek_lambda                   0x03BB	/* deprecated */
#define Pk_Greek_mu                       0x03BC
#define Pk_Greek_nu                       0x03BD
#define Pk_Greek_xi                       0x03BE
#define Pk_Greek_omicron                  0x03BF
#define Pk_Greek_pi                       0x03C0
#define Pk_Greek_rho                      0x03C1
#define Pk_Greek_finalsigma               0x03C2
#define Pk_Greek_finalsmallsigma          0x03C2	/* deprecated */
#define Pk_Greek_sigma                    0x03C3
#define Pk_Greek_tau                      0x03C4
#define Pk_Greek_upsilon                  0x03C5
#define Pk_Greek_phi                      0x03C6
#define Pk_Greek_chi                      0x03C7
#define Pk_Greek_psi                      0x03C8
#define Pk_Greek_omega                    0x03C9
#define Pk_Greek_iotadialytika            0x03CA
#define Pk_Greek_iotadieresis             0x03CA	/* deprecated */
#define Pk_Greek_upsilondialytika         0x03CB
#define Pk_Greek_upsilondieresis          0x03CB	/* deprecated */
#define Pk_Greek_omicrontonos             0x03CC
#define Pk_Greek_omicronaccent            0x03CC	/* deprecated */
#define Pk_Greek_upsilontonos             0x03CD
#define Pk_Greek_upsilonaccent            0x03CD	/* deprecated */
#define Pk_Greek_omegatonos               0x03CE
#define Pk_Greek_omegaaccent              0x03CE	/* deprecated */
#define Pk_Greek_switch                   0xF07E  /* Alias for mode_switch */
#endif /* Pk_GREEK */

/*
 * Cyrillic
 */
#ifdef Pk_CYRILLIC
#define Pk_Cyrillic_IO                    0x0401
#define Pk_Cyrillic_DJE                   0x0402	/* Serbocroatian */
#define Pk_Serbian_DJE                    0x0402	/* deprecated */
#define Pk_Macedonia_GJE                  0x0403
#define Pk_Ukrainian_IE                   0x0404
#define Pk_Cyrillic_DZE                   0x0405
#define Pk_Byelorussian_Ukrainian_I       0x0406
#define Pk_Ukrainian_I                    0x0406	/* deprecated */
#define Pk_Cyrillic_YI                    0x0407	/* Ukrainian */
#define Pk_Ukrainian_YI                   0x0407	/* deprecated */
#define Pk_Cyrillic_JE                    0x0408
#define Pk_Cyrillic_LJE                   0x0409
#define Pk_Cyrillic_NJE                   0x040A
#define Pk_Cyrillic_TSHE                  0x040B	/* Serbocroatian */
#define Pk_Serbian_TSHE                   0x040B	/* deprecated */
#define Pk_Cyrillic_KJE                   0x040C
#define Pk_Macedonia_KJE                  0x040C	/* deprecated */
#define Pk_Cyrillic_SHORTU                0x040E	/* Byelorussian */
#define Pk_Byelorussian_SHORTU            0x040E	/* deprecated */
#define Pk_Cyrillic_DZHE                  0x040F
#define Pk_Cyrillic_A                     0x0410
#define Pk_Cyrillic_BE                    0x0411
#define Pk_Cyrillic_VE                    0x0412
#define Pk_Cyrillic_GHE                   0x0413
#define Pk_Cyrillic_DE                    0x0414
#define Pk_Cyrillic_IE                    0x0415
#define Pk_Cyrillic_ZHE                   0x0416
#define Pk_Cyrillic_ZE                    0x0417
#define Pk_Cyrillic_I                     0x0418
#define Pk_Cyrillic_SHORTI                0x0419
#define Pk_Cyrillic_KA                    0x041A
#define Pk_Cyrillic_EL                    0x041B
#define Pk_Cyrillic_EM                    0x041C
#define Pk_Cyrillic_EN                    0x041D
#define Pk_Cyrillic_O                     0x041E
#define Pk_Cyrillic_PE                    0x041F
#define Pk_Cyrillic_ER                    0x0420
#define Pk_Cyrillic_ES                    0x0421
#define Pk_Cyrillic_TE                    0x0422
#define Pk_Cyrillic_U                     0x0423
#define Pk_Cyrillic_EF                    0x0424
#define Pk_Cyrillic_HA                    0x0425
#define Pk_Cyrillic_TSE                   0x0426
#define Pk_Cyrillic_CHE                   0x0427
#define Pk_Cyrillic_SHA                   0x0428
#define Pk_Cyrillic_SHCHA                 0x0429
#define Pk_Cyrillic_HARDSIGN              0x042A
#define Pk_Cyrillic_YERU                  0x042B
#define Pk_Cyrillic_SOFTSIGN              0x042C
#define Pk_Cyrillic_E                     0x042D
#define Pk_Cyrillic_YU                    0x042E
#define Pk_Cyrillic_YA                    0x042F
#define Pk_Cyrillic_a                     0x0430
#define Pk_Cyrillic_be                    0x0431
#define Pk_Cyrillic_ve                    0x0432
#define Pk_Cyrillic_ghe                   0x0433
#define Pk_Cyrillic_de                    0x0434
#define Pk_Cyrillic_ie                    0x0435
#define Pk_Cyrillic_zhe                   0x0436
#define Pk_Cyrillic_ze                    0x0437
#define Pk_Cyrillic_i                     0x0438
#define Pk_Cyrillic_shorti                0x0439
#define Pk_Cyrillic_ka                    0x043A
#define Pk_Cyrillic_el                    0x043B
#define Pk_Cyrillic_em                    0x043C
#define Pk_Cyrillic_en                    0x043D
#define Pk_Cyrillic_o                     0x043E
#define Pk_Cyrillic_pe                    0x043F
#define Pk_Cyrillic_er                    0x0440
#define Pk_Cyrillic_es                    0x0441
#define Pk_Cyrillic_te                    0x0442
#define Pk_Cyrillic_u                     0x0443
#define Pk_Cyrillic_ef                    0x0444
#define Pk_Cyrillic_ha                    0x0445
#define Pk_Cyrillic_tse                   0x0446
#define Pk_Cyrillic_che                   0x0447
#define Pk_Cyrillic_sha                   0x0448
#define Pk_Cyrillic_shcha                 0x0449
#define Pk_Cyrillic_hardsign              0x044A
#define Pk_Cyrillic_yeru                  0x044B
#define Pk_Cyrillic_softsign              0x044C
#define Pk_Cyrillic_e                     0x044D
#define Pk_Cyrillic_yu                    0x044E
#define Pk_Cyrillic_ya                    0x044F
#define Pk_Cyrillic_io                    0x0451
#define Pk_Cyrillic_dje                   0x0452	/* Serbocroatian */
#define Pk_Serbian_dje                    0x0452	/* deprecated */
#define Pk_Cyrillic_gje                   0x0453
#define Pk_Macedonia_gje                  0x0453	/* deprecated */
#define Pk_Ukrainian_ie                   0x0454
#define Pk_Cyrillic_dze                   0x0455
#define Pk_Byelorussian_Ukrainian_i       0x0456
#define Pk_Ukrainian_i                    0x0456	/* deprecated */
#define Pk_Cyrillic_yi                    0x0457	/* Ukrainian */
#define Pk_Ukrainian_yi                   0x0457	/* deprecated */
#define Pk_Cyrillic_je                    0x0458
#define Pk_Cyrillic_lje                   0x0459
#define Pk_Cyrillic_nje                   0x045A
#define Pk_Cyrillic_tshe                  0x045B	/* Serbocroatian */
#define Pk_Serbian_tshe                   0x045B	/* deprecated */
#define Pk_Cyrillic_kje                   0x045C
#define Pk_Macedonia_kje                  0x045C	/* deprecated */
#define Pk_Cyrillic_shortu                0x045E	/* Byelorussian */
#define Pk_Byelorussian_shortu            0x045E	/* deprecated */
#define Pk_Cyrillic_dzhe                  0x045F
#define Pk_Cyrillic_OMEGA                 0x0460
#define Pk_Cyrillic_omega                 0x0461
#define Pk_Cyrillic_YAT                   0x0462
#define Pk_Cyrillic_yat                   0x0463
#define Pk_Cyrillic_Eiotified             0x0464
#define Pk_Cyrillic_eiotified             0x0465
#define Pk_Cyrillic_YUS                   0x0466
#define Pk_Cyrillic_yus                   0x0467
#define Pk_Cyrillic_YUSiotifiedlittle     0x0468
#define Pk_Cyrillic_yusiotifiedlittle     0x0469
#define Pk_Cyrillic_YUSbig                0x046A
#define Pk_Cyrillic_yusbig                0x046B
#define Pk_Cyrillic_YUSiotifiedbig        0x046C
#define Pk_Cyrillic_yusiotifiedbig        0x046D
#define Pk_Cyrillic_KSI                   0x046E
#define Pk_Cyrillic_ksi                   0x046F
#define Pk_Cyrillic_PSI                   0x0470
#define Pk_Cyrillic_psi                   0x0471
#define Pk_Cyrillic_FITA                  0x0472
#define Pk_Cyrillic_fita                  0x0473
#define Pk_Cyrillic_IZHITSA               0x0474
#define Pk_Cyrillic_izhitsa               0x0475
#define Pk_Cyrillic_IZHITSAdoublegrave    0x0476
#define Pk_Cyrillic_izhitsadoublegrave    0x0477
#define Pk_Cyrillic_UK                    0x0478
#define Pk_Cyrillic_uk                    0x0479
#define Pk_Cyrillic_OMEGAround            0x047A
#define Pk_Cyrillic_omegaround            0x047B
#define Pk_Cyrillic_OMEGAtitlo            0x047C
#define Pk_Cyrillic_omegatitlo            0x047D
#define Pk_Cyrillic_OT                    0x047E
#define Pk_Cyrillic_ot                    0x047F
/* Thats not all: there are quite many characters in the 0x480...0x4FF range */
#endif /* Pk_CYRILLIC */

/*
 * Hebrew
 */

#ifdef Pk_HEBREW
#define Pk_Hebrew_sheva                   0x05B0
#define Pk_Hebrew_hatafsegol              0x05B1
#define Pk_Hebrew_hatafpatah              0x05B2
#define Pk_Hebrew_hatafqamats             0x05B3
#define Pk_Hebrew_hiriq                   0x05B4
#define Pk_Hebrew_tsere                   0x05B5
#define Pk_Hebrew_segol                   0x05B6
#define Pk_Hebrew_patah                   0x05B7
#define Pk_Hebrew_qamats                  0x05B8
#define Pk_Hebrew_holam                   0x05B9
#define Pk_Hebrew_qubuts                  0x05BB
#define Pk_Hebrew_dageshormapiq           0x05BC
#define Pk_Hebrew_meteg                   0x05BD
#define Pk_Hebrew_maqaf                   0x05BE
#define Pk_Hebrew_rafe                    0x05BF
#define Pk_Hebrew_paseq                   0x05C0
#define Pk_Hebrew_shindot                 0x05C1
#define Pk_Hebrew_sindot                  0x05C2
#define Pk_Hebrew_sofpasuq                0x05C3
#define Pk_Hebrew_aleph                   0x05D0
#define Pk_Hebrew_bet                     0x05D1
#define Pk_Hebrew_beth                    0x05D1	/* deprecated */
#define Pk_Hebrew_gimel                   0x05D2
#define Pk_Hebrew_gimmel                  0x05D2	/* deprecated */
#define Pk_Hebrew_dalet                   0x05D3
#define Pk_Hebrew_daleth                  0x05D3	/* deprecated */
#define Pk_Hebrew_he                      0x05D4
#define Pk_Hebrew_waw                     0x05D5
#define Pk_Hebrew_vav                     0x05D5	/* deprecated */
#define Pk_Hebrew_zayin                   0x05D6
#define Pk_Hebrew_zain                    0x05D6	/* deprecated */
#define Pk_Hebrew_het                     0x05D7
#define Pk_Hebrew_chet                    0x05D7	/* deprecated */
#define Pk_Hebrew_tet                     0x05D8
#define Pk_Hebrew_teth                    0x05D8	/* deprecated */
#define Pk_Hebrew_yod                     0x05D9
#define Pk_Hebrew_finalkaf                0x05DA
#define Pk_Hebrew_finalkaph               0x05DA	/* deprecated */
#define Pk_Hebrew_kaf                     0x05DB
#define Pk_Hebrew_kaph                    0x05DB	/* deprecated */
#define Pk_Hebrew_lamed                   0x05DC
#define Pk_Hebrew_finalmem                0x05DD
#define Pk_Hebrew_mem                     0x05DE
#define Pk_Hebrew_finalnun                0x05DF
#define Pk_Hebrew_nun                     0x05E0
#define Pk_Hebrew_samekh                  0x05E1
#define Pk_Hebrew_samech                  0x05E1	/* deprecated */
#define Pk_Hebrew_ayin                    0x05E2
#define Pk_Hebrew_finalpe                 0x05E3
#define Pk_Hebrew_pe                      0x05E4
#define Pk_Hebrew_finaltsadi              0x05E5
#define Pk_Hebrew_finalzade               0x05E5	/* deprecated */
#define Pk_Hebrew_finalzadi               0x05E5	/* deprecated */
#define Pk_Hebrew_tsadi                   0x05E6
#define Pk_Hebrew_zade                    0x05E6	/* deprecated */
#define Pk_Hebrew_zadi                    0x05E6	/* deprecated */
#define Pk_Hebrew_qof                     0x05E7
#define Pk_Hebrew_qoph                    0x05E7	/* deprecated */
#define Pk_Hebrew_kuf                     0x05E7	/* deprecated */
#define Pk_Hebrew_resh                    0x05E8
#define Pk_Hebrew_shin                    0x05E9
#define Pk_Hebrew_tav                     0x05EA
#define Pk_Hebrew_taw                     0x05EA	/* deprecated */
#define Pk_Hebrew_taf                     0x05EA	/* deprecated */
#define Pk_Yiddish_double_vav             0x05F0
#define Pk_Yiddish_vav_yod                0x05F1
#define Pk_Yiddish_double_yod             0x05F2
#define Pk_Hebrew_geresh                  0x05F3
#define Pk_Hebrew_gershayim               0x05F4
#define Pk_Hebrew_switch                  0xF07E  /* Alias for mode_switch */
#endif /* Pk_HEBREW */

/*
 *  Arabic
 */
#ifdef Pk_ARABIC
#define Pk_Arabic_comma                   0x060C
#define Pk_Arabic_semicolon               0x061B
#define Pk_Arabic_question_mark           0x061F
#define Pk_Arabic_hamza                   0x0621
#define Pk_Arabic_maddaonalef             0x0622
#define Pk_Arabic_hamzaonalef             0x0623
#define Pk_Arabic_hamzaonwaw              0x0624
#define Pk_Arabic_hamzaunderalef          0x0625
#define Pk_Arabic_hamzaonyeh              0x0626
#define Pk_Arabic_alef                    0x0627
#define Pk_Arabic_beh                     0x0628
#define Pk_Arabic_tehmarbuta              0x0629
#define Pk_Arabic_teh                     0x062A
#define Pk_Arabic_theh                    0x062B
#define Pk_Arabic_jeem                    0x062C
#define Pk_Arabic_hah                     0x062D
#define Pk_Arabic_khah                    0x062E
#define Pk_Arabic_dal                     0x062F
#define Pk_Arabic_thal                    0x0630
#define Pk_Arabic_ra                      0x0631
#define Pk_Arabic_zain                    0x0632
#define Pk_Arabic_seen                    0x0633
#define Pk_Arabic_sheen                   0x0634
#define Pk_Arabic_sad                     0x0635
#define Pk_Arabic_dad                     0x0636
#define Pk_Arabic_tah                     0x0637
#define Pk_Arabic_zah                     0x0638
#define Pk_Arabic_ain                     0x0639
#define Pk_Arabic_ghain                   0x063A
#define Pk_Arabic_tatweel                 0x0640
#define Pk_Arabic_feh                     0x0641
#define Pk_Arabic_qaf                     0x0642
#define Pk_Arabic_kaf                     0x0643
#define Pk_Arabic_lam                     0x0644
#define Pk_Arabic_meem                    0x0645
#define Pk_Arabic_noon                    0x0646
#define Pk_Arabic_heh                     0x0647
#define Pk_Arabic_ha                      0x0647	/* deprecated */
#define Pk_Arabic_waw                     0x0648
#define Pk_Arabic_alefmaksura             0x0649
#define Pk_Arabic_yeh                     0x064A
#define Pk_Arabic_fathatan                0x064B
#define Pk_Arabic_dammatan                0x064C
#define Pk_Arabic_kasratan                0x064D
#define Pk_Arabic_fatha                   0x064E
#define Pk_Arabic_damma                   0x064F
#define Pk_Arabic_kasra                   0x0650
#define Pk_Arabic_shadda                  0x0651
#define Pk_Arabic_sukun                   0x0652
#define Pk_Arabic_switch                  0xF07E  /* Alias for mode_switch */
#endif /* Pk_ARABIC */

/*
 * Katakana
 */

#ifdef Pk_KATAKANA
#define Pk_overline				       0x47e
#define Pk_kana_fullstop                               0xff61
#define Pk_kana_openingbracket                         0xff62
#define Pk_kana_closingbracket                         0xff63
#define Pk_kana_comma                                  0xff64
#define Pk_kana_conjunctive                            0xff65
#define Pk_kana_middledot                              0xff65  /* deprecated */
#define Pk_kana_WO                                     0xff66
#define Pk_kana_a                                      0xff67
#define Pk_kana_i                                      0xff68
#define Pk_kana_u                                      0xff69
#define Pk_kana_e                                      0xff6a
#define Pk_kana_o                                      0xff6b
#define Pk_kana_ya                                     0xff6c
#define Pk_kana_yu                                     0xff6d
#define Pk_kana_yo                                     0xff6e
#define Pk_kana_tsu                                    0xff6f
#define Pk_kana_tu                                     0xff6f  /* deprecated */
#define Pk_prolongedsound                              0xff70
#define Pk_kana_A                                      0xff71
#define Pk_kana_I                                      0xff72
#define Pk_kana_U                                      0xff73
#define Pk_kana_E                                      0xff74
#define Pk_kana_O                                      0xff75
#define Pk_kana_KA                                     0xff76
#define Pk_kana_KI                                     0xff77
#define Pk_kana_KU                                     0xff78
#define Pk_kana_KE                                     0xff79
#define Pk_kana_KO                                     0xff7a
#define Pk_kana_SA                                     0xff7b
#define Pk_kana_SHI                                    0xff7c
#define Pk_kana_SU                                     0xff7d
#define Pk_kana_SE                                     0xff7e
#define Pk_kana_SO                                     0xff7f
#define Pk_kana_TA                                     0xff80
#define Pk_kana_CHI                                    0xff81
#define Pk_kana_TI                                     0xff81  /* deprecated */
#define Pk_kana_TSU                                    0xff82
#define Pk_kana_TU                                     0xff82  /* deprecated */
#define Pk_kana_TE                                     0xff83
#define Pk_kana_TO                                     0xff84
#define Pk_kana_NA                                     0xff85
#define Pk_kana_NI                                     0xff86
#define Pk_kana_NU                                     0xff87
#define Pk_kana_NE                                     0xff88
#define Pk_kana_NO                                     0xff89
#define Pk_kana_HA                                     0xff8a
#define Pk_kana_HI                                     0xff8b
#define Pk_kana_FU                                     0xff8c
#define Pk_kana_HU                                     0xff8c  /* deprecated */
#define Pk_kana_HE                                     0xff8d
#define Pk_kana_HO                                     0xff8e
#define Pk_kana_MA                                     0xff8f
#define Pk_kana_MI                                     0xff90
#define Pk_kana_MU                                     0xff91
#define Pk_kana_ME                                     0xff92
#define Pk_kana_MO                                     0xff93
#define Pk_kana_YA                                     0xff94
#define Pk_kana_YU                                     0xff95
#define Pk_kana_YO                                     0xff96
#define Pk_kana_RA                                     0xff97
#define Pk_kana_RI                                     0xff98
#define Pk_kana_RU                                     0xff99
#define Pk_kana_RE                                     0xff9a
#define Pk_kana_RO                                     0xff9b
#define Pk_kana_WA                                     0xff9c
#define Pk_kana_N                                      0xff9d
#define Pk_voicedsound                                 0xff9e
#define Pk_semivoicedsound                             0xff9f
#define Pk_kana_switch          0xF07E  /* Alias for mode_switch */
#endif /* Pk_KATAKANA */

/*
 * Technical
 */

#ifdef Pk_TECHNICAL
#error Sorry, these values are not Unicode
#define Pk_leftradical                                 0x8a1
#define Pk_topleftradical                              0x8a2
#define Pk_horizconnector                              0x8a3
#define Pk_topintegral                                 0x8a4
#define Pk_botintegral                                 0x8a5
#define Pk_vertconnector                               0x8a6
#define Pk_topleftsqbracket                            0x8a7
#define Pk_botleftsqbracket                            0x8a8
#define Pk_toprightsqbracket                           0x8a9
#define Pk_botrightsqbracket                           0x8aa
#define Pk_topleftparens                               0x8ab
#define Pk_botleftparens                               0x8ac
#define Pk_toprightparens                              0x8ad
#define Pk_botrightparens                              0x8ae
#define Pk_leftmiddlecurlybrace                        0x8af
#define Pk_rightmiddlecurlybrace                       0x8b0
#define Pk_topleftsummation                            0x8b1
#define Pk_botleftsummation                            0x8b2
#define Pk_topvertsummationconnector                   0x8b3
#define Pk_botvertsummationconnector                   0x8b4
#define Pk_toprightsummation                           0x8b5
#define Pk_botrightsummation                           0x8b6
#define Pk_rightmiddlesummation                        0x8b7
#define Pk_lessthanequal                               0x8bc
#define Pk_notequal                                    0x8bd
#define Pk_greaterthanequal                            0x8be
#define Pk_integral                                    0x8bf
#define Pk_therefore                                   0x8c0
#define Pk_variation                                   0x8c1
#define Pk_infinity                                    0x8c2
#define Pk_nabla                                       0x8c5
#define Pk_approximate                                 0x8c8
#define Pk_similarequal                                0x8c9
#define Pk_ifonlyif                                    0x8cd
#define Pk_implies                                     0x8ce
#define Pk_identical                                   0x8cf
#define Pk_radical                                     0x8d6
#define Pk_includedin                                  0x8da
#define Pk_includes                                    0x8db
#define Pk_intersection                                0x8dc
#define Pk_union                                       0x8dd
#define Pk_logicaland                                  0x8de
#define Pk_logicalor                                   0x8df
#define Pk_partialderivative                           0x8ef
#define Pk_function                                    0x8f6
#define Pk_leftarrow                                   0x8fb
#define Pk_uparrow                                     0x8fc
#define Pk_rightarrow                                  0x8fd
#define Pk_downarrow                                   0x8fe
#endif /* Pk_TECHNICAL */

/*
 *  Special
 */

#ifdef Pk_SPECIAL
#error Sorry, these values are not Unicode
#define Pk_blank                                       0x9df
#define Pk_soliddiamond                                0x9e0
#define Pk_checkerboard                                0x9e1
#define Pk_ht                                          0x9e2
#define Pk_ff                                          0x9e3
#define Pk_cr                                          0x9e4
#define Pk_lf                                          0x9e5
#define Pk_nl                                          0x9e8
#define Pk_vt                                          0x9e9
#define Pk_lowrightcorner                              0x9ea
#define Pk_uprightcorner                               0x9eb
#define Pk_upleftcorner                                0x9ec
#define Pk_lowleftcorner                               0x9ed
#define Pk_crossinglines                               0x9ee
#define Pk_horizlinescan1                              0x9ef
#define Pk_horizlinescan3                              0x9f0
#define Pk_horizlinescan5                              0x9f1
#define Pk_horizlinescan7                              0x9f2
#define Pk_horizlinescan9                              0x9f3
#define Pk_leftt                                       0x9f4
#define Pk_rightt                                      0x9f5
#define Pk_bott                                        0x9f6
#define Pk_topt                                        0x9f7
#define Pk_vertbar                                     0x9f8
#endif /* Pk_SPECIAL */

/*
 *  Publishing
 */

#ifdef Pk_PUBLISHING
#error Sorry, these values are not Unicode
#define Pk_emspace                                     0xaa1
#define Pk_enspace                                     0xaa2
#define Pk_em3space                                    0xaa3
#define Pk_em4space                                    0xaa4
#define Pk_digitspace                                  0xaa5
#define Pk_punctspace                                  0xaa6
#define Pk_thinspace                                   0xaa7
#define Pk_hairspace                                   0xaa8
#define Pk_emdash                                      0xaa9
#define Pk_endash                                      0xaaa
#define Pk_signifblank                                 0xaac
#define Pk_ellipsis                                    0xaae
#define Pk_doubbaselinedot                             0xaaf
#define Pk_onethird                                    0xab0
#define Pk_twothirds                                   0xab1
#define Pk_onefifth                                    0xab2
#define Pk_twofifths                                   0xab3
#define Pk_threefifths                                 0xab4
#define Pk_fourfifths                                  0xab5
#define Pk_onesixth                                    0xab6
#define Pk_fivesixths                                  0xab7
#define Pk_careof                                      0xab8
#define Pk_figdash                                     0xabb
#define Pk_leftanglebracket                            0xabc
#define Pk_decimalpoint                                0xabd
#define Pk_rightanglebracket                           0xabe
#define Pk_marker                                      0xabf
#define Pk_oneeighth                                   0xac3
#define Pk_threeeighths                                0xac4
#define Pk_fiveeighths                                 0xac5
#define Pk_seveneighths                                0xac6
#define Pk_trademark                                   0xac9
#define Pk_signaturemark                               0xaca
#define Pk_trademarkincircle                           0xacb
#define Pk_leftopentriangle                            0xacc
#define Pk_rightopentriangle                           0xacd
#define Pk_emopencircle                                0xace
#define Pk_emopenrectangle                             0xacf
#define Pk_leftsinglequotemark                         0xad0
#define Pk_rightsinglequotemark                        0xad1
#define Pk_leftdoublequotemark                         0xad2
#define Pk_rightdoublequotemark                        0xad3
#define Pk_prescription                                0xad4
#define Pk_minutes                                     0xad6
#define Pk_seconds                                     0xad7
#define Pk_latincross                                  0xad9
#define Pk_hexagram                                    0xada
#define Pk_filledrectbullet                            0xadb
#define Pk_filledlefttribullet                         0xadc
#define Pk_filledrighttribullet                        0xadd
#define Pk_emfilledcircle                              0xade
#define Pk_emfilledrect                                0xadf
#define Pk_enopencircbullet                            0xae0
#define Pk_enopensquarebullet                          0xae1
#define Pk_openrectbullet                              0xae2
#define Pk_opentribulletup                             0xae3
#define Pk_opentribulletdown                           0xae4
#define Pk_openstar                                    0xae5
#define Pk_enfilledcircbullet                          0xae6
#define Pk_enfilledsqbullet                            0xae7
#define Pk_filledtribulletup                           0xae8
#define Pk_filledtribulletdown                         0xae9
#define Pk_leftpointer                                 0xaea
#define Pk_rightpointer                                0xaeb
#define Pk_club                                        0xaec
#define Pk_diamond                                     0xaed
#define Pk_heart                                       0xaee
#define Pk_maltesecross                                0xaf0
#define Pk_dagger                                      0xaf1
#define Pk_doubledagger                                0xaf2
#define Pk_checkmark                                   0xaf3
#define Pk_ballotcross                                 0xaf4
#define Pk_musicalsharp                                0xaf5
#define Pk_musicalflat                                 0xaf6
#define Pk_malesymbol                                  0xaf7
#define Pk_femalesymbol                                0xaf8
#define Pk_telephone                                   0xaf9
#define Pk_telephonerecorder                           0xafa
#define Pk_phonographcopyright                         0xafb
#define Pk_caret                                       0xafc
#define Pk_singlelowquotemark                          0xafd
#define Pk_doublelowquotemark                          0xafe
#define Pk_cursor                                      0xaff
#endif /* Pk_PUBLISHING */

/*
 *  APL
 */

#ifdef Pk_APL
#error Sorry, these values are not Unicode
#define Pk_leftcaret                                   0xba3
#define Pk_rightcaret                                  0xba6
#define Pk_downcaret                                   0xba8
#define Pk_upcaret                                     0xba9
#define Pk_overbar                                     0xbc0
#define Pk_downtack                                    0xbc2
#define Pk_upshoe                                      0xbc3
#define Pk_downstile                                   0xbc4
#define Pk_underbar                                    0xbc6
#define Pk_jot                                         0xbca
#define Pk_quad                                        0xbcc
#define Pk_uptack                                      0xbce
#define Pk_circle                                      0xbcf
#define Pk_upstile                                     0xbd3
#define Pk_downshoe                                    0xbd6
#define Pk_rightshoe                                   0xbd8
#define Pk_leftshoe                                    0xbda
#define Pk_lefttack                                    0xbdc
#define Pk_righttack                                   0xbfc
#endif /* Pk_APL */



#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PkKeyDef.h $ $Rev: 224590 $" )
#endif
