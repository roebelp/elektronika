/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	trans-morph.H				(c)	YoY'04						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_TRANSMORPH_H_
#define							_TRANSMORPH_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<elektro.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidTRANSMORPH					(Atransmorph::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Atransmorph : public Atransition
{
	AOBJ

								Atransmorph						(QIID qiid, char *name, Aobject *father, int x, int y);
	virtual						~Atransmorph					();

	virtual bool				notify							(Anode *o, int event, dword p);
	virtual void				paint							(Abitmap *b);
	virtual bool				mouse							(int x, int y, int state, int event);

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual bool				action							(Abitmap *out, Abitmap *in0, Abitmap *in1, float cross, int src, float power, Abitmap *in[8]);
	virtual void				settings						();
	
	virtual void				change							();

	Asection					section;
	Abitmap						*sources;
	Abitmap						*bmp[16];
	bool						bChange;
	Alist						*list;
	Aitem						*items;
	ActrlButton					*flipx;
	ActrlButton					*flipy;
	class Asnap2				*snap;
	int							nwipe;
	Abitmap						*wipe;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AtransmorphInfo : public AtransitionInfo
{
	AOBJ 

								AtransmorphInfo					(char *name, ACI *eci, char *ename, char *ehelp);

	virtual Atransition *		create							(QIID qiid, char *name, Aobject *father, int x, int y);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AtransmorphInfo::AtransmorphInfo(char *name, ACI *eci, char *ename, char *ehelp) : AtransitionInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					transmorphGetInfo				();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_TRANSMORPH_H
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
