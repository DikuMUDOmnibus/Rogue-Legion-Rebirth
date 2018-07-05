/*
 * Copyright (c) 2000 Fatal Dimensions
 *
 * See the file "LICENSE" or information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

/* Ported to Smaug 1.4a by Samson of Alsherok.
 * Consolidated for cross-codebase compatibility by Samson of Alsherok.
 * Modifications and enhancements to the code
 * Copyright (c)2001-2003 Roger Libiez ( Samson )
 * Registered with the United States Copyright Office
 * TX 5-562-404
 *
 * Contains codebase specific defines to make the rest of it all work - hopefully.
 * Anything your codebase needs to alter is more than likely going to be stored in here.
 * This should be the only file you need to edit to solve unforseen compiling problems
 * if I've done this properly. And remember, this is all based on what these defines mean
 * in your STOCK code. If you've made adjustments to any of it, then you'll need to adjust
 * them here too.
 */
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

   #define first_descriptor descriptor_list
   #define I3MAXPLAYERS -1 /* Merc doesn't track this */
   #define CH_I3DATA(ch)      ((ch)->pcdata->i3chardata)
   #define CH_I3LEVEL(ch)     ((ch)->level)
   #define CH_I3NAME(ch)      ((ch)->name)
   #define CH_I3TITLE(ch)     ((ch)->pcdata->title)
   #define CH_I3RANK(ch)      (IS_IMMORTAL((ch)) ? "Immortal" : "Player" )
   #define CH_I3SEX(ch)       ((ch)->sex)
   #define I3WIZINVIS(ch)     (IS_IMMORTAL((ch)) && IS_SET((ch)->act, PLR_WIZINVIS))
