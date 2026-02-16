#if defined __linux__
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#elif defined _WINE
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#elif defined _WIN32
#include "F:/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "F:/home/codeleaded/System/Static/Library/TransformedView.h"
#include "F:/home/codeleaded/System/Static/Library/Random.h"
#elif defined(__APPLE__)
#error "Apple not supported!"
#else
#error "Platform not supported!"
#endif

Rect rect;
Vector points;
TransformedView tv;

float Voronoi_Get(Vector* v,Vec2 p,float field){
	//float out = 0.0f;
	float dist = INFINITY;
	Vec2 nearest = { 0.0f,0.0f };

	for (int i = 0;i<points.size;i++){
		const Vec2 pt = *(Vec2*)Vector_Get(&points,i);
		const Vec2 d = Vec2_Sub(p,pt);
		const float l = Vec2_Mag2(d);
		//const float r = l < 0.001f ? 1.0f : 1.0f / l;
		//out += r;

		if(l < dist){
			nearest = pt;
			dist = l;
		}
	}

	//return F32_Clamp(out,0.0f,1.0f);

	const float rd = (field - sqrtf(dist)) / field;
	return F32_Clamp(rd,0.0f,1.0f);
}

void Setup(AlxWindow* w){
	points = Vector_New(sizeof(Vec2));
	rect = Rect_New((Vec2){ 0.0f,0.0f },(Vec2){ 80.0f,80.0f });
    tv = TransformedView_Make(
		(Vec2){ GetWidth(),GetHeight() },
		(Vec2){ 0.0f,0.0f },
		(Vec2){ 0.1f,0.1f },
		(float)GetWidth() / (float)GetHeight()
	);

	for(int i = 0;i<35;i++){
		const float fx = Random_f64_MinMax(rect.p.x,rect.p.x + rect.d.x);
		const float fy = Random_f64_MinMax(rect.p.y,rect.p.y + rect.d.y);
		Vector_Push(&points,(Vec2[]){{ fx,fy }});
	}
}
void Update(AlxWindow* w){
	TransformedView_Output(&tv,(Vec2){ GetWidth(),GetHeight() });
	tv.AspectRatio = (float)GetWidth() / (float)GetHeight();
	
	TransformedView_HandlePanZoom(&tv,w->Strokes,GetMouse());
	const Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());

	if(Stroke(ALX_MOUSE_L).PRESSED){
		if(Rect_Point_Overlap(rect,m)){
			Vector_Push(&points,(Vec2[]){ m });
		}
	}

	Clear(BLACK);

	const Vec2 wtl = TransformedView_ScreenWorldPos(&tv,(Vec2){ 0.0f,0.0f });
	const Vec2 wbr = TransformedView_ScreenWorldPos(&tv,(Vec2){ GetWidth(),GetHeight() });

	for (int i = (int)wtl.y;i<(int)wbr.y + 1;i++){
		for (int j = (int)wtl.x;j<(int)wbr.x + 1;j++){
			const Vec2 wp = { j,i };

			const float out = Voronoi_Get(&points,wp,15.0f);
			const Pixel c = Pixel_toRGBA(out,out,out,1.0f);

			const Vec2 sp = TransformedView_WorldScreenPos(&tv,wp);
			const Vec2 sd = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });
			Rect_RenderX(WINDOW_STD_ARGS,sp,Vec2_Add(sd,(Vec2){ 1.0f,1.0f }),c);
		}
	}

	for (int i = 0;i<points.size;i++){
		const Vec2 pt = *(Vec2*)Vector_Get(&points,i);
		const Vec2 sp = TransformedView_WorldScreenPos(&tv,pt);
		const Vec2 sd = TransformedView_WorldScreenLength(&tv,(Vec2){ 0.5f,0.5f });
		Circle_R_Render(WINDOW_STD_ARGS,sp,sd,WHITE);
	}

	const Rect sr = TransformedView_WorldScreenRect(&tv,rect);
	Rect_RenderWire(WINDOW_STD_ARGS,sr,WHITE,1.0f);
}
void Delete(AlxWindow* w){
	Vector_Free(&points);
}

int main(){
    if(Create("Voronoi",1600,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}