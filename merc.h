/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Dystopia Mud improvements copyright (C) 2000, 2001 by Brian Graversen  *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/
 /***************************************************************************
 *                                 _/                            _/        *
 *      _/_/_/  _/_/      _/_/_/  _/    _/_/    _/    _/    _/_/_/         *
 *     _/    _/    _/  _/        _/  _/    _/  _/    _/  _/    _/          *
 *    _/    _/    _/  _/        _/  _/    _/  _/    _/  _/    _/           *
 *   _/    _/    _/    _/_/_/  _/    _/_/      _/_/_/    _/_/_/            *
 ***************************************************************************
 * Mindcloud Copyright 2001-2003 by Jeff Boschee (Zarius),                 *
 * Additional credits are in the help file CODECREDITS                     *
 * All Rights Reserved.                                                    *
 ***************************************************************************/

#ifndef _MERC_HEADER_
#define _MERC_HEADER_

#include <stdlib.h>
#include <limits.h>
#include <sys/cdefs.h>
#include <sys/time.h>  
#include <pthread.h>
#include "jobo_quest.h"
#include "jobo_comm.h"
#include "kav_soundex.h" 
#include "monk.h"
#include "giant.h"
#include "fae.h"
#include "hobbit.h"
#include "angel.h"
#include "lich.h"
#include "shapeshifter.h"
#include "undead_knight.h"
#include "tanarri.h"
#include "cyborg.h"
#include "mage.h"
#include "ninja.h"
#include "spiderdroid.h"
#include "drow.h"
#include "demon.h"
#include "samurai.h"
#include "skyblade.h"
#include "drone.h"
#include "ghoul.h"
#include "draconian.h"
#include "thief.h"
#include "shadow.h"
#include "priest.h"
#include "jedi.h"
#include "class.h"
#include "garou.h"
#include "xrakisis.h"
#include "shinobi.h"
#include "elemental.h"
#include "dragon.h"

/*
 * Accommodate old non-Ansi compilers.
 */
#if defined(TRADITIONAL)
#define const
#define args( list )			( )
#define DECLARE_DO_FUN( fun )		void fun( )
#define DECLARE_SPEC_FUN( fun )		bool fun( )
#define DECLARE_SPELL_FUN( fun )	void fun( )
#define DECLARE_QUEST_FUN( fun )        void fun( )
#define DECLARE_SHOP_FUN( fun )         void fun( )
#define DECLARE_OBJ_FUN( fun )		void fun( )
#define DECLARE_ROOM_FUN( fun )		void fun( )
#else
#define args( list )			list
#define DECLARE_DO_FUN( fun )		DO_FUN    fun
#define DECLARE_SPEC_FUN( fun )		SPEC_FUN  fun
#define DECLARE_QUEST_FUN( fun )        QUEST_FUN fun
#define DECLARE_SPELL_FUN( fun )	SPELL_FUN fun
#define DECLARE_SHOP_FUN( fun )         SHOP_FUN  fun
#define DECLARE_OBJ_FUN( fun )		OBJ_FUN	  fun
#define DECLARE_ROOM_FUN( fun )		ROOM_FUN  fun
#endif



/*
 * Short scalar types.
 * Diavolo reports AIX compiler has bugs with short types.
 */
#if	!defined(FALSE)
#define FALSE	 0
#endif

#if	!defined(TRUE)
#define TRUE	 1
#endif

#if	defined(_AIX)
#if	!defined(const)
#define const
#endif
typedef int				sh_int;
typedef int				bool;
#define unix
#else
typedef short int			sh_int;
typedef unsigned char			bool;
#endif

/* mccp: support bits */
   
#include <zlib.h>
#define TELOPT_COMPRESS 85
#define COMPRESS_BUF_SIZE 16384

/*
 * Structure types.
 */
