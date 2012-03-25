/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	VOUT.H						(c)	YoY'01						WEB: www.vout.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_VOUT_H_
#define							_VOUT_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidVOUT						(Avout::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Avout : public Aeffect , public Athread
{
	AOBJ

								Avout							(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
								//Avout							(char *name, Alayer *l, class Afile *f);
	virtual						~Avout							();

	bool						notify							(Anode *o, int event, dword p);

	virtual void				settings						(bool emergency);
	bool						change							(int c);
	virtual void				run								();

	virtual void				action							(double time, double dtime, double beat, double dbeat);

	virtual bool				save							(Afile *f);
	virtual bool				load							(Afile *f);

	virtual int					priority						()	{ return priorityEXPORT; }

	Abitmap						*notregistred;
	Abitmap						*image;
	Asection					sectionImage;
	Asection					winChange;
	class Awindow				*win;
	class AdirectX				*dx;
	bool						winrun;
	bool						runout;
	int							current;
	int							error;
	int							winX;
	int							winY;
	class Agdi					*gdi;

	bool						OKI_registred;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvoutFront : public AeffectFront
{
	AOBJ

								AvoutFront						(QIID qiid, char *name, Avout *e, int h);
	virtual						~AvoutFront						();

	bool						notify							(Anode *o, int event, dword p);
	void						paint							(Abitmap *b);

	void						pulse							();

	Abitmap						*back;
	Aitem						*items;
	Alist						*list;
	Aselect						*source;
	Aselcolor					*color;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvoutBack : public AeffectBack
{
	AOBJ

								AvoutBack						(QIID qiid, char *name, Avout *e, int h);
	virtual						~AvoutBack						();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Avideo						*in[4];
	Avideo						*out;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvoutInfo : public AeffectInfo
{
	AOBJ 

								AvoutInfo						(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return INOUT; }
	virtual dword				version							() { return 0x00010500; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AvoutInfo::AvoutInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					voutGetInfo						();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_VOUT_H
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
