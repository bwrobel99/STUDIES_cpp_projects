//Bartosz Wrobel, 302940
#include "tsp.hpp"

double get_forbidden_cost(){ return NAN; }

std::vector<int> TSP_cost_matrix::sort_and_give_result() {
    std::vector<dpair> sorted_vec;
    dpair tmp;
    std::vector<int> vec_results;

    for (std::size_t i = 0; i < solution.size(); i++) {

        if (i == 0) {

            sorted_vec.push_back(solution[i]);
        }
        tmp = sorted_vec[i];
        for (std::size_t j = 0; j < solution.size(); j++) {
            if (tmp.second == solution[j].first) {

                sorted_vec.push_back(solution[j]);
                break;

            }
        }
    }

    for (int i = 0; i < sorted_vec.size(); i++) {

        vec_results.push_back(std::get<0>(sorted_vec[i])+1);

    }
    return vec_results;
}

void TSP_cost_matrix::create_new_matrix(double row_to_delete, double col_to_delete){

    for(std::size_t i = 0; i<inner_matrix.size(); i++){

        for(std::size_t j= 0; j<inner_matrix.size();j++){

            if(j==col_to_delete or i== row_to_delete) inner_matrix[i][j] = NAN;

        }

    }
    inner_matrix[col_to_delete][row_to_delete] = NAN;

}

double TSP_cost_matrix::get_smallest_incol_forpath(int row_num, int col_num){

    std::vector<double> min_vect;
    for(std::size_t i = 0; i<inner_matrix.size(); i++){

        if (&inner_matrix[i][col_num] != &inner_matrix[row_num][col_num]){

            min_vect.push_back(inner_matrix[i][col_num]);

        }
    }
    min_vect.erase(std::remove_if(std::begin(min_vect),
                                  std::end(min_vect),
                                  [](const auto& value) { return std::isnan(value); }),
                   std::end(min_vect));
    std::sort(min_vect.begin(), min_vect.end());
    return min_vect[0];
}

double TSP_cost_matrix::get_smallest_inrow_forpath(int row_num, int col_num) {

    std::vector<double> min_vect;
    for(std::size_t i = 0; i<inner_matrix.size(); i++){

        if (&inner_matrix[row_num][i] != &inner_matrix[row_num][col_num]){

            min_vect.push_back(inner_matrix[row_num][i]);

        }
    }
    min_vect.erase(std::remove_if(std::begin(min_vect),
                                  std::end(min_vect),
                                  [](const auto& value) { return std::isnan(value); }),
                   std::end(min_vect));
    std::sort(min_vect.begin(), min_vect.end());
    return min_vect[0];

}

double TSP_cost_matrix::get_smallest_incol(int col_num){

    std::vector<double> min_vect;
    for(std::size_t i = 0; i<inner_matrix.size(); i++){

            min_vect.push_back(inner_matrix[i][col_num]);

    }
    min_vect.erase(std::remove_if(std::begin(min_vect),
                                  std::end(min_vect),
                                  [](const auto& value) { return std::isnan(value); }),
                   std::end(min_vect));
    std::sort(min_vect.begin(), min_vect.end());
    return min_vect[0];
}

double TSP_cost_matrix::get_smallest_inrow(int row_num) {

    std::vector<double> min_vect;
    for(std::size_t i = 0; i<inner_matrix.size(); i++){

            min_vect.push_back(inner_matrix[row_num][i]);

    }
    min_vect.erase(std::remove_if(std::begin(min_vect),
                                  std::end(min_vect),
                                  [](const auto& value) { return std::isnan(value); }),
                   std::end(min_vect));
    std::sort(min_vect.begin(), min_vect.end());
    return min_vect[0];
}

bool TSP_cost_matrix::is_zero_in_row(int row_num) {

    for(auto elem : inner_matrix[row_num]){

        if (elem == 0) return true;

    }

    return false;

}

bool TSP_cost_matrix::is_zero_in_col(int col_num) {

    for (std::size_t i = 0; i < inner_matrix.size(); i++) {

        if(inner_matrix[i][col_num] == 0) return true;

    }
    return false;

}