typedef struct  area_affect             AREA_AFFECT;
typedef struct	affect_data		AFFECT_DATA;
typedef struct	affect2_data		AFFECT2_DATA;
typedef struct	area_data		AREA_DATA;
typedef struct	ban_data		BAN_DATA;
typedef struct	char_data		CHAR_DATA;
typedef struct  alias_data              ALIAS_DATA;
typedef struct  quest_data              QUEST_DATA;
typedef struct  top_board		TOP_BOARD;
typedef struct	wiz_data		WIZ_DATA;
typedef struct  history_data            HISTORY_DATA;
typedef struct  l_board			LEADER_BOARD;
typedef struct  religion_table          RELIGION_TABLE;
typedef struct  map_type                MAP_TYPE;
typedef	struct	editor_data		EDITOR_DATA;
typedef struct  channel_storage         CHANNEL_STORAGE;
typedef struct  kingdom_data		KINGDOM_DATA;
typedef struct  war_data		WAR_DATA;
typedef struct  dummy_arg               DUMMY_ARG;
typedef struct	descriptor_data		DESCRIPTOR_DATA;
typedef struct	exit_data		EXIT_DATA;
typedef struct	extra_descr_data	EXTRA_DESCR_DATA;
typedef struct	help_data		HELP_DATA;
typedef struct	kill_data		KILL_DATA;
typedef struct	mob_index_data		MOB_INDEX_DATA;
typedef struct	note_data		NOTE_DATA;
typedef struct	obj_data		OBJ_DATA;
typedef struct	obj_index_data		OBJ_INDEX_DATA;
typedef struct	pc_data			PC_DATA;
typedef struct	reset_data		RESET_DATA;
typedef struct	room_index_data		ROOM_INDEX_DATA;
typedef struct	time_info_data		TIME_INFO_DATA;
typedef struct	weather_data		WEATHER_DATA;
typedef struct  prog_list               PROG_LIST;
typedef struct  prog_code               PROG_CODE;
typedef struct  disabled_data           DISABLED_DATA;
typedef struct	project_data		PROJECT_DATA;
typedef struct  mob_trigger             MOB_TRIGGER;
typedef struct	auction_data		AUCTION_DATA;
typedef struct	sleep_data	        SLEEP_DATA; /* mpsleep*/
typedef enum {sCreate,sFree,sFreeList} structure_dowhat;

typedef struct  buf_type                BUFFER; 

struct buf_type
{
    BUFFER *    next;
    bool        valid;
    sh_int      state;  /* error state of the buffer */
    sh_int      size;   /* size in k */
    char *      string; /* buffer's string */
}; 

extern SLEEP_DATA *first_sleep;
/*
*  Sleeping prog data
*/
struct sleep_data
{
	SLEEP_DATA *next;
	SLEEP_DATA *prev;
	CHAR_DATA *ch;
	CHAR_DATA *mob;
	PROG_CODE *prog;
	int valid;
	int vnum;
	int line;
	int timer;
};

struct auction_data
{
	OBJ_DATA *	item;
	CHAR_DATA *	owner;
	CHAR_DATA *	high_bidder;
	sh_int		status;
	long		current_bid;
    long		minbid;
	long		bones_held;
};
#define AUCTION_LENGTH			  5
extern          AUCTION_DATA            auction_info;
extern          int                      arena;
extern		int			TOTAL_BID;



#define MINIMUM_BID			100

struct disabled_data
{
  DISABLED_DATA         * next;          /* pointer to next node          */
  struct cmd_type const * command;       /* pointer to the command struct */
  char                  * disabled_by;   /* name of disabler              */
  sh_int                  level;         /* level of disabler             */
};

struct	project_data
{
    PROJECT_DATA * next;		/* Next project in list*/
    PROJECT_DATA * prev;		/* Previous project in list*/
    NOTE_DATA *  first_log;		/* First log on project*/
    NOTE_DATA *  last_log;		/* Last log  on project*/
    char *name;
    char *owner;
    char *coder;
    char *status;
    char *date;
    char *description;
    bool taken;				/* Has someone taken project?*/
};

extern DISABLED_DATA *disabled_first;

/*
 * Function types.
 */
typedef	void DO_FUN	args( ( CHAR_DATA *ch, char *argument ) );
typedef bool SPEC_FUN	args( ( CHAR_DATA *ch ) );
typedef void QUEST_FUN args (( CHAR_DATA * questmaster, CHAR_DATA * ch, char *argument ));
typedef void SPELL_FUN	args( ( int sn, int level, CHAR_DATA *ch, void *vo ) );
typedef void SHOP_FUN  args (( CHAR_DATA * shopkeeper, CHAR_DATA * ch, char *argument ));
typedef void OBJ_FUN	args( ( OBJ_DATA *obj, char *argument ) );
typedef void ROOM_FUN	args( ( ROOM_INDEX_DATA *room, char *argument ) );

/*
 * String and memory management parameters.
 */
#define	MAX_KEY_HASH		 1024
#define MAX_STRING_LENGTH	 8192
#define MAX_INPUT_LENGTH	  400

/* 
 * Rotains Gobal Procedures
 */
void clear_stats    args( (CHAR_DATA *ch) );
void room_is_total_darkness args( (ROOM_INDEX_DATA *pRoomIndex) );
void improve_wpn    args( (CHAR_DATA *ch,int dtype, int right_hand) );
void improve_stance args( (CHAR_DATA *ch) );
void skillstance    args( (CHAR_DATA *ch, CHAR_DATA *victim) );
void show_spell     args( (CHAR_DATA *ch, int dtype) );
void fightaction    args( (CHAR_DATA *ch, CHAR_DATA *victim, int actype , \
int dtype, int wpntype) ); 
void crack_head     args( (CHAR_DATA *ch, OBJ_DATA *obj, char *argument) );
void critical_hit   args( (CHAR_DATA *ch, CHAR_DATA *victim, int dt, int dam) );

