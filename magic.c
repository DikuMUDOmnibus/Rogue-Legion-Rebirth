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
#include <time.h>
#include "merc.h"
#include "interp.h"
#include "magic.h"
#include "olc.h"


/*
 * Local functions.
 */
void	say_spell	args( ( CHAR_DATA *ch, int sn ) );
void	improve_spl	args( ( CHAR_DATA *ch, int dtype, int sn ) );




/*
 * Improve ability at a certain spell type.  KaVir.
 */
 

void improve_spl( CHAR_DATA *ch, int dtype, int sn )
{
    char buf[MAX_INPUT_LENGTH];
    char bufskill[MAX_INPUT_LENGTH];
    char buftype[MAX_INPUT_LENGTH];
    int dice1;
    int dice2;
    int cmax = 200;
    int amount = 0;

    dice1 = number_percent();
    dice2 = number_percent();

    if (IS_NPC(ch)) return;

         if (dtype == 0 ) sprintf(buftype,"#Ppurple#n");
    else if (dtype == 1 ) sprintf(buftype,"#Rred#n");
    else if (dtype == 2 ) sprintf(buftype,"#Bblue#n");
    else if (dtype == 3 ) sprintf(buftype,"#Ggreen#n");
    else if (dtype == 4 ) sprintf(buftype,"#Yyellow#n");
    else return;
    
    switch(ch->class)
    {
    	default:
    	cmax = 200;
    	break;
    	case CLASS_LICH:
    	cmax = 300;
    	break;
    	case CLASS_MAGE:
    	cmax = 270;
    	break;
        case CLASS_DROW:
        if((dtype == 0 || dtype == 1) && IS_SET(ch->special, SPC_DROW_CLE))
        cmax = 230;
        else if((dtype == 2 || dtype == 3) && IS_SET(ch->special, SPC_DROW_MAG))
        cmax = 230;
        else
        cmax = 200;
        break;
    }
    	
    cmax += (get_curr_int(ch) / 5);

    if (ch->spl[dtype] >= cmax) 
    {
    	ch->spl[dtype] = cmax;
    	return;
    }
    if ((dice1 > ch->spl[dtype] || dice2 > ch->spl[dtype]) || (dice1 >= 90 || dice2 >= 90))
    {
       amount += 1;
       if(get_curr_int(ch) > 45)
       amount += 1;
       if(get_curr_int(ch) > 100)
       amount += 1;
       if(global_dt)
          amount += 2;
    }
    else 
       return;
    if (!IS_NPC(ch) && !IS_SET(ch->act, PLR_BRIEF6))
    {
        if((amount > 0) && (ch->spl[dtype] < cmax))
        {
           sprintf(buf,"#cYour %s #cmagic improves by #C%d#n.\n\r",buftype,amount);
           send_to_char(buf,ch);
        }
    }
    ch->spl[dtype] += amount;

         if (ch->spl[dtype] == 1  ) sprintf(bufskill,"a newbie of");
    else if (ch->spl[dtype] == 26 ) sprintf(bufskill,"a novice at");
    else if (ch->spl[dtype] == 51 ) sprintf(bufskill,"a scholar at");
    else if (ch->spl[dtype] == 76 ) sprintf(bufskill,"a magus at");
    else if (ch->spl[dtype] == 101) sprintf(bufskill,"an adept at");
    else if (ch->spl[dtype] == 126) sprintf(bufskill,"a mage at");
    else if (ch->spl[dtype] == 151) sprintf(bufskill,"a warlock at");
    else if (ch->spl[dtype] == 176) sprintf(bufskill,"a master wizard at");
    else if (ch->spl[dtype] == 200) sprintf(bufskill,"a grand sorcerer at");
    else if (ch->spl[dtype] == 240) sprintf(bufskill,"the complete master of");
    else if (ch->spl[dtype] == 300) sprintf(bufskill,"possesing #RWicked#n knowledge of");
    else return;
    sprintf(buf,"#GYou are now %s %s magic.\n\r#n",bufskill,buftype);
    send_to_char(buf,ch);
    return;
}

