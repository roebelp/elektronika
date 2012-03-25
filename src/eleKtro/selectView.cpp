/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"elektroexp.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	SELECTVIEW.CPP				(c)	YoY'06						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"selectView.h"
#include						"interface.h"
#include						"resource.h"
#include						"effect.h"
#include						"elektro.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void stretchBitmap(dword *dbits, int dw0, int dh0, dword *sbits, int sw0, int sh0)
{
	int xs=0;
	int ys=0;
	int ws=sw0;
	int hs=sh0;
	int xd=0;
	int yd=0;
	int wd=dw0;
	int hd=dh0;
	int	w=wd;
	int h=hd;

	xs<<=16;
	ys<<=16;
	ws<<=16;
	hs<<=16;

	int	dw=ws/wd;
	int	dh=hs/hd;

	int		ww=mini(ws/dw, w);
	int		hh=mini(hs/dh, h);

	{
		int		j;
		dword	y=ys;
		for(j=0; j<hh; j++)
		{
			dword	*s=sbits+(y>>16)*sw0;
			dword	*d=dbits+(yd+j)*dw0+xd;
			int		i;
			dword	x=xs;
			for(i=0; i<ww; i++)
			{
				*(d++)=s[x>>16];
				x+=dw;
			}
			y+=dh;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AselViewButton : public Aobject
{
public:
	ELIBOBJ
								AselViewButton					(char *name, Aobject *l, int x, int y, int w, int h, int id);
	virtual						~AselViewButton					();

	virtual void				paint							(Abitmap *b);
	virtual bool				mouse							(int x, int y, int state, int event);
	virtual bool				dragdrop						(int x, int y, int state, int event, void *data=NULL);

	void						set								(Abitmap *b);
	void						set								(dword *bits, int width, int height);

	int							id;
	bool						press;
	Abitmap						*image;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AselViewButton::AselViewButton(char *name, Aobject *l, int x, int y, int w, int h, int id) : Aobject(name, l, x, y, w, h)
{
	this->id=id;
	press=false;
	image=new Abitmap(w, h);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AselViewButton::~AselViewButton()
{
	delete(image);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AselViewButton::paint(Abitmap *b)
{
	b->set(0, 0, image, bitmapNORMAL, bitmapNORMAL);
	if(press)
	{
		b->box(0, 0, pos.w-1, pos.h-1, 0xFFFFFFFF);
		b->box(1, 1, pos.w-2, pos.h-2, 0xFFFFFFFF);
		b->box(2, 2, pos.w-3, pos.h-3, 0xFF000000);
		b->box(3, 3, pos.w-4, pos.h-4, 0xFF000000);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AselViewButton::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseLDOWN:
		cursor(cursorHANDSEL);
		mouseCapture(true);
		focus(this);
		father->notify(this, nyPRESS, id);
		return true;

		case mouseMOVE:
		cursor(cursorHANDSEL);
		return true;

		case mouseLUP:
		mouseCapture(false);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AselViewButton::dragdrop(int x, int y, int state, int event, void *data)
{
	switch(event)
	{
		case dragdropENTER:
		case dragdropOVER:
		if(state&dragdropFILE)	
			return true;
		break;
		
		case dragdropDROP:
		if(state&dragdropFILE)
			return father->notify(this, nyCHANGE, (dword)data);
		break;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AselViewButton::set(Abitmap *b)
{
	image->set(0, 0, image->w, image->h, 0, 0, b->w, b->h, b, bitmapNORMAL, bitmapNORMAL);
	repaint();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AselViewButton::set(dword *bits, int width, int height)
{
	stretchBitmap(image->body32, image->w, image->h, bits, width, height);
	repaint();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ACI						AselectView::CI=ACI("AselectView", GUID(0xE4EC7600,0x00010150), &AcontrolObj::CI, 0, NULL);
EDLL ACI						AselViewButton::CI=ACI("AselViewButton", GUID(0xE4EC7600,0x00010155), &Aobject::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL AselectView::AselectView(QIID qiid, char *name, Aobject *L, int x, int y, int w, int h, int nx, int ny, int ow, int oh) : AcontrolObj(name, L, x, y, w, h)
{
	Aeffect	*ef=Aeffect::getEffect(L);
	nb=nx*ny;
	if(ef)
		control=new Acontrol(qiid, name, ef, this, Acontrol::KEY_01+(nb)-1);
	else
		control=new Acontrol(qiid, name, Atable::getTable(this), this, Acontrol::KEY_01+(nb)-1);
	{
		int ww=(w-(ow*nx))/(nx+1);
		int hh=(h-(oh*ny))/(ny+1);
		int	id=0;
		int y;
		for(y=0; y<ny; y++)
		{
			int yy=y*(oh+hh)+hh;
			for(x=0; x<nx; x++)
			{
				int					xx=x*(ow+ww)+ww;
				AselViewButton	*v=new AselViewButton("view", this, xx, yy, ow, oh, id);
				v->show(true);
				id++;
			}
		}
	}
	vw=ow;
	vh=oh;
	set(0);
	select();
	defvalue=-1;
	ctrlPaint=false;
	timer(CTRLTIMEREPAINT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL AselectView::~AselectView()
{
	delete(control);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool AselectView::notify(Anode *o, int event, dword p)
{
	switch(event)
	{
		case nyPRESS:
		value=p;
		control->select();
		control->set(Acontrol::KEY_01, (float)value);
		father->notify(this, nyCHANGE, (dword)&AselViewChange(p));
		select();
		repaint();
		return true;

		case nyCHANGE:
		if(o->isCI(&AselViewButton::CI))
		{
			AselViewButton *but=(AselViewButton *)o;
			int				id=but->id;
			int				n=id;
			char			*s=(char *)p;
			while(*s)
			{
				father->notify(this, nyCHANGE, (dword)&AselViewChange(n, s));
				s+=strlen(s)+1;
				n=(n+1)%nb;
				if(n==id)
					break;
			}
		}
		return true;
	}
	return AcontrolObj::notify(o, event, p);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool AselectView::keyboard(int event, int ascii, int scan, int state)
{
	switch(event)
	{
		case keyboardDOWN:
		if(state&keyboardALT)
		{
			if(defvalue!=-1)
				set(defvalue);
			else
				set(0);
			father->notify(this, nyCHANGE, (dword)&AselViewChange(value));
			return true;
		}
		break;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void AselectView::set(int n)
{
	value=n%nb;
	if(defvalue==-1)
		defvalue=value;
	control->set(Acontrol::KEY_01, (float)value);
	select();
	repaint();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL int AselectView::get()
{
	return value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool AselectView::sequence(int nctrl, float v)
{
	int ovalue=value;
	value=(int)v;
	if(ovalue!=value)
	{
		father->notify(this, nyCHANGE, (dword)&AselViewChange(value));
		select();
		ctrlPaint=true;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void AselectView::pulse()
{
	if(ctrlPaint)
	{
		repaint();
		ctrlPaint=false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void AselectView::paint(Abitmap *bitmap)
{
	//bitmap->boxfa(0, 0, pos.w, pos.h, 0x80FFFFFF);
	controlPaint(bitmap, pos.w, pos.h);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void AselectView::change(int n, Abitmap *b)
{
	AselViewButton *o=(AselViewButton *)this->fchild;
	while(o)
	{
		if(o->id==n)
		{
			o->set(b);
			break;
		}
		o=(AselViewButton *)o->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void AselectView::change(int n, dword *bits, int with, int height)
{
	AselViewButton *o=(AselViewButton *)this->fchild;
	while(o)
	{
		if(o->id==n)
		{
			o->set(bits, with, height);
			break;
		}
		o=(AselViewButton *)o->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AselectView::select()
{
	AselViewButton *o=(AselViewButton *)this->fchild;
	while(o)
	{
		o->press=(o->id==value);
		o=(AselViewButton *)o->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

