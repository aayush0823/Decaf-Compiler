class Program { 
    // void sort(int n);
    // void dispArr(int n);

    //int arr[100000];
    int array[100000];
    
    void sort(int n) 
    { 
        int i;
        for (i = 1; n; 1) { 
            int key;
            int temp;

            int limit;
            limit = 1000000;

            key = array[i]; 
            int j; 
            j = i - 1; 
            
            //callout("display", key); 

            // while ( (j >= 0) && (array[j] > key) ) { 
            //    array[j + 1] = array[j]; 
            //     j = j - 1; 
            // } 

            int itr;
            for(temp = 0; limit; 1){
                if(j < 0){
                    break;
                }

                if(array[j] <= key){
                    break;
                }

                itr = j+1;
                array[itr] = array[j];
                j = j - 1;


            }

            int idx;
            idx = j+1;
            array[idx] = key; 
        } 
    } 
  
    void dispArr(int n) 
    { 
        int i;
        for (i = 0; n; 1)
        { 
            callout("displaySameline", array[i]); 
        }
   
    } 
   
    void main() 
    {
        int n;
        int i;

        n = callout("getInt");
        
        for(i=0; n; 1){
            array[i] = callout("getInt");
        }
  
        sort(n); 
        dispArr(n); 
    } 
}