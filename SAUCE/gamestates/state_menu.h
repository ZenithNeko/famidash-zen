#pragma code-name(push, "XCD_BANK_03")
#pragma data-name(push, "XCD_BANK_03")
#pragma rodata-name(push, "XCD_BANK_03")

const uint8_t loNTAddrTableTitleScreen[]={
    LSB(NTADR_A(9, 11)),	// -1 = 4
    LSB(NTADR_A(15, 11)),	// 0
    LSB(NTADR_A(21, 11)),	// 1 
    LSB(NTADR_A(12, 17)),	// 2
    LSB(NTADR_A(18, 17)),	// 3
    LSB(NTADR_A(9, 11)),	// 4
    LSB(NTADR_A(15, 11))	// 5 = 0
};

const uint8_t hiNTAddrTableTitleScreen[]={
    MSB(NTADR_A(9, 11)),	// -1 = 4
    MSB(NTADR_A(15, 11)),	// 0
    MSB(NTADR_A(21, 11)),	// 1
    MSB(NTADR_A(12, 17)),	// 2
    MSB(NTADR_A(18, 17)),	// 3
    MSB(NTADR_A(9, 11)),	// 4
    MSB(NTADR_A(15, 11))	// 5 = 0
};

const unsigned char* const leveltexts[] = {
  level1text, level2text, NULL, NULL, level5text, NULL, NULL, NULL, NULL, NULL, NULL, levelCtext, NULL, NULL, NULL, NULL, NULL, level12text
};
const unsigned char* const leveltexts2[] = {
  level1text2, level2text2, level3text2, level4text2, level5text2, level6text2, level7text2, level8text2, level9text2, levelAtext2, levelBtext2, levelCtext2, levelDtext2, levelEtext2, levelFtext2, level10text2, level11text2, level12text2
};

const unsigned char level_text_size[] = {
    sizeof(level1text) - 1,
	sizeof(level2text) - 1,
	0,
	0,
	sizeof(level5text) - 1,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(levelCtext) - 1,
	0,
	0,
	0,
	0,
	0,
	sizeof(level12text) - 1,
};
const unsigned char level_text_size2[] = {
    sizeof(level1text2) - 1,
	sizeof(level2text2) - 1,
	sizeof(level3text2) - 1,
	sizeof(level4text2) - 1,
	sizeof(level5text2) - 1,
	sizeof(level6text2) - 1,
	sizeof(level7text2) - 1,
	sizeof(level8text2) - 1,
	sizeof(level9text2) - 1,
	sizeof(levelAtext2) - 1,
	sizeof(levelBtext2) - 1,
	sizeof(levelCtext2) - 1,
	sizeof(levelDtext2) - 1,
	sizeof(levelEtext2) - 1,
	sizeof(levelFtext2) - 1,
	sizeof(level10text2) - 1,
	sizeof(level11text2) - 1,
	sizeof(level12text2) - 1,
};

const char coin_counter[][3] = {
  "___",
  "^__",
  "_^_",
  "^^_",
  "__^",
  "^_^",
  "_^^",
  "^^^",
};



