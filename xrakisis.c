#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"

void do_gainsymbiote(CHAR_DATA * ch, char *argument)
{
        char      buf[MAX_STRING_LENGTH];
	char arg[MAX_INPUT_LENGTH];

	if (IS_NPC(ch))
	return;
 
  one_argument( argument, arg);  
        
  if (ch->level < 3)
  {
    send_to_char("You must be an avatar to gain a Symbiote.\n\r",ch);
    return;
  }

  if (!IS_NPC(ch) && ch->symbiotetype != 0)
  {   
    send_to_char("You already have a symbiote.\n\r",ch);
    return;
  }

  if (arg[0] == '\0')
  {
  
        send_to_char("type gainsymbiote (name) to choose a Symbiote.\n\r",ch);
	send_to_char("#Y--#CDeath Symbiote\n\r",ch);
        send_to_char("#Y--#CLife Symbiote\n\r",ch);
	send_to_char("Cost: 200,000 Bones\n\r",ch);
        return;
  }



if (!str_cmp(arg,"death"))
{
   if (ch->bones < 200000)
   {
        send_to_char( "You do not have enough bones.\n\r", ch);
        return;
   }
   else
   {
	ch->symbiotetype = SYMBIOTE_DEATH;
	send_to_char( "A Death Symbiote absorbs into your body.\n\r", ch);
	ch->bones -= 200000;
	return;
   }
}        
else if (!str_cmp(arg,"life"))
{
   if (ch->bones < 200000)
   {
        send_to_char( "You do not have enough bones.\n\r", ch);
        return;
   }
   else
   {
	ch->symbiotetype = SYMBIOTE_LIFE;
	send_to_char( "A Life Symbiote absorbs into your body.\n\r", ch);
	ch->bones -= 200000;
	return;
   }
}        
  else do_gainsymbiote(ch,"");   
  return;
}


