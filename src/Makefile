CC      = gcc
#NOCRYPT = -DNOCRYPT
C_FLAGS = -Wall -O -ggdb $(NOCRYPT)
L_FLAGS = -lz -lcrypt -lpthread
#L_FLAGS = -lz -lcrypt

#Intermud-3 - Comment out to disable I3 support in your code

#I3 = 1

O_FILES = act_comm.o act_info.o act_move.o act_obj.o act_wiz.o bit.o mccp.o \
	board.o build.o clan.o comm.o daemon.o db.o angel.o x-socials.o\
	demon.o drow.o fight.o kav_wiz.o handler.o kav_fight.o kav_info.o \
	interp.o mage.o magic.o mem.o monk.o monk2.o ninja.o olc.o \
	olc_act.o olc_save.o save.o special.o string.o arena.o auction.o\
	update.o vamp.o ww.o shapeshifter.o tanarri.o undead_knight.o \
        samurai.o wizutil.o const.o cyborg.o lich.o jope.o religion.o \
        jobo_king.o jobo_fight.o jobo_act.o jobo_wiz.o jobo_util.o \
        jobo_comm.o jobo_save.o social-edit.o jobo_update.o spiderdroid.o \
        jobo_quest.o msp.o kav_soundex.o desc_map.o jobo_shop.o zarius_proj.o \
	zarius.o changes.o vote.o skyblade.o ghoul.o draconian.o thief.o \
	shadow.o priest.o jedi.o psycho.o giant.o hobbit.o fae.o drone.o \
	zarius_quest.o zarius_bank.o olc_mpcode.o mob_prog.o \
	mob_cmds.o recycle.o wizlist.o zarius_comm.o zarius_games.o \
	shinobi.o xrakisis_eq.o xrakisis.o dragon.o elemental.o \
        armorcraft.o
	
ifdef I3
   O_FILES := i3.o $(O_FILES)
   C_FLAGS := $(C_FLAGS) -DI3 -DI3MERC
endif

merc: $(O_FILES)
	rm -f mcloud
	$(CC)  -o mcloud $(O_FILES) $(L_FLAGS)
	chmod g+w mcloud
	chmod g+w $(O_FILES)


.c.o: merc.h
	$(CC) -c $(C_FLAGS) $<

clean :
	rm -f *.o ; rm -f mcloud
