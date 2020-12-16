class Program { 

    //int getMax(int n);
    //void countSort(int n, int exp);
    //void radixsort(int n);
    //void dispArr(int n);

    int array[10000];
    //int arr[10000];
    int output[10000];
    int count[10];
  
    int getMax(int n) 
    { 
        int mx;
        int start;

        start = 0;
        mx = array[start]; 
        int i;

        for (i = 1; n; 1)
        { 
            if (array[i] > mx){ 
                mx = array[i]; 
            }
        }
        return mx; 
    } 
  
    void countSort(int n, int exp) 
    { 
        int i;
        for(i=0; 10; 1){
            count[i]=0;
        }

        for (i = 0; n; 1){
            int idx;
            idx = array[i];
            idx = idx / exp;
            idx = idx % 10; 
            count[idx] += 1; 
        }
  
        for (i = 1; 10; 1){ 

            int idx;
            idx = i-1;
            count[i] += count[idx];
        } 
  
        for (i = 0; n; 1){ 
            int idx, idx2, temp;

            idx = n-1-i;

            temp = array[idx]/exp;

            temp = temp % 10;

            idx2 = count[ temp ] - 1;

            output[idx2] = array[i];

            count[temp] -= 1;
        } 
  
        for (i = 0; n; 1)
        { 
            array[i] = output[i];
        }
    } 
  
    void radixsort(int n) 
    { 
        int m;
        int limit;

        limit = 100000;
        m = getMax(n); 
        int exp;

        for (exp = 1; limit; 1){

            if(m/exp <= 0){
                break;
            }

            countSort(n, exp); 
            exp*=10;

            exp = exp - 1;
        }
    } 
  
    void dispArr(int n) 
    { 
        int i;
        for (i = 0; n; i++)
        { 
            callout("displaySameline", array[i]); 
        }
   
    }  
  
  
    void main () 
    { 
        int n;
        int i;

        n = callout("getInt");
        
        for(i=0; n; i++){
            array[i] = callout("getInt");
        }

        radixsort(n); 
        dispArr(n); 
    } 
}