#include "defines/color1_charmap.h"
/*
	Refreshes level name & number
*/
void __fastcall__ refreshmenu(void) {
	__A__ = idx16_hi_NOC(leveltexts, level);
	if (__A__) draw_padded_text(leveltexts[level & 0x7F], level_text_size[level], 17, NTADR_A(8, 10));
	else one_vram_buffer_horz_repeat(' ', 17, NTADR_A(8, 10));
	// if (leveltexts2[level]) // always true
	draw_padded_text(leveltexts2[level & 0x7F], level_text_size2[level], 17, NTADR_A(8, 11));

	if (LEVELCOMPLETE[level]) { one_vram_buffer('y', NTADR_A(7, 9));
	one_vram_buffer('z', NTADR_A(8, 9)); }
	else one_vram_buffer_horz_repeat(' ', 2, NTADR_A(7, 9));

	{	// write the difficulty
		tmp1 = difficulty_list[level];
		pal_col(0x0a, difficulty_pal_A[tmp1]);
		pal_col(0x0b, difficulty_pal_B[tmp1]);
		
		tmp1 = (tmp1 << 1) + 'a';
		one_vram_buffer(tmp1, NTADR_A(7, 10));
		one_vram_buffer(++tmp1, NTADR_A(8, 10));
		one_vram_buffer((tmp1 += ('c'-'b')), NTADR_A(7, 11));
		one_vram_buffer(++tmp1, NTADR_A(8, 11));
		

	}
	tmp7 = stars_list[level];
	tmp8 = 0;
	while (tmp7 > 9) {
		tmp7 = tmp7 - 10;
		tmp8++;
	}

	if (tmp8) one_vram_buffer('0'+tmp8, NTADR_A(22, 9));
	else one_vram_buffer(' ', NTADR_A(22, 9));
	one_vram_buffer('0'+tmp7, NTADR_A(23, 9));
//palette stuff
	pal_col(0,colors_list[level]);
	pal_col(0xE,colors_list[level]);
//coin stuff
	coins = 0;


// then in the function...
// combine all three into a single number from 0 - 7 to represent which coins have been grabbed
		tmp7 = byte((byte(coin3_obtained[level] << 1) | coin2_obtained[level]) << 1) | coin1_obtained[level];
		tmp7 = byte(tmp7<<1) + tmp7;
// actually draw the coins
		multi_vram_buffer_horz((const char * const)coin_counter+tmp7, 3, NTADR_A(22, 12));

};

void state_menu();
//void bgmtest();


#include "defines/mainmenu_charmap.h"
void levelselection() {
  
	pal_fade_to_withmusic(4,0);
	ppu_off();
	pal_bright(0);
	// pal_bg(paletteMenu);
	set_scroll_x(0);
	set_scroll_y(0);  
	
	vram_adr(NAMETABLE_A);
	vram_unrle(game_main_menu);   

	refreshmenu();

	// one_vram_buffer(0xb0+TOTALCOINSTENS, NTADR_A(17,17));
	// one_vram_buffer(0xb0+TOTALCOINSONES, NTADR_A(18,17));

	cube_rotate[0] = 0;
	cube_rotate[1] = 0;
	attempts = 0;

	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	while (1){
		ppu_wait_nmi();
		music_update();

		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		if (twoplayer) one_vram_buffer('d', NTADR_A(31, 2));
		else one_vram_buffer('e', NTADR_A(31, 2));

		// if (pad[0] & PAD_UP && pad_new[0] & PAD_SELECT) { twoplayer ^= 0x01; sfx_play(sfx_coin, 0); }

		if (pad_new[0] & PAD_START){
			sfx_play(sfx_start_level, 0);
			famistudio_music_stop();
			for (tmp1 = 0; tmp1 < 30; tmp1++){
				ppu_wait_nmi();
				music_update();
			}
			gameState = 0x02;
			pal_fade_to(4,0);
			kandotemp = 0;
			return;
		}

		if (pad_new[0] & (PAD_B)){
			kandowatchesyousleep = 0;
			return;
		}
			
		if (pad_new[0] & PAD_RIGHT && pad_new[0] & PAD_LEFT) {}
			
		else if (pad_new[0] & (PAD_RIGHT)){
			++level;
			sfx_play(sfx_select, 0);
			if (level >= LEVEL_COUNT){
				level = 0x00;
			}
			refreshmenu();
		//	break;
		}
		else if (pad_new[0] & PAD_LEFT){
			--level;
			sfx_play(sfx_select, 0); 
			if (level == 0xFF){
				level = LEVEL_COUNT-1;
			}
			
			//break;
			refreshmenu();
		}
	}	

}


#include "defines/mainmenu_customize.h"

const uint8_t loNTAddrTableCustomizeScreen[] = {
	LSB(NTADR_A(13, 8)),		// -1 = 3
	LSB(NTADR_A(4, 14)),		// 0
	LSB(NTADR_A(13, 14)),		// 1
	LSB(NTADR_A(22, 14)),		// 2
	LSB(NTADR_A(13, 8)),		// 3
	LSB(NTADR_A(4, 14))			// 4 = 0
};

