// #pragma once
#include <algorithm> 
#include <climits>
#include <iostream>
#include <list>
// #include <math.h>
#include <memory> // defined std::unique_ptr
#include <sstream>
#include <vector>



// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"


#include "vertex-cover-proj.hpp"

bool verbose2 = false;

Graph::Graph() : m_num_vertices(0) {}
void Graph::set_num_vertices(int t_num_vertices) { m_num_vertices = t_num_vertices;}
int Graph::get_num_vertices() { return m_num_vertices; }
/// Returns the adjacency matrix
std::vector<std::vector<int>> Graph::get_adj_mat(){
    return m_adj_mat;
}

bool Graph::ini_adjacency_matrix() {
    std::vector<int> tem(m_num_vertices, 0);
    m_adj_mat.assign(m_num_vertices, tem);
    if (verbose2){
        std::cout << "Your initialized adjacency matrix: \n";
        for (std::vector<int> &i : m_adj_mat) {
            std::vector<int> vec = i;
            for (int j : vec) {
                std::cout << j << " ";
            }
        std::cout << std::endl;
        }
    }
    return true;
}

void Graph::set_edges(std::list<unsigned> &t_edges) { m_edges = t_edges;}

bool Graph::adjacency_matrix(std::string &err_msg) {
    int num1;
    int num2;
    std::list<unsigned> nums = m_edges;
    int V = m_num_vertices;
    ini_adjacency_matrix();
    if (nums.size() % 2 == 0){
        int nums_size = nums.size();
        for (int i = 0; i != (nums_size/2); ++i){

            num1 = nums.front();
            nums.pop_front();
        

            num2 = nums.front();
            nums.pop_front();

            if (verbose2){
                std::cout << "num1: " << num1 << "num2: " << num2 << std::endl;
            }

            if (num1 < V && num2 < V){
                m_adj_mat[num1][num2] = 1;
                m_adj_mat[num2][num1] = 1;
            } else {
                err_msg = "Vertices out of bounds";
                return false;
            } 
        }  
        if (verbose2) {

            std::cout << "Your populated adjacency matrix: \n";
            for (std::vector<int> &i : m_adj_mat) {
                std::vector<int> vec = i;
                for (int j : vec) {
                    std::cout << j << " ";
                }
            std::cout << std::endl;
            }
        } 
          
        return true;
        
    } 
    err_msg = "Missing argument for vertices";
    return false;
}

// bool shortest_path (std::vector<int> prev, int source, int target, std::vector<unsigned> &short_path, std::string &err_msg){
//     int u = target;

//     if (verbose2) {
//         std::cout << "Entered shortest_path" << std::endl;
//     }
    
//     if (prev[u] != -1 || u == source){
//         while (u != -1){
//             short_path.push_back(u);
//             u = prev[u];
//         }
//         if (verbose2) {
//             std::cout << "Short Path:" << std::endl;
//             for (int i : short_path) {
//                 std::cout << i << " ";
//             }
//             std::cout << std::endl;
//         }
//         return true;
//     } 
//     err_msg = "Unreachable vertex";
//     return false;
    
// }


// Inspired by https://codingnest.com/modern-sat-solvers-fast-neat-underused-part-1-of-n/
// Minisat::Var toVar(int value) {
//     return value-1;
// }

// bool Graph::k_vertex_cover(int k, std::vector<std::vector<int>> adj_mat_mod, std::vector<int> &res_vec){
//     int V = m_num_vertices;

//     std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
//     Minisat::vec<Minisat::Lit> literals_vector;
//     // boolean that indicates satisfiability
//     bool res = false;

//     // vector with the satisfiable solution
//     // std::vector<int> res_vec;
//     solver.reset (new Minisat::Solver());

//         // Not possible because we are compiling in C++11. Check https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
//         // solver = std::make_unique<Minisat::Solver()>;


//     // vec for verbose
//     std::vector<int> vec;
    
//     for (int i = 0; i < k*V ; ++i) {
//     solver->newVar();
//     }
    

//     // First Clause
//     if (verbose2){
//         std::cout << "Clause 1" << std::endl;
//     }
//     for (int i = 1; i <= k ; ++i){
//         for (int j = 1; j <= V; ++j){
//             literals_vector.push(Minisat::mkLit(toVar((j*k)-(k-i))));
//             vec.push_back((j*k)-(k-i));
//         }
//         solver->addClause(literals_vector);
//         literals_vector.clear();

