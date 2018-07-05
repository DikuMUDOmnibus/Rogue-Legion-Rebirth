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

ALIAS_DATA * alias_free;

void do_bountylist(CHAR_DATA *ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];
  DESCRIPTOR_DATA *d;

  sprintf(buf, " %s\n\r", get_dystopia_banner("  Bountylist  ", 60));
  send_to_char(buf, ch);
  stc("  #CName               Bounty     Status     Generation	Tier\n\r#n",ch);
  for ( d = descriptor_list; d != NULL; d = d->next )
  {
    if ( d->character != NULL )
    {
       if (!d->connected == CON_PLAYING) continue;
       if (d->character->level > 6) continue;
       if (!can_see(ch, d->character)) continue;
       sprintf(buf, "  #G%-15s#n    %6d        %2d           %d	%d\n\r",d->character->name, d->character->pcdata->bounty,
         d->character->race,d->character->generation, d->character->tier);
       stc(buf,ch);
    }
  }
  sprintf(buf, " %s\n\r", get_dystopia_banner("", 60));
  send_to_char(buf, ch);
  return;
}

void do_top( CHAR_DATA *ch, char *argument )
{
  char buf[MAX_STRING_LENGTH];
  int i;

  if (IS_NPC(ch)) return;

  stc("#r==--==#L**#r==--==#L**#r==--==#L**#r==--== #GTOP PKSCORE #r==--==#L**#r==--==#L**#r==--#r==#L**#r==--==#n\n\r\n\r",ch);
  for (i = 1; i <= MAX_TOP_PLAYERS / 2; i++)
  {
    sprintf(buf," %2d.  %-15s      %5d       %2d.  %-15s      %5d\n\r",
      i, top_board[i].name, top_board[i].pkscore,
      i + MAX_TOP_PLAYERS / 2, top_board[i + MAX_TOP_PLAYERS / 2].name, top_board[i + MAX_TOP_PLAYERS / 2].pkscore);
    send_to_char(buf,ch);
  }
  sprintf(buf,"\n\r                       #GYou #0:#G                %-4d\n\r",ch->race);
  send_to_char(buf,ch);
  stc("\n\r#r--==#L**#r==--==#L**#r==--==#L**#r==--==#L**#r==--==#L**#r==--==#L**#r==--==#L**#r==--==#L**#r==--==#L**#r==--#n\n\r",ch);
  return;
}

void do_trigger(CHAR_DATA *ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];
  char time[MAX_INPUT_LENGTH];
  OBJ_DATA *obj;
  int tick;

  argument = one_argument(argument, arg);
  one_argument(argument, time);

  if (arg[0] == '\0')
  {
    send_to_char("Trigger what ?\n\r", ch);
    return;
  }
  if (!is_number(time))
  {
    send_to_char("What should the timer be set at (a number please) ?\n\r", ch);
    return;
  }
  tick = atoi(time);
  if (tick < 1 || tick > 3)
  {
    send_to_char("Between 1 and 3 ticks please.\n\r", ch);
    return;
  }
  if ((obj = get_obj_carry(ch, arg, ch)) == NULL)
  {
    send_to_char("You don't have that item.\n\r", ch);
    return;
  }
  if (obj->item_type != ITEM_GRENADE)
  {
    send_to_char("That is not a grenade or a bomb.\n\r", ch);
    return;
  }
  if (obj->timer > 0)
  {
    send_to_char("It's already ticking, better run.\n\r", ch);
    return;
  }
  obj->timer = tick;
  send_to_char("You set the timer.\n\r", ch);
  act("$n fiddles with $p.", ch, obj, NULL, TO_ROOM);
  WAIT_STATE(ch, 6);
  return;
}

void do_dcredits(CHAR_DATA *ch, char *argument)
{
  do_help(ch, "dcredits");
  return;
}

void do_version( CHAR_DATA *ch, char *argument) 
{
  send_to_char("#Y*************************************************#n\n\r",ch);
  send_to_char("#Y*             This is MC2 Code                  *#n\n\r",ch);
  send_to_char("#Y*       Based on Dystopia Gold and MC1          *#n\n\r",ch);
  send_to_char("#Y*************************************************#n\n\r",ch);
}

