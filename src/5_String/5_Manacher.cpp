void Manacher(char *str,int rad[])//str��ԭ�ַ��� ma�Ǽ������ַ������iΪ���ļ�������Ӵ��İ볤��
{
    int len=strlen(str+1),l=0;
	for(int i=1;i<=len;++i){
        s[++l]='$';
        s[++l]=str[i];
    }
	s[++l]='$';s[0]='#';//s�Ǽ������ַ�����ַ���
	rad[1]=1;
    int R=1,ID=1;//R�ǵ�ǰ���������Ӵ������ҵĶ˵� IDΪR��Ӧ�Ļ����Ӵ�������
	for(int i=1;i<=l;++i){
		if(i<R)
			rad[i]=min(rad[2*ID-i],R-i+1);//2*ID-iΪi�ڵ�ǰ������������Ӵ�����������Ӧ��λ��
        else
			rad[i]=1;
		for(;s[i+rad[i]]==s[i-rad[i]];++rad[i]);
		if(R<rad[i]+i-1){
            R=rad[i]+i-1;
            ID=i;
        }
	}
    //ԭ�ַ�����������Ӵ�Ϊmax{rad[i]-1}
}