const uint8_t hiNTAddrTableCustomizeScreen[] = {
	MSB(NTADR_A(13, 8)),		// -1 = 3
	MSB(NTADR_A(4, 14)),		// 0
	MSB(NTADR_A(13, 14)),		// 1
	MSB(NTADR_A(22, 14)),		// 2
	MSB(NTADR_A(13, 8)),		// 3
	MSB(NTADR_A(4, 14))			// 4 = 0
};

static const uint8_t iconTable[] = {
	0, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x20, ('M'-'a'), 0x24, 0x26, 0x40, 0x42
};

void updateColors() {
	if (pad_new[0] & PAD_UP) {
		if (uint8_inc(icon_colors, settingvalue) & 0x30) {
			if ((uint8_t)(icon_colors[settingvalue] & 0x0F) >= 0x0D)
				uint8_store(icon_colors, settingvalue, (icon_colors[settingvalue] + 0x10) & 0x30);
		} else {
			if (((icon_colors[settingvalue] - 0x0D) & 0xFE) == 0)	// if color == 0x0D or 0x0E
				icon_colors[settingvalue] = 0x0F;
		}
	}
	if (pad_new[0] & PAD_DOWN) { 
		if (uint8_dec(icon_colors, settingvalue) & 0x30) {
			if ((uint8_t)(icon_colors[settingvalue] & 0x0F) >= 0x0D)
				uint8_store(icon_colors, settingvalue, (icon_colors[settingvalue] & 0x30) | 0x0C);
		} else {
			if (((icon_colors[settingvalue] - 0x0D) & 0xFE) == 0)	// if color == 0x0D or 0x0E
				icon_colors[settingvalue] = 0x0C;
		}
	}
	//if ((pad[0] & PAD_SELECT) && (pad_new[0] & PAD_A)) icon_colors[settingvalue] = 0x0D;	
}