void take_item      args( (CHAR_DATA *ch, OBJ_DATA *obj) );
void raw_kill       args( (CHAR_DATA *victim) );
void trip           args( (CHAR_DATA *ch, CHAR_DATA *victim) );
void disarm         args( (CHAR_DATA *ch, CHAR_DATA *victim) );
void make_corpse    args( (CHAR_DATA *ch) );
void one_hit        args( (CHAR_DATA *ch, CHAR_DATA *victim, int dt, int handtype) );

void special_hurl   args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
void make_part      args( (CHAR_DATA *ch, char *argument) );
void home_write             args( ( ) );
void behead                 args( (CHAR_DATA *victim) );
void paradox                args( (CHAR_DATA *ch) );

bool fair_fight             args( (CHAR_DATA *ch, CHAR_DATA *victim) );

/*
 * file stuff
 */
void save_topboard     args( (void) );
void load_leaderboard  args( (void) );
void save_leaderboard  args( (void) );
void load_bans	       args( (void) );
void save_bans	       args( (void) );
void load_kingdoms     args( (void) );
void save_kingdoms     args( (void) );

/* 
 * Godwars Game Parameters
 * By Rotain
 */

#define SKILL_ADEPT               100
#define SKILL_THAC0_32             18
#define SKILL_THAC0_00              6
#define VERSION_NUMBER              1
#define DONATION_ROOM_WEAPON     3207
#define DONATION_ROOM_ARMOR      3207
#define DONATION_ROOM_REST       3207
#define MAX_VAMPIRE_POWER           3 
#define MAX_CLAN                   11
#define MAX_DISCIPLINES		   44
#define MAX_ART                    12
#define MAX_SONGS		    1

/*
 * Game parameters.
 * Increase the max'es if you add more of something.
 * Adjust the pulse numbers to suit yourself.
 */
#define MUDNAME                   "The Rogue Legion"
#define MAX_KNUDE                 500
#define MAX_HISTORY                15
#define MAX_IGNORE                 10
#define MAX_ALIAS                  30
#define MAX_KINGDOM                 5
#define MAX_WAR			           30
#define CURRENT_REVISION            1 // change this each time you update revision of pfiles
#define PARADOX_TICK               30
#define MAX_SKILL		  231
#define MAX_SPELL		   81
#define MAX_LEVEL		   12
#define MAX_TOP_PLAYERS	           20
#define MAX_RELIGIONS               5

/* Size of the map and depth of recursion to undertake */
#define MAPX     10
#define MAPY      8
#define MAXDEPTH  2

#define NO_WATCH		   10
#define LEVEL_HERO		   (MAX_LEVEL - 9)
#define LEVEL_IMMORTAL		   (MAX_LEVEL - 5)

#define LEVEL_MORTAL		   (MAX_LEVEL - 10)
#define LEVEL_AVATAR		   (MAX_LEVEL - 9)
#define LEVEL_BUILDER		   (MAX_LEVEL - 5)
#define LEVEL_QUESTMAKER	   (MAX_LEVEL - 4)
#define LEVEL_ENFORCER		   (MAX_LEVEL - 3)
#define LEVEL_JUDGE		   (MAX_LEVEL - 2)
#define LEVEL_HIGHJUDGE		   (MAX_LEVEL - 1)
#define LEVEL_IMPLEMENTOR	   (MAX_LEVEL)

#define PULSE_THIRTY              (30 * PULSE_PER_SECOND)
#define PULSE_PER_SECOND	    4
#define PULSE_VIOLENCE		  ( 3 * PULSE_PER_SECOND)
#define PULSE_SHAPESPEC             7
#define PULSE_DB_DUMP             (1800* PULSE_PER_SECOND ) /* 30 minutes  */
#define PULSE_AUCTION             (10 * PULSE_PER_SECOND)
#define PULSE_EMBRACE             ( 4 * PULSE_PER_SECOND)
#define PULSE_MOBILE		  ( 4 * PULSE_PER_SECOND)
#define PULSE_PLAYERS	 	  ( 4 * PULSE_PER_SECOND)
#define PULSE_TICK		  (30 * PULSE_PER_SECOND)
#define PULSE_AREA		  (60 * PULSE_PER_SECOND)
#define PULSE_WW                  ( 4 * PULSE_PER_SECOND)
#define PULSE_ARENA		  (30 * PULSE_AREA)  /* 120 minutes */
#define PULSE_RAGNAROK            ( 15 * PULSE_AREA)
#define PULSE_HINT 		  ( 3 * PULSE_AREA)
#define PULSE_MINUTE              ( 60 * PULSE_PER_SECOND)

#ifdef I3
#include "i3.h"
#endif

/*
 * Let's just keep it down here - Jobo
 */
#include "board.h"

/*
 * Site ban structure.
 */
struct	ban_data
{
    BAN_DATA *	next;
    char *	name;
    char *      reason;
};

struct struckdrunk
{
    int min_drunk_level;
    int number_of_rep;
    char *replacement[11];
};

