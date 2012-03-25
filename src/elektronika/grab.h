/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	GRAB.H						(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_GRAB_H_
#define							_GRAB_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidGRAB						(Agrab::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Agrab : public Aeffect
{
	AOBJ

								Agrab							(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Agrab							();

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual void				action							(double time, double dtime, double beat, double dbeat);
	virtual void				settings						(bool emergency);

	virtual int					priority						()	{ return priorityIMPORT; }

	// private
	bool						active;
	int							xs,ys;
	Abitmap						*bgrab;
	Asection					section;
	HWND						hgrab;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AgrabFront : public AeffectFront
{
	AOBJ

								AgrabFront						(QIID qiid, char *name, Agrab *e, int h);
	virtual						~AgrabFront						();

	bool						notify							(Anode *o, int event, dword p);
	void						paint							(Abitmap *b);
	virtual bool				mouse							(int x, int y, int state, int event);


	void						pulse							();

	Abitmap						*back;
	Abutton						*select;
	Abutton						*overlay;

	bool						grabWnd;
	HWND						hcur;
	Abitmap						*winbut;

	class Awinovr				*win;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AgrabBack : public AeffectBack
{
	AOBJ

								AgrabBack						(QIID qiid, char *name, Agrab *e, int h);
	virtual						~AgrabBack						();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Avideo						*out;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AgrabInfo : public AeffectInfo
{
	AOBJ 

								AgrabInfo						(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return INOUT; }
	virtual dword				version							() { return 0x00010500; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AgrabInfo::AgrabInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					grabGetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_GRAB_H
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
