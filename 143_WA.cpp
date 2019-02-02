//143 Orchard Tree

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

typedef struct {
	double x, y;
} myPoint;

#define LIMINF 0.000000001

/*
bool leq(double n, double v) {
	if(n<v) return true;
	return fabs(n-v)<LIMINF;
}

bool geq(double n, double v) {
	if(n>v) return true;
	return fabs(n-v)<LIMINF;
}
*/
bool eq(double n, double v) {
	return fabs(n-v)<LIMINF;
}


double Sign(myPoint p1, myPoint p2, myPoint p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool IsPointInTri(myPoint pt, myPoint v1, myPoint v2, myPoint v3)
{
  bool b1, b2, b3;

  b1 = Sign(pt, v1, v2) < 0.0f;
  b2 = Sign(pt, v2, v3) < 0.0f;
  b3 = Sign(pt, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}

bool collinear(double x1, double y1, double x2,  
               double y2, double x3, double y3) 
{ 

    // Calculation the area of  
    // triangle. We have skipped  
    // multiplication with 0.5  
    // to avoid floating point  
    // computations  
    double a = x1 * (y2 - y3) +  
            x2 * (y3 - y1) +  
            x3 * (y1 - y2); 
  	return eq(a, 0);
} 


bool collinear(myPoint &p0, myPoint &p1, myPoint &p2) {
	return collinear(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y);
}

/*
bool pointInTriangle(myPoint &p, myPoint &p0, myPoint &p1, myPoint &p2) {  
    double dX = p.x-p2.x;
    double dY = p.y-p2.y;
    double dX21 = p2.x-p1.x;
    double dY12 = p1.y-p2.y;
    double D = dY12*(p0.x-p2.x) + dX21*(p0.y-p2.y);
    double s = dY12*dX + dX21*dY;
    double t = (p2.y-p0.y)*dX + (p0.x-p2.x)*dY;
    if (D<0) return leq(s,0.0) && leq(t, 0.0) && geq(s+t,D);
    return geq(s,0.0) && geq(t,0.0) && leq(s+t,D);

//    bool b0 = (Vector(P.x - A.x, P.y - A.y) * Vector(A.y - B.y, B.x - A.x) > 0);
//	bool b1 = (Vector(P.x - B.x, P.y - B.y) * Vector(B.y - C.y, C.x - B.x) > 0);
//	bool b2 = (Vector(P.x - C.x, P.y - C.y) * Vector(C.y - A.y, A.x - C.x) > 0);
//	return (b0 == b1 && b1 == b2);
}
*/

bool interval(double l, double r, double x) {
	if(l>r) {
		double aux = l;
		l = r;
		r = aux;
	}
	return eq(l,x) || eq(r,x) || (x>l&&x<r);
}

bool IsPointInTriLine(myPoint pt, myPoint v1, myPoint v2, myPoint v3)
{
	if(collinear(pt,v1,v2) && interval(v1.x,v2.x,pt.x) 
		&& interval(v1.y,v2.y,pt.y)) return true;
	if(collinear(pt,v1,v3) && interval(v1.x,v3.x,pt.x) 
		&& interval(v1.y,v3.y,pt.y)) return true;
	if(collinear(pt,v3,v2) && interval(v3.x,v2.x,pt.x) 
		&& interval(v3.y,v2.y,pt.y)) return true;
	return false;
}

int main() {
	myPoint p0, p1, p2;

	while(1) {
		cin >> p0.x >> p0.y;
		cin >> p1.x >> p1.y;
		cin >> p2.x >> p2.y;

		if(p0.x<0 || p0.x>100.0) while(1);
		if(p1.x<0 || p1.x>100.0) while(1);
		if(p2.x<0 || p2.x>100.0) while(1);


		if(eq(p0.x,0.0)&&eq(p0.y,0.0)
		 &&eq(p1.x,0.0)&&eq(p1.y,0.0)
		 &&eq(p2.x,0.0)&&eq(p2.y,0.0))
			break;

		bool isColl = false;
		if(collinear(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y)) {
			isColl = true;
			/*
			int cont = 0;
			if(eq(p0.x, floor(p0.x)) && eq(p0.y, floor(p0.y)) ) cont++;
			if(eq(p1.x, floor(p1.x)) && eq(p1.y, floor(p1.y)) ) cont++;
			if(eq(p2.x, floor(p2.x)) && eq(p2.y, floor(p2.y)) ) cont++;
			
			cout << setw(4) << cont << endl;
			//while(1);
			continue;
			*/
		}

		myPoint p;
		int cont = 0;
		p.x = 0.0;
		while(p.x<100.5) {
			p.y = 0.0;
			while(p.y<100.5) {
				if(isColl) {
					double minx = min(p0.x, min(p1.x, p2.x) );
					double miny = min(p0.y, min(p1.y, p2.y) );
					double maxx = max(p0.x, max(p1.x, p2.x) );
					double maxy = max(p0.y, max(p1.y, p2.y) );

					if(collinear(p, p0, p1) && p.x>minx && p.x<maxx 
						&& p.y>miny && p.y<maxy)
						cont++;
				}
				else {
					if(IsPointInTriLine(p,p0,p1,p2))
						cont++;
					else 
					if(IsPointInTri(p,p0,p1,p2))
						cont++;
				}
				p.y += 1.0;
			}
			p.x += 1.0;
		}
		cout << setw(4) << cont << endl;
	}

}
