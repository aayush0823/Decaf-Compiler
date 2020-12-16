class Program{
    // int pow(int i, int k);

    int pow(int i, int k){

        int j;
        int ans;

        ans = 1;

        for(j=0; k; 1){
            // int zig;
            ans *= i;
        }

        // zig = 0;
        
        return ans;
    }

    //int pow(){
    //    return 0;
    //}

    void main(){
        int n, k, i, ans;
        char p;

        //pqr();
        //k = p + i;
        //k = pqr - i;
        //p /= p;

        //int n;

        ans = 0;

        n = callout("getInt");
        k = callout("getInt");

        for(i=1; n+1; 1){
            ans += pow(i, k);
            
            // callout("display", ans);
        }

        callout("display", ans);
    }
}