void customize_screen() {
	settingvalue = 3; 
	pal_fade_to_withmusic(4,0);
	ppu_off();
	pal_bg(paletteMenu);
	mmc3_set_8kb_chr(MENUICONBANK);
	vram_adr(NAMETABLE_A);
	vram_unrle(customizescreen);   	

	TOTALCOINS = 0;
	TOTALCOINSONES = 0;
	TOTALCOINSTENS = 0;
	TOTALSTARSONES = 0;
	TOTALSTARSTENS = 0;

	for (tmp2 = 0; tmp2 < LEVEL_COUNT; tmp2++) {
		// TOTALCOINS = TOTALCOINS + coin1_obtained[tmp2] + coin2_obtained[tmp2] + coin3_obtained[tmp2];
		__A__ = tmp2; __asm__("tay");
		__A__ = TOTALCOINS;
		__asm__("clc \n adc %v, y", coin1_obtained);
		__asm__("clc \n adc %v, y", coin2_obtained);
		__asm__("clc \n adc %v, y", coin3_obtained);
		TOTALCOINS = __A__;
		if (LEVELCOMPLETE[tmp2]) TOTALSTARSONES += stars_list[tmp2];
	}
	TOTALCOINSONES = TOTALCOINS;
	
	while (TOTALSTARSONES > 9) {
		TOTALSTARSTENS = TOTALSTARSTENS + 1;
		TOTALSTARSONES = TOTALSTARSONES - 10;
	}
	if (TOTALCOINSTENS) one_vram_buffer(0xd0+TOTALCOINSTENS, NTADR_A(16,19));
	one_vram_buffer(0xd0+TOTALCOINSONES, NTADR_A(17,19));	

	if (TOTALSTARSTENS) one_vram_buffer(0xd0+TOTALSTARSTENS, NTADR_A(18,21));
	one_vram_buffer(0xd0+TOTALSTARSONES, NTADR_A(19,21));	

	one_vram_buffer('h', NTADR_A(13, 8));		
	one_vram_buffer('i', NTADR_A(13, 9));
	one_vram_buffer('f', NTADR_A(18, 8));
	one_vram_buffer('g', NTADR_A(18, 9));

	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	while (1) {
		tmp3 = 0;

		ppu_wait_nmi();
		music_update();

		pal_col(0x0a,color1);
		pal_col(0x0b,color2);
		pal_col(0x09,color3);

		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		if (!retro_mode) {
			tmp1 = iconTable[icon] + 'a';
			one_vram_buffer(tmp1, NTADR_A(15, 8));		
			one_vram_buffer(++tmp1, NTADR_A(16, 8));		
			one_vram_buffer((tmp1 += ('c'-'b')), NTADR_A(15, 9));		
			one_vram_buffer(++tmp1, NTADR_A(16, 9));		
		}
		else {
			one_vram_buffer('a'+0x6A, NTADR_A(15,8));			
			one_vram_buffer('b'+0x6A, NTADR_A(16,8));			
			one_vram_buffer('c'+0x6A, NTADR_A(15,9));			
			one_vram_buffer('d'+0x6A, NTADR_A(16,9));			
		}
		if (settingvalue == 3 && !retro_mode) {
			if (pad_new[0] & PAD_UP) {
				icon++;
				if (icon > (MAX_ICONS - 1)) icon = 0;
			}
			if (pad_new[0] & PAD_DOWN) {
				if (icon == 0) icon = MAX_ICONS - 1;
				else icon--;
			}
		} else if (settingvalue != 3) updateColors();

		if (pad_new[0] & PAD_RIGHT) {
			settingvalue++;
			if (settingvalue == 4) settingvalue = 0;
			tmp3--;
		}
		if (pad_new[0] & PAD_LEFT) {
			if (settingvalue == 0) settingvalue = 3;
			else settingvalue--;
			tmp3++;
		}

		if (tmp3) {
			tmp4 = settingvalue; ++tmp4;
			tmp5 = loNTAddrTableCustomizeScreen[tmp4]|(hiNTAddrTableCustomizeScreen[tmp4]<<8);
			one_vram_buffer('h', tmp5);		
			one_vram_buffer('i', tmp5 + VRAM_OFF(0, 1));
			one_vram_buffer('f', tmp5 = addloNOC(tmp5, VRAM_OFF(5, 0)));
			one_vram_buffer('g', tmp5 + VRAM_OFF(0, 1));

			tmp4 += tmp3;   // Get the old index
			tmp5 = loNTAddrTableCustomizeScreen[tmp4]|(hiNTAddrTableCustomizeScreen[tmp4]<<8);
			one_vram_buffer(' ', tmp5);		
			one_vram_buffer(' ', tmp5 + VRAM_OFF(0, 1));
			one_vram_buffer(' ', tmp5 = addloNOC(tmp5, VRAM_OFF(5, 0)));
			one_vram_buffer(' ', tmp5 + VRAM_OFF(0, 1));
		}

		if (pad_new[0] & PAD_B || pad_new[0] & PAD_START) {
			return;
		}
	}
}




#include "defines/mainmenu_charmap.h"

