/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	SELCOLOR.H					(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"elektrodef.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_SELCOLOR_H_
#define							_SELCOLOR_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"acontrol.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	If you use directly the variables in the class API, it's at your own risks. Prefer the methods...   

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidSELCOLOR					(Aselcolor::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aselcolor : public AcontrolObj
{
public:
	ELIBOBJ

	EDLL						Aselcolor						(QIID qiid, char *name, Aobject *L, int x, int y, int w=16, int h=16);
	EDLL virtual				~Aselcolor						();

	EDLL virtual bool			mouse							(int x, int y, int state, int event);
	EDLL virtual void			pulse							();
	EDLL virtual bool			keyboard						(int event, int ascii, int scan, int state);

	virtual bool				implementOsc					() { return true; }	// return true if overide Acontrol oscMessage
	EDLL virtual bool			oscMessage						(class AoscMessage *reply, class AoscMessage *query, int action); // return true if reply used

	EDLL virtual bool			sequence						(int nctrl, float value);

	EDLL virtual void			set								(dword color);
	EDLL virtual dword			get								();

	EDLL virtual void			paint							(Abitmap *b);

	Aobject						*wpal;

	dword						border;
private:
	dword						defcolor;
	bool						isdef;
	dword						color;
	dword						colorf;
	int							test;
	float						h,l,s;
	int							xx,yy;
	bool						ctrlPaint;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_SELCOLOR_H_
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
