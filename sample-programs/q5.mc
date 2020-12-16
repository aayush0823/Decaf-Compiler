class Program{
    // void dispArr(int n);
    // void heapPermutation(int size, int n);

    int array[10000];
    int a[10000];
    int i;

    void dispArr(int n) 
    { 
        int i, newLine;
        newLine = 10;

        for (i = 0; n; 1)
        { 
            callout("displaySameline", array[i]); 
        }
        callout("displayChar", newLine);

   
    } 
  
    void heapPermutation(int size, int n) 
    { 
        if (size == 1){
            dispArr(n); 
            return;
        }
  
        for (i=0; size; 1) 
        { 
            int newSize;
            newSize = size - 1;

            heapPermutation(newSize, n); 
            if (size % 2 == 1) 
            { 
                int temp;
                int start;

                start = 0;
                temp = array[start]; 
                array[start] = array[newSize]; 
                array[newSize] = temp; 
            } 
            else
            { 
                int temp;

                temp = array[i]; 
                array[i] = array[newSize]; 
                array[newSize] = temp; 
            }
        } 
    } 
  
    void main() 
    { 
        int n, i;
        n = callout("getInt");

        for(i=0; n; 1){
            array[i]=i+1;
        } 

        heapPermutation(n, n); 
    }
}