void funsettings() {
	settingvalue = 0; 
	pal_fade_to_withmusic(4,0);
	ppu_off();
	pal_bg(paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(funsettingscreen);   
	ppu_on_all();
	one_vram_buffer('c', NTADR_A(4, 7));	// settingvalue is set to 0 by default	
	pal_fade_to_withmusic(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		if (invisible) 	one_vram_buffer('g', NTADR_A(26, 7));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 7));	// this is auto optimized by cc65

		if ((options & platformer)) 	one_vram_buffer('g', NTADR_A(26, 9));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 9));	// this is auto optimized by cc65

		if (retro_mode) 	one_vram_buffer('g', NTADR_A(26, 11));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 11));	// this is auto optimized by cc65

		if (discomode) 	one_vram_buffer('g', NTADR_A(26, 13));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 13));	// this is auto optimized by cc65
		
		if (gameboy_mode) 	one_vram_buffer('g', NTADR_A(26, 16));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 16));	// this is auto optimized by cc65

		tmp1 = settingvalue;

		if (pad_new[0] & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == 4) { settingvalue = 0; }
			else { settingvalue++; sfx_play(sfx_select, 0);  }
		}

		if (pad_new[0] & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = 4; }
			else { settingvalue--; sfx_play(sfx_select, 0);  }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 2) << 5 = tmp1<<6 = (tmp1<<8)>>2
			one_vram_buffer(' ', NTADR_A(4, 7)+((tmp1<<8)>>2));
			one_vram_buffer('c', NTADR_A(4, 7)+((settingvalue<<8)>>2));
		}

		if (discomode & 0x02) { one_vram_buffer('2' - 0x20, NTADR_A(25, 14)); one_vram_buffer('X'-0x1B, NTADR_A(26, 14)); }
		else if (discomode & 0x04) { one_vram_buffer('3' - 0x20, NTADR_A(25, 14)); one_vram_buffer('X'-0x1B, NTADR_A(26, 14)); }
		else if (discomode & 0x08) { one_vram_buffer('4' - 0x20, NTADR_A(25, 14)); one_vram_buffer('X'-0x1B, NTADR_A(26, 14)); }
		else if (discomode & 0x10) { one_vram_buffer('5' - 0x20, NTADR_A(25, 14)); one_vram_buffer('X'-0x1B, NTADR_A(26, 14)); }
		else if (discomode & 0x01) { one_vram_buffer('1' - 0x20, NTADR_A(25, 14)); one_vram_buffer('X'-0x1B, NTADR_A(26, 14)); }
		else if (!discomode) { one_vram_buffer(' '-0x01, NTADR_A(25, 14)); one_vram_buffer(' '-0x01, NTADR_A(26, 14)); }

		if (pad_new[0] & (PAD_START | PAD_A)) {
			switch (settingvalue) {
				case 0x00: invisible ^= 1; break;
				case 0x01: options ^= platformer; break;
				case 0x02: retro_mode ^= 1; break;
				case 0x03: 
					if (!discomode) { discomode = 1; one_vram_buffer('1' - 0x20, NTADR_A(25, 14)); one_vram_buffer('X', NTADR_A(26, 14)); }
					else if (discomode & 0x10) { discomode = 0; one_vram_buffer(' ', NTADR_A(25, 14)); one_vram_buffer(' ', NTADR_A(26, 14)); }
					else if (discomode == 1) { discomode = 1 + 0x01; one_vram_buffer('2' - 0x20, NTADR_A(25, 14)); one_vram_buffer('X', NTADR_A(26, 14)); }
					else {
						discomode = discomode << 1;
					}
					break;
				case 0x04: if (!gameboy_mode) { gameboy_mode = 1;   color_emphasis(COL_EMP_GREY); }
					   else if (gameboy_mode) { gameboy_mode = 0; color_emphasis(COL_EMP_NORMAL); }
					   break;
					
				
				
			};
		}
			
		if (pad_new[0] & PAD_B) {
			// one_vram_buffer(' ', NTADR_A(6, 8));
			// one_vram_buffer(' ', NTADR_A(6, 12));
			// one_vram_buffer(' ', NTADR_A(6, 16));
			//one_vram_buffer(' ', NTADR_A(4, 8));
			//one_vram_buffer(' ', NTADR_A(4, 12));
			//one_vram_buffer(' ', NTADR_A(4, 16));
			return;
		}

	}
}


#include "defines/mainmenu_charmap.h"

