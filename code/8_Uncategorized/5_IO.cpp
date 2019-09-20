namespace IO {
	const int IN=1e6;
	char in[IN],*ip=in,*ie=in;
	#define getchar() (ip==ie && (ie=(ip=in)+fread(in,1,IN,stdin),ip==ie)?EOF:*ip++)
	struct Istream {
		template <class T>
		Istream &operator >>(T &x) {
			static char ch;static bool neg;
			for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
			for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
			x=neg?-x:x;
			return *this;
		}
	}fin;

	const int OUT=1e6;
	char out[OUT],*op=out,*oe=out+OUT;
	#define flush() fwrite(out,1,op-out,stdout)
	#define putchar(x) ((op==oe?(flush(),op=out,*op++):*op++)=(x)) 
	struct Ostream {
		~Ostream() {
			flush();
		}
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
	}fout;
}

using IO::fin;
using IO::fout;
