struct node {
  int element;
  int count = 0;
};
node n1;
node combine(node &x, node &y) {
  if (x.element == y.element) {
    node ans;
    ans.element = x.element;
    ans.count = x.count + y.count;
    return ans;
  }
  if (x.element < y.element)
    return x;
  else
    return y;
}
struct segtree
{
  int size;
  vector<node> sums;
  void init(int n) {
    size = 1;
    while (size < n) {
      size *= 2;
    }
    n1.element = INT_MAX;
    n1.count = 0;
    sums = vector<node>(2 * size, n1);
  }

  void update(int index, int value, int cur, int left, int right) {
    // if size of segment =1 leaf nodes
    if (right - left == 1) {
      n1.element = value;
      n1.count = 1;
      sums[cur] = n1;
      return;
    }
    int mid = left + (right - left) / 2;
    if (index < mid) {
      update(index, value, 2 * cur + 1, left, mid);
    }
    else
      update(index, value, 2 * cur + 2, mid, right);
// change operator as per problem.
    sums[cur] = combine(sums[2 * cur + 1], sums[2 * cur + 2]);
  }
  node sum(int l, int r, int cur, int left, int right) {
    // segment doesn't intersect
    if (left >= r or l >= right) {
      n1.element = INT_MAX;
      n1.count = 0;
      return n1;
    }
    // [l,r] lies inside [left,right]
    if (left >= l and right <= r) {
      return sums[cur];
    }
    int mid = left + (right - left) / 2;
    node left_sum = sum(l, r, 2 * cur + 1, left, mid);
    node right_sum = sum(l, r, 2 * cur + 2, mid, right);
    // trace(cur, left_sum.element, left_sum.count, right_sum.element, right_sum.count);
    node ans = combine(left_sum, right_sum);
    // trace(ans.element, ans.count);
    return ans;
  }
  node sum(int l, int r) {
    return sum(l, r, 0, 0, size);
  }

  void update(int index, int value) {
    update(index, value, 0, 0, size);
  }

};