void settings() {
	settingvalue = 0; 
	pal_fade_to_withmusic(4,0);
	ppu_off();
	pal_bg(paletteSettings);
	vram_adr(NAMETABLE_A);
	vram_unrle(settingscreen);   	
	ppu_on_all();
	one_vram_buffer('c', NTADR_A(4, 7));	// settingvalue is set to 0 beforehand
	pal_fade_to_withmusic(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		if (twoplayer) one_vram_buffer('g', NTADR_A(26, 7));
		else one_vram_buffer('f', NTADR_A(26, 7));

		if (options & oneptwoplayer) one_vram_buffer('g', NTADR_A(26, 9));
		else one_vram_buffer('f', NTADR_A(26, 9));

		if (options & sfxoff) one_vram_buffer('f', NTADR_A(26, 11));
		else one_vram_buffer('g', NTADR_A(26, 11));

		if (options & musicoff) one_vram_buffer('f', NTADR_A(26, 13));
		else one_vram_buffer('g', NTADR_A(26, 13));

		if (options & jumpsound) one_vram_buffer('g', NTADR_A(26, 15));
		else one_vram_buffer('f', NTADR_A(26, 15));

		if (decorations) one_vram_buffer('g', NTADR_A(26, 17));
		else one_vram_buffer('f', NTADR_A(26, 17));

		if (trails) one_vram_buffer('g', NTADR_A(26, 19));
		else one_vram_buffer('f', NTADR_A(26, 19));

		tmp1 = settingvalue;

		if (pad_new[0] & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == 7) { settingvalue = 0; sfx_play(sfx_select, 0); }
			else { settingvalue++; sfx_play(sfx_select, 0);  }
		}

		if (pad_new[0] & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = 7; sfx_play(sfx_select, 0); }
			else { settingvalue--; sfx_play(sfx_select, 0);  }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 2) << 5 = tmp1<<6 = (tmp1<<8)>>2
			one_vram_buffer(' ', NTADR_A(4, 7)+((tmp1<<8)>>2));
			one_vram_buffer('c', NTADR_A(4, 7)+((settingvalue<<8)>>2));
		}
		
		if (pad_new[0] & (PAD_A | PAD_START)) {
			switch (settingvalue) {
				case 0: // oneptwoplayer
					twoplayer ^= 1; break;
				case 1: // oneptwoplayer
					options ^= oneptwoplayer; break;
				case 2: // sfxoff
					options ^= sfxoff; break;
				case 3: // musicoff
					options ^= musicoff; if (options & musicoff) { famistudio_music_stop(); music_update(); } else { music_play(song_menu_theme); } break;
				case 4: // jumpsound
					options ^= jumpsound; break;
				case 5:
					decorations ^= 1; break;
				case 6:
					trails ^= 1; break;					
				case 7:
					if (pad[0] & PAD_A && pad_new[0] & PAD_START) {
					setdefaultoptions();
						// one_vram_buffer(0xb0+TOTALCOINSTENS, NTADR_A(17,17));
						// one_vram_buffer(0xb0+TOTALCOINSONES, NTADR_A(18,17));					
						sfx_play(sfx_death, 0);
						music_play(song_menu_theme);
						// one_vram_buffer_horz_repeat(' ', 1, NTADR_A(16, 15));					
					}
					break;
			}
		}
		if (options & platformer) twoplayer = 0;		
		if (twoplayer) options &= platformer^0xff;		

		if (pad_new[0] & PAD_B) {
			return;
		}

	}
}


#include "defines/mainmenu_charmap.h"

#ifdef FLAG_ENABLE_VER_NUM
	#if FLAG_BETA_BUILD
		const unsigned char ver[] = "BETA BUILD";
	#else
		const unsigned char ver[] = "VER";
	#endif
#endif