//         if (verbose2){
//             // for (auto i = vec.begin(); i != vec.end(); ++i){
//             // // str += "<";
//             // // str += std::to_string(*i);
//             // std::cout << *i;
//             // }
//             // std::cout << std::endl;
//             // vec.clear();
//         }
//     }

//     // Second Clause
//     if (verbose2){
//         std::cout << "Clause 2" << std::endl;
//     }
//     vec.clear();
//     for (int j = 1; j <= V; ++j){
//         for (int i = 1; i < k ; ++i){            
//             int temp = (j*k)-(k-i);
//             for (int l = temp+1; l <= j*k; ++l){
//                 literals_vector.push(~Minisat::mkLit(toVar(temp)));
//                 vec.push_back(0-temp);
//                 literals_vector.push(~Minisat::mkLit(toVar(l)));
//                 vec.push_back(0-l);
                
//                 solver->addClause(literals_vector);
//                 literals_vector.clear();

//                 if (verbose2){
//                     // std::cout << "temp, l " << temp << l << std::endl;
//                     for (unsigned int i = 0; i != vec.size(); ++i){
//                         std::cout << vec[i];
//                     }
//                     // solver->toDimacs();
//                     std::cout << std::endl;
//                     vec.clear();
//                 }                      
//             }
//         }
//     }


//     // Third clause
//     if (verbose2){
//         std::cout << "Clause 3" << std::endl;
//     }
//     vec.clear();
//     for (int i = 1; i <= k ; ++i){
//         for (int j = 1; j < V; ++j){                        
//             int temp = (j*k)-(k-i);
//             for (int l = temp+k; l <= V*k; l+=k){
//                 literals_vector.push(~Minisat::mkLit(toVar(temp)));
//                 vec.push_back(-temp);
//                 literals_vector.push(~Minisat::mkLit(toVar(l)));
//                 vec.push_back(-l);

//                 solver->addClause(literals_vector);
//                 literals_vector.clear();

//                 if (verbose2){
//                     // for (auto i = vec.begin(); i != vec.end(); ++i){

//                     // std::cout << *i;
//                     // }
//                     // std::cout << std::endl;
//                     // vec.clear();
//                 }                      
//             }
//         }
//     }

//     // Fourth clause
//     vec.clear();
//     if (verbose2){
//         std::cout << "Clause 4" << std::endl;
//     }
//     for (unsigned int i = 0 ; i < adj_mat_mod.size(); ++i){
//         for (unsigned int j = i; j < adj_mat_mod.size(); ++j){
//             if (adj_mat_mod[i][j] == 1){
//                 for (int l = 0; l < k; ++l){
//                     literals_vector.push(Minisat::mkLit(toVar((i+1)*k-l)));
//                     // std::cout << "c4 " << i*l << std::endl;
//                     vec.push_back(((i+1)*k-l));
//                     literals_vector.push(Minisat::mkLit(toVar((j+1)*k-l)));
//                     vec.push_back(((j+1)*k-l));
//                 }
//                 solver->addClause(literals_vector);
//                 literals_vector.clear();

//                 if (verbose2){
//                     for (unsigned int i = 0; i != vec.size(); ++i){
//                         std::cout << vec[i];
//                     }
//                     std::cout << std::endl;
//                     vec.clear();
//                 }                     
//             }
//         }
//     }
    
//     res = solver->solve();

//     if (verbose2) {
//         std::cout << "res is: " << res << std::endl;
//     }

//     if (res){
//         if (verbose2){
//             std::cout << "k * V: " << k*V << std::endl;
//         }
//         for (int i = 1; i <= k*V; ++i){
//             float j = i;
//             if (verbose2) {
//                 std::cout << "k: " << k << "\tV: " << V << std::endl;
//                 std::cout << "Checking vertice: " << j << "\t";
//             }
//             if (Minisat::toInt(solver->modelValue(toVar(i))) == 0){
//                 // Minisat::toLbool(
//                 res_vec.push_back(ceil(j/k)-1);
//                 if (verbose2) {
//                     std::cout << "\nVertice: " << i << "\tVertice ceil: " << ceil(j/k)-1 << std::endl;
//                 }
//             }

//             if (verbose2) {
//                 std::cout << "after the if" << std::endl;
//             }
//         }   
//         return true;         
//     }
//     return false;
// }

// void * Graph::vertex_cover(void * res_vec_VC){
//     bool satisfiable = false;
//     int V = m_num_vertices;

//     int k = 0;

//     std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
//     Minisat::vec<Minisat::Lit> literals_vector;
//     // bool res = false;

