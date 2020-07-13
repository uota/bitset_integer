#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

template <size_t N>
class bi {
public:
    std::bitset<N> val;
    bi(){}
    bi(int v){ val = std::bitset<N>(v); }
    bi(long long v){ val = std::bitset<N>(v); }
    bi(std::bitset<N> v){ val = v; }
    bi(const char *s){
        *this = bi(std::string(s));
    }
    bi(std::string s){
        bool this_sign=false;
        if(s[0]=='-'){
            this_sign = true;
            s.erase(s.begin());
        }
        for(char c : s){
            *this *= 10;
            *this += bi((c-'0'));
        }
        if(this_sign){
            *this = convert_c2();
        }
    }
    bi operator + (bi r) {
        int c = 0;
        bi<N> s;
        for(int i = 0; i < (int)N; i++){
            int t = c + r.val[i] + val[i];
            s.val[i] = t & 1;
            c = t >> 1;
        }
        return s;
    }
    bi operator - (bi r) {
        return *this + r.convert_c2();
    }
    bi operator * (bi r) {
        bi<N> l = *this, ret;
        bool ret_sign = false;
        if(l.sign()){
            l = l.convert_c2();
            ret_sign = !ret_sign;
        }
        if(r.sign()){
            r = r.convert_c2();
            ret_sign = !ret_sign;
        }
        for(int i = 0; i < (int)N; i++){
            if(l.val[i]){
                ret = ret + r;
            }
            r.val <<= 1;
        }
        if(ret_sign){
            ret = ret.convert_c2();
        }
        return ret;
    }
    bi operator / (bi r) {
        if(r.val.none()) throw std::range_error("Divided by zero.");
        bi<N> q, e;
        div(r, q, e);
        return q;
    }
    bi operator % (bi r) {
        if(r.val.none()) throw std::range_error("Divided by zero.");
        bi<N> q, e;
        div(r, q, e);
        return e;
    }
    void operator += (bi r) { val = (*this + r).val; }
    void operator -= (bi r) { val = (*this - r).val; }
    void operator *= (bi r) { val = (*this * r).val; }
    void operator /= (bi r) { val = (*this / r).val; }
    void operator %= (bi r) { val = (*this % r).val; }
    void operator =  (bi r) { val = r.val; }
    bool operator == (bi r) { return val == r.val; }
    bool operator != (bi r) { return val != r.val; }
    bool operator <  (bi r) { return (*this - r).sign(); }
    bool operator >  (bi r) { return (r - *this).sign(); }
    bool operator <= (bi r) { return !(r - *this).sign(); }
    bool operator >= (bi r) { return !(*this - r).sign(); }
    long long to_llong() {
        if(sign()){
            return -convert_c2().val.to_ullong();
        }
        return val.to_ullong();
    }
    std::string to_string() {
        std::string ret;
        bi n = *this;
        if(sign()){
            n = n.convert_c2();
        }
        std::vector<int> d(1,0);
        std::vector<int> b(1,1);
        for(int i = 0; i < (int)N; i++){
            if(n.val[i]){
                add_decimal(d,b);
            }
            add_decimal(b,b);
        }
        for(int x : d){
            ret += (char)(x + '0');
        }
        if(sign()){
            ret += "-";
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

private:
    bool sign(){ return val[N-1]; }
    bi convert_c2(){
        bi<N> temp = *this;
        temp.val.flip(); 
        temp = temp+bi<N>(1);
        return temp;
    }
    void div(bi<N> d, bi<N> &q, bi<N> &e){
        bi<N> n = *this;
        bool ret_sign = false;
        if(sign()){
            n = n.convert_c2();
            ret_sign = !ret_sign;
        }
        if(d.sign()){
            d = d.convert_c2();
            ret_sign = !ret_sign;
        }
        if(d.val.count()==1){
            for(int i = 0; i < (int)N; i++){
                if(d.val[i]){
                    q = n;
                    q.val >>= i;
                    break;
                }
            }
            e = n - q * d;
        }else{
            for(int i = (int)N - 1; i >= 0; i--){
                e.val <<= 1;
                e.val[0] = n.val[i];
                if(e >= d){
                    e = e - d;
                    q.val.set(i);
                }
            }
        }
        if(ret_sign){
            q = q.convert_c2();
        }
        if(sign()){
            e = e.convert_c2();
        }
    }
    void add_decimal(std::vector<int> &A, std::vector<int> &B){
        int sum, carry = 0;
        for(int i = 0; i < (int)B.size(); i++){
            sum = B[i] + carry;
            if(i < (int)A.size()){
                sum += A[i];
            }
            carry = sum / 10;
            if(i < (int)A.size()){
                A[i] = sum % 10;
            }else{
                A.emplace_back(sum % 10);
            }
        }
        if(carry > 0){
            A.emplace_back(carry);
        }
    }
};
