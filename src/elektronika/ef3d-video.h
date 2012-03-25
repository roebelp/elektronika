/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ef3d-video.H				(c)	YoY'03						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_EF3DVIDEO_H_
#define							_EF3DVIDEO_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidEF3DVIDEO					(Aef3dvideo::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aef3dvideo : public Ainput3d
{
	AOBJ

								Aef3dvideo						(QIID qiid, char *name, Aobject *father, int x, int y);
	virtual						~Aef3dvideo						();

	virtual bool				notify							(Anode *o, int event, dword p);
	virtual void				paint							(Abitmap *b);

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual void				settings						(bool emergency);
	
	virtual bool				init3D							(class Aef3dInfo *info);
	virtual bool				release3D						(class Aef3dInfo *info);
	
	virtual bool				action							(class Aef3dInfo *info);

	virtual IDirect3DTexture9*	getTexture						(int *type, float *cx, float *cy);

	class Adatavideo			*dt;
	class Aselect				*sel;
	class Aselcolor				*ckey;
	class Apaddle				*pkey;
	class Aselcolor				*ctint;
	class Apaddle				*ptint;
	Abitmap						*back;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aef3dvideoInfo : public Ainput3dInfo
{
	AOBJ 

								Aef3dvideoInfo					(char *name, ACI *eci, char *ename, char *ehelp);

	virtual Ainput3d *			create							(QIID qiid, char *name, Aobject *father, int x, int y);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline Aef3dvideoInfo::Aef3dvideoInfo(char *name, ACI *eci, char *ename, char *ehelp) : Ainput3dInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					ef3dvideoGetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_EF3DVIDEO_H
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
