class Program{

    char filename[1000];
    char data[100000];
    char curr[1000];

	void main(){

		int i;
		
		int n, success;

        n  = callout("getInt");

		for(i=0; i<n; i++){
		    filename[i] = getChar();
		}

		data = readLines(filename[]);
        
        success = writeLines(filename[], filename[], "w");
		i=0;
        int ans;
        int j;

        ans=0;

		while(data[i] != '\0'){
			j = i;

            while(data[j]){
                curr[j-i] = data[j];
                j++;
            }

            bool isNew;
            isNew = true;

            int k, l;
            for(k=0; k<ans; k++){
                for(l=i; l<j; l++)
                {
                    if(curr[l-i] != data[l])
                    {
                        break;
                    }

                    if(l == (j-1))
                    {
                        isNew = false;
                    }
                }

                if(isNew == false)
                {
                    break;
                }
    
            }

            if(isNew == true)
            {
                ans++;
            }

            i=j;
        }

        callout("print", "%d", and);
	}
}