bool TSP_cost_matrix::zeros_check_rows() {

    for (std::size_t i = 0; i < inner_matrix.size(); i++) {

        if (is_zero_in_row(i) == false) return false;

    }
    return true;
}

bool TSP_cost_matrix::zeros_check_cols(){

    for(std::size_t i =0; i<inner_matrix.size(); i++){

        if(is_zero_in_col(i) == false) return false;

    }
    return true;

}

void TSP_cost_matrix::reduce_col(int col_num) {

    double min = get_smallest_incol(col_num);
    for(std::size_t i = 0; i<inner_matrix.size();i++){

        inner_matrix[i][col_num]-=min;

    }

}

void TSP_cost_matrix::reduce_all_cols(){

    std::size_t dim = inner_matrix.size();
    for(std::size_t i = 0; i<dim;i++){

        reduce_col(i);

    }

}

void TSP_cost_matrix::reduce_row(int row_num) {

    double min = get_smallest_inrow(row_num);
    for(auto& elem: inner_matrix[row_num]){

        elem-=min;

    }

}

void TSP_cost_matrix::reduce_all_rows(){

    std::size_t dim = inner_matrix.size();
    for(std::size_t i = 0; i<dim;i++){

        reduce_row(i);

    }

}

dpair TSP_cost_matrix::find_paths() {

    std::vector<std::pair<double, dpair>> pos_ways;
    for(std::size_t i=0; i<inner_matrix.size();i++){

        for(std::size_t j = 0; j<inner_matrix.size(); j++){

            if(inner_matrix[i][j] == 0){

                dpair n_pair = std::make_pair(i,j);
                std::pair<double, dpair> new_pair = std::make_pair(0, n_pair);
                pos_ways.push_back(new_pair);

            }

        }

    }
    for(auto& elem : pos_ways){

        double sum = get_smallest_inrow_forpath(elem.second.first, elem.second.second) + get_smallest_incol_forpath(elem.second.first, elem.second.second);
        elem.first = sum;

    }
    double max_cost = pos_ways[0].first;
    dpair max_pair = pos_ways[0].second;
    for(auto elem : pos_ways){

        if (elem.first > max_cost) {
            max_cost = elem.first;
            max_pair = elem.second;
        }

    }
    solution.push_back(max_pair);
    return max_pair;

}

void TSP_cost_matrix::last_step() {

    std::vector<int> row_indexes;
    std::vector<int> col_indexes;
    if(!zeros_check_rows()){reduce_all_rows();}
    if(!zeros_check_cols()){reduce_all_cols();}
    for(std::size_t i = 0; i<inner_matrix.size() ; i++){

        if(is_zero_in_row(i)) row_indexes.push_back(i);
        if(is_zero_in_col(i)) col_indexes.push_back(i);

    }
    for(std::size_t i = 0; i<row_indexes.size(); i++){

        for(std::size_t j = 0; j<col_indexes.size() ; j++){

            int row_index = row_indexes[i];
            int col_index = col_indexes[j];
            int other_row = row_indexes[row_indexes.size() - 1 - i];
            int other_col = col_indexes[col_indexes.size() - 1 - j];
            if(std::isnan(inner_matrix[row_index][col_index])){

                solution.push_back(std::make_pair(row_index, other_col));
                solution.push_back(std::make_pair(other_row, col_index));

            }

        }

    }



}

double TSP_cost_matrix::get_size() { return inner_matrix.size(); }

std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix){

    std::size_t i = 0;
    TSP_cost_matrix test = TSP_cost_matrix(cost_matrix);
    dpair res;
    while(i<test.get_size()){

        if(!test.zeros_check_rows()){test.reduce_all_rows();}
        if(!test.zeros_check_cols()){test.reduce_all_cols();}
        res = test.find_paths();
        test.create_new_matrix(res.first, res.second);
        if(i==test.get_size() - 3) {test.last_step(); break;}
        i++;

    }
    std::vector<int> final = test.sort_and_give_result();
    return final;

}