void do_runeeq( CHAR_DATA *ch, char *argument )
{
  OBJ_INDEX_DATA *pObjIndex;
  OBJ_DATA *obj;
  char arg[MAX_INPUT_LENGTH];
  int vnum = 0;

  argument = one_argument( argument, arg );

  if (IS_NPC(ch)) return;

  if (arg[0] == '\0')
  {
    send_to_char("Please specify which piece of rune armor you wish to make: \n\rRing Collar Plate Helmet Leggings Boots Gloves Sleeves Cape Belt Bracer Mask.\n\r",ch);
    return;
  }
  if ( ch->bones < 15000 )
  {
    send_to_char("You don't have the 15K bones needed.\n\r",ch);
    return;
  }
  if      (!str_cmp(arg,"ring"        )) vnum = 814;
  else if (!str_cmp(arg,"collar"      )) vnum = 815;
  else if (!str_cmp(arg,"plate"       )) vnum = 817;
  else if (!str_cmp(arg,"helmet"      )) vnum = 818;
  else if (!str_cmp(arg,"leggings"    )) vnum = 819;
  else if (!str_cmp(arg,"boots"       )) vnum = 820;
  else if (!str_cmp(arg,"gloves"      )) vnum = 821;
  else if (!str_cmp(arg,"sleeves"     )) vnum = 822;
  else if (!str_cmp(arg,"cape"        )) vnum = 823;
  else if (!str_cmp(arg,"belt"        )) vnum = 824;
  else if (!str_cmp(arg,"bracer"      )) vnum = 816;
  else if (!str_cmp(arg,"mask"        )) vnum = 825;
  else
  {
    do_runeeq(ch,"");
    return;
  }
  if ( vnum == 0 || (pObjIndex = get_obj_index( vnum )) == NULL)
  {
    send_to_char("Missing object, please inform Jobo .\n\r",ch);
    return;
  }
  if(!IS_IMMORTAL(ch)) ch->bones -= 15000;
  obj = create_object(pObjIndex, 50);
  obj->questowner = str_dup(ch->pcdata->switchname);
  obj->ownerid = ch->pcdata->playerid;
  obj_to_char(obj, ch);
  ch->pcdata->rune_count++;
  act("You transform the 10K qp into $p.",ch,obj,NULL,TO_CHAR);
  act("$n forms $p out of 10K qp.",ch,obj,NULL,TO_ROOM);
  return;
}

