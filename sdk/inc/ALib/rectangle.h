/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	RECTANGLE.H					(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_RECTANGLE_H_
#define							_RECTANGLE_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"types.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	If you use directly the variables in the class API, it's at your own risks. Prefer the methods...   

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//! a class that represent a 2d rectangle
class Arectangle
{
public:
								Arectangle						() { x=0; y=0; w=0; h=0; }
								Arectangle						(Arectangle &r);
								Arectangle						(int x, int y, int w, int h);
								Arectangle						(int x, int y);

	bool						intersect						(Arectangle &r);	//  return also true if it instersect
	void						add								(Arectangle &r);
	void						add								(int x, int y);
	void						translat						(int x, int y);
	bool						contains						(int x, int y);

	// private

	int							x;
	int							y;
	int							w;
	int							h;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline Arectangle::Arectangle(Arectangle &r)
{
	x=r.x;
	y=r.y;
	w=r.w;
	h=r.h;
}

__inline Arectangle::Arectangle(int x, int y, int w, int h)
{
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;
}

__inline Arectangle::Arectangle(int x, int y)
{
	this->x=x;
	this->y=y;
	this->w=1;
	this->h=1;
}

__inline bool Arectangle::intersect(Arectangle &r)
{
	bool	b=true;
	int		xx=maxi(r.x, x);
	int		yy=maxi(r.y, y);
	
	w=mini(r.x+r.w, x+w)-xx;
	if(w<=0)
	{
		b=false;
		w=0;
	}
	h=mini(r.y+r.h, y+h)-yy;
	if(h<=0)
	{
		b=false;
		h=0;
	}
	
	x=xx;
	y=yy;
	
	return b;
}

__inline void Arectangle::translat(int x, int y)
{
	this->x+=x;
	this->y+=y;
}

__inline void Arectangle::add(Arectangle &r)
{
	int xx=mini(r.x, x);
	int yy=mini(r.y, y);
	w=maxi(r.x+r.w, x+w)-xx;
	h=maxi(r.y+r.h, y+h)-yy;
	x=xx;
	y=yy;
}

__inline void Arectangle::add(int nx, int ny)
{
	int xx=mini(nx, x);
	int yy=mini(ny, y);
	w=maxi(nx+1, x+w)-xx;
	h=maxi(ny+1, y+h)-yy;
	x=xx;
	y=yy;
}

__inline bool Arectangle::contains(int x, int y)
{
	return (x>=this->x)&&(x<(this->x+w))&&(y>=this->y)&&(y<(this->y+h));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_RECTANGLE_H_
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