bool is_obj( CHAR_DATA *ch )
{
    OBJ_DATA *obj;

    if ( ( obj = ch->pcdata->chobj ) == NULL )
    {
	send_to_char("Huh?\n\r",ch);
	return FALSE;
    }
    if ( obj->chobj == NULL || obj->chobj != ch )
    {
	send_to_char("Huh?\n\r",ch);
	return FALSE;
    }
    if (!IS_CLASS(ch,CLASS_DEMON))
    {
	send_to_char("Huh?\n\r",ch);
	return FALSE;
    }
    if (!IS_DEMPOWER(ch, DEM_MAGIC))
    {
	send_to_char("You haven't been granted the gift of Magic.\n\r",ch);
	return FALSE;
    }
    return TRUE;
}

/*
 * Lookup a skill by name.
 */
int skill_lookup( const char *name )
{
    int sn;

    for ( sn = 0; sn < MAX_SKILL; sn++ )
    {
	if ( skill_table[sn].name == NULL )
	    break;
	if ( LOWER(name[0]) == LOWER(skill_table[sn].name[0])
	&&   !str_prefix( name, skill_table[sn].name ) )
	    return sn;
    }

    return -1;
}



/*
 * Lookup a skill by slot number.
 * Used for object loading.
 */
int slot_lookup( int slot )
{
    extern bool fBootDb;
    int sn;

    if ( slot <= 0 )
	return -1;

    for ( sn = 0; sn < MAX_SKILL; sn++ )
    {
	if ( slot == skill_table[sn].slot )
	    return sn;
    }

    if ( fBootDb )
    {
	bug( "Slot_lookup: bad slot %d.", slot );
	abort( );
    }

    return -1;
}



/*
 * Utter mystical words for an sn.
 */
