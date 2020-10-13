//Bartosz Wrobel, 302940
#ifndef TSP_CPP_TSP_H
#define TSP_CPP_TSP_H
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <numeric>
using mx = std::vector<std::vector<double>>;
using dpair = std::pair<double, double>;

double get_forbidden_cost();
std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix);

class TSP_cost_matrix{

private:
    mx inner_matrix;
    std::vector<dpair> solution;
public:
    TSP_cost_matrix(mx matrix) : inner_matrix(matrix) {}
    void reduce_row(int row_num);
    void reduce_all_rows();
    void reduce_col(int col_num);
    void reduce_all_cols();
    dpair find_paths();
    bool is_zero_in_row(int row_num);
    bool is_zero_in_col(int col_num);
    bool zeros_check_rows();
    bool zeros_check_cols();
    double get_smallest_inrow(int row_num);
    double get_smallest_incol(int col_num);
    double get_smallest_inrow_forpath(int row_num, int col_num);
    double get_smallest_incol_forpath(int row_num, int col_num);
    void create_new_matrix(double row_to_delete, double col_to_delete);
    std::vector<int> sort_and_give_result();
    void last_step();
    double get_size();
};

#endif //TSP_CPP_TSP_H
