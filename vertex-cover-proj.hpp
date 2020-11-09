#pragma once

/// Graph class.
class Graph
{
    /// the number of vertices
    int m_num_vertices;
    std::vector<std::vector<int>> m_adj_mat;
    std::list<unsigned> m_edges;
    // std::unique_ptr<Minisat::Solver> solver;

public:
    /// Constructor. Creates a register with initial value of 0
    Graph();
    /// Sets the number of vertices
    void set_num_vertices(int t_num_vertices);
    /// Returns the number of vertices
    int get_num_vertices();
    /// Returns the adjacency matrix
    std::vector<std::vector<int>> get_adj_mat(); 
    /// Sets the graph vertices entered
    void set_edges(std::list<unsigned> &t_edges);
    /// Initializes adjacency matrix
    bool ini_adjacency_matrix();
    /// Creates the adjacency matrix
    bool adjacency_matrix(std::string &err_msg);
    /// Calculates the shortest path
    // bool dijkstra(std::list<unsigned> coordinates, std::vector<unsigned> &short_path, std::string &err_msg);

    /// Check satisfiability and return vertex cover with miniSAT
    void * vertex_cover(void * res_vec_VC);
    /* Returns approxiamtion 1 vertex cover: Pick a vertex of highest degree (most incident edges). 
    Add it to your vertex cover and throw away all edges incident on that vertex. Repeat till no edges remain.*/
    std::vector<int> approx_VC_1();
    /* Returns approximation 2 vertex cover: Pick an edge (u,v), and add both u and v to your vertex cover. 
    Throw away all edges attached to u and v. Repeat till no edges remain. */
    std::vector<int> approx_VC_2();
    /// Check satisfiability with a specific k
    bool k_vertex_cover(int k, std::vector<std::vector<int>> adj_mat_mod, std::vector<int> &res_vec);
    // /// Get approx_VC_1
    // bool approx_VC_1(std::vector<std::vector<int>> adj_mat_mod, std::vector<int> &res_vec);
    /// Print vertex cover
    bool print_vertex_cover(std::string &msg, std::vector<int> vertex_cover);
};

/**
 * Parses a command line.
 * Returns a character of a command and an optional argument.
 * Returns true on success and false on a parsing error.
 * On error, err_msg contains the error message
 */
bool parse_line (const std::string &line,
                 char &cmd, std::list<unsigned> &nums, std::string &err_msg);

bool parse_num (std::istringstream &input, std::list<unsigned> &nums);

bool print_short_path (std::vector<unsigned> short_path);

