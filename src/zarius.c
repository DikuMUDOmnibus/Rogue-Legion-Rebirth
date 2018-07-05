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

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "merc.h"
#include "interp.h"


char * CHAR2               args( ( long iNum ) );
bool is_valid_room         args( ( int vnum ) );

char * CHAR2 ( long iNum )
{
	static char csdf [ 256 ];
	sprintf( csdf, "%ld", iNum );
	return csdf;
}

void do_scatter( CHAR_DATA *ch, char *argument )
{
    char arg [ MIL ];
    OBJ_DATA *obj;
    CHAR_DATA *victim;
    bool found;

    argument = one_argument( argument, arg );
   
    if( arg[0] == '\0' )
    {
	send_to_char("Syntax: scatter <item>\n\r", ch );
	send_to_char("   Will loop until you have no more in inventory.\n\r", ch );
	return;
    }
  
    found = FALSE;

    for( obj = get_obj_carry(ch,arg,ch); obj; obj = get_obj_carry(ch,arg,ch) )
    {
	if( !obj )
	{
		send_to_char("There are no more objects in your inventory.\n\r",ch);
		return;
	}
	for ( victim = char_list; victim; victim = victim->next )
        {
		if( number_range(1,1000) == 1 )
		{
			found = TRUE;
			obj_from_char(obj);
			obj_to_char( obj, victim);
		}
	}
    }
    if( found )
	send_to_char( "Done\n\r",ch);
    return;
}

