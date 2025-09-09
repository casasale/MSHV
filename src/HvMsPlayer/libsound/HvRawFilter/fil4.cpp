double dot_product_da_da(const double *a, double *b,int size,int offset_b)
{
    double sum = 0;
    int i;
    //If the vectors are INTEGER or REAL -> DOT_PRODUCT(VECTOR_A, VECTOR_B) = SUM(VECTOR_A*VECTOR_B)
    for (i = 0; i < size; i++)
    {
        sum += a[i] * b[i+offset_b];
    }
    return sum;
}
void fil4(int *id1,int n1,int *id2,int &n2)
{
	/*! FIR lowpass filter designed using ScopeFIR
	! fsample     = 48000 Hz
	! Ntaps       = 49
	! fc          = 4500  Hz
	! fstop       = 6000  Hz
	! Ripple      = 1     dB
	! Stop Atten  = 40    dB
	! fout        = 12000 Hz*/
  const int NTAPS = 49;
  const int NDOWN = 4;
  static double t[NTAPS+10];
  const double  w[NTAPS+10] =
  {
	    0.000861074040, 0.010051920210, 0.010161983649, 0.011363155076,
        0.008706594219, 0.002613872664,-0.005202883094,-0.011720748164,
       -0.013752163325,-0.009431602741, 0.000539063909, 0.012636767098,
        0.021494659597, 0.021951235065, 0.011564169382,-0.007656470131, 
       -0.028965787341,-0.042637874109,-0.039203309748,-0.013153301537,   
        0.034320769178, 0.094717832646, 0.154224604789, 0.197758325022,   
        0.213715139513, 0.197758325022, 0.154224604789, 0.094717832646,   
        0.034320769178,-0.013153301537,-0.039203309748,-0.042637874109,   
       -0.028965787341,-0.007656470131, 0.011564169382, 0.021951235065,   
        0.021494659597, 0.012636767098, 0.000539063909,-0.009431602741,  
       -0.013752163325,-0.011720748164,-0.005202883094, 0.002613872664,   
        0.008706594219, 0.011363155076, 0.010161983649, 0.010051920210,   
        0.000861074040
  };
  n2=n1/NDOWN;
  if(n2*NDOWN!=n1) return;
  int k=0;// k=1-NDOWN;//-3
  for (int i = 0; i < n2; ++i)
  {//do i=1,n2 //k=k+NDOWN
     for (int j = 0; j < NTAPS-NDOWN; ++j) t[j] = t[j+NDOWN];//t(1:NTAPS-NDOWN)=t(1+NDOWN:NTAPS)          //!Shift old data down in array t
     for (int j = 0; j < NDOWN; ++j) t[j+(NTAPS-NDOWN)] = id1[j+k]; //t(1+NTAPS-NDOWN:NTAPS)=id1(k:k+NDOWN-1)    //!Insert new data at end of t
	 k+=NDOWN;
     id2[i]=(int)(dot_product_da_da(w,t,NTAPS,0));//id2(i)=nint(dot_product(w,t))
  }
}
fil4(rawm,crawm,dat_tt,k);