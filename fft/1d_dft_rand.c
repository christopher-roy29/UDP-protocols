#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>
int main()
{
        int i,N=1024;
	int m,t;
        float f,g;
        srand(time(NULL));

        fftw_plan p;

        //in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
        //fftw_complex in[][2] = {{1,2},{3,4},{5,6},{7,8}};
        fftw_complex in[N/2][2];
	//out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
        fftw_complex out[N][2];
        for(i=0;i<N/2;i++)
	{
		m= rand();
	        t= m%10;
	        if(t<0)
        	{
                	t=-1*t;
        	}
	        f= (t*1)+(t*0.1)+(t*0.01);
		g= (t*1)+(t*0.1)+(t*0.01)+(t*0.001); /*creating a random Float*/
		in[i][0]=f;
		in[i][1]=g;
	}	
	p = fftw_plan_dft_1d(N, (fftw_complex *)&in, (fftw_complex*)&out, FFTW_FORWARD, FFTW_ESTIMATE);

        fftw_execute(p);   /* repeat as needed */
        for(i =0; i < N/2; i++)
                printf("%f \t %fj \n", out[i][0], out[i][1]);

        fftw_destroy_plan(p);
        //fftw_free(in);
        //fftw_free(out);
return 0;
}