void do_advancesymbiote(CHAR_DATA * ch, char *argument)
{
        char      buf[MAX_STRING_LENGTH];
	char arg1[MAX_INPUT_LENGTH];
	int sgainexp = 10000 * ch->symbiotelvl;
	int sgainbones = 100 * ch->symbiotelvl;
	int mkills = 1000;

	if (IS_NPC(ch))
	return;

  one_argument( argument, arg1);

  if (ch->level < 3)
  {
    send_to_char("You must be avatar to advance your Symbiote.\n\r",ch);
    return;
  }
  if (ch->symbiotetype < 1)
  {
    send_to_char("You do not have a symbiote.\n\r",ch);
    return;
  }

  if (arg1[0] == '\0')
  {  
  
send_to_char("#R[#0--------------------#R[#7Symbiote Screen#R]#0--------------------#R]#n\n\r", ch);


	if (ch->symbiotetype == 2) stc("Death Symbiote\n\r",ch);
	if (ch->symbiotetype == 1) stc("Life Symbiote\n\r",ch);


    sprintf(buf, "Damroll Modifier: %d  \n\r",ch->symbiotedr);
    send_to_char(buf,ch);
    send_to_char("(damroll) cost 1 point for +5 DR\n\r", ch);
     

    sprintf(buf, "Hitroll Modifier: %d\n\r",ch->symbiotehr);
    send_to_char(buf,ch);
    send_to_char("(hitroll) cost 1 point for +5 HR\n\r", ch);

    sprintf(buf, "AC Modifier: %d\n\r",ch->symbioteac);
    send_to_char(buf,ch);
    send_to_char("(AC) cost 1 point for -10 AC\n\r", ch);

    sprintf(buf, "Damcap Modifier: %d\n\r",ch->symbiotedc);
    send_to_char(buf,ch);
    send_to_char("(damcap) cost 1 point for +10 Damcap\n\r", ch);

    sprintf(buf, "Current Level: %d\n\r",ch->symbiotelvl);
    send_to_char(buf,ch);

    sprintf(buf, "Symbiote Points %d\n\r",ch->symbiotepoints);
    send_to_char(buf, ch);

    sprintf(buf, "Mob kills until next point: %d\n\r",(mkills -= ch->symbiotemkills));
    send_to_char(buf,ch);

    sprintf(buf,"Cost of advancing symbiote's level :%d EXP, %d Bones\n\r", sgainexp, sgainbones);
    send_to_char(buf,ch);

    send_to_char("Symbiote Spells and Skills\n\r",ch);
    send_to_char("Level 0: 2x Exp\n\r",ch);
    send_to_char("Level 15: Spirit Armor\n\r",ch);
    send_to_char("Level 25: Bark Skin\n\r",ch);
    send_to_char("Level 60: Primal Rage\n\r",ch);

	if (ch->symbiotetype == 2)
    send_to_char("Level 80: Death Ray\n\r",ch);
	if (ch->symbiotetype == 1)
    send_to_char("Level 80: Holy Beam\n\r",ch);

/*    if (ch->symbiotetype == 1) 
    {
    send_to_char("Death Symbiote Abilities\n\r", ch);
    send_to_char("
   send_to_char("Superberserk (level 0)\n\r", ch);
    send_to_char("Tremble (level 20)\n\r", ch);
    send_to_char("4xexp (level 25)\n\r", ch);
    send_to_char("Greathelm (level 30)\n\r", ch);
    send_to_char("Mistform (level 50)\n\r", ch);
    send_to_char("Displacerform (level 70)\n\r", ch);
    }
    if (ch->symbiotetype == 2) 
    {
    send_to_char("Life Symbiote Abilities\n\r", ch);
    send_to_char("Thunderhammer (level 0)\n\r", ch);
    send_to_char("4xexp (level 25)\n\r", ch);
    send_to_char("Lifeshield (level 30)\n\r", ch);
    send_to_char("Mistform (level 50)\n\r", ch);
    }

*/
	send_to_char("#R[#0--------------------#R[#7Symbiote Screen#R]#0--------------------#R]#n\n\r", ch);
   return;
}


if (!str_cmp(arg1,"damroll"))
{

	if (ch->symbiotedr > 200)
	{
	send_to_char( "Symbiote Damroll Maxed\n\r", ch);
	return;
	}
	if (ch->symbiotepoints < 1)
	{
	send_to_char( "Not enough symbiote points.\n\r", ch);
	return;
	}
	send_to_char( "Damroll increased by 5.\n\r", ch);
	ch->symbiotedr += 5;
        ch->symbiotepoints -= 1;
	return;
}

if (!str_cmp(arg1,"hitroll"))
{

	if (ch->symbiotehr > 200)
	{
	send_to_char( "Symbiote Hitroll Maxed\n\r", ch);
	return;
	}
        if (ch->symbiotepoints < 1)
        {
        send_to_char( "Not enough symbiote points.\n\r", ch);
        return;
        }
	send_to_char( "Hitroll increased by 5.\n\r", ch);
	ch->symbiotehr += 5;
        ch->symbiotepoints -= 1;
	return;
}
if (!str_cmp(arg1,"damcap"))
{

	if (ch->symbiotedc > 400)
	{
	send_to_char( "Symbiote Damcap Maxed\n\r", ch);
	return;
	}
        if (ch->symbiotepoints < 1)
        {
        send_to_char( "Not enough symbiote points.\n\r", ch);
        return;
        }
	send_to_char( "Damcap increased by 10.\n\r", ch);
	ch->symbiotedc += 10;
        ch->symbiotepoints -= 1;
	return;
}
if (!str_cmp(arg1,"ac"))
{

	if (ch->symbioteac > 400)
	{
	send_to_char( "Symbiote AC Maxed\n\r", ch);
	return;
	}
        if (ch->symbiotepoints < 1)
        {
        send_to_char( "Not enough symbiote points.\n\r", ch);
        return;
        }
	send_to_char( "Armor increased by 10.\n\r", ch);
	ch->symbioteac += 10;
        ch->symbiotepoints -= 1;
	return;
}
if (!str_cmp(arg1,"level"))
{
		
	if( ch->symbiotelvl >= 100 )
	{
        send_to_char( "Already Maximum Symbiote Level.\n\r", ch );
        return;
	}
	if( ch->exp < sgainexp )
	{
        sprintf( buf, "Not enough Experience points, you need %d more.\n\r", ( sgainexp - ch->exp ) );
        send_to_char( buf, ch );
        return;
        }
        if( ch->bones < sgainbones ) 
	{
        sprintf( buf, "Not enough Bones, you need %d more.\n\r", ( sgainbones - ch->bones ) );
        send_to_char( buf, ch );
        return;
        }


        ch->bones -= sgainbones;
        ch->exp -= sgainexp;
        ch->symbiotelvl++;
	ch->symbiotepoints++;
	if (ch->symbiotetype == 2) stc("Your Death Symbiote has gained a level.\n\r",ch);
	if (ch->symbiotetype == 1) stc("Your Life Symbiote has gained a level.\n\r",ch);
}
	

return;
}

