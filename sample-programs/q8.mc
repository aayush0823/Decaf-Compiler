class Program{
    
    //void merging(int low, int mid, int high);
    //void sort(int low, int high);
    //void dispArr(int n);

    int array[100000];
    int a[100000];
    int b[100000];

    void merging(int low, int mid, int high) {
        //int l1, l2, i;

        int l1;
        int l2;
        int i, limit, idxi, idxl1, idxl2;

        limit = 100000;

        l1 = low;
        l2 = mid + 1;

        for(i = low; limit; 1) {
            
            if(l1 > mid){
                break;
            }

            if(l2 > high){
                break;
            }

            if(a[l1] <= a[l2]){
                b[i] = a[l1];
                l1 = l1 + 1;
            }

            if(a[l1] > a[l2])
            {
                b[i] = a[l2];
                l2 = l2 + 1;
            }

            idxi = i;
            idxl1 = l1;
            idxl2 = l2;

            //callout("displaySameline", idxi);
            //callout("displaySameline", idxl1);
            //callout("display", idxl2);
        }

        // callout("display", idxi);


        int itr;
        for(itr = idxl1; mid+1; 1){
            b[idxi] = a[itr];
            idxi += 1;
        }

        for(itr = idxl2; high+1; 1){
            b[idxi] = a[itr];
            idxi += 1;
        }

        for(i = low; high+1; i++){
            a[i] = b[i];
        }
    }

    void sort(int low, int high) {
        int mid;
        
        if(low < high) {
            
            mid = (low + high); 
            mid = mid/ 2;

            // callout("displaySameline", low);
            // callout("displaySameline", mid);
            // callout("display", high);

            sort(low, mid);

            int next;
            next = mid + 1;
            sort(next, high);
            merging(low, mid, high);

        } else { 
            return;
        }   
    }
    
    void dispArr(int n) 
    { 
        int i;
        for (i = 0; n; i++)
        { 
            callout("displaySameline", a[i]); 
        }
   
    } 

    void main() { 
        int n;
        int i;

        n = callout("getInt");
        
        for(i=0; n; 1){
            a[i] = callout("getInt");
        }
        
        int start;
        start = 0;

        int end;
        end = n-1;
        
        sort(start, end);
        dispArr(n);
    }
}