void say_spell( CHAR_DATA *ch, int sn )
{
    char buf  [MAX_STRING_LENGTH];
    char buf2 [MAX_STRING_LENGTH];
    char colour [MAX_STRING_LENGTH];
    char *pName;
    int iSyl;
    int length;

    struct syl_type
    {
	char *	old;
	char *	new;
    };

    static const struct syl_type syl_table[] =
    {
	{ " ",		" "		},
	{ "ar",		"abra"		},
	{ "au",		"kada"		},
	{ "bless",	"fido"		},
	{ "blind",	"nose"		},
	{ "bur",	"mosa"		},
	{ "cu",		"judi"		},
	{ "de",		"oculo"		},
	{ "en",		"unso"		},
	{ "light",	"dies"		},
	{ "lo",		"hi"		},
	{ "mor",	"zak"		},
	{ "move",	"sido"		},
	{ "ness",	"lacri"		},
	{ "ning",	"illa"		},
	{ "per",	"duda"		},
	{ "ra",		"gru"		},
	{ "re",		"candus"	},
	{ "son",	"sabru"		},
	{ "tect",	"infra"		},
	{ "tri",	"cula"		},
	{ "ven",	"nofo"		},
	{ "a", "c" }, { "b", "b" }, { "c", "q" }, { "d", "e" },
	{ "e", "z" }, { "f", "m" }, { "g", "o" }, { "h", "p" },
	{ "i", "u" }, { "j", "y" }, { "k", "t" }, { "l", "r" },
	{ "m", "w" }, { "n", "i" }, { "o", "a" }, { "p", "s" },
	{ "q", "d" }, { "r", "f" }, { "s", "g" }, { "t", "h" },
	{ "u", "j" }, { "v", "z" }, { "w", "x" }, { "x", "n" },
	{ "y", "l" }, { "z", "k" },
	{ "", "" }
    };

    buf[0]	= '\0';
    for ( pName = skill_table[sn].name; *pName != '\0'; pName += length )
    {
	for ( iSyl = 0; (length = strlen(syl_table[iSyl].old)) != 0; iSyl++ )
	{
	    if ( !str_prefix( syl_table[iSyl].old, pName ) )
	    {
		strcat( buf, syl_table[iSyl].new );
		break;
	    }
	}

	if ( length == 0 )
	    length = 1;
    }

    sprintf( buf2, "$n utters the words, '%s'.", buf );
    sprintf( buf,  "$n utters the words, '%s'.", skill_table[sn].name );
    if ( skill_table[sn].target == 0 )
    {
    	sprintf(colour,"$n's eyes glow bright purple for a moment.");
    	ADD_COLOUR(ch,colour,MAGENTA);
    	act(colour,ch,NULL,NULL,TO_ROOM);
    	sprintf(colour,"Your eyes glow bright purple for a moment.");
    	ADD_COLOUR(ch,colour,MAGENTA);
    	act(colour,ch,NULL,NULL,TO_CHAR);
    }
    else if ( skill_table[sn].target == 1 )
    {
    	sprintf(colour,"$n's eyes glow bright red for a moment.");
    	ADD_COLOUR(ch,colour,L_RED);
    	act(colour,ch,NULL,NULL,TO_ROOM);
    	sprintf(colour,"Your eyes glow bright red for a moment.");
    	ADD_COLOUR(ch,colour,L_RED);
    	act(colour,ch,NULL,NULL,TO_CHAR);
    }
    else if ( skill_table[sn].target == 2 )
    {
    	sprintf(colour,"$n's eyes glow bright blue for a moment.");
    	ADD_COLOUR(ch,colour,L_BLUE);
    	act(colour,ch,NULL,NULL,TO_ROOM);
    	sprintf(colour,"Your eyes glow bright blue for a moment.");
    	ADD_COLOUR(ch,colour,L_BLUE);
    	act(colour,ch,NULL,NULL,TO_CHAR);
    }
    else if ( skill_table[sn].target == 3 )
    {
    	sprintf(colour,"$n's eyes glow bright green for a moment.");
    	ADD_COLOUR(ch,colour,L_GREEN);
    	act(colour,ch,NULL,NULL,TO_ROOM);
    	sprintf(colour,"Your eyes glow bright green for a moment.");
    	ADD_COLOUR(ch,colour,L_GREEN);
    	act(colour,ch,NULL,NULL,TO_CHAR);
    }
    else if ( skill_table[sn].target == 4 )
    {
    	sprintf(colour,"$n's eyes glow bright yellow for a moment.");
    	ADD_COLOUR(ch,colour,YELLOW);
    	act(colour,ch,NULL,NULL,TO_ROOM);
    	sprintf(colour,"Your eyes glow bright yellow for a moment.");
    	ADD_COLOUR(ch,colour,YELLOW);
    	act(colour,ch,NULL,NULL,TO_CHAR);
    }
    return;
}



/*
 * Compute a saving throw.
 * Negative apply's make saving throw better.
 */
bool saves_spell( int level, CHAR_DATA *victim )
{
    int save;
    int tsave;

    if (!IS_NPC(victim))
    {
	tsave = ( victim->spl[0]+victim->spl[1]+victim->spl[2]+
		  victim->spl[3]+victim->spl[4] ) * 0.05;
    	save = 50 + ( tsave - level - victim->saving_throw ) * 5;
    }
    else
    	save = 50 + ( victim->level - level - victim->saving_throw ) * 5;
    save = URANGE( 15, save, 85 );
    return number_percent( ) < save;
}



/*
 * The kludgy global is for spells who want more stuff from command line.
 */
char *target_name;

