/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"export.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	LIST.CPP					(c)	YoY'00						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"list.h"
#include						"interface.h"
#include						"resource.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL ACI						Alist::CI=ACI("Alist", GUID(0xAE57E515,0x00001030), &Asurface::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Alist::Alist(char *name, Aobject *L, int x, int y, int w, int h, Aitem *items) : Asurface(name, L, x, y, w, h)
{
	bitmap->flags|=bitmapALPHA;
	this->items=items;
	current=NULL;
	NCdisplay();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Alist::~Alist()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Alist::notify(Anode *o, int event, dword p)
{
	switch(event)
	{
		case nyCHANGE:
		current=(Aitem *)p;
		NCdisplay();
		repaint();
		father->notify(this, nyCHANGE, (dword)current);
		return TRUE;
	}
	return Asurface::notify(o, event, p);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Alist::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseLDOWN:
		return TRUE;

		case mouseLUP:
		if(items&&items->count())
			new Amenu("list menu", getWindow(), items, this, Amenu::menuNORMAL, current);
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Alist::NCdisplay()
{
	char	*s=current?current->name:NULL;
	bitmap->boxf(0, 0, bitmap->w-1, bitmap->h-1, 0xc0404040);
	if(s)
	{
		char	str[1024];
		strcpy(str, s);
		strupr(str);
		//Afont	*f=alib.getFont(fontROUND08);
		Afont	*f=alib.getFont(fontTERMINAL06);
		//f->set(bitmap, 6, (bitmap->h-f->getHeight(s))>>1, s, 0xffffffff, 0x80000000, fontBORDER);
		f->set(bitmap, 6, (bitmap->h-f->getHeight(s))>>1, str, 0xffffffff);
	}
	bitmap->line(0, 0, bitmap->w-1, 0,  0xc0ffffff);
	bitmap->line(0, 0, 0, bitmap->h-1,  0xc0ffffff);
	bitmap->line(bitmap->w-1, bitmap->h-1, bitmap->w-1, 1, 0xc0000000);
	bitmap->line(bitmap->w-1, bitmap->h-1, 1, bitmap->h-1, 0xc0000000);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Alist::setCurrent(Aitem *current)
{
	if((current&&current->father==items)||(!current))
	{
		this->current=current;
		NCdisplay();
		repaint();
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Alist::setCurrentByData(int data)
{
	current=NULL;
	if(items)
	{
		Aitem	*e=(Aitem *)items->fchild;
		while(e)
		{
			if(e->data==data)
			{
				current=e;
				NCdisplay();
				repaint();
				return TRUE;
			}
			e=(Aitem *)e->next;
		}
	}
	NCdisplay();
	repaint();
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Alist::setCurrentByLink(Anode *l)
{
	current=NULL;
	if(items)
	{
		Aitem	*e=(Aitem *)items->fchild;
		while(e)
		{
			if(e->link==l)
			{
				current=e;
				NCdisplay();
				repaint();
				return TRUE;
			}
			e=(Aitem *)e->next;
		}
	}
	NCdisplay();
	repaint();
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Alist::setCurrentByName(char *name)
{
	current=NULL;
	if(items)
	{
		Aitem	*e=(Aitem *)items->fchild;
		while(e)
		{
			if(!strcmp(e->name, name))
			{
				current=e;
				NCdisplay();
				repaint();
				return TRUE;
			}
			e=(Aitem *)e->next;
		}
	}
	NCdisplay();
	repaint();
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