void do_upkeep(CHAR_DATA *ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];

  if (IS_NPC(ch)) return;
  send_to_char("#RUpkeep list#n\n\r\n\r",ch);
  if (IS_SET(ch->act, AFF_HIDE))          send_to_char("* You cannot be seen by other players.\n\r",ch);
  if (IS_SET(ch->act, PLR_WIZINVIS))      send_to_char("* You cannot be seen by other players.\n\r",ch);
  if (IS_SET(ch->newbits, NEW_DARKNESS))  send_to_char("* You are shrouded in a globe of darkness.\n\r",ch);
  if (IS_AFFECTED(ch, AFF_SHADOWPLANE))   send_to_char("* You are standing in the shadowplane.\n\r",ch);
  if (IS_AFFECTED(ch, AFF_ETHEREAL))      send_to_char("* You are in ethereal form.\n\r",ch);
  if (IS_SET(ch->act,PLR_HOLYLIGHT))      send_to_char("* You have superior vision.\n\r",ch);
  if (IS_IMMUNE(ch,IMM_SHIELDED))         send_to_char("* You are shielded from scrying eyes.\n\r",ch);

  if (IS_CLASS(ch, CLASS_GIANT))
  {
    if (ch->pcdata->powers[GIANT_STANDFIRM] == 1) send_to_char("* You have your feet planted firmly in the ground.\n\r",ch);
    if (IS_SET(ch->newbits, NEW_CUBEFORM))        send_to_char("* You feel the strength of the dawn running through you.\n\r",ch);
  }

  if (IS_CLASS(ch, CLASS_DROW))
  {
    if (IS_SET(ch->newbits, NEW_DROWHATE))
      send_to_char("* You are filled with hatred towards other creatures.\n\r", ch);
  }

  if (IS_CLASS(ch, CLASS_LICH))
  {
    if (IS_IMMUNE(ch,IMM_SHIELD2)) send_to_char("* You are shielded by the powers of chaos.\n\r",ch);
    if (ch->tick_timer[TIMER_CALLGOLEMS] < 1)   send_to_char("* You can call on your golems.\n\r", ch);
    if (!IS_SET(ch->pcdata->powers[GOLEMS_SUMMON], HAS_SUMMONED_FIRE))
      send_to_char("* You can summon another #Rfire#n golem.\n\r", ch);
    if (!IS_SET(ch->pcdata->powers[GOLEMS_SUMMON], HAS_SUMMONED_CLAY))
      send_to_char("* You can summon another #oclay#n golem.\n\r", ch);
    if (!IS_SET(ch->pcdata->powers[GOLEMS_SUMMON], HAS_SUMMONED_STONE))
      send_to_char("* You can summon another #Lstone#n golem.\n\r", ch);
    if (!IS_SET(ch->pcdata->powers[GOLEMS_SUMMON], HAS_SUMMONED_IRON))
      send_to_char("* You can summon another #ciron#n golem.\n\r", ch);
  }

  if (IS_CLASS(ch, CLASS_NINJA))
  {
    if (IS_VAMPAFF(ch, VAM_CLAWS)) send_to_char("* You have iron wrists attached.\n\r",ch);
  }
  if (IS_CLASS(ch, CLASS_TANARRI))
  {
    if (ch->pcdata->powers[TANARRI_FURY_ON] == 1) send_to_char("* You are in a mad fury.\n\r", ch);
  }
  if (IS_CLASS(ch, CLASS_DRONE))
  {
    if (ch->pcdata->powers[DRONE_EYE] == DRONE_EYE_OFF)
      send_to_char("* Your mindseye is off.\n\r", ch);
    else if (ch->pcdata->powers[DRONE_EYE] == DRONE_EYE_LEVEL)
      send_to_char("* Your mindseye reads the level of your victims.\n\r", ch);
    else if (ch->pcdata->powers[DRONE_EYE] == DRONE_EYE_READAURA)
      send_to_char("* Your mindseye reads the aura of your victims.\n\r", ch);
    else if (ch->pcdata->powers[DRONE_EYE] == DRONE_EYE_CUSTOM)
    {
      sprintf(buf, "* Your mindseye : %s\n\r", ch->poweraction);
      send_to_char(buf, ch);
    }
    else send_to_char("* Your mindseye is bugged.\n\r", ch);
    if (ch->pcdata->powers[DRONE_NIGHTMARE] == 1)
      send_to_char("* You have unleashed your nightmarish aura.\n\r", ch);
  }

  if (IS_CLASS(ch, CLASS_WEREWOLF))
  {
    if (IS_GAR1(ch, WOLF_COCOON)) send_to_char("* You are engulfed in a cocoon.\n\r",ch);
  }

  if (IS_CLASS(ch, CLASS_FAE))
  {
    if (IS_SET(ch->newbits, NEW_CUBEFORM)) send_to_char("* You are a force of nature.\n\r",ch);
  }

  if (IS_CLASS(ch, CLASS_DEMON))
  {
    if (IS_POLYAFF(ch, POLY_ZULOFORM)) send_to_char("* You are in demonic form.\n\r", ch);
    if (IS_VAMPAFF(ch, VAM_CLAWS)) send_to_char("* You have wicked claws extending from your fingers.\n\r", ch);
    if (IS_VAMPAFF(ch, VAM_FANGS)) send_to_char("* You have sharp fangs extending from your gums.\n\r", ch);
    if (IS_DEMAFF(ch,DEM_TAIL)) send_to_char("* You have a long tail extending from your back.\n\r", ch);
    if (IS_DEMAFF(ch,DEM_HOOVES)) send_to_char("* You have hooves instead of feet.\n\r", ch);
  }

  if (IS_CLASS(ch, CLASS_VAMPIRE))
  {
    if (IS_SET(ch->extra, EXTRA_FLASH)) send_to_char("* You move with lightning speed.\n\r", ch);
    if (IS_SET(ch->extra, EXTRA_BAAL)) send_to_char("* You carry the spirit of Baal.\n\r", ch);
  }
  return;
}

