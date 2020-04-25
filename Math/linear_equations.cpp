#include <bits/stdc++.h>

using namespace std;

const long double eps = 1e-11;

inline bool is_zero(long double x) {
  return abs(x) < eps;
}

template <typename T>
class LinearEquations {
  int h, w, coeff_w;
  vector <vector <T> > coefficients;

  void gaussian_elimination();

 public:
  LinearEquations() {};
  explicit LinearEquations(const vector <vector <T> > &, const vector <T> &);

  vector <T> solve();
};

template <typename T>
LinearEquations<T>::LinearEquations(const vector <vector <T> > &coeffs, 
                                    const vector <T> &b)
    : coefficients(coeffs) {
  this->h = static_cast<int>(coeffs.size());
  this->coeff_w = static_cast<int>(coeffs[0].size());
  for (int i = 0; i < static_cast<int>(b.size()); ++i)
    this->coefficients[i].push_back(b[i]);
  this->w = static_cast<int>(this->coefficients[0].size());
}

template <typename T>
void LinearEquations<T>::gaussian_elimination() {
  auto &coefficients = this->coefficients;
  int h = this->h, w = this->w, coeff_w = this->coeff_w;

  int r = 0;
  for (int c = 0; c < coeff_w; ++c) {
    int id = -1;
    for (int i = r; i < h; ++i) {
      if (!is_zero(coefficients[i][c]) 
          && (id == -1 || abs(coefficients[id][c]) < abs(coefficients[i][c]))) {
        id = i;
      }
    }
    if (id == -1) {
      continue;
    }
    if (id > r) {
      swap(coefficients[id], coefficients[r]);
    }
    vector <int> calc_ids;
    for (int j = c; j < w; ++j) {
      if (!is_zero(coefficients[r][j])) {
        calc_ids.push_back(j);
      }
    }
    T inv = 1 / coefficients[r][c];
    for (int i = r + 1; i < h; ++i) {
      if (is_zero(coefficients[i][c])) {
        continue;
      }
      T temp = -coefficients[i][c] * inv;
      for (int j : calc_ids) {
        coefficients[i][j] += coefficients[r][j] * temp;
      }
    }
    ++r;
  }
  for (int r = h - 1; r >= 0; --r) {
    for (int c = 0; c < coeff_w; ++c) {
      if (is_zero(coefficients[r][c])) {
        continue;
      }
      T inv = 1 / coefficients[r][c];
      for (int i = r - 1; i >= 0; --i) {
        if (is_zero(coefficients[i][c])) {
          continue;
        }
        T temp = -coefficients[i][c] * inv;
        for (int j = c; j < w; ++j) {
          coefficients[i][j] += coefficients[r][j] * temp;
        }
      }
      break;
    }
  }
}

template <typename T>
vector <T> LinearEquations<T>::solve() {
  int h = this->h, w = this->w, coeff_w = this->coeff_w;
  auto &coefficients = this->coefficients;

  vector <T> ret(coeff_w, 0);
  this->gaussian_elimination();
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < coeff_w; ++j) {
      if (is_zero(coefficients[i][j])) {
        continue;
      }
      ret[j] = coefficients[i][w - 1] / coefficients[i][j];
      break;
    }
  }
  return ret;
}


int main() {
  auto linear_equations = new LinearEquations<double>({{2, 3}, {3, 4}}, {1, 2});
  auto ans = linear_equations->solve();
  for (double x : ans)
    cout << x << endl;
  return 0;
}