void state_menu() {
	pal_fade_to_withmusic(4,0);
	ppu_off();
    pal_bg(splashMenu);

	mmc3_set_8kb_chr(MENUBANK);

	set_scroll_x(0);
    set_scroll_y(0);

	kandowatchesyousleep = 0;

//	mmc3_set_prg_bank_1(GET_BANK(state_menu));

	switch (kandotemp){
		case 0x00:	music_play(song_menu_theme); break;
		case 0x01:	break;
	}

	settingvalue = 0;
	
	has_practice_point = 0;
	
	// Enable SRAM write
	POKE(0xA001, 0x80);

	kandotemp = 1;
//	invisible = 0;
	

	oam_clear();

	// Expand the data for the menu nametable while the PPU is still off
    vram_adr(NAMETABLE_A);
    vram_unrle(game_start_screen);

	#ifdef FLAG_ENABLE_VER_NUM
		multi_vram_buffer_horz(ver, sizeof(ver)-1, NTADR_A(2,2));
		if (!FLAG_BETA_BUILD) {
			one_vram_buffer(FLAG_MAJ_VER, NTADR_A(6,2));
			one_vram_buffer(0x18, NTADR_A(7,2)); // dot
			one_vram_buffer(FLAG_MIN_VER, NTADR_A(8,2));
		}
	#endif
 	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	tmp4 = menuselection; ++tmp4;
	tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
	one_vram_buffer('a', tmp5);
	one_vram_buffer('b', addloNOC(tmp5, 1));
	pad[0] = pad_poll(0); // read the first controller
	pad_new[0] = get_pad_new(0);
	while (!(pad_new[0] & PAD_START)){
		rand8();
		ppu_wait_nmi();
		music_update();
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		//if ((pad[0] & PAD_LEFT) && (pad[0] & PAD_DOWN) && (pad[0] & PAD_SELECT) && (pad_new[0] & PAD_B)) { color_emphasis(COL_EMP_GREY); color_emphasis(COL_EMP_GREEN); }

		tmp3 = 0;
		
		if (pad_new[0] & PAD_RIGHT) {
			if (menuselection == 4) menuselection = 0;
			else menuselection++;
			tmp3--;
			sfx_play(sfx_select, 0);
		}
		if (pad_new[0] & PAD_LEFT) {
			if (menuselection == 0) menuselection = 4;
			else menuselection--;
			tmp3++;
			sfx_play(sfx_select, 0);
		}

		if (tmp3) {    // menu selection incremented
			tmp4 = menuselection; ++tmp4;
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
			one_vram_buffer('a', tmp5);
			one_vram_buffer('b', addloNOC(tmp5, 1));

			tmp4 += tmp3;   // Get the old index
			tmp5 = loNTAddrTableTitleScreen[tmp4]|(hiNTAddrTableTitleScreen[tmp4]<<8);
			one_vram_buffer(' ', tmp5);
			one_vram_buffer(' ', addloNOC(tmp5, 1));
		}
	}		

	switch (menuselection) {
		case 0x00: kandowatchesyousleep = 1;  levelselection(); return;
		case 0x01: funsettings(); return;
		case 0x02: gameState = 4; return;
		case 0x03: settings(); return;
		case 0x04: customize_screen(); return;
	};
  
}


/*
#include "defines/mainmenu_charmap.h"

void bgmtest() {
	
  	famistudio_music_stop();
  	music_update();
	kandotemp=0;
	pal_fade_to(4,0);
	ppu_off();
	pal_bg(paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(bgmtestscreen);   	
	ppu_on_all();
	pal_fade_to(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		one_vram_buffer(' '-1, NTADR_A(14, 10));
		one_vram_buffer(0xb0+song, NTADR_A(15,10));

		if (settingvalue == 0) {
			one_vram_buffer('c', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
		}		
		else if (settingvalue == 1) {
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer('c', NTADR_A(11, 14));
		}
		if (pad_new[0] & PAD_DOWN) settingvalue ^= 1;
		if (pad_new[0] & PAD_UP) settingvalue ^= 1;
		if (pad_new[0] & PAD_RIGHT && settingvalue == 0) { song++; if (song == song_max) {song = 0;} }
		if (pad_new[0] & PAD_LEFT && settingvalue == 0) { if (song == 0) {song = song_max - 1;} else song--; }
//		if (pad_new[0] & PAD_RIGHT && settingvalue == 1) sfx ++;
		if ((pad_new[0] & PAD_START || pad_new[0] & PAD_A) && settingvalue == 0) music_play(song);
		if (pad_new[0] & PAD_B) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			return;
		}
	}
	
}
*/
#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
