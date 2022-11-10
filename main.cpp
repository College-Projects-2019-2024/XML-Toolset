#include <bits/stdc++.h>


#ifndef ONLINE_JUDGE



#else

#define debug(...) 42


#endif



#include <iostream>

using namespace std;
using ll = long long;



#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

#define all(v) v.begin(),v.end()

#define allr(v) v.rbegin(),v.rend()
#define fori(size) for(int i=0; i < (size); i+= 1)
#define forj(size) for(int j=0; j < (size); j+= 1)
#define fork(size) for(int k=0; k < (size); k+= 1)
#define MOD 1000000007


void prefix(vector<ll> &v)
{

    int n = v.size();

    for ( int i = 1; i < n ; i++) v[i] = v[i] + v[i-1];
}

vector<ll> primeList(ll max)
{
    vector<ll> PL;

    if(max <= 2) PL.push_back(2);
    else
    {
        PL = primeList( --max  );

        for(int i = 0; i < PL.size(); i++)
        {
            if(max % PL[i] == 0) return PL;
        }

        PL.push_back(max);
    }
    return PL;
}
ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
ll lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}
ll nCr(int n, int r)
{
    if(r > n - r) r = n - r; // because C(n, r) == C(n, n - r)
    ll ans = 1;
    int i;

    for(i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

ll vec_in_no_dub(vector<ll> &v, ll n)
{
    int x; int it = 0;
    fori(n)
    {
        cin >> x;
        if (i==0 || v[it - 1] != x) v[it++] = x;
    }
    v.resize(it);
    return it;
}

ll getDivisors(ll n)
{
    ll ans = 0;
    for (ll i=1LL; i<=sqrtl(n); i++)
    {
        if (n%i == 0LL)
        {
            if (n/i == i) ans++;
            else ans+=2LL;
        }
    }
    return  ans;
}
void printDivisors(ll n)
{
    for (ll i=1LL; i<=sqrtl(n); i++)
    {
        if (n%i == 0LL)
        {
            if (n/i == i) cout <<" "<< i;
            else cout << " "<< i << " " << n/i;
        }
    }
}

int  n_less_than(vector<ll>&v ,ll n )
{
    return ( lower_bound(all(v) , n)- v.begin());
}

int  n_less_eq(vector<ll>&v ,ll n )
{
    return ( upper_bound(all(v) , n)- v.begin());
}

int  n_greater_eq(vector<ll>&v ,ll n )
{
    return v.size() - (  lower_bound(all(v) , n)- v.begin());
}


ll  n_greater_than(vector<ll>&v ,ll n )
{
    if (n>=v[v.size()-1]) return  0;
    return v.size() - (  upper_bound(all(v) , n)- v.begin());
}
int fact(int n)
{
    if (n <= 1)
        return 1;
    return n*fact(n-1);
}
int nPr(int n, int r)
{
    return fact(n)/fact(n-r);
}




void roate_left(vector<int>&v, int start, int end, int k)
{
    int f= end-start+1;
    k = k%f;
    vector<int> temp(f);

    for(int i = start; i <= end; i++)
    {
        int po = (i+k-start) % f;
        temp[po] = v[i];
    }
    for(int i = start; i <= end; i++)
    {
        v[i]= temp[i-start] ;
    }
}



bool cmp (vector <int> t,vector <int> s, int lastT, int lastS)
{
    //return true if s is less
    fori(26)
    {
        if ( t[i] !=0 && s[i] !=0 )
        {
            if (i==lastT && i==lastS )
            {
                if (s[i] < t[i]) return true;
                else return false;
            }
            else if  (i!=lastT && i!=lastS )
            {
                if (t[i] == s[i] ) continue;
                else if (s[i] > t[i] )return true;
                return false;
            }
        }
        else if ( t[i] ==0 && s[i] !=0 )
        {
            if (lastT <i) return false;

            return true;
        }
        else if  ( t[i] !=0 && s[i] ==0 )
        {
            if (lastS <i) return true;

            return false;
        }

    }
    return true;

}



int random(int min, int max)
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> gen(min, max);
    int a = gen(rng);
    return a;
}


int getSum(long long n)
{
    int sum = 0;
    int m = n;
    while(n > 0)
    {
        m = n % 10;
        sum = sum + m;
        n = n / 10;
    }
    return sum;
}





void printmsg (string s, int line, int CASE)
{
    switch (CASE)
    {
        case 1:
        {
            cout << "line :" <<line;
            cout << ' ' << s<<  " are closed although it was never opened" << endl;
        }
            break;
        case 2:
        {
            cout << "line :" <<line;
            cout << " that was opened and not closed" << ' '<<(s) << endl;
        }
            break;
        case 3:
        {
            cout << "sorry I found the closing of" << ' '<<(s)  << " That was at the line " <<line<< endl;
        }
            break;
        default: {}
    }
}



bool ans()
{
    string  str; stack <pair <string,int>> stac;

    int line  = 0;
    while(getline (cin,str))
    {
        line++;
        int end_pos=0;
        int x=str.length()-1;

        while(end_pos!=string::npos && end_pos!=x)
        {
            int start_pos=str.find('<',end_pos);
            end_pos = str.find('>', end_pos+1);

            if(end_pos==-1 && start_pos==-1) break;

            if(str[start_pos] == '<' && str[start_pos+1] != '/')
            {
                stac.push({str.substr(start_pos+1,end_pos-start_pos-1), (line)});
            }
            else if (str[start_pos+1] == '/')
            {
                if (stac.empty()) printmsg ( str.substr(start_pos + 2, end_pos - start_pos - 2),  line, 1);
                else
                {
                    list <pair <string,int>> myList;
                    while (! stac.empty() && (stac.top().first) != str.substr(start_pos+2,end_pos-start_pos-2))
                    {
                        printmsg(stac.top().first,stac.top().second,2);
                        myList.push_back(stac.top()) ;
                        stac.pop();
                    }
                    if ( !stac.empty()&& stac.top().first == str.substr(start_pos+2,end_pos-start_pos-2)) stac.pop();
                    else
                    {
                        while (!myList.empty())
                        {
                            printmsg(myList.back().first,myList.back().second,3);
                            stac.push(myList.back()) ;
                            myList.pop_back( );
                        }
                        printmsg ( str.substr(start_pos + 2, end_pos - start_pos - 2),  line, 1);
                    }
                }

            }
        }
    }

    while (! stac.empty())
    {
        printmsg(stac.top().first,stac.top().second,2);
        stac.pop();
    }

    return true;
}


int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool tests = false;
    bool yn = false;

    int t = 1; if(tests) cin>>t;
    fori(t)
    {
        if (ans() && yn) cout<<"YES";
        else if ( yn) cout<<"NO";
        cout<<endl;
    }
}