struct	wiz_data
{
    WIZ_DATA *	next;
    bool	valid;
    sh_int	level;
    char *	name;
};

/*
 * Time and weather stuff.
 */
#define SUN_DARK		    0
#define SUN_RISE		    1
#define SUN_LIGHT		    2
#define SUN_SET			    3

#define SKY_CLOUDLESS		    0
#define SKY_CLOUDY		    1
#define SKY_RAINING		    2
#define SKY_LIGHTNING		    3

#define MTRIG_SAY         0
#define MTRIG_LOCATE      1
#define MTRIG_SCRY        2
#define MTRIG_HUNTER      4

struct	time_info_data
{
    int		hour;
    int		day;
    int		month;
    int		year;
};

struct	weather_data
{
    int		mmhg;
    int		change;
    int		sky;
    int		sunlight;
};


struct bit_type
{
  char *const         name;
  int                 bit_value;
};

struct war_data
{
	int one;
	int two;
};

struct kingdom_data
{
  char * whoname;    // the name used in do_who().
  char * name;       // the keyword name.
  char * leader;     // who runs the place.
  char * general;    // who's the right hand man.
  int    recall;
  int    kills;      // amount of pkills done by kingdom members.
  int    deaths;     // amount of pkills done agains kingdom members.
  int    qps;        // the size of the kingdoms wealth.
  int    req_hit;    // hps req to join.
  int    req_move;   // move req to join.
  int    req_mana;   // mana req to join.
  int    req_qps;    // qps cost to join (will be donated to the kingdom vault).
};

       
/*
 * Directions.
 * Used in #ROOMS.
 */
typedef enum
{
  DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST, DIR_UP, DIR_DOWN,
  DIR_NORTHEAST, DIR_NORTHWEST, DIR_SOUTHEAST, DIR_SOUTHWEST,
DIR_SOMEWHERE
}
dir_types;

/*
 * Stable prompt ala Erwins howto.
 */
#define VT_SAVECURSOR            "\e7"   /* Save cursor and attrib         */
#define VT_RESTORECURSOR         "\e8"   /* Restore cursor pos and attribs */
#define VT_SETWIN_CLEAR          "\e[r"  /* Clear scrollable window size   */
#define VT_CLEAR_SCREEN          "\e[2J" /* Clear screen                   */
#define VT_CLEAR_LINE            "\e[2K" /* Clear this whole line          */
#define VT_RESET_TERMINAL        "\ec"

#define SUB_NORTH DIR_NORTH
#define SUB_EAST  DIR_EAST
#define SUB_SOUTH DIR_SOUTH
#define SUB_WEST  DIR_WEST
#define SUB_UP    DIR_UP
#define SUB_DOWN  DIR_DOWN
#define SUB_NE    DIR_NORTHEAST
#define SUB_NW    DIR_NORTHWEST
#define SUB_SE    DIR_SOUTHEAST
#define SUB_SW    DIR_SOUTHWEST

/*
 * threaded status - Jobo
 */
#define STATUS_LOOKUP       0   // New Descriptor, in lookup pr. default.   
#define STATUS_DONE         1   // The lookup is done.
#define STATUS_WAIT         2   // Closed while in thread.
#define STATUS_CLOSED       3   // Closed, ready to be recycled.

/*
 * Extra Descr bits - Jobo
 */
#define ED_TYPE_NONE        0
#define ED_TYPE_PULL        1
#define ED_TYPE_PRESS       2
#define ED_TYPE_PUSH        3
#define ED_TYPE_TOUCH       4

#define ED_ACTION_NONE      0
#define ED_ACTION_TELEPORT  1
#define ED_ACTION_OBJECT    2
#define ED_ACTION_SPELL     3
#define ED_ACTION_ELEVATOR  4

/*
 * Mudinfo Bits
 */
#define MUDINFO_UPDATED      0
#define MUDINFO_MCCP_USERS   1
#define MUDINFO_OTHER_USERS  2
#define MUDINFO_PEAK_USERS   3
#define MUDINFO_MBYTE        4
#define MUDINFO_BYTE         5
#define MUDINFO_DATA_PEAK    6
#define MUDINFO_MSP_USERS    7
#define MUDINFO_MBYTE_S      8
#define MUDINFO_BYTE_S       9
#define MUDINFO_MAX         10

/*
 * Taking care of the control center
 */
#define CCENTER_MIN_EXP     0   /* default 4K        */
#define CCENTER_MAX_EXP     1   /* default 3 mill    */
#define CCENTER_EXP_LEVEL   2   /* default 100 %     */
#define CCENTER_QPS_LEVEL   3   /* default 100 %     */
#define CCENTER_MAX         4

/*
 * Connected state for a channel.
 */