void do_cast( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *obj;
    void *vo;
    int mana;
    int sn;
    int chance;

    chance = number_percent(); 
    
    chance = number_percent(); 

    if ( chance > 40 && IS_CLASS(ch, CLASS_DEMON) && IS_SET(ch->warp, WARP_STUPID))
    {
        stc("You are too stupid to cast spells!\n\r", ch );
        return;
    }

    /*
     * Switched NPC's can cast spells, but others can't.
     */
    if ( IS_NPC(ch) && ch->desc == NULL )
	return;

    /* Polymorphed players cannot cast spells */
    if ( !IS_NPC(ch) && IS_AFFECTED(ch, AFF_POLYMORPH) && !IS_CLASS(ch, CLASS_ANGEL) && !IS_CLASS(ch, CLASS_FAE) && !IS_CLASS(ch, CLASS_PRIEST) &&
	!IS_VAMPAFF(ch,VAM_DISGUISED) && !IS_POLYAFF(ch, POLY_SPIDER) && ch->power[DISC_VAMP_OBEA] < 10
        && !IS_CLASS(ch, CLASS_GIANT)
	&& !IS_SET(ch->flag2, VAMP_OBJMASK) && !IS_CLASS(ch,CLASS_DEMON) && !IS_CLASS(ch, CLASS_MAGE) && 
	!IS_CLASS(ch, CLASS_CYBORG) && !(IS_CLASS(ch, CLASS_SHAPESHIFTER) && ch->pcdata->powers[FAERIE_LEVEL]>1))
    {
	if ( !is_obj(ch) )
	{
	    send_to_char( "You cannot cast spells in this form.\n\r", ch );
	    return;
	}
    }

    if (IS_CLASS(ch,CLASS_VAMPIRE) && IS_AFFECTED(ch, AFF_PEACE))
    {
	stc("You are unable to cast spells with Majesty on.\n\r",ch);
	return;
    }

    if (IS_CLASS(ch,CLASS_VAMPIRE) && IS_AFFECTED(ch, AFF_POLYMORPH) && ch->power[DISC_VAMP_OBEA] > 9)
    {
        stc("#wYour movement of pure magic guides you#n.\n\r",ch);
    }

    target_name = one_argument( argument, arg1 );
    one_argument( target_name, arg2 );

    if ( arg1[0] == '\0' )
    {
	send_to_char( "Cast which what where?\n\r", ch );
	return;
    }

    if ( ( sn = skill_lookup( arg1 ) ) < 0
    || ( !IS_NPC(ch) && ch->level < skill_table[sn].skill_level) )
    {
	send_to_char( "You can't do that.\n\r", ch );
	return;
    }
  
    if ( ch->position < skill_table[sn].minimum_position )
    {
	if (!IS_NPC(ch) && !IS_CLASS(ch, CLASS_VAMPIRE) &&
	    IS_VAMPAFF(ch, VAM_CELERITY))
	{
	    if ( ch->move < 25 )
	    {
		send_to_char( "You can't concentrate enough.\n\r", ch );
		return;
	    }
	    ch->move = ch->move - 25;
	}
	else
	{
	    if ( ch->move < 50 )
	    {
		send_to_char( "You can't concentrate enough.\n\r", ch );
		return;
	    }
	    ch->move = ch->move - 50;
	}
    }

        mana = IS_NPC(ch) ? 0 : UMAX(
	skill_table[sn].min_mana,
	100 / ( 2 + (ch->level*12) - skill_table[sn].skill_level) );


    if ( !IS_NPC(ch) && IS_SET(ch->special, SPC_WOLFMAN) )
    {
	if (ch->power[DISC_WERE_OWL] < 4) mana *= 2;
    }

    /*
     * Locate targets.
     */
    victim	= NULL;
    obj		= NULL;
    vo		= NULL;
      
    switch ( skill_table[sn].target )
    {
    default:
	bug( "Do_cast: bad target for sn %d.", sn );
	return;

    case TAR_IGNORE:
        send_purplespell(ch);
	break;

    case TAR_CHAR_OFFENSIVE:
	if ( arg2[0] == '\0' )
	{
	    if ( ( victim = ch->fighting ) == NULL )
	    {
		send_to_char( "Cast the spell on whom?\n\r", ch );
		return;
	    }
	}
	else
	{
	    if ( ( victim = get_char_room( ch, NULL, arg2 ) ) == NULL )
	    {
		send_to_char( "They aren't here.\n\r", ch );
		return;
	    }
	}
    if (IS_AFFECTED(victim, AFF_PEACE))
    {
        stc("You are unable to cast on that person.\n\r",ch);
        return;
    }    

    send_redspell(ch);
    if (victim != ch) send_redspell(victim);

    if (IS_CLASS(victim, CLASS_HOBBIT) && ch!=victim && number_range(1,4) != 3)
    {
      send_to_char("They resist the spell.\n\r",ch);
      WAIT_STATE(ch,6);
      return;
    }
        if (is_safe(ch,victim) && ch!=victim) return;
	if ( ch == victim )
	    send_to_char( "Cast this on yourself? Ok...\n\r", ch );

	if (!IS_NPC(victim) && (!CAN_PK(ch)||!CAN_PK(victim)) && (ch != victim))
	{
	    send_to_char( "You are unable to affect them.\n\r", ch );
	    return;
	}

        if (!IS_NPC(victim) && IS_CLASS( victim, CLASS_DROW ))
        {
            if (ch == victim )
            {
                send_to_char("You lower your magical resistance....\n\r", ch);
            }
            else if (number_percent ( )  <= victim->pcdata->stats[DROW_MAGIC])
            {
               send_to_char("Your spell does not affect them.\n\r", ch);
               return;
            }  
        }

	if ( !IS_NPC(ch) )
	{
	    if ( IS_AFFECTED(ch, AFF_CHARM) && ch->master == victim )
	    {
		send_to_char( "You can't do that on your own follower.\n\r",
		    ch );
		return;
	    }
	}

	vo = (void *) victim;
	break;

    case TAR_CHAR_DEFENSIVE:
	if ( arg2[0] == '\0' )
	{
	    victim = ch;
	}
	else
	{
	    if ( ( victim = get_char_room( ch, NULL, arg2 ) ) == NULL )
	    {
		send_to_char( "They aren't here.\n\r", ch );
		return;
	    }
	}

        if (!IS_NPC(victim) && IS_CLASS(victim, CLASS_DROW ))
        {
            if (ch == victim )
            {
                send_to_char("You lower your magical resistance....\n\r", ch);
            }
            else if (number_percent( ) <=victim->pcdata->stats[DROW_MAGIC])
            {
               send_to_char("Your spell does not affect them.\n\r", ch);
               return;
            }  
        }
        send_bluespell(ch);
        if (victim != ch) send_bluespell(victim);
	vo = (void *) victim;
	break;

    case TAR_CHAR_SELF:
	if ( arg2[0] != '\0' && !is_name( arg2, ch->name ) )
	{
	    send_to_char( "You cannot cast this spell on another.\n\r", ch );
	    return;
	}

        send_greenspell(ch);

	vo = (void *) ch;
	break;

    case TAR_OBJ_INV:
	if ( arg2[0] == '\0' )
	{
	    send_to_char( "What should the spell be cast upon?\n\r", ch );
	    return;
	}

	if ( ( obj = get_obj_carry( ch, arg2,ch ) ) == NULL )
	{
	    send_to_char( "You are not carrying that.\n\r", ch );
	    return;
	}

        send_yellowspell(ch);

	vo = (void *) obj;
	break;
    }
	    
    if ( !IS_NPC(ch) && ch->mana < mana )
    {
	send_to_char( "You don't have enough mana.\n\r", ch );
	return;
    }
    
      
    if ( str_cmp( skill_table[sn].name, "ventriloquate" ) )
    	say_spell( ch, sn );
    
    if (IS_CLASS(ch, CLASS_MAGE) || IS_CLASS(ch, CLASS_LICH))
    {
      WAIT_STATE( ch, skill_table[sn].beats / 2);
    }
    else
    {
      WAIT_STATE( ch, skill_table[sn].beats);
    }

    if ( !IS_NPC(ch) && number_percent( ) > ch->pcdata->learned[sn] )
    {
	send_to_char( "You lost your concentration.\n\r", ch );
	ch->mana -= mana / 2;
	improve_spl(ch,skill_table[sn].target,sn);
    }
    else
    {
	int tempentro = 0;
	if (IS_ITEMAFF(ch, ITEMA_AFFENTROPY))
	tempentro = 20;

	ch->mana -= mana;
	/* Check players ability at spell type for spell power...KaVir */
	if (IS_NPC(ch))
	    (*skill_table[sn].spell_fun) ( sn, ch->level, ch, vo );
	else if ( !IS_CLASS(ch, CLASS_MAGE) && !IS_CLASS(ch, CLASS_LICH))
	{
	    (*skill_table[sn].spell_fun) ( sn, ((ch->spl[skill_table[sn].target]*0.25)+tempentro), ch, vo );
	    improve_spl(ch,skill_table[sn].target,sn);
	}
	else
	{
	  (*skill_table[sn].spell_fun) ( sn, (ch->spl[skill_table[sn].target]*.5+tempentro),ch, vo );
	  improve_spl(ch,skill_table[sn].target,sn);
	 
	}
     }

    if ( skill_table[sn].target == TAR_CHAR_OFFENSIVE
    &&   victim != ch
    &&   victim->master != ch )
    {
	CHAR_DATA *vch;
	CHAR_DATA *vch_next;

	for ( vch = ch->in_room->people; vch; vch = vch_next )
	{
	    vch_next = vch->next_in_room;
	    if ( victim == vch && victim->fighting == NULL )
	    {
		multi_hit( victim, ch, TYPE_UNDEFINED );
		break;
	    }
	}
    }

    return;
}



