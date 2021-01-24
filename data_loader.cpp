#include "data_loader.h"

data_loader::data_loader(std::string _file_path, int _batch_size, double _valid_pct)
    : file_path(_file_path), batch_size(_batch_size), valid_pct(_valid_pct)
{
    // Read in all data
    std::pair<std::vector<std::string>, matrix<double>> all_data = read_csv();

    // Store number of observations (rows) and variables (columns - dependent variable)
    num_obs = all_data.second.get_rows();
    num_vars = all_data.second.get_cols() - 1;
    num_train = floor(num_obs * (1 - valid_pct));
    num_val = num_obs - num_train;

    // Random shuffle to get indicies for train and validation sets
    std::vector<int> inds(num_obs);
    for (int i = 0; i < num_obs; i++)
    {
        inds[i] = i;
    }
    std::random_shuffle(inds.begin(), inds.end());
    
    std::vector<int> train_inds(num_train);
    std::vector<int> val_inds(num_val);
    for (int i = 0; i < num_train; i++)
    {
        train_inds[i] = inds[i];
    }
    std::cout << std::endl;
    for (int i = num_train; i < num_obs; i++)
    {
        val_inds[i - num_train] = inds[i];
    }

    // Indices for x and y variables
    std::vector<int> x_inds(num_vars);
    for (int i = 0; i < num_vars; i++)
    {
        x_inds[i] = i;
    }


    // Partition data into train and val
    train_x = all_data.second.sub_rows(train_inds).sub_cols(x_inds);
    train_y = all_data.second.sub_rows(train_inds).sub_cols({ num_vars });
    val_x = all_data.second.sub_rows(val_inds).sub_cols(x_inds);
    val_y = all_data.second.sub_rows(val_inds).sub_cols({ num_vars });
}


std::pair<std::vector<std::string>, matrix<double>> data_loader::read_csv()
{
    // Column names and data matrix
    std::vector<std::string> col_names;
    std::vector<double> data_vec;

    // Create an input filestream
    std::ifstream my_file(file_path);

    // Make sure the file is open
    if (!my_file.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    double val;

    // Read the column names
    if (my_file.good())
    {
        // Extract the first line in the file
        std::getline(my_file, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while (std::getline(ss, colname, ',')) {

            // Initialize and add <colname, int vector> pairs to result
            col_names.push_back(colname);
        }
    }

    int row_indx = 0;
    int col_indx = 0;
    // Read data, line by line
    while (std::getline(my_file, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);

        // Keep track of the current column index
        col_indx = 0;

        // Extract each integer
        while (ss >> val) {

            // Add the current integer to the 'colIdx' column's values vector
            data_vec.push_back(val);

            // If the next token is a comma, ignore it and move on
            if (ss.peek() == ',') ss.ignore();

            // Increment the column index
            col_indx++;
        }
        row_indx++;
    }
    // Close file
    my_file.close();

    // Create data matrix and return as a pair with column names
    matrix<double> data_mat(row_indx, col_indx, data_vec);
    std::pair<std::vector<std::string>, matrix<double>> result(col_names, data_mat);
    return result;
}
