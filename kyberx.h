#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

class kyberx
{
public:
    int q = 1664;
    int mod = 2 * q + 1;
    int N = 256;

    void print(auto &encrypted_message)
    {
        cout << "***********************************************************************************************************\n";
        auto [u, v] = encrypted_message;
        cout << "U" << endl;
        print(u);

        cout << "V" << endl;
        print(v);
    }

    void print(vector<vector<vector<int>>> &vec)
    {
        cout << "***********************************************************************************************************\n";
        int m1 = vec.size();
        int m2 = vec[0].size();
        int m3 = vec[0][0].size();
        for (int i = 0; i < m1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                for (int k = 0; k < m3; k++)
                {
                    cout << vec[i][j][k] << ", ";
                }
                cout << endl;
            }
        }
    }

    void print(vector<vector<int>> &vec)
    {
        cout << "***********************************************************************************************************\n";
        int m1 = vec.size();
        int m2 = vec[0].size();
        for (int i = 0; i < m1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                cout << vec[i][j] << ", ";
            }
            cout << endl;
        }
    }

    void print(vector<int> &vec)
    {
        cout << "***********************************************************************************************************\n";
        int m1 = vec.size();
        for (int i = 0; i < m1; i++)
        {
            cout << vec[i] << ", ";
        }
        cout << endl;
    }

private:
    int addMod(int a, int b)
    {
        int val = (a + b) % mod;
        if (val > q)
            val -= mod;
        else if (val < -q)
            val += mod;
        return val;
    }

    vector<int> mul(vector<int> v1, vector<int> v2)
    {
        int n = v1.size();
        vector<int> ret(n, 0);

        for (int i = 0; i < n; i++)
        {
            int a = v2[i];
            for (int j = 0; j < n; j++)
            {
                int val = (a * v1[j]) % mod;
                if (val > q)
                    val -= mod;
                else if (val < -q)
                    val += mod;

                ret[(i + j) % n] += i + j < n ? val : -val;
                ret[(i + j) % n] %= mod;

                if (ret[(i + j) % n] > q)
                    ret[(i + j) % n] -= mod;
                else if (ret[(i + j) % n] < -q)
                    ret[(i + j) % n] += mod;
            }
        }

        return ret;
    }

    vector<int> add(vector<int> &v1, vector<int> &v2)
    {
        int n = v1.size();
        vector<int> ret(n);
        for (int i = 0; i < n; i++)
        {
            int val = (v1[i] + v2[i]) % mod;
            if (val > q)
                val -= mod;
            else if (val < -q)
                val += mod;
            ret[i] = val;
        }

        return ret;
    }
    vector<int> subtract(vector<int> &v1, vector<int> &v2)
    {
        int n = v1.size();
        vector<int> ret(n);
        for (int i = 0; i < n; i++)
        {
            int val = (v1[i] - v2[i]) % mod;
            if (val > q)
                val -= mod;
            else if (val < -q)
                val += mod;
            ret[i] = val;
        }

        return ret;
    }

    vector<vector<vector<int>>> matrix_multiplication(vector<vector<vector<int>>> &matrix1, vector<vector<vector<int>>> &matrix2, vector<vector<vector<int>>> &e)
    {
        int m = matrix1.size();
        int n = matrix1[0].size();
        int t = matrix2[0].size();
        int size = matrix1[0][0].size();

        vector<vector<vector<int>>> ret(m, vector<vector<int>>(t));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < t; j++)
            {
                vector<int> vec = e[i][j];
                for (int k = 0; k < n; k++)
                {
                    vector<int> v = mul(matrix1[i][k], matrix2[k][j]);
                    for (int c = 0; c < size; c++)
                    {
                        vec[c] = addMod(vec[c], v[c]);
                    }
                }
                ret[i][j] = vec;
            }
        }

        return ret;
    }

    vector<vector<vector<int>>> create_Random_Vector(int m1, int m2, int m3, int range, int neg)
    {
        vector<vector<vector<int>>> vec(m1, vector<vector<int>>(m2));

        for (int i = 0; i < m1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                for (int k = 0; k < m3; k++)
                {
                    int val = rand() % range;
                    int r = rand() % 2;
                    if (neg && r == 1)
                        val *= -1;
                    vec[i][j].push_back(val);
                }
            }
        }
        return vec;
    }

    string int_to_binary(int n)
    {
        string str;
        while (n > 0)
        {
            if (n % 2)
                str.push_back('1');
            else
                str.push_back('0');
            n /= 2;
        }
        while (str.size() < 8)
            str.push_back('0');
        reverse(str.begin(), str.end());
        return str;
    }

    vector<string> convert_message_to_binary(string str)
    {
        vector<string> vec;
        string ret = "";

        for (int i = 0; i < str.size(); i++)
        {
            int num = str[i];
            string str = int_to_binary(num);
            ret += str;
            if (ret.size() == N)
            {
                vec.push_back(ret);
                ret = "";
            }
        }
        return vec;
    }

    string convert_message_to_original(vector<string> &vec)
    {
        string ret;
        for (int i = 0; i < vec.size(); i++)
        {
            string str = vec[i];
            int n = str.size();
            for (int i = 0; i < n; i += 8)
            {
                string s;
                for (int j = 0; j < 8; j++)
                {
                    s.push_back(str[i + j]);
                }
                reverse(s.begin(), s.end());
                int num = 0;
                int p = 1;
                for (int j = 0; j < 8; j++)
                {
                    if (s[j] == '1')
                        num += p;
                    p *= 2;
                }
                char ch = num;
                if (ch != '#')
                    ret.push_back(ch);
            }
        }

        return ret;
    }

    pair<vector<vector<vector<int>>>, vector<vector<int>>> encryptFunc(vector<vector<vector<int>>> &A, vector<vector<vector<int>>> &t, vector<vector<int>> &m)
    {
        vector<vector<vector<int>>> r = create_Random_Vector(1, 2, N, 2, 1);

        vector<vector<vector<int>>> e1 = create_Random_Vector(1, 2, N, 2, 1);

        vector<vector<vector<int>>> e2 = create_Random_Vector(1, 2, N, 1, 0);

        vector<vector<vector<int>>> u = matrix_multiplication(r, A, e1);

        vector<vector<vector<int>>> V = matrix_multiplication(r, t, e2);

        vector<vector<int>> v;
        for (int i = 0; i < m.size(); i++)
        {
            vector<int> v1 = add(V[0][0], m[i]);
            v.push_back(v1);
        }

        return {u, v};
    }

    vector<string> decryptFunc(vector<vector<vector<int>>> &s, vector<vector<vector<int>>> &u, vector<vector<int>> &v)
    {
        vector<vector<vector<int>>> e0 = create_Random_Vector(1, 2, N, 1, 0);

        vector<vector<vector<int>>> dv = matrix_multiplication(u, s, e0);

        vector<vector<int>> dE;
        for (int i = 0; i < v.size(); i++)
        {
            vector<int> dE1 = subtract(v[i], dv[0][0]);
            dE.push_back(dE1);
        }

        vector<string> message;
        for (int i = 0; i < v.size(); i++)
        {
            string message1;
            for (int j = 0; j < dE[i].size(); j++)
            {
                if (dE[i][j] < -q / 2 || dE[i][j] > q / 2)
                {
                    message1.push_back('1');
                }
                else
                    message1.push_back('0');
            }
            message.push_back(message1);
        }

        return message;
    }

    tuple<vector<vector<vector<int>>>, vector<vector<vector<int>>>, vector<vector<vector<int>>>> createKeys2()
    {
        vector<vector<vector<int>>> A = create_Random_Vector(2, 2, N, q, 1);

        vector<vector<vector<int>>> s = create_Random_Vector(2, 1, N, 2, 1);

        vector<vector<vector<int>>> e = create_Random_Vector(2, 1, N, 2, 1);

        return {A, s, e};
    }