/*
 * Cast spells at targets using a magical object.
 */
void obj_cast_spell( int sn, int level, CHAR_DATA *ch, CHAR_DATA *victim, OBJ_DATA *obj )
{
    void *vo;

    if ( sn <= 0 )
	return;

	if (IS_NPC(ch)) return;


    if ( sn >= MAX_SKILL || skill_table[sn].spell_fun == 0 )
    {
	bug( "Obj_cast_spell: bad sn %d.", sn );
	return;
    }

    switch ( skill_table[sn].target )
    {
    default:
	bug( "Obj_cast_spell: bad target for sn %d.", sn );
	return;

    case TAR_IGNORE:
	vo = NULL;
	break;

    case TAR_CHAR_OFFENSIVE:
	if ( victim == NULL )
	    victim = ch->fighting;
	if ( victim == NULL )
	{
	    send_to_char( "You can't do that.\n\r", ch );
	    return;
	}
      if (is_safe(ch,victim) && ch!=victim) return;

        if (!IS_NPC(victim) && ch != victim)
        {
          if (IS_CLASS(victim, CLASS_HOBBIT) && number_range(1,4) != 3)
          {
            send_to_char("They resist the spell.\n\r",ch);
            return;
          }
          if (IS_CLASS(victim, CLASS_DROW ))
          {
            if (number_percent ( )  <= victim->pcdata->stats[DROW_MAGIC])  
            {
               send_to_char("Your spell does not affect them.\n\r", ch);
               return;
            }
          }
        }
	vo = (void *) victim;
	break;

    case TAR_CHAR_DEFENSIVE:
	if ( victim == NULL )
	    victim = ch;
	vo = (void *) victim;
	break;

    case TAR_CHAR_SELF:
	vo = (void *) ch;
	break;

    case TAR_OBJ_INV:
	if ( obj == NULL )
	{
	    send_to_char( "You can't do that.\n\r", ch );
	    return;
	}
	vo = (void *) obj;
	break;
    }

    target_name = "";
    (*skill_table[sn].spell_fun) ( sn, level, ch, vo );

    if ( skill_table[sn].target == TAR_CHAR_OFFENSIVE
    &&   victim != ch
    &&   victim->master != ch )
    {
	CHAR_DATA *vch;
	CHAR_DATA *vch_next;

	for ( vch = ch->in_room->people; vch; vch = vch_next )
	{
	    vch_next = vch->next_in_room;
	    if ( victim == vch && victim->fighting == NULL )
	    {
		multi_hit( victim, ch, TYPE_UNDEFINED );
		break;
	    }
	}
    }

    return;
}