#define CON_PLAYING			 0
#define CON_GET_NAME			 1
#define CON_GET_OLD_PASSWORD		 2
#define CON_CONFIRM_NEW_NAME		 3
#define CON_GET_NEW_PASSWORD		 4
#define CON_CONFIRM_NEW_PASSWORD	 5
#define CON_GET_NEW_SEX			 6
#define CON_GET_NEW_CLASS		 7
#define CON_GET_NEW_ANSI                 9 
#define CON_READ_MOTD			 10
#define CON_NOT_PLAYING			 11
#define CON_EDITING			 12
#define CON_COPYOVER_RECOVER             13
#define CON_WIZ                          21
#define CON_CONTLOGIN                    22
#define CON_PFILE                        20


/*
 * Character substates
 */
typedef enum
{
  SUB_NONE, SUB_PAUSE, SUB_PERSONAL_DESC, SUB_OBJ_SHORT, SUB_OBJ_LONG,
  SUB_OBJ_EXTRA, SUB_MOB_LONG, SUB_MOB_DESC, SUB_ROOM_DESC, SUB_ROOM_EXTRA,
  SUB_ROOM_EXIT_DESC, SUB_WRITING_NOTE, SUB_MPROG_EDIT, SUB_HELP_EDIT,
  SUB_WRITING_MAP, SUB_PERSONAL_BIO, SUB_REPEATCMD, SUB_RESTRICTED,
  SUB_DEITYDESC,
  /* timer types ONLY below this point */
  SUB_TIMER_DO_ABORT = 128, SUB_TIMER_CANT_ABORT
} char_substates;

/*
 * Timer macros.
 */

#define TIMER(ch, tmr)		((ch)->tick_timer[(tmr)])
#define SET_TIMER(ch, tmr, tm)	((ch)->tick_timer[(tmr)] = (tm))
#define ADD_TIMER(ch, tmr, tm)  ((ch)->tick_timer[(tmr)] += (tm))
#define SUB_TIMER(ch, tmr, tm)  ((ch)->tick_timer[(tmr)] -= (tm))
#define TIME_UP(ch, tmr)	((ch)->tick_timer[(tmr)] == 0 ? TRUE : FALSE)

#define RTIMER(room, rtmr)	 ((room)->tick_timer[(rtmr)])
#define SET_RTIMER(room, rtmr, rtm) ((room)->tick_timer[(rtmr)] = (rtm))
#define ADD_RTIMER(room, rtmr, rtm)  ((room)->tick_timer[(rtmr)] += (rtm))
#define SUB_RTIMER(room, rtmr, rtm)  ((room)->tick_timer[(rtmr)] -= (rtm))
#define RTIME_UP(room, rtmr)	 ((room)->tick_timer[(rtmr)] == 0 ? TRUE : FALSE)

#define TIMER_LAYONHANDS	0
#define TIMER_CALLGOLEMS	1
#define TIMER_BADMOON 		2
#define TIMER_VAMPCALL 		3
#define TIMER_UNCONCIOUS 	4
#define TIMER_PESTILENCE 	5
#define TIMER_DAEMONIC_TRANSFORM 6
#define TIMER_MESMERISE		7
#define TIMER_MESMERISED	8
#define TIMER_DAMN		9
#define TIMER_DRONE_DISTORT	11
#define TIMER_REGEN		12
#define TIMER_SLOW		13
#define TIMER_HASTE		14
#define TIMER_THIRD_ARM_GROWING	15
#define TIMER_FOURTH_ARM_GROWING 16
#define TIMER_THIRD_ARM_GOING	17
#define TIMER_FOURTH_ARM_GOING  18
#define TIMER_ACCURACY		19
#define TIMER_HDESIRE    20
#define TIMER_CANT_BE_TURNED    21
#define TIMER_CANT_TURN    	22
#define TIMER_TREE_WALK    	23
#define TIMER_CAN_CHANGE_HAWK   24
#define TIMER_CAN_CREATE_SHARD  25
#define TIMER_CAN_GUST	        26
#define TIMER_CAN_ENTER_STASIS  27
#define TIMER_CALLWILD      28
#define TIMER_ENTOMB            29
#define TIMER_CAN_BREATHE_FROST 30
#define TIMER_HELLFIRE_SUMMON   31
#define TIMER_GFURY	   	32
#define TIMER_WYRM_ROAR         33
#define TIMER_CAN_CALL_WAR_HORSE 35
#define TIMER_EXPERIENCE        36
#define TIMER_CAN_SPIT_VENOM    37
#define TIMER_CAN_GAIN_VOODOO   38
#define TIMER_CAN_FEATHER       39
#define TIMER_MIGHT             40
#define TIMER_CAN_POLYMORPH     41
#define TIMER_DEJAVU            42
#define TIMER_VAMPIRE_GROW      43
#define TIMER_SKILL_LEV1        44
#define TIMER_SKILL_LEV2        45
#define TIMER_SUPERNOVA        46
#define TIMER_CANT_BORROWLIFE   47
#define TIMER_SHARDS		48
#define TIMER_DJINN	49
#define TIMER_HUNTER		50
#define TIMER_MADNESS		51
#define TIMER_GENIE	52
#define TIMER_CAN_DO_NEXUS	53
#define TIMER_CAN_USE_HEALER	54
#define TIMER_DISCORD		55
#define TIMER_UNUSED		56
#define TIMER_INFERNO		57
#define TIMER_CHAOSPORT		58
#define TIMER_CANMAJESTY	59
#define TIMER_MAJESTY		60
#define TIMER_DSLEEP		61
#define TIMER_CHALLENGE         62
#define TIMER_PUMMEL		63
#define MAX_TIMER		64


