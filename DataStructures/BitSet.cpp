struct BitSet {
	unsigned int64 s[(XV>>6)+1];
    int maxI;
	
	BitSet(int v):maxI(v>>6) {
        memset(s,0,sizeof(s));
    }
    
	void Set(unsigned int pos,bool val) {
        val==0?(s[pos>>6]&=~(1ull<<(pos&63))):(s[pos>>6]|=1ull<<(pos&63));
    }

    bool Test(unsigned int pos) const {
        return s[pos>>6]>>(pos&63)&1;
    }
};
