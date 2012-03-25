/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	CTRLBUTTON.H				(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"elektrodef.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_CTRLBUTTON_H_
#define							_CTRLBUTTON_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"acontrol.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	If you use directly the variables in the class API, it's at your own risks. Prefer the methods...   

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidCTRLBUTTON					(ActrlButton::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ActrlButton : public AcontrolObj
{
public:
	ELIBOBJ

	EDLL 						ActrlButton						(QIID qiid, char *name, Aobject *L, int x, int y, int w, int h, Aresobj *o, int type=Abutton::btBITMAP);
	EDLL 						ActrlButton						(QIID qiid, char *name, Aobject *L, int x, int y, int w, int h, Abitmap *b, int type=Abutton::btBITMAP);
	EDLL virtual				~ActrlButton					();

	EDLL virtual void			pulse							();
	EDLL virtual void			paint							(Abitmap *b);
	EDLL virtual bool			notify							(Anode *o, int event, dword p);

	void						change							(Abitmap *b)	{ button->change(b); }

	EDLL virtual bool			sequence						(int nctrl, float value);

	EDLL bool					get								();
	EDLL void					set								(bool value);

	Abutton						*button;
	bool						ctrlPaint;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_CTRLBUTTON_H_
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