/* The costy healer */
void do_healme(CHAR_DATA *ch, char *argument)
{
  if (IS_NPC(ch)) return;
  if (ch->in_room != NULL && ch->in_room->vnum != ROOM_VNUM_ALTAR)
  {
    send_to_char("The healer is located at the altar in midgaard.\n\r",ch);
    return;
  }
  if (ch->fight_timer > 0)
  {
    send_to_char("Not with a fighttimer.\n\r",ch);
    return;
  }
  if (ch->bones < 1000)
  {
    send_to_char("The healer demands 1000 bones as payment for his service.\n\r",ch);
    return;
  }
  ch->hit  = ch->max_hit;
  ch->mana = ch->max_mana;
  ch->move = ch->max_move;
  ch->loc_hp[0] = 0;
  ch->loc_hp[1] = 0;
  ch->loc_hp[2] = 0;
  ch->loc_hp[3] = 0;
  ch->loc_hp[4] = 0;
  ch->loc_hp[5] = 0;
  ch->loc_hp[6] = 0;
  send_to_char("The healer heals your wounds and takes 1000 bones as payment.\n\r",ch);
  ch->bones -= 1000;
  WAIT_STATE(ch, 36);
  return;
}

/* MUDSTAT command */
void do_mudstat( CHAR_DATA *ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];

  extern char str_boot_time[];

  if (IS_NPC(ch)) return;

  send_to_char("#0--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==--#n\n\r\n\r",ch);

  if (global_exp)
  {
    send_to_char("#R*** #0Double Experience is #GON!#n\n\r",ch);
    if(pulse_exp > 0)
    {
    sprintf(buf, "      #Y%d #0minutes remaining#n\n\r\n\r", pulse_exp);
    send_to_char(buf, ch);
    }
  }
  else
  {
    send_to_char("#R*** #0Double Experience is #ROFF#n\n\r",ch);
    sprintf(buf, "#0--- #wCost for Exp still: #Y%d#n\n\r\n\r", exp_cost);
    send_to_char(buf, ch);
  }
  if (global_qp)
    send_to_char("#R*** #0Double Bones is #GON!#n\n\r\n\r#n",ch);
  else
    send_to_char("#R*** #0Double Bones is #ROFF#n\n\r\n\r#n",ch);
  if (global_cp)
  {
    send_to_char("#R*** #0Double Class Points is #GON!#n\n\r\n\r#n",ch);
    if(pulse_cp > 0)
    {
    sprintf(buf, "      #Y%d #0minutes remaining#n\n\r\n\r", pulse_cp);
    send_to_char(buf, ch);
    }
  }
  else
  {
    send_to_char("#R*** #0Double Class Points is #ROFF#n\n\r#n",ch);
    sprintf(buf, "#0--- #wCost for Double CP still: #Y%d#n\n\r\n\r", cp_cost);
    send_to_char(buf, ch);
  }
  if (global_dt)
  {
    send_to_char("#R*** #0SUPER TRAINING is #GON!#n\n\r#n",ch);
    if(pulse_dt > 0)
    {
    sprintf(buf, "      #Y%d #0minutes remaining#n\n\r\n\r", pulse_dt);
    send_to_char(buf, ch);
    }
  }
  else
  {
    send_to_char("#R*** #0SUPER TRAINING is #ROFF#n\n\r#n",ch);
    sprintf(buf, "#0--- #wCost for Super Training still: #Y%d#n\n\r\n\r", dt_cost);
    send_to_char(buf, ch);
  }
  if (global_chaos)
    send_to_char("#s*#s*#s* #GWorld is in #sC#sh#sa#so#ss#n\n\r\n\r#n",ch);
  else
    send_to_char("\n\r#n",ch);
  if (ragnarok)
    send_to_char("#CRAGNAROK MODE!!!!!!!#n  Everyone can kill everyone (HELP RAGNAROK)\n\r\n\r",ch);
  else
  {
    sprintf(buf,"#RRagnarok is still #Y%d #Rbones from happening.#n\n\r\n\r",ragnarok_cost);
    send_to_char(buf,ch);
  }
  sprintf(buf, "#0Number of players connected since last copyover/restart :#C %d\n\r#n", players_logged);
  send_to_char(buf,ch);
  sprintf(buf, "#0Number of players beheaded since last copyover/restart  :#C %d\n\r#n", players_decap);
  send_to_char(buf,ch);
  sprintf(buf, "#0Amount of generation stolen since last copyover/restart :#C %d\n\r\n\r#n", players_gstolen);
  send_to_char(buf,ch);
  sprintf( buf, "%s was last (re)started at : %s\rThe system time is currently     : %s\n\r",
    MUDNAME, str_boot_time, (char *) ctime( &current_time));
  send_to_char( buf, ch );
  send_to_char("#0--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==#B**#0==--==--#n\n\r\n\r",ch);
  return;
}

