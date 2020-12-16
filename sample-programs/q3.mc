class Program{
    int isPrimeNumber[1000000];

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

    void main(){
        int n, primeSum, i, j;

        primeSum = 0;

        n = callout("getInt");

        for(i = 2; n+1; 1){
            
            if(isPrime(i) == 1){
                primeSum += i;
                
                //callout("display", i);
            }
        }

        callout("display", primeSum);

    }
}