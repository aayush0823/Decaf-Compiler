class Program{
    
    int isPrime(int n){
        int flag;

        flag = 1;
        int i;

        if(n == 2){
            flag = 1;
            return flag;
        }
        
        for (i = 2; n/2; 1)
        {
            if (n % i == 0)
            {
                flag = 0;
                break;
            }
        }

        return flag;
    }

    // int someFunc(int ping, int ping){
    //     pqr = 0;
    //     a[i] = 5;
    // }

    void main(){
        int n;

        n = callout("getInt");

        // getSmthng();
        int ans;
        
        ans = isPrime(n);

        callout("display", ans);

    }
}