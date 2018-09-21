#include <bits/stdc++.h>

struct Istream {

	Istream() {
#ifndef ONLINE_JUDGE
#ifdef DEBUG
		freopen("input","r",stdin);
#else
		std::string fileName(__FILE__),name=fileName.substr(0,fileName.find('.'));
		freopen((name+".in").c_str(),"r",stdin);
		freopen((name+".out").c_str(),"w",stdout);
#endif
#endif
	}
#ifdef OI
	char getchar() {
		static const int IN=1e5;
		static char in[IN],*ip=in,*ie=in;
		return ip==ie && (ie=(ip=in)+fread(in,1,IN,stdin),ip==ie)?EOF:*ip++;
	}
#else
	Istream &operator >>(double &x) {
		scanf("%lf",&x);
		return *this;
	}
#endif
	template <class T> 
	Istream &operator >>(T &x) {
		static char ch;static bool neg;
		for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
		for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
		x=neg?-x:x;
		return *this;
	}

	Istream &operator >>(char &ch) {
		while(!isalnum(ch=getchar()) && !ispunct(ch));
		return *this;
	}

	Istream &operator >>(char *s) { 
		while(!isalnum(*s=getchar()) && !ispunct(*s));
		while(isalnum(*++s=getchar()) || ispunct(*s));
		*s=0;return *this;
	}

	template <class T>
	operator T() {
		static T x;*this>>x;
		return x;
	}
}fin;

struct Ostream {
#ifdef OO
	char out[(int)1e5],*op;
	
	Ostream():op(out) {}
	~Ostream() {
		flush();
	}
	
	void flush() {
		fwrite(out,1,op-out,stdout);
	}

	void putchar(char const &x) {
		*op==EOF && (flush(),op=out,*op++);
		*op++=x;
	}
#else
	Ostream &operator <<(double x) {
		printf("%.10lf",x);
		return *this;
	}
#endif
	template <class T>
	Ostream &operator <<(T x) {
		x<0 && (putchar('-'),x=-x);
		static char stack[233];static int top;
		for(top=0;x;stack[++top]=x%10+'0',x/=10);
		for(top==0 && (stack[top=1]='0');top;putchar(stack[top--]));
		return *this;
	}

	Ostream &operator <<(char ch) {
		putchar(ch);
		return *this;
	}

	Ostream &operator <<(const char *s) {
		while(*s)
			putchar(*s++);
		return *this;
	}
}fout;

template <class T> bool Enlarge(T &a,T const &b) {
	return a<b?a=b,1:0;
}

template <class T> bool Reduce(T &a,T const &b) {
	return a>b?a=b,1:0;
}

