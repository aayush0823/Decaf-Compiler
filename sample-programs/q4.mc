class Program{
    void main(){

        int limit;
        limit = callout("getInt");

        int a, b, n;
        int c; 

        int m;
        int count; 

        m = 2;
        count = 0;
        c = 0;

        for (c=0; limit; 1) { 
    
            for (n = 1; m; 1) { 
    
                a = m * m - n * n; 
                b = 2 * m * n; 
                c = m * m + n * n; 
    
                if (c > limit){ 
                    break; 
                }
    
                count += 1;
            } 
            c -= 1;
            m += 1; 
        }

        callout("display", count);

    }
}
