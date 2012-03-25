/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	APLAYER.H					(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_APLAYER_H_
#define							_APLAYER_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidAPLAYER						(Aaplayer::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aaplayer : public Aeffect
{
	AOBJ

	enum
	{
								ftypeNOTHING=1,
								ftypeMP3,
								ftypeWAV
	};

								Aaplayer						(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Aaplayer						();

	virtual void				action							(double time, double dtime, double beat, double dbeat);

	virtual bool				save							(Afile *f);
	virtual bool				load							(Afile *f);

	virtual int					priority						()	{ return priorityIMPORT; }

	bool						init							();
	void						end								();

	Asection					section;
	char						filename[ALIB_PATH];
	int							ftype;

	// mp3
	class IAMPDecoder			*mp3;
	class AMPStreamInfo			*mp3si;
	class MP3source				*mp3source;

	short						audioin[8192];
	//short						buffer[44100*2];
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AaplayerFront : public AeffectFront
{
	AOBJ

								AaplayerFront					(QIID qiid, char *name, Aaplayer *e, int h);// : AeffectFront(name, e, h);
	virtual						~AaplayerFront					();

	bool						save							(Afile *f);
	bool						load							(Afile *f);

	bool						notify							(Anode *o, int event, dword p);
	void						paint							(Abitmap *b);

	void						pulse							();

	Abitmap						*back;

	Apaddle						*bass;
	Apaddle						*medium;
	Apaddle						*treble;
	Apaddle						*volume;
	Adisplay					*left;
	Adisplay					*right;
	Abutton						*file;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AaplayerBack : public AeffectBack
{
	AOBJ

								AaplayerBack					(QIID qiid, char *name, Aaplayer *e, int h);
	virtual						~AaplayerBack					();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Asample						*out;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AaplayerInfo : public AeffectInfo
{
	AOBJ 

								AaplayerInfo					(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return PLAYER; }
	virtual dword				version							() { return 0x00010500; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AaplayerInfo::AaplayerInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					aplayerGetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_APLAYER_H
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