//     std::vector<int> res_vec;
    
//     // std::vector<int> res_vec_approx_2;

//     while (!satisfiable && k<V){
//         ++k;
//         // the next line de-allocates existing solver and allocates a new
//         // one in its place.
        
//         if (k_vertex_cover(k, m_adj_mat, res_vec)){
//             satisfiable = true;
//         }
//     }
//     *((std::vector<int>*)res_vec_VC) = res_vec; //https://www.geeksforgeeks.org/void-pointer-c-cpp/
//     return NULL;
// }



// // Calculates the degree of each vertex
// void get_vertex_degree(std::vector<std::vector<int>> &adj_mat){
//     int degree = 0;
//     for (unsigned i = 0; i < adj_mat[0].size(); ++i){
//         for (unsigned j = 0; j < adj_mat.size()-2; ++j){
//             degree = degree + adj_mat[j][i];
//         }
//         adj_mat[adj_mat.size()-1][i] = degree;
//         degree = 0 ;
//     }
// }

// // Adds a row with the index of each vertes and a row with the degree of each vertex
// void fix_adj_mat(std::vector<std::vector<int>> &adj_mat_mod, int V){
//     // std::vector<std::vector<int>> adj_mat_mod = m_adj_mat;
//     std::vector<int> ver_num;
//     std::vector<int> degree(V,0);

//     for (unsigned i = 0; i < adj_mat_mod.size() ; ++i) {
//         ver_num.push_back(i);
//     }

//     // Add a row that accounts for the vertex number
//     adj_mat_mod.push_back(ver_num);

//     // Add a row that accounts for the degree of the vertex
//     adj_mat_mod.push_back(degree);

//     // Calculate the degree of the adjaccency matrix
//     get_vertex_degree(adj_mat_mod);
// }

// // inspired on http://www.cplusplus.com/forum/beginner/31363/#msg169817
// // function to delete a column
// bool delete_column (std::vector<std::vector<int>> &adj_mat_mod, unsigned column_to_delete){
//     // unsigned columnToDelete = 2;
//     bool is_column_deleted = false;
//     for (unsigned i = 0; i < adj_mat_mod.size(); ++i){
//         if (adj_mat_mod[i].size() > column_to_delete){
//             adj_mat_mod[i].erase(adj_mat_mod[i].begin() + column_to_delete);
//             is_column_deleted = true;
//         }
//     }
//     return is_column_deleted;
// }

// // inspired on http://www.cplusplus.com/forum/beginner/31363/#msg169817
// // function to delete a row
// bool delete_row (std::vector<std::vector<int>> &adj_mat_mod, unsigned row_to_delete){
//     bool is_row_deleted = false;
//     if (adj_mat_mod.size() > row_to_delete){
//         adj_mat_mod.erase( adj_mat_mod.begin() + row_to_delete );
//         is_row_deleted = true;
//     }
//     return is_row_deleted;
// }

// int get_graph_degree(std::vector<std::vector<int>> &adj_mat_mod){
//     int graph_degree = 0;
//     for (int i:adj_mat_mod[adj_mat_mod.size()-1]){
//         graph_degree = graph_degree + i;
//     }
//     return graph_degree;
// }

// // for debugging
// void print_mat(std::vector<std::vector<int>> test_mat){
//     for (std::vector<int> i:test_mat){
//         for (int j : i){
//             std::cout << j << " ";
//         }
//         std::cout << "\n";

//     }
// }

// /// Get Approx-VC-1
// std::vector<int> Graph::approx_VC_1(){
//     std::vector<int> res_vec_approx_1;
//     std::vector<std::vector<int>> adj_mat_mod = m_adj_mat;
//     fix_adj_mat(adj_mat_mod, m_num_vertices);
//     // print_mat(adj_mat_mod);

//     int graph_degree = get_graph_degree(adj_mat_mod);
//     int max_degree_vertex;
//     int max_element_index;
//     // int max;
//     unsigned int tries = 0;
//     // int initial_adj_mat_size = adj_mat_mod.size();

//     if (verbose2){
//         std::cout << "inside approx_1" << std::endl;
//     }