void do_loop( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char arg3[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    int startvnum, endvnum, i;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    argument = one_argument( argument, arg3 );

    if ( arg1[0] == '\0' )
    {
       send_to_char( "#CSyntax: loop <command> <start##> <end##> <params>\n\r", ch );
       send_to_char( "  Where <command> is a valid command to execute,\n\r", ch );
       send_to_char( "  <start##> and <end##> are numbers/vnums,\n\r", ch );
       send_to_char( "  and <params> is a parameter list for <command>.\n\r", ch );
       send_to_char( "#GEXAMPLE: LOOP MSHOW 22000 22100#n\n\r", ch );
       return;
    }

    if ( arg2[0] == '\0' )
    {
       send_to_char( "You must specify a start number/vnum.\n\r", ch );
       return;
    }

    if ( arg3[0] == '\0' )
    {
       send_to_char( "You must specify an end number/vnum.\n\r", ch );
       return;
    }

    startvnum = (is_number(arg2) ? atoi(arg2) : 1);
    endvnum   = (is_number(arg3) ? atoi(arg3) : 1);

    if ( endvnum < 0 )
      endvnum = 1;

    if ( startvnum < 0 )
      startvnum = 1;

    if ( startvnum > endvnum )
    {
       i = endvnum;
       endvnum = startvnum;
       startvnum = i;
    }

    sprintf( buf, "Beginning loop for %s command, vnums %d to %d (%s).\n\r",
         arg1, startvnum, endvnum, argument );

    send_to_char( buf, ch );

    for ( i = startvnum ; i <= endvnum ; i++ )
    {
       sprintf( buf, "%s %d %s", arg1, i,
         (!str_cmp(arg1,"mstat") || !str_cmp(arg1,"ostat")) ?
          "\b" : argument );
       interpret( ch, buf );
    }

    send_to_char( "Done.\n\r", ch );

    return;
}

void do_allpeace( CHAR_DATA *ch, char *argument )
{
    DESCRIPTOR_DATA *d;

    for ( d = descriptor_list; d != NULL; d = d->next )
    {
	if ( d->connected == CON_PLAYING
	&&   d->character != ch
	&&   d->character->in_room != NULL
	&&   ch->level >= d->character->level
	&&   can_see( ch, d->character ) )
	{
	    char buf[MAX_STRING_LENGTH];
	    sprintf( buf, "%s peace", d->character->name );
	    do_at( ch, buf );
	}
    }
}

void do_gemote( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    DESCRIPTOR_DATA *d;
 
    if ( argument[0] == '\0' )
    {
        return;
    }
 
 
    for ( d = descriptor_list; d != NULL; d = d->next )
    {
        if ( d->connected == CON_PLAYING &&
                !IS_SET(d->character->deaf, CHANNEL_INFO) )
        {
            send_to_char( "#B[#0Gemote#B] ", d->character );
            sprintf(buf, "#0%s #w%s#n", ch->name, argument);
            send_to_char( buf, d->character);
            send_to_char( "#n\n\r",   d->character );
        }
    }
 
    return;
}

void do_freevnums(CHAR_DATA *ch, char *argument)
{int iA, free = 0, start = 0, count = 0, needed = atoi(argument);

 for (iA = 0; iA < 30000; iA++)
 {
    if (!get_room_index(iA) && !get_obj_index(iA) && !get_mob_index(iA))
    { if (!free) start = iA;
      free++;
    }
    else if (free)
    {
	sprintf(log_buf, "VNUMS %7d-%7d    ", start, start+free);
      if (free >= needed)
      {
	stc(log_buf, ch);
	count++;
      }
	if (count % 3 == 2)
	{
	    count = 0;
	    stc("\n\r", ch);
	}
	start = 0;
	free = 0;
    }
 }

 stc("\n\r", ch);

 return;
}

void do_unrestore(CHAR_DATA *ch, char *argument)
{
 CHAR_DATA *vict = get_char_world(ch,argument);

 if (!str_cmp(argument, "all"))
 {
  DESCRIPTOR_DATA *d;
 for (d = descriptor_list; d; d = d->next)
 {
    if (!d->character || d->connected > CON_PLAYING || IS_NPC(d->character))
	continue;
    do_unrestore(ch,d->character->pcdata->switchname);
 }
 return;
 }
 if (!*argument || vict == NULL)
 {
    stc("Unrestore who??\n\r", ch);
    return;
 }

 vict->hit = 1;
 vict->mana = 1;
 vict->move = 1;

 sprintf(log_buf, "#R%s #DHas been #sUN#s-#sRESTORED#W!! #sK#sI#sL#sL#s!#n",
    IS_NPC(vict) ? vict->short_descr : vict->pcdata->switchname);
 do_info(ch, log_buf);
 return;
}

void do_xpup(CHAR_DATA *ch, char *argument)
{
 CHAR_DATA *vict = get_char_world(ch,argument);

 if (!str_cmp(argument, "all"))
 {
  DESCRIPTOR_DATA *d;
 for (d = descriptor_list; d; d = d->next)
 {
    if (!d->character || d->connected > CON_PLAYING || IS_NPC(d->character))
	continue;
    do_xpup(ch,d->character->pcdata->switchname);
 }
 return;
 }
 if (!*argument || vict == NULL)
 {
    stc("XPup who??\n\r", ch);
    return;
 }

     SET_TIMER(vict, TIMER_EXPERIENCE, 15);

    send_to_char( "You feel at ease with your experience and learn quicker.\n\r", vict );
    act( "$n starts learning from their mistakes quicker.", vict, NULL, NULL, TO_ROOM );
 return;
}



void do_daynight(CHAR_DATA *ch, char *argument)
{
 if (weather_info.sunlight == SUN_LIGHT)
 {
    stc("It is now night.\n\r", ch);
    weather_info.sunlight = SUN_DARK;
 }
 else
 {
    stc("It is now day.\n\r", ch);
    weather_info.sunlight = SUN_LIGHT;
 }
return;
}

void do_clearflags(CHAR_DATA *ch, char *argument)
{
 char arg1[MIL];
 CHAR_DATA *vict;

 argument = one_argument(argument, arg1);

 if((vict = get_char_world(ch, arg1)) == NULL)
 {
    stc("They're not here!\n\r", ch);
    return;
 }
 vict->act2 = 0;
 vict->act  = 17952;
 
 stc("Their ACT flags have been cleared",ch);
 return;
}

void do_unpreg(CHAR_DATA *ch, char *argument)
{
//(imm only)
 char arg1[MIL];
 CHAR_DATA *vict;

 argument = one_argument(argument, arg1);

 if((vict = get_char_world(ch, arg1)) == NULL)
 {
    stc("They're not here!\n\r", ch);
    return;
 }
 
  free_string(vict->pcdata->conception);
  REMOVE_BIT(vict->extra, EXTRA_PREGNANT);
  REMOVE_BIT(vict->extra, EXTRA_LABOUR);  
  free_string(vict->pcdata->cparents);
  save_char_obj(vict);

 stc("You are not pregnant anymore\n\r", vict);
 stc("Done\n\r", ch);

 return;
}

void do_beep(CHAR_DATA *ch, char *argument)
{
//(imm only)
 char arg1[MIL];
 CHAR_DATA *vict;

 argument = one_argument(argument, arg1);

 if((vict = get_char_world(ch, arg1)) == NULL)
 {
    stc("They're not here!\n\r", ch);
    return;
 }
 

 sprintf(log_buf, "\a%s\a", argument);
 stc(log_buf, vict);

 return;
}

void do_startragbid(CHAR_DATA *ch, char *argument)
{
 char buf[MSL];
 
 if(ragnarok || ragnarok_timer == 120 * PULSE_AREA)
 {
 	stc("Ragnarok is already going or bidding is begun",ch);
 	return;
 }
 
 ragnarok_timer = 120 * PULSE_AREA;
 sprintf(buf, "Bidding on Ragnarok has begun, place your bids now.");
 do_info(ch, buf);
 return;
}

void do_endragnarok(CHAR_DATA *ch, char *argument)
{
 
 if(!ragnarok)
 {
 	stc("There is no ragnarok happening",ch);
 	return;
 }
 
	ragnarok_stop();
    ragnarok_timer = 0;
 return;
}

void do_checkpk(CHAR_DATA *ch, char *argument)
{
    DESCRIPTOR_DATA *d;
    CHAR_DATA *check1;
    CHAR_DATA *check2;
    char buf[MAX_STRING_LENGTH];

for (d = descriptor_list;d != NULL; d = d->next)
{
 if ((check1 = d->character) == NULL) continue;
if (d->connected > CON_PLAYING) continue;

 if ((check2 = d->character->fighting) == NULL) continue;

 if (IS_NPC(check2)) continue;

	sprintf(buf, "%s(%0.2f) is fighting %s(%0.2f)\n\r", check1->name,
atof(CHAR2((check1->hit / check1->max_hit )))
,check2->name,atof(CHAR2((check2->hit/check2->max_hit))));
	send_to_char(buf, ch);
}
for (d = descriptor_list; d; d = d->next)
{if ((check1 = d->character) == NULL) continue;
if (d->connected > CON_PLAYING) continue;

 if (check1->hit <500)
    {
	sprintf(buf, "%s's hp is at %d/%d(%0.2f)\n\r", check1->name,
check1->hit, check1->max_hit,
atof(CHAR2((check1->hit/check1->max_hit))));
	send_to_char(buf, ch);
    }
}
send_to_char("Done.\n\r", ch);
return;
}

char *centerjob (char *fill, const char *txt, int maxlen )
{
 int Tot;
 int tofill;
 int iA;
 const char *txt2 = txt;
 static char buf[MSL];
 char Lik[MSL];

 strcpy(buf,"");
 tofill = maxlen;
 tofill -= strlen(txt);
 tofill += (strlen(txt) - strlen(bash_color(txt)));

 tofill /= 2;

 for (Tot = 0, iA = 0; iA < tofill && Tot < maxlen; iA++, Tot++)
    strcat(buf, fill);

 for ( ; *txt; txt++ )
 {
    sprintf(Lik, "%s%c", buf, *txt);
    strcpy(buf, Lik);
 }

 Tot += strlen(bash_color(txt2));

 for (iA = Tot; iA < maxlen; iA++)
    strcat(buf, fill);

 return buf;
}

char * bash_color( const char *txt )
{
    const char *point;
    char *point2;
 static   char buf[MSL*4];

buf[0] = '\0';
point2 = buf;

for (point = txt; *point; point++)
{
    if (*point == '#' && *(point+1) != '\0')
    {
	point++; continue;
    }
    *point2 = *point;
    *++point2 = '\0';
}
*point2 = '\0';
return buf;
}

void randomize_object(int vnum)
{
 OBJ_DATA *obj;
 ROOM_INDEX_DATA	*rm = NULL;
 EXIT_DATA *pexit = NULL;
 int count = 0;
 int a, to_room;
 bool PLACE = 0;

// for (a = 500; a <= 90000; a++)
// {
//    if (get_room_index(a) != NULL) count++;
// }

// for (a = 500; a <= 90000; a++)
// {
//    if ((rm = get_room_index(a)) != NULL && number_range(1, count * 2) == 1)
//	break;
//    rm = NULL;
// }

//if (rm) 
//{
//obj = create_object(get_obj_index(vnum),0);
//if (!obj) return;
//obj_to_room(obj, rm);
//}
//else randomize_object(vnum);
while (!rm)          
    { 
        to_room = number_range(500, 90000); 
     
        if (is_valid_room(to_room)) 
            rm = get_room_index(number_range(500, 90000)); 
    }     
 
 
    for (a = 0; a < 6; a++) 
    { 
        if ((pexit = rm->exit[a]) != NULL && pexit->to_room != NULL) 
            count++; 
    } 
         
    if (rm && count > 0) 
        PLACE = TRUE; 
     
    if (PLACE){ 
        obj = create_object(get_obj_index(vnum), 0); 
 
        if (!obj)   return; 
         
        obj_to_room(obj, rm);   
    } 
    else    randomize_object(vnum);
return;
}

bool is_valid_room(int vnum) 
{   
    //  Arena 
    if (vnum >= 151 && vnum <= 170)     return FALSE; 
  
    /* 
     *  Kingdoms 
     */ 
    //  Kingdom 1 
    if (vnum >= 40300 && vnum <= 40399) return FALSE; 
    //  Kingdom 2 
    if (vnum >= 40400 && vnum <= 40499) return FALSE; 
    //  Kingdom 3 
    if (vnum >= 40500 && vnum <= 40599) return FALSE; 
    //  Kingdom 4 
    if (vnum >= 40600 && vnum <= 40699) return FALSE; 
    //  Kingdom 5 
    if (vnum >= 40700 && vnum <= 40799) return FALSE; 
  
    //  Class HQs 
    if (vnum >= 93300 && vnum <= 93600) return FALSE; 
  
    return TRUE; 
}

void do_randomload(CHAR_DATA *ch, char *argument)
{
 if (!get_obj_index(atoi(argument)))
 {
    stc("That object doesn't exist!\n\r", ch);
    return;
 }
 stc(get_obj_index((atoi(argument)))->short_descr, ch);
 if(ch->level > 6)
 {
 stc(" randomly loaded to a room on the mud.\n\r", ch);
}

 randomize_object(atoi(argument));

 return;
}

void do_prename(CHAR_DATA *ch, char *argument)
{
 CHAR_DATA *vict;
 char buf[MSL];
 OBJ_DATA *obj;

 argument = one_argument(argument, buf);

 if ((vict = get_char_world(ch, buf)) == NULL || IS_NPC(vict))
 {
    stc("THey aren't here!\n\r", ch);
    return;
 }
 else strcpy(buf, argument);

 sprintf(log_buf, "%s%s", PLAYER_DIR, capitalize(buf));

 if (!check_parse_name(buf) || fopen(log_buf,"r"))
 {
    stc("Illegal name. Choose another.\n\r", ch);
    return;
 }

 sprintf(log_buf, "%s%s", PLAYER_DIR, capitalize(vict->pcdata->switchname));
 unlink(log_buf);

 for (obj = object_list; obj; obj = obj->next)
 {
    if (!str_cmp(obj->questowner, vict->pcdata->switchname))
    {
	free_string(obj->questowner);
	obj->questowner = str_dup(buf);
    }
    if (!str_cmp(obj->questmaker, vict->pcdata->switchname))
    {
	free_string(obj->questmaker);
	obj->questmaker = str_dup(buf);
    }
 }

 free_string(vict->name);
 vict->name = str_dup(buf);
 free_string(vict->pcdata->switchname);
 vict->pcdata->switchname = str_dup(buf);

 act("#6You feel like $n!#n", vict, 0, 0, TO_CHAR);
 act("You turn the poor bastard into $t!", ch, buf, 0, TO_CHAR);

 return;
}

const  struct wiznet_type wiznet_table[] =
{
    {
        "Logs",       WIZ_LOGS,   9, "#G", "LOGS",
        "[+LOGS     ] You see logged strings.\n\r",
        "[-logs     ] You do not see loged strings.\n\r"
    },

    {
        "Links", WIZ_LINKS, 8, "#B", "LINKS",
        "[+LINKS    ] Shows details of players connecting to the mud.\n\r",
        "[-links    ] Not showing details of players connecting.\n\r"
    },

    {
        "Ticks", WIZ_TICKS, 8, "#D", "TICKS",
        "[+TICKS    ] Informs you of ALL area updates.\n\r",
        "[-ticks    ] You are not informed of area updates.\n\r"
    },

    {
        "Debug", WIZ_DEBUG, 8, "#P", "BUGS",
        "[+DEBUG    ] Notifies you of any errors.\n\r",
        "[-debug    ] You are not told of errors.\n\r"
    },

    {
        "Commands", WIZ_COMMANDS, 10, "#B", "CMDS",
        "[+COMMANDS ] You are notified of use of logged immortal commands.\n\r",
        "[-commands ] You are not told of the use of logged immortal commands.\n\r"
    },

    {
        "Create", WIZ_CREATE, 8, "#w", "CREATE",
        "[+CREATE   ] You are notified of use of logged mortal commands.\n\r",
        "[-create   ] You are not told of the use of logged mortal commands.\n\r"
    },

    {
        "Misc", WIZ_MISC, 8, "#c", "MISC",
        "[+MISC     ] Miscellaneous info is on.\n\r",
        "[-misc     ] Miscellaneous info is off.\n\r"
    },
    
     {
        "Death", WIZ_DEATH, 8, "#R", "DEATH",
        "[+DEATH    ] You now see deaths as they occur.\n\r",
        "[-death    ] You do not see death messages.\n\r"
    },
	
    { NULL, 0, 0, NULL, NULL }
};

void do_wiznet( CHAR_DATA *ch, char *argument )
{

    char arg [MAX_INPUT_LENGTH];
    int a;

    if( IS_NPC( ch ) )
	return;

    smash_tilde( argument );
    argument = one_argument( argument, arg );

    if ( arg[0] == '\0' || arg[0] == '?' )
    {
        char buf [ MAX_STRING_LENGTH ];

        send_to_char( "#BWiznet Channel Details:#n\n\r\n\r", ch );
        for ( a = 0; wiznet_table[a].min_level != 0; a++ )
        {

            if ( wiznet_table[a].min_level > get_trust( ch ) )

                buf[0] = '\0';
            if( IS_SET( PCF(ch,wiznet), wiznet_table[a].channel))
                send_to_char( wiznet_table[a].on_name,ch);
            else
                send_to_char( wiznet_table[a].off_name,ch);
        }

        send_to_char( "\n\r#wWiznet <name> toggles the monitor channels.#n\n\r", ch );
        return;
    }
    else
    {
        char buf [ MSL ];
	int  bit = -1;
	bool fSet;

	if( arg[0] == '+' ) fSet = TRUE;
	else if( arg[0] == '-' ) fSet = FALSE;
	else
	{
	    send_to_char( "Wiznet: config -option or +option?\n\r", ch );
	    return;
	}

        if( !str_cmp( arg+1, "ALL" ) )
            bit = WIZ_LOGS | WIZ_LINKS | WIZ_COMMANDS | WIZ_TICKS
                | WIZ_MISC | WIZ_CREATE | WIZ_DEBUG | WIZ_DEATH;
        else
            for ( a = 0; wiznet_table[a].min_level != 0; a++ )
            {
                if ( !str_prefix( arg+1, wiznet_table[a].name ) )
                {
                    bit = wiznet_table[a].channel;
                        break;
                }
            }

        if( bit < 1 )
        {
            do_wiznet( ch, "" );
            return;
        }

        if( fSet )
	{
	    SET_BIT( PCF(ch,wiznet), bit );
            sprintf( buf, "#Y%s is now ON.\n\r", arg+1 );
	    buf[0] = UPPER( buf[0] );
	    send_to_char( buf, ch );
	}
	else
	{
	    REMOVE_BIT( PCF(ch,wiznet), bit );
            sprintf( buf, "#Y%s is now OFF.\n\r", arg+1 );
	    buf[0] = UPPER( buf[0] );
	    send_to_char( buf, ch );
        }
    }

    return;
}



void wiznet( CHAR_DATA *ch, int chan, int level, const char *string )
{

   char buf[MAX_STRING_LENGTH];
   DESCRIPTOR_DATA *d;
   int a;
   bool found;
   
   found = FALSE;
   for ( a = 0; wiznet_table[a].min_level != 0; a++ )
       if( wiznet_table[a].channel == chan )
       {
           found = TRUE;
           break;
       }

   if( !found )
   {
       bug( "Wiznet: Bad channel %d", chan );
       return;
   }
   
       

   sprintf( buf, "#B[#WWIZNET#B][%s%7s#B]#n %s#n\n\r",
            wiznet_table[a].col,
            wiznet_table[a].id,
	    string );
   
   for ( d = descriptor_list; d != NULL; d = d->next )
   {
      if ( d->connected == CON_PLAYING
           && IS_SET( PCF( CH(d),wiznet ), chan )
           && d->character != ch
           && get_trust( CH(d) ) >= level
           && ( ch ? can_see( CH( d ), ch ) : TRUE ) )
          send_to_char( buf, d->character );
   }
   return;
}

void do_stanceset( CHAR_DATA *ch, char *argument )
{
	char arg1 [MIL];
	char arg2 [MIL];
	CHAR_DATA *victim;
	int sn = 0, amount = 0;
	
	argument = one_argument( argument, arg1 );
	argument = one_argument( argument, arg2 );
	
	if ( arg1[0] == '\0' || arg2[0] == '\0')
    {
	send_to_char( "#wSyntax: #Bstanceset #w<person> <amount>#n\n\r",	ch);
	return;
    }
	
	if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
    
    if ( !is_number( arg2 ) )
    {
	send_to_char( "Value must be numeric.\n\r", ch );
	return;
    }
	
	amount = atoi( arg2 );
	
	if (amount > 200 || amount < 0 )
    {
    	stc("Max is 200 for stances.\n\r", ch);
    	return;
    }
    
    for( sn=0 ; sn < 12 ; sn++ )
         victim->stance[sn]                    = amount;
         
    send_to_char( "Done.\n\r", ch );
}
  
void do_spellset( CHAR_DATA *ch, char *argument )
{
	char arg1 [MIL];
	char arg2 [MIL];
	CHAR_DATA *victim;
	int sn = 0, amount = 0;
	
	argument = one_argument( argument, arg1 );
	argument = one_argument( argument, arg2 );
	
	if ( arg1[0] == '\0' || arg2[0] == '\0')
    {
	send_to_char( "#wSyntax: #Bspellset #w<person> <amount>#n\n\r",	ch);
	return;
    }
    
	
	if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
    
    if ( !is_number( arg2 ) )
    {
	send_to_char( "Value must be numeric.\n\r", ch );
	return;
    }
	
    amount = atoi( arg2 );
    
    if (amount > 600 || amount < 0 )
    {
    	stc("Max is 600 for spells.\n\r", ch);
    	return;
    }
    
    for( sn=0 ; sn < 5 ; sn++ )
         victim->spl[sn]                    = amount;
         
    send_to_char( "Done.\n\r", ch );
}

void do_weapset( CHAR_DATA *ch, char *argument )
{
	char arg1 [MIL];
	char arg2 [MIL];
	CHAR_DATA *victim;
	int sn = 0, amount = 0;
	
	argument = one_argument( argument, arg1 );
	argument = one_argument( argument, arg2 );
	
	if ( arg1[0] == '\0' || arg2[0] == '\0')
    {
	send_to_char( "#wSyntax: #Bweapset #w<person> <amount>#n\n\r",	ch);
	return;
    }
    
	
	if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
    
    if ( !is_number( arg2 ) )
    {
	send_to_char( "Value must be numeric.\n\r", ch );
	return;
    }
	
    amount = atoi( arg2 );
    
    if (amount > 2000 || amount < 0 )
    {
    	stc("Max is 2000 for weapons.\n\r", ch);
    	return;
    }
    
    for( sn=0 ; sn <= 12 ; sn++ )
         victim->wpn[sn] = amount;
         
    send_to_char( "Done.\n\r", ch );
}

void do_dismember(CHAR_DATA *ch, char *argument)
{
  char arg[MSL];
  CHAR_DATA *victim;
  argument=one_argument(argument,arg);

  if(arg[0]== '\0')                                                             
  {
    stc("Dismember whom?\n\r",ch);
    return;
  }
  if((victim = get_char_room(ch,NULL,arg))==NULL)
  {
    stc("They are not here.\n\r",ch);
    return;
  }
  if(victim->trust > ch->trust)
  {
    stc("I don't THINK so!\n\r",ch);
    return;
  }

                                                                                
            SET_BIT(victim->loc_hp[2],LOST_ARM);                                
            SET_BIT(victim->loc_hp[6],BLEEDING_ARM_L);                          
            SET_BIT(victim->loc_hp[0],LOST_EYE_L);                              
            SET_BIT(victim->loc_hp[0],LOST_EYE_R);                              
            SET_BIT(victim->loc_hp[0],LOST_EYE_L);                              
            SET_BIT(victim->loc_hp[0],LOST_EAR_L);                              
            SET_BIT(victim->loc_hp[0],LOST_EAR_R);                              
            SET_BIT(victim->loc_hp[0],LOST_EAR_L);                              
            SET_BIT(victim->loc_hp[0],LOST_NOSE);                               
            SET_BIT(victim->loc_hp[0],BROKEN_NOSE);                             
            SET_BIT(victim->loc_hp[0],BROKEN_JAW);                              
            SET_BIT(victim->loc_hp[2],LOST_ARM);                                
            SET_BIT(victim->loc_hp[6],BLEEDING_ARM_L);                          
            SET_BIT(victim->loc_hp[3],LOST_ARM);                                
            SET_BIT(victim->loc_hp[6],BLEEDING_ARM_R);
            SET_BIT(victim->loc_hp[2],BROKEN_ARM);                              
            SET_BIT(victim->loc_hp[3],BROKEN_ARM);                              
            SET_BIT(victim->loc_hp[2],LOST_HAND);                               
            SET_BIT(victim->loc_hp[6],BLEEDING_HAND_L);                         
            SET_BIT(victim->loc_hp[3],LOST_HAND);                               
            SET_BIT(victim->loc_hp[6],BLEEDING_HAND_R);                         
            SET_BIT(victim->loc_hp[2],LOST_THUMB);                              
            SET_BIT(victim->loc_hp[2],LOST_FINGER_I);                           
            SET_BIT(victim->loc_hp[2],LOST_FINGER_M);                           
            SET_BIT(victim->loc_hp[2],LOST_FINGER_R);                           
            SET_BIT(victim->loc_hp[2],LOST_FINGER_L);                           
            SET_BIT(victim->loc_hp[2],BROKEN_THUMB);                            
            SET_BIT(victim->loc_hp[2],BROKEN_FINGER_I);                         
            SET_BIT(victim->loc_hp[2],BROKEN_FINGER_M);                         
            SET_BIT(victim->loc_hp[2],BROKEN_FINGER_R);                         
            SET_BIT(victim->loc_hp[2],BROKEN_FINGER_L);                         
            SET_BIT(victim->loc_hp[3],LOST_THUMB);                              
            SET_BIT(victim->loc_hp[3],LOST_FINGER_I);
            SET_BIT(victim->loc_hp[3],LOST_FINGER_M);                           
            SET_BIT(victim->loc_hp[3],LOST_FINGER_R);                           
            SET_BIT(victim->loc_hp[3],LOST_FINGER_L);                           
            SET_BIT(victim->loc_hp[3],BROKEN_THUMB);                            
            SET_BIT(victim->loc_hp[3],BROKEN_FINGER_I);                         
            SET_BIT(victim->loc_hp[3],BROKEN_FINGER_M);                         
            SET_BIT(victim->loc_hp[3],BROKEN_FINGER_R);                         
            SET_BIT(victim->loc_hp[3],BROKEN_FINGER_L);                         
            SET_BIT(victim->loc_hp[4],LOST_LEG);                                
            SET_BIT(victim->loc_hp[6],BLEEDING_LEG_L);                          
            SET_BIT(victim->loc_hp[5],LOST_LEG);                                
            SET_BIT(victim->loc_hp[6],BLEEDING_LEG_R);                          
            SET_BIT(victim->loc_hp[4],BROKEN_LEG);                              
            SET_BIT(victim->loc_hp[5],BROKEN_LEG);                              
            SET_BIT(victim->loc_hp[4],LOST_FOOT);                               
            SET_BIT(victim->loc_hp[6],BLEEDING_FOOT_L);                         
            SET_BIT(victim->loc_hp[5],LOST_FOOT);                               
            SET_BIT(victim->loc_hp[6],BLEEDING_FOOT_R);
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_16);                          
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_8);                           
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_4);                           
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_2);                           
            SET_BIT(victim->loc_hp[1],BROKEN_RIBS_1);                           
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_16);                    
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_8);                     
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_4);                     
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_2);                     
            SET_BIT(victim->loc_hp[LOC_HEAD],LOST_TOOTH_1);                     
        SET_BIT(victim->loc_hp[LOC_LEG_L],BROKEN_LEG);                          
        SET_BIT(victim->loc_hp[LOC_LEG_R],BROKEN_LEG);                          
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_SPINE);                         
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);                          
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);                           
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_NECK);                          
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);                          
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_NECK);                          
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);                          
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);                           
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_NECK);                          
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_NOSE);                          
        SET_BIT(victim->loc_hp[LOC_HEAD],BROKEN_JAW);                           
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_NECK);                          
make_part(victim,"arm");                                                        
make_part(victim,"arm");                                                        
make_part(victim,"leg");                                                        
make_part(victim,"leg");                                                        
make_part(victim,"blood");                                                      
make_part(victim,"blood");                                                      
                                                                                
        act("You dismembered $N!",ch,NULL,victim,TO_CHAR);
        send_to_char("You have been #RDISMEMBERED#n\n\r", victim );                     
        victim->in_room->blood += 200;

}

