/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	MAIN.CPP					(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"main.h"
#include						"resource.h"
#include						<math.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// elektronika SDK effect sample
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// if you want to use MFC/AFX
// add the MFC/AFX includes
// select "MFC  shared dll" in general tab of the project settings
// and remove the _USRDLL define in the project settings
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ACI								AexampleInfo::CI	= ACI("AexampleInfo",	GUID(0x50000000,0x00000020), &AeffectInfo::CI, 0, NULL);
ACI								Aexample::CI		= ACI("Aexample",		GUID(0x50000000,0x00000021), &Aeffect::CI, 0, NULL);
ACI								AexampleFront::CI	= ACI("AexampleFront",	GUID(0x50000000,0x00000022), &AeffectFront::CI, 0, NULL);
ACI								AexampleBack::CI	= ACI("AexampleBack",	GUID(0x50000000,0x00000023), &AeffectBack::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int						count=0;
static Aresource				resdll=Aresource("example01", GetModuleHandle("example01.dll"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void init()
{
	if(count==0)
	{
		// make globals inits as somes tables
	}
	count++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void end()
{
	count--;
	if(count==0)
	{
		// free globals inits
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aexample::Aexample(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule) : Aeffect(qiid, name, info, capsule)
{
	front=new AexampleFront(qiid, "example front", this, 50);
	front->setTooltips("example");
	back=new AexampleBack(qiid, "example back", this, 50);
	back->setTooltips("example");
	init();	// global init
	settings(false);
//	you can get table->videoW or table->videoH 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aexample::~Aexample()
{
	end();	// global free
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Aexample::save(class Afile *f)
{
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aexample::settings(bool emergency)
{
//	table->videoW or table->videoH have been changed
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aexample::setBox(Abitmap *b,int x, int y, sword *s, int n, dword color, float l)
{
	if(n)
	{
		int		d=y<<1;
		int		i;
		float	a=0.2f;
		int		v=0;
		for(i=0; i<n; i++)
		{
			int	i0=i<<1;
			int	i1=i0+1;
			v=maxi(v, (int)((float)s[i0]*(float)d*l)>>15);
			v=maxi(v, (int)((float)s[i1]*(float)d*l)>>15);
		}
		b->boxfa(x-v, y-v, x+v, y+v, color, a, lineaADD|lineaSATURATION);
	}
}

void Aexample::action(double time, double dtime, double beat, double dbeat)
{
	int				w=getVideoWidth();
	int				h=getVideoHeight();
	float			l=((AexampleFront *)front)->level->get();
	dword			cl=((AexampleFront *)front)->color0->get();
	dword			cc=((AexampleFront *)front)->color1->get();
	dword			cr=((AexampleFront *)front)->color2->get();
	Asample			*snd=((AexampleBack *)back)->in;
	Avideo			*vin=((AexampleBack *)back)->vin;
	Avideo			*out=((AexampleBack *)back)->out;
	sword			smp[64*2];
	sword			bas[64*2];
	sword			med[64*2];
	sword			tre[64*2];
	int				nget=0;

	l=(l<0.5f)?(l*2.f):((l-0.5f)*10.f+1.f);

	if(snd->isConnected())
	{
		snd->enter(__FILE__,__LINE__);
		snd->skip(maxi(snd->avaible()-64, 0));
		nget=snd->getBuffer(smp, bas, med, tre, 64);
		snd->leave();
	}

	out->enter(__FILE__,__LINE__);
	vin->enter(__FILE__,__LINE__);
	{
		Abitmap *b=out->getBitmap();
		Abitmap	*bin=vin->getBitmap();
		if(b)
		{
			int		nx=b->w>>2;
			int		ny=b->h>>1;
			int		v=0;
			if(bin)
			{
				bin->flags|=bitmapGLOBALALPHA;
				bin->alpha=0.05f;
				b->set(0, 0, bin, bitmapDEFAULT, bitmapDEFAULT);
			}
			else
				b->boxfa(0, 0, b->w, b->h, 0xff000000, 0.05f);
			setBox(b, v+=nx, ny, bas, nget, cl, l);
			setBox(b, v+=nx, ny, med, nget, cc, l);
			setBox(b, v+=nx, ny, tre, nget, cr, l);
		}
	}
	vin->leave();
	out->leave();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AexampleFront::paint(Abitmap *b)
{
	b->set(0, 0, back, bitmapDEFAULT, bitmapDEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AexampleFront::AexampleFront(QIID qiid, char *name, Aexample *e, int h) : AeffectFront(qiid, name, e, h)
{
	setTooltips("example");
	Aresobj	o=resdll.get(MAKEINTRESOURCE(PNG_MOONSTER_FRONT), "PNG");
	back=new Abitmap(&o);

	level=new Apaddle(MKQIID(qiid,0x90208F25F34D5325), "level", this, 20, 10, paddleBUTTON07);
	level->setTooltips("level");
	level->set(0.5f);
	level->show(TRUE);

	color0=new Aselcolor(MKQIID(qiid,0x00ecf002981258c0), "left color", this, 50, 16);
	color0->setTooltips("left color");
	color0->set(0xffff0080);
	color0->show(true);

	color1=new Aselcolor(MKQIID(qiid,0x39b9697df43647dc), "center color", this, 70, 16);
	color1->setTooltips("center color");
	color1->set(0xff80ff00);
	color1->show(true);

	color2=new Aselcolor(MKQIID(qiid,0xf5d68e5e5faf95c0), "right color", this, 90, 16);
	color2->setTooltips("right color");
	color2->set(0xff0080ff);
	color2->show(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AexampleFront::~AexampleFront()
{
	delete(back);
	delete(level);
	delete(color0);
	delete(color1);
	delete(color2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AexampleFront::notify(Anode *o, int event, dword p)
{
	switch(event)
	{
		case nyCHANGE:
		break;
	}
	return AeffectFront::notify(o, event, p);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AexampleBack::AexampleBack(QIID qiid, char *name, Aexample *e, int h) : AeffectBack(qiid, name, e, h)
{
	Aresobj	o=resdll.get(MAKEINTRESOURCE(PNG_MOONSTER_BACK), "PNG");
	back=new Abitmap(&o);

	in=new Asample(MKQIID(qiid, 0x5e0ae4008ec372bd), "audio input", this, pinIN, 10, 10);
	in->setTooltips("audio input");
	in->show(TRUE);

	vin=new Avideo(MKQIID(qiid, 0xa9ae7a306da63fb4), "video input", this, pinIN, 30, 10);
	vin->setTooltips("video input");
	vin->show(TRUE);

	out=new Avideo(MKQIID(qiid, 0x7c102324cbb0f380), "video output", this, pinOUT, pos.w-18, 10);
	out->setTooltips("video output");
	out->show(TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AexampleBack::~AexampleBack()
{
	delete(in);
	delete(vin);
	delete(out);
	delete(back);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AexampleBack::paint(Abitmap *b)
{
	b->set(0, 0, back, bitmapDEFAULT, bitmapDEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AexampleInfo::~AexampleInfo()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Aeffect * AexampleInfo::create(QIID qiid, char *name, Acapsule *capsule)
{
	return new Aexample(qiid, name, this, capsule);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" 
{
	DLLEXPORT class Aplugz * getPlugz()
	{
		return new AexampleInfo("example 01", &Aexample::CI, "SDK example 01", "SDK example 01");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////