//     while (graph_degree !=0){
//         ++tries;
//         if (tries > adj_mat_mod.size()-2){
//             std::cout << "Error: Inside approx_VC_1. Too many tries" << std::endl;
//             return res_vec_approx_1;
//         }
//         // max = *max_element(adj_mat_mod[adj_mat_mod.size()-1].begin(), adj_mat_mod[adj_mat_mod.size()-1].end());
//         // Inspired by https://riptutorial.com/cplusplus/example/11151/find-max-and-min-element-and-respective-index-in-a-vector
//         max_element_index = std::max_element(adj_mat_mod[adj_mat_mod.size()-1].begin(), adj_mat_mod[adj_mat_mod.size()-1].end()) - adj_mat_mod[adj_mat_mod.size()-1].begin();

//         max_degree_vertex = adj_mat_mod[adj_mat_mod.size()-2][max_element_index];

//         res_vec_approx_1.push_back(max_degree_vertex);
//         if (verbose2) {
//             std::cout << "pushed index " << max_degree_vertex << "into res_vec_approx_1" << std::endl;
//         }

//         // iterate over the max_element column and erase the rows that are != 0

//         for (unsigned i = 0; i < adj_mat_mod.size()-2; ++i){
//             if (adj_mat_mod[i][max_element_index] != 0){
//                 adj_mat_mod[i][max_element_index] = 0;
//                 adj_mat_mod[max_element_index][i] = 0;

//                 // if(delete_row(adj_mat_mod, i)){
//                 //     if(delete_column(adj_mat_mod, i)){
//                 //         --max_element_index;                    
//                 //         --i;}
//                 //     else{
//                 //         std::cout << "Error inside approx_VC_1 deleting a column" << std::endl;
//                 //     }
//                 // }
//                 // else{
//                 //     std::cout<< "Error inside approx_VC_1 deleting a row" << std::endl;
//                 // }
//             } 
//         }

//         get_vertex_degree(adj_mat_mod);
//         // print_mat(adj_mat_mod);
//         graph_degree = get_graph_degree(adj_mat_mod);
        
//         // std::cout << "graph_degree: " << graph_degree<< std::endl;
        
//     }
//     return res_vec_approx_1;
// }

// std::array<int, 2> edge_pick (std::vector<std::vector<int>> &adj_mat_mod){
//     std::array<int, 2> edge_picked = {0,0};
//     for (unsigned i = 0; i < adj_mat_mod.size()-2; ++i){
//         for (unsigned j = 0; j < adj_mat_mod.size()-2; ++j){
//             if (adj_mat_mod[i][j]==1){
//                 edge_picked = {(int)i, (int)j};
//                 // std::cout << "edge_picked" << i << " " << j << std::endl;
//                 return edge_picked;
//             }
//         }
//     }
//     std::cout << "Error in edge_picked" << std::endl;
//     return edge_picked;
// }

// /// Get Approx-VC-2
// std::vector<int> Graph::approx_VC_2(){
//     if (verbose2){
//         std::cout << "inside approx_2" << std::endl;
//     }

//     std::vector<int> res_vec_approx_2;
//     std::vector<std::vector<int>> adj_mat_mod = m_adj_mat;

//     fix_adj_mat(adj_mat_mod, m_num_vertices);

//     unsigned int tries = 0;

//     std::array<int, 2> edge_picked = {0,0};

//     int graph_degree = get_graph_degree(adj_mat_mod);
//     while (graph_degree !=0){
//         ++tries;
//         if (tries > adj_mat_mod.size()-2){
//             std::cout << "Error: Inside approx_VC_2. Too many tries" << std::endl;
//             return res_vec_approx_2;
//         }
//         edge_picked = edge_pick(adj_mat_mod);

//         res_vec_approx_2.push_back(edge_picked[0]);
//         res_vec_approx_2.push_back(edge_picked[1]);

//         for (int i : edge_picked){
//             for (unsigned j = 0; j < adj_mat_mod[i].size(); ++j){
//                 if (adj_mat_mod[i][j] == 1){
//                     adj_mat_mod[i][j] = 0;
//                     adj_mat_mod[j][i] = 0;
//                 }
//             }
//         }
//         // std::cout << "\n";
//         // print_mat(adj_mat_mod);
//         get_vertex_degree(adj_mat_mod);

//         graph_degree = get_graph_degree(adj_mat_mod);
//     }    

//     return res_vec_approx_2;

// }

/// Print vertex cover
bool Graph::print_vertex_cover(std::string &msg , std::vector<int> vertex_cover){
    std::sort(vertex_cover.begin(), vertex_cover.end());

    std::cout << msg;

    for (unsigned i = 0; i <vertex_cover.size()-1; ++i){
        std::cout << vertex_cover[i] << "," ;
    }
    std::cout << vertex_cover[vertex_cover.size()-1] << std::endl;
    return true;
}