void do_pkvision(CHAR_DATA *ch, char *argument)
{
  if (IS_NPC(ch)) return;
 
  if (UMIN(ch->race, (ch->pkill - ch->pdeath)) < 45)
  {
    send_to_char("huh?\n\r",ch);
    return;
  }
  if (has_timer(ch)) return;
  if (!IS_SET(ch->itemaffect, ITEMA_VISION))
  {
    SET_BIT(ch->itemaffect, ITEMA_VISION);
    SET_BIT(ch->newbits, NEW_VISION);  // so we know to remove it again.
    send_to_char("Your eyes flicker, and everything is clear.\n\r",ch);
  }
  else
    send_to_char("You already have superior sight.\n\r",ch);
  return;
}

void do_pkscry(CHAR_DATA *ch, char *argument)
{
  CHAR_DATA *victim;
  char arg[MAX_STRING_LENGTH];
  ROOM_INDEX_DATA *chroom;
  ROOM_INDEX_DATA *victimroom;

  argument = one_argument( argument, arg );

  if (IS_NPC(ch)) return;

  if (UMIN(ch->race, (ch->pkill - ch->pdeath)) < 10)
  {
    send_to_char("huh?\n\r",ch);
    return;
  }
  if ( arg[0] == '\0' )
  {
    send_to_char( "Scry on whom?\n\r", ch );
    return;
  }
  if ( ( victim = get_char_world( ch, arg ) ) == NULL )
  {
    send_to_char( "They aren't here.\n\r", ch );
    return;
  }
  if (IS_NPC(victim))
  {
    send_to_char("Not on mobs.\n\r",ch);
    return;
  }
  if (victim->in_room)
  {
    if (has_area_affect(victim->in_room->area, AREA_AFF_BADMOON, 0))
    {
      send_to_char("Some powerful magic prevent your scrying attempt.\n\r", ch);
      return;
    }
  }
  if (victim->trust > 6)
  {
    send_to_char("SPYING ON THE GODS!?!?!?!\n\r",ch);
    send_to_char("Someone is scrying you.\n\r",victim);
    return;
  }
  chroom = ch->in_room;
  victimroom = victim->in_room;
  char_from_room(ch);
  char_to_room(ch,victimroom);
  if (IS_AFFECTED(ch, AFF_SHADOWPLANE) && (!IS_AFFECTED(victim, AFF_SHADOWPLANE)))
  { 
    REMOVE_BIT(ch->affected_by, AFF_SHADOWPLANE);
    do_look(ch,"scry");
    SET_BIT(ch->affected_by, AFF_SHADOWPLANE);
  }
  else if (!IS_AFFECTED(ch, AFF_SHADOWPLANE) && (IS_AFFECTED(victim, AFF_SHADOWPLANE)))
  {
    SET_BIT(ch->affected_by, AFF_SHADOWPLANE);
    do_look(ch,"scry");
    REMOVE_BIT(ch->affected_by, AFF_SHADOWPLANE);
  } 
  else
    do_look(ch,"scry");
  char_from_room(ch);
  char_to_room(ch,chroom);
  if (ch->level < 7) ch->fight_timer += 3;
  if (victim->race > 14)
    send_to_char("You feel a slight tingle.\n\r",victim);
  return;
}

