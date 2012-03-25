/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	trans-video.H				(c)	YoY'04						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_TRANSVIDEO_H_
#define							_TRANSVIDEO_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<elektro.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidTRANSVIDEO					(Atransvideo::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Atransvideo : public Atransition
{
	AOBJ

								Atransvideo						(QIID qiid, char *name, Aobject *father, int x, int y);
	virtual						~Atransvideo					();

	virtual bool				notify							(Anode *o, int event, dword p);
	virtual void				paint							(Abitmap *b);

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual bool				action							(Abitmap *out, Abitmap *in0, Abitmap *in1, float cross, int src, float power, Abitmap *in[8]);
	virtual void				settings						(bool emergency);

	Abitmap						*sources;
	//int							cblur;
	//Abitmap						*blur[2];
	//Abitmap						*norm;
	Aselect						*mask;
	Aselect						*colormix;
	//Apaddle						*powersrc;
	//Apaddle						*powerblur;
	//Apaddle						*powernorm;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AtransvideoInfo : public AtransitionInfo
{
	AOBJ 

								AtransvideoInfo					(char *name, ACI *eci, char *ename, char *ehelp);

	virtual Atransition *		create							(QIID qiid, char *name, Aobject *father, int x, int y);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AtransvideoInfo::AtransvideoInfo(char *name, ACI *eci, char *ename, char *ehelp) : AtransitionInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					transvideoGetInfo				();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_TRANSVIDEO_H
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
