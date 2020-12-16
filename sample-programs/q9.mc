class Program{
    
    //void add(int m, int n);
    //void getA(int m, int n);
    //void getB(int m, int n);

    int A[100000];
	int B[100000];
	int C[100000];

	void add(int m, int n){  
    	int i, j; 
		int idx;

   		for (i = 0; m; i++)
   		{
        	for (j = 0; n; j++)
        	{  
				idx = n*i;
				idx += j;

            	C[idx] = A[idx] + B[idx];
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

	int main(){
        int m, n, i, j, newLine;

		newLine = 10;

        m = callout("getInt");
        n = callout("getInt");
		
        getA(m, n);
        getB(m, n);

    	add(m, n);  
		
		int idx;

        callout("displayChar", newLine);

	    for (i = 0; m; i++){
        	for (j = 0; n; j++){ 
				idx = n*i;
				idx += j;

        		callout("displaySameline", C[idx]); 
            }
            callout("displayChar", newLine);
   		}  
  
		return 0;  
	}
}