class Solution {
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth, sz, heavy, head, pos;
    int timer = 0;

    vector<int> seg;

    // First DFS: calculate subtree sizes and heavy child
    void dfs1(int u, int p) {
        parent[u] = p;
        sz[u] = 1;
        heavy[u] = -1;

        int maxSize = 0;

        for (int v : adj[u]) {
            if (v == p) continue;

            depth[v] = depth[u] + 1;
            dfs1(v, u);

            sz[u] += sz[v];

            if (sz[v] > maxSize) {
                maxSize = sz[v];
                heavy[u] = v;
            }
        }
    }

    // Second DFS: assign HLD positions
    void dfs2(int u, int h, string& s) {
        head[u] = h;
        pos[u] = timer++;

        if (heavy[u] != -1) {
            dfs2(heavy[u], h, s);
        }

        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            dfs2(v, v, s);
        }
    }

    // Segment tree: build
    void build(int node, int l, int r, string& s) {
        if (l == r) {
            // Find the node occupying this HLD position.
            seg[node] = 0;
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            seg[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;

        if (ql <= l && r <= qr) return seg[node];

        int mid = (l + r) / 2;

        return query(node * 2, l, mid, ql, qr) ^
               query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    // XOR mask of all characters on path u -> v
    int pathQuery(int u, int v) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }

            mask ^= query(1, 0, n - 1, pos[head[u]], pos[u]);

            u = parent[head[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);

        mask ^= query(1, 0, n - 1, pos[u], pos[v]);

        return mask;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;

        adj.assign(n, {});
        parent.assign(n, -1);
        depth.assign(n, 0);
        sz.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);

        timer = 0;

        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs1(0, -1);
        dfs2(0, 0, s);

        seg.assign(4 * n, 0);

        // Store the character mask at each HLD position.
        vector<int> base(n);

        for (int u = 0; u < n; u++) {
            base[pos[u]] = 1 << (s[u] - 'a');
        }

        function<void(int, int, int)> buildTree =
            [&](int node, int l, int r) {
                if (l == r) {
                    seg[node] = base[l];
                    return;
                }

                int mid = (l + r) / 2;

                buildTree(node * 2, l, mid);
                buildTree(node * 2 + 1, mid + 1, r);

                seg[node] =
                    seg[node * 2] ^ seg[node * 2 + 1];
            };

        buildTree(1, 0, n - 1);

        vector<bool> ans;

        for (string& q : queries) {
            string type;
            int u;
            char c;

            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                ss >> c;

                s[u] = c;

                int mask = 1 << (c - 'a');

                update(1, 0, n - 1, pos[u], mask);
            } else {
                int v;
                ss >> v;

                int mask = pathQuery(u, v);

                // At most one character may have odd frequency.
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};