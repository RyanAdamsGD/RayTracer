#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#define EQN_EPS     1e-30
#define IS_ZERO(x)	((x) > -EQN_EPS && (x) < EQN_EPS)
#ifndef CBRT
#define     cbrt(x)  ((x) > 0.0f ? pow((float)(x), 1.0f/3.0f) : \
			  		 ((x) < 0.0f ? -pow((float)-(x), 1.0f/3.0f) : 0.0f))
#endif

float rand_float(float min = 0.0f, float max = 1.0f);
float rand_double(float min, float max);

inline float min(float x, float y)
{ return ((x > y) ? y : x); }

inline float max(float x, float y)
{ return ((x > y) ? x : y); }

inline float clamp(float x, float min, float max)
{ return x>max?max:(x<min?min:x); }

template<class T>
T lerp(float x,const T& a,const T& b)
{ return a + (b-a) * x; }

template<class T>
T fourKnotSpline(float x, const T* knots)
{
	T c3 = -0.5f * knots[0] + 1.5f * knots[1] - 1.5f * knots[2] + 0.5f * knots[3];
	T c2 = knots[0] - 2.5f * knots[1] + 2.0f * knots[2] - 0.5f * knots[3];
	T c1 = 0.5f * (-knots[0] + knots[2]);
	T c0 = knots[1];

	return ((c3 * x + c2) * x + c1) * x + c0;
}

float mod(float a, float b);

float smoothPulseTrain(float e0, float e1, float e2, float e3, float period, float x);

float smoothPulse(float e0,float e1,float e2,float e3,float x); 

float smoothStep(float a,float b,float x);

int solveQuadric(float c[3], float s[2]);

int solveCubic(float c[4], float s[3]);

int solveQuartic(float c[5], float s[4]);

#endif
