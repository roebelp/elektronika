/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	WEBCLIENT.H					(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_WEBCLIENT_H_
#define							_WEBCLIENT_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
#include						<windows.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidWEBCLIENT					(Awebclient::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Awebclient : public Aeffect, public Athread
{
	AOBJ

								Awebclient						(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Awebclient						();

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual void				action							(double time, double dtime, double beat, double dbeat);
	virtual void				settings						(bool emergency);

	virtual void				run								();
	bool						startClient						();
	void						stopClient						();

	virtual int					priority						()	{ return priorityIMPORT; }

	// private
	Asection					section;
	bool						webrun;
	bool						webstop;
	Abitmap						*snap320;
	char						hostname[1024];
	word						port;
	int							state;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AwebclientFront : public AeffectFront
{
	AOBJ

								AwebclientFront					(QIID qiid, char *name, Awebclient *e, int h);
	virtual						~AwebclientFront				();

	bool						notify							(Anode *o, int event, dword p);
	void						paint							(Abitmap *b);

	void						pulse							();

	Abitmap						*back;
	Aedit						*ehostname;
	Aedit						*eport;
	Abutton						*active;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AwebclientBack : public AeffectBack
{
	AOBJ

								AwebclientBack					(QIID qiid, char *name, Awebclient *e, int h);
	virtual						~AwebclientBack					();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Avideo						*out;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AwebclientInfo : public AeffectInfo
{
	AOBJ 

								AwebclientInfo					(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return INOUT; }
	virtual dword				version							() { return 0x00010500; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AwebclientInfo::AwebclientInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					webclientGetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_WEBCLIENT_H
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
