/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	VMIX.H						(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_VMIX_H_
#define							_VMIX_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidVMIX						(Avmix::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Avmix : public Aeffect
{
	AOBJ

								Avmix							(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Avmix							();

	virtual bool				save							(class Afile *f);
	virtual bool				load							(class Afile *f);

	virtual bool				savePreset						(class Afile *f);
	virtual bool				loadPreset						(class Afile *f);

	virtual void				action							(double time, double dtime, double beat, double dbeat);
	virtual void				settings						(bool emergency);

	virtual int					priority						()	{ return priorityEXPORT-128; }

	// private

	void						audioProcess					(double dtime, float mix);

	float						m_cross;
	float						mixette;
	Asection					section;
	Abitmap						*image[2];
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvmixFront : public AeffectFront
{
	AOBJ

								AvmixFront						(QIID qiid, char *name, Avmix *e, int h);
	virtual						~AvmixFront						();

	bool						notify							(Anode *o, int event, dword p);
	void						paint							(Abitmap *b);

	void						pulse							();

	Abitmap						*back;
	Aselect						*lsource;
	Aselect						*rsource;
	Alist						*trans[4];
	Aitem						*itrans;
	Aselect						*automix;
	Aselpad						*autospeed;
	ActrlButton					*autoswitch;
	Aselect						*seltrans;
	Atransition					*tr[4];
	Atransition					*active;
	Aslider						*cross;
	ActrlButton					*lpush;
	ActrlButton					*rpush;
	ActrlButton					*lauto;
	ActrlButton					*rauto;
	ActrlButton					*absrc;
	Apaddle						*epow;
	Apaddle						*ret[2];

	double						beatauto;
	int							dirauto;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvmixBack : public AeffectBack
{
	AOBJ

								AvmixBack						(QIID qiid, char *name, Avmix *e, int h);
	virtual						~AvmixBack						();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Asample						*ain[8];
	Avideo						*in[8];
	Avideo						*out;
	Avideo						*outleft;
	Avideo						*outright;
	Avideo						*inleft;
	Avideo						*inright;
	Asample						*aout;
	Asample						*audio;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvmixInfo : public AeffectInfo
{
	AOBJ 

								AvmixInfo						(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return MIXER; }
	virtual dword				version							() { return 0x00019930; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AvmixInfo::AvmixInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					vmixGetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_VMIX_H
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
