/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ef3f-cube.CPP				(c)	YoY'05						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"ef3d-cube.h"
#include						"resource.h"
#include						<math.h>
#include						<d3d9.h>
#include						<D3dx9mesh.h>
#include						<assert.h>
#include						"ef3d-node.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ACI								Aef3dcubeInfo::CI	= ACI("Aef3dcubeInfo",	GUID(0x11111112,0xB0000140), &Aeffect3dInfo::CI, 0, NULL);
ACI								Aef3dcube::CI		= ACI("Aef3dcube",		GUID(0x11111112,0xB0000141), &Aeffect3d::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Adatacube
{
public:
	float						azoom;
	class Ad3dCube				*cube;
	
	Adatacube()
	{
		azoom=0.f;
		cube=null;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int						count=0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void init()
{
	count++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void end()
{
	count--;
	if(count==0)
	{
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char *efn[]=
{
	"cube number",
	"snake lenght",
	"xy amplitude",
	"z amplitude",
};


static QIID qiidef[]={ 0x898454d6e5a7a828, 0x891512ea212970c0, 0x08aa4d8d4e33ec7a, 0x877aa845d521e000 };

Aef3dcube::Aef3dcube(QIID qiid, char *name, Aobject *f, int x, int y) : Aeffect3d(qiid, name, f, x, y)
{
	char	str[1024];
	Aresobj	o=resource.get(MAKEINTRESOURCE(PNG_EF3DCUBE), "PNG");
	back=new Abitmap(&o);

	setTooltips("cube effect");
	
	init();
	dt=new Adatacube();
	dt->cube=new Ad3dCube("cube");
	dt->cube->size=2.f;
	
	sprintf(str, "%s/zoom", name);
	zoom=new Apaddle(MKQIID(qiid,0x240ac205d619ee10), str, this, 64, 16, paddleYOLI16);
	zoom->setTooltips("zoom");
	zoom->set(0.5f);
	zoom->show(TRUE);

	sprintf(str, "%s/amplitude", name);
	mastef=new Apaddle(MKQIID(qiid,0x04ac213374106d9e), str, this, 16+44, 41, paddleYOLI24);
	mastef->setTooltips("amplitude");
	mastef->set(0.5f);
	mastef->show(TRUE);

	{
		int	i;
		for(i=0; i<4; i++)
		{
			int	y=(i<4)?34:58;
			int	n=i&3;
			sprintf(str, "%s/%s", name, efn[i]);
			ef[i]=new Apaddle(MKQIID(qiid,qiidef[i]), str, this, 16+n*24+((n>>1)*24), y, paddleYOLI16);
			ef[i]->setTooltips(efn[i]);
			ef[i]->set(0.f);
			ef[i]->show(TRUE);
		}
	}

	sym=new Aselect(MKQIID(qiid, 0x5698545e54dffa75), "sym", this, pos.w-73, 34, 3, 1, &resource.get(MAKEINTRESOURCE(PNG_EF3DCUBE_SYM), "PNG"), 14, 14);
	sym->setTooltips("symmetry");
	sym->show(true);

	settings(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aef3dcube::~Aef3dcube()
{
	int	i;
	for(i=0; i<4; i++)
		delete(ef[i]);
	delete(mastef);
	delete(zoom);
	delete(sym);
	delete(dt->cube);
	delete(dt);
	delete(back);
	end();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Aef3dcube::notify(Anode *o, int event, dword p)
{
	return Aobject::notify(o, event, p);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aef3dcube::paint(Abitmap *b)
{
	b->set(0, 0, back, bitmapDEFAULT, bitmapDEFAULT);
	//b->boxfa(0, 0, pos.w, pos.h, 0xff000000, 0.1f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Aef3dcube::save(class Afile *f)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Aef3dcube::load(class Afile *f)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aef3dcube::settings(bool emergency)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Aef3dcube::init3D(class Aef3dInfo *info)
{
	ttime=0.f;
	return dt->cube->initAll(info->d3d->d3dev);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Aef3dcube::release3D(class Aef3dInfo *info)
{
	dt->cube->releaseAll();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Aef3dcube::action(Aef3dInfo *info)
{
	Aeffect				*e=Aeffect::getEffect(this);
	Ad3d				*d3d=info->d3d;
	HRESULT				r;
	int					texType;
	float				texCx,texCy;
	byte				rc,gc,bc;
	dword				color;
	IDirect3DTexture9	*tex=info->input->getTexture(&texType, &texCx, &texCy);

	if(!tex)
		return false;

	colorRGB(&rc,&gc, &bc, info->color);
	color=D3DCOLOR_RGBA(rc, gc, bc, (int)(info->power*255.99f));
	
	d3d->d3dev->BeginScene();

	dt->cube->setTexture(tex, texCx, texCy);
	tex->Release();
	
	
	r=d3d->d3dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	r=d3d->d3dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	
	r=d3d->d3dev->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU);

	r=d3d->d3dev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	r=d3d->d3dev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	r=d3d->d3dev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	r=d3d->d3dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	r=d3d->d3dev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	
	if(info->colorBoost)
		r=d3d->d3dev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
	else
		r=d3d->d3dev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	r=d3d->d3dev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	
	switch(info->bm)
	{
		case Aef3dInfo::blendFADE:	// normal
		r=d3d->d3dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		r=d3d->d3dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		r=d3d->d3dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		break;
		
		case Aef3dInfo::blendADD:	// add
		r=d3d->d3dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		r=d3d->d3dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		r=d3d->d3dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		break;

		case Aef3dInfo::blendSUB:	// sub
		r=d3d->d3dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		r=d3d->d3dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		r=d3d->d3dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		break;
	}
	
	d3d->d3dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        

	{	// matrix
		D3DXMATRIX	matWorld;
		D3DXMATRIX	matView;
		D3DXMATRIX	matProj;
	
		d3d->d3dev->BeginScene();

		D3DXMatrixIdentity(&matWorld);
		d3d->d3dev->SetTransform(D3DTS_WORLD, &matWorld);
	
		// view matrix	// +((dt->azoom=dt->azoom*0.5f+zoom->get()*0.5f)-0.5f)*50.f	
		D3DXMatrixLookAtLH( &matView,	&D3DXVECTOR3( 0.0f, 0.0f, -30.f ),
										&D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
										&D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
									
		d3d->d3dev->SetTransform(D3DTS_VIEW, &matView);
	
		// projection matrix
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
		d3d->d3dev->SetTransform(D3DTS_PROJECTION, &matProj);
	}	

	// light
	{
		D3DXVECTOR3 vecDir;
		D3DLIGHT9	light;
		ZeroMemory(&light, sizeof(light));
		light.Type = D3DLIGHT_DIRECTIONAL;

		light.Diffuse.r = 1.0f;
		light.Diffuse.g = 1.0f;
		light.Diffuse.b = 1.0f;
		
		vecDir=D3DXVECTOR3(1.f, 1.f, 1.f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

		light.Range = 1000.0f;

		d3d->d3dev->SetLight(0, &light);
		d3d->d3dev->LightEnable(0, TRUE);
	}

	d3d->d3dev->SetRenderState(D3DRS_LIGHTING, TRUE);
	//d3d->d3dev->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3d->d3dev->SetRenderState(D3DRS_AMBIENT, 0xff202020);

	d3d->d3dev->SetRenderState(D3DRS_ZENABLE, TRUE);

	float	speed=(mastef->get()-0.5f)*4.f+0.1f;
	float	xypow=ef[2]->get()*3.f;
	float	zpow=ef[3]->get();

	ttime+=(float)(info->dbeat*(speed*5.f+0.1f)*100.f);
	
	{
		static float	dx[]={1.f, -1.f, 1.f, -1.f};
		static float	dy[]={1.f, -1.f, -1.f, 1.f};
		static float	dz[]={1.f, 1.f, -1.f, -1.f};
		D3DXMATRIX		matTemp1;
		D3DXMATRIX		matTemp2;
		D3DXMATRIX		matTemp3;
		D3DXMATRIX		matTemp4;
		int				mirror=sym->get()+1;
		int				nbserp=(int)(ef[1]->get()*30.f)+1;
		int				nbcube=(int)(ef[0]->get()*9.f)+1;
		int				k;

		if(mirror==3)
			mirror=4;

		for(k=0; k<mirror; k++)
		{
			int	j;
			for(j=0; j<nbserp; j++)
			{
				double	v=ttime+(double)j*PI*20.f;
				int		i;

				for(i=0; i<nbcube; i++)
				{
					float	rtri=(float)(v-i*50000.0)/10.f+51.5616508515f;
					float	rquad=-(float)(v-i*40000.0)/10.5f+815.51515511f;
					float	toto=(float)(v-i*50000.0)/10.84451515f+51.515774742f;

					D3DXMatrixRotationX(&matTemp1, (rtri*1.6221f*dx[k])*0.01f);
					D3DXMatrixRotationY(&matTemp2, rtri*dy[k]*0.01f);
					D3DXMatrixRotationZ(&matTemp3, rquad*dx[k]*0.01f);
					D3DXMatrixMultiply(&matTemp4, &matTemp1, &matTemp2);
					D3DXMatrixMultiply(&dt->cube->matrice, &matTemp4, &matTemp3);

					dt->cube->matrice._41=(float)sin(rtri*0.0144f)*(float)sin(toto*0.0144f)*5.f*dx[k]*(xypow+0.01f);
					dt->cube->matrice._42=(float)sin(rtri*0.0195451f)*(float)sin(toto*0.0195451f)*5.f*dy[k]*(xypow+0.01f);
					dt->cube->matrice._43=30.f+(0.5f-zoom->get())*100.f+(float)sin(rtri*0.01f)*(float)sin(toto*0.01f)*40.f*(zpow+0.01f);

					dt->cube->renderAll(info->beat, color);
				}
			}
		}
	}

	d3d->d3dev->SetRenderState(D3DRS_ZENABLE, FALSE);
	d3d->d3dev->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3d->d3dev->LightEnable(0, FALSE);
	d3d->d3dev->EndScene();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Aef3dcube::fillSurface()
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aeffect3d * Aef3dcubeInfo::create(QIID qiid, char *name, Aobject *father, int x, int y)
{
	return new Aef3dcube(qiid, name, father, x, y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz * ef3dcubeGetInfo()
{
	return new Aef3dcubeInfo("cube", &Aef3dcube::CI, "cube", "cube");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
