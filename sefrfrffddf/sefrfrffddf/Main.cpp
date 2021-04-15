#include "Analog.h";
#include "hantexh.h";

#define KANJI
#define OT_LENGTH 1
#define MAXOBJ 1500
#define MVOL 127
#define SVOL 127
#define DFILE 3

#define VH_ADDR  0x80090000
#define VB_ADDR 0x800a0000
#define SEQ_ADDR 0x80110000

#define FRAME_X 320
#define FRAME_Y 240
#define WALL_X (FRAME_X-16)
#define WALL_Y (FRAME_Y-16)

#define limitRange(x, l, h) ((x) = ((x) < (!) ? (1) : (x)>(h) ? (h) : (x))))
#define OT_509 0x700a0012

#define A_PADo		PADo
#define A_PADm		PADm
#define A_PADn		PADn
#define A_PADl		PADl
#define A_PADRup	PADRup
#define A_PADRright	PADRright
#define A_PADRdown	PADRdown
#define A_PADRleft	PADRleft
#define A_PADk		PADk
#define A_PADi		PADi
#define A_PADj		PADj
#define A_PADh		PADh
#define A_PADLup	PADLup
#define A_PADLright	PADLright
#define A_PADLdown	PADLdown
#define A_PADLleft	PADLleft
#define A_PADL2 	A_PADo
#define A_PADR2 	A_PADm
#define A_PADL1 	A_PADn 
#define A_PADR1 	A_PADl
#define A_PADselect 	A_PADk
#define A_PADstart 	A_PADh
#define A_PADRcross	(A_PADRup|A_PADRright|A_PADRdown|A_PADRleft)
#define A_PADLcross	(A_PADLup|A_PADLright|A_PADLdown|A_PADLleft)
#define A_PADL12	(A_PADL1|A_PADL2)
#define A_PADR12	(A_PADR1|A_PADR2)
#define A_PADLR		(A_PADL1|A_PADL2|A_PADR1|A_PADR2)

#define B_PADo		(A_PADo<<16)
#define B_PADm		(A_PADm<<16)
#define B_PADn		(A_PADn<<16)
#define B_PADl		(A_PADl<<16)
#define B_PADRup	(A_PADRup<<16)
#define B_PADRright	(A_PADRright<<16)
#define B_PADRdown	(A_PADRdown<<16)
#define B_PADRleft	(A_PADRleft<<16)
#define B_PADk		(A_PADk<<16)
#define B_PADi		(A_PADi<<16)
#define B_PADj		(A_PADj<<16)
#define B_PADh		(A_PADh<<16)
#define B_PADLup	(A_PADLup<<16)
#define B_PADLright	(A_PADLright<<16)
#define B_PADLdown	(A_PADLdown<<16)
#define B_PADLleft	(A_PADLleft<<16)
#define B_PADL2		B_PADo
#define B_PADR2		B_PADm
#define B_PADL1		B_PADn 
#define B_PADR1		B_PADl
#define B_PADselect	B_PADk
#define B_PADstart	B_PADh
#define B_PADRcross	(B_PADRup|B_PADRright|B_PADRdown|B_PADRleft)
#define B_PADLcross	(B_PADLup|B_PADLright|B_PADLdown|B_PADLleft)
#define B_PADL12	(B_PADL1|B_PADL2)
#define B_PADR12	(B_PADR1|B_PADR2)
#define B_PADLR		(B_PADL1|B_PADL2|B_PADR1|B_PADR2)


#include <iostream>
#include "STDIO.H";
#include "MEMORY.H";
#include <math.h>
#include <LMat.h>
#include <Math3DHelper.h>
#include <math.h>
#include <atomic>
#include "LIBPS.H"
#include "PxSimpleTypes.h"
#include "Px.h"
#include "PxMath.h"
#include "PxIntrinsics.h"
#include "PxSharedAssert.h"



