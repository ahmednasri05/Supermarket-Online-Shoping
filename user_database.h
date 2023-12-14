#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "sqlite-header/sqlite3.h"
#include "check_conn_error.h"
#include "model_users.h"
#include "model_products.h"
#include <vector>

void saveUser(sqlite3* db, Person user)
{
	string query = "INSERT INTO users (name , password, phone, location) VALUES ('" + user.Name + "', '" + user.Password + "', '" + user.PhoneNumber + "', '" + user.Location + "');";

	int req = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
	checkForError(db, req);
}

void saveOrder(sqlite3* db, UserOrder userOrder) {
	string query = "INSERT INTO orders (user_id , product_id, quantity, product_name, product_price) VALUES ('" + to_string(userOrder.UserID) + "', '" + to_string(userOrder.ProductID) + "', '" + to_string(userOrder.Quantity) + "', '" + userOrder.ProductName + "', '" + to_string(userOrder.Price) + "');";

	int req = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
	checkForError(db, req);
}

vector<UserOrder> userOrdersByID(sqlite3* db, string userID) {
	vector<UserOrder> userOrders;
    sqlite3_stmt* stmt;
    string query = "SELECT user_id, product_id, quantity FROM orders WHERE user_id = '" + userID + "';";

    int req = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (req != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return userOrders;
    }

    // Execute the SELECT query
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        UserOrder order;
        order.UserID = sqlite3_column_int(stmt, 0);
        order.ProductID = sqlite3_column_int(stmt, 1); // Assuming product_id is an integer column
        order.Quantity = sqlite3_column_int(stmt, 2); // Assuming quantity is an integer column

        // Add the UserOrder object to the array
        userOrders.push_back(order);
    }
    sqlite3_finalize(stmt); // Finalize the prepared statement
	return userOrders;
}

void saveCategory(sqlite3* db, ProductCategory category) {
	string query = "INSERT INTO categories (category) VALUES ('" + category.CategoryType + "');";

	int req = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
	checkForError(db, req);
}

vector<ProductCategory> getCategories(sqlite3* db) {
	vector<ProductCategory> categories;
    sqlite3_stmt* stmt;
    string query = "SELECT * FROM categories;";

    int req = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (req != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return categories;
    }

    // Execute the SELECT query
    while (sqlite3_step(stmt) == SQLITE_ROW) {

        ProductCategory category;
        category.ID = sqlite3_column_int(stmt, 0);
        const unsigned char* categoryTypeText = sqlite3_column_text(stmt, 1);

        if (categoryTypeText) {
            // Convert the retrieved const char* to a C++ string and assign it to CategoryType
            category.CategoryType = reinterpret_cast<const char*>(categoryTypeText);
        }
        cout << "IDSS " << category.ID << endl;
        // Add the UserOrder object to the array
        categories.push_back(category);
    }
    sqlite3_finalize(stmt); // Finalize the prepared statement
	return categories;
}

void saveProduct(sqlite3* db, Product product) {

	string query = "INSERT INTO products (name, price, quantity, code, category, production_date, expiration_date) VALUES ('" + product.Name + "', '" + to_string(product.Price) + "','" + to_string(product.Quantity) + "' , '" + product.Code + "', '" + product.CategoryType + "', '" + product.ProductionDate + "', '" + product.ExpirationDate + "');";

	int req = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
	checkForError(db, req);
}

Product getProductById(sqlite3* db, string productID) {
	Product product;
    sqlite3_stmt* stmt;
    string query = "SELECT price, quantity, expiration_date, code, name FROM products WHERE code = '" + productID + "';";

    int req = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (req != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return product;
    }

    // Execute the SELECT query
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        UserOrder order;
        product.Price = sqlite3_column_int(stmt, 0); 
        product.Quantity = sqlite3_column_int(stmt, 1); 
         const unsigned char* expirationDate = sqlite3_column_text(stmt, 2);

        if (expirationDate) {
            // Convert the retrieved const char* to a C++ string and assign it to CategoryType
            product.ExpirationDate = reinterpret_cast<const char*>(expirationDate);
        }

        const unsigned char* code = sqlite3_column_text(stmt, 3);

        if (code) {
            // Convert the retrieved const char* to a C++ string and assign it to CategoryType
            product.Code = reinterpret_cast<const char*>(code);
        }

        const unsigned char* productName = sqlite3_column_text(stmt, 4);

        if (productName) {
            // Convert the retrieved const char* to a C++ string and assign it to CategoryType
            product.Name = reinterpret_cast<const char*>(productName);
        }
    }
    sqlite3_finalize(stmt); // Finalize the prepared statement
	return product;
}

void updateProduct(sqlite3* db, Product product) {
    sqlite3_stmt* stmt;
    string query = "UPDATE products SET quantity = '" + to_string(product.Quantity) + "' WHERE code = '" + product.Code + "';";
    
    int req = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (req != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Bind the parameters
    sqlite3_bind_int(stmt, 0, product.Quantity);
    
    
    // Execute the UPDATE query
    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        std::cerr << "Error updating data: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt); // Finalize the prepared statement
}
