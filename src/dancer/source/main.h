/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	MAIN.H						(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_MAIN_H_
#define							_MAIN_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						<elektro.h>
#include						<GL/gl.h>
#include						<GL/glu.h>
//#include						<GL/glaux.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidDANCER						(Adancer::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern Aresource				resdll;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Adancer : public Aeffect
{
	AOBJ

								Adancer							(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Adancer						();

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual void				action							(double time, double dtime, double beat, double dbeat);
	virtual void				settings						(bool emergency);

	virtual int					priority						() { return priorityFILTER; }

	void						initGL							();

	AoglBitmap					*ob;
	int							w,h;
	GLuint						texture[1];
	float						ttime;
	class Aanimat				*animat;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AdancerFront : public AeffectFront
{
	AOBJ

								AdancerFront					(QIID qiid, char *name, Adancer *e, int h);
	virtual						~AdancerFront					();

	void						paint							(Abitmap *b);

	Abitmap						*back;
	Apaddle						*speed;
	Apaddle						*xypow;
	Apaddle						*zpow;
	Apaddle						*nbserp;
	Apaddle						*nbcube;
	ActrlButton					*ccbuf;
	ActrlButton					*czbuf;
	Aselcolor					*col0;
	Aselcolor					*col1;
	Aselect						*selbody[3];
	Aselect						*src1;
	Aselect						*src2;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AdancerBack : public AeffectBack
{
	AOBJ

								AdancerBack						(QIID qiid, char *name, Adancer *e, int h);
	virtual						~AdancerBack					();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Avideo						*out;
	Avideo						*in1;
	Avideo						*in2;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AdancerInfo : public AeffectInfo
{
	AOBJ 

								AdancerInfo						(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return EFFECT3D; }
	virtual dword				version							() { return 0x00010500; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AdancerInfo::AdancerInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" 
{
	DLLEXPORT class Aplugz *	getPlugz						();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_MAIN_H
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