void do_consecrate(CHAR_DATA *ch, char *argument)
{
	OBJ_DATA *obj;
	char arg1[MAX_INPUT_LENGTH];
	char arg2[MAX_INPUT_LENGTH];
	char buf[MAX_STRING_LENGTH];
	int livingweap_needed = 0;

	argument = one_argument( argument, arg1 );
	argument = one_argument( argument, arg2 );

	if (arg1[0] == '\0')
	{
	send_to_char("Which item do you wish to consecrate?\n\r", ch);
	return;
	}
	if ( (obj = get_obj_carry(ch, arg1, ch)) == NULL)
	{
	send_to_char("You are not carrying that item.\n\r", ch);
	return;
	}
	if (obj->item_type != ITEM_WEAPON)
	{
	send_to_char("You may only Consecrate weapons.\n\r",ch);
	return;
	}
      else if (obj->item_type == ITEM_WEAPON)
	{
	sprintf( buf, "Weapon Name: %s \n\r", obj->short_descr );
	send_to_char( buf, ch );
        sprintf(buf, "Weapon is of type %s.\n\r", flag_string(weapon_flags, obj->value[3]));
	send_to_char( buf, ch );
	sprintf( buf, "Weapon Damage Min: %d  Max: %d \n\r", obj->value[1], obj->value[2] );
	send_to_char( buf, ch );
	sprintf( buf, "Weapon Level: %d, Weapon Points: %d \n\r", obj->weapon_level, obj->weapon_points);
	send_to_char( buf, ch );
	livingweap_needed = (obj->weapon_level * 100);
	sprintf( buf, "Weapon Experiance: %d, EXP til next Level: %d \n\r", obj->weapon_currentxp, 
	(livingweap_needed - obj->weapon_currentxp));
	send_to_char( buf, ch );
	sprintf( buf, "Earth Level: %d \n\r", obj->earth_level );
	send_to_char( buf, ch );
	sprintf( buf, "Lightning Level: %d \n\r", obj->lightning_level );
	send_to_char( buf, ch );
	sprintf( buf, "Fire Level: %d \n\r", obj->fire_level );
	send_to_char( buf, ch );
	sprintf( buf, "Water Level: %d \n\r", obj->water_level );
	send_to_char( buf, ch );
	springf( buf, "Shocking(5), Flaming(5), Frost(5), Vampiric(5), Poison(5)\n\r",ch);
	send_to_char( buf, ch );
	sprintf( buf, "Souls obtained With %s: %d \n\r",obj->short_descr, obj->soul_level );
	send_to_char( buf, ch );
	send_to_char("Cost of Advancing weapon: 10 Weapon Points\n\r",ch);
	send_to_char("Cost of Min Damage Increase: 1 Cost of Max Damage Increase: 1 \n\r", ch);
	}
	if (!str_cmp(arg2,"flaming"))
	{
		if (obj->weapon_points < 5)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s is engulfed in fire.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		SET_BIT(obj->weapflags, WEAPON_FLAMING);
		obj->weapon_points -= 5;
		return;
		}
	}
	if (!str_cmp(arg2,"shocking"))
	{
		if (obj->weapon_points < 5)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s is enveloped with Electicity.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		SET_BIT(obj->weapflags, WEAPON_SHOCKING);
		obj->weapon_points -= 5;
		return;
		}
	}
	if (!str_cmp(arg2,"frost"))
	{
		if (obj->weapon_points < 5)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s is covered with ice.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		SET_BIT(obj->weapflags, WEAPON_FROST);
		obj->weapon_points -= 5;
		return;
		}
	}
	if (!str_cmp(arg2,"vampiric"))
	{
		if (obj->weapon_points < 5)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s absorbs an evil taint.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		SET_BIT(obj->weapflags, WEAPON_VAMPIRIC);
		obj->weapon_points -= 5;
		return;
		}
	}
	if (!str_cmp(arg2,"poison"))
	{
		if (obj->weapon_points < 5)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s is coated with poison.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		SET_BIT(obj->weapflags, WEAPON_POISON);
		obj->weapon_points -= 5;
		return;
		}
	}
	if (!str_cmp(arg2,"earth"))
	{
		if (obj->weapon_points < 10)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s earth raised by one.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		obj->earth_level++;
		obj->weapon_points -= 10;
		return;
		}
	}
	if (!str_cmp(arg2,"lightning"))
	{
		if (obj->weapon_points < 10)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s lightning raised by one.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		obj->lightning_level++;
		obj->weapon_points -= 10;
		return;
		}
	}
	if (!str_cmp(arg2,"fire"))
	{
		if (obj->weapon_points < 10)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s fire raised by one.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		obj->fire_level++;
		obj->weapon_points -= 10;
		return;
		}
	}
	if (!str_cmp(arg2,"water"))
	{
		if (obj->weapon_points < 10)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s water raised by one.\n\r",obj->short_descr);
		send_to_char(buf,ch);
		obj->water_level++;
		obj->weapon_points -= 10;
		return;
		}
	}
	if (!str_cmp(arg2,"min"))
	{
		if (obj->weapon_points < 5)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s Min Damage increases!\n\r",obj->short_descr);
		send_to_char(buf,ch);
		obj->value[1]++;
		obj->weapon_points -= 1;
		return;
		}
	}
	if (!str_cmp(arg2,"max"))
	{
		if (obj->weapon_points < 1)
		{
		send_to_char("You dont have enough weapon points.\n\r",ch);
		return;
		}
		else
		{
		sprintf(buf,"%s's Max Damage increases!\n\r",obj->short_descr);
		send_to_char(buf,ch);
		obj->value[2]++;
		obj->weapon_points -= 1;
		return;
		}
	}

}	