void do_pkobjscry(CHAR_DATA *ch, char *argument)
{
  CHAR_DATA *gch;
  CHAR_DATA *victim; 
  OBJ_DATA *obj;
  ROOM_INDEX_DATA *location;
  ROOM_INDEX_DATA *from;
  DESCRIPTOR_DATA *tmp;
  char buf[MAX_STRING_LENGTH];
  char arg[MAX_INPUT_LENGTH];
  bool afk = FALSE;

  one_argument(argument, arg);
   
  if (IS_NPC(ch)) return;  
  if (UMIN(ch->race, (ch->pkill - ch->pdeath)) < 35)
  {
    send_to_char("Huh?\n\r",ch);
    return;
  }
  if ((obj = get_obj_world(ch, arg)) == NULL)
  {
    send_to_char("Nothing like that in hell, earth, or heaven.\n\r", ch);
    return;
  }
  if (IS_OBJ_STAT(obj, ITEM_NOLOCATE))
  {
    send_to_char("A powerful force prevents the scrying of this object.\n\r", ch);
    return;
  }
  if ((gch = obj->carried_by) != NULL)
  {
    if (gch->in_room == NULL)
    {
      send_to_char("All you see is a chaotic mass of colors, nothing seems right.\n\r",ch);
      return;
    }
    if (has_area_affect(gch->in_room->area, AREA_AFF_BADMOON, 0))
    {
      send_to_char("Some powerful magic prevent your scrying attempt.\n\r", ch);
      return;
    }
    tmp = gch->desc;
    gch->desc = ch->desc;
    sprintf(buf,"A pair of eyes grows on %s's %s.\n\rThe eyes blink once, then disappear.\n\r", gch->name, obj->short_descr);
    for (victim = gch->in_room->people; victim != NULL; victim = victim->next_in_room)
    {
      if (victim == gch) continue;  // the victim cannot see this.
      send_to_char(buf,victim);
    }
    if (IS_SET(gch->extra, EXTRA_AFK))
    {
      afk = TRUE;
      REMOVE_BIT(gch->extra, EXTRA_AFK);
    }
    do_look(gch,"");
    gch->desc = tmp;
    if (afk) SET_BIT(gch->extra, EXTRA_AFK);
    return;
  }
  else if ((location = obj->in_room) != NULL)
  {
    if (has_area_affect(location->area, AREA_AFF_BADMOON, 0))
    {
      send_to_char("Some powerful magic prevent your scrying attempt.\n\r", ch);
      return;
    }
    sprintf(buf,"A pair of eyes grows on %s.\n\rThe eyes blink once, then disappear.\n\r", obj->short_descr);
    for (victim = location->people; victim != NULL; victim = victim->next_in_room)
    {
      if (victim == ch) continue; // the player is seeing through the item, and will not see the eyes even if he is in the room.
      send_to_char(buf,victim);
    }
    obj_from_room(obj);
    from = ch->in_room;  
    char_from_room(ch);
    char_to_room(ch, location);
    do_look(ch, "");
    char_from_room(ch);
    char_to_room(ch, from);
    obj_to_room(obj, location);
    return;
  }
  else  // inside something.
  {
    send_to_char("It's pitch black, wonder where this item is.\n\r",ch);
    return;
  }
}

