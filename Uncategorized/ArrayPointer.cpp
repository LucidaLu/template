template <class T>
struct ArrayPointer {
	int id;

	ArrayPointer(T *x=0) {
		if(!x)
			id=-1;
		else
			a[id=cnt++]=*x;
	}

	T *operator ->() {
		return a+id;
	}
	
	T &operator *() {
		return a[id];
	}

	static T *a;
	static int cnt;
};

/*
template <> TypeName *ArrayPointer<TypeName>::a=(TypeName*)malloc(SIZE*sizeof(TypeName));
template <> int ArrayPointer<TypeName>::cnt=0;
overload operator_new
*/