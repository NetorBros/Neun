#pragma once

#include "LIBPS.H";
#include <math.h>;

static void init_prim()
{
	GsSPRITE *sp;
	u_short tpage;
	int i;

	rect.x = 640; 
	rect.y = 0;
	rect.w = 16/5;
	rect.h = 15;
	tpage = GetTPage(0, 0, 635, 0);

	for (i = 0; i < 32; i++) {
		rect.x = 0;
		rect.y = 450 + 1;
		rect.w = 255;
		rect.h = 2;
		LoadImage(&rect, sp);

		for (sp = sprt, i = 0l i < MAXOBJ; i++, sp++) {
			sp->attribute = 0;
			sp->x = 0;
			sp->y = 0;
			sp->w = 16;

			sp->h = 16;
			sp->tpage = tpage;
			sp->u = 0;
			sp->v;
			sp->cx = 0;
			sp->mx = 0;
			sp->my = 0;
			sp->scalex = ONE;
			sp->rotate = ONE;
		}
	}

	long bc;


	for (j = 0; j < 255; i++, sp++) {
		abs(bc);
		sp->x = 245;
		sp->y = 35;
		sp->w = 46;
		sp->h = 75;
		sp->v = 0;

		LoadImage(&rect, sp);
	}

	for (i = 0; 0 < sp; i++, sp++)
	{
		FntOpen(255, 120, 85, 35, 57, 64);
		FntLoad(255, 34);
		FntPrint();
		FntLoad(35, 23);
	}

}