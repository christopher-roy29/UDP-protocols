#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>
int main()
{
        int i,N=8;
        //fftw_complex  *out;
        fftw_plan p,q;

        //in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
        fftw_complex in[][2] = {{1,2},{3,4},{5,6},{7,8}};
        //out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
        fftw_complex out[N][2];
        p = fftw_plan_dft_1d(N, (fftw_complex *)&in, (fftw_complex*)&out,FFTW_FORWARD, FFTW_ESTIMATE);

        fftw_execute(p);   /* repeat as needed */
        for(i =0; i < N/2; i++)
	        printf("%f \t %fj \n", out[i][0], out[i][1]);
	double out1[N];
        q = fftw_plan_dft_c2r_1d(N, (fftw_complex *)&out, (double *)&out1, FFTW_ESTIMATE);
       	fftw_execute(q);
	printf("\n\nOutput:\n");
	for(i =0; i < N; i++)
                printf("\n%f \t ", out1[i]/N);
	fftw_destroy_plan(p);
	fftw_destroy_plan(q);
	//fftw_free(in);
        //fftw_free(out);
return 0;
}