/*
 * Spell functions.
 */
void spell_acid_blast( int sn, int level, CHAR_DATA *ch, void *vo )
{
    CHAR_DATA *victim = (CHAR_DATA *) vo;
    int dam;

    if (IS_ITEMAFF(victim, ITEMA_ACIDSHIELD)) return;
    dam = dice( level, 6 );
    if (IS_CLASS(ch, CLASS_LICH)) dam*=1.3;
    if ( saves_spell( level, victim ) ) dam /= 2;
    if (!IS_NPC(victim) && IS_IMMUNE(victim, IMM_ACID) ) dam = 0;
    if (IS_NPC(victim) && dam >= victim->hit) dam = victim->hit-1;
    if (dam==0) return;
    damage( ch, victim, dam, sn );
    return;
}

void spell_darmor( int sn, int level, CHAR_DATA *ch, void *vo )
{
  CHAR_DATA *victim = (CHAR_DATA *) vo;
  AFFECT2_DATA af;

  if (is_affected2( victim, sn )) return;

  af.type      = sn;
  af.duration  = 24;
  af.modifier  = -100;
  af.location  = APPLY_AC;
  af.bitvector = AFF2_DARMOR;
  affect2_to_char( victim, &af );
  act( "$n is shrouded in a suit of divine armor.", victim, NULL, NULL, TO_ROOM );
  send_to_char( "You are shrouded in a suit of divine armor.\n\r", victim );
  return;
}