public:
    pair<vector<vector<vector<int>>>, pair<vector<vector<vector<int>>>, vector<vector<vector<int>>>>> create_keys()
    {
        auto [A, s, e] = createKeys2();

        vector<vector<vector<int>>>
            t = matrix_multiplication(A, s, e);

        vector<vector<vector<int>>> private_key = s;
        pair<vector<vector<vector<int>>>, vector<vector<vector<int>>>> public_key = {A, t};

        return {private_key, public_key};
    }

    pair<vector<vector<vector<int>>>, vector<vector<int>>> encrypt(string &str, auto &public_key)
    {
        int ct = N - str.size() % N;
        while (ct--)
        {
            str.push_back('#');
        }
        auto [A, t] = public_key;

        vector<string> vec = convert_message_to_binary(str);

        vector<vector<int>> m;
        for (int i = 0; i < vec.size(); i++)
        {
            string s = vec[i];
            vector<int> mvec;
            for (int i = 0; i < s.size(); i++)
            {
                if (s[i] == '0')
                {
                    mvec.push_back(0);
                }
                else
                    mvec.push_back(-q);
            }
            m.push_back(mvec);
        }

        auto [u, v] = encryptFunc(A, t, m);

        return {u, v};
    }

    string decrypt(auto &encrypted_message, auto &private_key)
    {
        auto [u, v] = encrypted_message;
        vector<string> message = decryptFunc(private_key, u, v);
        string original_message = convert_message_to_original(message);

        return original_message;
    }
};
