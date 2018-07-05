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


void do_forge( CHAR_DATA *ch, char *argument )
{   
  char arg1[MAX_STRING_LENGTH];
  char arg2[MAX_STRING_LENGTH];
  OBJ_DATA *obj = NULL;
  OBJ_DATA *obj2 = NULL;

  argument = one_argument( argument, arg1 );
  argument = one_argument( argument, arg2 );

  if (IS_NPC(ch)) return;

  if ( arg1[0] == '\0' || arg2[0] == '\0' )
  {
    send_to_char("Syntax : forge <slab/gem/hilt> <item>   (read HELP FORGE for details)\n\r",ch);
    return;
  }
  if ((obj = get_obj_carry( ch, arg2,ch) ) == NULL)
  {
    send_to_char( "You are not carrying that item.\n\r", ch );
    return;
  }
  if (IS_SET(obj->quest, QUEST_ARTIFACT))
  {
    send_to_char("You cannot forge artifacts.\n\r", ch);
    return;
  }
  if (!IS_SET(ch->pcdata->jflags, JFLAG_KNOWS_FORGING))
  {
    send_to_char( "You don't have the skill to do any forging", ch);
    return;
  }
  if (ch->practice < 100 && !IS_CLASS(ch, CLASS_CYBORG))
  {
  	stc("It costs 100 primal to forge something", ch);
  	return;
  }
  if (!str_prefix(arg1, "copper"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require a copper forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_COPPER)
    {
      send_to_char("That thing isn't copper!\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_COPPER) 
          || IS_SET(obj->spectype, SITEM_IRON) 
          || IS_SET(obj->spectype, SITEM_MITHRIL) 
          || IS_SET(obj->spectype, SITEM_STEEL) ||
      IS_SET(obj->spectype, SITEM_ADAMANTITE))
    {
      send_to_char("That item is already forged.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_COPPER);
    forge_affect(obj, 3);
    extract_obj( obj2 );
    act("You forge copper onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges copper onto $p.\n\r",ch,obj,NULL,TO_ROOM);	
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "iron"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require an iron forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_IRON)
    {
      send_to_char("That thing isn't iron!\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_COPPER) 
          || IS_SET(obj->spectype, SITEM_IRON) 
          || IS_SET(obj->spectype, SITEM_MITHRIL) 
          || IS_SET(obj->spectype, SITEM_STEEL) ||
      IS_SET(obj->spectype, SITEM_ADAMANTITE))
    {
      send_to_char("That item is already forged.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_IRON);
    forge_affect(obj, 6);
    extract_obj( obj2 );
    act("You forge iron onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges iron onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "steel"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require a steel forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_STEEL)
    {
      send_to_char("That thing isn't steel!\n\r",ch);
      return;
    }
     else if (IS_SET(obj->spectype, SITEM_COPPER) 
          || IS_SET(obj->spectype, SITEM_IRON) 
          || IS_SET(obj->spectype, SITEM_MITHRIL) 
          || IS_SET(obj->spectype, SITEM_STEEL) ||
      IS_SET(obj->spectype, SITEM_ADAMANTITE))
    {
      send_to_char("That item is already forged.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_STEEL);
    forge_affect(obj, 9);
    extract_obj( obj2 );
    act("You forge steel onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges steel onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "adamantite"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require an adamantite forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_ADAMANTITE)
    {
      send_to_char("That thing isn't copper!\n\r",ch);
      return;
    }
 else if (IS_SET(obj->spectype, SITEM_COPPER) 
          || IS_SET(obj->spectype, SITEM_IRON) 
          || IS_SET(obj->spectype, SITEM_MITHRIL) 
          || IS_SET(obj->spectype, SITEM_STEEL) ||
      IS_SET(obj->spectype, SITEM_ADAMANTITE))
    {
      send_to_char("That item is already forged.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_ADAMANTITE);
    forge_affect(obj, 12);
    extract_obj( obj2 );
    act("You forge adamantite onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges adamantite onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "mithril"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL )
    {
      send_to_char( "You require an mithril forging slab.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_MITHRIL)
    {
      send_to_char("That thing isn't mithril!\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_COPPER) 
          || IS_SET(obj->spectype, SITEM_IRON) 
          || IS_SET(obj->spectype, SITEM_STEEL)
          || IS_SET(obj->spectype, SITEM_MITHRIL)
          || IS_SET(obj->spectype, SITEM_ADAMANTITE))
    {
      send_to_char("That item is already forged.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_MITHRIL);
    forge_affect(obj, 16);
    extract_obj( obj2 );
    act("You forge mithril onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges mithril onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix( arg1, "diamond" ))
  {
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require a diamond gemstone.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't a diamond gemstone.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge a diamond onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a diamond onto $p.\n\r",ch,obj,NULL,TO_ROOM); 
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 8000;
    }
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 8;
    return;
  }
  if (!str_prefix( arg1, "emerald" ))
  {
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require an emerald gemstone.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't an emerald gemstone.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge an emerald onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges an emerald onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 13000;
    }
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 13;
    return;
  }
  if (!str_prefix( arg1, "sapphire" ))
  {      
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL) 
    {        
      send_to_char( "You require a sapphire gemstone.\n\r", ch);
      return;
    }        
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't a sapphire gemstone.\n\r",ch);
      return; 
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }        
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge a sapphire onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a sapphire onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 12000;
    }
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 12;
    return;
  }
  if (!str_prefix( arg1, "ruby" ))
  {      
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL) 
    {        
      send_to_char( "You require a ruby gemstone.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't a ruby gemstone.\n\r",ch);
      return; 
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }        
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge a ruby onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a ruby onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 11000;
    }
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 11;
    return;
  }
  if (!str_prefix( arg1, "pearl" ))
  {      
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL) 
    {        
      send_to_char( "You require a pearl gemstone.\n\r", ch);
      return;
    }        
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't a pearl gemstone.\n\r",ch);
      return; 
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {        
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }        
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge a pearl onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a pearl onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {       
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 5000;
    }       
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 5;
    return;
  }        
  if (!str_prefix( arg1, "topaz" ))
  {      
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL) 
    {        
      send_to_char( "You require a topaz gemstone.\n\r", ch);
      return;
    }        
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't a topaz gemstone.\n\r",ch);
      return; 
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {        
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }        
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge a topaz onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a topaz onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {       
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 10000;
    }       
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 10;
    return;
  }        
  if (!str_prefix( arg1, "amethyst" ))
  {      
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL) 
    {        
      send_to_char( "You require an amethyst gemstone.\n\r", ch);
      return;
    }        
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't an amethyst gemstone.\n\r",ch);
      return; 
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {        
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }        
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge an amethyst onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges an amethyst onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {       
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 3000;
    }       
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 3;
    return;
  }        
  if (!str_prefix( arg1, "onyx" ))
  {      
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL) 
    {        
      send_to_char( "You require an onyx gemstone.\n\r", ch);
      return;
    }        
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't an onyx gemstone.\n\r",ch);
      return; 
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {        
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }        
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge an onyx onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges an onyx onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {       
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 9000;
    }       
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 9;
    return;
  }        
  if (!str_prefix( arg1, "opal" ))
  {      
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL) 
    {        
      send_to_char( "You require an opal gemstone.\n\r", ch);
      return;
    }        
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't n opal gemstone.\n\r",ch);
      return; 
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {        
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }        
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge an opal onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges an opal onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {       
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 6000;
    }       
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 6;
    return;
  }        
  if (!str_prefix( arg1, "lazuli" ))
  {      
    if ((obj2 = get_obj_carry(ch, (arg1),ch)) == NULL) 
    {        
      send_to_char( "You require a lazuli gemstone.\n\r", ch);
      return;
    }        
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't a lazuli gemstone.\n\r",ch);
      return; 
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {        
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }        
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge a lazuli onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a lazuli onto $p.\n\r",ch,obj,NULL,TO_ROOM);
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    if (obj->item_type == ITEM_WEAPON)
    {       
      if (obj->value[0] >= 1000) obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 2000;
    }       
    else if (obj->item_type == ITEM_ARMOR) obj->value[3] = 2;
    return;
  }
  if (!str_prefix( arg1, "jade" ))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require some jade.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_GEMSTONE)
    {
      send_to_char("That isn't a jade gemstone.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_GEMSTONE))
    {
      send_to_char("That item is already forged with a gemstone.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_GEMSTONE);
    extract_obj( obj2 );
    act("You forge some jade onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges some jade onto $p.\n\r",ch,obj,NULL,TO_ROOM);	
    if (obj->item_type == ITEM_WEAPON)
    {
      if (obj->value[0] >= 1000)
      obj->value[0] -= ((obj->value[0] / 1000) * 1000);
      obj->value[0] += 7000;
    }
    else if (obj->item_type == ITEM_ARMOR)
    { 
      if (!IS_EVIL(ch)) obj->value[3] = 7;
      else obj->value[3] = 139;
    }
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "ivory"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require an ivory hilt.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_HILT)
    {
      send_to_char("That isn't an ivory hilt.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_HILT))
    {
      send_to_char("That item is already forged with a hilt.\n\r",ch);
      return;
    }
    else if (obj->item_type != ITEM_WEAPON)
    { 
      send_to_char("You can only add hilts to weapons.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_HILT);
    extract_obj( obj2 );
    act("You forge an ivory hilt onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges an ivory hilt onto $p.\n\r",ch,obj,NULL,TO_ROOM);	
    obj->value[0] += 24;
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "ebony"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require an ebony hilt.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_HILT)
    { 
      send_to_char("That isn't an ebony hilt.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_HILT))
    {
      send_to_char("That item is already forged with a hilt.\n\r",ch);
      return;
    }
    else if (obj->item_type != ITEM_WEAPON)
    {
      send_to_char("You can only add hilts to weapons.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_HILT);
    extract_obj( obj2 );
    act("You forge an ebony hilt onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges an ebony hilt onto $p.\n\r",ch,obj,NULL,TO_ROOM);
    obj->value[0] += 4;
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "crystal"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require a crystal hilt.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_HILT)
    { 
      send_to_char("That isn't a crystal hilt.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_HILT))
    {
      send_to_char("That item is already forged with a hilt.\n\r",ch);
      return;
    }
    else if (obj->item_type != ITEM_WEAPON)
    {
      send_to_char("You can only add hilts to weapons.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_HILT);
    extract_obj( obj2 );
    act("You forge a crystal hilt onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a crystal hilt onto $p.\n\r",ch,obj,NULL,TO_ROOM);
    obj->value[0] += 30;
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "marble"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require a marble hilt.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_HILT)
    { 
      send_to_char("That isn't a marble hilt.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_HILT))
    {
      send_to_char("That item is already forged with a hilt.\n\r",ch);
      return;
    }
    else if (obj->item_type != ITEM_WEAPON)
    {
      send_to_char("You can only add hilts to weapons.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_HILT);
    extract_obj( obj2 );
    act("You forge a marble hilt onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a marble hilt onto $p.\n\r",ch,obj,NULL,TO_ROOM);
    obj->value[0] += 34;
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "gold"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require a gold hilt.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_HILT)
    { 
      send_to_char("That isn't  gold hilt.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_HILT))
    {
      send_to_char("That item is already forged with a hilt.\n\r",ch);
      return;
    }
    else if (obj->item_type != ITEM_WEAPON)
    {
      send_to_char("You can only add hilts to weapons.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_HILT);
    extract_obj( obj2 );
    act("You forge a gold hilt onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a gold hilt onto $p.\n\r",ch,obj,NULL,TO_ROOM);
    obj->value[0] += 48;
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "bronze"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require a bronze hilt.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_HILT)
    { 
      send_to_char("That isn't a bronze hilt.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_HILT))
    {
      send_to_char("That item is already forged with a hilt.\n\r",ch);
      return;
    }
    else if (obj->item_type != ITEM_WEAPON)
    {
      send_to_char("You can only add hilts to weapons.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_HILT);
    extract_obj( obj2 );
    act("You forge a bronze hilt onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a bronze hilt onto $p.\n\r",ch,obj,NULL,TO_ROOM);
    obj->value[0] += 1;
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "sandstone"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require a sandstone hilt.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_HILT)
    { 
      send_to_char("That isn't a sandstone hilt.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_HILT))
    {
      send_to_char("That item is already forged with a hilt.\n\r",ch);
      return;
    }
    else if (obj->item_type != ITEM_WEAPON)
    {
      send_to_char("You can only add hilts to weapons.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_HILT);
    extract_obj( obj2 );
    act("You forge a sandstone hilt onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a sandstone hilt onto $p.\n\r",ch,obj,NULL,TO_ROOM);
    obj->value[0] += 36;
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  if (!str_prefix(arg1, "limestone"))
  {
    if ((obj2 = get_obj_carry( ch, (arg1),ch)) == NULL)
    {
      send_to_char( "You require a limestone hilt.\n\r", ch);
      return;
    }
    if (obj2->item_type != ITEM_HILT)
    { 
      send_to_char("That isn't a limestone hilt.\n\r",ch);
      return;
    }
    else if (IS_SET(obj->spectype, SITEM_HILT))
    {
      send_to_char("That item is already forged with a hilt.\n\r",ch);
      return;
    }
    else if (obj->item_type != ITEM_WEAPON)
    {
      send_to_char("You can only add hilts to weapons.\n\r",ch);
      return;
    }
    SET_BIT(obj->spectype, SITEM_HILT);
    extract_obj( obj2 );
    act("You forge a limestone hilt onto $p.\n\r",ch, obj,NULL,TO_CHAR);
    act("$n forges a limestone hilt onto $p.\n\r",ch,obj,NULL,TO_ROOM);
    obj->value[0] += 53;
      if(!IS_CLASS(ch, CLASS_CYBORG) )
  {
  	ch->practice -= 100;
  }
    return;
  }
  else send_to_char("You cannot forge that.\n\r", ch);
  

  return;
}



void clear_stats( CHAR_DATA *ch )
{
    OBJ_DATA *obj;
    OBJ_DATA *obj_next;

  if (IS_NPC(ch))
    return;

    for ( obj = ch->carrying; obj != NULL; obj = obj_next )
    {
	obj_next = obj->next_content;
	if ( obj->wear_loc != WEAR_NONE )
    {
      obj_from_char(obj);
      obj_to_char(obj, ch);
    }
    }
    while ( ch->affected )
	affect_remove( ch, ch->affected );
    ch->armor			= 100;
    ch->hitroll			= 0;
    ch->damroll			= 0;
    ch->saving_throw		= 0;
    ch->pcdata->mod_str		= 0;
    ch->pcdata->mod_int		= 0;
    ch->pcdata->mod_wis		= 0;
    ch->pcdata->mod_dex		= 0;
    ch->pcdata->mod_con		= 0;
    save_char_obj( ch );
    return;
}

/* In case we need to remove our pfiles, or wanna turn mortal for a bit */
void do_relevel( CHAR_DATA *ch, char *argument )
{

    if (IS_NPC(ch)) return;

    if  (!str_cmp(ch->pcdata->switchname,"Xrakisis")) 
    {
	ch->level	= MAX_LEVEL;
	ch->trust	= MAX_LEVEL;
        ch->max_hit	= 300000;
	ch->hit		= ch->max_hit;
	ch->max_mana	= 300000;
	ch->mana	= ch->max_mana;
	ch->max_move	= 300000;
	ch->move	= ch->max_move;
        ch->pcdata->security = 9;
	send_to_char("Do