#define RTIMER_STINKING_CLOUD	0
#define RTIMER_LIFE_VORTEX	1
#define RTIMER_DEATH_VORTEX	2
#define RTIMER_GLYPH_PROTECTION	3
#define RTIMER_HIDE_ROOM	4
#define RTIMER_SWARM_BEES	5
#define RTIMER_SWARM_RATS	6
#define RTIMER_SWARM_BATS	7
#define RTIMER_GHOST_LIGHT	8
#define RTIMER_NEXUS_FLAME	9
#define RTIMER_NEXUS_WATER	10
#define RTIMER_NEXUS_AIR	11
#define RTIMER_NEXUS_EARTH	12
#define RTIMER_NEXUS_ENTROPY	13
#define RTIMER_WALL_NORTH	14
#define RTIMER_WALL_EAST	15
#define RTIMER_WALL_SOUTH	16
#define RTIMER_WALL_WEST	17
#define RTIMER_WALL_UP		18
#define RTIMER_WALL_DOWN	19
#define RTIMER_DISCORD		20
#define RTIMER_DARK_ROOM	21
#define RTIMER_SILENCE		22
#define RTIMER_FIRE             23
#define RTIMER_WATER            24
#define RTIMER_WIND             25
#define RTIMER_EARTH            26
#define RTIMER_HOLY             27
#define RTIMER_SAFE             28
#define MAX_RTIMER		29

/*
 * Needed for threads - Jobo
 */
struct dummy_arg {
  DUMMY_ARG        *next;
  DESCRIPTOR_DATA  *d;
  char             *buf;
  sh_int           status;
};

/*
 * Part of the communication storage system, Ye Jobo.
 */
struct channel_storage {
  char *last[MAX_STORAGE+1];
};

/*
 * Descriptor (channel) structure.
 */
struct descriptor_data
{
    DESCRIPTOR_DATA *	next;
    DESCRIPTOR_DATA *	snoop_by;
    CHAR_DATA *		character;
    CHAR_DATA *		original;
    char *		host;
  char                  *   showstr_head;           /* From ENVY code to compile */
  char                  *   showstr_point;          /* From ENVY code to compile */
  char                  *   outbuf;
  char                      inbuf[4 * MAX_INPUT_LENGTH];
  char                      incomm[MAX_INPUT_LENGTH];
  char                      inlast[MAX_INPUT_LENGTH];
  char                 **   pString;                /* OLC */
    sh_int		descriptor;
    sh_int		connected;
    sh_int              lookup_status;
    bool		fcommand;
    int			repeat;
    int			outsize;
    int			outtop; 
    int                       editor;                 /* OLC */
    void *              pEdit;          /* OLC */
  z_stream              *   out_compress;           /* MCCP */
  unsigned char         *   out_compress_buf;       /* MCCP */
};



/*
 * Attribute bonus structures.
 */
struct	str_app_type
{
    sh_int	tohit;
    sh_int	todam;
    sh_int	carry;
    sh_int	wield;
};

struct	int_app_type
{
    sh_int	learn;
};

struct	wis_app_type
{
    sh_int	practice;
};

struct	dex_app_type
{
    sh_int	defensive;
};

struct	con_app_type
{
    sh_int	hitp;
    sh_int	shock;
};

/*
 * TO types for act.
 */
#define TO_ROOM		    0
#define TO_NOTVICT	    1
#define TO_VICT		    2
#define TO_CHAR		    3
#define TO_ALL		    4

/*
 * Help table types.
 */
struct	help_data
{
    HELP_DATA *	next;
    HELP_DATA * prev;
    AREA_DATA * area;
    sh_int	level;
    char *	keyword;
    char *	text;
};

/*
 * Data structure for notes.
 */
struct	note_data
{
    NOTE_DATA *	next;
    char *	sender;
    char *	date;
    char *	to_list;
    char *	subject;
    char *	text;
    time_t	date_stamp;
    time_t	expire;
};

/*
 * An affect for areas
 */
struct area_affect
{
  AREA_AFFECT *next;
  sh_int       religion;
  sh_int       duration;
  sh_int       type;
  sh_int       level;
};


/*
 * An affect.
 */
struct	affect_data
{
    AFFECT_DATA *	next;
    sh_int		type;
    sh_int		duration;
    sh_int		location;
    sh_int		modifier;
    int			bitvector;
};

