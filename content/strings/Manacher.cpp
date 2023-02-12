/** manacher[i] = length of the longest palindrome:
 of odd size and center i/2 if i is even
 of even size and centers i/2 and (i+1)/2 if i is odd*/
vector<int> manacher(const string &s)
{
    int n = 2 * s.length();
    vector<int> rad(n);

    for (int i = 0, j = 0, k; i < n; i += k, j = max(j - k, 0))
    {
        for (; i >= j && i + j + 1 < n
               && s[(i - j) / 2] == s[(i + j + 1) / 2]; ++j);
        rad[i] = j;
        for (k = 1; i >= k &&
                    rad[i] >= k && rad[i - k] != rad[i] - k; ++k)
            rad[i + k] = min(rad[i - k], rad[i] - k);
    }

    return rad;
}

bool is_pal(const vector<int> &rad, int b, int e)
{
    int n = rad.size() / 2;
    return b >= 0 && e < n && rad[b + e] >= e - b + 1;
}