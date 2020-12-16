class Program{

	int alphabet[26];
    char filename[1000];
    char data[100000];

	void main(){

		int i;
		
		i = 0;
		int n;

		n = callout("getInt");

		for(i=0; i<n; i++){
			filename[i] = getChar();
		}

		data = readLines(filename[]);

		int i;
		i=0;

		while(data[i] != '\0'){
			alphabet[data[i]-'a']+=1;
			i+=1;
		}

		for(i=0; i<26; i++){
			print(alphabet[i], " ");
		}

	}
}