struct	affect2_data
{
    AFFECT2_DATA *	next;
    sh_int		type;
    sh_int		duration;
    sh_int		location;
    sh_int		modifier;
    int			bitvector;
};

/*
 * A quest
 */
struct quest_data
{
  QUEST_DATA *next;             // next quest player has
  sh_int time;                  // in mud hours
  sh_int type;                  // the type of quest
  int giver;                    // the questmasters vnum
  int vnums[4];                 // vnum of questor
};

/*
 * History data used for storing messages;
 */
struct history_data
{
  HISTORY_DATA *next;
  char *message;
};

/*
 * An alias
 */
struct  alias_data
{
  ALIAS_DATA * next;
  char       * short_n;
  char       * long_n;
};

/* Structure for the map itself */
struct map_type
{
  char tegn;                    /* Character to print at this map coord */
  int vnum;                     /* Room this coord represents */
  int depth;                    /* Recursive depth this coord was found at */
  int info;
  bool can_see;
};

typedef struct heap_data
{
  sh_int             iVertice;
  ROOM_INDEX_DATA  * knude[MAX_KNUDE];
} HEAP;
/*
 * A kill structure (indexed by level).
 */
struct	kill_data
{
    sh_int		number;
    sh_int		killed;
};

/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (Start of section ... start here)                     *
 *                                                                         *
 ***************************************************************************/

#define WIZ_TICKS		   (A)
#define WIZ_LINKS		   (B)
#define WIZ_DEBUG		   (C)
#define WIZ_LOGS           (D)
#define WIZ_CREATE         (E)
#define WIZ_COMMANDS       (F)
#define WIZ_MISC           (G)
#define WIZ_DEATH		   (H)

struct wiznet_type
{
   char *name;
   int  channel;
   int min_level;
   char *col;
   char *id;
   char *on_name;
   char *off_name;
};

/*
 * MOBprog definitions
 */                   
#define TRIG_ACT	(A)
#define TRIG_BRIBE	(B)
#define TRIG_DEATH	(C)
#define TRIG_ENTRY	(D)
#define TRIG_FIGHT	(E)
#define TRIG_GIVE	(F)
#define TRIG_GREET	(G)
#define TRIG_GRALL	(H)
#define TRIG_KILL	(I)
#define TRIG_HPCNT	(J)
#define TRIG_RANDOM	(K)
#define TRIG_SPEECH	(L)
#define TRIG_EXIT	(M)
#define TRIG_EXALL	(N)
#define TRIG_DELAY	(O)
#define TRIG_SURR	(P)
#define TRIG_GET	(Q)
#define TRIG_DROP	(R)
#define TRIG_SIT	(S)
#define TRIG_REGEX	(T)

/*
 * Prog types
 */
#define PRG_MPROG	0
#define PRG_OPROG	1
#define PRG_RPROG	2

struct prog_list
{
    int                 trig_type;
    char *              trig_phrase;
    int              vnum;
    char *              code;
    PROG_LIST *         next;
    bool                valid;
};

struct prog_code
{
    int                vnum;
    char *              code;
    PROG_CODE *         next;
}; 

/*
 * Bits for 'affected_by'.
 * Used in #MOBILES. flags2
 */

#define VAMP_ASHES		(A)
#define VAMP_CLONE		(B)
#define VAMP_OBJMASK		(C)
#define AFF_TOTALBLIND		(D)
#define AFF_SPIRITGUARD		(E)

#define AFF_CLAW                (L)
#define AFF_BITE                (M)
#define AFF_TAIL                (N)
#define AFF_WING                (O)

// flag3
#define AFF3_BLINK_1ST_RD	(A)
#define AFF3_BLINK_2ND_RD	(B)


/*
 * Well known mob virtual numbers.
 * Defined in #MOBILES.
 */
#define MOB_VNUM_VAMPIRE	   3404
#define MOB_VNUM_CANNIBAL	   30069
#define MOB_VNUM_WARLORD           3011 //FIX
/*
 * Immunities, for players.  KaVir.
 */
