void
fibonacci(Monitor *mon, int s) {
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	
	nx = mon->wx;
	ny = 0;
	nw = mon->ww;
	nh = mon->wh;
	
	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if(i < n - 1) {
				if(i % 2)
					nh /= 2;
				else
					nw /= 2;
				if((i % 4) == 2 && !s)
					nx += nw;
				else if((i % 4) == 3 && !s)
					ny += nh;
			}
			if((i % 4) == 0) {
				if(s)
					ny += nh;
				else
					ny -= nh;
			}
			else if((i % 4) == 1)
				nx += nw;
			else if((i % 4) == 2)
				ny += nh;
			else if((i % 4) == 3) {
				if(s)
					nx += nw;
				else
					nx -= nw;
			}
			if(i == 0)
			{
				if(n != 1)
					nw = mon->ww * mon->mfact;
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw;
			i++;
		}
		//resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
        int g = gappx; /* Use mon->gappx if your patch tracks gaps per monitor */
        int gap_left   = (nx == mon->wx) ? g : (g / 2);
        int gap_top    = (ny == mon->wy) ? g : (g / 2);
        int gap_right  = ((nx + nw) == (mon->wx + mon->ww)) ? g : (g / 2);
        int gap_bottom = ((ny + nh) == (mon->wy + mon->wh)) ? g : (g / 2);

        resize(c,
               nx + gap_left,
               ny + gap_top,
               nw - gap_left - gap_right - (2 * c->bw),
               nh - gap_top - gap_bottom - (2 * c->bw),
               False);
	}
}

void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}