void do_spinebreak(CHAR_DATA *ch, char *argument)
{
  char arg[MSL];
  CHAR_DATA *victim;
  argument=one_argument(argument,arg);

  if(arg[0]== '\0')                                                             
  {
    stc("Break Whos spine?\n\r",ch);
    return;
  }
  if((victim = get_char_room(ch,NULL,arg))==NULL)
  {
    stc("They are not here.\n\r",ch);
    return;
  }
  if(victim->trust > ch->trust)
  {
    stc("I don't THINK so!\n\r",ch);
    return;
  }
              
        SET_BIT(victim->loc_hp[LOC_BODY],BROKEN_SPINE);                         
                                               
        act("You break $N's spine!",ch,NULL,victim,TO_CHAR);
        send_to_char("Your spine spontaneously snaps and fills you with #RPAIN#n\n\r", victim );                     
}

void do_dblbuy( CHAR_DATA *ch, char *argument )
{
  char arg[MIL];
  char buf[MSL];
  char arg2[MIL];             
  int amount;

  argument = one_argument( argument, arg );
  argument = one_argument( argument, arg2);

  if (arg[0] == '\0')
  {
    send_to_char("Syntax: dblbuy <exp|train|cp> <bones>.\n\r",ch);
    send_to_char("Or      dblbuy <exp|train|cp> finish.\n\r",ch);
    send_to_char("These will be on for 30 minutes once turned on.\n\r",ch);
    return;
  }      
  if (!str_cmp(arg, "exp"))
  {
  	if (global_exp)
  	{
  		send_to_char("Double Exp is already on Freak!\n\r", ch);
  		return;
  	}
    
    if(!str_cmp(arg2, "finish"))
    {
      amount = exp_cost;	
    }
    else if (!is_number(arg2))
    {
      send_to_char("A number please, how many bones are you adding??\n\r",ch);
      return;
    }
    else
    {
    	amount = atoi(arg2);
    } 
  	if (amount > exp_cost)
  	{
         amount = exp_cost;
  	}
    if (ch->bones < amount)
  	{
    send_to_char("You don't have the bones.\n\r",ch);
    return;
  	}
    ch->bones -= amount;
    exp_cost -= amount;
  if (exp_cost <= 0)
  {
    exp_cost = 25000;
    pulse_exp = 30;
    do_toggle(ch, "exp on");
  }
  else
  {
  sprintf(buf, "#B%s #0adds #Y%d #0Bones to #RDouble Exp, #Y%d #0left to go!#n\n\r", ch->pcdata->switchname, amount, exp_cost);
  do_info(ch, buf);
  }
  return;
  }
  if (!str_cmp(arg, "cp"))
  {
  	if (global_cp)
  	{
  		send_to_char("Double Class Points is already on Freak!\n\r", ch);
  		return;
  	}
    
    if(!str_cmp(arg2, "finish"))
    {
      amount = cp_cost;	
    }
    else if (!is_number(arg2))
    {
      send_to_char("A number please, how many bones are you adding??\n\r",ch);
      return;
    }
    else
    {
    	amount = atoi(arg2);
    } 
  	if (amount > cp_cost)
  	{
    amount = cp_cost;
  	}
    if (ch->bones < amount)
  	{
    send_to_char("You don't have the bones.\n\r",ch);
    return;
  	}
    ch->bones -= amount;
    cp_cost -= amount;
  if (cp_cost <= 0)
  {
    cp_cost = 25000;
    pulse_cp = 30;
    do_toggle(ch, "cp on");
  }
  else
  {
  sprintf(buf, "#B%s #0adds #Y%d #0Bones to #PDouble Class Points, #Y%d #0left to go!#n\n\r", ch->pcdata->switchname, amount, cp_cost);
  do_info(ch, buf);
  }
  return;
  }
  if (!str_cmp(arg, "train"))
  {
  	if (global_dt)
  	{
  		send_to_char("Super Training Points is already on Freak!\n\r", ch);
  		return;
  	}
    
    if(!str_cmp(arg2, "finish"))
    {
      amount = dt_cost;	
    }
    else if (!is_number(arg2))
    {
      send_to_char("A number please, how many bones are you adding??\n\r",ch);
      return;
    }
    else
    {
    	amount = atoi(arg2);
    } 
  	if (amount > dt_cost)
  	{
    amount = dt_cost;
  	}
    if (ch->bones < amount)
  	{
    send_to_char("You don't have the bones.\n\r",ch);
    return;
  	}
    ch->bones -= amount;
    dt_cost -= amount;
  if (dt_cost <= 0)
  {
    dt_cost = 50000;
    pulse_dt = 30;
    do_toggle(ch, "dt on");
  }
  else
  {
  sprintf(buf, "#B%s #0adds #Y%d #0Bones to #WSuper Training, #Y%d #0left to go!#n\n\r", ch->pcdata->switchname, amount, dt_cost);
  do_info(ch, buf);
  }
  return;
  }
  else do_dblbuy(ch,"");
  return;
}

