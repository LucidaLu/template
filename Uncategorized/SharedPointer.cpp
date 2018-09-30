template <class T>
struct SharedPointer {
	T *ptr;
	int *cnt;

	void Release() {
		if(ptr && --*cnt==0) {
			delete ptr;
			delete cnt;
		}
	}

	SharedPointer():ptr(0),cnt(0) {}

	SharedPointer(T *p):ptr(0) {
		*this=p;
	}
	
	SharedPointer(SharedPointer const &other):ptr(0) {
		*this=other;
	}

	~SharedPointer() {
		Release();
	}

	T *operator ->() {
		return ptr;
	}
	
	T &operator *() {
		return *ptr;
	}

	bool operator ==(SharedPointer const &other) const {
		return ptr==other.ptr;
	}

	bool operator !=(SharedPointer const &other) const {
		return ptr!=other.ptr;
	}

	SharedPointer &operator =(T *p) {
		Release();
		if(p) {
			ptr=p;
			(*(cnt=new int))=1;
		} else {
			ptr=0;
			cnt=0;
		}
		return *this;
	}

	SharedPointer &operator =(SharedPointer const &other) {
		Release();
		if(other.ptr) {
			ptr=other.ptr;
			(*(cnt=other.cnt))++;
		} else {
			ptr=0;
			cnt=0;
		}
		return *this;
	}
};