#define IMM_SLASH	      1	/* Resistance to slash, slice. 		*/
#define IMM_STAB	      2	/* Resistance to stab, pierce. 		*/
#define IMM_SMASH	      4	/* Resistance to blast, pound, crush. 	*/
#define IMM_ANIMAL	      8	/* Resistance to bite, claw. 		*/
#define IMM_MISC	     16	/* Resistance to grep, suck, whip. 	*/
#define IMM_CHARM	     32	/* Immune to charm spell. 		*/
#define IMM_HEAT	     64	/* Immune to fire/heat spells. 		*/
#define IMM_COLD	    128	/* Immune to frost/cold spells.		*/
#define IMM_LIGHTNING	    256	/* Immune to lightning spells.		*/
#define IMM_ACID	    512	/* Immune to acid spells.		*/
#define IMM_SUMMON	   1024	/* Immune to being summoned.		*/
#define IMM_VOODOO	   2048	/* Immune to voodoo magic.		*/
#define IMM_VAMPIRE	   4096	/* Allow yourself to become a vampire.	*/
#define IMM_STAKE	   8192	/* Immune to being staked (vamps only). */
#define IMM_SUNLIGHT	  16384	/* Immune to sunlight (vamps only).	*/
#define IMM_SHIELDED	  32768 /* For Obfuscate. Block scry, etc.	*/
#define IMM_HURL	  65536 /* Cannot be hurled.			*/
#define IMM_BACKSTAB	 131072 /* Cannot be backstabbed.		*/
#define IMM_KICK	 262144 /* Cannot be kicked.			*/
#define IMM_DISARM	 524288 /* Cannot be disarmed.			*/
#define IMM_STEAL	1048576 /* Cannot have stuff stolen.		*/
#define IMM_SLEEP	2097152 /* Immune to sleep spell.		*/
#define IMM_DRAIN       4194304 /* Immune to energy drain.		*/
#define IMM_SHIELD2	8388608 /* Chaotic shield			*/
#define IMM_TRANSPORT  16777216 /* Objects can't be transported to you.	*/
#define IMM_TRAVEL     33554432

/*
 * ACT bits for mobs.
 * Used in #MOBILES.
 */
#define ACT_IS_NPC		    (A)		/* Auto set for mobs	*/
#define ACT_SENTINEL		(B)		/* Stays in one room	*/
#define ACT_SCAVENGER		(C)		/* Picks up objects	*/
#define ACT_AGGRESSIVE		(D)		/* Attacks PC's		*/
#define ACT_STAY_AREA		(E)		/* Won't leave area	*/
#define ACT_WIMPY		    (F)		/* Flees when hurt	*/
#define ACT_PET			    (G)		/* Auto set for pets	*/
#define ACT_TRAIN		    (H)		/* Can train PC's	*/
#define ACT_PRACTICE		(I)		/* Can practice PC's	*/
#define ACT_MOUNT		    (J)		/* Can be mounted	*/
#define ACT_NOPARTS		    (K)		/* Dead = no body parts	*/
#define ACT_NOEXP		    (L)		/* No exp for killing   */
#define ACT_PROTOTYPE		(M)
#define ACT_NOAUTOKILL		(N)
#define ACT_NOEXP2			(O)
#define ACT_NOTRAVEL		(P)
#define ACT_NOSUMMON		(Q)
#define ACT_NODAMAGE        (R)
#define ACT_DEALER		    (S)

/*
 * Thingers for Demon Warps
 */

#define WARP_CBODY				1
#define WARP_SBODY				2
#define WARP_STRONGARMS				4
#define WARP_STRONGLEGS				8
#define WARP_VENOMTONG				16
#define WARP_SPIKETAIL				32
#define WARP_BADBREATH				64
#define WARP_QUICKNESS				128
#define WARP_STAMINA				256
#define WARP_HUNT				512
#define WARP_DEVOUR				1024
#define WARP_TERROR				2048
#define WARP_REGENERATE				4096
#define WARP_STEED				8192
#define WARP_WEAPON				16384
#define WARP_INFIRMITY				32768
#define WARP_GBODY				65536
#define WARP_SCARED				131072
#define WARP_MAGMA				262144
#define WARP_WEAK				524288
#define WARP_SLOW				1048576
#define WARP_VULNER				2097152
#define WARP_SHARDS				4194304
#define WARP_WINGS				8388608
#define WARP_CLUMSY				16777216
#define WARP_STUPID				33554432
#define WARP_SPOON				67108864
#define WARP_FORK				134217728
#define WARP_KNIFE				268435456
#define WARP_SALADBOWL				536870912



/* Bits for the Discie thing Numbers.. really.. not bits */

#define DISC_VAMP_CELE			2
#define DISC_VAMP_FORT			3
#define DISC_VAMP_OBTE			4
#define DISC_VAMP_PRES			5
#define DISC_VAMP_QUIE			6
#define DISC_VAMP_THAU			7
#define DISC_VAMP_AUSP			8
#define DISC_VAMP_DOMI			9
#define DISC_VAMP_OBFU			10
#define DISC_VAMP_POTE			11
#define DISC_VAMP_PROT			12
#define DISC_VAMP_SERP			13
#define DISC_VAMP_VICI			14
#define DISC_VAMP_DAIM			15
#define DISC_VAMP_ANIM			16

#define DISC_FAE_NATURE                  1
#define DISC_FAE_ARCANE                 17

#define DISC_WERE_BEAR			18
#define DISC_WERE_LYNX			19
#define DISC_WERE_BOAR			20
#define DISC_WERE_OWL			21
#define DISC_WERE_SPID			22
#define DISC_WERE_WOLF			23
#define DISC_WERE_HAWK			24
#define DISC_WERE_MANT			25
#define DISC_WERE_RAPT			26
#define DISC_WERE_LUNA			27
#define DISC_WERE_PAIN			28
#define DISC_WERE_C