void update_exp()
{
  if (pulse_exp > 0)
  {
    if (--pulse_exp == 0)
    {
      global_exp = FALSE;
      pulse_exp = -1;
      do_info(NULL,"#RDouble Exp #0is now #YOFF#n");
    }
  }
}

void update_dt()
{
  if (pulse_dt > 0)
  {
    if (--pulse_dt == 0)
    {
      global_dt = FALSE;
      pulse_dt = -1;
      do_info(NULL,"#WSuper Training #0now #ROFF#n");
    }
  }
}

void update_cp()
{
  if (pulse_cp > 0)
  {
    if (--pulse_cp == 0)
    {
      global_cp = FALSE;
      pulse_cp = -1;
      do_info(NULL,"#wDouble Class Points now #ROFF#n");
    }
  }
}


void do_newwho(CHAR_DATA *ch, char *argument)
{
    char buf[MAX_STRING_LENGTH];
  char faith[MAX_STRING_LENGTH];
  char buf3[MAX_STRING_LENGTH];
  char buf4[MAX_STRING_LENGTH];
  char buf5[MAX_STRING_LENGTH];
  char buf6[MAX_STRING_LENGTH];
  char buf7[MAX_STRING_LENGTH];
    char buf8[MAX_STRING_LENGTH];
  char buf9[MAX_STRING_LENGTH];
  char buf10[MAX_STRING_LENGTH];
  char buf11[MAX_STRING_LENGTH];
  char buf12[MAX_STRING_LENGTH];
  char buf13[MAX_STRING_LENGTH];
  char buf14[MAX_STRING_LENGTH];
  char buf15[MAX_STRING_LENGTH];
  char buf16[MAX_STRING_LENGTH];
    char buf17[MAX_STRING_LENGTH];
    char buf18[MAX_STRING_LENGTH];
    char buf19[MAX_STRING_LENGTH];
    char buf20[MAX_STRING_LENGTH];
    char kav[MAX_STRING_LENGTH];
    char king[MAX_STRING_LENGTH];
    DESCRIPTOR_DATA *d;
    CHAR_DATA *wch;
    int iLevelLower;
    int iLevelUpper;
    int nPlayerAll = 0;
    int nPlayerVis = 0;
    int nImmVis = 0;
    char pkratio[MAX_STRING_LENGTH];
    bool fClassRestrict;
    bool fImmortalOnly;
    bool immortal = FALSE,avatar = FALSE,mortal = FALSE, mains = FALSE;
    bool imm = FALSE,ava = FALSE, mor = FALSE;
  bool a1 = FALSE;
  bool a2 = FALSE;
  bool a3 = FALSE;
  bool a4 = FALSE;
  bool a5 = FALSE;
  bool a6 = FALSE;
  bool a7 = FALSE;
  bool a8 = FALSE;
  bool a9 = FALSE;
  bool a10 = FALSE;
  bool a11 = FALSE;
  bool a12 = FALSE;
  bool a13 = FALSE;
  bool a14 = FALSE;
  bool a15 = FALSE;
  bool a16 = FALSE;

  if (IS_NPC(ch)) return;

    /*
     * Set default arguments.
     */
    iLevelLower    = 0;
    iLevelUpper    = MAX_LEVEL;
    fClassRestrict = FALSE;
    fImmortalOnly  = FALSE;

    /*
     * Parse arguments.
     */
    for ( ;; )
    {
	char arg[MAX_STRING_LENGTH];

	argument = one_argument( argument, arg );
	if ( arg[0] == '\0' )
	    break;

	if ( is_number( arg ) )
	{
	    send_to_char("Enter 'Avatar' for level 3's, or 'God' for level 4's and 5's.\n\r",ch);
	    return;
	}
	else
	{
	    /*
	     * Look for classes to turn on.
	     */
	    arg[3]    = '\0';
	    if (   !str_cmp( arg, "imm" ) || !str_cmp( arg, "immortal" )
		|| !str_cmp( arg, "ava" ) || !str_cmp( arg, "avatar"   ) )
	    {
		fClassRestrict = TRUE;
	    }
	    else if ( !str_cmp( arg, "god" ) || !str_cmp( arg, "imp" ) )
	    {
		fImmortalOnly = TRUE;
	    }
	    else
	    {
		send_to_char("Enter 'Avatar' for level 3's, or 'God' for level 4's and 5's.\n\r",ch);
		return;
	    }
	}
    }

    /*
     * Now show matching chars.
     */
    pkratio[0] = '\0';
    buf[0] = '\0';
  buf3[0] = '\0';
  buf4[0] = '\0';
  buf5[0] = '\0';
  buf6[0] = '\0';
  buf7[0] = '\0';
  buf8[0] = '\0';
  buf9[0] = '\0';
  buf10[0] = '\0';
  buf11[0] = '\0';
  buf12[0] = '\0';   
  buf13[0] = '\0';
  buf14[0] = '\0';
  buf15[0] = '\0';
  buf16[0] = '\0';
  buf17[0] = '\0';
    buf18[0] = '\0';
    buf19[0] = '\0';
    buf20[0] = '\0';

  for (d = descriptor_list; d != NULL; d = d->next)
  {
	char const *class;

    /*
	 * Check for match against restrictions.
	 * Don't use trust as that exposes trusted mortals.
     */

	if ( (d->connected != CON_PLAYING && d->connected != CON_EDITING) 
	   || (!can_see( ch, d->character )  )  )
	    continue;
        
     wch   = ( d->original != NULL ) ? d->original : d->character;
	if ( wch->level < iLevelLower
	||   wch->level > iLevelUpper
	|| ( fImmortalOnly  && wch->level <  LEVEL_IMMORTAL )
	|| ( fClassRestrict && wch->level != LEVEL_HERO     ) )
	    continue;
	
    
     if (wch->level < 7) nPlayerAll++;
       /*
        * Visibility :-)
        */
    if (!can_see(ch, wch)) continue;
    
    //if (wch->level > 6 && IS_SET(wch->act, PLR_WIZINVIS)) continue;

    if (wch->level < 7) nPlayerVis++;
    else nImmVis++;

        /* Calculate pkratio */
        if (wch->pkill > 0)
      {
          if (100*wch->pkill/(wch->pkill + wch->pdeath) < 100)
            sprintf(pkratio,"#R(#G0.%-2d#R)#n", (100*wch->pkill/(wch->pkill + wch->pdeath)));
    else
            sprintf(pkratio,"#R(#G1.00#R)#n");
    }
        else sprintf(pkratio,"#R(#G0.00#R)#n");

    /*
	 * Figure out what to print for class.
     */
	class = " ";

        if ((IS_HEAD(wch,LOST_HEAD) || IS_EXTRA(wch,EXTRA_OSWITCH)) && wch->pcdata->chobj != NULL)
    {
	    if (wch->pcdata->chobj->pIndexData->vnum == 12)
	    	class = "[#RA Head#n    ]";
	    else if (wch->pcdata->chobj->pIndexData->vnum == 30005)
	    	class = "[#PA Brain#n   ]";
    else
	    	class = "[#GAn Object#n ]";
	} else
	switch ( wch->level )
      {
	default: break;
	case MAX_LEVEL -  0:
		     if ( IS_EXTRA(wch, EXTRA_AFK) )
			class = "#1      AFK#n       ";
	        else if (wch->prefix != NULL)
			class = wch->prefix;
			 else if (!str_cmp(wch->pcdata->switchname,"Zarius"))
			class = "   #p-#P=#0Coder#P=#p-#n    ";
            else 
            class = "     IMP     "; 
            break;
	case MAX_LEVEL -  1: 
	  if ( IS_EXTRA(wch, EXTRA_AFK) )
			class = "#1      AFK#n      ";
	        else if (wch->prefix != NULL)
			class = wch->prefix;
	  else if (!str_cmp(wch->pcdata->switchname, "______"))
	      class = " #b*#W^#b* #RD#re#0a#rt#Rh #b*#W^#b*#n  ";
	  else if (!str_cmp(wch->pcdata->switchname, "Anubis"))
	      class = "*>]Lobishomen[<*";
	  else if (!str_cmp(wch->pcdata->switchname, "-----"))
	      class = "    #r[#WEt#we#0r#wn#Wal#r]#n   ";
	  else
	  	  class = "  #B[#G*#B] #YGOD  #B[#G*#B]#n  "; 
	  break;
	case MAX_LEVEL -  2: class = "  #B[#G*#B] #YGOD  #B[#G*#B]#n  "; break;
	case MAX_LEVEL -  3: class = "Sherriff        "; break;
	case MAX_LEVEL -  4: class = "Alterboy        "; break;
	case MAX_LEVEL -  5: class = "[#CQ#yuest#CM#yaker#n]"; break;
        case MAX_LEVEL - 6:
        case MAX_LEVEL - 7:
        case MAX_LEVEL - 8:
        case MAX_LEVEL - 9:
                     if (wch->prefix != NULL) class = wch->prefix;
                else if (IS_EXTRA(wch, EXTRA_AFK)) class = " #C*#0***A#CF#0K***#C*#n ";
                else if (IS_SET(wch->pcdata->jflags, JFLAG_BULLY)) class = "  #0B#Rully#n       ";
		else if (wch->race <= 0 ) class = "#B[ #gU#Gseless#b #YS#ycum#B ]#n";
		else if (wch->race <= 3 ) class = "#B[  #RD#reg#Re#rner#Ra#rte#B  ]#n";
		else if (wch->race <= 6 ) class = "#B[    #0L#Wac#wk#0y#B     ]#n";
		else if (wch->race <= 9 ) class = "#B[   #0H#Wench#0m#Wen#B   ]#n";
		else if (wch->race <= 12) class = "#B[#CGr#coun#Cd#WPo#0und#Wer#B]#n";
		else if (wch->race <= 15) class = "#B[    #rB#Rada#rss#B    ]#n";
	        else if (wch->race <= 18) class = "#B[     #CT#chu#Cg#B     ]#n";
		else if (wch->race <= 21) class = "#B[    #yC#Yo#ynvi#Yc#yt#B   ]#n";
		else if (wch->race <= 24) class = "#B[  #gBa#Gc#gkS#Gt#gabbe#Gr#B ]#n";
		else if (wch->race <= 27) class = "#B[    #YO#yut#RL#raw#B    ]#n";
		else if (wch->race <= 30) class = "#B[   #PM#par#Pk#ps#PM#pan#B   ]#n";
		else if (wch->race <= 33) class = "#B[#0C#won#Wt#wr#0#Wac#0t#WK#wi#0l#Wl#wa#B]#n";
		else if (wch->race <= 36) class = "#B[  #BHe#ba#Bd#b Hun#Bter#B ]#n";
		else if (wch->race <= 39) class = "#B[  GS#gpe#Gc#gia#Glis#gt#B  ]#n";
		else if (wch->race <= 42) class = "#B[  #0M#Wa#Ds#Wte#0rM#Wi#0nd#B  ]#n";
		else if (wch->race <= 45) class = "#B[     #0D#Wo#0n#B      ]#n";
		else if (wch->race <= 50) class = "#B[  #pC#Pri#pm#Pe #pL#Por#pd#B  ]#n";
		else if (wch->race <= 55) class = "#B[   #YK#yi#Yn#yg #YP#yi#Yn#B   ]#n";   
          break;
      
	case MAX_LEVEL - 10: class = "#B[  #gMortal#B  ]#n"; break;
	case MAX_LEVEL - 11: class = "#B[  #6Newbie#B  ]#n"; break;
	case MAX_LEVEL - 12: class = "#B[#7Undefined#B ]#n"; break;
	}
    /*
	 * Format it up.
     */
  
  if ( wch->class > 0)
    {
  if (IS_CLASS(wch, CLASS_MAGE) ) { sprintf(kav, " #CMage#n  ");}
  else if (IS_CLASS(wch, CLASS_CYBORG))  { sprintf(kav," #0Cyborg#n ");}
  else if( IS_CLASS(wch, CLASS_PRIEST))  { sprintf(kav," #wPriest#n ");}
  else if( IS_CLASS(wch, CLASS_SHAPESHIFTER)) { sprintf( kav, " #rShape#n " );}
  else if( IS_CLASS(wch, CLASS_JEDI) )   { sprintf(kav," #BJedi#n   ");}
  else if( IS_CLASS(wch, CLASS_ANGEL) )  { sprintf(kav," #WAngel#n  ");}
  else if( IS_CLASS(wch, CLASS_SHADOW) ) { sprintf(kav,"#0Sh#wad#0ow#n ");}
  else if( IS_CLASS(wch, CLASS_SKYBLADE)){ sprintf(kav,"#cSky#WBld#n ");}
  else if( IS_CLASS(wch, CLASS_THIEF) )  { sprintf(kav," #0Thief#n " );}
  else if( IS_CLASS(wch, CLASS_GHOUL) )
      {
      sprintf( kav, " #gGhoul#n " );
}
  else if( IS_CLASS(wch, CLASS_DRACONIAN) )
      {
      sprintf( kav, " #GDraco#n " );
      }
  else if( IS_CLASS(wch, CLASS_UNDEAD_KNIGHT) )
      {
          sprintf( kav, " #BKnight#n " );
      }
      else if ( IS_CLASS(wch, CLASS_WEREWOLF))
      {
          sprintf( kav, " #YWolf#n  " );
      }
      else if ( IS_CLASS(wch, CLASS_MONK))
      {
          sprintf(kav," #PMonk#n  ");
      }
      else if ( IS_CLASS(wch, CLASS_DROW)) 
      {
          sprintf(kav," #pDrow#n  ");
      }
      else if ( IS_CLASS(wch, CLASS_VAMPIRE))
      {
          sprintf( kav, " #rV#0am#rp#n  ");
      }
      else if ( IS_CLASS(wch, CLASS_TANARRI))
      {
          sprintf( kav, "#RTanarri#n " );
      }
      else if (wch->class == CLASS_LICH)
      {
          sprintf( kav, " #0Lich #n " );
      }
      else if (wch->class == CLASS_FAE)
      {
          sprintf( kav, " #yFae#n   " );
      }
      else if (wch->class == CLASS_GIANT)
      {
          sprintf( kav, " #GGiant#n " );
      }
      else if (wch->class == CLASS_HOBBIT)
      {
          sprintf( kav, "#yHo#Ybb#yit#n" );
      }
      else if (wch->class == CLASS_DRONE)
      {
          sprintf( kav, "#w Drone#n  ");
      }
      else if ( IS_CLASS(wch, CLASS_SAMURAI) )
      {
          sprintf( kav, "#YSamurai#n");
      }
      else if ( IS_CLASS(wch, CLASS_NINJA) )
      {
          sprintf( kav, "#p Ninja#n  ");
      }
      else if ( IS_CLASS(wch, CLASS_DEMON) )
      {
          sprintf( kav, "#r Demon#n ");
      }
      else 
              sprintf( kav, "#nNone#n   " );
    }
          
      else
	      sprintf( kav, "#nNone#n   " );

    /* 
     * Religions
     */
    if (IS_SET(wch->newbits, NEW_MASTERY))
    {
      if (!IS_SET(wch->special, SPC_HAS_CHOSEN_RELIGION)) sprintf(faith,"#C-=#pFaithless#C=-#n");
      else sprintf(faith,"%s %s",
        religion_table[wch->pcdata->religion].rankname[wch->pcdata->relrank],religion_table[wch->pcdata->religion].name);
    }
    else sprintf(faith, " ");
        
      sprintf( king, "%s", kingdom_table[wch->pcdata->kingdom].whoname);
      if (!str_cmp(kingdom_table[wch->pcdata->kingdom].general, wch->name))
      {
	if( wch->sex == SEX_FEMALE ) sprintf( king, "Princess of %s", kingdom_table[wch->pcdata->kingdom].whoname);
        else sprintf( king, "General of %s", kingdom_table[wch->pcdata->kingdom].whoname);
      }
      else if ( !strcmp(wch->pcdata->switchname,kingdom_table[wch->pcdata->kingdom].leader) )
      {
	if( wch->sex == SEX_FEMALE ) sprintf( king, "Queen of %s",kingdom_table[wch->pcdata->kingdom].whoname );
	else sprintf( king, "King of %s",kingdom_table[wch->pcdata->kingdom].whoname );
      }
    if (wch->level > 6 )
    {
	sprintf( buf3 + strlen(buf3), "#0[#n%s#0] %s %s%s %s %s\n\r",
	    class,
	    kav,
	    wch->pcdata->switchname,
	    wch->pcdata->title,
	    king, faith);
	  imm = TRUE;
    }

	else if ( wch->level >= 3 && wch->level <= 6 )
    {
          if ( wch->race >= 43 )
          {
            sprintf( buf4 + strlen(buf4), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king, faith);
		a16 = TRUE;
          }
          else if ( wch->race >= 40 && wch->race <= 42 )
      {
            sprintf( buf6 + strlen(buf6), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king, faith);
		a15 = TRUE;
      }
          else if ( wch->race >= 37 && wch->race <= 39 )
      {
            sprintf( buf7 + strlen(buf7), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king, faith);
		a14 = TRUE;
      }
          else if ( wch->race >= 34 && wch->race <= 36 )
      {
            sprintf( buf8 + strlen(buf8), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
		a13 = TRUE;
      }
          else if ( wch->race >= 31 && wch->race <= 33 )
      {
            sprintf( buf9 + strlen(buf9), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king, faith);
		a12 = TRUE;
      }
          else if ( wch->race >= 28 && wch->race <= 30 )
      {
            sprintf( buf10 + strlen(buf10), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
		a11 = TRUE;
      }
          else if ( wch->race >= 25 && wch->race <= 27 )
      {
            sprintf( buf11 + strlen(buf11), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
		a10 = TRUE;
      }
          else if ( wch->race >= 22 && wch->race <= 24 )
      {
            sprintf( buf12 + strlen(buf12), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
		a9 = TRUE;
      }
          else if ( wch->race >= 19 && wch->race <= 21 )
      {
            sprintf( buf13 + strlen(buf13), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
		a8 = TRUE;
      }
          else if ( wch->race >= 16 && wch->race <= 18 )
      {
            sprintf( buf14 + strlen(buf14), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
		a7 = TRUE;
      }
          else if ( wch->race >= 13 && wch->race <= 15 )
      {
            sprintf( buf15 + strlen(buf15), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
		a6 = TRUE;
      }
          else if ( wch->race >= 10 && wch->race <= 12 )
      {
            sprintf( buf16 + strlen(buf16), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
		a5 = TRUE;
      }
          else if ( wch->race >= 7 && wch->race <= 9 )
      {
            sprintf( buf17 + strlen(buf17), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
	    a4 = TRUE;
      }
          else if ( wch->race >= 4 && wch->race <= 6 )
      {
            sprintf( buf18 + strlen(buf18), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
	    a3 = TRUE;
      }
          else if ( wch->race >= 1 && wch->race <= 3 )
      {
            sprintf( buf19 + strlen(buf19), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
	    a2 = TRUE;
      }
          else if ( wch->race == 0 )
      {
            sprintf( buf20 + strlen(buf20), "%-16s %-8s %s%s %s %s\n\r",
              class,
              kav,
              wch->pcdata->switchname,
              wch->pcdata->title,
              king,faith);
            a1 = TRUE;
      }
	  ava = TRUE;
    }

        else if ( wch->level < 3 )
    {
        sprintf( buf5 + strlen(buf5), "%-16s %-8s %s %s%s %s\n\r",
            class,
            kav,
            wch->pcdata->switchname,
            wch->pcdata->title,
            king,faith);
          mor = TRUE;
    }

   if ( !mains )
   {
      sprintf(buf, " %s\n\r", get_dystopia_banner("", 76));
  send_to_char(buf, ch);
    send_to_char("                     #W_____ _       #w_     _           #0_    #R___     #n\n\r", ch);
    send_to_char("                    #W|     |_|___ #w_| |___| |___ #0_ _ _| |  #R|_  |    #n\n\r", ch);
    send_to_char("                    #W| | | | |   #w| . |  _| | . #0| | | . |  #R|  _|    #n\n\r", ch);
    send_to_char("                    #W|_|_|_|_|_|_#w|___|___|_|___#0|___|___|  #R|___|    #n\n\r", ch);
      mains = TRUE;
  }

  }

    if ( imm )
  {
      if ( !immortal )
      { 
      sprintf(buf, "\n\r %s\n\r", get_dystopia_banner("#0Gods of #Cmc clone#n", 80));
    send_to_char(buf, ch);
      immortal = TRUE; 
      }
      stc(buf3,ch);
  }         

    if ( ava )
  {
      if ( immortal ) stc("\n\r",ch);
      if ( !avatar )
      { 
      sprintf(buf, " %s\n\r", get_dystopia_banner("    Avatars     ", 80));
    send_to_char(buf, ch);
      avatar = TRUE; 
      }
      if ( a16 ) stc(buf4, ch);
      if ( a15 ) stc(buf6, ch);
      if ( a14 ) stc(buf7, ch);
      if ( a13 ) stc(buf8, ch);
      if ( a12 ) stc(buf9, ch);
      if ( a11 ) stc(buf10,ch);
      if ( a10 ) stc(buf11,ch);
      if ( a9  ) stc(buf12,ch);
      if ( a8  ) stc(buf13,ch);
      if ( a7  ) stc(buf14,ch);
      if ( a6  ) stc(buf15,ch);
      if ( a5  ) stc(buf16,ch);
      if ( a4  ) stc(buf17,ch);
      if ( a3  ) stc(buf18,ch);
      if ( a2  ) stc(buf19,ch);
      if ( a1  ) stc(buf20,ch);
  }

    if ( mor )
  {
      if ( avatar ) stc("\n\r",ch);
      if ( immortal && !avatar ) stc("\n\r",ch);
      if ( !mortal )
      { 
      sprintf(buf, " %s\n\r", get_dystopia_banner("    Mortals     ", 80));
    send_to_char(buf, ch);
      mortal = TRUE; }
      stc(buf5,ch);
  }
    sprintf(buf, "\n\r %s\n\r", get_dystopia_banner("", 80));
  send_to_char(buf, ch);
  sprintf(buf, "       #C%d#0/#C%d #GVisible players and #C%d #Gvisible immortals connected to %s#n\n\r",
    nPlayerVis, nPlayerAll, nImmVis, MUDNAME);
  send_to_char(buf, ch);
   sprintf(buf, " %s\n\r", get_dystopia_banner("", 80));
  send_to_char(buf, ch);
  return;

}