void spell_armor( int sn, int level, CHAR_DATA *ch, void *vo )
{
    CHAR_DATA *victim = (CHAR_DATA *) vo;
    AFFECT_DATA af;

    if ( is_affected( victim, sn ) )
	return;
    af.type      = sn;
    af.duration  = 24;
    af.modifier  = -20;
    af.location  = APPLY_AC;
    af.bitvector = 0;
    affect_to_char( victim, &af );
    act( "$n is shrouded in a suit of translucent glowing armor.", victim, NULL, NULL, TO_ROOM );
    send_to_char( "You are shrouded in a suit of translucent glowing armor.\n\r", victim );
    if ( ch != victim )
	send_to_char( "Ok.\n\r", ch );
    return;
}



void spell_godbless( int sn, int level, CHAR_DATA *ch, void *vo )
{
    CHAR_DATA *victim = (CHAR_DATA *) vo;
    AFFECT_DATA af;

    if ( is_affected( victim, sn ) ) return;
    af.type      = sn;
    af.duration  = 150;
    af.location  = APPLY_HITROLL;
    af.modifier  = 150;
    af.bitvector = 0;
    affect_to_char( victim, &af );

    af.location  = APPLY_SAVING_SPELL;
    af.modifier  = 0 - 150;
    affect_to_char( victim, &af );

    af.location  = APPLY_DAMROLL;
    af.modifier  = 150;
    affect_to_char( victim, &af );
    act( "$n is filled with God's Blessing.", victim, NULL, NULL, TO_ROOM );
    send_to_char( "You are filled with God's Blessing.\n\r", victim );
    return;
}

void spell_visage(int sn, int level, CHAR_DATA *ch, void *vo)
{
    CHAR_DATA *victim = (CHAR_DATA *) vo;
    AFFECT_DATA af;

    if ( is_affected( victim, sn ) ) return;

    af.type      = sn;
    af.duration  = number_range(2, 5);
    af.location  = APPLY_HITROLL;
    af.modifier  = level * 2;
    af.bitvector = 0;
    affect_to_char( victim, &af );

    af.location  = APPLY_DAMROLL;
    af.modifier  = level * 2;
    affect_to_char( victim, &af );

    act( "$n grows a horrid visage.", victim, NULL, NULL, TO_ROOM );
    send_to_char( "You squirm and squeel with glee.\n\r", victim );
    return;
}

void spell_ninja_focus(int sn, int level, CHAR_DATA *ch, void *vo)
{
  CHAR_DATA *victim = (CHAR_DATA *) vo;
  AFFECT_DATA af;

  if ( is_affected( victim, sn ) ) return;

  af.type      = sn;
  af.duration  = number_range(50, 100);
  af.location  = APPLY_HITROLL;
  af.modifier  = level * 10;
  af.bitvector = 0;
  affect_to_char( victim, &af );
  
  af.location  = APPLY_DAMROLL;
  af.modifier  = level * 10;
  affect_to_char( victim, &af );

  send_to_char( "You focus your mental prowess on battle.\n\r", victim );
  return;
}

void spell_forcebless( int sn, int