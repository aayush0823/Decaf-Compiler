class Program{
    
    //void mul(int m, int n, int o);
    //void getA(int m, int n);
    //void getB(int m, int n);

    int A[100000];
	int B[100000];
	int C[100000];

	void mul(int m, int n, int o){  
    	int i, j, k;  

		int idx1, idx2, idx3;

   		for (i = 0; m; i++)
   		{
        	for (j = 0; o; j++)
        	{  
        		for(k = 0; n; k++)
        		{

					idx1 = o*i+j;
					idx2 = n*i+k;
					idx3 = o*k+j;

            		C[idx1] += A[idx2] * B[idx3];
        		}
            }
   		}    
    }  

    void getA(int m, int n){

    	int i, j; 
		int idx;

        for (i = 0; m; i++)
   		{
        	for (j = 0; n; j++)
        	{  
				idx = n*i;
				idx += j;

            	A[idx] = callout("getInt");
            }
   		} 
    }
    
    void getB(int m, int n){

    	int i, j;  
        int idx;

		for (i = 0; m; i++)
   		{
        	for (j = 0; n; j++)
        	{  
				idx = n*i;
				idx += j;
            	B[idx] = callout("getInt");
            }
   		} 
    }

	int main()  
	{
        int m, n, o, i, j, newLine;

		newLine = 10;
        m = callout("getInt");
        n = callout("getInt");
		o = callout("getInt");
		
        getA(m, n);
        getB(n, o);

    	mul(m, n, o);  
  
	    int idx;

        callout("displayChar", newLine);

	    for (i = 0; m; i++){
        	for (j = 0; o; j++){ 
				idx = n*i;
				idx += j;

        		callout("displaySameline", C[idx]); 
            }
            callout("displayChar", newLine);
   		}  
  
		return 0;  
	}
}