WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once
class Display_3
{
public:
	Display_3(void);
	~Display_3(void);
	void Draw(int *viewing);
	void transform3D(double r11, double r12, double r13, double tx,
		double r21, double r22, double r23, double ty,
		double r31, double r32, double r33, double tz,
		double x, double y, double z, double * x1, double * y1, double * z1);
};

