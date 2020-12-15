#pragma once

typedef struct tagVertex_Color
{
	vec3 vPos;
	vec3 vColor;
}VTXCOL;

typedef struct tagVertex_Normal
{
	vec3 vPos;
	vec3 vColor;
	vec3 vNormal;
}VTXNORMAL;

typedef struct tagVertex_UV
{
	vec3 vPos;
	vec3 vColor;
	vec2 vTexUV;
}VTXUV;

typedef struct tagCamera_Desc
{
	vec3		vEye; // 카메라의 위치.In.WorldSpace
	vec3		vAt; // 카메라가 바라보는 점.
	vec3		vAxisY; // 내 좌표계상에서의 y축벡터의 방향.
}CAMERADESC;

typedef struct tagProjection_Desc
{
	float		fFovY; // 내 카메라의 시야 범위.
	float		fAspect; // 내 윈도우의 가로, 세로 비율.
	float		fNear;
	float		fFar;
}PROJDESC;

typedef struct tagTextureSet
{
	int iWidth;
	int iHeight;
	int iChannel;
	unsigned char* pData;
}TEXTURESET;

typedef struct tagPolygon16
{
	unsigned short		_0, _1, _2;
}POLYGON16;

typedef struct tagPolygon32
{
	unsigned long		_0, _1, _2;
}POLYGON32;