 /* 
 c program:
 --------------------------------
  1. draws Mandelbrot set for Fc(z)=z*z +c
  using Mandelbrot algorithm ( boolean escape time )
 -------------------------------         
 2. technique of creating ppm file is  based on the code of Claudio Rocchini
 http://en.wikipedia.org/wiki/Image:Color_complex_plot.jpg
 create 24 bit color graphic file ,  portable pixmap file = PPM 
 see http://en.wikipedia.org/wiki/Portable_pixmap
 to see the file use external application ( graphic viewer)
  */
 #include <stdio.h>
 #include <math.h>
 #include <time.h>
 int main()
 {
          /* screen ( integer) coordinate */
        int iX,iY;
	clock_t begin;
  	clock_t end;
	double totalTime;
        const int iXmax = 1000; 
        const int iYmax = 1000;
        /* world ( double) coordinate = parameter plane*/
        double Cx,Cy;
        const double CxMin=-2.5;
        const double CxMax=1.5;
        const double CyMin=-2.0;
        const double CyMax=2.0;
        /* */
        double PixelWidth=(CxMax-CxMin)/iXmax;
        double PixelHeight=(CyMax-CyMin)/iYmax;
        /* color component ( R or G or B) is coded from 0 to 255 */
        /* it is 24 bit color RGB file */
        const int MaxColorComponentValue=255; 
        FILE * fp;
        char *filename="fractalColor.ppm";
        char *comment="# ";/* comment should start with # */
        static unsigned char color[3];
        /* Z=Zx+Zy*i  ;   Z0 = 0 */
        double Zx, Zy;
        double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
        /*  */
        int Iteration;
	int Iteration2;
        const int IterationMax=36;
        /* bail-out value , radius of circle ;  */
        const double EscapeRadius=2;
        double ER2=EscapeRadius*EscapeRadius;
        /*create new file,give it a name and open it in binary mode  */
        fp= fopen(filename,"wb"); /* b -  binary mode */
        /*write ASCII header to the file*/
        fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmax,iYmax,MaxColorComponentValue);
        /* compute and write image data bytes to the file*/
	begin = clock();
        for(iY=0;iY<iYmax;iY++)
        {
             Cy=CyMin + iY*PixelHeight;
             if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
             for(iX=0;iX<iXmax;iX++)
             {         
                        Cx=CxMin + iX*PixelWidth;
                        /* initial value of orbit = critical point Z= 0 */
                        Zx=0.0;
                        Zy=0.0;
                        Zx2=Zx*Zx;
                        Zy2=Zy*Zy;
                        /* */
                        for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
                        {
                            Zy=2*Zx*Zy + Cy;
                            Zx=Zx2-Zy2 +Cx;
                            Zx2=Zx*Zx;
                            Zy2=Zy*Zy;
                        };
                        /* compute  pixel color (24 bit = 3 bytes) */
			Iteration2 = Iteration % 16;
                        if (Iteration==IterationMax)
                        { /*  interior of Mandelbrot set = black */
                           color[0]=0;
                           color[1]=0;
                           color[2]=0;                           
                        }
                        else if (Iteration2 == 0)
			{
			   color[0]=66;
                           color[1]=30;
                           color[2]=15;
			}
                        else if (Iteration2 == 1)
			{
			   color[0]=25;
                           color[1]=7;
                           color[2]=26;
			}
                        else if (Iteration2 == 2)
			{
			   color[0]=9;
                           color[1]=1;
                           color[2]=47;
			}
                        else if (Iteration2 == 3)
			{
			   color[0]=4;
                           color[1]=4;
                           color[2]=73;
			}
                        else if (Iteration2 == 4)
			{
			   color[0]=0;
                           color[1]=7;
                           color[2]=100;
			}
                        else if (Iteration2 == 5)
			{
			   color[0]=12;
                           color[1]=44;
                           color[2]=138;
			}
                        else if (Iteration2 == 6)
			{
			   color[0]=24;
                           color[1]=82;
                           color[2]=177;
			}
                        else if (Iteration2 == 7)
			{
			   color[0]=57;
                           color[1]=125;
                           color[2]=209;
			}
                        else if (Iteration2 == 8)
			{
			   color[0]=134;
                           color[1]=181;
                           color[2]=229;
			}
                        else if (Iteration2 == 9)
			{
			   color[0]=211;
                           color[1]=236;
                           color[2]=248;
			}
                        else if (Iteration2 == 10)
			{
			   color[0]=241;
                           color[1]=233;
                           color[2]=191;
			}
                        else if (Iteration2 == 11)
			{
			   color[0]=248;
                           color[1]=201;
                           color[2]=95;
			}
                        else if (Iteration2 == 12)
			{
			   color[0]=255;
                           color[1]=170;
                           color[2]=0;
			}
                        else if (Iteration2 == 13)
			{
			   color[0]=204;
                           color[1]=128;
                           color[2]=0;
			}
                        else if (Iteration2 == 14)
			{
			   color[0]=153;
                           color[1]=87;
                           color[2]=0;
			}
                        else if (Iteration2 == 15)
			{
			   color[0]=106;
                           color[1]=52;
                           color[2]=3;
			}

			/*
                        else if (Iteration == 17)
			{
			   color[0]=255;
                           color[1]=255;
                           color[2]=255;
			}
                        else if (Iteration == 18)
			{
			   color[0]=255;
                           color[1]=255;
                           color[2]=255;
			}
                        else if (Iteration == 19)
			{
			   color[0]=255;
                           color[1]=255;
                           color[2]=255;
			}
                        else
			{
			   color[0]=255;
                           color[1]=255;
                           color[2]=255;
			}
			*/			
                  
                        /*write color to the file*/
                        fwrite(color,1,3,fp);

                }

        }
	end = clock();
	totalTime = (((double)(end - begin))/CLOCKS_PER_SEC);
	printf("%lf\n", totalTime);
        fclose(fp);
        return 0;
 }
