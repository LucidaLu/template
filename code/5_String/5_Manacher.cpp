void Manacher(char *str,int rad[])//str是原字符串 ma是加入新字符后的以i为中心极大回文子串的半长度
{
    int len=strlen(str+1),l=0;
	for(int i=1;i<=len;++i){
        s[++l]='$';
        s[++l]=str[i];
    }
	s[++l]='$';s[0]='#';//s是加入新字符后的字符串
	rad[1]=1;
    int R=1,ID=1;//R是当前极长回文子串的最右的端点 ID为R对应的回文子串的中心
	for(int i=1;i<=l;++i){
		if(i<R)
			rad[i]=min(rad[2*ID-i],R-i+1);//2*ID-i为i在当前这个极长回文子串中在左边相对应的位置
        else
			rad[i]=1;
		for(;s[i+rad[i]]==s[i-rad[i]];++rad[i]);
		if(R<rad[i]+i-1){
            R=rad[i]+i-1;
            ID=i;
        }
	}
    //原字符串的最长回文子串为max{rad[i]-1}
}
