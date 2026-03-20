s = input()
n = len(s)

ans = 0
for i in range(n-3):
    ans += (s[i] + s[i+1] + s[i+2] + s[i+3]) == 'meow'

print(ans)