void do_pkhunter(CHAR_DATA *ch, char *argument)
{
  MOB_INDEX_DATA *pMobIndex;
  CHAR_DATA *mob;
  MOB_TRIGGER *mProg;

  if (IS_NPC(ch)) return;
  if (UMIN(ch->race, (ch->pkill - ch->pdeath)) < 60)
  {
    send_to_char("Huh?\n\r",ch);
    return;
  }
  if (!TIME_UP(ch, TIMER_HUNTER))
  {
    send_to_char("You can only summon the hunter once every 18 hours.\n\r", ch);
    return;
  }
  if ((pMobIndex = get_mob_index(MOB_VNUM_HUNTER)) == NULL)
  {
    send_to_char("Bug, please report this to an immortal.\n\r", ch);
    return;
  }
  mob = create_mobile(pMobIndex);
  if (trigger_free == NULL)
  {
    mProg             = alloc_perm(sizeof(*mProg));
  }   
  else
  {
    mProg             = trigger_free;
    trigger_free      = trigger_free->next;
  }
  mProg->type         = MTRIG_HUNTER;
  mProg->vnum         = 0;
  mProg->keywords     = str_dup("&tracking*");
  mProg->roomOutput   = str_dup("Follow me master, I have found the trail.");
  mProg->chOutput     = str_dup("I cannot find the trail, master.");
  mProg->next         = mob->triggers;
  mob->triggers       = mProg;

  mob->decay_pulse    = number_range(6, 8);

  char_to_room(mob, ch->in_room);
  act("You call upon the dark hunter, and it appears in a puff of smoke.", ch, NULL, NULL, TO_CHAR);
  act("$n calls upon the dark hunter, and it appears in a puff of smoke.", ch, NULL, NULL, TO_ROOM);
  do_follow(ch, "hunter");
  SET_TIMER(ch, TIMER_HUNTER, 18);
  return;
}


void do_pkportal (CHAR_DATA *ch, char *argument)
{  
  CHAR_DATA *victim;
  char arg[MAX_STRING_LENGTH];
  ROOM_INDEX_DATA *location;

  one_argument (argument, arg);
    
  if (IS_NPC(ch)) return;
  if (UMIN(ch->race, (ch->pkill - ch->pdeath)) < 50)
  {
    send_to_char("Huh?\n\r",ch);
    return;
  }
  if ((victim = get_char_world(ch, arg)) == NULL)
  {
    send_to_char("Walk the silverpath to whom?\n\r", ch );
    return;
  }
  if (IS_NPC(victim))
  {
    send_to_char("Not on mobs.\n\r",ch);
    return;
  }
  if (victim->fight_timer == 0)
  {
    send_to_char("They are not engaged in pk.\n\r",ch);
    return;
  }
  if (IS_SET(victim->in_room->room_flags, ROOM_ASTRAL))
  {
    stc( "You can't find it's room.\n\r",ch);
    return;
  }
  if (IS_SET(ch->in_room->room_flags, ROOM_ASTRAL))
  {
    stc( "Your room is not connected to the astral plane.\n\r",ch);
    return;
  }
  location = victim->in_room;
  act("You step onto the silverpath.", ch, NULL, NULL, TO_CHAR);
  act("$n steps into thin air.", ch, NULL, NULL, TO_ROOM);
  char_from_room(ch);
  char_to_room(ch, location);
  do_look(ch, "auto");
  act("You leave the silverpath.", ch, NULL, NULL, TO_CHAR);
  act("$n steps out of thin air.", ch, NULL, NULL, TO_ROOM);
  WAIT_STATE(ch, 6);
  return;  
}

void do_pkaura (CHAR_DATA *ch, char *argument)
{
  CHAR_DATA *victim;
  char      arg [MAX_INPUT_LENGTH];
  char      buf [MAX_INPUT_LENGTH];
   
  argument = one_argument( argument, arg );
   
  if (IS_NPC(ch)) return;
 if (UMIN(ch->race, (ch->pkill - ch->pdeath)) < 20)
  {
    send_to_char("huh?\n\r",ch);
    return;
  }
  if ( arg[0] == '\0' )
  {
    send_to_char("Read the aura of who?\n\r",ch);
    return;
  }
  if ( ( victim = get_char_world( ch, arg ) ) == NULL )
  {
    send_to_char( "They aren't here.\n\r", ch );
    return;
  }
  if (IS_NPC(victim))
  {
    send_to_char("Not on mobs.\n\r",ch);
    return;
  }
  if (victim->in_room)
  {
    if (has_area_affect(victim->in_room->area, AREA_AFF_BADMOON, 0))
    {
      send_to_char("Some powerful magic prevent your aura scrying attempt.\n\r", ch);
      return;
    }
  }
  if (victim->trust > 6)
  