#include <bits/stdc++.h>
using namespace std;
int n,m;
int will_exit[500][500];
int component_size[500][500];

struct Node {
    int x, y;
    bool operator<(const Node &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Node other) const {
        return x == other.x && y == other.y;
    }
};
map<Node, vector<Node>> G;
map<Node, vector<Node>> G_;
int br_minx[500][500], br_maxx[500][500], br_miny[500][500], br_maxy[500][500];

vector<Node> order;
bool visited[500][500];
void visit(Node u) {
    if (visited[u.x][u.y]) return;
    visited[u.x][u.y] = true;
    for (Node &v: G[u]) {
        visit(v);
    }
    order.push_back(u);
}
Node* component[500][500];
void assign(Node u, Node *parent) {
    if (component[u.x][u.y] != nullptr) return;
    component[u.x][u.y] = parent;
    for (Node &v: G_[u]) {
        assign(v, parent);
    }
}

char grid[500][500];
bool exitsGrid(Node u) {
    if (u.x < 0 || u.x >= n || u.y < 0 || u.y >= m) return true;
    if (will_exit[u.x][u.y] != -1) return will_exit[u.x][u.y];

    will_exit[u.x][u.y] = false;
    switch (grid[u.x][u.y]) {
        case '<':
            will_exit[u.x][u.y] = exitsGrid({u.x, u.y-1});
            break;
        case '>':
            will_exit[u.x][u.y] = exitsGrid({u.x, u.y+1});
            break;
        case 'v':
            will_exit[u.x][u.y] = exitsGrid({u.x+1, u.y});
            break;
        case '^':
            will_exit[u.x][u.y] = exitsGrid({u.x-1, u.y});
            break;
        default:
            break;
    }

    return will_exit[u.x][u.y];
}

void expandBoundingRectangle(Node u) {
    Node *p = component[u.x][u.y];
    if (component_size[p->x][p->y] > 1) return;
    if (visited[u.x][u.y]) return;
    visited[u.x][u.y] = true;
    for (Node &v: G[u]) {
        Node *p_v = component[v.x][v.y];
        expandBoundingRectangle(v);
        br_minx[p->x][p->y] = min(br_minx[p->x][p->y], br_minx[p_v->x][p_v->y]);
        br_maxx[p->x][p->y] = max(br_maxx[p->x][p->y], br_maxx[p_v->x][p_v->y]);
        br_miny[p->x][p->y] = min(br_miny[p->x][p->y], br_miny[p_v->x][p_v->y]);
        br_maxy[p->x][p->y] = max(br_maxy[p->x][p->y], br_maxy[p_v->x][p_v->y]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin>>n>>m>>q;

    for (int r=0; r<n; ++r)
        for (int c=0; c<m; ++c) {
            cin>>grid[r][c];
            if (grid[r][c] == '<' && c-1 >= 0) {
                G[{r,c}].push_back({r,c-1});
                G_[{r,c-1}].push_back({r,c});
            }
            if (grid[r][c] == '>' && c+1 < m) {
                G[{r,c}].push_back({r,c+1});
                G_[{r,c+1}].push_back({r,c});
            }
            if (grid[r][c] == '^' && r-1 >= 0) {
                G[{r,c}].push_back({r-1,c});
                G_[{r-1,c}].push_back({r,c});
            }
            if (grid[r][c] == 'v' && r+1 < n) {
                G[{r,c}].push_back({r+1,c});
                G_[{r+1,c}].push_back({r,c});
            }
        }

    // "Pass One"
    memset(will_exit, -1, sizeof(will_exit));
    for (int r=0; r<n; ++r)
        for (int c=0; c<m; ++c)
            will_exit[r][c] = exitsGrid({r,c});

    // "Pass Two"
    memset(component_size, 0, sizeof(component_size));
    memset(visited, false, sizeof(visited));
    for (int r=0; r<n; ++r)
        for (int c=0; c<m; ++c) {
            component[r][c] = nullptr;
            br_minx[r][c] = br_maxx[r][c] = br_miny[r][c] = br_maxy[r][c] = -1;
            visit({r,c});
        }
    for (int i=order.size()-1; i>=0; --i)
        assign(order[i], &order[i]);
    for (int r=0; r<n; ++r)
        for (int c=0; c<m; ++c) {
            Node *p = component[r][c];
            component_size[p->x][p->y]++;
            if (br_minx[p->x][p->y] == -1) {
                br_minx[p->x][p->y] = br_maxx[p->x][p->y] = r;
                br_miny[p->x][p->y] = br_maxy[p->x][p->y] = c;
            } else {
                br_minx[p->x][p->y] = min(br_minx[p->x][p->y], r);
                br_maxx[p->x][p->y] = max(br_maxx[p->x][p->y], r);
                br_miny[p->x][p->y] = min(br_miny[p->x][p->y], c);
                br_maxy[p->x][p->y] = max(br_maxy[p->x][p->y], c);
            }
        }

    // "Pass Three"
    memset(visited, false, sizeof(visited));
    for (int r=0; r<n; ++r) {
        for (int c=0; c<m; ++c) {
            if (exitsGrid({r,c})) continue;
            Node *p = component[r][c];
            if (component_size[p->x][p->y] > 1) continue;
            expandBoundingRectangle({r,c});
        }
    }

    auto inside = [](Node tl, Node br, Node p) {
        return tl.x <= p.x && p.x <= br.x && tl.y <= p.y && p.y <= br.y;
    };
    auto completeCover = [inside](Node tl1, Node br1, Node tl2, Node br2) {
        return !(inside(tl1,br1,tl2) && inside(tl1,br1,br2));
    };

    for (int i=0; i<q; ++i) {
        int rs, cs, r1, c1, r2, c2;
        cin>>rs>>cs>>r1>>c1>>r2>>c2;
        --rs; --cs; --r1; --c1; --r2; --c2;
        if (will_exit[rs][cs]) {
            cout<<"YES\n";
            continue;
        }
        Node *p = component[rs][cs];
        int minx = br_minx[p->x][p->y], maxx = br_maxx[p->x][p->y];
        int miny = br_miny[p->x][p->y], maxy = br_maxy[p->x][p->y];
        bool ans = completeCover({r1,c1}, {r2,c2}, {minx,miny}, {maxx,maxy});
        cout<<(ans ? "YES\n" : "NO\n");
    }
}