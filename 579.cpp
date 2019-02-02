#include <cstdio>
#include <iostream>

using namespace std;

//579

int main() {
	int h, m;
	double hourAngle, minuteAngle, diff;

	while( 1 ) {
		scanf("%d:%02d", &h, &m);
		if(!h&&!m) break;

		//printf("%02d:%02d\n", h, m);

		if(h==12) hourAngle = 0.00;
		else hourAngle = ((double)30.00) * (double)h;
		hourAngle += (double)30.00 * ( (double)m / (double)60.00 );

		minuteAngle = (double)6.00 * (double)m;

		//printf("hourAngle = %.03lf\n", hourAngle);
		//printf("minuteAngle = %.03lf\n", minuteAngle);

		double diff = hourAngle - minuteAngle;
		if(diff<0) diff += 360.00;
		if(diff>180.00) diff = 360.00 - diff;
		printf("%0.03lf\n", diff);
	}

}