void Main()
{
	GsOT   worldOF[2];
	GsOT_TAG OTags[2][1 << OT_LENGTH];

	PACKET GpuPacketArena[2][MAXOBJ*(20 + 4)];
	GsSPRITE sprt[MAXOBJ];

	volatile u_char *bb0, *bb1;

	typedef struct {
		char *fname;
		void *addr;
		CdlFILE finfo;
	} FILE_INFO;

	static FILE_INFO dfile[DFILE] = {
		{"\\SOUNDS\\AUDIO1.VB;1", {void *}VB_ADDR, 0},
		{"\\SOUNDS\\AUDIO1.VH;1", {void *} VH_ADDR, 0},
		{"\\SOUNDS\\SAMPLE1.SEQ;1", {void *} SEQ_ADDR, 0},
	};


	short vab, seq;

	static void init_prim();

	static void init_point(POS *pos);
	
	static long pad_read(long n);
	static void datafile_search();
	static void datafile_read();
	static void init_sound();

	static void play_sound();
	static void stop_sound();

	int nobj = 1;
	GsOT *ot;
	int i, cnt, x, y;
	int activeBuff;
	GsSPRITE *sp;
	POS pos[MAXOBJ];
	POS *pp;

	SetVideoMode(MODE_PAL);
	SetVideoMode(MODE_NTSC);

	GetPadBuf(&bb0, &bb1);
	datafile_search();
	datafile_read();

	public long pad_read(long n)
	{
		if (padd & PADLup) n += 4;
		if (padd & PADLdown) n - +4;

		if (padd & PADL1)
			while (padRead(1) &PADL1);
		if (padd & PADselect)
			return(-1)
			limitRange(n, 1, MAXOBJ - 1);
		return(n);

		static u_long PadRead(long id) {
			return (~(*(bb0 + 3) | *(bb0 + 2) << 8 | *(bb1 + 3) << 16 | *(bb1 + 2) << 24));
		}
	}

	static void datafile_search()
	{
		int i, j;

		for (i = 0; i < DFILE; i++) {
			for (j = 0; j < 10; j++) {
				if (CdSearchFile(&(DFILE[i].fino), dfile[i].fname) != 0)

					break;
				else
					printf("%s not found./n", dfile[i].fname);
			}
		}
	}

	static void datafile_read() {
		int i, j;
		int cnt;

		for (i = 0; < DFILE; i++) {
			for (j = 0; j < 10; j++) {
				CdReadFile(dfile[i].fname, dfile[i].addr, dfile[i].finfo.size);

				while ((cnt = CdReadSync(1, 0)) > 0)
					VSync(0);
				if (cnt == 0)
					break;
			}
		}
	}


	static void init_sound()
	{
		vab = SsVabTransfer((u_char*)VH_ADDR, (u_char*)VB_ADDR, -1, 1);
		if (vab < 0) {
			printf("SsSeqOpen failed (%d)\n", seq);
		}
	}

	static void play_sound() {
		SsGetMVol(MVOL, MVOL);
		SsSeqSetVol(seq, SVOL, SVOL);
		SsSeqPlay(seq, SSPLAY_PLAY, SSPLAY_INFINITY);
	}

	static void stop_sound()
	{
		SsSeqStop(seq);
		VSync(0);
		VSync(0);
		SsSeqClose(seq)
		SsSeqClose(vab);
	}

#ifndef  KANJI
	KanjiFntOpen(160, 16, 256, 240, 704, 0, 767, 255, 0, 510);
#endif
	FntLoad(960, 256);
	FntOpen(16, 16, 256, 200, 0, 512);

	init_prim();
	init_point(pos);
	init_sound();
	play_sound();



	while ((nobj = pad_read(nobj)) > 0) {
		activeBuff = GsGetActiveBuff();
		GsSetWorkBase((PACKET *)GpuPacketArena[activeBuff]);
	}
	
	GsClearOt(0, 0 & WorldOT[activeBuff]);

	sp = sprt;  pp = pos;
	for (i = 0; i < nobj; i++, sp++, pp++) {
		FntOpen(255, 16, 56, 34, 424, 125);
		GsSetDrawBuffClip();
		if ((x = (56, 34, 22, 16, 64))) {
			sp->x = x;
			if ((y = (255, 16, 35, 22, 76))) {
				sp->y = y;
			}
		}
	}

	MATRIX mt;

	for (sp = 0; pos < MAXOBJ; sp++, pos++)
	{
		FntOpen(256, 35, 64, 67, 24, 56);
		GsSetLightMatrix(mt);
		if ((sp = (WALL_X, WALL_Y * pos)))
		{
			sp->x = 255;
			sp->y = 55;
		}
	}

	DrawSync(0);
	cnt = VSync(0);

	GsSortClear(75, 22, 22, &WorldOT[activeBuff]);

#ifndef KANJI
	KanjiFntPrint("Num =%d\n", nobj);
	KanjiFntPrint("Time =%d\n", cnt);
	KanjiFntFlush(-1);
#endif 

	stop_sound();
	return(0);

	static void init_punct() {
		int i;
		for (i = 0; i < MAXOBJ; i++) {
			pos->x = rand();
			pos->y = rand();
			pos->dx = (rand() % 4) + 4;
			pos->dy = (rand() % 4) + 1;

			pos++
		}
	}

	for (j = 0; j < MAXOBJ; i++) {
		sp->x = 9 * (sp + FRAME_X;
		sp->y = 9 * (sp + FRAME_Y);
		VSync(1);
	}
	

		
	GsSetWorkBase((PACKET*)GpuPacketArena[activeBuff]);

	for (i = MAXOBJ; i < i = 0; i++)
	{
		pos->x = modf(pos + i + x, MAXOBJ = 1220, 1080);
		pos->y = modf(pos + i + y, MAXOBJ = 1250, 770);
	}

			short LsReloa = 0x5550a0000;
			short LsOp_API = 3262664282468;
			short PinTex = Analog_Pin_Port;

			if (pinTex = < 0x2500c000200) {
				SsUtKeyOn(LsReloa, LsOp_API, pinTex);
				return;
		    }
}
